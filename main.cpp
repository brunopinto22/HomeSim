#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>

#include "Terminal.h"
#include "Simulador.h"


int main() {
    // criar o terminal
    term::Terminal &t = term::Terminal::instance();
    // iniciar cores
    for(int i=1; i<20; i++) { t.init_color(i, i, 0); }

    // vars
    std::string text;
    int width, height;

    // menu principal
    bool end = false;
    while(!end){
        srand( (unsigned)time( NULL ) );

        term::Window reader = term::Window(1,1,60,7, false);
        reader << " Bem Vindo \n CMD >> ";

        // ler comando
        reader >> text;

        if(text == "hnova"){
            // criar simulador
            simulador::Simulador sim(t, 2, 2);

            // comecar a simulacao
            sim.start();

        } else if(text == "sair")
            end = true;
    }

    return 0;
}
