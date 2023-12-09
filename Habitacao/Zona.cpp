#include <sstream>
#include "Zona.h"

namespace zona {
    Zona::Zona(int number_id, int x, int y):id(number_id), pos_x(x), pos_y(y) {

        props.push_back(new propriedades::Propriedade("temperatura", "C", -273, propriedades::UNSET));
        props.push_back(new propriedades::Propriedade("luz","Lumens", 0, propriedades::UNSET));
        props.push_back(new propriedades::Propriedade("radiacao","Becquerel", 0, propriedades::UNSET));
        props.push_back(new propriedades::Propriedade("vibracao","Hz", 0, propriedades::UNSET));
        props.push_back(new propriedades::Propriedade("humidade","%", 0, 100));
        props.push_back(new propriedades::Propriedade("fumo","%", 0, 100));
        props.push_back(new propriedades::Propriedade("som","dB", 0, propriedades::UNSET));
    }

    Zona::Zona() : Zona(-1, 0, 0) {}

    int Zona::getID() const { return id; }

    int Zona::getPosX() const { return pos_x; }

    int Zona::getPosY() const { return pos_y; }

    std::string Zona::getError(){ return error; }


    bool Zona::setProp(const std::string& type, int new_value) {
        int current;
        std::string min, max, unit;

        auto it = std::find_if(props.begin(), props.end(), [&current, &min, &max, &unit, new_value, type](propriedades::Propriedade* prop) {
            *prop = new_value;
            current = prop->getValue();
            min = prop->getMin();
            max = prop->getMax();
            unit = prop->getUnit();
            return prop->getType() == type;
        });

        if (it == props.end()) {
            std::ostringstream oss;
            oss << "A Propriedade \'" << type << "\' nao existe";
            error = oss.str();
            return false;
        }

        if (current != new_value) {
            std::ostringstream oss;
            oss << "A Propriedade \'" << type << "\' nao tem de estar entre [" << min << "," << max << "]";
            error = oss.str();
            return false;
        }

        std::ostringstream oss;
        oss << current << " " << unit;
        error = oss.str();
        return true;
    }

    int Zona::getPropValue(std::string type) const{
        for(const auto & p : props)
            if(p->getType() == type)
                return p->getValue();

        return propriedades::UNSET;
    }
    std::string Zona::getPropValueStr(std::string type) const{
        for(const auto & p : props)
            if(p->getType() == type)
                return p->getValueStr();
        return "-";
    }





} // zona