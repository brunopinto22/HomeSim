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
        oss << Componente::getInfo() << " : " << rules.size();

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

    void Processador::addRule(regra::Regra *rule) {
        rules.push_back(rule);
    }

    std::string Processador::getAction() const {
        return command;
    }




} // processador