import uasyncio
import utime
from machine import Pin

class Stepper:
    fullStepSequenceSingle = [
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
    
    pins = []
    stepSequence = fullStepSequenceDouble
        
    def __init__(self, motorPins: list):
        self.pins = [Pin(motorPins[0], Pin.OUT),
                         Pin(motorPins[1], Pin.OUT),
                         Pin(motorPins[2], Pin.OUT),
                         Pin(motorPins[3], Pin.OUT)]
        
        for pin in self.pins:
            pin.value(0)
    
    async def move(self, steps: int, msDelay: float) -> bool:
        # Activate motor, rotating the shaft in direction and number of steps given by steps (positive steps = clockwise).
        
        if(steps == 0):
            return False
        
        # TODO step sequence as options or arg for class
        c = 0
        sortedPins = self.pins if(steps > 0) else self.pins[::-1]
        adjustedSteps = abs(steps) #int(abs(steps)/(len(sortedPins) * len(stepperSequence)))
        for _ in range(adjustedSteps):
            for step in self.stepSequence:
                for i in range(len(sortedPins)):
                    c += 1
                    print(c)
                    sortedPins[i].value(step[i])
                utime.sleep_ms(msDelay)
        
        return True

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
