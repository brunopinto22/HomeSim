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
            prop->setValue(new_value);
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
        std::ostringstream oss;
        std::istringstream iss(type);

        char t;
        if(iss >> t){
            count_Gadgets++;
            switch (t) {
                case static_cast<char>(aparelho::AparelhoType::AQUECEDOR):
                    comps.push_back(new aparelho::Aquecedor(number_id));
                    oss << "Foi adicionado um Aquecedor \'a" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(aparelho::AparelhoType::ASPERSOR):
                    comps.push_back(new aparelho::Aspersor(number_id));
                    oss << "Foi adicionado um Aspersor \'a" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(aparelho::AparelhoType::REFRIGERADOR):
                    comps.push_back(new aparelho::Refrigerador(number_id));
                    oss << "Foi adicionado um Refrigerador \'a" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(aparelho::AparelhoType::LAMPADA):
                    comps.push_back(new aparelho::Lampada(number_id));
                    oss << "Foi adicionada uma Lampada \'a" << number_id << "\'";
                    error = oss.str();
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
        std::ostringstream oss;

        // verificar se o id existe
        // Check if the ID already exists
        for (const auto& comp : comps) {
            if (comp->getID() == (static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(number_id))) {
                oss << "O Processador com o ID \'p" << number_id << "\' já existe na Zona_" << getID();
                error = oss.str();
                return false;
            }
        }

        count_Processors++;
        comps.push_back(new processador::Processador(number_id, this->getID(), cmd));
        oss << "Foi adicionado um Processador \'p" << number_id << "\' do tipo \'" << cmd << "\'";
        error = oss.str();
        return true;

    }

    bool Zona::changeProcCmd(int proc_id, const std::string &new_cmd) {
        std::ostringstream oss;

        // procurar o Processador
        auto processorIt = std::find_if(comps.begin(), comps.end(), [proc_id](const componente::Componente* comp) {
            return comp->getID() == "p" + std::to_string(proc_id);
        });
        if (processorIt == comps.end()) {
            oss << "O Processador com o ID " << proc_id << " nao foi encontrado";
            error = oss.str();
            return false;
        }

        processador::Processador* proc = dynamic_cast<processador::Processador*>(*processorIt);

        if(proc->getAction() == new_cmd){
            oss << "O comando Processador \'p" << proc_id << "\' ja e \'" << new_cmd << "\'";
            error = oss.str();
            return false;
        }

        proc->changeType(new_cmd);
        oss << "O comando do Processador \'p" << proc_id << "\' foi mudado para \'" << new_cmd << "\'";
        error = oss.str();
        return true;
    }

    bool Zona::addSensor(int number_id, std::string &type) {
        std::ostringstream oss;
        std::istringstream iss(type);
        char t;
        if(iss >> t){
            count_Sensors++;
            switch (t) {
                case static_cast<char>(propriedades::PropriedadeType::TEMPERATURA):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::TEMPERATURA)));
                    oss << "Foi adicionado um Sensor de Temperatura \'s" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::VIBRACAO):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::VIBRACAO)));
                    oss << "Foi adicionado um Sensor de Movimento \'s" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::LUZ):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::LUZ)));
                    oss << "Foi adicionado um Sensor de Luminosidade \'s" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::RADIACAO):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::RADIACAO)));
                    oss << "Foi adicionado um Sensor de Radiacao \'s" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::HUMIDADE):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::HUMIDADE)));
                    oss << "Foi adicionado um Sensor de Humidade \'s" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::SOM):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::SOM)));
                    oss << "Foi adicionado um Sensor de Som \'s" << number_id << "\'";
                    error = oss.str();
                    return true;

                case static_cast<char>(propriedades::PropriedadeType::FUMO):
                    comps.push_back(new sensor::Sensor(number_id, getProp(propriedades::PropriedadeType::FUMO)));
                    oss << "Foi adicionado um Sensor de Fumo \'s" << number_id << "\'";
                    error = oss.str();
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

    bool Zona::removeComponent(char type, int number_id) {
        std::string id_Str = type + std::to_string(number_id);

        auto it = std::find_if(comps.begin(), comps.end(), [id_Str](const componente::Componente* comp) {
            return comp->getID() == id_Str;
        });

        if (it != comps.end()) {
            error = "O " + (*it)->getInfo() + " foi removido";
            delete *it;
            comps.erase(it);
            return true;
        }

        error = "Nao foi encontrado o Componente \'" + id_Str + "\'";
        return false;
    }

    bool Zona::checkComponent(std::string component_id) const {
        auto checkComp = std::find_if(comps.begin(), comps.end(), [component_id](const componente::Componente* comp) {
            return comp->getID() == component_id;
        });
        return checkComp != comps.end();
    }

    std::string Zona::getComponents() {
        std::ostringstream oss;

        for(const auto & c : comps)
            if(c->getType() != static_cast<char>(componente::ComponenteType::PROCESSADOR))
                oss << " " << c->getType();

        return oss.str();
    }

    std::string Zona::getComponentsStr() {
        std::ostringstream oss;

        for(const auto & c : comps)
            oss << c->getInfo() << "\n";

        return oss.str();
    }

    bool Zona::addRule(int rule_id, int sens_id, const std::string &rule_type, const std::string &values, int proc_id) {
        std::ostringstream oss;
        std::istringstream iss(values);

        // procurar o Processador
        auto processorIt = std::find_if(comps.begin(), comps.end(), [proc_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(proc_id);
        });
        if (processorIt == comps.end()) {
            oss << "O Processador com o ID " << proc_id << " nao foi encontrado";
            error = oss.str();
            return false;
        }

        // procurar o Sensor
        auto sensorIt = std::find_if(comps.begin(), comps.end(), [sens_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::SENSOR) + std::to_string(sens_id);
        });
        if (sensorIt == comps.end()) {
            oss << "O Sensor com o ID " << sens_id << " nao foi encontrado";
            error = oss.str();
            return false;
        }

        processador::Processador* proc = dynamic_cast<processador::Processador*>(*processorIt);
        sensor::Sensor* sen = dynamic_cast<sensor::Sensor*>(*sensorIt);

        int val1, val2;
        switch (regra::checkRuleType(rule_type)) {
            case regra::IGUAL:
                if(iss >> val1){}
                else {
                    error = "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1]";
                    return false;
                }
                break;

            case regra::MAIOR:
                if(iss >> val1){}
                else {
                    error = "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1]";
                    return false;
                }
                break;

            case regra::MENOR:
                if(iss >> val1){}
                else {
                    error = "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1]";
                    return false;
                }
                break;

            case regra::ENTRE:
                if(iss >> val1 >> val2){}
                else {
                    error = "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2]";
                    return false;
                }
                break;

            case regra::FORA:
                if(iss >> val1 >> val2){}
                else {
                    error = "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2]";
                    return false;
                }
                break;

            default:
                oss << "O tipo de Regra \'" << rule_type << "\' nao existe";
                error = oss.str();
            return false;
        }

        // adicionar a Regra ao Processador
        proc->addRule(regra::checkRuleType(rule_type), rule_id, sen, values);

        oss << "Foi criada uma Regra \'r" << rule_id << "\' acossiada ao Processador " << proc_id ;
        error = oss.str();
        return true;
    }

    processador::Processador Zona::getProcessor(int id) const {
        // procura o Processador
        std::string targetID = static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(id);
        auto it = std::find_if(comps.begin(), comps.end(), [targetID](const componente::Componente* comp) {
            return comp->getID() == targetID;
        });

        if (it != comps.end()) {
            return dynamic_cast<const processador::Processador&>(*(*it));
        } else {
            return {};
        }
    }

    bool Zona::removeRule(int proc_id, int rule_id) {
        std::ostringstream oss;

        // procurar o Processador
        auto processorIt = std::find_if(comps.begin(), comps.end(), [proc_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(proc_id);
        });
        if (processorIt == comps.end()) {
            oss << "O Processador com o ID " << proc_id << " nao foi encontrado";
            error = oss.str();
            return false;
        }
        processador::Processador* proc = dynamic_cast<processador::Processador*>(*processorIt);


        if(!proc->ruleExists(rule_id)){
            oss << "A regra \'r" << proc_id << "\' nao existe no Processador \'" << proc->getID() << "\'";
            error = oss.str();
            return false;
        }

        // remove a Regra do Processador
        proc->removeRule(rule_id);
        oss << "Foi removida uma Regra \'r" << std::to_string(proc_id) << "\' acossiada ao Processador " << proc_id ;
        error = oss.str();
        return true;
    }

    std::string Zona::getRules(int proc_id) const {
        std::ostringstream oss;

        // procurar o Processador
        auto processorIt = std::find_if(comps.begin(), comps.end(), [proc_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(proc_id);
        });
        if (processorIt == comps.end()) {
            oss << "O Processador com o id=" << proc_id << " nao existe";
            return oss.str();
        }

        processador::Processador* proc = dynamic_cast<processador::Processador*>(*processorIt);
        oss << "Regras de " << proc->getID() << "\n"
            << proc->getRules();

        return oss.str();
    }

    int Zona::getNumberOfRulesOfProcessor(int proc_id) {
        std::ostringstream oss;

        // procurar o Aparelho
        auto processorIt = std::find_if(comps.begin(), comps.end(), [proc_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(proc_id);
        });

        if (processorIt == comps.end()) {
            oss << "O Processador com o id=" << proc_id << " nao existe";
            error = oss.str();
            return -1;
        }

        processador::Processador* proc = dynamic_cast<processador::Processador*>(*processorIt);

        int num = proc->getNumberOfRules();

        if(num == 0) {
            oss << "O " << proc->getID() << " nao tem nenhuma Regra associada";
            error = oss.str();
        }

        return num;
    }

    bool Zona::linkProcAndGadget(int proc_id, int gadget_id) {
        std::ostringstream oss;

        // procurar o Processador
        auto processorIt = std::find_if(comps.begin(), comps.end(), [proc_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(proc_id);
        });
        if (processorIt == comps.end()) {
            oss << "O Processador com o id=" << proc_id << " nao existe";
            error = oss.str();
            return false;
        }
        // procurar o Aparelho
        auto componentIt = std::find_if(comps.begin(), comps.end(), [gadget_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::APARELHO) + std::to_string(gadget_id);
        });
        if (componentIt == comps.end()) {
            oss << "O Aparelho com o id=" << gadget_id << " nao existe";
            error = oss.str();
            return false;
        }
        processador::Processador* proc = dynamic_cast<processador::Processador*>(*processorIt);
        aparelho::Aparelho* gadget = dynamic_cast<aparelho::Aparelho*>(*componentIt);

        if(proc->gadgetExists(gadget_id)){
            oss << "O Aparelho \'" << static_cast<char>(componente::ComponenteType::APARELHO) << gadget_id << "\' ja esta na saida do Processador \'" << static_cast<char>(componente::ComponenteType::PROCESSADOR) << proc_id << "\'";
            error = oss.str();
            return false;
        }

        // assicia o Aparelho ao Processador
        proc->link(gadget);

        oss << "Foi associado a saida do Processador \'" << static_cast<char>(componente::ComponenteType::PROCESSADOR) << proc_id << "\' o Aparelho \'" << static_cast<char>(componente::ComponenteType::APARELHO) << gadget_id << "\'";
        error = oss.str();
        return true;
    }

    bool Zona::unlinkProcAndGadget(int proc_id, int gadget_id) {
        std::ostringstream oss;

        // procurar o Processador
        auto processorIt = std::find_if(comps.begin(), comps.end(), [proc_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::PROCESSADOR) + std::to_string(proc_id);
        });
        if (processorIt == comps.end()) {
            oss << "O Processador com o id=" << proc_id << " nao existe";
            error = oss.str();
            return false;
        }
        // procurar o Aparelho
        auto componentIt = std::find_if(comps.begin(), comps.end(), [gadget_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::APARELHO) + std::to_string(gadget_id);
        });
        if (componentIt == comps.end()) {
            oss << "O Aparelho com o id=" << gadget_id << " nao existe";
            error = oss.str();
            return false;
        }
        processador::Processador* proc = dynamic_cast<processador::Processador*>(*processorIt);

        if(!proc->gadgetExists(gadget_id)){
            oss << "O Aparelho \'" << static_cast<char>(componente::ComponenteType::APARELHO) << gadget_id << "\' nao esta na saida do Processador \'" << static_cast<char>(componente::ComponenteType::PROCESSADOR) << proc_id << "\'";
            error = oss.str();
            return false;
        }

        // desassicia o Aparelho do Processador
        proc->unlink(gadget_id);

        oss << "Foi desassociado da saida do Processador \'" << static_cast<char>(componente::ComponenteType::PROCESSADOR) << proc_id << "\' o Aparelho \'" << static_cast<char>(componente::ComponenteType::APARELHO) << gadget_id << "\'";
        error = oss.str();
        return true;
    }

    bool Zona::sendCmdTo(int gadget_id, std::string command) {
        std::ostringstream oss;

        // procurar o Processador
        auto componentIt = std::find_if(comps.begin(), comps.end(), [gadget_id](const componente::Componente* comp) {
            return comp->getID() == static_cast<char>(componente::ComponenteType::APARELHO) + std::to_string(gadget_id);
        });
        if (componentIt == comps.end()) {
            oss << "O Aparelho com o id=" << gadget_id << " nao existe";
            error = oss.str();
            return false;
        }

        aparelho::Aparelho* gadget = dynamic_cast<aparelho::Aparelho*>(*componentIt);

        // enviar comando
        gadget->runCommand(command);

        oss << "Foi enviado o comando \'" << command << "\' ao Aparelho \'" << static_cast<char>(componente::ComponenteType::APARELHO) << gadget_id << "\'";
        error = oss.str();
        return true;
    }

    bool Zona::tick() {
        std::ostringstream oss;
        std::string output;

        // correr cada Componente
        for (auto& comp : comps){
            output = comp->run(props);
            if(!output.empty())
                oss << " " << output;
        }

        error = oss.str();
        return true;
    }

} // zona