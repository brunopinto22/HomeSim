#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include "Terminal.h"
#include "Prompt.h"

using namespace std;
using namespace term;

int main() {
    // criar o terminal
    Terminal &t = Terminal::instance();

    // vars
    cmd::Prompt prompt;
    ostringstream oss;
    string text;

    int i = 0;

    do{
        // limpar memoria
        srand( (unsigned)time( NULL ) );
        oss.str("");
        oss.clear();

        // criar janelas
        Window field = Window(1, 1, 57, 21);
        Window reader = Window(1,22,57,7);
        Window info = Window(59,1,60,28);
        reader << " CMD \n >> ";

        // imprimir output
        oss << prompt << endl;
        if(!prompt.eValido()){

            info << prompt.pedirErro();
        }
        else
            info << oss.str();

        // ler comando
        reader >> text;
        prompt = text;

    }while(prompt.continuar());

    std::cout << "\nAdeus ;)\n";
    return 0;
}
