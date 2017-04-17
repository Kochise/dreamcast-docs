DirectSound sample program -- PlaySound
-----------------------------------------

* Purpose:
This is a basic DirectSound application.  It loads a WAV file from the specified
file and plays it through the Dreamcast.  It supports both mono and stereo wav files.

This sample allows the user to specify a particular audio source to play.  The 
source may be specified with a full pathname (ie "\windows\jump.wav"), or
it may be specified with just the filename (ie "jump.wav"), in which case
the sample will look for the file in <WCEDreamcastSDK>\release\(retail/debug)\Samples.
The file "jump.wav" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage:   s PlaySound <WAV filename>

Example: s PlaySound jump.wav
Example: s PlaySound \PC\Samples\jump.wav

* This sample plays the wav file once, and then exits.
