#include "Terminal.h"
#include "Simulador.h"


int main() {
    // criar o terminal
    term::Terminal &t = term::Terminal::instance();

    // criar simulador
    simulador::Simulador sim(t);

    //_sleep(500);

    // comecar a simulacao
    sim.run();

    t.clear();
    return 0;
}
