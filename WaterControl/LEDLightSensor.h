#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Time.h>
#include <TimeAlarms.h>

#define MAXTIMINGS 85



class LEDLightSensor {
 private:
  uint8_t data[6];
  uint8_t _anode, _cathode;
  boolean read(void);
  unsigned long _lastreadtime;
  boolean firstreading;
  void charge(void);

 public:
  LEDLightSensor(uint8_t anode, uint8_t cathode);
  void begin(void);
  float readBrightness(void);

};
