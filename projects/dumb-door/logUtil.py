import os
import utime
from machine import RTC

class LogUtil:
    logFilename: str = None
    logFileMaxSizeByte: int = None
    chunkSize: int = None
    rtc: tuple = None
    utcOffset: int = None
    
    def __init__(self,
                 logFilename: str,
                 logFileMaxSizeByte: int,
                 chunkSize: int = 16384): # 16 kb, capped to 264 kb RAM on standard PICO
        self.logFilename = logFilename
        self.logFileMaxSizeByte = logFileMaxSizeByte
        self.chunkSize = chunkSize
        self.rtc = RTC()
        self.utcOffset = 0
        
        if(not self.logFilename in os.listdir()):
            with open(self.logFilename, "a") as file:
                file.write(self.getFormattedLine("LogUtil init created a new logfile\n"))
        
    def rotateLogFile(self, logFileSize: int, logDeleteMultiplier: float = 0.5) -> None:
        # Rotate logfile, removing the first portion (logFileSize * logfileDeleteMultiplier) of the log file.
        
        prefix = self.getPrefix()
        print(f"{prefix}Logfile size exceeds logFileMaxSizeByte ({logFileSize}/{self.logFileMaxSizeByte} bytes), triggered clean up...")
        tmpLogFilename = f"tmp_{self.logFilename}"
        tmpLogFileSize = 0
        skipBytes = int(logFileSize * logDeleteMultiplier)

        logFileEof = False
        for i in range(0, 999): # Using index i for chunks
            if(logFileEof or tmpLogFileSize > skipBytes):
                break
                
            chunk = ""
            print(f"{prefix}Cleaning up (logfile size {skipBytes + (self.chunkSize * i)}/{logFileSize} bytes)...")
            with open(self.logFilename, "rb") as readFile:
                readFile.seek(skipBytes + (self.chunkSize * i), 0)
                chunk = readFile.read(self.chunkSize)
                if not chunk: # EOF
                    chunk = readFile.read()
                    logFileEof = True
                    
            with open(tmpLogFilename, "wb+") as writeFile:
                writeFile.seek(0, 0)
                writeFile.write(chunk)
                tmpLogFileSize = writeFile.tell()
                
        os.rename(tmpLogFilename, self.logFilename)
        # EOF messes with remove file for some reason, truncate file, then delete
        with open(tmpLogFilename, "w") as file:
            pass
        os.remove(tmpLogFilename)
        
    def getPrefix(self) -> str:
        # Get prefix for simple log line.
        
        return f"{self.nowUtc()}: "
        
    def nowUtc(self) -> str:
        # Convert rtc.datetime() into  UTC string.
        
        # (YYYY, MM, DD, w, hh, mm, ss, s)
        dt = self.rtc.datetime()
        # TODO could set and store as const, would need method to update self.utcOffset to also set this. Saves some computing speed for each log line
        direction = "+" if(self.utcOffset > 0) else "-"
        offsetString = "Z" if(self.utcOffset == 0) else f"{direction}{self.utcOffset:02}:00"
        return f"{dt[0]:02}-{dt[1]:02}-{dt[2]:02}T{dt[4]:02}:{dt[5]:02}:{dt[6]:02}{offsetString}"
    
    def getFormattedLine(self, message: str) -> str:
        # Get line used in simple logs.
        
        return f"{self.getPrefix()}{message}"
        
    def log(self, message: str, logToFile: bool = True, doPrint: bool = True, encoding: str = "utf-8") -> None:
        # Print and log message in a given format.
        
        formattedMessage = self.getFormattedLine(message)
        if(doPrint):
            print(formattedMessage)
            
        if(logToFile):
            log = f"{formattedMessage}\n"
            logSize = len(log.encode(encoding))
            logFileSize = os.stat(self.logFilename)[6]
            
            if((logFileSize + logSize + 10) > self.logFileMaxSizeByte):
                self.rotateLogFile(logFileSize)
                
            with open(self.logFilename, "a") as file:
                file.write(log)
