DirectSound sample program -- StreamingSound
-----------------------------------------

* Purpose:
This sample demonstrates how to play streaming wav files from the image.

This sample allows the user to specify a particular audio source to play.  The 
source may be specified with a full pathname (ie "\windows\longtest.wav"), or
it may be specified with just the filename (ie "longtest.wav"), in which case
the sample will look for the file in <WCEDreamcastSDK>\release\(retail/debug)\Samples.
The file "longtest.wav" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage:   s StreamingSound <WAV filename>

Example: s StreamingSound longtest.wav
Example: s StreamingSound \PC\Samples\longtest.wav

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
