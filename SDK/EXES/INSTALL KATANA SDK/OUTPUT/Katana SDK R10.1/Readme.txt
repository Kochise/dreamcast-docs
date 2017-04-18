readme.txt
May 3, 2000

This development software is intended to help
developers begin work on Internet and modem-based
game development.  Major new functionality has
been added since R9 and it is expected that
installing R10 will break existing R9 projects.
If Internet development is not necessary for your
project, it is recommended that you continue
development with R9.

Nearly all areas of functionality have been
updated from R9 to R10.  Don't try to
integrate pieces of R9 with R10; this sort of
development will not be supported.

Please see changes.txt for more details about the 
changes from R9 to R10.

1. Overview
-------------

This software will allow you to develop for Katana
(Sega Dreamcast).  Make a backup copy of your 
current development environment before upgrading 
to R10.

R10 supports modem and network development.  All
development kits (set 5.24) come with built in
modems, as well as all commercial Sega Dreamcasts.
Included with the SDK are two in-game web
browsers. One is the PlanetWeb browser which is
used by consumers in the US.  The second is the
Access browser.  This browser is used by consumers
in Europe and Japan.  You can find samples of each
of these browser in the \Sample\net\Browser
directory. PlanetWeb is in the "US" subdirectory
and Access in the "Europe" subdirectory.

In addition to the two browsers we have also
included two stacks, a PlanetWeb stack and an
Access stack.  These stacks can be found in the
\Sample\net\stack directory.

Also included is a modem driver.  It is possible
to get direct access to the modem if needed.  An
example of this is located in the
\Sample\Net\Modem directory.

Two source-level debugging environments are
included with this release.  Codescape and
Metrowerks Codewarrior are supported. Codewarrior
provides an integrated development environment and
better C++ support.  In addition Codewarrior now 
supports a command line tools for the compiler.  
Support for the freely available, command-line 
based gnu compiler and linker have been added in 
this release.

You can burn and test GD-ROMs with this software,
in conjunction with the GD Writer hardware and
the CD Craft burning software.

This development environment includes a number of
demonstration programs supplied by VideoLogic.
Sega would like to express appreciation to
VideoLogic for supplying these high-quality demos,
which are installed into \Sample\km2Demo.
Additionally, VideoLogic has supplied a 3D Studio
Max to Kamui model converter in
\Utl\Gfx\Conv\3DS2Kamui.

R10 now supports MIDI playback of sounds using
the audio64 driver.

2. Known Problems and Issues
----------------------------

- Reflash of GD Writer units required

  An intermittent bug has been identified in the
  firmware of existing GD Writer units that can
  cause disc burns to fail while writing track 2.
  This updated firmware improves the reliability
  of the GD Writer units.  The flash firmware has
  been updated since R9 and it is recommended that
  all developers reflash with this new version.

  The GUI utility for reflashing the GD Writer
  firmware to version 0.53 has been included in
  this release, installed into the
  \utl\dev\dbflash\gdrflash directory. The utility 
  is called DldWin.exe. 

- Development target firmware reflash *IS*      
  required when upgrading from R9.  

  The installation program initiates the flashing
  process for you by default.  If you need to
  reflash the firmware in your development system
  manually, use the DBFlash program, supplied in
  \utl\dev\dbflash.

  The reflash process requires the SLIDE SW on the
  front of the unit to be toggled twice; follow
  the instructions carefully.

- Support for global constructors has been
  implemented.  The sbinit.c file, common to all
  Shinobi programs, has changed to handle proper
  initialization of global constructors for C++.
  This affects the Metrowerks and GNU compilers.

- The shinobi_workaround() function has been
  modified to to properly initialize the GNU
  environment.

- Kamui samples have been removed. Most of the
  samples have been ported to Kamui2. Sega of
  America recommends that you port your title to
  Kamui2 if you are using Kamui. Support for Kamui
  is still in the SDK for this release, however.
  If you wish to continue using Kamui you have to
  link with the Ninja libs and follow the
  initialization of Kamui2. Contact Sega of
  American DTS if you have any questions or
  problems.

- Due to lack of interest on the part of
  third-party developers, Ninja samples have been
  removed.  The libs and .h files still remain in
  the SDK; however, Sega of America will be
  discontinuing support for this API.

