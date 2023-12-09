#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "Habitacao.h"

namespace habitacao {
    Habitacao::Habitacao(int width, int height):width(width), height(height),number_id(0), ticks(0), number_of_zones(0) {}

    int Habitacao::getNumberID() {
        number_id++;
        return number_id;
    }

    int Habitacao::getWidth() const { return width; }

    int Habitacao::getHeight() const { return height; }

    int Habitacao::getTicks() const { return ticks; }

    std::string Habitacao::getError() const { return error; }

    int Habitacao::getNumberOfZones() const { return number_of_zones; }

    bool Habitacao::isZoneTacken(int x, int y){
        for(auto & z : zonas)
            if(z->getPosY() == y && z->getPosX() == x)
                return true;
        return false;
    }

    zona::Zona Habitacao::getZone(int index) const {
        if (index >= 0 && index < zonas.size())
            return *zonas.at(index);
        else
            return {};

    }

    zona::Zona Habitacao::getZone(int x, int y) const {
        auto it = std::find_if(zonas.begin(), zonas.end(), [x, y](const zona::Zona* zona) { return zona->getPosX() == x && zona->getPosY() == y; });

        if (it != zonas.end()) {
            return *(*it);
        } else
            return {};
    }

    zona::Zona Habitacao::getZoneByID(int id) const {
        auto it = std::find_if(zonas.begin(), zonas.end(), [id](const zona::Zona* zona) { return zona->getID() == id; });

        if (it != zonas.end())
            return *(*it);
        else
            return {};
    }

    bool Habitacao::checkZoneID(int id) const{

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

    bool Habitacao::changeZoneProp(int id, std::string prop_name, int new_value) {
        std::ostringstream oss;

        if(!checkZoneID(id)){
            oss << "A Zona com o id=" << id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [id](const zona::Zona* z) { return z->getID() == id; });
        zona::Zona* target = *it;

        if (!target->setProp(prop_name, new_value)) {
            error = target->getError();
            return false;
        }

        error = target->getError();
        return true;
    }


    bool Habitacao::tick() {
        ticks++;
        return true;
    }




} // habitacao