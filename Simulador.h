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

        // habitacao
        habitacao::Habitacao h;

        // funcional
        bool isOn;
        std::string error;

    public:
        Simulador(term::Terminal& t, int width, int height);

        void start();
        // iniciar a simulacao

        bool verifyCMD(std::string prompt);
        // verifica o comando

        void printZones() const;
        // imprime as zonas

    };

} // simulador

#endif //HOMESIM_SIMULADOR_H
