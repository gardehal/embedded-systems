# Camera Platform

Small platform for a web camera which can pan (360 degrees) and tilt (120 degrees). 
Related to [3D printed Camera Platform project](https://github.com/gardehal/3d-printing/tree/main/created/camera-platform).

> [!NOTE]
> Work in progress

## TODO

- 3D designs
- Documentation
- Python code
- Buy parts
  - Check part compatability, small stepper motors and (already bought) drivers
- PCB layout - 12v from wall charger into Pico and motors, pico and controls into drivers into motors, status LED, on/off

## Circuit Diagram

![Circuit Diagram](./circuit-diagram-01.png)

## Part list
TODO

## Setup guide

## Assembly

## Useful links

- PICO with VS Code IDE - https://youtu.be/O6lkYTfcMEg
- Basic PICO W internet connection - https://www.tomshardware.com/how-to/connect-raspberry-pi-pico-w-to-the-internet
- MicroPython async - https://www.youtube.com/watch?v=5VLvmA__2v0
- PICO sheet - https://datasheets.raspberrypi.com/picow/pico-w-datasheet.pdf
- PICO server - https://www.raspberrypi.com/news/how-to-run-a-webserver-on-raspberry-pi-pico-w/
- Using 28BYJ-48 Stepper motor without 5-pin driver - hhttps://www.youtube.com/watch?v=OH4L3VHq5e0

## VS Code IDE

- Extensions:
    - MicroPico (formerly name Pico-W-Go and Pico-Go)
- Workflow:
    - Connect PICO with Data USB cable
    - Right click file > Run current file on Pico
    - Test functionality
    - Ctrl+C, X + Enter (abort current program)
    - Ctrl+Shift+P + "MicroPython: Reset > Soft" (soft reset machine)

## Retrospect

#### Good

#### Bad
