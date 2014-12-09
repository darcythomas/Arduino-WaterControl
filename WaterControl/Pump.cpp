

#include "Pump.h"

Pump::Pump(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4 ) {
  _pin1 = pin1; 
  _pin2 = pin2; 
  _pin3 = pin3; 
  _pin4 = pin4; 
  
//    pinMode(_pin1, OUTPUT);
//  pinMode(_pin2, OUTPUT);
//  pinMode(_pin3, OUTPUT);
//  pinMode(_pin4, OUTPUT);
//  digitalWrite(_pin1,LOW);
//  digitalWrite(_pin2,LOW); 
//  digitalWrite(_pin3,LOW);
//  digitalWrite(_pin4,LOW);



    
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    digitalWrite(6,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(7,LOW);

  
  pinMode(10, OUTPUT);
  
  digitalWrite(10,LOW);


}


void Pump::pumpOn(void) {
 
  
  Serial.println("Pump turned on"); 
    
   
  digitalWrite(10,HIGH);
    digitalWrite( 5,HIGH);
    digitalWrite( 6,HIGH); 
  
}
void Pump::pumpOff(void) {
  
  digitalWrite(10,LOW);
  
  digitalWrite(5,LOW);
  digitalWrite(6,LOW); 
  digitalWrite(7,LOW);
  digitalWrite(4,LOW);   
  Serial.println("Pump turned off"); 
}
boolean Pump::isPumpOn(void) {
 return digitalRead(_pin2) || digitalRead(_pin3);
}




