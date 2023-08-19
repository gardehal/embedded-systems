import uasyncio
import urequests
import utime
import uos
import network
import usocket

from picozero import RGBLED
from machine import Pin, reset

from queue import Queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py
import secrets # Secret values in secrets.py
from ledColor import *
import lockStatus as ls
import action as act
        
logFilename = "dumbDoor.log"
logFileMaxSizeByte = int(512 * 1024) # 512 kb, capped to 2 mb on standard PICO. Keep in mind the temporary file will add additional when rotating/cleaning

rgb = RGBLED(red = 1, green = 2, blue = 3)
button = Pin(14, Pin.IN, Pin.PULL_DOWN)

# UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
datetime = "[DateTime Uninitialized]"
tickMsOffset = 0

# TODO toggle lock, toggle status only, authentication on socket calls, fix socket/button only working every other, classes with vars for "enums" like lockStatus

def rotateLogFile(logPrefix: str, logFileSize: int, logDeleteMultiplier: float = 0.5) -> None:
    # Rotate logfile, removing the first portion (logFileSize * logfileDeleteMultiplier) of the log file.
    
    print(f"{logPrefix} Logfile size exceeds logFileMaxSizeByte ({logFileSize}/{logFileMaxSizeByte} bytes), triggered clean up...")
    tmpLogFilename = f"tmp_{logFilename}"
    tmpLogFileSize = 0
    skipBytes = int(logFileSize * logDeleteMultiplier)

    logFileEof = False
    for i in range(0, 999):
        if(logFileEof or tmpLogFileSize > skipBytes):
            break
        
        chunkSize = 16 * 1024 # 16 kb, capped to 264 kb RAM on standard PICO
        chunk = ""
        print(f"{logPrefix} Cleaning up (logfile size {skipBytes + (chunkSize * i)}/{logFileSize} bytes)...")
        with open(logFilename, "rb") as readFile:
            readFile.seek(skipBytes + (chunkSize * i), 0)
            chunk = readFile.read(chunkSize)
            if not chunk: # EOF
                chunk = readFile.read()
                logFileEof = True
            
        with open(tmpLogFilename, "wb+") as writeFile:
            writeFile.seek(0, 0)
            writeFile.write(chunk)
            tmpLogFileSize = writeFile.tell()
        
    uos.rename(tmpLogFilename, logFilename)
    # EOF messes with remove file for some reason, truncate file, then delete
    with open(tmpLogFilename, "w") as file:
        pass
    uos.remove(tmpLogFilename)
    
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

async def setupSocketConnection(ip: str) -> Dict:
    # Set up socket listeners for wireless calls.
    
    await log("Setting up socket...")
    socketAddress = usocket.getaddrinfo("0.0.0.0", 80)[0][-1]
    
    listenerSocket = usocket.socket()
    listenerSocket.setsockopt(usocket.SOL_SOCKET, usocket.SO_REUSEADDR, 1)
    listenerSocket.bind(socketAddress)
    listenerSocket.listen(1)
    
    await log(f"Socket listening on {socketAddress}")
    return listenerSocket

async def setupLan() -> str:
    # Connect to the internet using secrets from secrets.py file and set up .
    
    await log("Connecting to LAN...")
    
    defaultIp = "0.0.0.0"
    ip = defaultIp
    while ip == defaultIp:
        ip = await connectWlan()
        await uasyncio.sleep_ms(1000)
        
    while not tickMsOffset:
        try:
            headers = { "User-Agent": "Mozilla/5.0 (Windows NT 6.0; WOW64; rv:24.0) Gecko/20100101 Firefox/24.0" }
            datetimeJson = urequests.get(datetimeSourceUrl, headers = headers).json()
            
            global datetime
            datetime = datetimeJson["datetime"]
            global tickMsOffset
            tickMsOffset = utime.ticks_ms()
        except Exception as e:
            await log("PICO connected to LAN, but there was an error with setting datetimeJson:")
            await log(str(e))
            await log("Retrying fetch of datetimeJson")
            await blinkOnce(rgb_blue, rgb_red) # Buildt in wait, 1000 ms

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
        await ledQueue.put(rgb_red)
        await ledQueue.put(rgb_off)
    elif(doorStatus == ls.unlocked):
        newStatus = ls.locked
        await ledQueue.put(rgb_green)
        await ledQueue.put(rgb_off)
    else:
        raise Exception(f"doorStatus was invalid: {doorStatus}")
    
    await log(f"Lock status updating: {doorStatus} -> {newStatus}")
    return newStatus
    
