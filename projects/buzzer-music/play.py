import os
import sys
import serial
import time
import unicodedata

melodiesArgs = ["-melodies", "-m", "-songs", "-s"]
helpArgs = ["-help", "-h"]

class Main:
    def main():            
        argC = len(sys.argv)
        argIndex = 1
        while argIndex < argC:
            arg = sys.argv[argIndex].lower()
            print("arg: " + str(sys.argv[argIndex]))

            # List contents of melodies directory
            if(argC < 2 or arg in melodiesArgs):
                Main.PrintMelodies()

                argIndex += 1
                continue

            # Print help
            if(arg in helpArgs):
                Main.PrintHelp()

                argIndex += 1
                continue

            # If else - argument was not a flag defined above, check for int or default to search string
            # Play song by index (see -melodies flag)
            if(Main.IsInt(arg)):
                # select song and play
                print("int")

                argIndex += 1
                continue

            # Play song by similar input song name
            if(type(arg) is str):
                # select song and play
                print("str")

                argIndex += 1
                continue
            
    def GetFullFilePath(dirName, fileName = None):
        """
        A method for getting the full path from root file the script is called from and a sub-directory with optional file. \n
        string dirName \n
        string fileName(optional)
        """

        appendPath = dirName
        if(fileName != None):
            appendPath = os.path.join(dirName, fileName)

        return os.path.join(sys.path[0], appendPath)
        
    def Play():
        ser = serial.Serial(port = "COM4", baudrate = 9600, timeout = 1)

        while 1:
            time.sleep(1)
            # ser.write("A".encode()) # Unicode A = 65
            val = "\u0041"
            # val = "\u028A"
            enc = val.encode()
            print(val)
            print(enc)
            print("---")
            ser.write(enc)

    def PrintMelodies():
        """
        A simple console print of songs in the melodies folder.
        """

        print("--- Melodies ---")
        
        a = os.listdir(Main.GetFullFilePath("melodies"))

        if(len(a) < 1):
            print("No melodies found. See README.md for guide to add melodies.")
            return

        for filename in a:
            print(filename)

    def PrintHelp():
        """
        A simple console print that informs user of program arguments.
        """

        print("--- Help ---")
        print("Arguments marked with ? are optional.")
        print("All arguments that triggers a function start with dash(-).")
        print("All arguments must be separated by space only.")
        print("To submit sentences with spaces between words, use quotation marks (\", \'), otherwise they will be counted as separate arguments.")
        print("\te.g.: $ python todo.py -add \"This is a sentence.\"")
        print("\n")

        print(str(melodiesArgs) + ": prints a list of melodies available.")
        print(str(helpArgs) + ": prints this information about input arguments.")
        print("int" + ": plays the song with number..........") # TODO
        print("string" + ": searches songs for similar name ............") # TODO

    def IsInt(s):
        try: 
            int(s)
            return True
        except ValueError:
            return False

if __name__ == "__main__":
    Main.main()




### Plan
# 1. read array of files from molodies folder
# 2. pick melody (can also be done with arguments)
# 3. print melody name? and set beat
# 4. read array of notes and beats
# 5. for each send note with corresponding beat (preload notes then send beats? preload both beats and notes?)
#       - Send notes as Unicode characters, format: decimal (of note or beat) -> hex -> ser.write("\u[hex]".encode()) https://unicode-table.com/en/ https://www.calculator.net/hex-calculator.html or lib
# 6. read beat = 0 to finish melody

# Arduino awaits any input;
# Input from serial: start serial code to play from incoming serial data
# Button press or afer a set timeout, play song from melody folder using old code

# Python terminal aways commands to start;
# With no arguments, prompt argument help print, then play from melody folder in order
# With integer argument, play index that corresponds with melody
# With string argument, search for song name that contains input args
# Print help for overvoew of arguments implementerd
# Print ordered list of songs in folder, with index (ex. "1 - Twinkle Twinkle Little Star\n" etc.)