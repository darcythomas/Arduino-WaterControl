

#include "Pump.h"

Pump::Pump(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4 ) {
  _pin1 = pin1; 
  _pin2 = pin2; 
  _pin3 = pin3; 
  _pin4 = pin4; 

}

void Pump::begin(void) {
  // set up the pins!
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);
  digitalWrite(_pin1,LOW);
  digitalWrite(_pin2,LOW); 
  digitalWrite(_pin3,LOW);
  digitalWrite(_pin4,LOW);
}

void Pump::pumpOn(void) {
 
  digitalWrite(_pin3,HIGH);
  digitalWrite(_pin4,HIGH); 
  
}
void Pump::pumpOff(void) {
  digitalWrite(_pin3,LOW);
  digitalWrite(_pin4,LOW); 
}
boolean Pump::isPumpOn(void) {
 return digitalRead(_pin3) || digitalRead(_pin4);
}




