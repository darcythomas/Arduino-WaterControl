#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif



#define MAXTIMINGS 85



class LEDLightSensor {
 private:
  uint8_t data[6];
  uint8_t _pin, _type;
  boolean read(void);
  unsigned long _lastreadtime;
  boolean firstreading;

 public:
  LEDLightSensor(uint8_t pin, uint8_t type);
  void begin(void);
  float readHumidity(void);

};
