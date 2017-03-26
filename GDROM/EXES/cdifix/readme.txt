
CDIfix 0.3a (C) 2000 by DeXT

http://cdirip.cjb.net


** Warning! Please make a backup copy of your CDI image before using this! **


History:
--------

 0.3a
  - Fixed a bug that prevented some special type images for being fixed
    (three or more contiguous short tracks at the very start of the image)
  - Improved error detection
 0.3
  - Open File dialog and Error Message Boxes (simply double click to use it)
  - added CDI v3.0 support
  - rewritten steal engine (again), now does multiple passes
  - tracks smaller than 300 sectors (i.e. 150 sectors) can now be fixed
  - any number of contiguos "short" tracks are now supported
 0.2
  - completely rewritten steal-logic engine
 0.1 beta3
  - internal release
 0.1 beta2
  - major bugfix (LBAs weren't changed)
 0.1 beta
  - didn't work properly (sorry)


Purpose:
--------

This program is intended for people having trouble when trying to record
certain CDI images with some recorders which doesn't support "short" tracks.
Errors vary from "Illegal field in command descriptor block" or "Buffer
underrun" messages, to bad LBA burned CD with no ISO track at all. This is
valid also for CDI images being converted with tools like CDIrip or CDI2nero.

After some research I've found that some recorders can't write tracks with
less than 302 sectors, and there are some CD images that has 300 sectors or
less sized tracks. These burners won't be able to burn those images. Some of
them are: Mitsumi, Ricoh, Iomega, Waitec, some Philips and HP 7100/7200/8250,
Sony CRX-120... etc.

This little utility does a very simple thing which will allow those recorders
to burn these images with no problems: it will enlarge those short tracks up
to 302 sectors by stealing sectors from a contiguous track. This way total
image size won't change.

But be aware this program has some limitations:

- Only Audio tracks are supported

- Single audio track images cannot be fixed

From 0.3 onwards any number of contiguous "short" tracks are supported, this
is achieved thanks to a new multi-pass stealing engine. However, at least it
is required that total first session lenght containing audio tracks is large
enough so all "short" tracks can be fixed (i.e. there must be at least one
"long" track from where stealing sectors).


Usage:
------

The usage is very simple, just do a double clic to it and an Open File dialog
will appear, then select your CDI image to be fixed.

You can also use it from command-line, i.e. write the name of the image next
to the program's name, just like CDIrip:

cdifix image.cdi

Finally, you can also drag-and-drop your CDI image file over CDIrip's main
executable file.

It will then start scanning image. If a short track is found, it will try to
fix it by changing its size and stealing sectors from a contiguous track.

If any error is found the program will simply stop and show an error message.
If everything is fine, once all tracks are fixed it will end with an "Image is
now fixed!" message and hopefully now you can burn your CDI image with no
problems!

Please be aware that this program will alter your CDI image! So make a backup
copy before fixing it for security reasons.


That's all. Hope you like it.

DeXT

