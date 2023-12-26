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

        virtual std::string getInfo() const override;
        // devolve a informacao do componente

        int getValue() const;
        std::string getValueStr() const;
        // devolve o valor da Propriedade que esta a ver

        std::string run() override;
        // corre o Sensor

    };

} // sensor

#endif //HOMESIM_SENSOR_H
