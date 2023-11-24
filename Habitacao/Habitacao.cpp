#include "Habitacao.h"

namespace habitacao {
    Habitacao::Habitacao(int width, int height):width(width), height(height),number_id(0), number_of_zones(0) {}

    int Habitacao::getNumberID() {
        number_id++;
        return number_id;
    }

    int Habitacao::getWidth() const { return width; }

    int Habitacao::getHeight() const { return height; }

    int Habitacao::getNumberOfZones() const { return number_of_zones; }

    void Habitacao::addZone(int x, int y) {
        this->zonas.push_back(new zona::Zona(getNumberID(), x, y));
        number_of_zones++;
    }

} // habitacao