import serial

ser = serial.Serial(port = "COM4", baudrate = 9600)

while 1:
    ad = ser.read()
    print(ad)