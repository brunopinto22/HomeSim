#include <sstream>
#include "Simulador.h"

namespace simulador {
    Simulador::Simulador(term::Terminal &t, int width, int height):t(&t), isOn(false), h(width, height) { }

    void Simulador::start() {
        term::Window reader = term::Window(1,1,60,7);
        term::Window output = term::Window(1, 8, 60, 21);

        std::string text;
        std::ostringstream oss;

        bool end = false;
        do{
            // refresh da janela
            reader.clear();
            reader << ">> ";

            // imprimir zonas
            //printZones();

            // ler comando
            reader >> text;

            if(!verifyCMD(text))
                output << error;


            if(text == "sair")
                end = true;
            if(text == "znova"){
                output.clear();
                Znova newzona(1,1);
                if(!newzona.Execute(h))
                    output << newzona.getError();
                else
                    output << "Criei uma Zona em (1,1)";

            }


        } while(!end);

    }

    bool Simulador::verifyCMD(std::string prompt) {

        std::string comando, argumentos;
        size_t spacePos = prompt.find(' ');

        if (spacePos != std::string::npos) { // com argumentos
            comando = prompt.substr(0, spacePos);
            argumentos = prompt.substr(spacePos + 1);

        } else { // sem argumentos
            comando = prompt;
            argumentos = "";
        }

        if(comando.empty()){
            error = "comando vazio";
            return false;

        } else if(comando == "prox"){
            if(argumentos.empty())
                return true;
            error = "Erro de formatacao : prox";
            return false;

        } else if(comando == "avanca"){
            if(!argumentos.empty() && argumentos.length() == 1)
                return true;
            error = "Erro de formatacao : avanca <n>";
            return false;

        } else if(comando == "hnova"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : hnova <num linhas> <num colunas>";
            return false;

        } else if(comando == "hrem"){
            if(argumentos.empty())
                return true;
            error = "Erro de formatacao : hrem";
            return false;

        } else if(comando == "znova"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : znova <linha> <coluna>";
            return false;

        } else if(comando == "zrem"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : zrem <ID zona>";
            return false;

        } else if(comando == "zlista"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : zlista";
            return false;

        } else if(comando == "zcomp"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : zcomp <ID zona>";
            return false;

        } else if(comando == "pmod"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : pmod <ID zona> <nome> <valor>";
            return false;

        } else if(comando == "cnovo"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : cnovo <ID zona> <s | p | a> <tipo | comando>";
            return false;

        } else if(comando == "crem"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : crem <ID zona> <s | p | a> <ID>";
            return false;

        } else if(comando == "rnova"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]";
            return false;

        } else if(comando == "pmuda"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : pmuda <ID zona> <ID proc. regras> <novo comando>";
            return false;

        } else if(comando == "rlista"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : rlista <ID zona> <ID proc. regras>";
            return false;

        } else if(comando == "rrem"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : rrem <ID zona> <ID proc. regras> <ID regra>";
            return false;

        } else if(comando == "asoc"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : asoc <ID zona> <ID proc. regras> <ID aparelho>";
            return false;

        } else if(comando == "ades"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : ades <ID zona> <ID proc. regras> <ID aparelho>";
            return false;

        } else if(comando == "acom"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : acom <ID zona> <ID aparelho> <comando>";
            return false;

        } else if(comando == "psalva"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : psalva <ID zona> <ID proc. regras> <nome>";
            return false;

        } else if(comando == "prepoe"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : prepoe <nome>";
            return false;

        } else if(comando == "prem"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : prem <nome>";
            return false;

        } else if(comando == "plista"){
            if(argumentos.empty())
                return true;
            error = "plista";
            return false;

        } else if(comando == "exec"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : exec <nome de ficheiro>";
            return false;

        } else if(comando == "sair"){
            if(argumentos.empty())
                return true;
            error = "Erro de formatacao : sair";
            return false;

        }

        error = "Erro de formatacao : comando nao existe";
        return false;
    }

    void Simulador::printZones() const {

        for(int x=0; x<h.getHeight(); x++){
            for(int y=0; y<h.getWidth(); y++){
                term::Window zona = term::Window(1, 8, 60, 21);
            }
        }

    }


} // simulador