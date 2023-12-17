#include <sstream>
#include <fstream>
#include "Simulador.h"


namespace simulador {

    Simulador::Simulador(term::Terminal &t):t(&t), isOn(false), h(nullptr) {
        // iniciar cores
        for(int i=1; i<20; i++) { t.init_color(i, i, 0); }
    }


    void Simulador::run() {
        std::string prompt;

        // criacao das janelas
        term::Window title = term::Window(1,1,70,5, false);
        term::Window reader = term::Window(1,6,70,7, true);
        term::Window output = term::Window(1, 13, 70, 33, true);
        term::Window info = term::Window(72,1,120,5, true);

        title << term::set_color(COLOR_MESSAGE)
              << "   _____  _____  _____  _____    _____  _____  _____\n"
              << "  |  |  ||     ||     ||   __|  |   __||     ||     |\n"
              << "  |     ||  |  || | | ||   __|  |__   ||-   -|| | | |\n"
              << "  |__|__||_____||_|_|_||_____|  |_____||_____||_|_|_|";

        isOn = true;
        do{
            // limpar vars e janelas
            prompt.clear();
            reader.clear();
            reader << " >> ";

            // imprimir zonas
            printZones();

            // imprimir informacao sobre a simulacao
            info.clear();
            if(h != nullptr)
                info << term::set_color(COLOR_MESSAGE)<< "\n\tHabitacao:" << term::set_color(COLOR_DEFAULT) << h->getWidth() << "x" << h->getHeight()
                << term::set_color(COLOR_MESSAGE)  <<"\tTicks:" << term::set_color(COLOR_DEFAULT) << h->getTicks()
                << term::set_color(COLOR_MESSAGE)  <<"\tNum. Zonas:" << term::set_color(COLOR_DEFAULT) << h->getNumberOfZones();
            else
                info << term::set_color(COLOR_ERROR) << "\n\tAinda nao existe uma Habitacao";

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
        if(isFromExec)
            output << "\n";
        else
            output.clear();
        output << term::set_color(COLOR_DEFAULT);


        if(cmd.empty()){
            output << term::set_color(COLOR_ERROR) << "Comando vazio";

        } else if(h == nullptr && cmd != "hnova" && cmd != "exec" && cmd != "sair" && cmd != "help"){
            output << term::set_color(COLOR_ERROR) << "Tem primeiro de criar uma habitacao: hnova <numLinhas> <numColunas>\n";

        } else if(cmd == "prox"){
            exe = new Step;
            if(exe->Execute(*h, args))
                output << term::set_color(COLOR_SUCCESS) << exe->getError();
            else
                output << term::set_color(COLOR_ERROR) << exe->getError();
            return;

        } else if(cmd == "avanca"){

            int n;
            if (iss >> n) {
                exe = new Step;
                for (int i = 0; i < n; i++) {
                    if (exe->Execute(*h, ""))
                        output << term::set_color(COLOR_SUCCESS) << exe->getError();
                    else
                        output << term::set_color(COLOR_ERROR) << exe->getError();
                }
            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : avanca <n>";

            return;

        } else if(cmd == "hnova"){

            int width, height;
            if (iss >> width >> height){

                if(h != nullptr){
                    output << term::set_color(COLOR_ERROR) << "Ja tem uma Habitacao criada";
                    return;

                } else if(width < 0 || height < 0 || width > 4 || height > 4){
                    output << term::set_color(COLOR_ERROR) << "Erro de formatacao : <num linhas> e <num colunas> tem de estar compreendido entre [1, 4]";
                    return;

                }

                h = new habitacao::Habitacao(width, height);

                output << term::set_color(COLOR_SUCCESS) << "Habitacao " << width << "x" << height << " criada";

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : hnova <num linhas> <num colunas>";

        } else if(cmd == "hrem"){

            if(!args.empty()){
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : hrem";

            } else {
                delete h;
                h = nullptr;
                output << term::set_color(COLOR_SUCCESS) << "A Habitacao foi removida";
            }
            return;

        } else if(cmd == "znova"){

            exe = new Znova;

        } else if(cmd == "zrem"){

            exe = new Zrem;

        } else if(cmd == "zlista"){

            if(!args.empty()){
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : zlista";
                return;
            }

            if(h->getNumberOfZones() == 0){
                output << term::set_color(COLOR_ERROR) << "Nao existem Zonas criadas";
                return;
            }

            for(int i=0; i < h->getNumberOfZones(); i++){
                zona::Zona z = h->getZone(i);
                output
                << term::set_color(COLOR_MESSAGE) << "Zona_" << z.getID()<< term::set_color(COLOR_DEFAULT) <<
                " (" << z.getPosX() << "," << z.getPosY() << ") : "
                << "sensores=" << z.getNumberOfSensors() << " processadores=" << z.getNumberOfProcessors() << " aparelhos=" << z.getNumberOfGadgets() <<"\n";
            }

        } else if(cmd == "zcomp"){

            int id;
            if (iss >> id) {

                if(h->getNumberOfZones() == 0){
                    output << term::set_color(COLOR_ERROR) << "Nao existem Zonas criadas";
                    return;
                }

                zona::Zona z = h->getZoneByID(id);
                output
                << term::set_color(COLOR_MESSAGE) << "Zona_" << z.getID() << "\n"
                << term::set_color(COLOR_DEFAULT) << z.getComponentsStr();

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : zcomp <ID zona>";


        }  else if(cmd == "zprops"){

            int id;
            if (iss >> id)
                printZoneProps(h->getZoneByID(id), output);

            else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : zprops <ID zona>";


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

            int idZone, idPross;
            if (iss >> idZone >> idPross) {
                output << term::set_color(COLOR_SUCCESS) << "A listar as regras do processador " << idPross << " da zona " << idZone;

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : rlista <ID zona> <ID proc. regras>";


        } else if(cmd == "rrem"){

            int idZone, idPross, idRule;
            if (iss >> idZone >> idPross >> idRule) {
                output << term::set_color(COLOR_SUCCESS) << "A remover a regra " << idRule << " do processador " << idPross << " da zona " << idZone;

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : rrem <ID zona> <ID proc. regras> <ID regra>";

        } else if(cmd == "asoc"){

            int idZone, idPross, idApr;
            if (iss >> idZone >> idPross >> idApr) {
                output << term::set_color(COLOR_SUCCESS) << "A associar o processador " << idPross << " da zona " << idZone << " ao aparelho " << idApr;

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : asoc <ID zona> <ID proc. regras> <ID aparelho>";

        } else if(cmd == "ades"){

            int idZone, idPross, idApr;
            if (iss >> idZone >> idPross >> idApr) {
                output << term::set_color(COLOR_SUCCESS) << "A desassociar o processador " << idPross << " da zona " << idZone << " ao aparelho " << idApr;

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : ades <ID zona> <ID proc. regras> <ID aparelho>";

        } else if(cmd == "acom"){

            int idZone, idApr;
            std::string command;
            if (iss >> idZone >> idApr >> command) {
                output << term::set_color(COLOR_SUCCESS) << "A enviar \'" << command << "\'ao aparelho " << idApr;

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : acom <ID zona> <ID aparelho> <comando>";

        } else if(cmd == "psalva"){

            int idZone, idPross;
            std::string name;
            if (iss >> idZone >> idPross >> name) {
                output << term::set_color(COLOR_SUCCESS) << "A guardar o processador " << idPross << " da zona " << idZone << " no nome \'" << name << "\'";

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : psalva <ID zona> <ID proc. regras> <nome>";

        } else if(cmd == "prepoe"){

            std::string name;
            if (iss >> name) {
                output << term::set_color(COLOR_SUCCESS) << "A repor a copia do processador \'" << name << "\'";

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : prepoe <nome>";

        } else if(cmd == "prem"){

            std::string name;
            if (iss >> name) {
                output << term::set_color(COLOR_SUCCESS) << "A apagar a copia do processador \'" << name << "\'";

            } else
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : prem <nome>";

        } else if(cmd == "plista"){

            if(!args.empty())
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : plista";
            else
                output << term::set_color(COLOR_SUCCESS) << "A listar as copias guardadas\n";

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
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : exec <nome de ficheiro>";

        } else if(cmd == "sair"){
            if(!args.empty())
                output << term::set_color(COLOR_ERROR) << "Erro de formatacao : sair";
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

        if(exe->Execute(*h, args))
            output << term::set_color(COLOR_SUCCESS) << " " << exe->getError();
        else
            output << term::set_color(COLOR_ERROR) << " Erro: " << exe->getError();

    }


    void Simulador::printZones() {
        // limpa o vetor
        for(auto & zona : zonas)
            delete zona;
        zonas.clear();

        // verifica se existe uma habitacao
        if(h == nullptr)
            return;

        // cria as janelas das zonas
        for(int x=0; x < h->getHeight(); x++)
            for(int y=0; y < h->getWidth(); y++)
                zonas.push_back(new term::Window(72+30*x, 6+10*y, 30, 10, true));

        // verifica se existem zonas
        if(h->getNumberOfZones() <= 0)
            return;

        // imprime a informacao de cada zona
        int count = 0;
        for(int x=0; x < h->getHeight(); x++){
            for(int y=0; y < h->getWidth(); y++){
                // vai buscar a zona correspodente
                zona::Zona current_zone = h->getZone(y + 1, x + 1);
                if (current_zone.getID() != -1)
                    *zonas.at(count) << term::set_color(COLOR_ID) << "Zona_" << current_zone.getID()
                    << term::set_color(COLOR_DEFAULT) << "\n" << current_zone.getComponents();
                count++;
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
        << term::set_color(COLOR_ID) << " rnova " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID regras> <regra> <ID sensor> [par1] [par2] [..]\n"
        << term::set_color(COLOR_ID) << " pmuda " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID regras> <novo comando>\n"
        << term::set_color(COLOR_ID) << " rlista " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID regras>\n"
        << term::set_color(COLOR_ID) << " asoc " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID regras> <ID aparelho>\n"
        << term::set_color(COLOR_ID) << " ades " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID regras> <ID aparelho>\n"
        << term::set_color(COLOR_ID) << " acom " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID aparelho> <comando>\n"
        << term::set_color(COLOR_ID) << " psalva " << term::set_color(COLOR_DEFAULT) << "<ID zona> <ID proc. regras> <nome>\n"
        << term::set_color(COLOR_ID) << " prepoe " << term::set_color(COLOR_DEFAULT) << "<nome> \n"
        << term::set_color(COLOR_ID) << " prem " << term::set_color(COLOR_DEFAULT) << "<nome> \n"
        << term::set_color(COLOR_ID) << " plista\n" << term::set_color(COLOR_DEFAULT)
        << term::set_color(COLOR_ID) << " exec " << term::set_color(COLOR_DEFAULT) << "<nome de ficheiro>\n"
        << term::set_color(COLOR_ID) << " sair\n" << term::set_color(COLOR_DEFAULT);

    }

} // simulador
