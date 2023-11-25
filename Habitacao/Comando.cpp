#include <sstream>
#include "Comando.h"

void Comando::defineError(std::string error_message) { this->error = error_message; }

std::string Comando::getError() const {
    return error;
}


Znova::Znova(int x, int y) : x(x), y(y) {}

bool Znova::Execute(habitacao::Habitacao &h) {
    std::ostringstream oss;

    if(h.getNumberOfZones() >= h.getHeight()*h.getWidth()){
        defineError("A Habitacao esta cheia");
        return false;
    }

    if(h.isZoneTacken(this->x,this->y)){
        oss << "A posicao (" << this->x << "," << this->y <<") esta preenchida";
        defineError(oss.str());
        return false;
    }

    if(x < 1 || x > h.getHeight() || y < 1 || y > h.getWidth()){
        oss << "o valor de x e de y tem de estar compreendidos entre (1," << h.getHeight() << ") e (1," << h.getWidth()<<")";
        defineError(oss.str());
        return false;
    }

    // verificar se existe algo nessas coordenadas
    // .... \\

    h.addZone(this->x, this->y);
    return true;
}

