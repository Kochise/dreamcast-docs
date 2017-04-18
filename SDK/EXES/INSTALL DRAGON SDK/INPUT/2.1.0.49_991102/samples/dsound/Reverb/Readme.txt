DirectSound sample program -- Reverb
-----------------------------------------

* Purpose:
This sample demonstrates how to use Reverb effects when playing sounds.
It loads a WAV file from the specified file. The wav file is played twice 
without the DSP effect, and then twice with the DSP effect, and then exits.

This sample allows the user to specify a particular audio source to play.  The 
source may be specified with a full pathname (ie "\windows\jump.wav"), or
it may be specified with just the filename (ie "jump.wav"), in which case
the sample will look for the file in <WCEDreamcastSDK>\release\(retail/debug)\Samples.
The file "jump.wav" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage:   s Reverb <WAV filename>

Example: s Reverb jump.wav
Example: s Reverb \PC\Samples\jump.wav

* This sample exits automatically.
