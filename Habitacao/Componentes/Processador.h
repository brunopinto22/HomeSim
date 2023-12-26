#ifndef HOMESIM_PROCESSADOR_H
#define HOMESIM_PROCESSADOR_H

#include <string>
#include <vector>
#include "Componente.h"
#include "Regra.h"
#include "Aparelho.h"

namespace processador {

    class Processador : public componente::Componente{
    private:
        std::string command;
        bool sent;

        std::vector<aparelho::Aparelho*> gadgets;
        std::vector<regra::Regra*> rules;

    public:
        Processador(int id, std::string command);

        void changeType(std::string cmd);
        // muda o tipo de Processador
        // se for LIGAR torna se num DESLIGAR
        // e vice versa

        virtual std::string getInfo() const override;
        // devolve a informacao do componente

        bool areRulesTrue();
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

        bool gadgetExists(int gadget_id) const;
        // verifica se o Aparelho ja esta na saida do Processador
        // retorna:     true - caso esteja na saida
        //              false - caso contrario

        void link(aparelho::Aparelho *aparelho);
        // adiciona um aparelho a saida do Processador

        void unlink(int gadget_id);
        // remove um aparelho a saida do Processador

        void notifyGadgets();
        // envia o comando para os Aparelhos associados

        std::string getAction() const;
        // devolve a acao realizada ao ser verdade
        // retorna:     true - ligar
        //              false - desligar

        std::string run() override;
        // corre o Processador

    };

} // processador

#endif //HOMESIM_PROCESSADOR_H
