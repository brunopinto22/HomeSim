#include <sstream>
#include "Zona.h"

#include "Componentes/Aparelho.h"
#include "Componentes/Processador.h"
#include "Componentes/Sensor.h"


namespace zona {
    Zona::Zona(int number_id, int x, int y):id(number_id), pos_x(x), pos_y(y), count_Sensors(0), count_Processors(0), count_Gadgets(0) {
        props.push_back(new propriedades::Temperatura());
        props.push_back(new propriedades::Luz());
        props.push_back(new propriedades::Radiacao());
        props.push_back(new propriedades::Vibracao());
        props.push_back(new propriedades::Humidade());
        props.push_back(new propriedades::Fumo());
        props.push_back(new propriedades::Som());
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
            return prop->getName() == type;
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
        oss << current << "" << unit;
        error = oss.str();
        return true;
    }

    int Zona::getPropValue(const std::string& type) const{
        for(const auto & p : props)
            if(p->getName() == type)
                return p->getValue();

        return propriedades::UNSET;
    }
    std::string Zona::getPropValueStr(const std::string& type) const{
        for(const auto & p : props)
            if(p->getName() == type)
                return p->getValueStr();
        return "-";
    }

    propriedades::Propriedade &Zona::getProp(propriedades::PropriedadeType type) {
        for (propriedades::Propriedade* prop : props)
            if (prop->getType() == type)
                return *prop;
        return *props[0];
    }


    int Zona::getNumberOfSensors() const { return count_Sensors; }
    int Zona::getNumberOfProcessors() const { return count_Processors; }
    int Zona::getNumberOfGadgets() const { return count_Gadgets; }


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
            count_Gadgets++;
            switch (t) {
                case static_cast<char>(aparelho::AparelhoType::AQUECEDOR):
                    comps.push_back(new aparelho::Aquecedor(number_id));
                    error = "Foi adicionado um Aquecedor";
                    return true;

                case static_cast<char>(aparelho::AparelhoType::ASPERSOR):
                    comps.push_back(new aparelho::Aspersor(number_id));
                    error = "Foi adicionado um Aspersor";
                    return true;

                case static_cast<char>(aparelho::AparelhoType::REFRIGERADOR):
                    comps.push_back(new aparelho::Refrigerador(number_id));
                    error = "Foi adicionado um Refrigerador";
                    return true;

                case static_cast<char>(aparelho::AparelhoType::LAMPADA):
                    comps.push_back(new aparelho::Lampada(number_id));
                    error = "Foi adicionado um Lampada";
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

        count_Processors++;
        if(cmd == "ligar"){
            comps.push_back(new processador::Processador(number_id, processador::ProcessorType::LIGAR));
            error = "Foi adicionado um Processador do tipo \'ligar\'";
            return true;
        }
        else if(cmd == "desligar"){
            comps.push_back(new processador::Processador(number_id, processador::ProcessorType::DESLIGAR));
            error = "Foi adicionado um Processador do tipo \'desligar\'";
            return true;
        }

        count_Processors--;
        error = "O comando do Processador nao foi reconhecido";
        return false;
    }

    bool Zona::addSensor(int number_id, std::string &type) {
        std::istringstream iss(type);
        char t;
        if(iss >> t){
            count_Sensors++;
            switch (t) {
                case static_cast<char>(propriedades::PropriedadeType::TEMPERATURA):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::TEMPERATURA)));
                    error = "Foi adicionado um Sensor de Temperatura";
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::VIBRACAO):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::VIBRACAO)));
                    error = "Foi adicionado um Sensor de Movimento";
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::LUZ):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::LUZ)));
                    error = "Foi adicionado um Sensor de Luminosidade";
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::RADIACAO):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::RADIACAO)));
                    error = "Foi adicionado um Sensor de Radiacao";
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::HUMIDADE):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::HUMIDADE)));
                    error = "Foi adicionado um Sensor de Humidade";
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::SOM):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::SOM)));
                    error = "Foi adicionado um Sensor de Som";
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::FUMO):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::FUMO)));
                    error = "Foi adicionado um Sensor de Fumo";
                    return true;

                default:
                    error = "O tipo de Sensor nao foi reconhecido";
                    count_Sensors--;
                    return false;
            }
        }

        error = "O tipo de Sensor deveria de ser um caracter";
        return false;
    }

    std::string Zona::getComponents() {
        std::ostringstream oss;

        for(const auto & c : comps)
            oss << c->getType() << " ";

        return oss.str();
    }

    std::string Zona::getComponentsStr() {
        std::ostringstream oss;

        for(const auto & c : comps)
            oss << c->getInfo() << "\n";

        return oss.str();
    }

} // zona