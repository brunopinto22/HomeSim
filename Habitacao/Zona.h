#ifndef HOMESIM_ZONA_H
#define HOMESIM_ZONA_H

#include <string>
#include <vector>
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
        std::vector<componente::Componente> comps;
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

        int getPropValue(std::string type) const;
        std::string getPropValueStr(std::string type) const;
        // devolve a temperatura

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

        bool addSensor(int number_id, std::string& type);
        // adiciona um Sensor a Zona
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        std::string getComponents();
        // devolve os componentes da Zona

        std::string getComponentsStr();
        // devolve os componentes da Zona com toda a sua informacao

    };

} // zona

#endif //HOMESIM_ZONA_H
