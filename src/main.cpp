#include <Arduino.h>
#include "ports.h"
#include <LoRaE220Communication.h>
#include <sensors.h>
#include <rtc.h>

LoRaE220Communication lora(e220_TX, e220_RX, e220_AUX, e220_M0, e220_M1, DeviceFunction::sensor);   
RealTimeClock rtc;
LM35 sensorTemp1(lm35_1);
LM35 sensorTemp2(lm35_2);
SensorData sensorData;

void updateSensorData();

void setup(){
    Serial.begin(9600);
    delay(100);

 	lora.setup();
    lora.printParameters();
    sensorTemp1.begin();
    sensorTemp2.begin();
    rtc.begin();
    rtc.adjust();

}

void loop(){
    updateSensorData();
    lora.printSensorsData(sensorData);
	//lora.sendSensorsDataPacket(sensorData);
    delay(1000);
}

void setSensorData(){
    sensorData.id = 1;
    sensorData.tempCell = 37.1;
    sensorData.tempExternal = 34.7;
    sensorData.tempInternal = 32.2;
    sensorData.irradiance = 750;
    sensorData.date = 1647555749;
}

void updateSensorData(){
    sensorData.id = 1;
    sensorData.tempCell=sensorTemp1.getTemp();
    sensorData.tempExternal=sensorTemp2.getTemp();
    sensorData.tempInternal = rtc.getTemperature();
    sensorData.date = rtc.getDate().unixtime();
    //sensorData.date = 1647555749;
    sensorData.irradiance = 750;
}