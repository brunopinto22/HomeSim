#include <iostream>
#include <sstream>
#include "Comando.h"

void Comando::defineError(std::string error_message) { this->error = error_message; }

std::string Comando::getError() const {
    return error;
}



Step::Step() {}
bool Step::Execute(habitacao::Habitacao &h, std::string args){
    if(!args.empty()){
        defineError("prox");
        return false;
    }

    if(!h.tick()){
        defineError(h.getError());
        return false;
    }
    return true;

}


Znova::Znova() {}
bool Znova::Execute(habitacao::Habitacao &h, std::string args) {
    std::ostringstream oss;
    std::istringstream iss(args);
    int x,y;

    if(iss >> x >> y){

        if(h.getNumberOfZones() >= h.getHeight()*h.getWidth()){
            defineError("A Habitacao esta cheia");
            return false;

        } else if(x < 1 || x > h.getHeight() || y < 1 || y > h.getWidth()){
            oss << "O valor de x e de y tem de estar compreendidos entre (1," << h.getHeight() << ") e (1," << h.getWidth()<<")";
            defineError(oss.str());
            return false;

        } else if(h.isZoneTacken(x,y)){
            oss << "A posicao (" << x << "," << y <<") esta preenchida";
            defineError(oss.str());
            return false;
        }


        h.addZone(x, y);
        oss << "Foi criada a zona em (" << x << "," << y << ")";
        defineError(oss.str());
        return true;

    }
    defineError("znova <x> <y>");
    return false;

}


Zrem::Zrem() {}
bool Zrem::Execute(habitacao::Habitacao &h, std::string args) {
    std::ostringstream oss;
    std::istringstream iss(args);
    int id;
    if (iss >> id) {

        if(!h.checkZoneID(id)){
            oss << "A Zona com o id=" << id << " nao existe";
            defineError(oss.str());
            return false;
        }

        h.removeZone(id);
        oss << "A Zona_" << id << " foi removida";
        defineError(oss.str());
        return true;

    }
    defineError("zrem <ID zona>");
    return false;

}

Pmod::Pmod() {}
bool Pmod::Execute(habitacao::Habitacao &h, std::string args) {

    std::ostringstream oss;
    std::istringstream iss(args);

    int id, value;
    std::string name;
    if (iss >> id >> name >> value) {

        if(!h.changeZoneProp(id, name, value)){
            defineError(h.getError());
            return false;
        }

        oss << "A Propriedade " << name << " da Zona_" << id << " foi atualizada para " << h.getError();
        defineError(oss.str());
        return true;

    }

    defineError("pmod <ID zona> <nome> <valor>");
    return false;
}

Cnovo::Cnovo() {}
bool Cnovo::Execute(habitacao::Habitacao &h, std::string args) {

    std::ostringstream oss;
    std::istringstream iss(args);

    int zone_id;
    char type;
    std::string typeOrCmd;
    if (iss >> zone_id >> type >> typeOrCmd) {

        if(!h.addComponent(zone_id, type, typeOrCmd)){
            defineError(h.getError());
            return false;
        }

        oss << h.getError() << " na Zona_" << zone_id;
        defineError(oss.str());
        return true;
    }

    defineError("cnovo <ID zona> <s | p | a> <tipo | comando>");
    return false;
}

Crem::Crem() {}
bool Crem::Execute(habitacao::Habitacao &h, std::string args) {

    std::ostringstream oss;
    std::istringstream iss(args);

    int zone_id, comp_id;
    char type;
    std::string typeOrCmd;
    if (iss >> zone_id >> type >> comp_id) {

        if(!h.removeComponent(zone_id, type, comp_id)){
            defineError(h.getError());
            return false;
        }

        oss << h.getError() << " na Zona_" << zone_id;
        defineError(oss.str());
        return true;
    }

    defineError("crem <ID zona> <s | p | a> <ID>");
    return false;
}

Rnova::Rnova() {}
bool Rnova::Execute(habitacao::Habitacao &h, std::string args) {

    std::ostringstream oss;
    std::istringstream iss(args);

    int zone_id, proc_id, sens_id;
    std::string rule_type, params;
    if (iss >> zone_id >> proc_id >> rule_type >> sens_id ) {
        std::getline(iss >> std::ws, params);

        if(!h.addRule(zone_id, proc_id, sens_id, rule_type, params)){
            defineError(h.getError());
            return false;
        }

        oss << h.getError() << " na Zona_" << zone_id;
        defineError(oss.str());
        return true;

    }

    defineError("rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]");
    return false;
}

Pmuda::Pmuda() {}
bool Pmuda::Execute(habitacao::Habitacao &h, std::string args) {

    std::ostringstream oss;
    std::istringstream iss(args);

    int zone_id, proc_id;
    std::string new_cmd;
    if (iss >> zone_id >> proc_id >> new_cmd) {

        if(!h.changeProcCmd(zone_id, proc_id, new_cmd)){
            defineError(h.getError());
            return false;
        }

        oss << h.getError() << " na Zona_" << zone_id;
        defineError(oss.str());
        return true;

    }

    defineError("pmuda <ID zona> <ID proc. regras> <novo comando>");
    return false;
}

Rlista::Rlista() {}
bool Rlista::Execute(habitacao::Habitacao &h, std::string args) {

    std::istringstream iss(args);
    bool result;

    int zone_id, proc_id;
    if (iss >> zone_id >> proc_id) {

        result = h.getProcessorRules(zone_id, proc_id);

        defineError(h.getError());
        return result;
    }

    defineError("rlista <ID zona> <ID proc. regras>");
    return false;
}

Rrem::Rrem() {}
bool Rrem::Execute(habitacao::Habitacao &h, std::string args) {

    std::istringstream iss(args);
    bool result;

    int zone_id, proc_id, rule_id;
    if (iss >> zone_id >> proc_id >> rule_id) {

        result = h.removeRule(zone_id, proc_id, rule_id);
        defineError(h.getError());

        return result;
    }

    defineError("rrem <ID zona> <ID proc. regras> <ID regra>");
    return false;
}

Asoc::Asoc() {}
bool Asoc::Execute(habitacao::Habitacao &h, std::string args) {

    std::istringstream iss(args);
    bool result;

    int zone_id, proc_id, gadget_id;
    if (iss >> zone_id >> proc_id >> gadget_id) {

        result = h.linkProcAndGadget(zone_id, proc_id, gadget_id);
        defineError(h.getError());

        return result;
    }

    defineError("asoc <ID zona> <ID proc. regras> <ID aparelho>");
    return false;
}

Acom::Acom() {}
bool Acom::Execute(habitacao::Habitacao &h, std::string args) {

    std::istringstream iss(args);
    bool result;

    int zone_id, gadget_id;
    std::string cmd;
    if (iss >> zone_id >> gadget_id >> cmd) {

        result = h.sendCommandToGadget(zone_id, gadget_id, cmd);
        defineError(h.getError());

        return result;
    }

    defineError("acom <ID zona> <ID aparelho> <comando>");
    return false;
}