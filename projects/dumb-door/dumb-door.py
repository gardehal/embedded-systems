import uasyncio
import random

import network
from picozero import RGBLED
from machine import Pin, reset

import queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py
import secrets  # Secret values in secrets.py

# TODO motor, button, on/off switch?, getting call over internet to lock/unlock, press+hold button to switch status without locking/unlocking door usage for correcting default state without having to force motor

rgb = RGBLED(red = 1, green = 2, blue = 3)
rgb_off = (0, 0, 0)
rgb_white = (255, 255, 255)
rgb_red = (255, 0, 0)
rgb_green = (0, 255, 0)
rgb_blue = (0, 0, 255)

button = Pin(14, Pin.IN, Pin.PULL_DOWN)

lockStatus = {"open": 0, "locked": 1}
doorStatus = lockStatus["locked"]

async def connectWlan():
    # Connect to WLAN using secrets from secrets.py file.
        
    rgb.color = rgb_blue
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    print([_[0] for _ in wlan.scan()])
    
    wlan.connect(secrets.ssid, secrets.password)
    wlan.ifconfig(secrets.ipStruct)
    while wlan.status() < 1:
        print(f"Waiting for connection... Status: {wlan.status()}")
        await blink(rgb_blue)
        
    ip = wlan.ifconfig()[0]
    print(f"Connected on IP: {ip}")
    return ip

async def blinkQ(q, off: tuple = rgb_off, onSeconds: float = 0.5, offSeconds: float = 0.5):
    # Blink LED with on color for onSeconds then off for offSeconds.
    
    c = rgb_off
    while 1:
        if(not q.empty()):
            c = await q.get()
        await blinkOnce(c, off, onSeconds, offSeconds)

async def blink(on: tuple, off: tuple = rgb_off, onSeconds: float = 0.5, offSeconds: float = 0.5):
    # Blink LED with on color for onSeconds then off for offSeconds.
    
    while 1:
        await blinkOnce(on, off, onSeconds, offSeconds)
        
async def blinkOnce(on: tuple, off: tuple = rgb_off, onSeconds: float = 0.5, offSeconds: float = 0.5):
    # Blink LED ONCE with on color for onSeconds then off for offSeconds.
    
    rgb.color = on
    await uasyncio.sleep(onSeconds)
    rgb.color = off
    await uasyncio.sleep(offSeconds)
    
def toggleLock():
    # Toggle lock, opening if status is locked, locking if status is open.
    
    if(doorStatus == lockStatus["locked"]):
        # TODO activate motor ccw
        print("WIP")
    else:
        # TODO activate motor cw
        print("WIP")
        
    toggleLockStatus()
    
def toggleLockStatus():
    # Toggle lock status only, not the physical door lock. Green LED = locked, red LED = open.
    
    if(doorStatus == lockStatus["locked"]):
        rgb.color = rgb_green
    else:
        rgb.color = rgb_red
        
async def waitButton():
    # Wait for button input.
    
    last = button.value()
    while(button.value() == 1) or (button.value() == last):
        last = button.value()
        await uasyncio.sleep(0.04)
        
    return last

async def main():
    try:
        # Signal startup
        await blinkOnce(rgb_white)
        
        if(0):
            ip = await connectWlan()
            # Run infinite loop until reset or fixed
            if(ip[0] == '0'):
                print("PICO connected to WLAN but IP was 0.0.0.0")
                await blink(rgb_red)
       
        q = queue.Queue()
        uasyncio.create_task(blinkQ(q, (100, 0, 100), 1, 2))
        timestamp = utime.ticks_ms()
        # Signal connect OK, default to locked state and wait for calls to toggle lock over WLAN or though button
        while 1:
            await waitButton()
            print("pressed")
            await q.put((random.randrange(1, 255), random.randrange(1, 255), random.randrange(1, 255)))
            
            #blink(rgb_green, 2)
            # TODO toggle lock, toggle status, blink async
            
    except KeyboardInterrupt:
        print(f"An error occurred, resetting machine")
        reset()
        
uasyncio.run(main())
reset()
