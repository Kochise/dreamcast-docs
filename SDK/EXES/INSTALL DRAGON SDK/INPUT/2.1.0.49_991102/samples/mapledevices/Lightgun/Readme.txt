MapleDevices sample program -- LightGun
-----------------------------------------

* Purpose:
This sample demonstrates how to handle the lightgun in a WinCE for
Dreamcast application.  Multiple lightguns can be used simultaneously.
The sample draws a small object on the screen at the last point that each
lightgun was pointing at when the lightgun's trigger was pulled.

Press the 'B' button on a controller to calibrate the controller.

Note - If you have a non-lightgun controller attached, the sample will 
display 'Not Gun' on the screen.  If there is no controller at all on a port,
then it will display 'No Input'.  If a keyboard is attached and then 
subsequently removed, the on-screen status for that port will stick at 'Not
Gun' (rather than reverting to 'No Input') because of the way DInput works -
device addition/removal is only recognized when the device is polled.  Since
the keyboard is not polled, the sample can't tell that the keyboard was 
removed.  This will not affect the normal flow of applications.

* Required Files\Parameters:
None

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
