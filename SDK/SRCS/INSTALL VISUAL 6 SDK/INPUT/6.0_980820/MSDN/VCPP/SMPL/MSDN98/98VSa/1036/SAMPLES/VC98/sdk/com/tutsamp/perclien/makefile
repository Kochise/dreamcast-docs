#/*+=========================================================================
#  File:       MAKEFILE
#
#  Summary:    Makefile for building the PERCLIEN.EXE binary. PERCLIEN
#              is a Win32 EXE that acts as a client of the PERSERVE,
#              PERTEXT, and PERDRAW DLL servers to create and manipulate
#              various COM objects for an application that edits and
#              stores an open-ended series of text and drawing pages.
#
#              This Makefile therefore depends on a prior build (and the
#              resultant registration) of the PERSERVE.DLL, PERTEXT.DLL,
#              and PERDRAW.DLL COM servers.
#
#              This Makefile creates a subdirectory (TEMP) for the
#              .OBJ and .RES files used during the build process.
#
#              For a comprehensive tutorial code tour of PERCLIEN's
#              contents and offerings see the tutorial PERCLIEN.HTM
#              file. For more specific technical details see the comments
#              dispersed throughout the PERCLIEN source code.
#
#              See PERSERVE.HTM (in the main tutorial directory) more
#              details on the PERSERVE server and how it works with
#              PERCLIEN.EXE.
#
#              See PERTEXT.HTM (in the main tutorial directory) more
#              details on the PERTEXT server and how it works with
#              PERCLIEN.EXE.
#
#              See PERDRAW.HTM (in the main tutorial directory) more
#              details on the PERDRAW server and how it works with
#              PERCLIEN.EXE.
#
#              In general, to set up your system to build and test the
#              Win32 code samples in this COM Tutorial series, see the
#              main TUTORIAL.HTM file for details.  This MAKEFILE is
#              Microsoft NMAKE compatible and the 'debug' build can be
#              achieved by simply issuing the NMAKE command in the
#              command prompt window.
#
#  Builds:     PERCLIEN.EXE.
#
#  Origin:     5-20-97: atrent - Editor-inheritance from STOCLIEN code
#              sample makefile.
#
#--Usage:-------------------------------------------------------------------
#  NMAKE Options
#
#  Use the table below to determine the additional options for NMAKE to
#  generate various application debugging, profiling and performance tuning
#  information.
#
#  Application Information Type         Invoke NMAKE
#  ----------------------------         ------------
#  For No Debugging Info                nmake nodebug=1
#  For Working Set Tuner Info           nmake tune=1
#  For Call Attributed Profiling Info   nmake profile=1
#
#  Note: The three options above are mutually exclusive (you may use only
#        one to compile/link the application).
#
#  Note: creating the environment variables NODEBUG, TUNE, and PROFILE
#        is an alternate method to setting these options via the nmake
#        command line.
#
#  Additional NMAKE Options             Invoke NMAKE
#  ----------------------------         ------------
#  For No ANSI NULL Compliance          nmake no_ansi=1
#    (ANSI NULL is defined as PVOID 0)
#  To compile for Unicode               nmake unicode=1
#    (Default is ANSI)
#  To clean up temporary binaries       nmake clean
#  To clean up all generated files      nmake cleanall
#
#---------------------------------------------------------------------------
#  This file is part of the Microsoft COM Tutorial Code Samples.
#
#  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.
#
#  This source code is intended only as a supplement to Microsoft
#  Development Tools and/or on-line documentation.  See these other
#  materials for detailed information regarding Microsoft code samples.
#
#  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
#  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
#  PARTICULAR PURPOSE.
#=========================================================================+*/

#  WIN32.MAK should be included at the front of every Win32 makefile.
#
#  Define APPVER = [ 3.50 | 3.51 | 4.0 ] prior to including win32.mak to get
#  build time checking for version dependencies and to mark the executable
#  with version information.
#
#  Define TARGETOS = [ WIN95 | WINNT | BOTH ] prior to including win32.mak
#  to get some build time checking for platform dependencies.
#
APPVER=4.0
TARGETOS=BOTH
!include <win32.mak>

# Assign the main program name macro.
PGM=perclien

# Use a temporary sub-directory to store intermediate
# binary files like *.obj, *.res, *.map, etc.
TDIR = TEMP

# The sibling ..\INC and ..\LIB directories are added to the front of
# the INCLUDE and LIB macros to inform the compiler and linker of
# these application-specific locations for include and lib files.
INCLUDE=..\inc;$(INCLUDE)
LIB=..\lib;$(LIB)

