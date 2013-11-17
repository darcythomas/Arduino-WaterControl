#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class ConductivitySensor {
 private: 
  uint8_t _pin;


 public:
  ConductivitySensor(uint8_t pin);
  float readConductivity(void);

};
