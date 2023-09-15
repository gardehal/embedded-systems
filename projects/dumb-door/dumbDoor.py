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
from ioUtil import Stepper, halfStepSequence
from rgbColor import RgbColor as rgb
from lockStatus import LockStatus
from lockAction import LockAction


# TODO toggle lock/status button, authentication on socket calls, modularize code (io), logging on threads still clashing?

class DumbDoor:
    
    # UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
    datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
    logFilename = "dumbDoor.log"
    logFileMaxSizeByte = int(512 * 1024) # 512 kb, capped to 2 mb on standard PICO. Keep in mind the temporary file will add additional when rotating/cleaning

    rgbLed = RGBLED(red = 1, green = 2, blue = 3)
    mainButton = Pin(28, Pin.IN, Pin.PULL_DOWN)
    mainMotor = Stepper([12, 14, 13, 15], halfStepSequence, 400)

    statusLed = RgbLedUtil(rgbLed)
    logger = LogUtil(logFilename, logFileMaxSizeByte)
    netUtil = NetworkUtil()
    http = HttpUtil()

    ledQueue = Queue()
    inputQueue = Queue()

    def log(self, message: str, logToFile: bool = True, doPrint: bool = True, encoding: str = "utf-8") -> None:
        # Log message safely for threads.
        
        lock = _thread.allocate_lock()
        with lock:
            try:
                self.logger.log(message, logToFile, doPrint, encoding)
            except:
                #self.log(str(e))
                self.statusLed.blink(rgb.yellow, rgb.red)
            
    async def setupLan(self) -> str:
        # Connect to the internet using secrets from secrets.py file.
        
        self.log("Connecting to LAN...")
        
        defaultIp = "0.0.0.0"
        ip = defaultIp
        while ip == defaultIp:
            self.log("Getting IP...")
            ip = self.netUtil.connectWlan(secrets.ssid, secrets.password, secrets.ipTuple)
            await self.statusLed.blinkOnce(rgb.blue, rgb.off)
            
        self.log(f"Connected on IP: {ip}")
        return ip

    async def setupDatetime(self) -> int:
        # Fetch datetime and more basics for logging.
        
        tickMsOffset = 0
        while not tickMsOffset:
            try:
                self.log(f"Initializing datetime...")
                headers = { "User-Agent": self.http.basicUserHeader }
                datetimeJson = urequests.get(datetimeSourceUrl, headers = headers).json()
                datetime = datetimeJson["datetime"]
                tickMsOffset = utime.ticks_ms()
                
                self.logger.datetimeInitiated = datetime
                self.logger.tickMsInitiated = tickMsOffset
                
                self.log(f"datetime ({datetime}) and tickMsOffset ({tickMsOffset}) initialized")
            except Exception as e:
                self.log("PICO connected to LAN, but there was an error with setting datetimeJson:")
                self.log(str(e))
                self.statusLed.blinkOnce(rgb.blue, rgb.red) # Built-in wait, 1000 ms

        return tickMsOffset
        
    async def toggleLockStatus(self, doorStatus: int, ledQueue: Queue) -> int:
        # Toggle lock status only, not the physical door lock. Updates LED: Green = locked, red = open.
        
        newStatus = 0
        if(doorStatus == LockStatus.locked):
            newStatus = LockStatus.unlocked
            await self.ledQueue.put(rgb.red)
            await self.ledQueue.put(rgb.off)
        elif(doorStatus == LockStatus.unlocked):
            newStatus = LockStatus.locked
            await self.ledQueue.put(rgb.green)
            await self.ledQueue.put(rgb.off)
        else:
            self.log(f"toggleLockStatus - Invalid status: {newStatus}, defaulting to old status: {doorStatus}")
            return doorStatus
        
        self.log(f"Lock status updating: {doorStatus} -> {newStatus}")
        return newStatus
        
    async def toggleLock(self, doorStatus: int, ledQueue: Queue) -> int:
        # Toggle lock, opening if status is locked, locking if status is open.
        
        toggleSource = "unknown"
        toggleBy = "unknown"
        newStatus = await self.toggleLockStatus(doorStatus, ledQueue)
        if(newStatus == LockStatus.locked):
            await self.mainMotor.move(200, 5)
            self.mainMotor.deInit()
            self.log(f"{toggleSource} - {toggleBy} - Locked")
        elif(newStatus == LockStatus.unlocked):
            await self.mainMotor.move(-200, 5)
            self.mainMotor.deInit()
            self.log(f"{toggleSource} - {toggleBy} - Unlocked")
        else:
            self.log(f"toggleLock - Invalid status: {newStatus}, defaulting to old status: {doorStatus}")
            return doorStatus
            
        return newStatus

    def listenSocket(self, listenerSocket: Dict) -> None:
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
                message = f"+{self.logger.tickMsInitiated} ms after initialization"
                data = None
                if(not action):
                    code = 404
                    status = "FAIL"
                    message = "Path was not valid"
                
                connection.send(self.http.getHtmlHeader(code, status))
                connection.send(self.http.getJsonWrapper(code, status, message, data))
                
                if(action):
                    self.inputQueue.put_nowait(action)
            except Exception as e:
                print(str(e))
                utime.sleep_ms(100)
                continue
            finally:
                if(connection):
                    connection.close()
            
    async def listenMainButton(self) -> None:
        # Wait for main button input and determine actions to take.
        
        while 1:
            last = self.mainButton.value()
            while(self.mainButton.value() == 1) or (self.mainButton.value() == last):
                last = self.mainButton.value()
                await uasyncio.sleep_ms(100)
                
            # TODO hardcoded lock only, missing status
            await self.inputQueue.put(1)

    def runMainLoop(self) -> None:
        # Run mainLoop using uasyncio for the async functionality.
        
        uasyncio.run(self.mainLoop())
        
    async def mainLoop(self) -> None:
        # Set up outputs; status LED and main loop for motor handleing
        
        # Default to locked state and create async LED status blink
        doorStatus = LockStatus.locked
        await self.ledQueue.put(rgb.white)
        await self.ledQueue.put(rgb.off)
        uasyncio.create_task(self.statusLed.blinkQueue(self.ledQueue, 200, 2000))
        
        self.log("Main loop started")
        while 1:
            if(not self.inputQueue.empty()):
                action = await self.inputQueue.get()
                if(action == LockAction.lockToggle):
                    doorStatus = await self.toggleLock(doorStatus, self.ledQueue)
                elif(action == LockAction.statusToggle):
                    doorStatus = await self.toggleLockStatus(doorStatus, self.ledQueue)
                
            await uasyncio.sleep_ms(100)
            
        self.log("Main loop completed")
        
    async def run(self) -> None:
        # Entry point
        
        try:
            self.log("")
            self.log("Initializing...")
            self.log(f"Mem info: {str(micropython.mem_info())}")
            self.log(f"Sys info: {str(uos.uname())}")
            
            ip = await self.setupLan()
            self.setupDatetime()
            listenerSocket = self.netUtil.setupTcpSocketConnection(ip, port = 80, maxClients = 2)
            
            self.log("Initialize complete")
            
            # Start main loop in a new thread and set up input listeners on main thread
            # Note: this is done because sockets seem to have issues when not on the first/main thread
            _thread.start_new_thread(self.runMainLoop, ())
            
            self.log("Input listeners starting...")
            uasyncio.create_task(self.listenMainButton())
            uasyncio.create_task(self.listenSocket(listenerSocket))    
            self.log("Input listeners started")
            
        except KeyboardInterrupt:
            self.log("Keyboard interrupt")
            reset()
        except Exception as e:
            self.log("Error caught: ")
            self.log(str(e))
            raise e
            