#ifndef HOMESIM_SIMULADOR_H
#define HOMESIM_SIMULADOR_H

#include <vector>

#include "Terminal.h"
#include "Habitacao//Comando.h"
#include "Habitacao/Habitacao.h"
#include "Habitacao/Zona.h"


namespace utils{

    std::string getError();

    void splitCMD(std::string prompt, std::string* cmd, std::string* args);
    // divide o comando em comando e argumentos

    bool verifyCMD(std::string& comando, std::string& argumentos);
    // verifica o comando

}


namespace simulador {

    class Simulador {
    private:
        // terminal
        term::Terminal* t;

        // janelas
        std::vector<term::Window*> zonas;

        // habitacao
        habitacao::Habitacao h;

        // funcional
        bool isOn;
        std::string error;

    public:
        Simulador(term::Terminal& t, int width, int height);

        void start();
        // iniciar a simulacao

        void executeCommand(std::string& cmd, std::string& args, term::Window& output, bool isFromExec);
        // executa os comandos

        bool step(term::Window& output);
        // avanca um instante da simulacao

        void printZones();
        // imprime as zonas

    };


} // simulador



#endif //HOMESIM_SIMULADOR_H
