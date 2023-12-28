#include <sstream>
#include <utility>
#include "Processador.h"


namespace processador {
    Processador::Processador(int id, std::string command)
    : componente::Componente(id, static_cast<char>(componente::ComponenteType::PROCESSADOR), "processador"), command(std::move(command)), sent(false) { }

    void Processador::changeType(std::string cmd) {
        this->command = std::move(cmd);
    }

    std::string Processador::getInfo() const {
        std::ostringstream oss;
        oss << Componente::getInfo() << " : " << getNumberOfRules();

        return oss.str();
    }

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
        auto it = std::find_if(rules.begin(), rules.end(), [rule_id](regra::Regra *rule) {
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

    void Processador::addRule(regra::Regra *rule) {
        rules.push_back(rule);
    }

    void Processador::removeRule(int rule_id) {
        // procurar a Regra
        auto it = std::remove_if(rules.begin(), rules.end(), [rule_id](regra::Regra *rule) {
            return rule->getID() == rule_id;
        });

        // remover a Regra
        rules.erase(it, rules.end());
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