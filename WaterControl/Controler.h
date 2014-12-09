#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include "ConductivitySensor.h"
#include "LEDLightSensor.h"
#include "DHT.h"
#include "Pump.h"

class Controler {
private: 
  uint8_t _pin;

  unsigned long  _pumpLastRanAt;
  boolean IsSoilDry();
  boolean IsThereWater();
  boolean IsItDayTime();

  boolean HasEnoughTimeElapsed();







public:
  Controler();
  boolean PumpShouldRun(void);  
  float ReadHumidity(void);
  float ReadTemperature(void);
  float SoilConductivity(void);
  float WaterConductivity(void);

  void  RunPump(unsigned long);
  unsigned long  PeriodToRunPumpFor();

  void CheckAndRunPump(void);
};



