#include "Controler.h"
#include <Time.h>
#include <TimeAlarms.h>

#define PumpPinA 4  
#define PumpPinB 5  
#define PumpPinC 6  
#define PumpPinD 7  

#define DHTPIN 9     //  pin temp/humidity sensor is connected to
#define DHTTYPE DHT11 

#define SoilDataPin 2
#define SoilPowerPin 13
#define WaterDataPin 3
#define WaterPowerPin 11

#define LightSensorAnode 2
#define LightSensorCathode 3

unsigned long Interval = 1840909;//((1000 * 3000) * 1);  //440 times over 15 days

boolean IsSoilDry();
boolean IsThereWater();
boolean IsItDayTime();




boolean HasEnoughTimeElapsed();

int RunPumpForMilliSec();
boolean PumpShouldRun();
float ReadHumidity(void);
float ReadTemperature(void);
float SoilConductivity(void);
float WaterConductivity(void);

void  RunPump(unsigned long);
unsigned long  PeriodToRunPumpFor();

void CheckAndRunPump(void);



ConductivitySensor::ConductivitySensor _soilSensor(SoilDataPin, SoilDataPin);
ConductivitySensor::ConductivitySensor _waterSensor(WaterDataPin, WaterPowerPin);
LEDLightSensor _lightsensor(LightSensorAnode,LightSensorCathode);
DHT::DHT _dht(DHTPIN,DHTTYPE);
Pump _pump(PumpPinA, PumpPinB, PumpPinC, PumpPinD);


Controler::Controler() {

}


boolean Controler::PumpShouldRun(void) {

  //if last water was not pumped too recently (vary on humidity+temp?)
  if(!HasEnoughTimeElapsed())
  {
   // Serial.println("It's way too soon to be pumping!");
    return false;
  }
  //if day |light sensor
  if(!IsItDayTime())
  {
    Serial.println("It's way too dark outside to be pumping!");
    return false;
  }

  //if water level ok
  if(!IsThereWater())
  {
    Serial.println("It's no water to be pumping!");      
    return false;
  }

  //if soil is dry
  if(!IsSoilDry())
  {
    Serial.println("It's way too damp to be pumping!");
    return false;
  }

  return true;
}


boolean Controler::HasEnoughTimeElapsed()
{
  //return true;
  unsigned long currentMillis = millis(); 
  if(currentMillis - _pumpLastRanAt > Interval   ) {   
   
    Serial.print("Time: ");
  Serial.println(  now()); 
  
    _pumpLastRanAt = currentMillis;
    Serial.print("_pumpLastRanAt ");
    Serial.println(_pumpLastRanAt);   
    Serial.print("interval ");
    Serial.println(Interval);

    return true;
  } 
  return false;
}

boolean Controler::IsThereWater()
{ 
  float threshold = 0;
  float conductivity = WaterConductivity();

  return conductivity >  threshold;   
}

boolean Controler::IsItDayTime()
{
  return true;
}
boolean Controler::IsSoilDry()
{
  float threshold = 500;
  float soilConductivity = SoilConductivity();

  return soilConductivity <  threshold;   
}


float Controler::ReadLuminosity()
{
  return _lightsensor.readBrightness();
}

float Controler::ReadHumidity()
{
  return _dht.readHumidity();
}

float Controler::ReadTemperature()
{
  return _dht.readTemperature();
}

float Controler::SoilConductivity()
{
  return _soilSensor.readConductivity();
}

float Controler::WaterConductivity()
{
  return _waterSensor.readConductivity();
}

void  Controler::RunPump(unsigned long period)
{
  _pump.pumpOn();
  Alarm.delay(period);
   _pumpLastRanAt = millis();
  _pump.pumpOff();
  
}


unsigned long  Controler::PeriodToRunPumpFor(){
  //adjust based on temp/humidity
  return 5000;
}

void Controler::CheckAndRunPump()
{
  boolean pumpNeedsToRun = PumpShouldRun();
  if(pumpNeedsToRun)
  {
    unsigned long pumpForMilliSec = PeriodToRunPumpFor();
    RunPump(pumpForMilliSec);
  } 

}

