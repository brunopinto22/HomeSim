#ifndef HOMESIM_PROCESSADOR_H
#define HOMESIM_PROCESSADOR_H

#include <string>
#include <vector>
#include "Componente.h"
#include "Regra.h"

namespace processador {

    class Processador : public componente::Componente{
    private:
        std::string command;
        std::vector<regra::Regra*> rules;

    public:
        Processador(int id, std::string command);

        void changeType(std::string cmd);
        // muda o tipo de Processador
        // se for LIGAR torna se num DESLIGAR
        // e vice versa

        virtual std::string getInfo() const override;
        // devolve a informacao do componente

        bool areRulesTrue() const;
        // verifica se as regras sao todas verdade
        // retorna:     true - caso sejam todas verdade
        //              false - caso contrario

        int getNumberOfRules() const;
        // devolve o numero de Regras

        bool ruleExists(int rule_id) const;
        // verifica se existe a regra no Processador

        std::string getRules() const;
        // devolve a lista de Regras

        void addRule(regra::Regra* rule);
        // adiciona uma Regra ao Processador

        void removeRule(int rule_id);
        // remove uma Regra do Processador

        std::string getAction() const;
        // devolve a acao realizada ao ser verdade
        // retorna:     true - ligar
        //              false - desligar

    };

} // processador

#endif //HOMESIM_PROCESSADOR_H
