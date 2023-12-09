#ifndef HOMESIM_PROPRIEDADE_H
#define HOMESIM_PROPRIEDADE_H

#include <string>

namespace propriedades {

    constexpr int UNSET = -1000;
    constexpr int NULL_VALUE = -2000;


    class Propriedade {
    private:
        // valor a que esta definido
        int value;

        // unidade de medida
        std::string unit;

        // nome da propriedade
        std::string type;

        // valor max e min que a propriedade pode assumir
        int min, max;

    public:
        Propriedade();
        Propriedade(std::string type, std::string unit, int max, int min);
        ~Propriedade() = default;

        int getValue() const;
        std::string getValueStr() const;
        // devolve o valor da propriedade

        std::string getMin() const;
        // devolve o valor minimo da propriedade

        std::string getMax() const;
        // devolve o valor maximo da propriedade

        std::string getUnit() const;
        // devolve o valor da propriedade

        std::string getType() const;
        // devolve o valor minimo da propriedade

        bool checkNewValue(int& new_value) const;
        // verifica se o valor novo e aceitavel para a propriedade

        Propriedade& operator+(int new_value);
        Propriedade& operator-(int new_value);
        Propriedade& operator*(int new_value);
        Propriedade& operator/(int new_value);
        Propriedade& operator=(int new_value);

    };


} // propriedades

#endif //HOMESIM_PROPRIEDADE_H
