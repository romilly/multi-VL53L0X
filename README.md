I'm experimenting to see how easy it is to connect multiple VL53L0X sensors to a Pi, Nano or Adafruit feather.

I have two approaches in mind:

1. Use an I2C multiplexer
1. Use an Arduino SPI slave that selectively enables the chips and gives each a unique I2C address

Day-by-day progress is detailed in the [Journal](plan/journal.md)

My code is subject to the MIT license.

Adafruit code is subject to the same license.

Nick Gammon's code is subject to the  [Creative Commons Attribution 3.0 Australia License](https://creativecommons.org/licenses/by/3.0/au/)