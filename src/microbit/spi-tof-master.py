from microbit import *
import struct
from time import sleep

SENSORS = 2

def spi_read(sensor):
    pin16.write_digital(0)  # Chip select
    ibuffer = struct.pack('<B', sensor)
    spi.write(ibuffer)
    result = spi.read(1)
    pin16.write_digital(1)  # Chip select off
    return result

spi.init(baudrate=100000)
while True:
    for i in [0, 1]:
        print(i, ord(spi_read(i)))
        sleep(0.1)