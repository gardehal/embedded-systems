import uasyncio
import urequests
import utime
import uos

import network
from picozero import RGBLED
from machine import Pin, reset

from queue import Queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py
import secrets  # Secret values in secrets.py
        
logFilename = "dumbDoor.log"
logFileMaxSizeByte = 50 #(1024 * 1024) / 2 # 0.5 mb

rgb = RGBLED(red = 1, green = 2, blue = 3)
rgb_off = (0, 0, 0)
rgb_white = (255, 255, 255)
rgb_red = (255, 0, 0)
rgb_green = (0, 255, 0)
rgb_blue = (0, 0, 255)

button = Pin(14, Pin.IN, Pin.PULL_DOWN)

lockStatus = {"open": 1, "locked": 2}

# UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
datetime = "[Uninitialized]"
tickMsOffset = 0

# TODO motor, button, on/off switch?, getting call over internet to lock/unlock, press+hold button to switch status without locking/unlocking door usage for correcting default state without having to force motor
# TODO toggle lock, toggle status only, better lock status like enum or object - not a dict, logging to file/truncate
    
async def log(message: str) -> None:
    # Log some change.
    
    log = f"{datetime} +{utime.ticks_ms() - tickMsOffset}: {message}"
    
    print(log)
    
    with open(logFilename, "a") as file:
        fileSize = uos.stat(logFilename)[6]
        # if(fileSize > logFileMaxSizeByte):
        #     file.truncate(int(logFileMaxSizeByte - (logFileMaxSizeByte / 2)))
        
        # file.seek(0, 0)
        file.write(f"{log}\n")
        file.close()

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
    global datetime
    datetime = datetimeJson["datetime"]
    
    global tickMsOffset
    tickMsOffset = utime.ticks_ms()
    
    return ip
        
async def blinkOnce(a: tuple, b: tuple = rgb_off, aMs: int = 500, bMs: int = 500) -> None:
    # Blink LED ONCE with a color for aMs milliseconds then b for bMs milliseconds.
    
    rgb.color = a
    await uasyncio.sleep_ms(aMs)
    rgb.color = b
    await uasyncio.sleep_ms(bMs)

async def blink(a: tuple, b: tuple = rgb_off, aMs: int = 500, bMs: int = 500) -> None:
    # Blink LED with a color for aMs milliseconds then b for bMs milliseconds.
    
    while 1:
        await blinkOnce(a, b, aMs, bMs)

async def blinkQueue(queue, aMs: int = 500, bMs: int = 500) -> None:
    # Blink LED with colours from queue, first item for aMs milliseconds then the next item for bMs milliseconds, repeating.
    
    a = rgb_off
    b = rgb_off
    while 1:
        if(not queue.empty()):
            a = await queue.get()
            b = await queue.get()
        
        await blinkOnce(a, b, aMs, bMs)
    
async def toggleLockStatus(doorStatus: int, ledQueue: Queue) -> int:
    # Toggle lock status only, not the physical door lock. Updates LED: Green = locked, red = open.
    
    newStatus = 0
    if(doorStatus == lockStatus["locked"]):
        newStatus = lockStatus["open"]
        await ledQueue.put(rgb_red) # type: ignore
        await ledQueue.put(rgb_off) # type: ignore
    elif(doorStatus == lockStatus["open"]):
        newStatus = lockStatus["locked"]
        await ledQueue.put(rgb_green) # type: ignore
        await ledQueue.put(rgb_off) # type: ignore
    else:
        raise Exception(f"doorStatus was invalid: {doorStatus}")
    
    await log(f"Lock status updating: {doorStatus} -> {newStatus}")
    return newStatus
    
async def toggleLock(doorStatus, ledQueue: Queue) -> int:
    # Toggle lock, opening if status is locked, locking if status is open.
    
    toggleSource = "unknown"
    toggleBy = "unknown"
    newStatus = await toggleLockStatus(doorStatus, ledQueue)
    if(newStatus == lockStatus["open"]):
        # TODO activate motor cw
        await log(f"{toggleSource} - {toggleBy} - Opened")
    else:
        # TODO activate motor ccw
        await log(f"{toggleSource} - {toggleBy} - Locked")
        
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
        await log(str(uos.uname()))
        await log("Initializing")
        await blinkOnce(rgb_white)
        
        await connect()
            
        # Signal connect OK, default to locked state and create async LED status blink
        ledQueue = Queue()
        await ledQueue.put(rgb_green) # type: ignore
        await ledQueue.put(rgb_off) # type: ignore
        doorStatus = lockStatus["locked"]
        uasyncio.create_task(blinkQueue(ledQueue, 800, 4000))
        
        # Main loop
        await log("Initialize complete")
        while 1:
            await registerInput()
            doorStatus = await toggleLock(doorStatus, ledQueue)
            
    except KeyboardInterrupt:
        reset()
    except Exception as e:
        await log("Error caught: ")
        await log(str(e))
        reset()
        
uasyncio.run(main())

