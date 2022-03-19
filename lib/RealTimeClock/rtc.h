#ifndef RTC_H
#define RTC_H

#include <Arduino.h>
#include <SPI.h>
#include <RTClib.h>
#include <Adafruit_I2CDevice.h>

class RealTimeClock
{
public: 
    // Class constructor
    void begin();
    void adjust();
    float getTemperature();
    DateTime getDate();
    void printDate(DateTime now);

private:
    RTC_DS3231 _rtc;

private:
    DateTime _now;
    float _temperature;
    void _updateDate();


};


#endif // LoRa_COMM