#include <sstream>
#include "Zona.h"

namespace zona {
    Zona::Zona(int number_id, int x, int y):id(number_id), pos_x(x), pos_y(y) {}
    Zona::Zona() : id(-1) {}

    int Zona::getID() const { return id; }

    int Zona::getPosX() const { return pos_x; }

    int Zona::getPosY() const { return pos_y; }

    int Zona::getTemperature() const { return temperature.getValue(); }
    std::string Zona::getTemperatureStr() const {
        std::ostringstream oss;
        oss << temperature.getValue() << temperature.getUnit();

        return oss.str();
    }

    int Zona::getLight() const { return light.getValue(); }
    std::string Zona::getLightStr() const {
        std::ostringstream oss;
        oss << light.getValue() << light.getUnit();

        return oss.str();
    }

    int Zona::getRadiation() const { return radiation.getValue(); }
    std::string Zona::getRadiationStr() const {
        std::ostringstream oss;
        oss << radiation.getValue() << radiation.getUnit();

        return oss.str();
    }

    int Zona::getVibration() const { return vibration.getValue(); }
    std::string Zona::getVibrationStr() const {
        std::ostringstream oss;
        oss << vibration.getValue() << vibration.getUnit();

        return oss.str();
    }

    int Zona::getHumidity() const { return humidity.getValue(); }
    std::string Zona::getHumidityStr() const {
        std::ostringstream oss;
        oss << humidity.getValue() << humidity.getUnit();

        return oss.str();
    }

    int Zona::getSmoke() const { return smoke.getValue(); }
    std::string Zona::getSmokeStr() const {
        std::ostringstream oss;
        oss << smoke.getValue() << smoke.getUnit();

        return oss.str();
    }

    int Zona::getSound() const { return sound.getValue(); }
    std::string Zona::getSoundStr() const {
        std::ostringstream oss;
        oss << sound.getValue() << sound.getUnit();

        return oss.str();
    }






} // zona