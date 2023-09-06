import utime
from machine import Pin

pins = [Pin(12, Pin.OUT), Pin(13, Pin.OUT), Pin(14, Pin.OUT), Pin(15, Pin.OUT)]
stepSequence = [
    [1, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 1],
    [1, 0, 0, 1],
]

def step(direction, steps, delay):
    for _ in range(steps):
        for step in stepSequence:
            for i in range(len(pins)):
                pins[i].value(step[i])
                #pins[i].value(step[i]) # Beeping caused by pins being on?
                utime.sleep(delay)
                
step_index = 0

if(1):
    while 1:
        print("5 steps started")
        step(1, 5, 0.05)
else:
    print("5 steps started")
    step(1, 5, 0.05)
    
for i in range(len(pins)):
    pins[i].value(0)
