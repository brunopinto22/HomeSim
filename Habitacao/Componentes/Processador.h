#ifndef HOMESIM_PROCESSADOR_H
#define HOMESIM_PROCESSADOR_H

#include <string>
#include <vector>
#include "Componente.h"
#include "Regra.h"

namespace processador {

    enum class ProcessorType : bool {
        LIGAR = true,
        DESLIGAR = false
    };

    class Processador : public componente::Componente{
    private:
        ProcessorType type;
        std::vector<regra::Regra*> rules;

    public:
        Processador(int id, ProcessorType type);

        char getType() const override;

        void changeType();
        // muda o tipo de Processador
        // se for LIGAR torna se num DESLIGAR
        // e vice versa

        virtual std::string getInfo() const override;
        // devolve a informacao do componente

        bool areRulesTrue() const;
        // verifica se as regras sao todas verdade
        // retorna:     true - caso sejam todas verdade
        //              false - caso contrario

        void addRule(regra::Regra* rule);
        // adiciona uma Regra ao Processador

        bool getAction() const;
        // devolve a acao realizada ao ser verdade
        // retorna:     true - ligar
        //              false - desligar

    };

} // processador

#endif //HOMESIM_PROCESSADOR_H
