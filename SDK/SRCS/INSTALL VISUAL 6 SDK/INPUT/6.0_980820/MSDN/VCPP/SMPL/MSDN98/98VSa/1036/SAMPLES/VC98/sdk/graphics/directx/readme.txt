DirectX 5 Release Notes for the Platform SDK
----------------------------------------------

Setting up your DirectX build environment
-----------------------------------------
To setup your DirectX build environment, edit the 
<sdkdir>\samples\graphics\directx\dxsetenv.bat
file to point to the location of your compiler, assembler, and the location
of the Platform SDK. Run the dxsetenv.bat batch file.

Windows 95-specific libs (VC and Watcom) are installed to <sdkdir>\lib. 
Windows 95-specific libs (Borland) are installed to <sdkdir>\lib\borland. 

If you have problems building the samples when running under a DOS Command 
box, try using a NT DOS CMD box instead. Start\Run, Type "CMD", hit enter".    

If you encounter problems building samples using the default build 
environment, you may need to edit the DXSETENV.BAT file to use WINDEF.H 
released with Microsoft Visual C++ version 5.0.

SDK Samples
-----------

To ensure compatability with all editors, all tabs in sample source code files
have been replaced with spaces.

All SDK samples are designed to be built in the directory they are in.  
Once your Win32 development environment is set up, you 
can go to any sample directory and do a make.

There is a main make file in each sample directory:
MAKEFILE        - for use with Microsoft VC++ 2.0 or higher (NMAKE)

There are 2 ways to build each sample, debug or retail.   To build a
sample as retail with VC++, just type:

nmake nodebug=1

To build a sample as debug with VC++, just type:

nmake

There is also a master make file in the SAMPLES directory that will compile
all the samples at once:
MAKEFILE        - for use with Microsoft VC++ 2.0 or higher (NMAKE)


Creating a setup program for your game
---------------------------------------
We have included the source code to a sample setup program for a game
which uses the DirectX runtimes. The source for this program is located in 
<sdkdir>\samples\Graphics\DirectX\setup. Note that to build 
your own custom setup program, all you need to do is edit the copy_list 
at the start of DINSTALL.C to be your list of files, search for 
"fox", and then for "bear", and change things appropriately.

Next, create a game directory that includes your files and the setup program 
you have built. Xcopy /s the <sdkdir>\redist\DirectX5\win95\directx directory to the 
root of your game directory, i.e.:

XCOPY /S c:\mssdk\redist\DirectX5\win95\directx\*.* D:\FUNGAME

If you are building an autorun CD title, you can copy the AUTORUN.INF at 
<sdkdir>\samples\Graphics\DirectX\setup to the root of your game directory. 
If your installation program is called SETUP.EXE, you will not have to make 
any changes to this file. If it is called something else, then you can edit 
AUTORUN.INF appropriately.


Notes for users of Visual C++ 4.2
---------------------------------
Visual C++ 4.2 includes the DX2 header files and libraries.  If you are
getting errors compiling the samples, make sure that the DX5 include
and lib paths come before the MSVC++ 4.2 include and libs.


Notes for users of Watcom C/C++
-------------------------------
Watcom C/C++ v10.6 is required to compile the DXSDK samples.
v10.0 is not sufficient. The Microsoft Windows Platform SDK is also required
and is expected to be in \MSTOOLS on the same drive as your DXSDK
sample files. If the Platform SDK is elsewhere, you can set the MSTOOLS
environment variable to point to its root directory (e.g. set
MSTOOLS=\MSTOOLS).

Change lines 408-410 of SAMPLES\WIN32.MAK from:
        libc = libc.lib oldnames.lib
        libcmt = libcmt.lib oldnames.lib
        libcdll = msvcrt.lib oldnames.lib
to:
        libc =
        libcmt =
        libcdll =

The Watcom makefiles expect the WATCOM environment variable
to be set, as it should have been by the Watcom installation procedure.

Only a subset of the samples have Watcom makefiles.

Watcom and Watcom C/C++ are trademarks of Powersoft, Watcom Division.
