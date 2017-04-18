MapleDevices sample program -- VMU_LCD
-----------------------------------------

* Purpose:
This sample demonstrates how to draw things on the LCD screen of a VMU
device.  It includes simple "Etch-a-Sketch" functionality which allows the
user to draw on the LCD screen using the buttons of the controller that it is
attached to.

The controls are:
Directional Pad:    Move the cursor
'A' Button:         Clear the display
'B' Button:         Hold the Pen up while moving
<ESC>:              Quit the app (Pressed on the soft keyboard).

Note that for certain controllers, the VMU is actually inserted in the opposite
direction compared to other controllers; for instance, the lightgun and the
joystick each display the controller's LCD display in different orientations; this
sample accounts for this automatically.

Because the VMU is not accessed except when necessary, it is not always immediately
apparent on the on-screen display that something has changed.  The next time any
form of input occurs, the app notices that the VMU has been removed, and acts 
accordingly.

* Required Files\Parameters:
None

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
