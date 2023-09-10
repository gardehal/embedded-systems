import uasyncio
import utime
from machine import Pin

class Stepper:
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
    
    pins = []
    stepSequence = []
        
    def __init__(self, motorPins: list, stepSequence: list = halfStepSequence):
        # Init Stepper class, setting pins, step sequence.
        
        self.pins = [Pin(motorPins[0], Pin.OUT),
                         Pin(motorPins[1], Pin.OUT),
                         Pin(motorPins[2], Pin.OUT),
                         Pin(motorPins[3], Pin.OUT)]
        
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
        
        c = 0
        sortedPins = self.pins if(steps > 0) else self.pins[::-1]
        # TODO better control over steps, 1 step is currently nPins *nStepper sequence
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
