import uasyncio
import urequests
import utime
import uos
import network
import usocket
import _thread
import micropython

from picozero import RGBLED
from machine import Pin, reset
from queue import Queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py

import secrets # Secret values in secrets.py
from logUtil import LogUtil
from rgbLedUtil import RgbLedUtil
from rgbColor import RgbColor as rgb
from lockStatus import LockStatus
from lockAction import LockAction

logFilename = "dumbDoor.log"
logFileMaxSizeByte = int(512 * 1024) # 512 kb, capped to 2 mb on standard PICO. Keep in mind the temporary file will add additional when rotating/cleaning

rgbLed = RGBLED(red = 1, green = 2, blue = 3)
button = Pin(4, Pin.IN, Pin.PULL_DOWN)

statusLed = RgbLedUtil(rgbLed)
logger = LogUtil(logFilename, logFileMaxSizeByte)

# UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
ledQueue = Queue()
inputQueue = Queue()

# TODO toggle lock/status button, motor, authentication on socket calls, modularize code (logging, led, network), ledutil some non-red colors = red

async def connectWlan() -> str:
    # Connect to WLAN using secrets from secrets.py file.
        
    await logger.log("Connecting to WLAN...")
    
    wlanScan = []
    statusLed.setColor(rgb.blue)
    while not wlanScan:
        wlan = network.WLAN(network.STA_IF)
        wlan.active(True)
        wlanScan = wlan.scan()
        await logger.log(f"Scanned SSIDs: {[_[0] for _ in wlanScan]}")
    
    wlan.connect(secrets.ssid, secrets.password)
    wlan.ifconfig(secrets.ipStruct)
    while wlan.status() < 1:
        await logger.log(f"Waiting for connection... Status: {wlan.status()}")
        await statusLed.blink(rgb.blue)
        
    ip = wlan.ifconfig()[0]
    await logger.log(f"Connected on IP: {ip}")
    return ip

async def setupSocketConnection(ip: str) -> Dict:
    # Set up socket listeners for wireless calls.
    
    await logger.log("Setting up socket...")
    socketAddress = usocket.getaddrinfo(ip, 80)[0][-1]
    
    listenerSocket = usocket.socket()
    listenerSocket.setsockopt(usocket.SOL_SOCKET, usocket.SO_REUSEADDR, 1)
    listenerSocket.bind(socketAddress)
    listenerSocket.listen(1)
    
    await logger.log(f"Socket listening on {socketAddress}")
    return listenerSocket

async def setupLan() -> str:
    # Connect to the internet using secrets from secrets.py file and set up .
    
    await logger.log("Connecting to LAN...")
    
    defaultIp = "0.0.0.0"
    ip = defaultIp
    while ip == defaultIp:
        await logger.log("Getting IP...")
        ip = await connectWlan()
        await statusLed.blinkOnce(rgb.blue, rgb.off)
        
    tickMsOffset = 0
    while not tickMsOffset:
        try:
            await logger.log(f"Initializing datetime...")
            headers = { "User-Agent": "Mozilla/5.0 (Windows NT 6.0; WOW64; rv:24.0) Gecko/20100101 Firefox/24.0" }
            datetimeJson = urequests.get(datetimeSourceUrl, headers = headers).json()
            datetime = datetimeJson["datetime"]
            tickMsOffset = utime.ticks_ms()
            
            logger.datetimeInitiated = datetime
            logger.tickMsInitiated = tickMsOffset
            
            await logger.log(f"datetime ({datetime}) and tickMsOffset ({tickMsOffset}) initialized")
        except Exception as e:
            await logger.log("PICO connected to LAN, but there was an error with setting datetimeJson:")
            await logger.log(str(e))
            await statusLed.blinkOnce(rgb.blue, rgb.red) # Built-in wait, 1000 ms

    return ip
    
async def toggleLockStatus(doorStatus: int, ledQueue: Queue) -> int:
    # Toggle lock status only, not the physical door lock. Updates LED: Green = locked, red = open.
    
    newStatus = 0
    if(doorStatus == LockStatus.locked):
        newStatus = LockStatus.unlocked
        await ledQueue.put(rgb.red)
        await ledQueue.put(rgb.off)
    elif(doorStatus == LockStatus.unlocked):
        newStatus = LockStatus.locked
        await ledQueue.put(rgb.green)
        await ledQueue.put(rgb.off)
    else:
        await logger.log(f"toggleLockStatus - Invalid status: {newStatus}, defaulting to old status: {doorStatus}")
        return doorStatus
    
    await logger.log(f"Lock status updating: {doorStatus} -> {newStatus}")
    return newStatus
    
