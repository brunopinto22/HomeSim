#ifndef HOMESIM_COMANDO_H
#define HOMESIM_COMANDO_H

#include <string>
#include "Habitacao.h"

class Comando {
private:
    std::string error;
    std:: string args;

public:
// -- FUNCS VIRTUAIS
    virtual ~Comando(){}

    virtual bool Execute(habitacao::Habitacao &h, std::string args) = 0;
    // funcao para executar o comando

// -- FUNCS GLOBAIS
    void defineError(std::string error_message);
    // funcao para definir o erro

    std::string getError() const;
    // funcao para recuperar o erro

};



class Znova : public Comando {
public:
    Znova();

    bool Execute(habitacao::Habitacao &h, std::string args) override;
};


class Zrem : public Comando {
public:
    Zrem();

    bool Execute(habitacao::Habitacao &h, std::string args) override;
};


class Zlista : public Comando {
public:
    Zlista();

    bool Execute(habitacao::Habitacao &h, std::string args) override;
};


class Zcomp : public Comando {
public:
    Zcomp();

    bool Execute(habitacao::Habitacao &h, std::string args) override;
};


class Zprops : public Comando {
public:
    Zprops();

    bool Execute(habitacao::Habitacao &h, std::string args) override;
};


class Pmod : public Comando {
public:
    Pmod();

    bool Execute(habitacao::Habitacao &h, std::string args) override;
};


class Cnovo : public Comando {
public:
    Cnovo();

    bool Execute(habitacao::Habitacao &h, std::string args) override;
};


#endif //HOMESIM_COMANDO_H
