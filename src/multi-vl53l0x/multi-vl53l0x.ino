#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox;

void setup() {
  Wire.begin();
  tcaselect(0x29);
  lox = Adafruit_VL53L0X();
  Serial.begin(9600);
  

}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  
  Serial.print("Reading a measurement... ");
  
  lox.rangingTest(&measure, true); // pass in 'true' to get debug data printout!
  /*
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
   
  }
  */
  delay(100);
  

}

    #define TCAADDR 0x70
     
    void tcaselect(uint8_t i) {
      if (i > 7) return;
     
      Wire.beginTransmission(TCAADDR);
      Wire.write(1 << i);
      Wire.endTransmission();  
    }
