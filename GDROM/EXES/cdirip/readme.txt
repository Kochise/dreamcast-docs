
CDIrip 0.4 by DeXT

http://cdirip.freeyellow.com


*** Warning! See "2 sectors issue" below. Your may have got it! ***


Disclaimer
----------

Please note that this software is a generic-purpose tool, which must not be
used to duplicate Copyrigth-protected content. The user is only allowed to do
a legitimate use of it. I (the author) do not endorse any illegal use of this
software. This is provided for free, and comes without any kind of warranty.
The author will not be responsible for the consequences that may derive from
the proper or improper use of this software. Use it at your own risk.


What is this
------------

This is a small proggie capable of extracting all the tracks contained in a
CDI (DiscJuggler) v2.0 image. This can be very useful since many people has
trouble using this software because of its lack of support for many burners,
and there is no program that understands that type of image.

So this program will allow you to record the contents of a DiscJuggler image
with another CD-recording application. Any program that understands standard
WAV audio and ISO images will do the job, such as CDR-Win, cdrecord, WinOnCD
or Fireburner.


How do I use this
-----------------

If you don't like MS-DOS you can simply double clic CDIrip's icon and it will
ask you for a CDI image filename. With this method, options below cannot be
used, though.

As this is a command-line tool, you'll have to open a MS-DOS window if you
want to get the most from it. Basic syntax is:

cdirip image.cdi [options]

[brackets] mean optional. For example, you can open a MS-DOS window, then cd
to the directory where both image and CDIrip are located and type:

cdirip image.cdi

Where "image.cdi" is the image you want to extract (it can also be preceeded
by an optional path). There is support for long filenames inside so you can
use any dumb name for your image files. You don't need to write .CDI extension
since CDIrip will do it for you if needed.

There is a set of options which alters program behaviour. You have to type
them just after image filename (i.e.: cdirip image.cdi /option1 /option2):

/info    shows information about tracks found inside the image, without
         saving anything to hard disk

/iso     converts all Mode2 tracks to standard ISO/2048 format instead of
         default BIN/2336 for CD-XA Multisession discs (see below)

/bin     forces BIN format for every Mode2 track (even CD-Extra)

/raw     save audio tracks as RAW (LSB format) instead of WAV

/cut     cuts last 2 sectors of first track only

/cutall  cuts last 2 sectors of every track (can be combined with /cut)

/full    save full Data tracks (do not cut automatically - see below)

As an example, if you want to save info about an image into a text file you
can write in the command line:

cdirip image.cdi /info >info.txt

Once executed, the program will analyze the image and extract all the tracks
found inside it to the current directory. All audio tracks will be saved as
"TAudioXX.wav", where XX is the absolute track number. Data tracks are saved
as "TDataXX.iso". For CD-XA Multisession discs, all data tracks will be saved
as BIN/2336 format, with name "TDataXX.bin" (see below).

There is an option, "/iso", which forces ISO/2048 conversion to all data
tracks, just like CDIrip 0.3 did (this is only necessary for cdrecord).
Please note that in this case cuesheet will not be created for ISO tracks
because of the lack of support for Mode2/2048 tracks in both CDR-Win and
Fireburner.

While ripping, the program will show some data about the tracks being saved.
That is: track number, track type (Audio, Mode1 or Mode2), length (in sectors)
and the physical LBA where this track starts in the CD. The most important one
is the LBA of the last data track, just because in a Multisession CD, the
second session MUST start at the same exact number as shown by CDIrip for it
to work. So I'd recommend you write down that number for later use.

The program will also generate a cuesheet file named "TDisc.cue" with all
tracks found in the first session, along with proper PREGAP entries. Normally
only tracks from the first session will be included in the cuesheet, since
CDR-Win doesn't support cuesheets for second session. So data tracks in 2nd
and following sessions will be converted to ISO/2048 format and saved alone,
without entry in the cuesheet. These must be manually recorded with CDR-Win
specifying "MODE2" format (please read below).

There is a special case with CD-XA Multisession discs, where two cuesheets
will be generated, one for each session, and data tracks will be saved in
BIN/2336 format. This is intended for use with Fireburner since CDR-Win
doesn't seem to support this kind of CD. This can also be burned with cdrecord
or WinOnCD but first you'll have to use "/iso" option while extracting.

*** 2 sectors issue ***

From user reports, I've seen that some recorders (e.g. Mitsumi and others)
don't record properly short audio tracks (300 sectors): they all will get
increased 2 sectors in size when burned. This is catastrophic for Multisession
(including CD-Extra) CDs, since the total size of first session will also get
increased in 2 sectors and so it will push LBA of last data track 2 sectors
away from its original position, thus ruining the resulting CD.

