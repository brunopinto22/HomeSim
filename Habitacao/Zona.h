#ifndef HOMESIM_ZONA_H
#define HOMESIM_ZONA_H

#include <string>
#include <vector>
#include <memory>
#include "Propriedade.h"
#include "Componentes/Componente.h"

namespace zona {


    class Zona {
    private:
        int id;

        // coordenadas
        int pos_x, pos_y;

        // propriedades
        std::vector<propriedades::Propriedade*> props;

        // componentes
        std::vector<componente::Componente*> comps;
        int count_Sensors;
        int count_Processors;
        int count_Gadgets;

        std::string error;

    public:
        Zona();
        Zona(int number_id, int x, int y);

        int getID() const;
        // devolve o ID

        int getPosX() const;
        // devolve a posicao em x
        int getPosY() const;
        // devolve a posicao em y

        std::string getError();
        // devolve o ultimo erro ocorrido

        bool setProp(const std::string& type, int new_value);
        // define o valor de uma propriedade
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        int getPropValue(const std::string& type) const;
        std::string getPropValueStr(const std::string& type) const;
        // devolve uma dada popriedade

        propriedades::Propriedade& getProp(propriedades::PropriedadeType type);
        // devolve uma dada popriedade

        int getNumberOfSensors() const;
        // devolve o numero de Sensores na Zona
        int getNumberOfProcessors() const;
        // devolve o numero de Processadores na Zona
        int getNumberOfGadgets() const;
        // devolve o numero de Aparelhos na Zona

        bool addComponent(int number_id, char type, std::string& typeOrCmd);
        // adiciona um componente a Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool addGadget(int number_id, std::string& type);
        // adiciona um Aparelho a Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool addProcessor(int number_id, std::string& cmd);
        // adiciona um Processador a Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool changeProcCmd(int proc_id, const std::string& new_cmd);
        // muda o comando de um dado Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool addSensor(int number_id, std::string& type);
        // adiciona um Sensor a Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool removeComponent(char type, int number_id);
        // remove um dado Componente pelo seu id
        // retorna:     true caso o encontre e remova
        //              false em caso de erro

        bool checkComponent(std::string component_id) const;
        // verifica se um Componente existe na zona
        // retorna:     true caso exista
        //              false caso nao exista

        std::string getComponents();
        // devolve os componentes da Zona

        std::string getComponentsStr();
        // devolve os componentes da Zona com toda a sua informacao

        bool addRule(int rule_id, int sens_id, const std::string &rule_type, const std::string &values, int proc_id);
        // adicona uma Regra acossiada a um Processador e a um Sensor

        bool removeRule(int proc_id, int rule_id);
        // remove uma dada Regra de um Processador
        // retorna:     true caso o encontre e remova
        //              false em caso de erro

        std::string getRules(int proc_id) const;
        // lista as Regras de um Processador

        int getNumberOfRulesOfProcessor(int proc_id);
        // devolve o numero de Regras de um dado Processador
        // retorna:     -1 em caso de erro

        bool linkProcAndGadget(int proc_id, int gadget_id);
        // acossia um Aparelho a saida do um Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool unlinkProcAndGadget(int proc_id, int gadget_id);
        // desacossia um Aparelho a saida do um Processador numa dada Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool sendCmdTo(int gadget_id, std::string command);
        // envia um comando a um Aparelho na Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        bool tick();
        // avanca 1 tick na habitacao
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

    };

} // zona

#endif //HOMESIM_ZONA_H
