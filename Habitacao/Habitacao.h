#ifndef HOMESIM_HABITACAO_H
#define HOMESIM_HABITACAO_H

#include <vector>
#include "Zona.h"

namespace habitacao {

    class Habitacao {
    private:
        int number_id;
        int width, height; // tamanho da habitacao
        int ticks;

        int number_of_zones; // contador de zonas
        std::vector<zona::Zona*> zonas;

        std::string error;

    public:
        Habitacao();
        Habitacao(int width, int height);

        int getNumberID();
        // devolve o número do ID para a Zona/Sensor/Aparelho/Regra

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

        zona::Zona* getZone(int i) const;
        // devolve uma zona

        bool checkID(int id) const;
        // verifica se o ID existe

        void addZone(int x, int y);
        // adiciona uma zona

        void removeZone(int id);
        // remove uma zona

        bool tick();
        // avanca 1 tick na habitacao
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

    };

} // habitacao

#endif //HOMESIM_HABITACAO_H