From version 0.4 I have added a new option, "/cut", that can be used to solve
this issue. It will cut the last 2 sectors of the first track so you can burn
it correctly. But you'll have to find out if your burner needs this switch.
Some burners such as Mitsumi has been reported to have this issue.

There is a second issue with several recording applications such as cdrecord,
Fireburner or WinOnCD, where EVERY audio track will get increased 2 sectors in
size. So I've included a second option, "/cutall", which will cut last 2
sectors of EVERY track, so it should be used if you plan to use any of these
recording software.

Both "/cut" and "/cutall" options can be combined together, and this would
result in cutting 4 sectors from first track then 2 sectors from every other
track. This could be needed by certain users (Mitsumi and short audio tracks).
If you get "Illegal field in command descriptor block" error in DiscJuggler
while trying to record the original CDI image then you'll have to use CDIrip
with these two options together.

Finally, I've seen that every recording software out there tends to add 2
blank sectors at every data track's end. From version 0.4, CDIrip does
automatically cut data tracks in first session so them can be burned
correctly. If needed, this can be avoided with the "/full" option.


Could you give me some examples?
--------------------------------

Sure!

cdirip image.cdi               --> simplest way

cdirip image.cdi /info         --> show info only (sessions, tracks, LBA etc)

cdirip image.cdi /cut          --> cut FIRST track only

cdirip image.cdi /cutall       --> cut ALL tracks (for cdrecord and others)

