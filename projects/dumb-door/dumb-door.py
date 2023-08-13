import uasyncio
import random
import urequests
import utime

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

datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London"
datetime = "[Unknown]"
datetimeSet = False
        
async def log(message: str) -> None:
    # Log some change.
    
    log = f"{datetime} +{utime.ticks_ms()}: {message}"
    
    print(log)
    # TODO log to rotating file

async def connectWlan() -> str:
    # Connect to WLAN using secrets from secrets.py file.
        
    rgb.color = rgb_blue
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    await log(f"Scanned SSIDs: {[_[0] for _ in wlan.scan()]}")
    
    wlan.connect(secrets.ssid, secrets.password)
    wlan.ifconfig(secrets.ipStruct)
    while wlan.status() < 1:
        await log(f"Waiting for connection... Status: {wlan.status()}")
        await blink(rgb_blue)
        
    ip = wlan.ifconfig()[0]
    await log(f"Connected on IP: {ip}")
    return ip

async def connect() -> str:
    await log("PICO connecting to WLAN...")
    ip = await connectWlan()
    
    if(ip.startswith("0.")): # Run infinite loop until reset or fixed
        await log("PICO connected to WLAN but IP was 0.0.0.0")
        await blink(rgb_red)
        
    datetimeJson = urequests.get(datetimeSourceUrl).json()
    datetime = datetimeJson["datetime"]
    datetimeSet = True
    
    return ip

async def blinkQueue(queue, aMs: int = 500, bMs: int = 500) -> None:
    # Blink LED with colours from queue, first item for aMs milliseconds then the next item for bMs milliseconds, repeating.
    
    a = rgb_off
    b = rgb_off
    while 1:
        if(not queue.empty()):
            a = await queue.get()
            b = await queue.get()
        
        await blinkOnce(a, b, aMs, bMs)

async def blink(a: tuple, b: tuple = rgb_off, aMs: int = 500, bMs: int = 500) -> None:
    # Blink LED with a color for aMs milliseconds then b for bMs milliseconds.
    
    while 1:
        await blinkOnce(a, b, aMs, bMs)
        
async def blinkOnce(a: tuple, b: tuple = rgb_off, aMs: int = 500, bMs: int = 500) -> None:
    # Blink LED ONCE with a color for aMs milliseconds then b for bMs milliseconds.
    
    rgb.color = a
    await uasyncio.sleep_ms(aMs)
    rgb.color = b
    await uasyncio.sleep_ms(bMs)
    
async def toggleLock() -> int:
    # Toggle lock, opening if status is locked, locking if status is open.
    
    if(doorStatus == lockStatus["locked"]):
        # TODO activate motor ccw
        print("WIP")
    else:
        # TODO activate motor cw
        print("WIP")
        
    await log("Lock toggled")
    return await toggleLockStatus()
    
async def toggleLockStatus() -> int:
    # Toggle lock status only, not the physical door lock. Green LED = locked, red LED = open.
    
    newStatus = lockStatus["open"] if(doorStatus == lockStatus["locked"]) else lockStatus["locked"]
    await log(f"Lock status updated: {doorStatus} -> {newStatus}")
    return newStatus
        
async def registerInput() -> None:
    # Wait for button or API input.
    
    last = button.value()
    while(button.value() == 1) or (button.value() == last):
        last = button.value()
        # TODO input form API or similar
        await uasyncio.sleep_ms(40)
        
    return last

async def main() -> None:
    try:
        # Signal startup
        await log("Initializing")
        await blinkOnce(rgb_white)
        
        await connect()
            
        # Signal connect OK, default to locked state and create async LED status blink
        q = queue.Queue()
        await q.put(rgb_green) # type: ignore
        await q.put(rgb_off) # type: ignore
        doorStatus = lockStatus["locked"]
        uasyncio.create_task(blinkQueue(q, 1000, 4000))
        
        # Main loop
        await log("Initialize complete")
        while 1:
            await registerInput()
            newStatus = await toggleLock()
            ledStatus = rgb_green if(newStatus == 1) else rgb_red
            await q.put(ledStatus) # type: ignore
            await q.put(rgb_off) # type: ignore
            
            # TODO toggle lock, toggle status
            
    except KeyboardInterrupt:
        reset()
        
uasyncio.run(main())
reset()
