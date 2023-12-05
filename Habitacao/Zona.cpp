#include <sstream>
#include "Zona.h"

namespace zona {
    Zona::Zona(int number_id, int x, int y):id(number_id), pos_x(x), pos_y(y) {}

    int Zona::getID() const { return id; }

    int Zona::getPosX() const { return pos_x; }

    int Zona::getPosY() const { return pos_y; }

    std::string Zona::getProps() const {
        std::ostringstream oss;


        return oss.str();
    }

} // zona