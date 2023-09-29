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




from machine import Pin, I2C, SoftI2C
from PiicoDev_LIS3DH import PiicoDev_LIS3DH
from PiicoDev_Unified import sleep_ms # cross-platform compatible sleep function

devices = i.scan()
if len(devices) == 0:
    print("No i2c device !")
else:
    print('i2c devices found:',len(devices))

for device in devices:
    print("Decimal address: ",device," | Hexa address: ",hex(device))

# From https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/pinouts :
# SDO - When in I2C mode, this pin can be used for address selection. When connected to GND or left open, the address is 0x18 - it can also be connected to 3.3V to set the address to 0x19
motion = PiicoDev_LIS3DH(bus = 1, sda = Pin(26), scl = Pin(27), address = 0x18)

while True:
    x, y, z = motion.angle # Tilt could be measured with respect to three different axes
    print("Angle: {:.0f}°".format(y)) # Print the angle of rotation around the y-axis
    sleep_ms(50)