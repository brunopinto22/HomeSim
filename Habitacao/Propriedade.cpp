#include "Propriedade.h"

#include <utility>
#include <sstream>

namespace propriedades {
    Propriedade::Propriedade() {}

    Propriedade::Propriedade(std::string type, std::string unit, int min, int max) : value(UNSET), type(std::move(type)), unit(std::move(unit)), min(min), max(max) { }

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

    std::string Propriedade::getType() const { return type; }

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


} // propriedades