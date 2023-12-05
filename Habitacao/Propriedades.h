#ifndef HOMESIM_PROPRIEDADES_H
#define HOMESIM_PROPRIEDADES_H

#include <string>

namespace propriedades {

    class Propriedades {
    private:
        int* temperature;
        int* light;
        int* radiation;
        int* vibration;
        int* humidity;
        int* smoke;
        int* sound;

    public:
        Propriedades();

        // temperatura
        int getTemperature() const;
        std::string getTemperatureStr() const;
        bool changeTemperature(int new_value);

        // luz
        int getLight() const;
        std::string getLightStr() const;
        bool changeLight(int new_value);

        // radiacao
        int getRadiation() const;
        std::string getRadiationStr() const;
        bool changeRadiation(int new_value);

        // vibracao
        int getVibration() const;
        std::string getVibrationStr() const;
        bool changeVibration(int new_value);

        // humidade
        int getHumidity() const;
        std::string getHumidityStr() const;
        bool changeHumidity(int new_value);

        // fumo
        int getSomke() const;
        std::string getSomkeStr() const;
        bool changeSmoke(int new_value);

        // som
        int getSound() const;
        std::string getSoundStr() const;
        bool changeSound(int new_value);


    };

} // propriedades

#endif //HOMESIM_PROPRIEDADES_H
