#include "Regra.h"

namespace regra {
    Regra::Regra(RegraType type, sensor::Sensor& sensor) : type(type), sensor(sensor) {}

    RegraType Regra::getType() const { return type; }

    bool Regra::check() const { return false; }


    RegraIgual::RegraIgual(sensor::Sensor& sensor, int value) : Regra(IGUAL, sensor), value(value) { }
    bool RegraIgual::check() const {
        return sensor.getValue() == value;
    }

    RegraMaior::RegraMaior(sensor::Sensor& sensor, int value) : Regra(MAIOR, sensor), value(value) { }
    bool RegraMaior::check() const {
        return sensor.getValue() > value;
    }

    RegraMenor::RegraMenor(sensor::Sensor& sensor, int value) : Regra(MENOR, sensor), value(value) { }
    bool RegraMenor::check() const {
        return sensor.getValue() < value;
    }

    RegraEntre::RegraEntre(sensor::Sensor& sensor, int value, int value2) : Regra(ENTRE, sensor), value(value), value2(value2) { }
    bool RegraEntre::check() const {
        return sensor.getValue() >= value && sensor.getValue() <= value2;
    }

    RegraFora::RegraFora(sensor::Sensor& sensor, int value, int value2) : Regra(FORA, sensor), value(value), value2(value2) { }
    bool RegraFora::check() const {
        return sensor.getValue() <= value && sensor.getValue() >= value2;
    }

} // regra