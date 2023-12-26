#include <sstream>
#include "Componente.h"

namespace componente {
    Componente::Componente(int id, char type, std::string name) : type(type), name(name) {
        std::ostringstream oss;
        oss << type << id;
        this->id = oss.str();
    }

    std::string Componente::getID() const { return id; }

    char Componente::getType() const { return type; }

    std::string Componente::getInfo() const {
        std::ostringstream oss;
        oss << getName() << " > " << getID();
        return oss.str();
    }

    std::string Componente::run() { return ""; }

    std::string Componente::getName() const { return name; }



} // componente