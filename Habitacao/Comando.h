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
    void defineError(std::string error_message);
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


class Zrem : public Comando {
private:
    int id;
public:
    Zrem(int id);

    bool Execute(habitacao::Habitacao& h) override;
};


class Zlista : public Comando {
public:
    Zlista();

    bool Execute(habitacao::Habitacao& h) override;
};


class Zcomp : public Comando {
private:
    int id;
public:
    Zcomp(int id);

    bool Execute(habitacao::Habitacao& h) override;
};


class Zprops : public Comando {
private:
    int id;
public:
    Zprops(int id);

    bool Execute(habitacao::Habitacao& h) override;
};


class Pmod : public Comando {
private:
    int id, value;
    std::string name;
public:
    Pmod(int id, std::string name, int value);

    bool Execute(habitacao::Habitacao& h) override;
};


class Cnovo : public Comando {
private:
    int idZona;
    char type;
    std::string typeOrCmd;
public:
    Cnovo(int idZona, char type, std::string typeOrCmd);

    bool Execute(habitacao::Habitacao& h) override;
};


#endif //HOMESIM_COMANDO_H
