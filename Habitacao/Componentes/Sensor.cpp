#include <sstream>
#include "Sensor.h"

namespace sensor {
    Sensor::Sensor(int id, propriedades::Propriedade &prop)
    : componente::Componente(id, static_cast<char>(componente::ComponenteType::SENSOR), "sensor"), prop(prop) {}

    char Sensor::getType() const {
        return Componente::getType();
    }

    std::string Sensor::getInfo() const {
        std::ostringstream oss;
        oss << Componente::getInfo() << " : " << getValueStr();

        return oss.str();
    }

    int Sensor::getValue() const { return prop.getValue(); }

    std::string Sensor::getValueStr() const { return prop.getValueStr(); }




} // sensor