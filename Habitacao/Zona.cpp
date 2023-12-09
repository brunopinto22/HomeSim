#include <sstream>
#include "Zona.h"

namespace zona {
    Zona::Zona(int number_id, int x, int y):id(number_id), pos_x(x), pos_y(y) {
        temperature = *new propriedades::Propriedade("C", -273, propriedades::UNSET);
        light = *new propriedades::Propriedade("Lumens", 0, propriedades::UNSET);
        radiation = *new propriedades::Propriedade("Becquerel", 0, propriedades::UNSET);
        vibration = *new propriedades::Propriedade("Hz", 0, propriedades::UNSET);
        humidity = *new propriedades::Propriedade("%", 0, 100);
        smoke = *new propriedades::Propriedade("%", 0, 100);
        sound = *new propriedades::Propriedade("dB", 0, propriedades::UNSET);
    }

    Zona::Zona() : Zona(-1, 0, 0) {}

    int Zona::getID() const { return id; }

    int Zona::getPosX() const { return pos_x; }

    int Zona::getPosY() const { return pos_y; }

    std::string Zona::getError(){ return error; }


    bool Zona::setProp(std::string type, int new_value) {
        int current;
        std::string min, max, unit;

        if(type == "temperatura"){
            min = temperature.getMin();
            max = temperature.getMax();
            unit = temperature.getUnit();

            temperature = new_value;
            current = temperature.getValue();

        } else if(type == "luz"){
            min = light.getMin();
            max = light.getMax();
            unit = light.getUnit();

            light = new_value;
            current = light.getValue();

        } else if(type == "radiacao"){
            min = radiation.getMin();
            max = radiation.getMax();
            unit = radiation.getUnit();

            radiation = new_value;
            current = radiation.getValue();


        } else if(type == "vibracao"){
            min = vibration.getMin();
            max = vibration.getMax();
            unit = vibration.getUnit();

            vibration = new_value;
            current = vibration.getValue();

        } else if(type == "humidade"){
            min = humidity.getMin();
            max = humidity.getMax();
            unit = humidity.getUnit();

            humidity = new_value;
            current = humidity.getValue();

        } else if(type == "fumo"){
            min = smoke.getMin();
            max = smoke.getMax();
            unit = smoke.getUnit();

            smoke = new_value;
            current = smoke.getValue();

        } else if(type == "som"){
            min = sound.getMin();
            max = sound.getMax();
            unit = sound.getUnit();

            sound = new_value;
            current = sound.getValue();

        } else {
            std::ostringstream oss;
            oss << "A Proppriedade \'" << type << "\' nao existe";
            error = oss.str();
            return false;
        }

        if(current != new_value){
            std::ostringstream oss;
            oss << "A Proppriedade \'" << type << "\' nao tem de estar entre [" << min << "," << max << "]";
            error = oss.str();
            return false;
        }

        std::ostringstream oss;
        oss << current << " " << unit;
        error = oss.str();
        return true;
    }

    int Zona::getTemperature() const { return temperature.getValue(); }
    std::string Zona::getTemperatureStr() const { return temperature.getValueStr(); }

    int Zona::getLight() const { return light.getValue(); }
    std::string Zona::getLightStr() const { return light.getValueStr(); }

    int Zona::getRadiation() const { return radiation.getValue(); }
    std::string Zona::getRadiationStr() const { return radiation.getValueStr(); }

    int Zona::getVibration() const { return vibration.getValue(); }
    std::string Zona::getVibrationStr() const { return vibration.getValueStr(); }

    int Zona::getHumidity() const { return humidity.getValue(); }
    std::string Zona::getHumidityStr() const { return humidity.getValueStr(); }

    int Zona::getSmoke() const { return smoke.getValue(); }
    std::string Zona::getSmokeStr() const { return smoke.getValueStr(); }

    int Zona::getSound() const { return sound.getValue(); }
    std::string Zona::getSoundStr() const { return sound.getValueStr(); }




} // zona