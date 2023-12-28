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

    virtual bool Execute(habitacao::Habitacao *&h, std::string args) = 0;
    // funcao para executar o comando

// -- FUNCS GLOBAIS
    void defineError(std::string error_message);
    // funcao para definir o erro

    std::string getError() const;
    // funcao para recuperar o erro

};



class Hnova : public Comando {
public:
    Hnova();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};


class Hrem : public Comando {
public:
    Hrem();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};


class Prox : public Comando {
public:
    Prox();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};


class Znova : public Comando {
public:
    Znova();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};


class Zrem : public Comando {
public:
    Zrem();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};


class Pmod : public Comando {
public:
    Pmod();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};


class Cnovo : public Comando {
public:
    Cnovo();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Crem : public Comando {
public:
    Crem();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Rnova : public Comando {
public:
    Rnova();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Pmuda : public Comando {
public:
    Pmuda();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Rlista : public Comando {
public:
    Rlista();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Rrem : public Comando {
public:
    Rrem();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Asoc : public Comando {
public:
    Asoc();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Ades : public Comando {
public:
    Ades();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};

class Acom : public Comando {
public:
    Acom();

    bool Execute(habitacao::Habitacao *&h, std::string args) override;
};


#endif //HOMESIM_COMANDO_H
