import uasyncio
from dumbDoor import DumbDoor
from ioUtil import halfStepSequence

# UTC is preferable since it's near constant, local times, e.g. London, will not account for daylight saving time.
datetimeSourceUrl = "http://worldtimeapi.org/api/timezone/etc/utc" # "http://worldtimeapi.org/api/timezone/Europe/London" 
logFilename = "dumbDoor.log"
logFileMaxSizeByte = int(512 * 1024) # 512 kb, capped to 2 mb on standard PICO. Keep in mind the temporary file will add additional when rotating/cleaning

statusLedPins = [1, 2, 3]
mainButtonPin = 28
mainMotorPins = [12, 14, 13, 15]
mainMotorSequence = halfStepSequence
mainMotorMaxSteps = 400

door = DumbDoor(datetimeSourceUrl, logFilename, logFileMaxSizeByte, statusLedPins, mainButtonPin, mainMotorPins, mainMotorSequence, mainMotorMaxSteps)
uasyncio.run(door.run())