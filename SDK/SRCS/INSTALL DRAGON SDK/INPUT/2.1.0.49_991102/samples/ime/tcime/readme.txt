TC IME sample -- tcime.exe
-----------------------------

* Purpose:
This directory contains code for a sample application that 
demonstrates how to use the Traditional Chinese Phonetic IME
to implement an IME user interface. This sample supports both
the Dreamcast English hardware keyboard, and also contains
an onscreen keyboard if the hardware keyboard is not
available.

On the gamepad when on-screen keyboard is active:
  A       Select key
  X       Backspace
  Y       Convert (won't do anything for TCIME)
  B       Confirm (won't do anything for TCIME)
  Start   Exit

On the gamepad when candidate list is active:
  A       Select key
  X       Cancel
  Y       Select key
  B       Cancel
  Start   Exit
  
On the hardware keyboard:
  Ctrl-Space    Toggled on/off IME.
  Shift-Space   Toggled Full/Half shape mode.

NOTE: In order for this sample to work, you must select 
Traditional Chinese IME under the "Fonts and Language" 
section of the Configuration Tool, and then rebuild your 
image.  Alternatively, from the command line environment, 
you can set the environment variable COUNTRY=CHT and 
IMGTCIME=1, and then rebuild your image with "makeimg".

* Required Files\Syntax:
None
