#ifndef HOMESIM_REGRA_H
#define HOMESIM_REGRA_H

#include "Sensor.h"

namespace regra {

    enum RegraType {
        IGUAL,
        MAIOR,
        MENOR,
        ENTRE,
        FORA,
        NOTATYPE
    };
    RegraType checkRuleType(const std::string& str);
    std::string checkRuleType(RegraType type);

    class Regra {
    private:
        int id;
        RegraType type;

    protected:
        sensor::Sensor& sensor;
    public:
        Regra(int id, sensor::Sensor &sensor, RegraType type);

        int getID() const;
        // devolve o Id da Regra

        RegraType getType() const;
        // devolve o tipo de Regra

        std::string getInfo() const;
        // devolve a informacao da Regra

        virtual bool check() const;
        // verifica se a regra e verdade
        // retorna:     true - caso seja verdade
        //              false - caso contrario

    };

    class RegraIgual : public Regra{
    private:
        int value;
    public:
        RegraIgual(int id, sensor::Sensor& sensor, int value);
        bool check() const override;
    };
    class RegraMaior : public Regra{
    private:
        int value;
    public:
        RegraMaior(int id, sensor::Sensor& sensor, int value);
        bool check() const override;
    };
    class RegraMenor : public Regra{
    private:
        int value;
    public:
        RegraMenor(int id, sensor::Sensor& sensor, int value);
        bool check() const override;
    };


    class RegraEntre : public Regra{
    private:
        int value, value2;
    public:
        RegraEntre(int id, sensor::Sensor& sensor, int value, int value2);
        bool check() const override;
    };
    class RegraFora : public Regra{
    private:
        int value, value2;
    public:
        RegraFora(int id, sensor::Sensor& sensor, int value, int value2);
        bool check() const override;
    };


} // regra

#endif //HOMESIM_REGRA_H