async def activateMotor(steps: int) -> int:
    # Activate motor, rotating the shaft in direction and number of steps given by steps.
    
    return 0
    
async def toggleLock(doorStatus: int, ledQueue: Queue) -> int:
    # Toggle lock, opening if status is locked, locking if status is open.
    
    toggleSource = "unknown"
    toggleBy = "unknown"
    newStatus = await toggleLockStatus(doorStatus, ledQueue)
    if(newStatus == LockStatus.locked):
        await activateMotor(-100)
        await logger.log(f"{toggleSource} - {toggleBy} - Locked")
    elif(newStatus == LockStatus.unlocked):
        await activateMotor(100)
        await logger.log(f"{toggleSource} - {toggleBy} - Unlocked")
    else:
        await logger.log(f"toggleLock - Invalid status: {newStatus}, defaulting to old status: {doorStatus}")
        return doorStatus
        
    return newStatus

def listenSocket(inputQueue: Queue, listenerSocket: Dict) -> None:
    # Listen and receive data over given paths on PICO IP.
    
    while 1:
        try:
            connection, _ = listenerSocket.accept()
            request = str(connection.recv(1024))
            #print(request) # Verbose
        
            action = 0
            if(request.find("/toggleLock") == 6):
                action = LockAction.lockToggle
            elif(request.find("/toggleStatus") == 6):
                action = LockAction.statusToggle

            code = 200
            status = "SUCCESS"
            message = f"+{logger.tickMsInitiated} ms after initialization"
            data = None
            if(not action):
                code = 404
                status = "FAIL"
                message = "Path was not valid"
            
            connection.send(f"HTTP/1.0 {code} {status}\r\nContent-type: application/json\r\n\r\n")
            connection.send(f"{{ 'code': {code}, 'status': {status}, 'message': {message}, 'data': {data} }}")
            
            if(action):
                inputQueue.put_nowait(action)
        except Exception as e:
            print(str(e))
            utime.sleep_ms(100)
            continue
        finally:
            if(connection):
                connection.close()
        
async def listenMainButton(inputQueue: Queue) -> None:
    # Wait for main button input and determine actions to take.
    
    while 1:
        last = button.value()
        while(button.value() == 1) or (button.value() == last):
            last = button.value()
            await uasyncio.sleep_ms(100)
            
        # TODO hardcoded lock only, missing status
        await inputQueue.put(1)

def runMainLoop() -> None:
    # Run mainLoop using uasyncio for the async functionality.
    
    uasyncio.run(mainLoop())
    
async def mainLoop() -> None:
    # Set up outputs; status LED and main loop for motor handleing
    
    # Default to locked state and create async LED status blink
    doorStatus = LockStatus.locked
    global inputQueue
    global ledQueue
    await ledQueue.put(rgb.white)
    await ledQueue.put(rgb.off)
    uasyncio.create_task(statusLed.blinkQueue(ledQueue, 200, 2000))
    
    await logger.log("Main loop started")
    while 1:
        if(not inputQueue.empty()):
            action = await inputQueue.get()
            if(action == LockAction.lockToggle):
                doorStatus = await toggleLock(doorStatus, ledQueue)
            elif(action == LockAction.statusToggle):
                doorStatus = await toggleLockStatus(doorStatus, ledQueue)
            
        await uasyncio.sleep_ms(100)
        
    await logger.log("Main loop completed")
        
async def main() -> None:
    # Entry point
    
    try:
        await logger.log("")
        await logger.log("Initializing...")
        await logger.log(f"Mem info: {str(micropython.mem_info())}")
        await logger.log(f"Sys info: {str(uos.uname())}")
        
        ip = await setupLan()
        listenerSocket = await setupSocketConnection(ip)
        
        await logger.log("Initialize complete")
        
        # Start main loop in a new thread and set up input listeners on main thread
        # Note: this is done because sockets seem to have issues when not on the first/main thread
        _thread.start_new_thread(runMainLoop, ())
        
        await logger.log("Input listeners starting...")
        global inputQueue
        uasyncio.create_task(listenMainButton(inputQueue))
        uasyncio.create_task(listenSocket(inputQueue, listenerSocket))    
        await logger.log("Input listeners started")
        
    except KeyboardInterrupt:
        await logger.log("Keyboard interrupt")
        reset()
    except Exception as e:
        await logger.log("Error caught: ")
        await logger.log(str(e))
        raise e
        
uasyncio.run(main())
