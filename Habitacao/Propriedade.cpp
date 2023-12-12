#include "Propriedade.h"

#include <utility>
#include <sstream>

namespace propriedades {
    Propriedade::Propriedade() {}

    Propriedade::Propriedade(std::string type, std::string unit, int min, int max) : value(UNSET), name(std::move(type)), unit(std::move(unit)), min(min), max(max) { }

    int Propriedade::getValue() const { return value; }
    std::string Propriedade::getValueStr() const {
        std::ostringstream oss;
        oss << getValue() << " " << getUnit();
        return oss.str();
    }

    std::string Propriedade::getMin() const {
        std::ostringstream oss;
        oss << min;
        return min == UNSET ? "-" : oss.str();
    }

    std::string Propriedade::getMax() const {
        std::ostringstream oss;
        oss << max;
        return max == UNSET ? "-" : oss.str();
    }

    std::string Propriedade::getUnit() const { return unit; }

    std::string Propriedade::getName() const { return name; }

    PropriedadeType Propriedade::getType() const{ return type; }

    bool Propriedade::checkNewValue(int &new_value) const {
        if(max == UNSET)
            return new_value >= min;

        if(min == UNSET)
            return new_value <= max;

        return new_value >= min && new_value <=max;
    }

    Propriedade &Propriedade::operator+(int new_value) {
        int final = this->value + new_value;
        if (checkNewValue(final))
            this->value = final;
        return *this;
    }

    Propriedade &Propriedade::operator-(int new_value) {
        int final = this->value - new_value;
        if (checkNewValue(final))
            this->value = final;
        return *this;
    }

    Propriedade &Propriedade::operator*(int new_value) {
        int final = this->value * new_value;
        if (checkNewValue(final))
            this->value = final;
        return *this;
    }

    Propriedade &Propriedade::operator/(int new_value) {
        int final = this->value / new_value;
        if (checkNewValue(final))
            this->value = final;
        return *this;
    }

    Propriedade &Propriedade::operator=(int new_value) {
        if (checkNewValue(new_value))
            this->value = new_value;
        return *this;
    }


    Temperatura::Temperatura() : Propriedade("luz","Lumens", 0, propriedades::UNSET) { }

    Luz::Luz() : Propriedade("luz","Lumens", 0, propriedades::UNSET) { }

    Radiacao::Radiacao() : Propriedade("radiacao","Becquerel", 0, propriedades::UNSET) { }

    Vibracao::Vibracao() : Propriedade("vibracao","Hz", 0, propriedades::UNSET) { }

    Humidade::Humidade() : Propriedade("humidade","%", 0, 100) { }

    Fumo::Fumo() : Propriedade("fumo","%", 0, 100) { }

    Som::Som() : Propriedade("som","dB", 0, propriedades::UNSET) { }
} // propriedades