LINK = $(link)

# If UNICODE=1 is defined then define UNICODE during Compiles.
# The default is to compile with ANSI for running under both
# Win95 and WinNT.
!IFDEF UNICODE
LINKFLAGS = $(ldebug)
CDBG=$(cdebug) -DUNICODE -D_UNICODE
RCFLAGS = -DWIN32 -DRC_INCLUDE -DUNICODE
!ELSE
LINKFLAGS = $(ldebug)
CDBG=$(cdebug)
RCFLAGS = -DWIN32 -DRC_INCLUDE
!ENDIF

# If NODEBUG is not defined then define DEBUG during Compiles.
# The default is to compile with debug symbols in the binaries.
!IFNDEF NODEBUG
CDBG = $(CDBG) -DDEBUG
RCFLAGS = $(RCFLAGS) -DDEBUG
!ENDIF

# APPLIBS are libraries used by this application that are outside
# of its indigenous file set and are needed during the final link.
APPLIBS = apputil.lib shell32.lib

# PGMOBJS is a macro that defines the object files for this application.
PGMOBJS = $(TDIR)\$(PGM).obj $(TDIR)\guilist.obj $(TDIR)\listsink.obj \
          $(TDIR)\pagefile.obj $(TDIR)\listwin.obj $(TDIR)\textwin.obj \
          $(TDIR)\guitext.obj $(TDIR)\textsink.obj \
          $(TDIR)\guidraw.obj $(TDIR)\drawsink.obj


# The final target.
all: tempdir output

# Make the temporary work sub-directory.
tempdir:
  -mkdir $(TDIR)

# The actual output products.
output: $(PGM).exe

# Compilation/Dependency rules for the main source files.
$(TDIR)\$(PGM).obj: $(PGM).cpp $(PGM).h resdef.h guilist.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ $(PGM).cpp

$(TDIR)\guilist.obj: guilist.cpp guilist.h $(PGM).h resdef.h listsink.h \
       listwin.h guitext.h textwin.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ guilist.cpp

$(TDIR)\listsink.obj: listsink.cpp listsink.h guilist.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ listsink.cpp

$(TDIR)\pagefile.obj: pagefile.cpp pagefile.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ pagefile.cpp

$(TDIR)\listwin.obj: listwin.cpp listwin.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ listwin.cpp

$(TDIR)\guitext.obj: guitext.cpp guitext.h $(PGM).h resdef.h \
       textsink.h textwin.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ guitext.cpp

$(TDIR)\textsink.obj: textsink.cpp textsink.h guitext.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ textsink.cpp

$(TDIR)\textwin.obj: textwin.cpp textwin.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ textwin.cpp

$(TDIR)\guidraw.obj: guidraw.cpp guidraw.h $(PGM).h resdef.h drawsink.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ guidraw.cpp

$(TDIR)\drawsink.obj: drawsink.cpp drawsink.h guidraw.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ drawsink.cpp

# Compile the resources.
$(TDIR)\$(PGM).res: $(PGM).rc $(PGM).ico resdef.h
  rc $(RCFLAGS) -r -fo$@ $(PGM).rc

# Link the object and resource binaries into the final target binary.
$(PGM).exe: $(PGMOBJS) $(TDIR)\$(PGM).res
  $(LINK) @<<
    $(LINKFLAGS)
    -out:$@
    -map:$(TDIR)\$*.map
    $(PGMOBJS)
    $(TDIR)\$*.res
    $(olelibs) $(APPLIBS)
<<

# Target to clean up temporary binaries.
clean:
  -del $(PGM).pdb
  -deltree /y $(TDIR)
  -rmdir /s /q $(TDIR)

# Target to clean up all generated files.
cleanall:
  -del *.aps
  -del *.bsc
  -del *.dll
  -del *.dsp
  -del *.dsw
  -del *.exe
  -del *.exp
  -del *.lib
  -del *.mak
  -del *.map
  -del *.mdp
  -del *.ncb
  -del *.obj
  -del *.opt
  -del *.pch
  -del *.pdb
  -del *.plg
  -del *.res
  -del *.sbr
  -del *.vcp
  -del resource.h
  -deltree /y $(TDIR)
  -rmdir /s /q $(TDIR)
  -deltree /y debug
  -rmdir /s /q debug
  -deltree /y release
  -rmdir /s /q release
