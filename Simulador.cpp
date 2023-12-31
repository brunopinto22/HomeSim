#include <sstream>
#include <fstream>
#include "Simulador.h"


namespace simulador {

    Simulador::Simulador(term::Terminal &t):t(&t), isOn(false), h(nullptr) {
        // iniciar cores
        for(int i=1; i<20; i++) { t.init_color(i, i, 0); }

        title =   "      _____  _____  _____  _____    _____  _____  _____\n     |  |  ||     ||     ||   __|  |   __||     ||     |\n     |     ||  |  || | | ||   __|  |__   ||-   -|| | | |\n     |__|__||_____||_|_|_||_____|  |_____||_____||_|_|_|";

    }


    void Simulador::run() {
        std::string prompt;

        // criacao das janelas
        term::Window titleW = term::Window(1,1,70,5, false);
        term::Window reader = term::Window(1,6,70,7, true);
        term::Window output = term::Window(1, 13, 70, 37, true);
        term::Window info = term::Window(72,1,120,5, true);

        titleW << term::set_color(COLOR_MESSAGE) << title;

        isOn = true;
        do{
            // limpar vars e janelas
            prompt.clear();
            reader.clear();
            reader << " >> ";

            // imprimir zonas
            printZones();

            // imprimir informacao sobre a simulacao
            printInfo(info);

            // ler comando
            reader >> prompt;

            // executa o comando
            executeCommand(prompt, output, false);

        } while(isOn);

    }


    void Simulador::splitCMD(std::string prompt, std::string* cmd, std::string* args){
        size_t spacePos = prompt.find(' ');
        if (spacePos != std::string::npos) { // com argumentos
            *cmd = prompt.substr(0, spacePos);
            *args = prompt.substr(spacePos + 1);
        } else { // sem argumentos
            *cmd = prompt;
            *args = "";
        }
    }


