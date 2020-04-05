// Adapted from from http://www.gammon.com.au/spi


#include <SPI.h>

void setup (void)
{

  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  Serial.begin (9600);
  Serial.println("Starting...");

}  // end of setup


void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

  // send request
  for (int i=0; i < 2; i++) {
    int result;
    c = i & 0x01;
    result = SPI.transfer (c);
    Serial.print(i);
    Serial.print('=');
    Serial.println(result);

  }

  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (1000);  // 1 seconds delay
}  // end of loop
