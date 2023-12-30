#include <sstream>
#include <utility>
#include "Processador.h"


namespace processador {
    Processador::Processador() : zone_id(-1),
    componente::Componente(-1, static_cast<char>(componente::ComponenteType::PROCESSADOR), "processador"), command(std::move("")), sent(false) { }


    Processador::Processador(int id, int zone_id, std::string command) : zone_id(zone_id),
    componente::Componente(id, static_cast<char>(componente::ComponenteType::PROCESSADOR), "processador"), command(std::move(command)), sent(false) { }

    void Processador::changeType(std::string cmd) {
        this->command = std::move(cmd);
    }

    std::string Processador::getInfo() const {
        std::ostringstream oss;
        oss << Componente::getInfo() << " : " << getNumberOfRules();

        return oss.str();
    }

    int Processador::getOrigin() const { return zone_id; }

    bool Processador::areRulesTrue() {
        if(rules.empty())
            return false;

        for(const auto &r : rules) {
            if (!r->check()) {
                sent = false;
                return false;
            }
        }

        return true;
    }

    int Processador::getNumberOfRules() const {
        return rules.size();
    }

    bool Processador::ruleExists(int rule_id) const {
        // procura a Regra pelo ID
        auto it = std::find_if(rules.begin(), rules.end(), [rule_id](const regra::Regra* rule) {
            return rule->getID() == rule_id;
        });

        return it != rules.end();
    }

    std::string Processador::getRules() const {
        std::ostringstream oss;

        for (const auto& rule : rules)
            oss << " " << rule->getInfo() << "\n";

        return oss.str();
    }

    void Processador::addRule(regra::RegraType type, int id, sensor::Sensor* sen, const std::string& values) {
        std::istringstream iss(values);

        int val1, val2;

        switch (type) {
            case regra::IGUAL:
                if (iss >> val1)
                    rules.push_back(new regra::RegraIgual(id, sen, val1));
                break;

            case regra::MAIOR:
                if (iss >> val1)
                    rules.push_back(new regra::RegraMaior(id, sen, val1));
                break;

            case regra::MENOR:
                if (iss >> val1)
                    rules.push_back(new regra::RegraMenor(id, sen, val1));
                break;

            case regra::ENTRE:
                if (iss >> val1 >> val2)
                    rules.push_back(new regra::RegraEntre(id, sen, val1, val2));
                break;

            case regra::FORA:
                if (iss >> val1 >> val2)
                    rules.push_back(new regra::RegraFora(id, sen, val1, val2));
                break;

            default:
                break;
        }

    }


    void Processador::removeRule(int rule_id) {
        // procurar a Regra
        rules.erase(std::remove_if(rules.begin(), rules.end(), [rule_id](const regra::Regra* rule) {
            return rule->getID() == rule_id;
        }), rules.end());
    }

    bool Processador::gadgetExists(int gadget_id) const {
        auto it = std::find_if(gadgets.begin(), gadgets.end(), [gadget_id](const aparelho::Aparelho *ap) {
            return ap->getID() == static_cast<char>(componente::ComponenteType::APARELHO) + std::to_string(gadget_id);
        });

        return it != gadgets.end();
    }

    void Processador::link(aparelho::Aparelho *aparelho) {
        gadgets.push_back(aparelho);
    }

    void Processador::unlink(int gadget_id) {
        // procurar o Aparelho
        auto it = std::remove_if(gadgets.begin(), gadgets.end(), [gadget_id](aparelho::Aparelho *ap) {
            return ap->getID() == static_cast<char>(componente::ComponenteType::APARELHO) + std::to_string(gadget_id);
        });

        // remover o Aparelho
        gadgets.erase(it, gadgets.end());
    }

    void Processador::notifyGadgets() {
        if(sent)
            return;

        for(const auto& ap : gadgets)
            ap->runCommand(getAction());

        sent = true;
    }

    std::string Processador::getAction() const {
        return command;
    }

    void Processador::run(std::vector<propriedades::Propriedade *> &props) {
        if(areRulesTrue())
            notifyGadgets();
    }


} // processador