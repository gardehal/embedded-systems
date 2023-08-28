import uasyncio
import utime
from machine import Pin

class MotorUtil:
    pins = []
    fullStepSequence = [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]]
    
    def __init__(self, motorPins: list):
        self.pins = [Pin(motorPins[0], Pin.OUT),
                         Pin(motorPins[1], Pin.OUT),
                         Pin(motorPins[2], Pin.OUT),
                         Pin(motorPins[3], Pin.OUT)]
    
    async def move(self, steps: int) -> int:
        # Activate motor, rotating the shaft in direction and number of steps given by steps.
        
        i = 0
        while 1:
            for step in self.fullStepSequence:
                for j in range(len(self.pins)):
                    self.pins[j].value(step[j])
                    await uasyncio.sleep_ms(10)
            
            i += 1
        
        return i

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
