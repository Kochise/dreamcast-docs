MapleDevices sample program -- VMU_Flash
-----------------------------------------

* Purpose:
This sample demonstrates how to modify the contents of a flash
device.  It can dump the contents of a flash device, Format a
flash device, or copy from one flash device to another.

* Required Files\Parameters:
Usage: VMU_Flash [Action]
-?       This output
-D       Dump Flash Devices.  Dumps contents of all connected
         flash devices to the debugger
-F       Format Flash Devices.  Formats all connected flash devices
-C       Copy Flash devices.  For each controller that is connected,
         if there are two flash devices connected to it, then copy
         the contents from the device in connection 2 to the device
         in connection 1

* This sample exits automatically.