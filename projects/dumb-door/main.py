import uasyncio
from dumbDoor import DumbDoor

door = DumbDoor()
uasyncio.run(door.run())