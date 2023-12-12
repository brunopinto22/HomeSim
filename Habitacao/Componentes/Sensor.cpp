#include "Sensor.h"

namespace sensor {
    Sensor::Sensor(int id, propriedades::Propriedade &prop)
    : componente::Componente(id, 't'), prop(prop) {}

    char Sensor::getType() const {
        return Componente::getType();
    }

    int Sensor::check() const { return prop.getValue(); }


} // sensor