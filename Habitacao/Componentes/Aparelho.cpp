#include "Aparelho.h"
#include <sstream>
#include <utility>

namespace aparelho {
    Aparelho::Aparelho(int id, AparelhoType type, std::string name)
    : componente::Componente(id, static_cast<char>(componente::ComponenteType::APARELHO), std::move(name)), isOn(false), ticks_passed(0), type(type) {}

    bool Aparelho::getIsOn() const { return isOn; }

    void Aparelho::turnOn() {
        resetTicks();
        isOn = true;
    }
    void Aparelho::turnOff() {
        resetTicks();
        isOn = false;
    }

    int Aparelho::getTicks() const { return ticks_passed; }

    void Aparelho::resetTicks() { ticks_passed = 0; }

    char Aparelho::getType() const {
        if(!isOn) // esta desligado
            return static_cast<char>(type);

        return std::toupper(static_cast<char>(type));
    }

    void Aparelho::runCommand(std::string command) {

      if(command == "ligar")
        turnOn();

      else if(command == "desligar")
          turnOff();

    }

    std::string Aparelho::run() { ticks_passed++; return "";}

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
    std::string Aquecedor::run() {
        Aparelho::run();
        std::ostringstream oss;

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1){
            oss << "+ " << "5 " << static_cast<char>(propriedades::PropriedadeType::SOM);
            return oss.str();
        }

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1){
            oss << "- " << "5 " << static_cast<char>(propriedades::PropriedadeType::SOM);
            return oss.str();
        }


        if(getIsOn() && getTicks() % 3 == 0 && getTicks() <= 50){
            oss << "+ " << "1 " << static_cast<char>(propriedades::PropriedadeType::TEMPERATURA);
            return oss.str();
        }

        return "";

    }


    Aspersor::Aspersor(int id) : Aparelho(id, AparelhoType::ASPERSOR, "aspersor") { }
    std::string Aspersor::run() {
        Aparelho::run();
        std::ostringstream oss;

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1){
            oss << "+ " << "50 " << static_cast<char>(propriedades::PropriedadeType::HUMIDADE) << " < 75\n"
                << "+ " << "100 " << static_cast<char>(propriedades::PropriedadeType::VIBRACAO);
            return oss.str();
        }

        if(getIsOn() && getTicks() == 2){
            oss << "= " << "0 " << static_cast<char>(propriedades::PropriedadeType::FUMO);
            return oss.str();
        }

        if(getIsOn() && getTicks() == 5)
            turnOff();

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1){
            oss << "- " << "100 " << static_cast<char>(propriedades::PropriedadeType::VIBRACAO);
            return oss.str();
        }

        if(!getIsOn() && getTicks() <= 5){
            oss << "+ " << "50 " << static_cast<char>(propriedades::PropriedadeType::HUMIDADE) << " < 75%\n"
                << "+ " << "100 " << static_cast<char>(propriedades::PropriedadeType::VIBRACAO);
            return oss.str();
        }

        return "";
    }


    Refrigerador::Refrigerador(int id) : Aparelho(id, AparelhoType::REFRIGERADOR, "refrigerador") { }
    std::string Refrigerador::run() {
        Aparelho::run();
        std::ostringstream oss;

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1){
            oss << "+ " << "20 " << static_cast<char>(propriedades::PropriedadeType::SOM);
            return oss.str();
        }

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1){
            oss << "- " << "20 " << static_cast<char>(propriedades::PropriedadeType::SOM);
            return oss.str();
        }


        if(getIsOn() && getTicks() % 3 == 0 && getTicks() <= 50){
            oss << "- " << "1 " << static_cast<char>(propriedades::PropriedadeType::TEMPERATURA);
            return oss.str();
        }

        return "";
    }


    Lampada::Lampada(int id) : Aparelho(id, AparelhoType::LAMPADA, "lampada") { }
    std::string Lampada::run() {
        Aparelho::run();
        std::ostringstream oss;

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1){
            oss << "+ " << "900 " << static_cast<char>(propriedades::PropriedadeType::LUZ);
            return oss.str();
        }

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1){
            oss << "- " << "900 " << static_cast<char>(propriedades::PropriedadeType::LUZ);
            return oss.str();
        }

        return "";
    }

} // aparelho