#include "Adafruit_VL53L0X.h"
#include <SPI.h>

/*
Subject to MIT license.
Sensor code inspired by https://github.com/adafruit/Adafruit_VL53L0X/tree/master/examples/vl53l0x_dual
but rewritten from scratch:
1. Uses SPI,
2. removed redundant code,
2. returns scaled byte for distance,
3. handles up to 8 sensors,
4. returns error values for invalid sensor, invalid reading,


SPI slave code adapted from http://www.gammon.com.au/spi
*/

const byte MAX_OK = 253; // largest acceptable range / 2
const byte NO_SUCH_SENSOR = 255;
const byte INVALID_READING = 254;
const int SENSORS = 2; // two sensors for now
// addresses we will assign to sensors
byte address[SENSORS];
// pins to shutdown
byte shutdown_pin[SENSORS];
// scaled distances
byte distance[SENSORS];

// create array of sensors
Adafruit_VL53L0X lox[SENSORS];
VL53L0X_RangingMeasurementData_t measure;

// for debugging
volatile byte spi_in, spi_out;
char buffer[10];

void setID() {

  int i;
  for (i=0; i < SENSORS; i++) {
    shutdown_pin[i] = i + 2; // pins go from 2 to SENSORS + 2
    address[i] = (byte) 0x30 + i; // addresses go from 0x30 to 0x37
    pinMode(shutdown_pin[i], OUTPUT);
    digitalWrite(shutdown_pin[i], LOW);
  }
  delay(10);
  for (i=0; i < SENSORS; i++) {
    digitalWrite(shutdown_pin[i], HIGH);
    delay(10);
    bool result = lox[i].begin(address[i]);
    if(!result) {
      while(1);  // loop forever if the setup didn't work
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

  }
}

void setup() {
  Serial.begin(9600);
  Serial.println('starting');
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
spi_in = c;
spi_out = c < SENSORS ? distance[c] : NO_SUCH_SENSOR; // return scaled distance or error code
SPDR = spi_out;
}  // end of interrupt routine SPI_STC_vect


void loop() {
  readSensors();
  sprintf(buffer, "%u,%u,%u,%u", spi_in, spi_out, distance[0], distance[1]);
  Serial.println(buffer);
  delay(100); // read all sensors every 1/10 second
}