- Audio64 efficiency improvements
  
  Due to changes in the audio64 programming layer,
  R10 is not source-compatible with
  Release 9.

  The Audio64 audio streamer has been completely
  reworked. The R9 version used synchronous
  Shinobi File IO calls and synchronous SH4 memory
  copies to transfer data to sound RAM.  The R10
  version uses asynchronous File IO calls and DMA
  data transfer methods (if selected) and is much
  more efficient.  A number of R9 streamer calls
  which are no longer used have been removed. See
  changes.txt for the complete list of changes.

  - The Audio64 Library initialization procedure 
    has been greatly simplified, and the sample 
    boilerplate code has been completely 
    re-written.  In general, the Audio64 Library 
    initializes with required default function 
    pointers installed (for interrupt processing, 
    file IO, memory management, DMA calls etc.) 
    and these function pointers may be overwritten
    at link time during the build process.  See the
    A64Thunk sample program for more details.

  - A DMA transfer mechanism has been added, and
    is used by the new acTransfer command.

  - CRI (ADX and SofDec) Middleware support has
    been added for Audio64.  It is no longer
    necessary to switch out Audio64 during video
    playback.

  - MIDI support has been added (MidiDa.drv) and
    works cleanly with the Audio64 library API,
    offering standard MIDI Format File 0 playback
    with interrupt callback support.  MIDI
    instrument banks can be created with either
    the Sega Midi Program Editor (Macintosh) or a
    standard DLS editor (PC) and the DLS file
    converted with the DLS2TB.EXE DOS utility.

  - Additional sound driver commands have been
    added to fully support all AICA channel
    hardware registers (see list below).

  - The MKBANK.EXE tool has been fixed to allow
    byte-aligned (MIDI and ADPCM) files to
    co-exist with 32-bit aligned bank data in a
    KAT back.

    Sample code:

     ALL boilerplate sample code has changed
     significantly, so please pay close attention
     to the new initialization procedures.

     A64Thunk	- Static hooks for integrating    
                  Audio64 with run-time 
                  environments
     AcTransfer	- CPU/DMA transfer mechanism
     AmStream	- Async streamer
     AmPlayMidi	- MIDI streamer

- Metrowerks Codewarrior C/C++ compiler updated

  We updated to version 4.0.6 Build 0524. This 
  includes a new command line version of the 
  compiler. This has been integrated into the  
  build environment.

  As of this build, the IDE may not build projects
  properly.  These build problems cannot be
  replicated if you build your project using the
  command-line build process.  Specifically, we
  have seen the following problems:

  - In order for debugging information to be 
    present in the ELF file, the user must select 
    the appropriate build (either debug or 
    release) and go to Project -> Enable Debugger. 
    Without this option selected, the code will 
    run fine, but Codescape will report "main is 
    an invalid expression and a breakpoint cannot 
    be set there". This option muse be selected 
    for every new project - although it is saved 
    in the stationary, it does  not get 
    transferred to the new projects that are 
    created.

  - Compiled programs may cause an exception upon
    executing. This is caused by a bad
    prefix_dc.h.  Users should not change the
    default prefix_dc.h file that comes with the
    R10, otherwise certain symbols will not be
    included and the code will stop execution in
    sbinit.c

  - Adding files to a project may cause an 
    erroneous message dialog to pop up complaining 
    that "One or more files couldn't be added to 
    the project." In order to avoid this error, go 
    into the Project Settings and add the
    appropriate filetype that you want to add to 
    your project.
  
  - Sometimes windows get placed out of the    
    visible screen viewing area.

- Latest Adaptec ASPI driver required

  The Codescape debugger requires the most recent
  version (4.60) of the Adaptec ASPI driver to be
  installed.  This driver is available from:

http://www.adaptec.com/support/faqs/aspilayer.html

- A noticeable slow-down may occur in Kamui2 when
  rendering multiple times without a page flip.  

  See the "SplitTst" sample for a workaround
  showing 4-player split screen in Kamui2.

- Using either the audio64 or manatee sound driver
  immediately after initialization may cause 
  errors

  To work around this issue, always pause at least
  500 ms after initializing the audio system
  before issuing any sound commands.

- Start of audio streaming using audio64 library
  pauses video

  When loading and playing a digital audio stream
  from GD-ROM, there is a pause in rendering for
  around 250ms while the streamer subsystem
  initializes. This can produce a noticeable 
  hiccup in the display.

- Second disk partition on GD-ROM emulator drive
  does not appear under Windows NT

  A bug currently exists in Windows NT preventing
  the second partition from being seen.  If you
  need the entire 4 GB storage space, the drive
  can be re-formatted as NTFS or FAT-32.  See the
  section labeled "Formatting the Emulation Drive"
  (p.47) in the "GD-Workshop User Guide"
  distributed with this release.

- Textures and file loads must be 32-byte aligned

  Due to DMA restrictions, Kamui textures and file
  loading operations should be aligned to 32-byte
  boundaries.  For an example of how to do this
  properly, see the Align32Byte() macro in the 
  QuikTest sample program.

- gcc generates warnings on headers

  The versions of Shinobi headers in this release
  do not compile cleanly when used with gcc;
  warnings are generated, mostly related to type
  checking.  However, the sample programs run as
  expected.

