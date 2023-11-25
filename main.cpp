#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

#include "Terminal.h"
#include "Simulador.h"


int main() {
    // criar o terminal
    term::Terminal &t = term::Terminal::instance();
    // iniciar cores
    for(int i=1; i<20; i++) { t.init_color(i, i, 0); }

    // vars
    std::string text, cmd, args;
    int width, height;

    // menu principal
    term::Window reader = term::Window(1,1,100,14, false);
    term::Window out = term::Window(2,15,100,3, false);

    t.clear();
    bool end = false;
    while(!end){
        args.clear();

        reader.clear();

        reader << "Bem Vindo\n\n" << term::set_color(COLOR_MESSAGE)
        << "ooooo   ooooo   .oooooo.   ooo        ooooo oooooooooooo     .oooooo..o ooooo ooo        ooooo" << "\n"
        << "`888'   `888'  d8P'  `Y8b  `88.       .888' `888'     `8    d8P'    `Y8 `888' `88.       .888'" << "\n"
        << " 888     888  888      888  888b     d'888   888            Y88bo.       888   888b     d'888" << "\n"
        << " 888ooooo888  888      888  8 Y88. .P  888   888oooo8        `\"Y8888o.   888   8 Y88. .P  888 " << "\n"
        << " 888     888  888      888  8  `888'   888   888    \"            `\"Y88b  888   8  `888'   888" << "\n"
        << " 888     888  `88b    d88'  8    Y     888   888       o    oo     .d8P  888   8    Y     888 " << "\n"
        << "o888o   o888o  `Y8bood8P'  o8o        o888o o888ooooood8    8\"\"88888P'  o888o o8o        o888o" << "\n"
        << term::set_color(0) << "\n\n\n Command >> ";

        // ler comando
        reader >> text;

        // dividir comando
        utils::splitCMD(text, &cmd, &args);

        if(!utils::verifyCMD(cmd, args)){
            out.clear();
            out << term::set_color(COLOR_ERROR) << utils::getError();

        } else if(cmd == "hnova"){

            std::istringstream iss(args);
            if (iss >> width >> height) {

                // criar simulador
                simulador::Simulador sim(t, width, height);
                // comecar a simulacao
                sim.start();
            }

        } else if(cmd == "sair"){
            if(args.empty())
                end = true;
            else{
                out.clear();
                out << term::set_color(COLOR_ERROR) << "Erro de formatacao: sair";
            }
        }
        else{
            out.clear();
            out << term::set_color(COLOR_ERROR) << "Tem primeiro de criar uma habitacao: hnova <numLinhas> <numColunas>";
        }

    }

    return 0;
}
