#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif



#define MAXTIMINGS 85



class Pump {
 private:
  boolean pump;
  uint8_t _pin1, _pin2, _pin3, _pin4, ;
 

 public:
  Pump(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
  void begin(void);
  void pumpOn(void);
  void pumpOff(void);
  boolean isPumpOn(void);

};
