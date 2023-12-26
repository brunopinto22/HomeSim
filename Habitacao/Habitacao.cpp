#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "Habitacao.h"
#include "Componentes/Regra.h"

namespace habitacao {
    Habitacao::Habitacao(int width, int height):width(width), height(height), number_id(0), zone_number_id(0), rule_number_id(0), ticks(0), number_of_zones(0) {}

    int Habitacao::getZoneNumberID(){
        zone_number_id++;
        return zone_number_id;
    }

    int Habitacao::getRuleNumberID(){
        rule_number_id++;
        return rule_number_id;
    }

    int Habitacao::getNumberID() {
        number_id++;
        return number_id;
    }

    int Habitacao::getWidth() const { return width; }

    int Habitacao::getHeight() const { return height; }

    int Habitacao::getTicks() const { return ticks; }

    std::string Habitacao::getError() const { return error; }

    int Habitacao::getNumberOfZones() const { return number_of_zones; }

    bool Habitacao::isZoneTacken(int x, int y){
        for(auto & z : zonas)
            if(z->getPosY() == y && z->getPosX() == x)
                return true;
        return false;
    }

    zona::Zona Habitacao::getZone(int index) const {
        if (index >= 0 && index < zonas.size())
            return *zonas.at(index);
        else
            return {};

    }

    zona::Zona Habitacao::getZone(int x, int y) const {
        auto it = std::find_if(zonas.begin(), zonas.end(), [x, y](const zona::Zona* zona) { return zona->getPosX() == x && zona->getPosY() == y; });

        if (it != zonas.end()) {
            return *(*it);
        } else
            return {};
    }

    zona::Zona Habitacao::getZoneByID(int id) const {
        auto it = std::find_if(zonas.begin(), zonas.end(), [id](const zona::Zona* zona) { return zona->getID() == id; });

        if (it != zonas.end())
            return *(*it);
        else
            return {};
    }

    bool Habitacao::checkZoneID(int id) const{

        auto it = std::find_if(zonas.begin(), zonas.end(), [id](const zona::Zona* zona) {return zona->getID() == id;});
        if(it != zonas.end())
            return true;
        return false;

    }

    void Habitacao::addZone(int x, int y) {
        this->zonas.push_back(new zona::Zona(getZoneNumberID(), x, y));
        number_of_zones++;
    }

    void Habitacao::removeZone(int id) {
        zonas.erase(std::remove_if(zonas.begin(),zonas.end(), [id](const zona::Zona* zona) { return zona->getID() == id; }), zonas.end());
        number_of_zones--;
    }

    bool Habitacao::changeZoneProp(int id, std::string prop_name, int new_value) {
        std::ostringstream oss;

        if(!checkZoneID(id)){
            oss << "A Zona com o id=" << id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [id](const zona::Zona* z) { return z->getID() == id; });
        zona::Zona* target = *it;

        if (!target->setProp(prop_name, new_value)) {
            error = target->getError();
            return false;
        }

        error = target->getError();
        return true;
    }

    bool Habitacao::checCompType(char type) {
        switch (type) {
            case static_cast<char>(componente::ComponenteType::APARELHO):
            case static_cast<char>(componente::ComponenteType::SENSOR):
            case static_cast<char>(componente::ComponenteType::PROCESSADOR):
                return true;
            default:
                return false;
        }
    }

    bool Habitacao::addComponent(int zone_id, char type, std::string& typeOrCmd) {
        std::ostringstream oss;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        if (!target->addComponent(getNumberID(), type, typeOrCmd)) {
            error = target->getError();
            return false;
        }

        error = target->getError();
        return true;
    }

    bool Habitacao::removeComponent(int zone_id, char type, int comp_id) {
        std::ostringstream oss;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        if(!checCompType(type)){
            oss << "O tipo de Componente \'" << type << "\' nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        if (!target->removeComponent(type, comp_id)) {
            error = target->getError();
            return false;
        }

        error = target->getError();
        return true;
    }

    bool Habitacao::addRule(int zone_id, int proc_id, int sens_id, const std::string& rule_type, const std::string& values) {
        std::ostringstream oss;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        if (!target->addRule(getRuleNumberID(), sens_id, rule_type, values, proc_id)) {
            error = target->getError();
            return false;
        }

        error = target->getError();
        return true;
    }

    bool Habitacao::removeRule(int zone_id, int proc_id, int rule_id){
        std::ostringstream oss;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        if (!target->removeRule(proc_id, rule_id)) {
            error = target->getError();
            return false;
        }

        error = target->getError();
        return true;
    }

    bool Habitacao::getProcessorRules(int zone_id, int proc_id) {
        std::ostringstream oss;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;


        if(target->getNumberOfRulesOfProcessor(proc_id) <= 0){
            error = target->getError();
            return false;
        }

        error = target->getRules(proc_id);
        return true;
    }

    bool Habitacao::changeProcCmd(int zone_id, int proc_id, const std::string &new_cmd) {
        std::ostringstream oss;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        if(!target->changeProcCmd(proc_id, new_cmd)) {
            error = target->getError();
            return false;
        }

        error = target->getError();
        return true;
    }

    bool Habitacao::linkProcAndGadget(int zone_id, int proc_id, int gadget_id) {
        std::ostringstream oss;
        bool result;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        result = target->linkProcAndGadget(proc_id, gadget_id);
        error = target->getError();

        return result;
    }

    bool Habitacao::unlinkProcAndGadget(int zone_id, int proc_id, int gadget_id) {
        std::ostringstream oss;
        bool result;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        result = target->unlinkProcAndGadget(proc_id, gadget_id);
        error = target->getError();

        return result;
    }

    bool Habitacao::sendCommandToGadget(int zone_id, int gadget_id, std::string command) {
        std::ostringstream oss;
        bool result;

        if(!checkZoneID(zone_id)){
            oss << "A Zona com o id=" << zone_id << " nao existe";
            error = oss.str();
            return false;
        }

        // procura e guarda a zona
        auto it = std::find_if(zonas.begin(), zonas.end(), [zone_id](const zona::Zona* z) { return z->getID() == zone_id; });
        zona::Zona* target = *it;

        result = target->sendCmdTo(gadget_id, command);
        error = target->getError();

        return result;
    }



    bool Habitacao::tick() {
        std::ostringstream oss;
        ticks++;

        for(auto& zona : zonas) {
            zona->tick();
            oss << zona->getError();
        }

        error = oss.str();
        return true;
    }


} // habitacao