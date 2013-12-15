
#include "DHT.h"
#include "ConductivitySensor.h"
#include "Pump.h"


long previousMillis = 0;       
long interval = 1000;    


#define PumpPinA 4  
#define PumpPinB 5  
#define PumpPinC 6  
#define PumpPinD 7  


#define DHTPIN 9     // what pin we're connected to

#define SoilPin 2
#define WaterPin 3

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
ConductivitySensor SoilSensor(SoilPin);
ConductivitySensor LevelSensor(WaterPin);

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
}

void loop() {  
   unsigned long currentMillis = millis(); 
   if(currentMillis - previousMillis > interval) {    
      previousMillis = currentMillis;
      printOut();
  }  
}
boolean turnOnPump()
{
  //if day |light sensor
  //if last water was not pumped too recently (vary on humidity+temp?)
  //if water level ok
  //if soil is dry
}

void printOut()
{
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float s = SoilSensor.readConductivity();
  float l = LevelSensor.readConductivity();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } 
  else {
    Serial.print("Humidity: "); 
    Serial.print(h);    
    Serial.println(" %");
 
      
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
       
    Serial.print("Level conductivity: "); 
    Serial.println(l);
   
 
    
    Serial.print("Soil conducivity: "); 
    Serial.print(s);
    Serial.print("\r\n");
    Serial.print("\r\n");
     
    
  }
  
}


