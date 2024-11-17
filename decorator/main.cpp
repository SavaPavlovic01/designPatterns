#include <iostream>

class Beverage{
public:
    virtual float cost() const = 0;
    virtual std::string description() const = 0;
};

class BeverageDecorator : public Beverage{
public:
    virtual float cost() const = 0;
    virtual std::string description() const = 0;
};

class Coffee: public Beverage {
public:
    float cost() const override{
        return 0.99f;
    }

    std::string description() const override{
        return "Basic Coffee";
    }
};

class Water: public Beverage {
    public:
    float cost() const override{
        return 0.50f;
    }

    std::string description() const override{
        return "Basic Water";
    }
};

class Milk :public BeverageDecorator{
public:
    Milk(Beverage& beverage): beverage(beverage) {}

    float cost() const override{
        return beverage.cost() + 0.20f;
    }

    std::string description() const override{
        return "Milk " + beverage.description();
    }

private:
    Beverage& beverage;
};

class Sugar :public BeverageDecorator{
public:
    Sugar(Beverage& beverage): beverage(beverage) {}

    float cost() const override{
        return beverage.cost() + 0.15f;
    }

    std::string description() const override{
        return "Sugar " + beverage.description();
    }

private:
    Beverage& beverage;
};

int main(){
    Coffee coffee;
    Water water;
    Milk coffeMilk = Milk(coffee);
    Sugar coffeSugar = Sugar(coffeMilk);
    Sugar extraSugar((Beverage&)coffeSugar);
    std::cout<<extraSugar.description()<<std::endl;
    return 0;
}