async def toggleLock(doorStatus: int, ledQueue: Queue) -> int:
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

async def listenSocket(inputQueue: Queue, listenerSocket: Dict) -> int:
    # Listen and receive data over given paths on PICO IP.
    
    
    # Blinking tied to socket
    # Button delayed input or not triggering
    # Socket triggers twice
    # Without timeout, soocket hogs all threads for some reason
    #listenerSocket.settimeout(2)
    
    listenerSocket.setblocking(False)
    import uselect
    poller = uselect.poll()
    poller.register(listenerSocket, uselect.POLLIN)
    #if not res:
        # s is still not ready for input, i.e. operation timed out
    
    connection = None
    while 1:
        try:
            res = poller.poll(1000)  # time in milliseconds
            if not res:
                print("not res")
                await uasyncio.sleep_ms(100)
                continue
            
            connection, _ = listenerSocket.accept()
            request = str(connection.recv(1024))
            # await log(request) # Verbose
        
            action = 0
            if(request.find("/toggleLock")):
                action = act.lock
            elif(request.find("/toggleStatus")):
                action = act.status

            code = 200
            status = "SUCCESS"
            message = f"+{tickMsOffset} ms after initialization"
            data = None
            if(not action):
                code = 404
                status = "FAIL"
                message = "Path was not valid"
            
            connection.send(f"HTTP/1.0 {code} {status}\r\nContent-type: application/json\r\n\r\n")
            connection.send(f"{{ 'code': {code}, 'status': {status}, 'message': {message}, 'data': {data} }}")
            
            if(action):
                print("inputQueue put")
                print(action)
                print(connection)
                await inputQueue.put(action)
        except:
            await uasyncio.sleep_ms(100)
            continue
        finally:
            if(connection):
                connection.close()
        
async def listenMainButton(inputQueue: Queue) -> int:
    # Wait for main button input and determine actions to take.
    
    while 1:
        last = button.value()
        while(button.value() == 1) or (button.value() == last):
            last = button.value()
            await uasyncio.sleep_ms(100)
            
        # TODO hardcoded lock only, missing status
        print("botton put")
        await inputQueue.put(1)

async def main() -> None:
    try:
        # Signal startup
        await log("")
        await log("Initializing")
        await log(str(uos.uname()))
        
        # Connect to LAN and listen on socket
        ip = await setupLan()
        listenerSocket = await setupSocketConnection(ip)
        
        # Default to locked state and create async LED status blink
        doorStatus = ls.locked
        ledQueue = Queue()
        await ledQueue.put(rgb_green)
        await ledQueue.put(rgb_off)
        uasyncio.create_task(blinkQueue(ledQueue, 200, 2000))
        
        # Initialize complete
        await log("Initialize complete")
        
        # Main loop
        inputQueue = Queue()
        uasyncio.create_task(listenSocket(inputQueue, listenerSocket))
        uasyncio.create_task(listenMainButton(inputQueue))
        while 1:
            if(not inputQueue.empty()):
                action = await inputQueue.get()
                if(action == act.lock):
                    doorStatus = await toggleLock(doorStatus, ledQueue)
                elif(action == act.status):
                    doorStatus = await toggleLockStatus(doorStatus, ledQueue)
                  
            await uasyncio.sleep_ms(100)
            
        await log("Main loop completed")
    except KeyboardInterrupt:
        await log("Keyboard interrupt")
        reset()
    except Exception as e:
        await log("Error caught: ")
        await log(str(e))
        raise e
        
uasyncio.run(main())
    
