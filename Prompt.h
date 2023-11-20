#ifndef HOMESIM_PROMPT_H
#define HOMESIM_PROMPT_H

#include <string>
using namespace std;


namespace cmd { class Prompt {

private:
    bool valido;
    string comando;
    string argumentos;
    string erro;

public:
    Prompt();

    const bool verificarComando();

    // sets
    Prompt& operator=(string& text);
    void definirComando(const string &cmd);
    void definirArgumentos(const string &args);
    void definirValido(const bool &valido);
    void definirErro(const string &error);

    // gets
    bool eValido() const;
    bool continuar() const;
    string pedirComando() const;
    string pedirArgumentos() const;
    string pedirErro() const;
    friend ostream& operator<<(ostream& os, const Prompt& prompt);

};}


#endif //HOMESIM_PROMPT_H
