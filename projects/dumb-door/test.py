import uasyncio
from ioUtil import Stepper

mainMotor = Stepper([12, 14, 13, 15])

#while 1: print("1")

print("start")
uasyncio.run(mainMotor.move(11, 50))
#uasyncio.run(mainMotor.moveDegrees(-45, 50))
print("end")
mainMotor.deInit()

