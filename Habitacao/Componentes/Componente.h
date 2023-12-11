#ifndef HOMESIM_COMPONENTE_H
#define HOMESIM_COMPONENTE_H

#include <string>

namespace componente {

    enum class ComponenteType : char {
        APARELHO = 'a',
        SENSOR = 's',
        PROCESSADOR = 'p'
    };

    class Componente {
    private:
        std::string id;
        char type;

    public:
        Componente(int id, char type);

    // -- FUNCS VIRTUAIS
        virtual ~Componente(){}

        virtual char getType() const;
        // devolve o caracter que o descreve

    // -- FUNCS GLOBAIS
        std::string getID() const;
        // devolve o ID do componente

    };

} // componente

#endif //HOMESIM_COMPONENTE_H
