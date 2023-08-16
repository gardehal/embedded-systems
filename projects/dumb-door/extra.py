
import utime

def readButtonHold(button: Dict) -> int:
    # Measure the length in ms of a button being held down.
    
    msStart = utime.ticks_ms()
    while button.value():
        pass
        
    return utime.ticks_ms() - msStart

def readButtonPress(button: Dict) -> int:
    # Read if a button has been pressed once, signal returning depending on XXX.
    
    lastState = button.value()
    while(button.value() == 1) or (button.value() == lastState):
        lastState = button.value()
        
    return lastState