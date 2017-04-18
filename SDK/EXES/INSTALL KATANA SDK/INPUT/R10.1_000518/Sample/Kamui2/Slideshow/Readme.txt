SlideShow by Sandeep Singh Bisla at SEGA-Europe. 
Program: Add PVR files to Slidelist.txt and watch them in a Slide Show with Dissolve
Zoom Transition, also accepts Stride Format PVRs. Includes a timer from 1 to 59
seconds for each image. just add a comma and number between 1 and 59 to get length
of pause in seconds. Default is 2 seconds if nothing entered. Program uses asynchronous
ADX streaming from the text file. Example for Slidelist.txt:

>mypvr.pvr, 3		

This will display mypvr.pvr for 3 seconds, if there is no comma and number then default
pause is used which is 2 seconds.

For audio support:
The first line of program has an audio field, if the user adds any ADX/WAV/AU/AIFF file
it will play (ADX files will loop continuously). Example:
>audio: sample.adx
If space is after "audio:" is left blank then no audio will play!
