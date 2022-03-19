#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "ports.h"

class LM35
{
public:
    LM35(uint8_t pin);
    float getTemp();
    void begin();
    void printTemp(float temp);
    void printPin();
private:
    float _temp;
    void updateTemp();
    uint8_t _pin;
};

class IRRADSens
{
public:
    IRRADSens(uint8_t pin);
    float getIrrad();
    void begin();
    void printIrrad(float irrad);
    void printPin();
private:
    float _irrad;
    void updateIrrad();
    uint8_t _pin;
};

#endif // LoRa_COMM
