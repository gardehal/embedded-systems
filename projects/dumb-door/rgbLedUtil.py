import uasyncio
from rgbColor import RgbColor

class RgbLedUtil:
    # Note: Intended for from uasyncio, picozero.RGBLED, and micropython-async Queue ( https://raw.githubusercontent.com/peterhinch/micropython-async/master/v3/primitives/queue.py ).
    
    def __init__(self, rgbLed: tuple):
        self.rgbLed: tuple = rgbLed # picozero.RGBLED
    
    def setColor(self, color: tuple) -> None:
        # Set LED to color to color given.
        
        self.rgbLed.color = color
        
    async def blinkOnce(self, a: tuple, b: tuple = RgbColor.off, aMs: int = 500, bMs: int = 500) -> None:
        # Blink LED ONCE with a color for aMs milliseconds then b for bMs milliseconds.
        
        self.setColor(a)
        await uasyncio.sleep_ms(aMs)
        self.setColor(b)
        await uasyncio.sleep_ms(bMs)

    async def blink(self, a: tuple, b: tuple = RgbColor.off, aMs: int = 500, bMs: int = 500) -> None:
        # Blink LED with a color for aMs milliseconds then b for bMs milliseconds.
        
        while 1:
            await self.blinkOnce(a, b, aMs, bMs)

    async def blinkQueue(self, queue: Queue, aMs: int = 500, bMs: int = 500) -> None:
        # Blink LED with colours from queue, first item for aMs milliseconds then the next item for bMs milliseconds, repeating. Function will use queue updates.
        
        a = RgbColor.off
        b = RgbColor.off
        while 1:
            if(not queue.empty()):
                a = await queue.get()
            if(not queue.empty()):
                b = await queue.get()
            
            await self.blinkOnce(a, b, aMs, bMs)

    async def blinkQueues(self, colorQueue: Queue, timerQueue: Queue) -> None:
        # Blink LED with colours from colorQueue, and timing (milliseconds) for each blink from timerQueue, repeating. Function will use queue updates.
        
        a = RgbColor.off
        b = RgbColor.off
        aMs = 1000
        bMs = 1000
        while 1:
            if(not colorQueue.empty()):
                a = await colorQueue.get()
            if(not colorQueue.empty()):
                b = await colorQueue.get()
            if(not timerQueue.empty()):
                aMs = await timerQueue.get()
            if(not timerQueue.empty()):
                bMs = await timerQueue.get()
            
            await self.blinkOnce(a, b, aMs, bMs)
