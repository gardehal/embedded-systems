# More details & schematic on electrocredible.com
import utime
from machine import Pin

# Define the pins for the stepper motor
stepper_pins = [Pin(12, Pin.OUT), Pin(13, Pin.OUT), Pin(14, Pin.OUT), Pin(15, Pin.OUT)]

# Define the sequence of steps for the motor to take
step_sequence = [
    [1, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1],
]

def step(direction, steps, delay):
    global step_index
    for i in range(steps):
        step_index = (step_index + direction) % len(step_sequence)
        for pin_index in range(len(stepper_pins)):
            pin_value = step_sequence[step_index][pin_index] 
            stepper_pins[pin_index].value(pin_value)
        utime.sleep(delay)
        

step_index = 0
while 1:
    step(1, 500, 0.5)
#step(-1, 500, 0.5)