- Dereferencing NULL not allowed

  System device control registers reside in low
  memory.  Accesses to the memory region
  0x00000000-0x001fffff are almost always the
  result of dereferencing the NULL pointer, which
  is a programming error.  
  
  If you're using Codescape for development, you
  should at some point force Codescape to trap
  these error conditions:

  - Select Debug/Breakpoints/Configure
    Breakpoint(s) to open the breakpoint setup
    dialog box.

  - Click the Add Watch... button.

  - In the Watch Settings tab, enter 0x00000000
    into the Location Expression text box.  In the
    Data Expression group, uncheck the Include
    Data Condition checkbox.  In the Access Size
    option group, select Any.  In the Access Type
    option group, select Write.

  - In the Advanced tab, from Location Mask
    Selector, select "20 bits".

  - Click the OK button to complete the setup.

- Sound example programs may not run as expected
  under default Windows installation

  The low-level sound drivers included in this
  release are called manatee.drv and audio64.drv.
  These files are usually installed into the
  \driver folder.  By default, a Windows
  machine running Internet Explorer 4.0 or higher
  will not display files with a .drv extension.
  As a result, when you try to create a GD-ROM
  image by dragging all files in the gd_root
  folder into GD Workshop, the driver is not
  included.

  To see the .drv files, select the drive
  containing the development software
  installation, click the Explorer window's View
  menu, and select Options.  Select the View tab.
  Make sure the "Show all files" radio button is
  selected, and deselect the "Hide file extensions
  for known file types" check box.  Finally, click
  Apply.

- GD Workshop hard limits exist

  Due to GD-ROM format and performance
  considerations, there are certain numeric limits
  on GD-ROM emulation and usage with GD Workshop:

  - Maximum number of files per project: 20,000
  - Maximum number of file extents over 1 
    project: 64,000
  - Maximum number of files in a directory on
    emulation drive: 4,000
  - Maximum number of directories on emulation
    drive: 512

- Submit directory contains some older-versioned
  drivers

  You may notice that we have included some driver
  files in the \Submit directory hierarchy that do
  not match the drivers in the \Driver directory.
  The latest versions of all drivers are found in
  the \Driver folder at the root of the
  installation.  Some of the drivers in the
  \Submit folder hierarchy, which are used by the
  DreamOn and Ginsu tools, are matched to the
  versions of the sampler disc software in the
  \Submit folder.  Therefore, for your own
  development, you should always use the drivers
  in the \Driver folder for your own application
  development, and allow the DreamOn and Ginsu
  tools in the \Submit folder to load the driver
  versions that they are matched with.

- System-to-system DMA transfer hardware bug

  A bug within the Hitachi SH-4 when issuing DMA
  transfers from system memory to system memory
  can cause certain registers to fail to be
  updated under a variety of highly specific
  circumstances.

  The bug occurs when all three of the following
  conditions are met:

  1. DMA single-address read mode access is in
     progress

  2. DMA dual-address mode read access from
     external bus or from peripheral control
     registers is in progress
  
  3. CPU attempts to write to peripheral control
     registers: BSC, DMAC, CPG, RTC, INTC, TMU,
     SCI, SCIF, H-UDI, SDSR, and ASERAM.  However,
     this does not include registers SDMR2 and
     SDMR3 of BSC, TCPR2 of TMU, SCRDR1 of SCI,
     SCFDR2 and SCRDR2 of SCIF, and SDRR of H-UDI.
     Note that these control registers are
     accessed whenever any SH-4 peripheral 
     services are accessed, such as the GD-ROM 
     controller.

  Because of the complexity of working around this
  bug, it is highly recommended that developers
  abstain from system-to-system memory DMA. Please
  contact Sega DTS for help on this issue.

- Large static arrays compile slowly
 
  Both Codewarrior and gcc can take an extremely
  long time to compile some of the large static
  arrays used as textures in the Kamui2 samples.
  For example, the Fortune demo can take up to 20
  minutes to compile on a P2-300, versus 2 minutes
  for Hitachi C.  We are working with both
  compiler vendors to improve this performance.
  In the meantime, try to avoid recompiling large
  data elements in your application.
  
- Use of IPMaker required

  In previous releases of this development
  software, Sega supplied default versions of
  IP.BIN and IP0000.BIN for use in emulating a
  GD-ROM.  Now, Sega provides the tool (IPMaker)
  to allow you to create your own IP.BIN and
  IP0000.BIN file.

- Programs do not run on Set 5.23

  Set 5.23 development hardware is no longer
  supported.  Contact Sega for upgrade
  instructions.

