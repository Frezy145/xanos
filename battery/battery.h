
#ifndef BATTERY_H
#define BATTERY_H

class Battery {

public:
    Battery(int pin);

    float readVoltage(){};
    int getPercentage(){}; 

private:
    int _pin;
};

#endif