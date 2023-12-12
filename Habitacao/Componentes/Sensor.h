#ifndef HOMESIM_SENSOR_H
#define HOMESIM_SENSOR_H

#include "Componente.h"
#include "../Propriedade.h"

namespace sensor {

    class Sensor : public componente::Componente {
    private:
        propriedades::Propriedade& prop;

    public:
        Sensor(int id, propriedades::Propriedade &prop);

        char getType() const override;
        // devolve o caracter que o descreve

        int check() const;
        // verifica e devolve o valor da Proppriedade que esta a ver

    };

} // sensor

#endif //HOMESIM_SENSOR_H
