#include <iostream>
#include <vector>
#include <memory>

class Observer{
public:
    virtual void notify(float, float) = 0;
};

class Displayer{
public:
    virtual void display() = 0;
};

class Subject{
public:
    virtual void update() = 0;
    virtual void addListener(std::shared_ptr<Observer>) = 0;
    virtual void removeListener(std::shared_ptr<Observer>) = 0;
};

class WeatherData : public Subject{
public:

    WeatherData(){}

    void update(){
        for(auto& it:listeners){
            it->notify(temp, humidity);
        }
    }

    void addListener(std::shared_ptr<Observer> l){
        listeners.push_back(l);
    }

    void removeListener(std::shared_ptr<Observer> l) {
        for(auto it = listeners.begin(); it != listeners.end(); it++){
            if(*it == l){
                listeners.erase(it);
                return;
            }
        }
    }

    float getTemp(){return temp;}

    float getHuidity(){return humidity;}

    void setData(float t, float h){
        temp = h;
        humidity = h;
        update();
    }

private:
    std::vector<std::shared_ptr<Observer>> listeners = std::vector<std::shared_ptr<Observer>>();
    float temp = 0.0f;
    float humidity = 0.0f;
};

class ValueDisplay : public Observer, Displayer{
public:

    ValueDisplay(Subject& subject): subject(subject){
        subject.addListener(std::make_shared<ValueDisplay>(*this));
    }

    void notify(float temp, float humidity){
        this->temp = temp;
        this->humidity = humidity;
        display();
    }

    void display(){
        std::cout<<"TEMP:"<<temp<<" HUMIDITY:"<<humidity<<std::endl;
    }

private:
    Subject& subject;
    float temp;
    float humidity;
};


class ValueDisplayPlus5 : public Observer, Displayer{
public:
    ValueDisplayPlus5(Subject& subject):subject(subject){
        subject.addListener(std::make_shared<ValueDisplayPlus5>(*this));
    }

    void notify(float temp, float humidity){
        this->temp = temp + 5;
        this->humidity = humidity + 5;
        display();
    }

    void display(){
        std::cout<<"TEMP PLUS 5:"<<temp<<" HUMIDITY PLUS 5:"<<humidity<<std::endl;
    }

private:
    Subject& subject;
    float temp;
    float humidity;
};

int main(){
    WeatherData data;
    ValueDisplay disp1(data);
    ValueDisplayPlus5 disp2(data);

    data.setData(5.2f, 78.0f);
    data.setData(25.0f, 64.0f);
    return 0;
}