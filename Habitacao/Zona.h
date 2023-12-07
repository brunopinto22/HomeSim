#ifndef HOMESIM_ZONA_H
#define HOMESIM_ZONA_H

#include <string>
#include "Propriedade.h"

namespace zona {


    class Zona {
    private:
        int id;
        int pos_x, pos_y; // coordenadas

        propriedades::Temperature temperature;
        propriedades::Light light;
        propriedades::Radiation radiation;
        propriedades::Vibration vibration;
        propriedades::Humidity humidity;
        propriedades::Smoke smoke;
        propriedades::Sound sound;

    public:
        Zona();
        Zona(int number_id, int x, int y);

        int getID() const;
        // devolve o ID

        int getPosX() const;
        // devolve a posicao em x
        int getPosY() const;
        // devolve a posicao em y

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
