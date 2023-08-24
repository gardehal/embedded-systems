import uos
import utime

class LogUtil:
    datetimeInitiated: str = None
    tickMsInitiated: int = None
    
    def __init__(self,
                 logFilename: str,
                 logFileMaxSizeByte: int,
                 datetimeInitiated: str = "[datetime not initialized]",
                 tickMsInitiated: int = 0,
                 chunkSize: int = 16384): # 16 kb, capped to 264 kb RAM on standard PICO
        self.logFilename: str = logFilename
        self.logFileMaxSizeByte: int = logFileMaxSizeByte
        self.datetimeInitiated: str = datetimeInitiated
        self.tickMsInitiated: int = tickMsInitiated
        self.chunkSize: int = chunkSize
        
    def rotateLogFile(self, logPrefix: str, logFileSize: int, logDeleteMultiplier: float = 0.5) -> None:
        # Rotate logfile, removing the first portion (logFileSize * logfileDeleteMultiplier) of the log file.
        
        print(f"{logPrefix} Logfile size exceeds logFileMaxSizeByte ({logFileSize}/{self.logFileMaxSizeByte} bytes), triggered clean up...")
        tmpLogFilename = f"tmp_{self.logFilename}"
        tmpLogFileSize = 0
        skipBytes = int(logFileSize * logDeleteMultiplier)

        logFileEof = False
        for i in range(0, 999): # Using index i for chunks
            if(logFileEof or tmpLogFileSize > skipBytes):
                break
                
            chunk = ""
            print(f"{logPrefix} Cleaning up (logfile size {skipBytes + (chunkSize * i)}/{logFileSize} bytes)...")
            with open(self.logFilename, "rb") as readFile:
                readFile.seek(skipBytes + (chunkSize * i), 0)
                chunk = readFile.read(self.chunkSize)
                if not chunk: # EOF
                    chunk = readFile.read()
                    logFileEof = True
                    
            with open(tmpLogFilename, "wb+") as writeFile:
                writeFile.seek(0, 0)
                writeFile.write(chunk)
                tmpLogFileSize = writeFile.tell()
                
        uos.rename(tmpLogFilename, self.logFilename)
        # EOF messes with remove file for some reason, truncate file, then delete
        with open(tmpLogFilename, "w") as file:
            pass
        uos.remove(tmpLogFilename)
        
    async def log(self, message: str, logToFile: bool = True, doPrint: bool = True) -> None:
        # Print and log message in a given format.
        
        prefix = f"{self.datetimeInitiated} +{utime.ticks_ms() - self.tickMsInitiated}:"
        formattedMessage = f"{prefix} {message}"
        
        if(doPrint):
            print(formattedMessage)
            
        if(logToFile):
            if(not self.logFilename in uos.listdir()):
                with open(self.logFilename, "a") as file:
                    file.write("Created new logfile")
                    
            log = f"{formattedMessage}\n"
            logSize = len(log.encode("utf-8"))
            logFileSize = uos.stat(self.logFilename)[6]
            
            if((logFileSize + logSize + 10) > self.logFileMaxSizeByte):
                rotateLogFile(prefix, logFileSize)
                
            with open(self.logFilename, "a") as file:
                file.write(log)
