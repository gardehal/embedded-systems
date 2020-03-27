# 12-Step Led Clock

A clock consisting of 24 leds, the left columns represents hours, one hour per step, while the right columns represent minutes, 5 minutes per step.

Originally I had planned to do 2 columns, and have an indicator for AM/PM, but ran out of pins. I could have charlieplexed with more pins, doing 2 clusters of 12 leds would only have cost me 8 pints total, leave plenty for other features, but the complexity was already fairly high and I doubt I have the wires for that.

Due to lack of resistors, pins 2 and 13 have two 220 Ω resistors in parallel which result in halving the resistors Ohm value (220 Ohm devided by 2 resistors = 110 Ohm). If one have the resourses, one could use a single 100 Ω resistor for both instances.
 
[Code](./12-step-led-clock.ino)
 
Note that the video is **not** sped up, but that the delay time is altered (1 minute = 1 second). The video start at the time 00:00.

[Video, Part 1](./12-step-led-clock-1.mp4)
[Video, Part 2](./12-step-led-clock-2.mp4)
 
## Circuit Diagram
 
![Circuit Diagram](./12-step-led-clock.png)

## Led Grid

| Y\X | X0 | X1 | X2 | X3 |
| --- | --- | --- | --- | --- |
| Y5 | 0, 5 | 1, 5 | 2, 5 | 3, 5 |
| Y4 | 0, 4 | 1, 4 | 2, 4 | 3, 4 |
| Y3 | 0, 3 | 1, 3 | 2, 3 | 3, 3 |
| Y2 | 0, 2 | 1, 2 | 2, 2 | 3, 2 |
| Y1 | 0, 1 | 1, 1 | 2, 1 | 3, 1 |
| Y0 | 0, 0 | 1, 0 | 2, 0 | 3, 0 |