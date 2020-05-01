import os
import sys
import serial
import time
import unicodedata

import melody

melodiesArgs = ["-melodies", "-m", "-songs", "-s"]
helpArgs = ["-help", "-h"]
initializeArgs = ["-initialize", "-init", "-i"] # add to help print

class Main:
    def Main():            
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

            # Initialize
            if(arg in initializeArgs):
                if(argC - argIndex < 2):
                    print("Missing an argument: .h class path to initialize.")
                    argIndex += 1
                    continue

                filepath = Main.GetFullFilePath("", sys.argv[argIndex + 1])
                if(not os.path.exists(filepath)):
                    print("File does not exist: '" + str(filepath) + "'.")
                    argIndex += 2
                    continue

                Main.PyCopyHClass(filepath)

                argIndex += 2
                continue

            # If else - argument was not a flag defined above, check for int or default to search string
            # Play song by index (see -melodies flag)
            if(Main.IsInt(arg)):
                fn = Main.GetMelodies()[int(arg) - 1]
                m = Main.LoadPyMelody(Main.GetFullFilePath("melodies", fn))
                print("Now playing: \n\t" + arg + ": " + m)

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

    def GetMelodies():
        """
        Get a list of all melodies.
        """
        return os.listdir(Main.GetFullFilePath("melodies"))

    # def PlayMelody(melody):
    #     print(melody.)

    def LoadPyMelody(filepath):
        """ 
        Reads the filepath.h file and translates to python version of melody.
        string filepath
        """
        name = ""
        notes = []
        beats = []
        tempo = 0

        # For line
        # Find var declaration
        # match var name with assigned var name
        # If var is notes, get values after =
        # For each line in file until end var assignment ;
        # Split line on ", "
        # for notes only: lookup note var name and get int value in notes.h
        # if notes is found (optinal: and can be parsed to int)
        # add note to notes array
        # Skip non-note/non int values
        # optional save to file to avoid doing this again 
        
        f = open(filepath)
        lines = f.readlines()
        i = 0

        print(lines[len(lines) - 1])

        for line in lines:
            if(line.find("=") >= 0 and (line.split("=")[1][0] is "{" or line.split("=")[1][1] is "{")): # Get assignment of a variable
                if(line.split("=")[0].lower().find("note") >= 0): # Get note array declaration
                    
                    j = i
                    while 1: # Continue until the current lines has a ; (end of code line)
                        tempLine = lines[j]
                        if(tempLine.find("{") >= 0):
                            tempLine = tempLine.split("{")[1]
                        if(tempLine.find("}") >= 0):
                            tempLine = tempLine.split("}")[0]

                        values = tempLine.split(" ")

                        for value in values: # TODO lets some comments though, add // and # check before v?
                            v = value.split(",")[0]
                            if(v.find("#") < 0 and v.find("//") < 0 
                            and v.find("\n") < 0 and v.find("\t") < 0 
                            and len(v) > 0 and v != "0"): # Ignore comments or empty values
                                notes.append(v)

                        if(lines[j].find(";") >= 0):
                            break
                        j += 1
            i += 1

        print("notes")
        print(notes)
        # m = melody.Melody(name, notes, beats, tempo)
        return "WIP"


    def SendToSerial():
        """
        Send data to serial port using PySerial.
        """
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

        a = Main.GetMelodies()
        i = 0

        print("--- Melodies ---")

        if(len(a) < 1):
            print("No melodies found. See README.md for guide to add melodies.")
            return

        for filename in a:
            i += 1
            print(str(i) + ": " + filename)

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

        print(str(initializeArgs) + " + [string filename]: translates an Arduino class from the filename.h to a python class filename.h.")
        print(str(melodiesArgs) + ": prints a list of melodies available.")
        print(str(helpArgs) + ": prints this information about input arguments.")
        print("int" + ": plays the song with number..........") # TODO
        print("string" + ": searches songs for similar name ............") # TODO

    def IsInt(s):
        """
        Determine wether the string can be parse to int.
        string s
        """
        try: 
            int(s)
            return True
        except ValueError:
            return False
    
    def PyCopyHClass(filepath):
        """
        Copy a single Arduino OOP .h class in filepath to a simplified Python class.
        string filepath (relative to where code was called from) 
        """
        pyClassString = ""
        classname = ""

        with open(filepath) as f:
            for line in f:
                if(line.find("class", 0 , 5) is 0):
                    print(line)
                    pyClassString += ("\n" + line.rstrip() + ":")
                    classname = line.split(" ")[1].rstrip()
                    print("\tPyCopyHClass: Added class declaration.")
                if(line.find(classname + "(") >= 0):
                    print(line)
                    constructorDef = "\n\tdef __init__(self"
                    constructorBlock = ""
                    args = line.split("(")[1].split(")")[0].split(", ")

                    for argDef in args:
                        arg = argDef.split(" ")[1]
                        constructorDef += (", " + arg)
                        constructorBlock += ("\n\t\tself." + arg + " = " + arg)
                        print("\tPyCopyHClass: Added field: '" + str(arg) + "'.")

                    constructorDef += ("):")
                    constructor = constructorDef + constructorBlock
                    pyClassString += (constructor)
                    print("\tPyCopyHClass: Added constructor.")

        # print("pyClassString")
        # print(pyClassString)

        w = open(Main.GetFullFilePath(str(classname.lower())) + ".py", "w")
        w.write(pyClassString)
        
        # close(f)
        # close(w)
            
if __name__ == "__main__":
    Main.Main()




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