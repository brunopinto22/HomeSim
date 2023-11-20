#include <sstream>
#include "Prompt.h"

using namespace cmd;

// Construtor
Prompt::Prompt(): valido(false) { }

const bool Prompt::verificarComando() {

    if(comando.empty()){
        definirErro("comando vazio");
        return false;

    } else if(comando == "prox"){
        if(argumentos.empty())
            return true;
        definirErro("Erro de formatacao : prox");
        return false;

    } else if(comando == "avanca"){
        if(!argumentos.empty() && argumentos.length() == 1)
            return true;
        definirErro("Erro de formatacao : avanca <n>");
        return false;

    } else if(comando == "hnova"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : hnova <num linhas> <num colunas>");
        return false;

    } else if(comando == "hrem"){
        if(argumentos.empty())
            return true;
        definirErro("Erro de formatacao : hrem");
        return false;

    } else if(comando == "znova"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : znova <linha> <coluna>");
        return false;

    } else if(comando == "zrem"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : zrem <ID zona>");
        return false;

    } else if(comando == "zlista"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : zlista");
        return false;

    } else if(comando == "zcomp"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : zcomp <ID zona>");
        return false;

    } else if(comando == "pmod"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : pmod <ID zona> <nome> <valor>");
        return false;

    } else if(comando == "cnovo"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : cnovo <ID zona> <s | p | a> <tipo | comando>");
        return false;

    } else if(comando == "crem"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : crem <ID zona> <s | p | a> <ID>");
        return false;

    } else if(comando == "rnova"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]");
        return false;

    } else if(comando == "pmuda"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : pmuda <ID zona> <ID proc. regras> <novo comando>");
        return false;

    } else if(comando == "rlista"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : rlista <ID zona> <ID proc. regras>");
        return false;

    } else if(comando == "rrem"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : rrem <ID zona> <ID proc. regras> <ID regra>");
        return false;

    } else if(comando == "asoc"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : asoc <ID zona> <ID proc. regras> <ID aparelho>");
        return false;

    } else if(comando == "ades"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : ades <ID zona> <ID proc. regras> <ID aparelho>");
        return false;

    } else if(comando == "acom"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : acom <ID zona> <ID aparelho> <comando>");
        return false;

    } else if(comando == "psalva"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : psalva <ID zona> <ID proc. regras> <nome>");
        return false;

    } else if(comando == "prepoe"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : prepoe <nome>");
        return false;

    } else if(comando == "prem"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : prem <nome>");
        return false;

    } else if(comando == "plista"){
        if(argumentos.empty())
            return true;
        definirErro("plista");
        return false;

    } else if(comando == "exec"){
        if(!argumentos.empty())
            return true;
        definirErro("Erro de formatacao : exec <nome de ficheiro>");
        return false;

    } else if(comando == "sair"){
        if(argumentos.empty())
            return true;
        definirErro("Erro de formatacao : sair");
        return false;

    }

    definirErro("Erro de formatacao : comando nao existe");
    return false;

}

Prompt& Prompt::operator=(string& text){

    size_t spacePos = text.find(' ');

    if (spacePos != string::npos) { // com argumentos
        definirComando(text.substr(0, spacePos));
        definirArgumentos(text.substr(spacePos + 1));

    } else { // sem argumentos
        definirComando(text);
        definirArgumentos("");
    }

    definirValido(verificarComando());

    return *this;
}

void Prompt::definirErro(const std::string &error) { this->erro = error; }

void Prompt::definirComando(const std::string &cmd) { this->comando = cmd; }

void Prompt::definirArgumentos(const std::string &args) { this->argumentos = args; }

void Prompt::definirValido(const bool &valido) { this->valido = valido; }



bool Prompt::eValido() const { return valido; }

bool Prompt::continuar() const {
    if(eValido())
        if(comando == "sair")
            return false;
    return true;
}

string Prompt::pedirComando() const { return this->comando; }

string Prompt::pedirArgumentos() const { return this->argumentos; }

string Prompt::pedirErro() const { return this->erro; }

ostream &cmd::operator<<(ostream& oss, const Prompt& prompt) {
    oss << prompt.pedirComando() << " " << prompt.pedirArgumentos();

    return oss;
}
