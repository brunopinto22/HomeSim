#include "Aparelho.h"
#include <sstream>
#include <utility>

namespace aparelho {
    Aparelho::Aparelho(int id, AparelhoType type, std::string name)
    : componente::Componente(id, static_cast<char>(type), std::move(name)), isOn(false), type(type), ticks_passed(0) {}

    bool Aparelho::getIsOn() const { return isOn; }

    bool Aparelho::turnOnOff() {
        resetTicks();
        isOn = !isOn;
        return isOn;
    }

    int Aparelho::getTicks() const { return ticks_passed; }

    void Aparelho::resetTicks() { ticks_passed = 0; }

    char Aparelho::getType() const { return static_cast<char>(type); }

    void Aparelho::run(std::vector<propriedades::Propriedade *> &props) { ticks_passed++; }

    std::string Aparelho::getInfo() const {
        std::ostringstream oss;

        oss << Componente::getInfo() << " : ";
        if(getIsOn())
            oss << "Ligado";
        else
            oss << "desligado";

        return oss.str();
    }


    Aquecedor::Aquecedor(int id) : Aparelho(id, AparelhoType::AQUECEDOR, "aquecedor") { }

    void Aquecedor::run(std::vector<propriedades::Propriedade*> &props) {
        Aparelho::run(props);

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1){

            auto it = std::find_if(props.begin(), props.end(), [](propriedades::Propriedade* prop) {
                return prop->getName() == "som";
            });

            if (it != props.end())
                (*it) += 5;

            return;
        }

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1){
            auto it = std::find_if(props.begin(), props.end(), [](propriedades::Propriedade* prop) {
                return prop->getName() == "som";
            });

            if (it != props.end())
                (*it) -= 5;
            return;
        }


        if(getIsOn() && getTicks() % 3 == 0 && getTicks() <= 50){
            auto it = std::find_if(props.begin(), props.end(), [](propriedades::Propriedade* prop) {
                return prop->getName() == "temperatura";
            });

            if (it != props.end())
                (*it) += 1;
            return;
        }

    }


    Aspersor::Aspersor(int id) : Aparelho(id, AparelhoType::ASPERSOR, "aspersor") { }

    void Aspersor::run(std::vector<propriedades::Propriedade *> &props) {
        Aparelho::run(props);
    }

    Refrigerador::Refrigerador(int id) : Aparelho(id, AparelhoType::REFRIGERADOR, "refrigerador") { }

    void Refrigerador::run(std::vector<propriedades::Propriedade *> &props) {
        Aparelho::run(props);
    }

    Lampada::Lampada(int id) : Aparelho(id, AparelhoType::LAMPADA, "lampada") { }

    void Lampada::run(std::vector<propriedades::Propriedade *> &props) {
        Aparelho::run(props);
    }

} // aparelho