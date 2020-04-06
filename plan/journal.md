# Project journal for multi-VL53L0X

I'm experimenting to see how easy it is to connect multiple VL53L0X sensors to a Pi, Nano or Adafruit feather.

I have two approaches in mind:

1. Use an I2C multiplexer
1. Use an Arduino SPI slave that selectively enables the chips and gives each a unique I2C address


## Saturday 04 April 2020

I successfully ran the multiplexer on an Adafruit CircuitPython board and a veteran Raspberry Pi a couple of days ago.

I'm currently working thorough a series of steps towards the SPI slave solution.

More info on my [blog](https://blog.rareschool.com/).

Code is here.

## Sunday 05 April 2020

Time to tidy up and extend the code.

I want to use iteration and arrays to support 1-8 sensors.

## Monday 06 April 2020

New code is working.