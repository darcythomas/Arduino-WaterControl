

#include "ConductivitySensor.h"
#include <Time.h>
#include <TimeAlarms.h>

ConductivitySensor::ConductivitySensor(uint8_t pin) {
  _pin = pin; 
  _powerPin = -1;
  // set up the pins!
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
}

ConductivitySensor::ConductivitySensor(uint8_t pin, uint8_t powerPin) {
  _pin = pin; 
  _powerPin = powerPin;
  // set up the pins!
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
  pinMode(_powerPin, OUTPUT);
  digitalWrite(_pin, HIGH);
}


float ConductivitySensor::readConductivity(void) {
  
  //this is conserve energy and reduce galvanic damage to sensors
  if(_powerPin >0)
  {
    digitalWrite(_powerPin, HIGH);
    Alarm.delay(20);//give time to stablise
  }

  int reading = analogRead(_pin); 

  if(_powerPin >0){      
    digitalWrite(_powerPin, HIGH);  
  }

  return (reading/1023.0) * 1000.0;//return normalised result
}



