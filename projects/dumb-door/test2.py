import utime
from machine import Pin

stepper_pins = [Pin(12, Pin.OUT), Pin(13, Pin.OUT), Pin(14, Pin.OUT), Pin(15, Pin.OUT)]
step_sequence = [
    [1, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 1],
    [1, 0, 0, 1],
]

def step(direction, steps, delay):
    for i in range(steps):
        for step in step_sequence:
            for j in range(len(stepper_pins)):
                stepper_pins[j].value(step[j])
                utime.sleep(delay)
                
step_index = 0
while 1:
    print("5 steps started")
    step(1, 5, 0.01)