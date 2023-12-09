#ifndef HOMESIM_SIMULADOR_H
#define HOMESIM_SIMULADOR_H

#include <vector>

#include "Terminal.h"
#include "Habitacao//Comando.h"
#include "Habitacao/Habitacao.h"
#include "Habitacao/Zona.h"


namespace simulador {

    class Simulador {
    private:
        // terminal
        term::Terminal* t;

        // janelas
        std::vector<term::Window*> zonas;

        // habitacao
        habitacao::Habitacao* h;

        // funcional
        bool isOn;

    public:
        Simulador(term::Terminal& t);

        void run();
        // executar a simulacao

        static void splitCMD(std::string prompt, std::string* cmd, std::string* args);
        // divide o comando em comando e argumentos

        void executeCommand(std::string& prompt, term::Window& output, bool isFromExec);
        // executa os comandos

        void printZones();
        // imprime as zonas

        static void printZoneProps(const zona::Zona& type, term::Window& output);
        // imprime as propriedades de uma zona

        static void printHelp(term::Window& output);
        // imprime uma lista de comandos

    };


} // simulador



#endif //HOMESIM_SIMULADOR_H
