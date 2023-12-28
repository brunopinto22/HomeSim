#ifndef HOMESIM_HABITACAO_H
#define HOMESIM_HABITACAO_H

#include <vector>
#include "Zona.h"

namespace habitacao {

    class Habitacao {
    private:
        int number_id;
        int zone_number_id;
        int rule_number_id;

        // tamanho da habitacao
        int width, height;
        int ticks;

        int number_of_zones; // contador de zonas
        std::vector<zona::Zona*> zonas;

        std::string error;

    public:
        Habitacao();
        Habitacao(int width, int height);

        int getZoneNumberID();
        // devolve o numero do ID para a Zona

        int getRuleNumberID();
        // devolve o numero do ID para a Regra

        int getNumberID();
        // devolve o numero do ID para o Componente

        int getWidth() const;
        // devolve a 'largura' da habitacao

        int getHeight() const;
        // devolve a 'altura' da habitacao

        int getTicks() const;
        // devolve os ticks da habitacao

        std::string getError() const;
        // devolve o ultimo erro ocorrido na habitacao

        int getNumberOfZones() const;
        // devolve o número de Zonas existentes

        bool isZoneTacken(int x, int y);
        // verifica se existe uma zona nas coords

        zona::Zona getZone(int index) const;
        // devolve uma zona

        zona::Zona getZone(int x, int y) const;
        // devolve uma zona

        zona::Zona getZoneByID(int id) const;
        // devolve uma zona

        bool checkZoneID(int id) const;
        // verifica se o ID de Zona existe

        void addZone(int x, int y);
        // adiciona uma zona

        void removeZone(int id);
        // remove uma zona

        bool changeZoneProp(int id, std::string prop_name, int new_value);
        // define o valor de uma propriedade de uma dada zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        static bool checCompType(char type);
        // verifica se o tipo de Componente e valido

        bool addComponent(int zone_id, char type, std::string& typeOrCmd);
        // adiciona um Componente a uma dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool removeComponent(int zone_id, char type, int comp_id);
        // remove um Componente de uma dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool addRule(int zone_id, int proc_id, int sens_id, const std::string& rule_type, const std::string& values);
        // adiciona uma Regra a um Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool removeRule(int zone_id, int proc_id, int rule_id);
        // remove uma Regra de um Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool getProcessorRules(int zone_id, int proc_id);
        // lista as Regras de um Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro
        // ( o output e guardado no error )

        bool changeProcCmd(int zone_id, int proc_id, const std::string& new_cmd);
        // muda o comando de um dado Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool linkProcAndGadget(int zone_id, int proc_id, int gadget_id);
        // acossia um Aparelho a saida do um Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool unlinkProcAndGadget(int zone_id, int proc_id, int gadget_id);
        // desacossia um Aparelho a saida do um Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool sendCommandToGadget(int zone_id, int gadget_id, std::string command);
        // envia um comando a um Aparelho numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool tick();
        // avanca 1 tick na habitacao
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

    };

} // habitacao

#endif //HOMESIM_HABITACAO_H
