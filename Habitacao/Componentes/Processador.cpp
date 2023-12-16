#include <sstream>
#include "Processador.h"


namespace processador {
    Processador::Processador(int id, ProcessorType type) : componente::Componente(id, 'p', "processador"), type(type) { }

    char Processador::getType() const {
        return Componente::getType();
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

    bool Processador::getAction() const {
        return static_cast<bool>(type);
    }



} // processador