#include "Adafruit_VL53L0X.h"
#include <SPI.h>

const byte MAX_OK = 253; // largest acceptable range / 2
const byte NO_SUCH_SENSOR = 255;
const byte INVALID_READING = 254;
const int SENSORS = 2; // two sensors for now
// addresses we will assign
byte address[SENSORS];
// set the pins to shutdown
byte shutdown_pin[SENSORS];
byte distance[SENSORS];

Adafruit_VL53L0X lox[SENSORS];
VL53L0X_RangingMeasurementData_t measure;

void setAllPins(int state) {
  for (int i=0; i < SENSORS; i++) {
    digitalWrite(shutdown_pin[i], state);
  }
}

void setID() {
  // all reset
 // Serial.println("setting resest pins low");
  int i;
  for (i=0; i < SENSORS; i++) {
    shutdown_pin[i] = i + 2; // pins go from 2 to SENSORS + 2
    address[i] = (byte) 0x30 + i; // addresses go from 0x30 to 0x37
    pinMode(shutdown_pin[i], OUTPUT);
    digitalWrite(shutdown_pin[i], LOW);
  }
  delay(10);
  // Serial.println("starting set up");
  for (i=0; i < SENSORS; i++) {
    digitalWrite(shutdown_pin[i], HIGH);
    delay(10);
    bool result = lox[i].begin(address[i]);
    if(!result) {
     // while(1);  // loop forever if the setup didn't work
      }
  }
  delay(10);
}

void readSensors() {
  for (int i=0; i < SENSORS; i++) {
    float range;
    lox[1].rangingTest(&measure, false);
    if (measure.RangeStatus != 4) {
      range = measure.RangeMilliMeter;
      distance[i] = min(range / 2, MAX_OK);
    } else {
      distance[i] = INVALID_READING;
    }
    /*
  Serial.print(i);
  Serial.print(" = ");
  Serial.print(range);
  Serial.print(' ');
  Serial.println(distance[i]);
  */
  }
}
  


void setup() {
  Serial.begin(9600);++++++
   // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  setID();
  SPI.attachInterrupt();
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register
SPDR = c < SENSORS ? distance[c] : NO_SUCH_SENSOR;
}  // end of interrupt routine SPI_STC_vect




void loop() {
  readSensors();
  delay(100);
}
