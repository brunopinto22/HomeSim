#ifndef HOMESIM_COMANDO_H
#define HOMESIM_COMANDO_H

#include <string>
#include "Habitacao.h"

class Comando {
private:
    std::string error;

public:
// -- FUNCS VIRTUAIS
    virtual ~Comando(){}

    virtual bool Execute(habitacao::Habitacao& h) = 0;
    // funcao para executar o comando

// -- FUNCS GLOBAIS
    void defineError(std::string& error_message);
    // funcao para definir o erro

    std::string getError() const;
    // funcao para recuperar o erro

};




class Znova : public Comando {
private:
    int x, y;

public:
    Znova(int x, int y);

    bool Execute(habitacao::Habitacao& h) override;
};


#endif //HOMESIM_COMANDO_H
