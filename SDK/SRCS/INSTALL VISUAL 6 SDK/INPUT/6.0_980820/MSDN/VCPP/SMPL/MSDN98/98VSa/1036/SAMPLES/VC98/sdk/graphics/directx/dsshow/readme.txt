DirectSound Mixing Test (dsshow)
--------------------------------

This app allows the user to play with most of the controls exposed by
DirectSoundBuffers, including the mixing of multiple sounds, and changing
frequency, pan, and volume of those sounds.

Open one or more .wav files using the File.Open dialog.  A control bar will
be displayed for each file opened.  Dsshow uses static buffers for its sounds
and is therefore designed for short sounds only.  If you try to open a file
that is very large, you will run out of system memory - beware!

The control bar for each sound contains a bunch of things.  First, the file
name is displayed at the top.  The next line states whether the buffer is
mixed in software (SW) or hardware (HW), and whether the buffer is playing
or stopped.  Dsshow will put buffers in hardware whenever possible.  On the
next two lines, the current play and write cursors are displayed.  They are
updated every half second or so.  Then there are sliders to control the
buffers frequency, pan, and volume settings.  At the bottom, there is a
Play/Stop button (it morphs back and forth, try it!) and a Close button (to
delete the file from the view), and a checkbox for Looping.

The dsshow title bar tells you information about the hardware mixing
capabilities of your sound card.  It displays the number of free hw mixing
channels and hw memory (if you have an ISA card like most people).  If both
of those numbers are 0, your card does not have hardware mixing.

There are also two interesting things you can do from the Options menu.
First, you can set the format of the primary buffer by selecting
Options.Output Type.  This will list the formats supported by the primary
buffer, and let you choose one.  Also, you can toggle Options.Enumerate Drivers
which will show you what objects DirectSoundEnumerate will list for you,
and allow you to select one.  This only happens when you start up Dsshow,
so to see the effect, select this menu item, exit Dsshow, and then run Dsshow
again.

