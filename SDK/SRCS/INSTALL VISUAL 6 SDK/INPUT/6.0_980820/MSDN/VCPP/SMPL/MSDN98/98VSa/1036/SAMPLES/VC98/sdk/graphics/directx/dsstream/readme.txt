DirectSound Streaming Test (dsstream)
-------------------------------------

This sample illustrates how to play a long sound using a streaming
DirectSoundBuffer.  Because of this design, it may not work correctly when
using very short sounds, like only 1 or 2 seconds long.  Those files are 
more appropriate for static buffers; see DirectSound Mixing Test (dsshow)
for examples of how to code such buffers.

Open a .wav files using the File.Open dialog.  The UI of the sample only
allows you to open one file at a time; however, this is a limitation of the
sample, not a limitation of DirectSound.

There are buttons to Play and Stop the file, and a checkbox to indicate
whether the file should be looped or not.  Regardless of the checkbox,
the DirectSoundBuffer will be played with looping since a streaming buffer
is being used.

There are sliders to control the sound's frequency, pan, and volume settings.
In addition, there is a slider indicating the progress through the sound
data.

The last thing to know: you can toggle Options.Enumerate Drivers, which
will show you what objects DirectSoundEnumerate will list for you, and allow
you to select one.  This only happens when you start up Dsstream, so to see
the effect, select this menu item, exit Dsstream, and then run Dsstream
again.

