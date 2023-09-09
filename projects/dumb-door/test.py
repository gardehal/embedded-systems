import uasyncio
from ioUtil import Stepper

mainMotor = Stepper([12, 13, 14, 15])

#while 1: print("1")

print("start")
uasyncio.run(mainMotor.move(100, 50))
print("end")

