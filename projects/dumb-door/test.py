import uasyncio
from ioUtil import Stepper

mainMotor = Stepper([15, 14, 13, 12])

#while 1: print("1")

print("start")
uasyncio.run(mainMotor.move(100, 50))
print("end")

