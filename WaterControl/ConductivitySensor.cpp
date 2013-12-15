

#include "ConductivitySensor.h"

ConductivitySensor::ConductivitySensor(uint8_t pin) {
  _pin = pin; 
    // set up the pins!
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
}


float ConductivitySensor::readConductivity(void) {
  //TODO turn sensor on and off (will require hardware change)
  //this is conserve energy and reduce galvanic damage to sensors
  int reading = analogRead(_pin); 
   return (reading/1023.0) * 1000.0;//return normalised result
}


