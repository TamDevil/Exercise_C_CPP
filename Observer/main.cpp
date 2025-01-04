

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Observer{
    public:
    virtual void update(int speed, float temperature) = 0;
};

class Engine{
    private:
    int EngineSpeed = 0;
    float EngineTemperature = 35;
    vector<Observer*> observers;
    public:
    void addObserver(Observer* observer){
        observers.push_back(observer);
    }
    void removeObserver(Observer* observer){
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notifyObservers(){
        for(auto observer : observers){
            observer->update(EngineSpeed, EngineTemperature);
        }
    }
    void setEngineState(int speed, float temperature){
        EngineSpeed = speed;
        EngineTemperature = temperature;
        notifyObservers();
    }
    void getState();
};

class CoolingSystem : public Observer{
    public:
    void update(int speed, float temperature){
    cout << "Trạng thái quạt làm mát: " << (temperature > 90 ? "Bật" : "Tắt") << endl;
}
};

class WarningSystem : public Observer{
    public: 
    void update(int speed, float temperature){
        if (speed > 6000 && temperature > 100)
        {
            cout << "Kích hoạt cảnh báo!" << endl;
        }
        
    }
};

class EngineControlUnit : public Observer{
    private:
    float Performance = 0;
    float Fuel = 0;
    public:
    void update(int speed, float temperature){
        Performance = 95 - temperature/5;
        Fuel = speed / 60 ;
        cout << "Performance: " << Performance << ", Fuel: " << Fuel << endl;
    }

};

int main(int argc, char const *argv[])
{
    CoolingSystem Cool;
    WarningSystem Warning;
    EngineControlUnit ECU;
    Engine subject;
    subject.addObserver(&Cool);
    subject.addObserver(&Warning);
    subject.addObserver(&ECU);
    subject.setEngineState(6000, 100);

    return 0;
}
