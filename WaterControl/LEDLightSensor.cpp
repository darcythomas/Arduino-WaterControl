


#include "LEDLightSensor.h"
#include <Time.h>
#include <TimeAlarms.h>

LEDLightSensor::LEDLightSensor(uint8_t anode, uint8_t cathode) {
  _anode = anode;
  _cathode = cathode;
  firstreading = true;
}

void LEDLightSensor::begin(void) {
  // set up the pins!
  pinMode(_anode, INPUT);
  pinMode(_cathode, INPUT);
  digitalWrite(_anode, HIGH);
  digitalWrite(_cathode, HIGH);
  _lastreadtime = 0;
}

float LEDLightSensor::readBrightness(void) {
  float f;
  int j;
  begin();
  
    pinMode(_cathode,INPUT);
  digitalWrite(_cathode,LOW);  // turn off internal pull-up resistor
  
  for ( j = 0; j < 30000; j++) {
    if ( digitalRead(_cathode)==0) break;
    
  delayMicroseconds(4000);
  }
  
  return 30000.0-j;
  if(read())
  {
  f= 1.0;
      return f;
    
  }
  Serial.print("Read fail");
  return NAN;
}


boolean LEDLightSensor::read(void) {
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;
  unsigned long currenttime;

  // pull the pin high and wait 250 milliseconds
  digitalWrite(_cathode, HIGH);
  Alarm.delay(250);

  currenttime = millis();
  if (currenttime < _lastreadtime) {
    // ie there was a rollover
    _lastreadtime = 0;
  }
  if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
    return true; // return last correct measurement
    //Alarm.delay(2000 - (currenttime - _lastreadtime));
  }
  firstreading = false;
  /*
    Serial.print("Currtime: "); Serial.print(currenttime);
    Serial.print(" Lasttime: "); Serial.print(_lastreadtime);
  */
  _lastreadtime = millis();

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  
  // now pull it low for ~20 milliseconds
  pinMode(_cathode, OUTPUT);
  digitalWrite(_cathode, LOW);
  Alarm.delay(20);
  //cli();
  digitalWrite(_cathode, HIGH);
  delayMicroseconds(40);
  pinMode(_cathode, INPUT);

  // read in timings
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (digitalRead(_cathode) == laststate) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    laststate = digitalRead(_cathode);

    if (counter == 255) break;

    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      data[j/8] <<= 1;
      if (counter > 6)
        data[j/8] |= 1;
      j++;
    }

  }

  sei();
  
  /*
  Serial.println(j, DEC);
  Serial.print(data[0], HEX); Serial.print(", ");
  Serial.print(data[1], HEX); Serial.print(", ");
  Serial.print(data[2], HEX); Serial.print(", ");
  Serial.print(data[3], HEX); Serial.print(", ");
  Serial.print(data[4], HEX); Serial.print(" =? ");
  Serial.println(data[0] + data[1] + data[2] + data[3], HEX);
  */

  // check we read 40 bits and that the checksum matches
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }
  

  return false;

}
