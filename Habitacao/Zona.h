#ifndef HOMESIM_ZONA_H
#define HOMESIM_ZONA_H

#include <string>
#include "Propriedade.h"

namespace zona {


    class Zona {
    private:
        int id;
        int pos_x, pos_y; // coordenadas

        std::string error;

        propriedades::Propriedade temperature;
        propriedades::Propriedade light;
        propriedades::Propriedade radiation;
        propriedades::Propriedade vibration;
        propriedades::Propriedade humidity;
        propriedades::Propriedade smoke;
        propriedades::Propriedade sound;


    public:
        Zona();
        Zona(int number_id, int x, int y);

        int getID() const;
        // devolve o ID

        int getPosX() const;
        // devolve a posicao em x
        int getPosY() const;
        // devolve a posicao em y

        std::string getError();
        // devolve o ultimo erro ocorrido


        bool setProp(std::string type, int new_value);
        // define o valor de uma propriedade
        // retorna:     true caso corra tudo bem
        //              false em caso de algum erro

        int getTemperature() const;
        std::string getTemperatureStr() const;
        // devolve a temperatura

        int getLight() const;
        std::string getLightStr() const;
        // devolve a luz

        int getRadiation() const;
        std::string getRadiationStr() const;
        // devolve a radiacao

        int getVibration() const;
        std::string getVibrationStr() const;
        // devolve a vibracao

        int getHumidity() const;
        std::string getHumidityStr() const;
        // devolve a humidade

        int getSmoke() const;
        std::string getSmokeStr() const;
        // devolve o fumo

        int getSound() const;
        std::string getSoundStr() const;
        // devolve o som

    };

} // zona

#endif //HOMESIM_ZONA_H
