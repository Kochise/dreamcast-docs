MIDI sample program -- Format1
-----------------------------------------

* Purpose:
This is a demonstration of how to play Format 1 SMF MIDI files on
a Dreamcast machine.  The actual MIDI playing techniques are essentially
the same as for the PlayMIDI sample.  What this sample demonstrates is
how to convert a Format 1 sequence into a single Format 0 track that
the Dreamcast hardware sequencer is capable of playing.

This application has no user interface, and does not create a window.  It simply
initializes the necessary MIDI objects, converts and plays one or more MIDI 
sequences (as given on the command line), and exits.

Note: Because Dreamcast supports Standard MIDI File format sequences
natively, this sample demonstrates how to load and play a Standard
MIDI File format sequence without converting into the standard
Windows MIDIEVENT format.  Standard Windows operating systems (any
other version of WinCE, Windows 95/98/NT) support only the Windows
MIDIEVENT format for MIDI data.

This sample allows the user to specify a particular MIDI file to play.  The 
source may be specified with a full pathname (ie "\windows\demomidi.mid"), or
it may be specified with just the filename (ie "demomidi.mid"), in which case
the sample will look in <WCEDreamcastSDK>\release\(retail,debug)\Samples.
The file "demomidi.mid" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage:   s Format1 <MIDI filename>"  

Example: s Format1 demomidi.mid
Example: s Format1 \PC\Samples\demomidi.mid

* This sample exits automatically after performing the specified 
functionality.