- Kamui2 sample programs may lose text on   
  composite output due to overscan

  Some Kamui2 sample programs output text to the 
  display in regions that NTSC and PAL consider
  to be overscan regions.  To work around and
  see the invisible text, use a VGA monitor.

- Return codes from main() are not passed
  through Codescape

  Standard arguments and return values from main()
  are not supported by Codescape.  If a program
  passes through the end of its execution cycle,
  an exception is raised.

- Metrowerks produces "Can't assign register" 
  error messages under specific optimization 
  levels

  Under certain conditions, the Metrowerks
  compiler may complain about register allocation
  if the "No optimization" optimization level is
  selected.  To work around, select the "C/C++
  Language Options," and change the Inline Depth
  to "Don't Inline" when turning off
  optimizations.

- Vertex buffers should be set up in non-cacheable
  memory

  For an example of accessing memory in a
  non-cached manner, examine the
  SH4_P2NonCachedMem() macro in the QuikTest
  sample program.

- pvrconv.exe requires textures to be 8x8 or
  larger

  If you require a smaller texture, create it
  within an 8x8 bitmap and reference to the proper
  UV coordinates within the 8x8 bitmap.

- Compiling with /optimize=1 changes source-level
  debugging behavior

  When in optimize mode, the Hitachi compiler's
  instruction scheduler reorders instructions
  incompatibly with source-level debugging in
  Codescape.  The most common manifestation of
  this behavior is watched variables that appear
  to change their value at strange times.  This
  behavior is confusing but correct.  Switch to
  assembly debugging or compile with optimization
  off to work around.

- Sound Effects Editor crashes if Sound Box is not
  attached

  Sound Effects Editor crashes with an error 10,
  requiring a soft reset on the Macintosh if the
  HKT-03 is not connected or turned on; this
  occurs when you go to Window->I/O Modules, and
  select an Input Module.

- Source selection dialog under PCM stream convert
  appears doubled (buttons overdraw each other)

  In Sound Data Converter, if you choose Edit->PCM
  Stream Convert, and hit the Source button, the
  resulting dialog appears and then redraws,
  appearing doubled.

  It's possible to partially workaround by
  clicking on the location where the button
  originally appears.

- No way to write to the GD-ROM filesystem

  Use the LibCross fileserver routines for simple
  file I/O.  See also the "Hello" sample located
  in the "Sample\stdio_stl\" folder or
  look at "QuikTst2" in the Kamui2 sample area.

- "Start a new compilation environment" desktop
  icon incorrect under Windows NT

  The icon seems to behave correctly, however.

- Index file closes after launching a .PDF
  documentation link

  When using Adobe Acrobat, in order to keep the
  Index.pdf file open after choosing a new PDF
  file to read, use the File/Preferences/General
  command.  Deselect the checkbox that reads "Open
  Cross-Document Links in Same Window."

- Hitachi C++ not supported

  Although the Hitachi C++ compiler compiles most
  of the C++ programs in this release, Sega does
  not recommend it for C++ development.  Use the
  Metrowerks or gnu compilers instead.

3. Other important files
------------------------

\legal.txt: Legal information and disclaimer
            associated with this development
            software.

\readme.txt: This file.

\getstart.txt: Information on setting up your
	      development system.  All users
	      should read this file.

\changes.txt: Major functionality changes
              since R6.

4. Support options
------------------

We look forward to hearing about problems or
questions that you have regarding Dreamcast
development.  Here's how you can get help or
contact us:

- Printed and on-line documentation

Check the \doc folder for on-line versions of the
manuals and training materials.

- Electronic mail

Developers in the United States may contact
Sega of America's technical support by sending
e-mail to dts@sega.com.  Developers in Europe may
contact Sega of Europe by sending e-mail to
edts@soepd.sega.co.uk.

Your e-mail will be routed to the appropriate
engineer.

- DTS Web site

Sega of America maintains a private Web site for
developers at http://www.dts.sega.com/NextGen/
that contains current development software,
frequently asked questions, and archives of
message bases.  To be granted access to the Web
site, send e-mail from your corporate e-mail
address to dts@sega.com.  You will be
voice-validated for access.

- Listserver

Sega provides an active electronic mail listserver
dedicated to Dreamcast game development.  This
listserver allows you to send mail to a large
number of Sega internal and third-party Dreamcast
developers.  To join the listserver, send e-mail
from your corporate e-mail address to
elite-listserv@sega.com with the words "subscribe
elite" in the body of the message.  You will be
voice-validated for access.

- Telephone

Sega of America's phone number has recently
changed.  In the US, Sega of America's Developer
Technical Support department may be contacted at
(415) 701-4060, 10:00 am to 6:00 pm, Monday
through Friday.  In Europe, Sega of Europe's
Developer Technical Support may be contacted at
+(44) (0) 181-996-4421.