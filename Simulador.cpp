#include <sstream>
#include <fstream>
#include "Simulador.h"


namespace utils{

    std::string error;

    std::string getError(){ return error; }

    void splitCMD(std::string prompt, std::string* cmd, std::string* args){
        size_t spacePos = prompt.find(' ');
        if (spacePos != std::string::npos) { // com argumentos
            *cmd = prompt.substr(0, spacePos);
            *args = prompt.substr(spacePos + 1);
        } else { // sem argumentos
            *cmd = prompt;
            *args = "";
        }
    }

    bool verifyCMD(std::string& comando, std::string& argumentos) {

        std::istringstream iss(argumentos);

        if(comando.empty()){
            error = "comando vazio";
            return false;

        } else if(comando == "prox"){
            if(argumentos.empty())
                return true;
            error = "Erro de formatacao : prox";
            return false;

        } else if(comando == "avanca"){

            int n;
            if (iss >> n){
                if(n < 0){
                    error = "Erro de formatacao : <n> tem de ser maior que 0";
                    return false;
                }
                return true;
            }
            error = "Erro de formatacao : avanca <n>";
            return false;

        } else if(comando == "hnova"){

            int x, y;
            if (iss >> x >> y){
                if(x < 0 || x > 4 || y < 0 || y > 4) {
                    error = "Erro de formatacao : <num linhas> e <num colunas> tem de estar compreendido entre [1, 4]";
                    return false;
                }
                return true;
            }
            error = "Erro de formatacao : hnova <num linhas> <num colunas>";
            return false;

        } else if(comando == "hrem"){
            if(argumentos.empty())
                return true;
            error = "Erro de formatacao : hrem";
            return false;

        } else if(comando == "znova"){
            int x, y;
            if (iss >> x >> y)
                return true;

            error = "Erro de formatacao : znova <linha> <coluna>";
            return false;

        } else if(comando == "zrem"){
            int id;
            if (iss >> id)
                return true;
            error = "Erro de formatacao : zrem <ID zona>";
            return false;

        } else if(comando == "zlista"){
            if(!argumentos.empty())
                return true;
            error = "Erro de formatacao : zlista";
            return false;

        } else if(comando == "zcomp"){
            int id;
            if (iss >> id)
                return true;
            error = "Erro de formatacao : zcomp <ID zona>";
            return false;

        } else if(comando == "pmod"){
            int id, value;
            std::string name;
            if (iss >> id >> name >> value)
                return true;
            error = "Erro de formatacao : pmod <ID zona> <nome> <valor>";
            return false;

        } else if(comando == "cnovo"){
            int id;
            char type;
            std::string typeOrCmd;
            if (iss >> id >> type >> typeOrCmd)
                return true;
            error = "Erro de formatacao : cnovo <ID zona> <s | p | a> <tipo | comando>";
            return false;

        } else if(comando == "crem"){
            int id, idZone;
            char type;
            if (iss >> idZone >> type >> id)
                return true;
            error = "Erro de formatacao : crem <ID zona> <s | p | a> <ID>";
            return false;

        } else if(comando == "rnova"){
            int idZone, idPross, idSens, par1, par2;
            std::string rule;
            if (iss >> idZone >> idPross >> rule >> idSens >> par1 >> par2)
                return true;
            else if (iss >> idZone >> idPross >> rule >> idSens >> par1)
                return true;
            error = "Erro de formatacao : rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]";
            return false;

        } else if(comando == "pmuda"){
            int idZone, idPross;
            std::string command;
            if (iss >> idZone >> idPross >> command)
                return true;
            error = "Erro de formatacao : pmuda <ID zona> <ID proc. regras> <novo comando>";
            return false;

        } else if(comando == "rlista"){
            int idZone, idPross;
            if (iss >> idZone >> idPross)
                return true;
            error = "Erro de formatacao : rlista <ID zona> <ID proc. regras>";
            return false;

        } else if(comando == "rrem"){
            int idZone, idPross, idRule;
            if (iss >> idZone >> idPross >> idRule)
                return true;
            error = "Erro de formatacao : rrem <ID zona> <ID proc. regras> <ID regra>";
            return false;

        } else if(comando == "asoc"){
            int idZone, idPross, idApr;
            if (iss >> idZone >> idPross >> idApr)
                return true;
            error = "Erro de formatacao : asoc <ID zona> <ID proc. regras> <ID aparelho>";
            return false;

        } else if(comando == "ades"){
            int idZone, idPross, idApr;
            if (iss >> idZone >> idPross >> idApr)
                return true;
            error = "Erro de formatacao : ades <ID zona> <ID proc. regras> <ID aparelho>";
            return false;

        } else if(comando == "acom"){
            int idZone, idApr;
            std::string command;
            if (iss >> idZone >> idApr >> command)
                return true;
            error = "Erro de formatacao : acom <ID zona> <ID aparelho> <comando>";
            return false;

        } else if(comando == "psalva"){
            int idZone, idPross;
            std::string name;
            if (iss >> idZone >> idPross >> name)
                return true;
            error = "Erro de formatacao : psalva <ID zona> <ID proc. regras> <nome>";
            return false;

        } else if(comando == "prepoe"){
            std::string name;
            if (iss >> name)
                return true;
            error = "Erro de formatacao : prepoe <nome>";
            return false;

        } else if(comando == "prem"){
            std::string name;
            if (iss >> name)
                return true;
            error = "Erro de formatacao : prem <nome>";
            return false;

        } else if(comando == "plista"){
            if(argumentos.empty())
                return true;
            error = "plista";
            return false;

        } else if(comando == "exec"){
            std::string filename;
            if(iss >> filename)
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
}


namespace simulador {

    Simulador::Simulador(term::Terminal &t, int width, int height):t(&t), isOn(false), h(width, height) {

        // criar as janelas das zonas
        for(int x=0; x < height; x++)
            for(int y=0; y < width; y++)
                zonas.push_back(new term::Window(61+20*x, 1+5*y, 20, 5, true));
    }


    void Simulador::start() {
        std::string text;
        std::string cmd, args;
        std::ostringstream oss;

        // limpar terminal
        t->clear();

        // janelas
        term::Window title = term::Window(1,1,60,5, false);
        term::Window reader = term::Window(1,6,60,7, true);
        term::Window output = term::Window(1, 13, 60, 21, true);

        title << term::set_color(COLOR_MESSAGE)
              << " _____ _____ _____ _____    _____ _____ _____\n"
              << "|  |  |     |     |   __|  |   __|     |     |\n"
              << "|     |  |  | | | |   __|  |__   |-   -| | | |\n"
              << "|__|__|_____|_|_|_|_____|  |_____|_____|_|_|_|";

        isOn = true;
        do{

            // refresh da janela
            reader.clear();
            reader << ">> ";

            // imprimir zonas
            printZones();

            // ler comando
            reader >> text;

            // dividir comando
            utils::splitCMD(text, &cmd, &args);

            // executa o comando
            executeCommand(cmd, args, output, false);

        } while(isOn);

    }


    void Simulador::executeCommand(std::string& cmd, std::string& args, term::Window& output, bool isFromExec) {

        if(!isFromExec)
            output.clear();
        output << term::set_color(COLOR_DEFAULT);
        std::istringstream iss(args);

        if(!utils::verifyCMD(cmd, args)){
            output << term::set_color(COLOR_ERROR) << utils::getError() << "\n";
            return;

        }
        else if(cmd == "prox"){
            step(output);
            return;

        } else if(cmd == "avanca"){

            int n;
            if (iss >> n) {

                for(n; n > 0; n--)
                    if(!step(output))
                        output << term::set_color(COLOR_ERROR) << error << "\n";

            }
            return;

        } else if(cmd == "hnova"){
            output << term::set_color(COLOR_ERROR) << "Ja criou uma habitacao\n";
            return;

        } else if(cmd == "hrem"){
            isOn = false;
            return;

        } else if(cmd == "znova"){

            int x, y;
            if (iss >> x >> y) {
                Znova newzona(x,y);

                if(!newzona.Execute(h))
                    output << term::set_color(COLOR_ERROR) << newzona.getError() << "\n";
                else
                    output << term::set_color(COLOR_SUCCESS) << "Criou uma Zona em ("<< x <<","<< y <<")\n";

            }
            return;

        } else if(cmd == "zrem"){

            int id;
            if (iss >> id) {
                output << term::set_color(COLOR_SUCCESS) << "A remover a zona " << id << "\n";
            }
            return;

        } else if(cmd == "zlista"){

            output << term::set_color(COLOR_SUCCESS) << "A listar as zonas\n";
            return;

        } else if(cmd == "zcomp"){

            int id;
            if (iss >> id) {
                output << term::set_color(COLOR_SUCCESS) << "A listar os componentes da zona " << id << "\n";
            }
            return;

        } else if(cmd == "pmod"){

            int id, value;
            std::string name;
            if (iss >> id >> name >> value) {
                output << term::set_color(COLOR_SUCCESS) << "A modificar a propriedade " << name << " da zona " << id << "para" << value << "\n";
            }
            return;

        } else if(cmd == "cnovo"){

            int id;
            char type;
            std::string typeOrCmd;
            if (iss >> id >> type >> typeOrCmd) {
                output << term::set_color(COLOR_SUCCESS) << "A adicionar " << type << " com as definicoes" << typeOrCmd << " na zona" << id << "\n";
            }
            return;

        } else if(cmd == "crem"){

            int id, idZone;
            char type;
            if (iss >> idZone >> type >> id) {
                output << term::set_color(COLOR_SUCCESS) << "A remover " << type << " " << id << " da zona" << idZone << "\n";
            }
            return;

        } else if(cmd == "rnova"){

            int idZone, idPross, idSens, par1, par2;
            std::string rule;
            if (iss >> idZone >> idPross >> rule >> idSens >> par1 >> par2) {
                output << term::set_color(COLOR_SUCCESS) << "A adicionar uma regra \'" << rule << "\' " << idZone << " " << idPross << idSens << " " << par1 << " " << par2 << "\n";
            } else if (iss >> idZone >> idPross >> rule >> idSens >> par1) {
                output << term::set_color(COLOR_SUCCESS) << "A adicionar uma regra \'" << rule << "\' " << idZone << " " << idPross << idSens << " " << par1 << "\n";
            }
            return;

        } else if(cmd == "pmuda"){

            int idZone, idPross;
            std::string command;
            if (iss >> idZone >> idPross >> command) {
                output << term::set_color(COLOR_SUCCESS) << "A mudar o comando do processador " << idPross << " da zona " << idZone << " com o comando " << command << "\n";
            }
            return;

        } else if(cmd == "rlista"){

            int idZone, idPross;
            if (iss >> idZone >> idPross) {
                output << term::set_color(COLOR_SUCCESS) << "A listar as regras do processador " << idPross << " da zona " << idZone << "\n";
            }
            return;

        } else if(cmd == "rrem"){

            int idZone, idPross, idRule;
            if (iss >> idZone >> idPross >> idRule) {
                output << term::set_color(COLOR_SUCCESS) << "A remover a regra " << idRule << " do processador " << idPross << " da zona " << idZone << "\n";
            }
            return;

        } else if(cmd == "asoc"){

            int idZone, idPross, idApr;
            if (iss >> idZone >> idPross >> idApr) {
                output << term::set_color(COLOR_SUCCESS) << "A associar o processador " << idPross << " da zona " << idZone << " ao aparelho " << idApr <<"\n";
            }
            return;

        } else if(cmd == "ades"){

            int idZone, idPross, idApr;
            if (iss >> idZone >> idPross >> idApr) {
                output << term::set_color(COLOR_SUCCESS) << "A desassociar o processador " << idPross << " da zona " << idZone << " ao aparelho " << idApr <<"\n";
            }
            return;

        } else if(cmd == "acom"){

            int idZone, idApr;
            std::string command;
            if (iss >> idZone >> idApr >> command) {
                output << term::set_color(COLOR_SUCCESS) << "A enviar \'" << command << "\'ao aparelho " << idApr <<"\n";
            }
            return;

        } else if(cmd == "psalva"){

            int idZone, idPross;
            std::string name;
            if (iss >> idZone >> idPross >> name) {
                output << term::set_color(COLOR_SUCCESS) << "A guardar o processador " << idPross << " da zona " << idZone << " no nome \'" << name << "\'\n";
            }
            return;

        } else if(cmd == "prepoe"){

            std::string name;
            if (iss >> name) {
                output << term::set_color(COLOR_SUCCESS) << "A repor a copia do processador \'" << name << "\'\n";
            }
            return;

        } else if(cmd == "prem"){

            std::string name;
            if (iss >> name) {
                output << term::set_color(COLOR_SUCCESS) << "A apagar a copia do processador \'" << name << "\'\n";
            }
            return;

        } else if(cmd == "plista"){
            output << term::set_color(COLOR_SUCCESS) << "A listar as copias guardadas\n";
            return;

        } else if(cmd == "exec"){

            std::string filename, text;
            if(iss >> filename) {
                std::ifstream file(filename);

                // verificar se o ficheiro abriu
                if(!file.is_open()){
                    output << term::set_color(COLOR_ERROR) << "Nao foi possivel abrir o ficheiro \'" << filename << "\'\n";
                    return;
                }

                while (std::getline(file, text)) {
                    // dividir o comando
                    utils::splitCMD(text, &cmd, &args);
                    // executa o comando
                    executeCommand(cmd, args, output, true);
                }

            }
            return;

        } else if(cmd == "sair")
            isOn = false;

    }


    bool Simulador::step(term::Window& output){
        output << term::set_color(COLOR_SUCCESS) << "Avancei um instante\n";
        return true;
    }


    void Simulador::printZones() {
        zona::Zona* z;
        int count = 0;

        if(h.getNumberOfZones() <= 0)
            return;

        for(int i=0; i < zonas.size(); i++)
            zonas.at(i)->clear();

        for(int x=0; x < h.getHeight(); x++){
            for(int y=0; y < h.getWidth(); y++){
                int i = 0;
                do{
                    z = h.getZone(i);
                    if(z != nullptr && z->getPosX() == y+1 && z->getPosY() == x+1)
                        break;
                    i++;
                } while(z != nullptr);

                if(z == nullptr)
                    *zonas.at(count) << "";
                else
                    *zonas.at(count) << z->getID();

                count++;

            }
        }

    }

} // simulador
