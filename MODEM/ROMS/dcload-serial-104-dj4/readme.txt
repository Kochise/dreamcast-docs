dcload 1.0.4 - a Dreamcast serial loader by <andrewk@napalm-x.com>

Features

* Compressed binary transfers (dc-tool supports loading elf, srec, and bin)
* PC I/O (read, write, etc to PC)
* Exception handler

Building

1. Edit Makefile.cfg for your system, and then run make

Installation

1. PC - run make install (installs dc-tool)
2. DC
   a. cd make-cd, edit Makefile, insert blank cd-r, run make
   b. take target-src/1st_read/1st_read.bin and stuff it on a cd yourself
      (please use the IP.BIN from the make-cd directory if you are going
       to distribute either cds or cd images)

Testing

1. cd example-src
2. dc-tool -x console-test.bin (tests some PC I/O)
   (or dc-tool -x console-test, now that dc-tool can load ELF)
3. dc-tool -x exception-test.bin (generates an exception)
   (or dc-tool -x exception-test, now that dc-tool can load ELF)

KOS GDB-over-dcload

To run a GNU debugger session over the dcload connection:

1. Build/obtain an sh-elf targetted GNU debugger
2. Put a 'gdb_init()' call somewhere in the startup area of your
   KOS-based program
3. Build your program with the '-g' GCC switch to include debugging info
4. Launch your program using 'dc-tool -g -x <prog.elf>'
5. Launch sh-elf-gdb and connect to the dc-tool using 'target remote :2159'
6. Squash bugs 

Notes

* dcload and dc-tool (both IP and serial) are now maintained by the KOS
  team. Please join the KallistiOS list for help with these tools.
    http://sf.net/projects/cadcdev/
* Now compiles with gcc-3.4.1, Binutils-2.15, newlib-1.12.0
* Tested systems: Debian GNU/Linux 2.2; Gentoo/Linux 2.6.7; Cygwin;
  Mac OSX 10.3.5 (Panther)
* 1.56M and 500K baud now supported with the FTDI USB-Serial driver.
  note: currently works with FT232BM USB-Serial UART running at 6.144Mhz.
  e.g.:
    linux:  dc-tool -t /dev/usb/tts/0 -b 1500000 -x <sh-executable>
    Cygwin: dc-tool -t COM4 -b 500000 -x <sh-executable>
* As of 1.0.4, little-endian byte order is enforced in the host so dc-tool
  should now run on big-endian systems like a Mac.
* As of 1.0.4, Changed cdrecord option -xa1 to -xa: i've made one too many
  softdrink coasters since the authors of this tool changed the meaning of
  that option.
* 115200 works fine for me. Apparently it doesn't for some people. 
* As of 1.0.3, serial speed is changed at runtime rather than compile time. 
* There is now a -e option that will enable an alternate 115200 (which 
  doesn't work for me). If it works for you, please email 
  andrewk@napalm-x.com, especially if it works better than the default 115200.
* Patches and improvements are welcome.

Mac OSX Notes

* This was tested on Panther 10.3.5 only. It may or may not work on any other
  version of OSX. YMMV.
* Of course some sort of USB serial must be used. Standard RS232 adapters
  work as does Axlen's USB coders' cable.
* OSX does *not* support non-standard baud rates, so speeds higher
  than 115200 currently do not work. This is due to a limitation in the
  IOSerialFamily kernel module so it can not be easily worked around at
  this time.
* Compilation on OSX requires libintl, which must be installed with Fink
  using the 'gettext' package. (Using 'fink' or 'apt-get' is fine).
    http://fink.sf.net/
* You may see duplicate symbol warnings at compile time, like _strncpy
  in libiberty.dylib. You can safely ignore these.

Credits

* Minilzo was written by Markus Oberhumer
* There are some various files from newlib-1.8.2 here, and video.s was written 
  by Marcus Comstedt.
* win32 porting and implementation of -t by Florian 'Proff' Schulze
* bugfix and implementation of -b by The Gypsy
* fixes for cygwin by Florian 'Proff' Schulze
* Minor initialization fix in dcload for gcc-3.4.x. Serial protocol endian
  fixes - Paul Boese a.k.a. Axlen
* Fixes for Mac OSX (and testing) by Dan Potter
* Fixes for libbfd segfaults by Atani  
