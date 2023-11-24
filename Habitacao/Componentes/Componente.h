#ifndef HOMESIM_COMPONENTE_H
#define HOMESIM_COMPONENTE_H

#include <string>

namespace componente {

    class Componente {
    private:
        std::string id;
        char name;

    public:
    // -- FUNCS VIRTUAIS
        virtual ~Componente(){}

    // -- FUNCS GLOBAIIS
        std::string getID() const;
        // devolve o ID do componente

        char getName() const;
        // devolve o caracter que o descreve

    };

} // componente

#endif //HOMESIM_COMPONENTE_H
