import uasyncio
import urequests
import utime
import _thread
import uos
import micropython

from picozero import RGBLED
from machine import Pin, reset

from queue import Queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py

import secrets # Secret values in secrets.py
from logUtil import LogUtil
from networkUtil import NetworkUtil
from httpUtil import HttpUtil
from rgbLedUtil import RgbLedUtil
from rgbColor import RgbColor as rgb
from lockStatus import LockStatus
from lockAction import LockAction

logFilename = "dumbDoor.log"
logFileMaxSizeByte = 3000#int(512 * 1024) # 512 kb, capped to 2 mb on standard PICO. Keep in mind the temporary file will add additional when rotating/cleaning

rgbLed = RGBLED(red = 1, green = 2, blue = 3)
mainButton = Pin(4, Pin.IN, Pin.PULL_DOWN)

statusLed = RgbLedUtil(rgbLed)
logger = LogUtil(logFilename, logFileMaxSizeByte)
netUtil = NetworkUtil()
httpUtil = HttpUtil()

# UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
ledQueue = Queue()
inputQueue = Queue()

# TODO toggle lock/status button, motor, authentication on socket calls, modularize code (logging, led, network, http stuff, motor/other outputs),
# ledutil some non-red colors = red, logging error - wipes file

def log(message: str, logToFile: bool = True, doPrint: bool = True, encoding: str = "utf-8") -> None:
    # Log message thread safely.
    
    lock = _thread.allocate_lock()
    with lock:
        logger.log(message, logToFile, doPrint)
        
async def setupLan() -> str:
    # Connect to the internet using secrets from secrets.py file.
    
    log("Connecting to LAN...")
    
    defaultIp = "0.0.0.0"
    ip = defaultIp
    while ip == defaultIp:
        log("Getting IP...")
        ip = netUtil.connectWlan(secrets.ssid, secrets.password, secrets.ipTuple)
        await statusLed.blinkOnce(rgb.blue, rgb.off)
        
    log(f"Connected on IP: {ip}")
    return ip

async def setupDatetime() -> int:
    # Fetch datetime and more basics for logging.
    
    tickMsOffset = 0
    while not tickMsOffset:
        try:
            log(f"Initializing datetime...")
            headers = { "User-Agent": httpUtil.basicUserHeader }
            datetimeJson = urequests.get(datetimeSourceUrl, headers = headers).json()
            datetime = datetimeJson["datetime"]
            tickMsOffset = utime.ticks_ms()
            
            logger.datetimeInitiated = datetime
            logger.tickMsInitiated = tickMsOffset
            
            log(f"datetime ({datetime}) and tickMsOffset ({tickMsOffset}) initialized")
        except Exception as e:
            log("PICO connected to LAN, but there was an error with setting datetimeJson:")
            log(str(e))
            statusLed.blinkOnce(rgb.blue, rgb.red) # Built-in wait, 1000 ms

    return tickMsOffset
    
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
        log(f"toggleLockStatus - Invalid status: {newStatus}, defaulting to old status: {doorStatus}")
        return doorStatus
    
    log(f"Lock status updating: {doorStatus} -> {newStatus}")
    return newStatus
    
async def toggleLock(doorStatus: int, ledQueue: Queue) -> int:
    # Toggle lock, opening if status is locked, locking if status is open.
    
    toggleSource = "unknown"
    toggleBy = "unknown"
    newStatus = await toggleLockStatus(doorStatus, ledQueue)
    if(newStatus == LockStatus.locked):
        #await activateMotor(-100)
        log(f"{toggleSource} - {toggleBy} - Locked")
    elif(newStatus == LockStatus.unlocked):
        #await activateMotor(100)
        log(f"{toggleSource} - {toggleBy} - Unlocked")
    else:
        log(f"toggleLock - Invalid status: {newStatus}, defaulting to old status: {doorStatus}")
        return doorStatus
        
    return newStatus

def listenSocket(inputQueue: Queue, listenerSocket: Dict) -> None:
    # Listen and receive data over given paths on PICO IP.
    
    connection = None
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
            
            connection.send(httpUtil.getHtmlHeader(code, status))
            connection.send(httpUtil.getJsonWrapper(code, status, message, data))
            
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
        last = mainButton.value()
        while(mainButton.value() == 1) or (mainButton.value() == last):
            last = mainButton.value()
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
    
    log("Main loop started")
    while 1:
        if(not inputQueue.empty()):
            action = await inputQueue.get()
            if(action == LockAction.lockToggle):
                doorStatus = await toggleLock(doorStatus, ledQueue)
            elif(action == LockAction.statusToggle):
                doorStatus = await toggleLockStatus(doorStatus, ledQueue)
            
        await uasyncio.sleep_ms(100)
        
    log("Main loop completed")
    
async def main() -> None:
    # Entry point
    
    try:
        log("")
        log("Initializing...")
        log(f"Mem info: {str(micropython.mem_info())}")
        log(f"Sys info: {str(uos.uname())}")
        
        ip = await setupLan()
        setupDatetime()
        listenerSocket = netUtil.setupTcpSocketConnection(ip, port = 80, maxClients = 2)
        
        log("Initialize complete")
        
        # Start main loop in a new thread and set up input listeners on main thread
        # Note: this is done because sockets seem to have issues when not on the first/main thread
        _thread.start_new_thread(runMainLoop, ())
        
        log("Input listeners starting...")
        global inputQueue
        uasyncio.create_task(listenMainButton(inputQueue))
        uasyncio.create_task(listenSocket(inputQueue, listenerSocket))    
        log("Input listeners started")
        
    except KeyboardInterrupt:
        log("Keyboard interrupt")
        reset()
    except Exception as e:
        log("Error caught: ")
        log(str(e))
        raise e
        
uasyncio.run(main())
