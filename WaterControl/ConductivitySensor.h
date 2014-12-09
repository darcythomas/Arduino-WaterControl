#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class ConductivitySensor {
 private: 
  uint8_t _pin;
  uint8_t _powerPin;


 public:
  ConductivitySensor(uint8_t pin);
  ConductivitySensor(uint8_t pin, uint8_t powerPin);
  float readConductivity(void);

};
