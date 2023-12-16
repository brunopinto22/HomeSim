#ifndef HOMESIM_APARELHO_H
#define HOMESIM_APARELHO_H

#include "Componente.h"
#include "../Propriedade.h"
#include <vector>

namespace aparelho {

    enum class AparelhoType : char {
        AQUECEDOR = 'a',
        ASPERSOR = 's',
        REFRIGERADOR = 'r',
        LAMPADA = 'l'
    };

    class Aparelho : public componente::Componente{
    private:

        bool isOn;
        // estado de desligado ou ligado

        int ticks_passed;
        // ticks passados desde a ultima mudança no ambiente

        AparelhoType type;
        // tipo do aparelho

    public:
        Aparelho(int id, AparelhoType type, std::string name);

        bool getIsOn() const;
        // devolve o estado do aparelho

        int getTicks() const;
        // devolve ticks passados desde a ultima mudança no ambiente

        void resetTicks();
        // redefine os ticks passados desde a ultima mudança no ambiente

        char getType() const override;
        // devolve o caracter que o descreve

        virtual std::string getInfo() const override;
        // devolve a informacao do componente

        bool turnOnOff();
        // liga/desliga o aparelho

        virtual void run(std::vector<propriedades::Propriedade*>& props);

    };


    class Aquecedor : public Aparelho {
    public:
        Aquecedor(int id);
        void run(std::vector<propriedades::Propriedade*>& props) override;
    };

    class Aspersor : public Aparelho {
    public:
        Aspersor(int id);
        void run(std::vector<propriedades::Propriedade*>& props) override;
    };

    class Refrigerador : public Aparelho {
    public:
        Refrigerador(int id);
        void run(std::vector<propriedades::Propriedade*>& props) override;
    };

    class Lampada : public Aparelho {
    public:
        Lampada(int id);
        void run(std::vector<propriedades::Propriedade*>& props) override;
    };

} // aparelho

#endif //HOMESIM_APARELHO_H
