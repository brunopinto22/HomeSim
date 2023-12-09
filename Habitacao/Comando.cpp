#include <sstream>
#include "Comando.h"

void Comando::defineError(std::string error_message) { this->error = error_message; }

std::string Comando::getError() const {
    return error;
}



Step::Step() {}
bool Step::Execute(habitacao::Habitacao &h, std::string args){
    if(!args.empty()){
        defineError("Erro de formatacao : prox");
        return false;
    }

    if(!h.tick()){
        defineError(h.getError());
        return false;
    }
    return true;

}


Znova::Znova() {}
bool Znova::Execute(habitacao::Habitacao &h, std::string args) {
    std::ostringstream oss;
    std::istringstream iss(args);
    int x,y;

    if(iss >> x >> y){

        if(h.getNumberOfZones() >= h.getHeight()*h.getWidth()){
            defineError("A Habitacao esta cheia");
            return false;

        } else if(x < 1 || x > h.getHeight() || y < 1 || y > h.getWidth()){
            oss << "O valor de x e de y tem de estar compreendidos entre (1," << h.getHeight() << ") e (1," << h.getWidth()<<")";
            defineError(oss.str());
            return false;

        } else if(h.isZoneTacken(x,y)){
            oss << "A posicao (" << x << "," << y <<") esta preenchida";
            defineError(oss.str());
            return false;
        }


        h.addZone(x, y);
        oss << "Foi criada a zona em (" << x << "," << y << ")";
        defineError(oss.str());
        return true;

    }
    defineError("Erro de formatacao : znova <x> <y>");
    return false;

}


Zrem::Zrem() {}
bool Zrem::Execute(habitacao::Habitacao &h, std::string args) {
    std::ostringstream oss;
    std::istringstream iss(args);
    int id;
    if (iss >> id) {

        if(!h.checkZoneID(id)){
            oss << "A Zona com o id=" << id << " nao existe";
            defineError(oss.str());
            return false;
        }

        h.removeZone(id);
        oss << "A Zona_" << id << " foi removida";
        defineError(oss.str());
        return true;

    }
    defineError("Erro de formatacao : zrem <ID zona>");
    return false;

}

Pmod::Pmod() {}
bool Pmod::Execute(habitacao::Habitacao &h, std::string args) {

    std::ostringstream oss;
    std::istringstream iss(args);

    int id, value;
    std::string name;
    if (iss >> id >> name >> value) {

        if(!h.changeZoneProp(id, name, value)){
            defineError(h.getError());
            return false;
        }

        oss << "A Propriedade " << name << " da Zona_" << id << " foi atualizada para " << h.getError();
        defineError(oss.str());
        return true;

    }

    defineError("Erro de formatacao : pmod <ID zona> <nome> <valor>");
    return false;
}
