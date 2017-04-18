Tankanji IME sample -- tkime.exe
--------------------------------

* Purpose:
This directory contains code for a sample application that 
demonstrates how to use the Tankanji library to implement
an IME user interface.  This sample supports both the 
Dreamcast Japanese hardware keyboard, and also contains
an onscreen keyboard if the hardware keyboard is not
available.

On the gamepad:
  A       Select key
  X       Backspace
  Y       Convert or Space
  B       Determine (only in the Output Window)
  Start   Exit

NOTES: In order for this sample to work, you must select
TanKanji IME under the "Fonts and Language" section of 
the ConfigTool.

Alternatively, from the command line environment, you
can set the environment variables COUNTRY=JAPAN and 
IMGTKIME=1 and rebuild your image with makeimg.  If
you do this, make sure that the environment variable
IMGPIME is NOT set.

The keyboard does not know if the sample has been 
stopped and restarted, so it is possible for them to get
out of sync with each other.  If you run the sample once,
change the keyboard's mode (ie IME on, etc), and then exit 
the sample, the next time you run the sample the keyboard's 
mode will be different than what the sample thinks it is.
Unplugging and replugging the keyboard will guarantee that
the states are in sync.

* Required Files\Parameters:
None

* Limitations:
TKIME is a limited IME and does not support RKC in halfwidth
katakana.  For a more full-featured IME, you should use
PIME instead.