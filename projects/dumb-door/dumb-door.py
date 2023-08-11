import picozero
import time
import network
import machine
import urequests

import secrets
from lockStatus import lockStatus

# TODO motor, button, on/off switch?, getting call over internet to lock/unlock

rgb = picozero.RGBLED(red = 1, green = 2, blue = 3)
rgb_off = (0, 0, 0)
rgb_white = (255, 255, 255)
rgb_red = (255, 0, 0)
rgb_green = (0, 255, 0)
rgb_blue = (0, 0, 255)

doorStatus = lockStatus["unknown"]

def connectWlan():
    # Connect to WLAN using secrets from secrets.py file.
        
    rgb.color = rgb_blue
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    print([_[0] for _ in wlan.scan()])
    
    wlan.connect(secrets.ssid2g, secrets.password)
    while wlan.status() < 1:
        print(f"Waiting for connection... Last status: {wlan.status()}")
        
        blink(rgb_blue)
        
    ip = wlan.ifconfig()[0]
    print(f"Connected on IP: {ip}")
    return ip

def blink(ledColor: tuple, sleepSeconds: number = 0.8):
    # Blink LEDs off then to given ledColor, sleeping for given sleepSeconds.
    
    rgb.color = rgb_off
    time.sleep(sleepSeconds)
    rgb.color = ledColor
    time.sleep(sleepSeconds)
    
def toggleLock():
    # Toggle lock, opening if status is locked, locking if status is open.
    
    if(doorOpen):
        rgb.color = rgb_red
    else:
        rgb.color = rgb_green
    
def toggleLockStatus():
    # Toggle lock status only, not the physical door lock. Green LED = locked, red LED = open.
    
    if(doorOpen):
        rgb.color = rgb_red
    else:
        rgb.color = rgb_green
    
try:
    # Signal startup and connect to WLAN
    blink(rgb_white)
    ip = connectWlan()
    
    # Pico connected to WLAN but IP was 0.0.0.0, run infinite loop until reset or fixed
    if(ip[0] == '0'):
        while 1:
            blink(rgb_red)
            
    # Signal connect OK, default to locked state and wait for calls to toggle lock over WLAN or though button
    rgb.color = rgb_green
    doorStatus = lockStatus["locked"]
    print(doorStatus)
        
except KeyboardInterrupt:
    print(f"An error occured, resetting machine")
    machine.reset()