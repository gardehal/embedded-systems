import os
import sys
import serial
import time
import unicodedata
import re

import melody

melodiesArgs = ["-melodies", "-m", "-songs", "-s"]
helpArgs = ["-help", "-h"]
initializeArgs = ["-initialize", "-init", "-i"] # add to help print

class Main:
    def Main():     
        """
        Main function. Parses arguments from terminal and executes relevant code.

        array of any sys.argv
        """       

        argC = len(sys.argv)
        argIndex = 1
        while argIndex < argC:
            arg = sys.argv[argIndex].lower()
            print("arg: " + str(sys.argv[argIndex]))

            # List contents of melodies directory
            if(argC < 2 or arg in melodiesArgs):
                Main.PrintAllMelodies()

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
                melodies = Main.GetMelodies()
                if(int(arg) < 1 or int(arg) > len(melodies)):
                    print("Selected song is out of range of song list, must be 1 - " + str(len(melodies)))
                    argIndex += 1
                    continue

                fn = melodies[int(arg) - 1]
                m = Main.LoadPyMelody(Main.GetFullFilePath("melodies", fn))
                Main.PlayMelody(m)

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
        A method for getting the full path from root file the script is called from and a sub-directory with optional file.

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

    def LoadPyMelody(filepath):
        """ 
        Reads the filepath.h file and translates to python version of melody.

        string filepath
        """
        name = ""
        notes = []
        beats = []
        tempo = 0
        
        f = open(filepath)
        lines = f.readlines()
        i = 0

        # print(lines[len(lines) - 1]) # .h melody class declaration

        for line in lines:
            if(line.find("=") >= 0): # Get assignment of a variable
                if(line.split("=")[1][0:1] is "{" or line.split("=")[1][1] is "{"): # Get assignment of arrays
                    if(line.split("=")[0].lower().find("note") >= 0): # Get note array declaration
                        notesVals = Main.GetArrayFromFileLines(lines[i:], False)

                        # melody file only contains variables in 
                        notesH = open("notes.h")
                        for noteVal in notesVals:
                            if(noteVal is "0"): # Skip looking for 0 notes (pause/no note)
                                notes.append(int(noteVal))
                                continue

                            notesH.seek(0)
                            for hLine in notesH:
                                hLineArr = re.split("\s+", hLine)
                                hName = hLineArr[1]
                                hVal = hLineArr[2]

                                if(noteVal == hName):
                                    notes.append(int(hVal))
                        
                        notesH.close()
                            
                    if(line.split("=")[0].lower().find("beat") >= 0): # Get beats array declaration
                        beats = Main.GetArrayFromFileLines(lines[i:], True)
                    
                if(line.split("=")[0].lower().find("tempo") >= 0): # Get tempo int declaration
                    tempo = line.split("=")[1].strip().replace(";", "")

                if(line.split("=")[0].lower().find("name") >= 0): # Get name string declaration
                    name = line.split("=")[1].lstrip().replace(";", "").replace("\"", "")
                    
            i += 1
        
        f.close()

        Main.PrintS("notes: ", len(notes))
        Main.PrintS(notes)
        Main.PrintS("beats: ", len(beats))
        Main.PrintS(beats)
        Main.PrintS("tempo")
        Main.PrintS(tempo)
        Main.PrintS("name")
        Main.PrintS(name)
        m = melody.Melody(name, notes, beats, tempo)
        return m

    def GetArrayFromFileLines(fileLines, parseInt):
        """
        Gets an array from array of string fileLines. fileLines should start at array declaration, as it will read untill the first ;

        array of string fileLines
        boolean parseInt 
        """
        array = []
        i = 0
        while 1: # Continue until the current lines has a ; (end of code line)
            tempLine = fileLines[i]
            if(tempLine.find("{") >= 0):
                tempLine = tempLine.split("{")[1]
            if(tempLine.find("}") >= 0):
                tempLine = tempLine.split("}")[0]

            values = tempLine.split(",")

            for value in values:
                if(value.find("#") >= 0 or value.find("//") >= 0): # Ignore comments
                    continue

                v = value.strip()
                if(len(v) > 0): # Ignore empty values
                    if(parseInt):
                        array.append(int(v))
                    else:
                        array.append(str(v))

            if(fileLines[i].find(";") >= 0):
                break
            i += 1

        return array

    def PlayMelody(melody):
        """
        Plays Melody melody by sending unicode characters over serial (USB) to Arduino that's is listenening, configured after buzzer-melody.png and running buzzer-melody.ino code.

        Melody melody
        """
        tempo = int(melody.tempo)
        tempoInSeconds = tempo / 1000
        notes = melody.notes
        beats = melody.beats
        Main.PrintS("Now playing: \n\t", melody.melodyName)
        
        ser = serial.Serial(port = "COM4", baudrate = 9600, timeout = 1)

        notesLen = len(notes)
        print("Playing")
        print("tempo")
        print(tempo)
        print("tempo s")
        print(tempoInSeconds)
        i = 0

        print("TODO play Melody")
        # sollution: send a string of 0000@0000 to serial, python uses substring but can use @ as delim later:
        ser.write("0650@1000".encode()) # Plays note 650 for 1000 ms, rememper to sleep for that time to avoid trying to play multiple tones at once 
        
        while 1:
            Main.PrintS(" --- ", i, "/", notesLen, " --- ")
            if(i == notesLen):
                break

            time.sleep(tempoInSeconds)
            print(tempoInSeconds)
            data = str(notes[i]).zfill(4) + "@" + str(beats[i] * tempo).zfill(4) # zFill adds leading zeros until the length of the string is argument, in this case 4. Format "xxxx@yyyy"
            print(data)
            Main.SendToSerial(ser, data)
            # time.sleep(float(float(beats[i]) * float(tempoInSeconds)))
            time.sleep(0.9) # Timing issues, can't send more frequently than 1000 ms? doesn't seem to ahve anything to do with serials timeout
            print("end")
            i += 1

        Main.PrintS("Finished playing: \n\t", melody.melodyName)

        # TODO
        # 0. Print "now playing.. x"
        # 1. use python time.sleep(y) where y is the seconds-version of tempo, need to translate first 
        #       - Tempo seems to bethe pause between the notes, beats is the multiplication of tempo, ie. tempo 100 and beat 10 means note will be played for 10 * 100 ms = 1000 ms = 1 second, with a 100 ms pause before and after
        # 2. get unicode characters for note and beat
        # 3. send note
        # 4. send beat
        # 5. repeat for notes and beats
        # 6. send 0 as beat to end? special char?
        # NB: Arduino code must understand that 2 serial values are needed to make a sound

    def SendToSerial(ser, data):
        """
        Send data to serial port using PySerial.
        """        
        # ser = serial.Serial(port = "COM4", baudrate = 9600, timeout = 1) # serial initiation "restarts" Arduino board

        encoded = data.encode()
        ser.write(encoded)

    def PrintAllMelodies():
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

    def PrintS(*params):
        """
        Format all parameters *params as string in print() so there's no need to surround everything with str().

        splat params
        """

        s = ""
        for p in params:
            s += str(p)

        print(s)

    
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
        
        f.close()
        w.close()
            
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