cdirip image.cdi /full         --> save all data tracks full (don't cut)

cdirip image.cdi /iso          --> save all data tracks as ISO (like 0.3)

cdirip image.cdi /iso /full    --> (exact same behaviour as CDIrip 0.3)

cdirip image.cdi /cut /cutall  --> cut 4 sect from first track then 2 to rest

cdirip image.cdi /cutall /full --> cut audio tracks only (trick ;)


How does it works
-----------------

* Single Data or Audio CDs

It will save all data or audio tracks found along with proper cuesheet. This
can be directly loaded with CDR-Win.

 TDisc.cue (TData01.iso)

  or 

 TDisc.cue (TAudio01.wav, TAudio02.wav...)


* Mixed-mode CDs

Same as above, it will save first data track in Mode1/2048 format then audio
tracks, all in a single cuesheet. This can also be directly loaded and
recorded with CDR-Win with no problems.

 TDisc.cue (TData01.iso, TAudio02.wav, TAudio03.wav...)


* CD-Extra

Two sessions, first one with audio track(s) then second one with a data track
(usually in Mode2/2336 format). A cuesheet will be generated for FIRST session
containing audio tracks only. Data track in second session will be converted
to ISO/2048 format and saved separately so it can be loaded with CDR-Win and
recorded in second step, specifying MODE2 as track type (please read below).

 Tdisc.cue (TAudio01.wav, TAudio02.wav...)

  and

 TData03.iso (alone)


* CD-XA Multisession CDs

Two data tracks, both in Mode2/2336 (CD-XA) format. This is new behaviour
since 0.4 version so read carefully:

If this kind of CD is detected, CDIrip's normal behaviour will change and now
it will save all data tracks in BIN/2336 format. First data track will also be
cutted automatically to avoid the "2 sectors issue" stated above. Finally TWO
cuesheets will be generated, one for each session. This is intended to be
recorded with Fireburner since CDR-Win doesn't seem to support these kind of
CDs.

 TDisc.cue (TData01.bin)  (cutted) (can also contain audio tracks)

  and

 TDisc2.cue (TData02.bin)

You can avoid this behaviour specifying "/iso" option, then it will act
just like CDIrip 0.3, saving all data tracks as ISO format and without
cuesheets. This is intended to users which want to use cdrecord or WinOnCD for
burning.


How do I record them back
-------------------------

* Single Audio, Data and Mixed-mode CDs

Just load CDR-Win and then load the cuesheet generted by CDIrip. Now press
"Start Recording". Easy, isn't it? :)

Please note that Mixed-mode CDs, which have a data track then some audio
tracks, "Open New Session" checkbox shouldn't be checked single this is a
single session disc.


* CD-Extra

This kind of image has one or more audio tracks in the first session then a
data track on the second. Below are instructions for use with CDR-Win:

Step 1:

Load CDR-Win, push the "Record Disk" button, and then "Load Cuesheet". Load
the "TDisc.cue" file generated by CDIrip. Check the "Open New Session"
checkbox (leave the rest as default) and then press "Start Recording". This
will record the first session.

NOTE: If you cannot check the "Open New Session" checkbox at first step, your
burner is not properly supported by CDR-Win. Then you'll have to use a
different recording software (at least for the first session only). Users have
reported that Fireburner, cdrecord and WinOnCD works (and probably NTI
CD-Maker and Ahead Nero, too). But please note that you'll have to use "/cut"
or "/cutall" options with any of these software, because of the "2 sectors
issue" common to all these software.

Step 2 (optional):

Once recorded, you can check that the LBA for the second session is the
correct one, if you want to be sure. This is not neccesary althought
recommended. For that you'll need "cdrecord" package. Just type in the
command line:

cdrecord dev=0,1,0 -msinfo

Note that you could need to change device settings (0,1,0) according with your
recorder setup. See CDR-Win's "Devices and Settings" window for that info.

This command will show you 2 numbers (x,y). The second one MUST be the same
LBA value as shown by CDIrip in the last data track while ripping. If it is
not, it won't work (see "2 sectors issue" above).

You can also use ISObuster to test LBA of last data track, but this can be
done only after recording entire disc. Just load the disc into ISObuster,
click on the second session and look at the start sector value below.

Step 3:

If everything goes right, now you have to add the second session. Press the
"File Backup and Tools" button in main CDR-Win window. In Function choose
"Record an ISO9660 Image File", then add the ISO image. In Recording Options
select "MODE2" as Track Mode. You may want to deselect "Write Postgap" since
it writes additional 150 sectors after the data track, which are not needed.
All the remaining options should be leaved as default values (Finalize Session
must be checked). Finally, press "START" button.

That's it!

If CDR-Win didn't work for you, you can still use other software such as
Fireburner, cdrecord or WinOnCD, but you must extract all tracks with
"/cutall" option since these software needs it.

Fireburner: use the same method as described below for CD-XA Multisession
discs, but only for first session (for second one you still will have to use
CDR-Win or cdrecord).

cdrecord: use the following command lines (stuff between parentheses is for
multiple audio tracks only):

cdrecord dev=0,1,0 speed=4 -multi -audio TAudio01.wav (-audio TAudio02.wav...)

cdrecord dev=0,1,0 speed=4 -multi -xa1 TData01.iso

Note: if you choose RAW format for audio tracks then you'll have to add
"-swab" option (LSB support) to the command line.


* CD-XA Multisession

These kind of CDs have two data tracks, each one in a different session. This
can only be recorded with Fireburner, cdrecord and WinOnCD, AFAIK.

Fireburner: click on "Visual CUE burner / Binchunker", press right mouse
button and select "Load tracks from *.CUE". Load first cuesheet, then press
right mouse button again and select "Burn / Test Burn". In burning window
uncheck "Test Burn" and leave checked "Eject CD", "Multi-session" and "Close
Session". On Recording Method select "Track at Once (TAO)" and click OK. This
will record first session.

Once recorded go to Visual CUE window again, right-click and select "Clear CD
Layout". Then repeat the same method for second cuesheet.

cdrecord: extract tracks with "/iso" option, then record them with following
command lines:

cdrecord dev=0,1,0 speed=4 -multi -xa1 TData01.iso

cdrecord dev=0,1,0 speed=4 -multi -xa1 TData02.iso

That's it!


Does it have bugs
-----------------

I've found out that CDR-Win (and possibly other software, too) always adds 2
blank sectors at the end of every data track. In CD-Extra or Mixed-mode CDs
this doesn´t seem to have any warmful effect, but in Multisession CDs where
there is a data track in the first session, it has to be cutted for it to work
correclty. CDIrip does this automatically (this can be avoided with "/full"
option, if needed).

If you are going to use cdrecord, Fireburner or WinOnCD (other software has
not been tested, although will probably have this issue, too) on a CD-Extra
image, then you MUST add "/cutall" option to the command line, because of the
"2 sectors issue" associated with these programs. Please read above. Also note
that any of these software is capable of burning 300 sectors audio tracks (will
always record them as 302 sectors long).


How many versions are out there
-------------------------------

CDIrip is a Win32 console application coded in straight c and compiled with
Borland C++ 5.5 Free Command-Line Tools, which is freely available at
Borland's website.


 0.4 (2000/10/12)

  - No need to use DOS-prompt for basic usage: just do double click to it
  - Support for Mixed-mode (Mode1/2048) and CD-XA Multisession (Mode2/2336)
    data tracks in cuesheet
  - Data tracks in first session are now automatically cutted by 2 sectors
  - Data tracks in CD-XA Multisession discs are now saved in BIN/2336 format
  - Audio tracks are now saved in WAV format
  - Added "/raw" option to force RAW format to audio tracks
  - Added "/iso" option to force ISO/2048 conversion to all data tracks
  - Added "/bin" option to force BIN/2336 format + 2 cuesheets
  - Added "/full" option to avoid cutting data tracks
  - Added "/cut" and "/cutall" options to cut tracks
  - Added "/info" option
  - Added progress counter (wow!)
  - Small bugfixes

 0.3 (2000/09/06)

  - Automatic cuesheet generation

 0.2 (2000/09/04)

  - Support added for Mode1/2048 tracks

 0.1 (2000/09/03)

  - First, internal release


(C) 2000 DeXT
