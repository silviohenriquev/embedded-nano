#include "sensors.h"

float temp=0;
const float resolution = 5.0/1023;
//pega um valor de tensao, por exemplo leu 5v
// agora a gente vai multiplicar 5V vezes

IRRADSens::IRRADSens(uint8_t pin){
    this->_pin = pin;
}

void IRRADSens::begin(){
    pinMode(this->_pin, INPUT);
}

void IRRADSens::updateIrrad(){

    this->_irrad =((analogRead(this->_pin))*5000/(1023*0.1154));
    
}

float IRRADSens::getIrrad(){
    this->updateIrrad();
    return this->_irrad;
}

void IRRADSens::printIrrad(float irrad){
    Serial.print("Irradiancia: ");
    Serial.print((int)this->_irrad);
    Serial.println(" W/m2");
}

void IRRADSens::printPin(){
    Serial.println(this->_pin);
}


LM35::LM35(uint8_t pin){
    this->_pin = pin;
}

void LM35::begin(){
    pinMode(this->_pin, INPUT);
}

void LM35::updateTemp(){
    temp=(analogRead(this->_pin)*resolution)/0.01;
    this->_temp = temp;
}

float LM35::getTemp(){
    this->updateTemp();
    return this->_temp;
}

void LM35::printTemp(float temp){
    Serial.print("Temperatura: ");
    Serial.println(temp);
}

void LM35::printPin(){
    Serial.println(this->_pin);
}