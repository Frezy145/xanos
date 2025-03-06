#include "battery.h" 

Battery::Battery(int pin) : _pin(pin) {
    
    Battery::readVoltage();
    Battery::getPercentage();
}