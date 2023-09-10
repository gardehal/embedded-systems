import uasyncio
from ioUtil import Stepper

mainMotor = Stepper([12, 14, 13, 15])
s1 = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1],
    ]
s2 = [
    [1, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1],
    ]

s3 = mainMotor.fullStepSequenceDouble
s4 = mainMotor.fullStepSequenceSingle[::-1]
mainMotor.stepSequence = s2

#while 1: print("1")

print("start")
uasyncio.run(mainMotor.move(11, 150))
print("end")
mainMotor.deInit()

