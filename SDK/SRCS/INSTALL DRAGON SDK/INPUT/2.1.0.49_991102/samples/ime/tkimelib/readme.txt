Tankanji IME sample library version -- tkimelib.lib
---------------------------------------------------

* Purpose

This directory contains code for a sample library that 
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

* Notes

In order for this sample to work, you must set the
environment variable IMGTKIME=1, and then rebuild your image
with "makeimg".

The IME defaults to a simple English-only stripped version for 
use with the sample browser (htmlsamp). To use Japanese, you will 
need to set KANJI=1 when building this library.

This sample only builds for Windows CE.  Do not attempt to
build for Windows 95 ... it won't work due to lack of Unicode
support on that platform.

This library is not an application, so you will need to create
an EXE to use it. See the htmlsamp sample that incorporates the
use of this IME (in the htmlsamp, you will also need to set 
KANJI=1 if you want Japanese).

* Known issues

The IME mode indicator doesn't always display properly when
in English mode. This is because English mode changes are
not preserved as the IME is toggled on and off.

The henkan key does not allow the user to scroll through the
candidate list. Also, scrolling through the candidate list
with the spacebar does wrap around the bottom of the list.

