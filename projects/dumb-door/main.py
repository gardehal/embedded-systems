import uasyncio
from dumbDoor import DumbDoor
from ioUtil import halfStepSequence

import secrets # Secret values in secrets.py

wifiSsid = secrets.ssid
wifiPassword = secrets.password
wifiIps = secrets.ipTuple
    
# UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
logFilename = "dumbDoor.log"
# 512 kb, capped to 2 mb on standard PICO. Keep in mind the temporary file will add additional when rotating/cleaning
logFileMaxSizeByte = int(512 * 1024)

statusLedPins = [1, 2, 3]
mainButtonPin = 28
mainMotorPins = [12, 14, 13, 15]
mainMotorSequence = halfStepSequence
mainMotorMaxSteps = 400

door = DumbDoor(wifiSsid, wifiPassword, wifiIps,
                datetimeSourceUrl, logFilename, logFileMaxSizeByte,
                statusLedPins, mainButtonPin, mainMotorPins,
                mainMotorSequence, mainMotorMaxSteps)

door.defaultLockSteps = 600
door.defaultLockStepSleepMs = 1

uasyncio.run(door.run())