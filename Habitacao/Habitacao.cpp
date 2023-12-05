#include <stdexcept>
#include <algorithm>
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

    bool Habitacao::isZoneTacken(int x, int y){
        for(auto & z : zonas)
            if(z->getPosY() == y && z->getPosX() == x)
                return true;
        return false;
    }

    zona::Zona* Habitacao::getZone(int i) const {

        try{
            zona::Zona* z = this->zonas.at(i);
            return z;

        } catch(const std::out_of_range& e) {
            return nullptr;
        }
    }

    bool Habitacao::checkID(int id) const{

        auto it = std::find_if(zonas.begin(), zonas.end(), [id](const zona::Zona* zona) {return zona->getID() == id;});
        if(it != zonas.end())
            return true;
        return false;

    }

    void Habitacao::addZone(int x, int y) {
        this->zonas.push_back(new zona::Zona(getNumberID(), x, y));
        number_of_zones++;
    }


    void Habitacao::removeZone(int id) {
        zonas.erase(std::remove_if(zonas.begin(),zonas.end(), [id](const zona::Zona* zona) { return zona->getID() == id; }), zonas.end());
        number_of_zones--;
    }



} // habitacao