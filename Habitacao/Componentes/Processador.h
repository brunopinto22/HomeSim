#ifndef HOMESIM_PROCESSADOR_H
#define HOMESIM_PROCESSADOR_H

#include <string>
#include "Componente.h"

namespace processador {

    enum class ProcessorType{
        IGUAL,
        MAIOR,
        MENOR,
        ENTRE,
        FORA
    };

    class Processador : public componente::Componente{
    private:

    public:
        Processador();

        char getType() const override;
    };

} // processador

#endif //HOMESIM_PROCESSADOR_H