    void Simulador::executeCommand(std::string& prompt, term::Window& output, bool isFromExec) {

        // dividir comando
        std::string cmd, args;
        splitCMD(prompt, &cmd, &args);

        // guardar os argumentos
        std::istringstream iss(args);

        Comando* exe = nullptr;

        // parte visual
        if(!isFromExec)
            output.clear();
        output << term::set_color(COLOR_DEFAULT);


        if(cmd.empty()){
            output << term::set_color(COLOR_ERROR) << " Erro: Comando vazio";

        } else if(cmd == "prox"){

            exe = new Prox;
            if (exe->Execute(h, args))
                output << term::set_color(COLOR_DEFAULT) << exe->getError();
            else
                output << term::set_color(COLOR_ERROR) << exe->getError();

            return;

        } else if(cmd == "avanca"){

            int n;
            if (iss >> n) {
                exe = new Prox;
                for (int i = 0; i < n; i++) {
                    if (exe->Execute(h, ""))
                        output << term::set_color(COLOR_DEFAULT) << exe->getError();
                    else
                        output << term::set_color(COLOR_ERROR) << exe->getError();
                }
            } else
                output << term::set_color(COLOR_ERROR) << " Erro: avanca <n>";

            return;

        } else if(cmd == "hnova"){

            exe = new Hnova;

        } else if(cmd == "hrem"){

            exe = new Hrem;

        } else if(cmd == "znova"){

            exe = new Znova;

        } else if(cmd == "zrem"){

            exe = new Zrem;

        } else if(cmd == "zlista"){

            if(!args.empty()){
                output << term::set_color(COLOR_ERROR) << " Erro: zlista";
                return;
            }

            if(h->getNumberOfZones() == 0){
                output << term::set_color(COLOR_ERROR) << " Nao existem Zonas criadas";
                return;
            }

            for(int i=0; i < h->getNumberOfZones(); i++){
                zona::Zona z = h->getZone(i);
                output
                << term::set_color(COLOR_ID) << "Zona_" << z.getID() << term::set_color(COLOR_DEFAULT) << " (" << z.getPosX() << "," << z.getPosY() << ")\n"
                << term::set_color(COLOR_MESSAGE) << " sensores : " << term::set_color(COLOR_DEFAULT) << z.getNumberOfSensors()
                << term::set_color(COLOR_MESSAGE) << " | processadores : " << term::set_color(COLOR_DEFAULT) << z.getNumberOfProcessors()
                << term::set_color(COLOR_MESSAGE) << " | aparelhos : " << term::set_color(COLOR_DEFAULT) << z.getNumberOfGadgets() <<"\n";
            }

        } else if(cmd == "zcomp"){

            int id;
            if (iss >> id) {

                if(h->getNumberOfZones() == 0){
                    output << term::set_color(COLOR_ERROR) << " Nao existem Zonas criadas";
                    return;
                }

                zona::Zona z = h->getZoneByID(id);
                output
                << term::set_color(COLOR_MESSAGE) << "Zona_" << z.getID() << "\n"
                << term::set_color(COLOR_DEFAULT) << z.getComponentsStr();

            } else
                output << term::set_color(COLOR_ERROR) << " Erro: zcomp <ID zona>";


        }  else if(cmd == "zprops"){

            int id;
            if (iss >> id)
                printZoneProps(h->getZoneByID(id), output);
            else
                output << term::set_color(COLOR_ERROR) << " Erro: zprops <ID zona>";

        } else if(cmd == "pmod"){

            exe = new Pmod;

        } else if(cmd == "cnovo"){

            exe = new Cnovo;

        } else if(cmd == "crem"){

            exe = new Crem;

        } else if(cmd == "rnova"){

            exe = new Rnova;

        } else if(cmd == "pmuda"){

            exe = new Pmuda;

        } else if(cmd == "rlista"){

            exe = new Rlista;
            if(exe->Execute(h, args)) {
                std::string text = exe->getError();
                std::istringstream issOut(text);
                std::string line;

                // seperar o titulo do resto do conteudo
                std::getline(issOut, line);
                output << term::set_color(COLOR_MESSAGE) << line << "\n" << term::set_color(COLOR_DEFAULT);
                while (std::getline(issOut, line))
                    output << line << "\n";
            }
            else
                output << term::set_color(COLOR_ERROR) << " Erro: " << exe->getError();

            return;

        } else if(cmd == "rrem"){

            exe = new Rrem;

        } else if(cmd == "asoc"){

            exe = new Asoc;

        } else if(cmd == "ades"){

            exe = new Ades;

        } else if(cmd == "acom"){

            exe = new Acom;

        } else if(cmd == "psalva"){

            exe = new Psalva;

        } else if(cmd == "prepoe"){

            std::string name;
            if (iss >> name) {
                output << term::set_color(COLOR_SUCCESS) << "A repor a copia do processador \'" << name << "\'";

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : prepoe <nome>";

        } else if(cmd == "prem"){

            exe = new Prem;

        } else if(cmd == "plista"){

            exe = new Plista;
            if(exe->Execute(h, args)) {
                std::string text = exe->getError();
                std::istringstream issOut(text);
                std::string line;

                // seperar o titulo do resto do conteudo
                std::getline(issOut, line);
                output << term::set_color(COLOR_MESSAGE) << line << "\n" << term::set_color(COLOR_DEFAULT);
                while (std::getline(issOut, line))
                    output << line << "\n";
            }
            else
                output << term::set_color(COLOR_ERROR) << " Erro: " << exe->getError();

            return;

        } else if(cmd == "exec"){

            std::string filename, text;
            if(iss >> filename) {
                std::ifstream file(filename);

                // verificar se o ficheiro abriu
                if(!file.is_open()){
                    output << term::set_color(COLOR_ERROR) << "Nao foi possivel abrir o ficheiro \'" << filename << "\'";
                }

                while (std::getline(file, text)) {
                    // executa o comando
                    executeCommand(text, output, true);
                }

            } else
                output << term::set_color(COLOR_ERROR) << "Erro: exec <nome de ficheiro>";

        } else if(cmd == "sair"){
            if(!args.empty())
                output << term::set_color(COLOR_ERROR) << "Erro: sair";
            else
                isOn = false;

            return;

        } else if (cmd == "help") {
            printHelp(output);

        } else {
            output << term::set_color(COLOR_ERROR) << " Erro: comando nao existe";
            return;
        }

        if(exe == nullptr)
            return;

        if(exe->Execute(h, args))
            output << term::set_color(COLOR_SUCCESS) << " " << exe->getError() << "\n";
        else
            output << term::set_color(COLOR_ERROR) << " Erro: " << exe->getError() << "\n";

    }


    void Simulador::printInfo(term::Window &output) {
        output.clear();

        if(h == nullptr)
            output << term::set_color(COLOR_ERROR) << "\n\tAinda nao existe uma Habitacao";

        else
        output  << term::set_color(COLOR_ID) << "\n\tHabitacao:" << term::set_color(COLOR_DEFAULT) << h->getWidth() << "x" << h->getHeight()
                << term::set_color(COLOR_MESSAGE) << "  |  "
                << term::set_color(COLOR_ID) << "Ticks:" << term::set_color(COLOR_DEFAULT) << h->getTicks()
                << term::set_color(COLOR_MESSAGE) << "  |  "
                << term::set_color(COLOR_ID) << "Num. Zonas:" << term::set_color(COLOR_DEFAULT) << h->getNumberOfZones();
    }


    void Simulador::printZones() {
        // limpa o mapa
        for (auto& zone : zonas_windows)
            delete zone.second;
        zonas_windows.clear();

        // verifica se existe uma habitacao
        if (h == nullptr)
            return;

        // cria as janelas das zonas
        for (int x = 0; x < h->getHeight(); x++)
            for (int y = 0; y < h->getWidth(); y++)
                zonas_windows[std::make_pair(x, y)] = new term::Window(72 + 30 * x, 6 + 11 * y, 30, 11, true);

        // verifica se existem zonas
        if (h->getNumberOfZones() <= 0)
            return;

        // imprime a informacao de cada zona
        for (int x = 0; x < h->getHeight(); x++) {
            for (int y = 0; y < h->getWidth(); y++) {
                // vai buscar a zona correspondente
                zona::Zona current_zone = h->getZone(y + 1, x + 1);
                if (current_zone.getID() != -1)
                    *zonas_windows.at(std::make_pair(x, y)) << term::set_color(COLOR_ID) << "Zona_" << current_zone.getID()
                                                    << term::set_color(COLOR_DEFAULT) << "\n" << current_zone.getComponents();
            }
        }
    }

    void Simulador::printZoneProps(const zona::Zona& z, term::Window& output) {
        if(z.getID() == -1){
            output << term::set_color(COLOR_ERROR) << "Essa Zona nao existe";
            return;
        }

        output << term::set_color(COLOR_ID) << "Propriedades da Zona_" << z.getID() << "\n\n";

        auto printProp = [&](const std::string& type) {
            if (z.getPropValue(type) != propriedades::UNSET) {
                output << term::set_color(COLOR_MESSAGE) << type << ": " << term::set_color(COLOR_DEFAULT) << z.getPropValueStr(type) << "\n";
            }
        };

        printProp("temperatura");
        printProp("luz");
        printProp("radiacao");
        printProp("vibracao");
        printProp("humidade");
        printProp("fumo");
        printProp("som");

        output << term::set_color(COLOR_DEFAULT);

    }

    void Simulador::printHelp(term::Window &output) {

        output
        << term::set_color(COLOR_ID) << " prox\n" << term::set_color(COLOR_DEFAULT)
        << term::set_color(COLOR_ID) << " avanca " << term::set_color(COLOR_DEFAULT) << "<n>\n"
        << term::set_color(COLOR_ID) << " hnova " << term::set_color(COLOR_DEFAULT) << "<num linhas> <num colunas>\n"
        << term::set_color(COLOR_ID) << " hrem\n" << term::set_color(COLOR_DEFAULT)
        << term::set_color(COLOR_ID) << " znova " << term::set_color(COLOR_DEFAULT) << "<linha> <coluna>\n"
        << term::set_color(COLOR_ID) << " zrem " << term::set_color(COLOR_DEFAULT) << "<ID zona>\n"
        << term::set_color(COLOR_ID) << " zlista\n" << term::set_color(COLOR_DEFAULT)
        << term::set_color(COLOR_ID) << " zcomp " << term::set_color(COLOR_DEFAULT) << "<ID zona>\n"
        << term::set_color(COLOR_ID) << " zprops " << term::set_color(COLOR_DEFAULT) << "<ID zona>\n"
        << term::set_color(COLOR_ID) << " pmod " << term::set_color(COLOR_DEFAULT) << "<ID zona> <nome> <valor> \n"
        << term::set_color(COLOR_ID) << " cnovo " << term::set_color(COLOR_DEFAULT) << "<ID zona> <s | p | a> <tipo | comando>\n"
        << term::set_color(COLOR_ID) << " crem " << term::set_color(COLOR_DEFAULT) << "<ID zona> <s | p | a> <ID>\n"
        << term::set_color(COLOR_ID) << " pmuda " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc.> <novo comando>\n"
        << term::set_color(COLOR_ID) << " rnova " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc.> <regra> <ID sensor> [par1] [par2] [..]\n"
        << term::set_color(COLOR_ID) << " rrem " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc.> <ID regras>\n"
        << term::set_color(COLOR_ID) << " rlista " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc.>\n"
        << term::set_color(COLOR_ID) << " asoc " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc.> <ID aparelho>\n"
        << term::set_color(COLOR_ID) << " ades " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc.> <ID aparelho>\n"
        << term::set_color(COLOR_ID) << " acom " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID aparelho> <comando>\n"
        << term::set_color(COLOR_ID) << " psalva " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc.> <nome>\n"
        << term::set_color(COLOR_ID) << " prepoe " << term::set_color(COLOR_DEFAULT) << "<nome> \n"
        << term::set_color(COLOR_ID) << " prem " << term::set_color(COLOR_DEFAULT) << "<nome> \n"
        << term::set_color(COLOR_ID) << " plista\n" << term::set_color(COLOR_DEFAULT)
        << term::set_color(COLOR_ID) << " exec " << term::set_color(COLOR_DEFAULT) << "<nome de ficheiro>\n"
        << term::set_color(COLOR_ID) << " sair\n" << term::set_color(COLOR_DEFAULT);

    }

} // simulador
