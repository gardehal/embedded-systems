
import utime

#mainMotorPins = [Pin(9, Pin.OUT), Pin(10, Pin.OUT), Pin(11, Pin.OUT), Pin(12, Pin.OUT)]
#fullStepSequence = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]

class MotorUtil:
    async def activateMotor(self, motor: tuple, steps: int) -> int:
        # Activate motor, rotating the shaft in direction and number of steps given by steps.
        
        i = 0
        while i < steps:
            for step in fullStepSequence:
                for j in range(len(mainMotorPins))
                    mainMotorPins[j].value(step[j])
                    await uasyncio.sleep_ms(1)
            
            i += 1
        
        return 0

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
