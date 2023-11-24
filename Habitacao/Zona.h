#ifndef HOMESIM_ZONA_H
#define HOMESIM_ZONA_H

#include <string>

namespace zona {

    class Zona {
    private:
        int id;
        int pos_x, pos_y; // coordenadas

    public:
        Zona(int number_id, int x, int y);

        int getID() const;
        // devolve o ID
        int getPosX() const;
        // devolve a posicao em x
        int getPosY() const;
        // devolve a posicao em y



    };

} // zona

#endif //HOMESIM_ZONA_H
