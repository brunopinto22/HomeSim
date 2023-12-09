#ifndef HOMESIM_ZONA_H
#define HOMESIM_ZONA_H

#include <string>
#include <vector>
#include "Propriedade.h"

namespace zona {


    class Zona {
    private:
        int id;
        int pos_x, pos_y; // coordenadas

        std::string error;

        // propriedades
        std::vector<propriedades::Propriedade*> props;

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

    };

} // zona

#endif //HOMESIM_ZONA_H
