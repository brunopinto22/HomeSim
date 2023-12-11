#include <sstream>
#include "Componente.h"

namespace componente {
    Componente::Componente(int id, char type) : type(type) {
        std::ostringstream oss;
        oss << type << id;
        this->id = oss.str();
    }

    std::string Componente::getID() const { return id; }

    char Componente::getType() const { return type; }


} // componente