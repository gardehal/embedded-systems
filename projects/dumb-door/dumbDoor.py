import uasyncio
import urequests
import utime
import uos

import network
from picozero import RGBLED
from machine import Pin, reset

from queue import Queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py
import secrets # Secret values in secrets.py
from ledColor import *
import lockStatus as ls
        
logFilename = "dumbDoor.log"
logFileMaxSizeByte = 900 #(512 * 1024) # 512 kb, capped to 2 mb on standard PICO. Keep in mind the temp file will be ca. 50% additional when rotating/cleaning

rgb = RGBLED(red = 1, green = 2, blue = 3)

button = Pin(14, Pin.IN, Pin.PULL_DOWN)

# UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
datetime = "[Uninitialized]"
tickMsOffset = 0

# TODO toggle lock, toggle status only, better lock status like enum or object - not a dict, logging to file/truncate, getting call over internet to lock/unlock

def rotateLogFile(logPrefix: str, logFileSize: int) -> None:
    # Rotate logfile.
    
    print(f"{logPrefix} Logfile size exceeds logFileMaxSizeByte ({logFileSize}/{logFileMaxSizeByte} bytes), triggered clean up...")
    tmpLogFilename = "tmp_dumbDoor.log"
    tmpLogFileSize = 0

    # TODO repeat until copied x bytes
    #while(tmpLogFileSize < logFileMaxSizeByte):
    print(f"{logPrefix} Cleaning up (logfile size {logFileSize}/{logFileMaxSizeByte} bytes)...")
    
    blockSize = 16 * 1024 # 132 kb, capped to 264 kb RAM on standard PICO
    block = ""
    with open(logFilename, "rb") as readFile:
        readFile.seek(blockSize, 2)
        block = readFile.read(blockSize)
        
        # TODO ??? eof or something fails
        if block:
            print(block)
        
    with open(tmpLogFilename, "wb+") as writeFile:
        writeFile.seek(0, 0)
        writeFile.write(block)
        tmpLogFileSize = writeFile.tell()
        
    # TODO rename/delete tmp
    
async def log(message: str, logToFile: bool = True) -> None:
    # Print and log message in standard format.
    
    prefix = f"{datetime} +{utime.ticks_ms() - tickMsOffset}:"
    formattedMessage = f"{prefix} {message}"
    
    print(formattedMessage)
    
    if(logToFile):
        log = f"{formattedMessage}\n"
        logSize = len(log.encode("utf-8"))
        logFileSize = uos.stat(logFilename)[6]
        
        if((logFileSize + logSize + 1) > logFileMaxSizeByte):
            rotateLogFile(prefix, logFileSize)
                    
        with open(logFilename, "a") as file:
            file.write(log)

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
    # Connect to the internet using secrets from secrets.py file and set up .
    
    await log("PICO connecting to WLAN...")
    ip = await connectWlan()
    
    if(ip.startswith("0.")): # Run infinite loop until reset or fixed
        await log("PICO connected to WLAN but IP was 0.0.0.0")
        await blink(rgb_red)
        
    datetimeJson = urequests.get(datetimeSourceUrl).json()
    global datetime
    datetime = datetimeJson["datetime"]
    
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
    if(doorStatus == ls.locked):
        newStatus = ls.unlocked
        await ledQueue.put(rgb_red) # type: ignore
        await ledQueue.put(rgb_off) # type: ignore
    elif(doorStatus == ls.unlocked):
        newStatus = ls.locked
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
    if(newStatus == ls.locked):
        # TODO activate motor ccw
        await log(f"{toggleSource} - {toggleBy} - Locked")
    else:
        # TODO activate motor cw
        await log(f"{toggleSource} - {toggleBy} - Unlocked")
        
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
        await log("")
        await log("Initializing")
        await log(str(uos.uname()))
        await blinkOnce(rgb_white)
        
        # Connect to internet
        await connect()
            
        # Default to locked state and create async LED status blink
        doorStatus = ls.locked
        ledQueue = Queue()
        await ledQueue.put(rgb_green) # type: ignore
        await ledQueue.put(rgb_off) # type: ignore
        uasyncio.create_task(blinkQueue(ledQueue, 200, 2000))
        
        # Initialize complete
        global tickMsOffset
        tickMsOffset = utime.ticks_ms()
        await log("Initialize complete")
        
        # Main loop
        while 1:
            await registerInput()
            doorStatus = await toggleLock(doorStatus, ledQueue)
            
        await log("Main loop completed")
    except KeyboardInterrupt:
        await log("Keyboard interrupt")
        reset()
    except Exception as e:
        await log("Error caught: ")
        await log(str(e))
        reset()
        
uasyncio.run(main())
