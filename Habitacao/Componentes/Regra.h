#ifndef HOMESIM_REGRA_H
#define HOMESIM_REGRA_H

#include "Sensor.h"

namespace regra {

    enum RegraType {
        IGUAL,
        MAIOR,
        MENOR,
        ENTRE,
        FORA
    };

    class Regra {
        RegraType type;

    protected:
        sensor::Sensor& sensor;
    public:
        Regra(RegraType type, sensor::Sensor& sensor);

        RegraType getType() const;
        // devolve o tipo de Regra

        virtual bool check() const;
        // verifica se a regra e verdade
        // retorna:     true - caso seja verdade
        //              false - caso contrario

    };

    class RegraIgual : public Regra{
    private:
        int value;
    public:
        RegraIgual(sensor::Sensor& sensor, int value);
        bool check() const override;
    };
    class RegraMaior : public Regra{
    private:
        int value;
    public:
        RegraMaior(sensor::Sensor& sensor, int value);
        bool check() const override;
    };
    class RegraMenor : public Regra{
    private:
        int value;
    public:
        RegraMenor(sensor::Sensor& sensor, int value);
        bool check() const override;
    };


    class RegraEntre : public Regra{
    private:
        int value, value2;
    public:
        RegraEntre(sensor::Sensor& sensor, int value, int value2);
        bool check() const override;
    };
    class RegraFora : public Regra{
    private:
        int value, value2;
    public:
        RegraFora(sensor::Sensor& sensor, int value, int value2);
        bool check() const override;
    };


} // regra

#endif //HOMESIM_REGRA_H
