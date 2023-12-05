//#ifndef HOMESIM_PROPRIEDADE_H
//#define HOMESIM_PROPRIEDADE_H
//
//#include <string>
//
//namespace propriedades {
//
//    constexpr int UNSET = -1000;
//
//    class Propriedade {
//    private:
//        int value;
//        std::string unit;
//
//    public:
//        Propriedade();
//        virtual ~Propriedade(){}
//
//        int getValue() const;
//        // devolve o valor da propriedade
//
//        std::string getUnit() const;
//        // devolve o valor da propriedade
//
//        virtual bool checkNewValue(int& new_value) const;
//        // verifica se o valor novo e aceitavel para a propriedade
//
//        // funcoes aritmeticas
//        Propriedade operator+(int value);
//        Propriedade operator-(int value);
//        Propriedade operator*(int value);
//        Propriedade& operator=(int value);
//
//    };
//
//
//    class Temperature : public Propriedade{
//    public:
//        bool checkNewValue(int& new_value) const override;
//        Temperature operator+(int value);
//        Temperature operator-(int value);
//        Temperature operator*(int value);
//        Temperature& operator=(int value);
//    };
//
//    class Light : public Propriedade{
//    public:
//        bool checkNewValue(int& new_value) const override;
//        Light operator+(int value);
//        Light operator-(int value);
//        Light operator*(int value);
//        Light& operator=(int value);
//    };
//
//    class Radiation : public Propriedade{
//    public:
//        bool checkNewValue(int& new_value) const override;
//        Radiation operator+(int value);
//        Radiation operator-(int value);
//        Radiation operator*(int value);
//        Radiation& operator=(int value);
//    };
//
//    class Vibration : public Propriedade{
//    public:
//        bool checkNewValue(int& new_value) const override;
//        Vibration operator+(int value);
//        Vibration operator-(int value);
//        Vibration operator*(int value);
//        Vibration& operator=(int value);
//    };
//
//    class Humidity : public Propriedade{
//    public:
//        bool checkNewValue(int& new_value) const override;
//        Humidity operator+(int value);
//        Humidity operator-(int value);
//        Humidity operator*(int value);
//        Humidity& operator=(int value);
//    };
//
//    class Smoke : public Propriedade{
//    public:
//        bool checkNewValue(int& new_value) const override;
//        Smoke operator+(int value);
//        Smoke operator-(int value);
//        Smoke operator*(int value);
//        Smoke& operator=(int value);
//    };
//
//    class Sound : public Propriedade{
//    public:
//        bool checkNewValue(int& new_value) const override;
//        Sound operator+(int value);
//        Sound operator-(int value);
//        Sound operator*(int value);
//        Sound& operator=(int value);
//    };
//
//} // propriedades
//
//#endif //HOMESIM_PROPRIEDADE_H
