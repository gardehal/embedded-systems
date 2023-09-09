import uasyncio
import utime
from machine import Pin

class Stepper:
    pins = []
    fullStepSequence = [
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
        
    def __init__(self, motorPins: list):
        self.pins = [Pin(motorPins[0], Pin.OUT),
                         Pin(motorPins[1], Pin.OUT),
                         Pin(motorPins[2], Pin.OUT),
                         Pin(motorPins[3], Pin.OUT)]
    
    async def move(self, steps: int, msDelay: float) -> bool:
        # Activate motor, rotating the shaft in direction and number of steps given by steps (positive steps = clockwise).
        
        # TODO 1 step moves 4 full steps in the motor
        #adjustedSteps = int(steps/4)
        
        # TODO direction, negative steps should be ccw
        #cw = steps > 0
        
        # TODO halfstep because of accuracy
        stepSequence = self.fullStepSequence if(steps > 0) else reverse(self.fullStepSequence)
        for _ in range(steps):
            for step in stepSequence:
                print("step")
                for i in range(len(self.pins)):
                    print("pin")
                    self.pins[i].value(step[i])
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
