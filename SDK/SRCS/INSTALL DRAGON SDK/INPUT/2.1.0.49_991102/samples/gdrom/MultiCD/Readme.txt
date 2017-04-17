GDROM sample program -- MultiCD
-----------------------------------------

* Purpose:
This sample demonstrates how to handle multiple-CD titles.  It
sets WinCE up to notify the application via a WM_DEVICECHANGE when
the GD-ROM drive door has opened or closed.

This is done via 'DeviceIoControl()' and 'IOCTL_SEGACD_SET_DOOR_BEHAVIOR'.
See the 'AppInit' function to see how to use this.  The message handling
is done in the 'WndProc' function.

To use this sample, open and close the GD-ROM drive on your katana, and
status information should be output to the debugger.

* Required Files\Parameters:
None

* Note: You must place a GD-ROM or CD-ROM in your Katana, or the 
IOCTL_SEGACD_SET_DOOR_BEHAVIOR DeviceIoControl function will return 
"ERROR_NO_MEDIA_IN_DRIVE".

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
