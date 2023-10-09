import uasyncio
import urequests
import utime
import _thread
import uos
import micropython

from picozero import RGBLED
from machine import Pin, reset

from queue import Queue  # https://github.com/peterhinch/micropython-async/blob/master/v3/primitives/queue.py

from logUtil import LogUtil
from networkUtil import NetworkUtil
from httpUtil import HttpUtil
from rgbLedUtil import RgbLedUtil
from ioUtil import Stepper, halfStepSequence
from rgbColor import RgbColor as rgb
from lockStatus import LockStatus
from lockAction import LockAction
from lockInput import LockInput

class DumbDoor:
    
    wifiSsid = None
    wifiPassword = None
    ipTuple = None
    
    datetimeSourceUrl = None
    logFilename = None
    logFileMaxSizeByte = 0

    rgbLed = None
    mainButton = None
    mainMotor = None
    defaultLockSteps = 200
    defaultLockStepSleepMs = 5

    statusLed = None
    logger = None
    netUtil = None
    http = None

    ledQueue = None
    ledTimerQueue = None
    inputQueue = None
    lock = _thread.allocate_lock()
    
    def __init__(self, wifiSsid: str,
                 wifiPassword: str,
                 ipTuple: tuple,
                 datetimeSourceUrl: str,
                 logFilename: str,
                 logFileMaxSizeByte: int,
                 statusLedPins: list[int],
                 mainButtonPin: int,
                 mainMotorPins: list[int],
                 mainMotorSequence: list[int],
                 mainMotorMaxSteps: int,):
        # Initialize DumbDoor, using inputted settings.
        
        self.wifiSsid = wifiSsid
        self.wifiPassword = wifiPassword
        self.ipTuple = ipTuple
        
        self.datetimeSourceUrl = datetimeSourceUrl
        self.logFilename = logFilename
        self.logFileMaxSizeByte = logFileMaxSizeByte
        
        self.rgbLed = RGBLED(red = statusLedPins[0], green = statusLedPins[1], blue = statusLedPins[2])
        self.mainButton = Pin(mainButtonPin, Pin.IN, Pin.PULL_DOWN)
        self.mainMotor = Stepper(mainMotorPins, mainMotorSequence, mainMotorMaxSteps)
        
        self.statusLed = RgbLedUtil(self.rgbLed)
        self.logger = LogUtil(self.logFilename, self.logFileMaxSizeByte)
        self.netUtil = NetworkUtil()
        self.http = HttpUtil()
        self.ledQueue = Queue()
        self.ledTimerQueue = Queue()
        self.inputQueue = Queue()
        
    def log(self, message: str, logToFile: bool = True, doPrint: bool = True, encoding: str = "utf-8") -> None:
        # Log message safely for threads.
        
        with self.lock:
            try:
                self.logger.log(message, logToFile, doPrint, encoding)
            except Exception as e:
                print("log exception:")
                print(str(e))
                print("message:")
                print(message)
                
    async def setupLan(self) -> str:
        # Connect to the internet using secrets from secrets.py file.
        
        self.log("Connecting to LAN...")
        await self.ledQueue.put(rgb.blue)
        await self.ledQueue.put(rgb.off)
        
        defaultIp = "0.0.0.0"
        ip = defaultIp
        try:
            while ip == defaultIp:
                self.log("Getting IP...")
                ip = self.netUtil.connectWlan(self.wifiSsid, self.wifiPassword, self.ipTuple)
        except Exception as e:
            self.log("setupLan exception:")
            self.log(str(e))
            await self.ledQueue.put(rgb.blue)
            await self.ledQueue.put(rgb.red)
            raise e
            
        self.log(f"Connected on IP: {ip}")
        return ip

    async def setupDatetime(self) -> int:
        # Fetch datetime and more basics for logging.
        
        tickMsOffset = 0
        while not tickMsOffset:
            try:
                self.log(f"Initializing datetime...")
                datetimeRequest = urequests.get(self.datetimeSourceUrl)
                
                datetimeJson = datetimeRequest.json()
                datetime = datetimeJson["datetime"]
                tickMsOffset = utime.ticks_ms()
                
                datetimeRequest.close()
                
                self.logger.datetimeInitiated = datetime
                self.logger.tickMsInitiated = tickMsOffset
                
                self.log(f"datetime ({datetime}) and tickMsOffset ({tickMsOffset}) initialized")
            except Exception as e:
                self.log("PICO connected to LAN, but there was an error with setting datetimeInitiated:")
                self.log(str(e))
                await self.statusLed.blinkOnce(rgb.blue, rgb.red) # Built-in wait, 1000 ms

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
        
    async def toggleLock(self, lockInput: tuple, doorStatus: int, ledQueue: Queue) -> int:
        # Toggle lock, opening if status is locked, locking if status is open.
        
        newStatus = await self.toggleLockStatus(doorStatus, ledQueue)
        if(newStatus == LockStatus.locked):
            await self.mainMotor.move(lockInput.steps, lockInput.stepSleepMs)
            self.mainMotor.deInit()
            self.log(f"{lockInput.source} - {lockInput.caller} - Locked")
        elif(newStatus == LockStatus.unlocked):
            await self.mainMotor.move(0 - lockInput.steps, lockInput.stepSleepMs)
            self.mainMotor.deInit()
            self.log(f"{lockInput.source} - {lockInput.caller} - Unlocked")
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
            
                lockInput = LockInput(0, "socket", "unknown", self.defaultLockSteps, self.defaultLockStepSleepMs)
                if(request.find("/toggleLock") == 6):
                    lockInput.action = LockAction.lockToggle
                elif(request.find("/toggleStatus") == 6):
                    lockInput.action = LockAction.statusToggle
                    
                if(request.find("steps=") > 6):
                    argStart = request.split("steps=")[-1]
                    arg = argStart.split(" ")[0].split("&")[0]
                    lockInput.steps = int(arg)
                if(request.find("stepsleepms=") > 6):
                    argStart = request.split("stepsleepms=")[-1]
                    arg = argStart.split(" ")[0].split("&")[0]
                    lockInput.stepSleepMs = int(arg)

                code = 200
                status = "SUCCESS"
                message = f"+{self.logger.tickMsInitiated} ms after initialization"
                data = None
                if(not lockInput.action):
                    code = 404
                    status = "FAIL"
                    message = "Path was not valid"
                
                connection.send(self.http.getHtmlHeader(code, status))
                connection.send(self.http.getJsonWrapper(code, status, message, data))
                
                if(lockInput.action):
                    self.inputQueue.put_nowait(lockInput)
            except Exception as e:
                self.log("listenSocket exception:")
                self.log(str(e))
                utime.sleep_ms(100)
                continue
            finally:
                if(connection):
                    connection.close()
            
    async def listenMainButton(self) -> None:
        # Wait for main button input and determine actions to take.
        
        while 1:
            pressStartMs = 0
            last = self.mainButton.value()
            while(self.mainButton.value() == 1) or (self.mainButton.value() == last):
                if(self.mainButton.value() != last):
                    pressStartMs = utime.ticks_ms()
                    
                last = self.mainButton.value()
                await uasyncio.sleep_ms(100)
                
            pressEndMs = utime.ticks_ms()
            if((pressEndMs - pressStartMs) > 5000): # > 5 second press will toggle status but not unlock the door
                await self.inputQueue.put(LockInput(LockAction.statusToggle, "mainButton", "unknown", self.defaultLockSteps, self.defaultLockStepSleepMs))
            else:
                await self.inputQueue.put(LockInput(LockAction.lockToggle, "mainButton", "unknown", self.defaultLockSteps, self.defaultLockStepSleepMs))

    def runMainLoop(self) -> None:
        # Run mainLoop using uasyncio for the async functionality.

        uasyncio.run(self.mainLoop())

    async def mainLoop(self) -> None:
        # Set up outputs; status LED and main loop for motor handleing
            
        # Default to locked state and create async LED status blink
        doorStatus = LockStatus.locked
        await self.ledQueue.put(rgb.green)
        await self.ledQueue.put(rgb.off)
        await self.ledTimerQueue.put(200)
        await self.ledTimerQueue.put(2000)

        self.log("Main loop started")
        while 1:
            if(not self.inputQueue.empty()):
                lockInput = await self.inputQueue.get()
                if(lockInput.action == LockAction.lockToggle):
                    doorStatus = await self.toggleLock(lockInput, doorStatus, self.ledQueue)
                elif(lockInput.action == LockAction.statusToggle):
                    doorStatus = await self.toggleLockStatus(doorStatus, self.ledQueue)

            await uasyncio.sleep_ms(100)

        self.log("Main loop completed")
        
    def startListeners(self, listenerSocket) -> None:
        # Set up outputs; status LED and main loop for motor handleing
        
        self.log("Input listeners starting...")
        uasyncio.create_task(self.listenMainButton())
        uasyncio.create_task(self.listenSocket(listenerSocket))    
        self.log("Input listeners started")
        
    async def run(self) -> None:
        # Entry point
        
        try:
            self.log("")
            self.log("Initializing...")
            self.log(f"Sys info: {str(uos.uname())}")
            self.log(f"Mem info: {str(micropython.mem_info())}")
            
            uasyncio.create_task(self.statusLed.blinkQueues(self.ledQueue, self.ledTimerQueue))
            await self.ledQueue.put(rgb.white)
            await self.ledQueue.put(rgb.off)
            await self.ledTimerQueue.put(250)
            await self.ledTimerQueue.put(250)
            
            ip = await self.setupLan()
            await self.setupDatetime()
            listenerSocket = self.netUtil.setupTcpSocketConnection(ip, port = 80, maxClients = 2)
            
            self.log("Initialize complete")
            
            # Start main loop in a new thread and set up input listeners on main thread
            # Note: this is done because sockets seem to have issues when not on the first/main thread
            _thread.start_new_thread(self.runMainLoop, ())
            self.startListeners(listenerSocket)
                 
        except KeyboardInterrupt:
            self.log("Keyboard interrupt")
            reset()
        except Exception as e:
            self.log("Error caught: ")
            self.log(str(e))
            raise e
            