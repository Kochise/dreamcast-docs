Miscellaneous sample program -- DesktopCompat
-----------------------------------------

* Purpose:
This sample shows how to initialize directdraw, directinput and
directsound for both the destop and the katana.  If UNDER_CE is
defined, the code compiles in a full screen mode that can run both
on the desktop and the katana.  If UNDER_CE is not defined, 
however, the code runs on windowed mode.

The code displays an image on the screen.  Use the differnt input 
devices attached to your desktop or the dreamcast to move the
image around.  The sample recognizes the newly plugged
devices both under the dreamcast and the desktop environments.  
When the image hits the border of the screen, a sound is played.
Under the dreamcast, pressing the A button on the controller 
plays a sound.  Under the desktop, pressing the first button of any 
joystick plays a sound.  


* Required Files\Parameters:
None

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
