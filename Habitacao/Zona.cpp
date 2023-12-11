#include <sstream>
#include "Zona.h"

#include "Componentes/Aparelho.h"
#include "Componentes/Processador.h"
#include "Componentes/Regra.h"


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

    bool Zona::addComponent(int number_id, char type, std::string& typeOrCmd) {

        switch (type) {
            case static_cast<char>(componente::ComponenteType::APARELHO):
                return addGadget(number_id, typeOrCmd);

            case static_cast<char>(componente::ComponenteType::SENSOR):
                return addSensor(number_id, typeOrCmd);

            case static_cast<char>(componente::ComponenteType::PROCESSADOR):
                return addProcessor(number_id, typeOrCmd);

            default:
                std::ostringstream oss;
                oss << "O tipo \'" << type << "\' nao existe";
                error = oss.str();
                return false;
        }

    }

    bool Zona::addGadget(int number_id, std::string &type) {
        std::istringstream iss(type);
        char t;
        if(iss >> t){
            switch (t) {
                case static_cast<char>(aparelho::AparelhoType::AQUECEDOR):
                    comps.push_back(*new aparelho::Aquecedor(number_id));
                    error = "Foi adicionado um Aquecedor";
                    return true;

                case static_cast<char>(aparelho::AparelhoType::ASPERSOR):
                    return true;

                case static_cast<char>(aparelho::AparelhoType::REFRIGERADOR):
                    return true;

                case static_cast<char>(aparelho::AparelhoType::LAMPADA):
                    return true;

                default:
                    error = "O tipo de Aparelho nao foi reconhecido";
                    return false;
            }

        }

        error = "O tipo de Aparelho deveria de ser um caracter";
        return false;
    }

    bool Zona::addProcessor(int number_id, std::string &cmd) {

        if(cmd == "igual_a")
            return true;
        else if(cmd == "maior_que")
            return true;
        else if(cmd == "menor_que")
            return true;
        else if(cmd == "entre")
            return true;
        else if(cmd == "fora")
            return true;

        error = "O comando do Processador nao foi reconhecido";
        return false;
    }

    bool Zona::addSensor(int number_id, std::string &type) {
        std::istringstream iss(type);
        char t;
        if(iss >> t){

        }

        error = "O tipo de Sensor deveria de ser um caracter";
        return false;
    }

    std::string Zona::getComponents() {
        std::ostringstream oss;

        for(const auto & c : comps)
            oss << c.getType() << " ";

        return oss.str();
    }

    std::string Zona::getComponentsStr() {
        std::ostringstream oss;

        for(const auto & c : comps)
            oss << c.getType() << c.getID() << "\n";

        return oss.str();
    }


} // zona