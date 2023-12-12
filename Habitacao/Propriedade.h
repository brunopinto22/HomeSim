#ifndef HOMESIM_PROPRIEDADE_H
#define HOMESIM_PROPRIEDADE_H

#include <string>

namespace propriedades {

    constexpr int UNSET = -1000;

    enum PropriedadeType : char {
        TEMPERATURA = 't',
        VIBRACAO = 'v',
        LUZ = 'm',
        RADIACAO = 'r',
        HUMIDADE = 'h',
        SOM = 'o',
        FUMO = 'f'
    };

    class Propriedade {
    private:
        // valor a que esta definido
        int value;

        // unidade de medida
        std::string unit;

        // nome da propriedade
        std::string name;

        // tipo da
        PropriedadeType type;

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

        std::string getName() const;
        // devolve o nome da propriedade

        PropriedadeType getType() const;
        // devolve o tipo da propriedade

        bool checkNewValue(int& new_value) const;
        // verifica se o valor novo e aceitavel para a propriedade

        Propriedade& operator+(int new_value);
        Propriedade& operator-(int new_value);
        Propriedade& operator*(int new_value);
        Propriedade& operator/(int new_value);
        Propriedade& operator=(int new_value);

    };


    class Temperatura : public Propriedade{
    public:
        Temperatura();
    };

    class Luz : public Propriedade{
    public:
        Luz();
    };

    class Radiacao : public Propriedade{
    public:
        Radiacao();
    };

    class Vibracao : public Propriedade{
    public:
        Vibracao();
    };

    class Humidade : public Propriedade{
    public:
        Humidade();
    };

    class Fumo : public Propriedade{
    public:
        Fumo();
    };

    class Som : public Propriedade{
    public:
        Som();
    };


} // propriedades

#endif //HOMESIM_PROPRIEDADE_H
