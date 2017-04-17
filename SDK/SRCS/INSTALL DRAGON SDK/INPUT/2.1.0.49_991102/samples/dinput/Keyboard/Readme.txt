DirectInput sample program -- Keyboard
-----------------------------------------

* Purpose:
This sample shows how to read data from the Keyboard using WinCE for Dreamcast.
It has simple textbox functionality that demonstrates how to queue up key
presses and handle them in an app.

Note: DirectInput on WinCE for Dreamcast is not intended to be used for
standard text entry;  It is more targeted at handling cursor key and other 
sparse input.  If an application requires text entry via the keyboard, then
it is strongly recommended that they use the standard Windows messaging
approach (ie WM_CHAR, WM_KEYDOWN).


* Required Files\Parameters:
None

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
