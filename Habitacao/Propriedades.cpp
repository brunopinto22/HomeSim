#include <sstream>
#include "Propriedades.h"

namespace propriedades {
    Propriedades::Propriedades():temperature(nullptr), light(nullptr), radiation(nullptr), vibration(nullptr), humidity(nullptr), smoke(nullptr), sound(nullptr) {}

    int Propriedades::getTemperature() const { return *temperature; }
    std::string Propriedades::getTemperatureStr() const {
        std::ostringstream oss;
        oss << temperature << " ºC";
        return oss.str();
    }
    bool Propriedades::changeTemperature(int new_value) {
        if(new_value < -273)
            return false;
        *temperature = new_value;
        return true;
    }


    int Propriedades::getLight() const { return *light; }
    std::string Propriedades::getLightStr() const {
        std::ostringstream oss;
        oss << light << " Lumens";
        return oss.str();
    }
    bool Propriedades::changeLight(int new_value) {
        if(new_value < 0)
            return false;
        *light = new_value;
        return true;
    }


    int Propriedades::getRadiation() const { return *radiation; }
    std::string Propriedades::getRadiationStr() const {
        std::ostringstream oss;
        oss << radiation << " Becquerel";
        return oss.str();
    }
    bool Propriedades::changeRadiation(int new_value) {
        if(new_value < 0)
            return false;
        *radiation = new_value;
        return true;
    }


    int Propriedades::getVibration() const { return *vibration; }
    std::string Propriedades::getVibrationStr() const {
        std::ostringstream oss;
        oss << vibration << " Hz";
        return oss.str();
    }
    bool Propriedades::changeVibration(int new_value) {
        if(new_value < 0)
            return false;
        *vibration = new_value;
        return true;
    }


    int Propriedades::getHumidity() const { return *humidity; }
    std::string Propriedades::getHumidityStr() const {
        std::ostringstream oss;
        oss << humidity << " %";
        return oss.str();
    }
    bool Propriedades::changeHumidity(int new_value) {
        if(new_value < 0 || new_value > 100)
            return false;
        *humidity = new_value;
        return true;
    }


    int Propriedades::getSomke() const { return *smoke; }
    std::string Propriedades::getSomkeStr() const {
        std::ostringstream oss;
        oss << smoke << " %";
        return oss.str();
    }
    bool Propriedades::changeSmoke(int new_value) {
        if(new_value < 0 || new_value > 100)
            return false;
        *smoke = new_value;
        return true;
    }


    int Propriedades::getSound() const { return *sound; }
    std::string Propriedades::getSoundStr() const {
        std::ostringstream oss;
        oss << sound << " Db";
        return oss.str();
    }
    bool Propriedades::changeSound(int new_value) {
        if(new_value < 0)
            return false;
        *sound = new_value;
        return true;
    }


} // propriedades