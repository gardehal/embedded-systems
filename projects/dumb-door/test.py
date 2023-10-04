from machine import Pin
import utime
import uasyncio
from rgbLedUtil import RgbLedUtil
from picozero import RGBLED
from rgbColor import RgbColor as rgb
from queue import Queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py

trigger = Pin(3, Pin.OUT)
echo = Pin(2, Pin.IN)

def ultra():
    trigger.low()
    utime.sleep_us(2)
    trigger.high()
    utime.sleep_us(5)
    trigger.low()
    
    signaloff = 0
    signalon = 0
    while echo.value() == 0:
        signaloff = utime.ticks_us()
    while echo.value() == 1:
        signalon = utime.ticks_us()
        
    timepassed = signalon - signaloff
    distanceCm = (timepassed * 0.0343) / 2
    
    print("The distance from object is ",distanceCm,"cm")
    if(distanceCm > 5):
        print("door open")
    else:
        print("door closed")
   
while 0:
   ultra()
   utime.sleep_ms(2000)
   
   
async def blink():
    print("blink start")
    statusLed = RgbLedUtil(RGBLED(red = 1, green = 2, blue = 3))
    ledQueue = Queue()
    print("queue")
    await ledQueue.put(rgb.white)
    await ledQueue.put(rgb.off)
    uasyncio.create_task(statusLed.blinkQueue(ledQueue, 200, 2000))
    
    await uasyncio.sleep_ms(100000000)
    print("blink over")
  
print("test blink")  
uasyncio.run(blink())
    
