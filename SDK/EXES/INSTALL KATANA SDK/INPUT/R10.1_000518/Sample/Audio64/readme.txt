Audio64 Samples -- R10 Release
-------------------------------------------------------------------------------

Reflecting the internal changes to the Audio64 library, all of the existing
sample code has been reworked. The samples summaries are enumerated below.
New samples are noted.

A64Thunk (new)
--------------
The Audio64 library contains Audio64 hook functions that map (thunk) to
appropriate functions in the Shinobi library. If needed, these may be
overridden by explicitly including these modules (a64chain.c, a64dma.c,
a64file.c) in your object file list and substituting alternate support.

AcDsp
-----
The sample uses the AC layer to play a raw sound file with DSP effects.
Sound memory is manually allocated.

AcPlayMidi (new)
----------
The sample shows how to play a raw MIDI file.

AcPlaySound
-----------
The sample shows how to use the new filter and amplitude envelope commands, as well as
LFO commands.

AcTransfer (new)
----------------
The sample is a suggested setup for using AICA DMA for Audio64 transfers.
The focus here is very specific; this is essentially a DMA sample that
happens to access AICA memory and the AICA DMA.

AmAbuse
-------
The sample is an Audio64 potpourri (everything but the kitchen sink) of
the AM layer APIs used to stress test the library.

AmAbuseMidi
-----------
The sample is an Audio64 potpourri (including the kitchen sink) of the AM
layer APIs used to stress test the library.

AmPlayMidi
----------
The sample shows how to play MIDI from a bank, and sets MIDI callbacks.

AmStream (new)
--------------
This is a sample of a 4 stream AM layer setup where each stream plays one
"instrument" in the composition. It demonstrates the asynchronous stream
APIs.
