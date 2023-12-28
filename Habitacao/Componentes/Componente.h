#ifndef HOMESIM_COMPONENTE_H
#define HOMESIM_COMPONENTE_H

#include <string>
#include <vector>
#include "../Propriedade.h"

namespace componente {

    enum class ComponenteType : char {
        APARELHO = 'a',
        SENSOR = 's',
        PROCESSADOR = 'p'
    };

    class Componente {
    private:
        std::string id;
        std::string name;
        char type;

    public:
        Componente(int id, char type, std::string name);

    // -- FUNCS VIRTUAIS
        virtual ~Componente(){}

        virtual char getType() const;
        // devolve o caracter que o descreve

        virtual std::string getInfo() const;
        // devolve a informacao do componente

        virtual void run(std::vector<propriedades::Propriedade *> &props);
        // corre o componente

    // -- FUNCS GLOBAIS
        std::string getID() const;
        // devolve o ID do componente

        std::string getName() const;
        // devolve o nome do componente

    };

} // componente

#endif //HOMESIM_COMPONENTE_H
