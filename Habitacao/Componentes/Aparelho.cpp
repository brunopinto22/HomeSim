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
    void Aquecedor::run(std::vector<propriedades::Propriedade *> &props) {
        Aparelho::run(props);

        // primeiro instante ligado
        if (getIsOn() && getTicks() == 1) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::SOM;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(5);
                else
                    (*it)->setValue((*it)->getValue() + 5);
            }

        }

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::SOM;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(0);
                else
                    (*it)->setValue((*it)->getValue() - 5);
            }
        }

        // efeito default ligado
        if(getIsOn() && getTicks() % 3 == 0 && getTicks() <= 50){
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::TEMPERATURA;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(1);
                else
                    (*it)->setValue((*it)->getValue() + 1);
            }
        }

    }


    Aspersor::Aspersor(int id) : Aparelho(id, AparelhoType::ASPERSOR, "aspersor") { }
    void Aspersor::run(std::vector<propriedades::Propriedade *> &props) {
        Aparelho::run(props);

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1) {
            auto humid = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::HUMIDADE;
            });
            auto vib = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::VIBRACAO;
            });

            if (humid != props.end()){
                if((*humid)->getValue() == propriedades::UNSET) {
                    (*humid)->setValue(0);

                }
                else if((*humid)->getValue() < 75){
                    if((*humid)->getValue() == 0)
                        (*humid)->setValue(50);
                    else
                        (*humid)->setValue((*humid)->getValue() + static_cast<int>((*humid)->getValue() / 2));

                }

            }

            if (vib != props.end()){
                if((*vib)->getValue() == propriedades::UNSET)
                    (*vib)->setValue(0);
                else
                    (*vib)->setValue((*vib)->getValue() + 100);
            }

        }

        if(getIsOn() && getTicks() == 2) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::FUMO;
            });

            if (it != props.end())
                (*it)->setValue(0);
        }

        if(getIsOn() && getTicks() == 5)
            turnOff();

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::VIBRACAO;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(0);
                else
                    (*it)->setValue((*it)->getValue() - 100);
            }

        }

    }


    Refrigerador::Refrigerador(int id) : Aparelho(id, AparelhoType::REFRIGERADOR, "refrigerador") { }
    void Refrigerador::run(std::vector<propriedades::Propriedade *> &props) {
        Aparelho::run(props);

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::SOM;
            });

            if (it != props.end())
                (*it)->setValue((*it)->getValue() + 20);
        }

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::SOM;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(0);
                else
                    (*it)->setValue((*it)->getValue() - 20);
            }

        }

        // efeito default ligado
        if(getIsOn() && getTicks() % 3 == 0 && getTicks() <= 50) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::TEMPERATURA;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(0);
                else
                    (*it)->setValue((*it)->getValue() + 1);
            }

        }

    }


    Lampada::Lampada(int id) : Aparelho(id, AparelhoType::LAMPADA, "lampada") { }
    void Lampada::run(std::vector<propriedades::Propriedade *> &props) {
        Aparelho::run(props);

        // primeiro instante ligado
        if(getIsOn() && getTicks() == 1) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::LUZ;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(0);
                else
                    (*it)->setValue((*it)->getValue() + 900);
            }

        }

        // primeiro instante desligado
        if(!getIsOn() && getTicks() == 1) {
            auto it = std::find_if(props.begin(), props.end(), [](const propriedades::Propriedade* p) {
                return p->getType() == propriedades::PropriedadeType::LUZ;
            });

            if (it != props.end()){
                if((*it)->getValue() == propriedades::UNSET)
                    (*it)->setValue(0);
                else
                    (*it)->setValue((*it)->getValue() - 900);
            }
        }

    }

} // aparelho