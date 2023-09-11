import uasyncio
import utime
from machine import Pin

class Stepper:
    
    pins = []
    stepperFullRotationSteps = 0
    stepSequence = []
    stepIndex = 0 # NB: Always update stepIndex when setting stepSequence
    fullStepSequence = [
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1],]
    fullStepSequenceDouble = [
        [1, 1, 0, 0],
        [0, 1, 1, 0],
        [0, 0, 1, 1],
        [1, 0, 0, 1],]
    halfStepSequence = [
        [1, 0, 0, 0],
        [1, 1, 0, 0],
        [0, 1, 0, 0],
        [0, 1, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 1],
        [0, 0, 0, 1],
        [1, 0, 0, 1],]
        
    def __init__(self, motorPins: list, stepSequence: list = halfStepSequence, stepperMotorStepDegree: float = 1.8):
        # Init Stepper class, setting pins, step sequence.
        
        self.pins = [Pin(motorPins[0], Pin.OUT),
                         Pin(motorPins[1], Pin.OUT),
                         Pin(motorPins[2], Pin.OUT),
                         Pin(motorPins[3], Pin.OUT)]
        
        self.stepperFullRotationSteps = 360 / stepperMotorStepDegree
        self.stepIndex = 0
        self.stepSequence = stepSequence
        self.deInit()
    
    def deInit(self) -> bool:
        # De-init/disable powers to the pins.
        
        for pin in self.pins:
            pin.value(0)
            
        return True
    
    def brake(self) -> bool:
        # Initiates all coils, allowing shaft to spin, but with slight resistance. Maybe cause funky power generation.
        
        for pin in self.pins:
            pin.value(1)
        
        return True
    
    def lock(self) -> bool:
        # Powers half the pins, effectivly "locking" shaft in place.
        
        for i, pin in enumerate(self.pins):
            if(i % 2):
                pin.value(1)
            else:
                pin.value(0)
        
        return True
    
    async def move(self, steps: int, msDelay: float) -> bool:
        # Move shaft, rotating the shaft in direction and number of steps given by steps (positive steps = clockwise).
        
        if(steps == 0):
            return False
        
        # Steps always start at 0, which can move the shaft backwards, use stepIndex
        sortedPins = self.pins if(steps > 0) else self.pins[::-1]
        adjustedSteps = abs(steps)
        stepCounter = 0
        for _ in range(adjustedSteps):
            for step in self.stepSequence:
                for i in range(len(sortedPins)):
                    sortedPins[i].value(step[i])
                    
                stepCounter += 1
                if(stepCounter > adjustedSteps):
                    return True
                
                utime.sleep_ms(msDelay)
        
        return True
    
    async def moveDegrees(self, degrees: float, msDelay: float) -> bool:
        # Move shaft, rotating the shaft in direction and degrees given (positive degrees = clockwise).
        
        if(degrees == 0):
            return False
        
        sortedPins = self.pins if(degrees > 0) else self.pins[::-1]
        adjustedSteps = self.map(abs(degrees), 0, 360, 0, 400) # self.stepperFullRotationSteps # TODO 200 for full step, 400 for half, 800 for 1/4 etc.
        print(adjustedSteps)
        stepCounter = 0
        for _ in range(adjustedSteps):
            for step in self.stepSequence:
                for i in range(len(sortedPins)):
                    sortedPins[i].value(step[i])
                    
                stepCounter += 1
                if(stepCounter > adjustedSteps):
                    return True
                
                utime.sleep_ms(msDelay)
        
        return True
    
    def map(self, x: float, in_min: float, in_max: float, out_min: float, out_max: float) -> float:
        # https://www.arduino.cc/reference/en/language/functions/math/map/
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        
class ButtonUtil:
    def readButtonHold(button: tuple) -> int:
        # Measure the length in ms of a button being held down.
        
        msStart = utime.ticks_ms()
        while button.value():
            pass
            
        return utime.ticks_ms() - msStart

    def readButtonPress(button: tuple) -> int:
        # Read if a button has been pressed once, signal returning depending on XXX.
        
        lastState = button.value()
        while(button.value() == 1) or (button.value() == lastState):
            lastState = button.value()
            
        return lastState
