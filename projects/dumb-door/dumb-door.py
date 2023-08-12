import time

import network
import picozero
from machine import Pin, reset

import secrets  # Secret values in secrets.py

# TODO motor, button, on/off switch?, getting call over internet to lock/unlock, press+hold button to switch status without locking/unlocking door usage for correcting default state without having to force motor

rgb = picozero.RGBLED(red = 1, green = 2, blue = 3)
rgb_off = (0, 0, 0)
rgb_white = (255, 255, 255)
rgb_red = (255, 0, 0)
rgb_green = (0, 255, 0)
rgb_blue = (0, 0, 255)

button = Pin(14, Pin.IN, Pin.PULL_DOWN)

lockStatus = {"open": 0, "locked": 1}
doorStatus = lockStatus["locked"]

def connectWlan():
    # Connect to WLAN using secrets from secrets.py file.
        
    rgb.color = rgb_blue
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    print([_[0] for _ in wlan.scan()])
    
    wlan.connect(secrets.ssid, secrets.password)
    wlan.ifconfig(secrets.ipStruct)
    while wlan.status() < 1:
        print(f"Waiting for connection... Status: {wlan.status()}")
        blink(rgb_blue)
        
    ip = wlan.ifconfig()[0]
    print(f"Connected on IP: {ip}")
    return ip

def blink(ledColor: tuple, sleepSeconds: number = 0.5):
    # Blink LEDs off then to given ledColor, sleeping for given sleepSeconds between on/off.
    
    rgb.color = ledColor
    time.sleep(sleepSeconds)
    rgb.color = rgb_off
    time.sleep(sleepSeconds)
    
def toggleLock():
    # Toggle lock, opening if status is locked, locking if status is open.
    
    if(doorStatus == lockStatus["locked"]):
        # TODO activate motor ccw
        print("WIP")
    else:
        # TODO activate motor cw
        print("WIP")
        
    toggleLockStatus()
    
def toggleLockStatus():
    # Toggle lock status only, not the physical door lock. Green LED = locked, red LED = open.
    
    if(doorStatus == lockStatus["locked"]):
        rgb.color = rgb_green
    else:
        rgb.color = rgb_red

def main():
    try:
        # Signal startup
        await blink(rgb_white)
        
        if(1):
            ip = connectWlan()
            # Run infinite loop until reset or fixed
            if(ip[0] == '0'):
                print("PICO connected to WLAN but IP was 0.0.0.0")
                while 1:
                    await blink(rgb_red)
                
        # Signal connect OK, default to locked state and wait for calls to toggle lock over WLAN or though button
        while 1:
            blink(rgb_green, 2)
            # TODO check status, blink async
            
    except KeyboardInterrupt:
        print(f"An error occurred, resetting machine")
        reset()
        
main()
