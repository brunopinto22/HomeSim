#include "Regra.h"
#include <map>
#include <sstream>

namespace regra {

    RegraType checkRuleType(const std::string& str) {

            static const std::map<std::string, RegraType> stringToEnum = {
                {"igual_a", IGUAL},
                {"maior_que", MAIOR},
                {"menor_que", MENOR},
                {"entre", ENTRE},
                {"fora", FORA}
            };

        auto it = stringToEnum.find(str);
        if (it != stringToEnum.end()) {
            return it->second;
        } else {
            return NOTATYPE;
        }
    }

    std::string checkRuleType(RegraType type) {
        static const std::map<RegraType, std::string> enumToString = {
                {IGUAL, "igual_a"},
                {MAIOR, "maior_que"},
                {MENOR, "menor_que"},
                {ENTRE, "entre"},
                {FORA, "fora"}
        };

        auto it = enumToString.find(type);
        if (it != enumToString.end()) {
            return it->second;
        } else {
            return "NOTATYPE";
        }
    }

    Regra::Regra(int id, sensor::Sensor* sensor, RegraType type) : id(id), type(type), sensor(sensor) {}

    int Regra::getID() const{ return id; }

    RegraType Regra::getType() const { return type; }

    std::string Regra::getInfo() const {
        std::ostringstream oss;

        oss << checkRuleType(type) << " > r" << getID();

        return oss.str();
    }

    Regra& Regra::operator=(const Regra& other) {
        if (this != &other) {
            id = other.id;
            type = other.type;
            sensor = nullptr;
        }
        return *this;
    }


    bool Regra::check() const { return false; }


    RegraIgual::RegraIgual(int id, sensor::Sensor* sensor, int value) : Regra(id, sensor, IGUAL), value(value) { }
    bool RegraIgual::check() const {
        return sensor->getValue() == value;
    }
    std::string RegraIgual::getInfo() const {
        std::ostringstream oss;

        oss << Regra::getInfo() << " : " << sensor->getValueStr() << " == " << value;
        return oss.str();
    }

    RegraMaior::RegraMaior(int id, sensor::Sensor* sensor, int value) : Regra(id, sensor, MAIOR), value(value) { }
    bool RegraMaior::check() const {
        return sensor->getValue() > value;
    }
    std::string RegraMaior::getInfo() const {
        std::ostringstream oss;

        oss << Regra::getInfo() << " : " << sensor->getValueStr() << " > " << value;
        return oss.str();
    }

    RegraMenor::RegraMenor(int id, sensor::Sensor* sensor, int value) : Regra(id, sensor, MENOR), value(value) { }
    bool RegraMenor::check() const {
        return sensor->getValue() < value;
    }
    std::string RegraMenor::getInfo() const {
        std::ostringstream oss;

        oss << Regra::getInfo() << " : " << sensor->getValueStr() << " < " << value;
        return oss.str();
    }

    RegraEntre::RegraEntre(int id, sensor::Sensor* sensor, int value, int value2) : Regra(id, sensor, ENTRE), value(value), value2(value2) { }
    bool RegraEntre::check() const {
        return sensor->getValue() >= value && sensor->getValue() <= value2;
    }
    std::string RegraEntre::getInfo() const {
        std::ostringstream oss;

        oss << Regra::getInfo() << " : " << value << " > " << sensor->getValueStr() << " > " << value2;
        return oss.str();
    }

    RegraFora::RegraFora(int id, sensor::Sensor* sensor, int value, int value2) : Regra(id, sensor, FORA), value(value), value2(value2) { }
    bool RegraFora::check() const {
        return sensor->getValue() <= value && sensor->getValue() >= value2;
    }
    std::string RegraFora::getInfo() const {
        std::ostringstream oss;

        oss << Regra::getInfo() << " : " << value << " > " << sensor->getValueStr() << " < " << value2;
        return oss.str();
    }

} // regra