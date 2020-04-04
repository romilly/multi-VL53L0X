"""
This example shows how to use two VL53L0X sensors attached to TCA9548A channels 0 and 1.

lightly adapted from the Adafruit example at
https://circuitpython.readthedocs.io/projects/tca9548a/en/latest/
and the VL53L0X driver example at
https://circuitpython.readthedocs.io/projects/vl53l0x/en/latest/
"""

import time
import board
import busio
import adafruit_tca9548a
import adafruit_vl53l0x

# Create I2C bus as normal
i2c = busio.I2C(board.SCL, board.SDA)

# Create the TCA9548A object and give it the I2C bus
tca = adafruit_tca9548a.TCA9548A(i2c)

# For each sensor, create it using the TCA9548A channel instead of the I2C object
tof0 = adafruit_vl53l0x.VL53L0X(tca[0])
tof1 = adafruit_vl53l0x.VL53L0X(tca[1])

# Main loop will read the range and print it every second.
while True:
    print("Range for tof0: {0}mm".format(tof0.range))
    print("Range for tof1: {0}mm".format(tof1.range))
    time.sleep(1.0)