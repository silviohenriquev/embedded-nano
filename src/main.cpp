#include <Arduino.h>
#include "ports.h"
#include <LoRaE220Communication.h>
#include <sensors.h>
#include <rtc.h>
#include <Adafruit_ADS1X15.h>

#define TIME 30

LoRaE220Communication lora(e220_TX, e220_RX, e220_AUX, e220_M0, e220_M1, DeviceFunction::sensor);   
RealTimeClock rtc;
Adafruit_ADS1115 ads;
LM35 sensorTemp1(lm35_1);
//LM35 sensorTemp2(lm35_2);
SensorData lastSensorData;
SensorData sensorData;

void updateSensorData();
void setSensorData();
void clearSensorData();
void data();

int count;
const float x = 5.0/1023;

void setup(){
    Serial.begin(9600);
    delay(100);

    lora.setup();
    lora.printParameters();
    rtc.begin();
    ads.setGain(GAIN_SIXTEEN);
    ads.begin();
    sensorTemp1.begin();

    //sensorTemp2.begin();
}

void loop(){
    data();
	lora.sendSensorsDataPacket(sensorData);
    rtc.printDate(sensorData.date);
    lora.blink(1000);
}


void setSensorData(){
    sensorData.id = 1;
    sensorData.tempCell = 37.1;
    sensorData.tempExternal = 34.7;
    sensorData.tempInternal = 32.2;
    sensorData.irradiance = 750;
    sensorData.date = 1647555749;
}

void clearSensorData(){
    sensorData.tempCell = 0;
    sensorData.tempExternal = 0;
    sensorData.tempInternal = 0;
    sensorData.irradiance = 0;
    sensorData.date = 0;
}

void updateSensorData(){
    sensorData.id = 1;
    lastSensorData.tempCell=sensorTemp1.getTemp();
    //lastSensorData.tempCell = 0;
    //lastSensorData.tempExternal=sensorTemp2.getTemp();
    lastSensorData.tempExternal = 0;
    lastSensorData.tempInternal = rtc.getTemperature();
    //lastSensorData.date = rtc.getDate().unixtime();
    lastSensorData.irradiance = (((ads.readADC_SingleEnded(0)*0.0078125)/1000)*8292.215)-0.6454468;
}

void data(){
    clearSensorData();
    for(count=0; count<TIME; count++){
        //Serial.println(count);
        updateSensorData();
        sensorData.tempCell += lastSensorData.tempCell;
        sensorData.tempExternal += lastSensorData.tempExternal;
        sensorData.tempInternal += lastSensorData.tempInternal;
        sensorData.irradiance += lastSensorData.irradiance;
        if(count != (TIME-1)){
            delay(1000);
        }
        // Serial.print(lastSensorData.id);
        // Serial.print("   |   ");
        // Serial.print(lastSensorData.irradiance);
        // Serial.print("   |   ");
        // Serial.print(lastSensorData.tempCell);
        // Serial.print("   |   ");
        // Serial.print(lastSensorData.tempExternal);
        // Serial.print("   |   ");
        // Serial.println(lastSensorData.tempInternal);
    }
    sensorData.id = 1;
    sensorData.tempCell = (sensorData.tempCell)/TIME;
    sensorData.tempExternal = (sensorData.tempExternal)/TIME;
    sensorData.tempInternal = (sensorData.tempInternal)/TIME;
    sensorData.irradiance = (sensorData.irradiance)/TIME;
    sensorData.date = rtc.getDate().unixtime();

    // Serial.print(sensorData.id);
    // Serial.print("   |   ");
    // Serial.print(sensorData.irradiance);
    // Serial.print("   |   ");
    // Serial.print(sensorData.tempCell);
    // Serial.print("   |   ");
    // Serial.print(sensorData.tempExternal);
    // Serial.print("   |   ");
    // Serial.print(sensorData.tempInternal);
    // Serial.print("   |   ");
    // rtc.printDate(sensorData.date);
}