#include <sstream>
#include <utility>
#include "Processador.h"


namespace processador {
    Processador::Processador(int id, std::string command)
    : componente::Componente(id, static_cast<char>(componente::ComponenteType::PROCESSADOR), "processador"), command(std::move(command)) { }

    void Processador::changeType(std::string cmd) {
        this->command = std::move(cmd);
    }

    std::string Processador::getInfo() const {
        std::ostringstream oss;
        oss << Componente::getInfo() << " : " << getNumberOfRules();

        return oss.str();
    }

    bool Processador::areRulesTrue() const {
        if(rules.empty())
            return false;

        for(const auto &r : rules)
            if(!r->check())
                return false;

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
        // procurar a regra
        auto it = std::remove_if(rules.begin(), rules.end(), [rule_id](regra::Regra *rule) {
            return rule->getID() == rule_id;
        });

        // remover a regra
        rules.erase(it, rules.end());
    }

    std::string Processador::getAction() const {
        return command;
    }




} // processador