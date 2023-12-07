#ifndef HOMESIM_PROPRIEDADE_H
#define HOMESIM_PROPRIEDADE_H

#include <string>

namespace propriedades {

    constexpr int UNSET = -1000;

    class Propriedade {
    private:
        // valor a que esta definido
        int value;

        // unidade de medida
        std::string unit;

        // valor max e min que a propriedade pode assumir
        int min, max;

    public:
        Propriedade(std::string unit, int max, int min);
        virtual ~Propriedade(){}

        int getValue() const;
        // devolve o valor da propriedade

        std::string getUnit() const;
        // devolve o valor da propriedade

        bool checkNewValue(int& new_value) const;
        // verifica se o valor novo e aceitavel para a propriedade

        // funcoes aritmeticas
        Propriedade operator+(int new_value);
        Propriedade operator-(int new_value);
        Propriedade operator*(int new_value);
        Propriedade& operator=(int new_value);

    };


    //
    class Temperature : public Propriedade{
    public:
        Temperature();
    };

    class Light : public Propriedade{
    public:
        Light();
    };

    class Radiation : public Propriedade{
    public:
        Radiation();
    };

    class Vibration : public Propriedade{
    public:
        Vibration();
    };

    class Humidity : public Propriedade{
    public:
        Humidity();
    };

    class Smoke : public Propriedade{
    public:
        Smoke();
    };

    class Sound : public Propriedade{
    public:
        Sound();
    };

} // propriedades

#endif //HOMESIM_PROPRIEDADE_H
