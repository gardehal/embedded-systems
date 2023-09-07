import utime
from machine import Pin

pins = [Pin(15, Pin.OUT), Pin(14, Pin.OUT), Pin(13, Pin.OUT), Pin(12, Pin.OUT)]
halfstepSequence = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1],
]
fullstepSequence = [
    [1, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 1],
    [1, 0, 0, 1],
]

def step(direction, steps, delay):
    for _ in range(steps):
        for step in fullstepSequence:
            for i in range(len(pins)):
                pins[i].value(step[i])
                utime.sleep_ms(delay)
                
step_index = 0

if(1):
    while 1:
        print("5 steps started")
        step(1, 5, 50)
else:
    print("5 steps started")
    step(1, 5, 50)
    
for i in range(len(pins)):
    pins[i].value(0)
