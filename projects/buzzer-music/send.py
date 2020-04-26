import serial
import time

ser = serial.Serial(port = "COM4", baudrate = 9600, timeout = 1)

while 1:
    # ad = ser.read()
    # print(ad)
    time.sleep(1)
    ser.write("4".encode())
    print(ser.read())

quit()