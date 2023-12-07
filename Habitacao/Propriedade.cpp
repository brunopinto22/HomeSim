#include "Propriedade.h"

#include <utility>

namespace propriedades {
    Propriedade::Propriedade(std::string unit, int min, int max) : value(UNSET), unit(std::move(unit)), min(min), max(max) { }

    int Propriedade::getValue() const { return value; }

    std::string Propriedade::getUnit() const { return unit; }

    bool Propriedade::checkNewValue(int &new_value) const {
        if(max == UNSET)
            return new_value >= min;

        if(min == UNSET)
            return new_value <= max;

        return new_value >= min && new_value <=max;
    }

    Propriedade Propriedade::operator+(int new_value) {
        if (checkNewValue(new_value))
            this->value += new_value;
        return *this;
    }

    Propriedade Propriedade::operator-(int new_value) {
        if (checkNewValue(new_value))
            this->value -= new_value;
        return *this;
    }

    Propriedade Propriedade::operator*(int new_value) {
        if (checkNewValue(new_value))
            this->value *= new_value;
        return *this;
    }

    Propriedade &Propriedade::operator=(int new_value) {
        if (checkNewValue(new_value))
            this->value = new_value;
        return *this;
    }


    Temperature::Temperature() : Propriedade("ºC", -273, UNSET) {}

    Light::Light() : Propriedade("Lumens", 0, UNSET) {}

    Radiation::Radiation() : Propriedade("Becquerel", 0, UNSET) {}

    Vibration::Vibration() : Propriedade("Hz", 0, UNSET) {}

    Humidity::Humidity() : Propriedade("%", 0, 100) {}

    Smoke::Smoke() : Propriedade("Obscuração (%)", 0, 100)  {}

    Sound::Sound() : Propriedade("dB", 0, UNSET)  {}


} // propriedades