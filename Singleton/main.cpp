#include <iostream>

using namespace std;

void isOverheating(){
    cout << "Động cơ đang quá nhiệt!" << endl;
}

class EngineControlUnit{
    private:
    static EngineControlUnit *Instance;
    int EngineSpeed = 0;
    float EngineTemperature = 35;
    EngineControlUnit(){}
    public:

    static EngineControlUnit *getInstance(){
        if (!Instance)
        {
            Instance = new EngineControlUnit();
        }
            return Instance;
        
    }
    void setEngineSpeed(int speed){
    if (speed >= 0 && speed <= 6000)
    {
        EngineSpeed = speed;
    }else{
        cout << "Tốc độ động cơ không hợp lệ!" << endl;
    }

}
    int getEngineSpeed(){
    return EngineSpeed;            
    }

    void setEngineTemperature(float temperature){
        if (temperature >= - 20 && temperature <= 120)
        {
            EngineTemperature = temperature;
        }else{
            cout << "Nhiệt độ động cơ không hợp lệ!" << endl;
        }
        
    }
    float getEngineTemperature(){
        return EngineTemperature;
    }

    void diagnostics(){
        cout << "Tốc độ động cơ: " << getEngineSpeed() <<" RPM" << endl;
        cout << "nhiệt độ động cơ: " << getEngineTemperature() <<" Celsius" << endl;
        if (getEngineTemperature() > 100)
        {
            isOverheating();
        }
        
    }    

};

EngineControlUnit *EngineControlUnit::Instance = nullptr;

int main(int argc, char const *argv[])
{
    EngineControlUnit *ECU = EngineControlUnit::getInstance();
    ECU->setEngineSpeed(10000);
    ECU->setEngineTemperature(120);
    ECU->diagnostics();
    return 0;
}
