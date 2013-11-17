

#include "ConductivitySensor.h"

ConductivitySensor::ConductivitySensor(uint8_t pin) {
  _pin = pin; 
    // set up the pins!
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
}


float ConductivitySensor::readConductivity(void) {
  int reading = analogRead(_pin); 
   return (reading/1023.0) * 1000.0;
}


