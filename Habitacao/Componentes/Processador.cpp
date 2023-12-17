#include <sstream>
#include "Processador.h"


namespace processador {
    Processador::Processador(int id, ProcessorType type)
    : componente::Componente(id, static_cast<char>(componente::ComponenteType::PROCESSADOR), "processador"), type(type) { }

    char Processador::getType() const {
        return Componente::getType();
    }

    void Processador::changeType() {
        if(type == ProcessorType::LIGAR)
            type = ProcessorType::DESLIGAR;
        else
            type = ProcessorType::LIGAR;
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

    bool Processador::getAction() const {
        return static_cast<bool>(type);
    }




} // processador