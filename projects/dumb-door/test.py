import uasyncio
from ioUtil import Stepper, halfStepSequence

mainMotorPins = [12, 14, 13, 15]
mainMotorSequence = halfStepSequence
mainMotorMaxSteps = 400

mainMotor = Stepper(mainMotorPins, mainMotorSequence, mainMotorMaxSteps)

async def move():
    print("starting")
    await mainMotor.move(1100, 5)
    print("end")

#uasyncio.run(move())




from machine import Pin
from PiicoDev_LIS3DH import PiicoDev_LIS3DH
from PiicoDev_Unified import sleep_ms # cross-platform compatible sleep function

# From https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/pinouts :
# SDO - When in I2C mode, this pin can be used for address selection. When connected to GND or left open, the address is 0x18 - it can also be connected to 3.3V to set the address to 0x19
motion = PiicoDev_LIS3DH(bus = 1, sda = Pin(26), scl = Pin(27), address = 0x18)
motion.range = 4 # Set the range to +-2g

while True:
    x, y, z = motion.acceleration
    x = round(x,2) # round data for a nicer-looking print()
    y = round(y,2)
    z = round(z,2)
    myString = "X: " + str(x) + ", Y: " + str(y) + ", Z: " + str(z) # build a string of data
    #print(myString)
    if(x > 1):
        print("opened")
    else:
        print("not opened")

    sleep_ms(100)