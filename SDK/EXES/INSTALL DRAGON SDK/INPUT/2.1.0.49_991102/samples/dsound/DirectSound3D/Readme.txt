DirectSound sample program -- DirectSound3D
-----------------------------------------

* Purpose:
This sample demonstrates how to use DirectSound3D.  It "moves" a sound around
the listener in a circle.

This sample allows the user to specify a particular audio source to play.  The 
source may be specified with a full pathname (ie "\windows\jump.wav"), or
it may be specified with just the filename (ie "jump.wav"), in which case
the sample will look for the file in <WCEDreamcastSDK>\release\(retail/debug)\Samples.
The file "jump.wav" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage:   s DirectSound3D <WAV filename>

Example: s DirectSound3D jump.wav
Example: s DirectSound3D \PC\Samples\jump.wav


* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
