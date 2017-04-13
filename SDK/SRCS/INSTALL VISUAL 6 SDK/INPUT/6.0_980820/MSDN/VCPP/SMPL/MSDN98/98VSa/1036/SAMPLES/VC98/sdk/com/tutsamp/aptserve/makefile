#/*+=========================================================================
#  File:       MAKEFILE
#
#  Summary:    Makefile for building the APTSERVE.EXE binary.  APTSERVE
#              is a local apartment threaded COM server that offers the
#              Car, UtilityCar, and CruiseCar components each in separte
#              multithreading Apartments. As a local server APTSERVE makes
#              used of the custom car-related interfaces (ICar, IUtility,
#              and ICruise) that are marshaled by the MARSHAL.DLL server.
#              This Makefile thus depends on the prior build (and the
#              resultant registration) of the MARSHAL.DLL server.
#
#              This Makefile creates a subdirectory (TEMP) for the
#              .OBJ and .RES files used during the build process.
#
#              For a comprehensive tutorial code tour of APTSERVE's
#              contents and offerings see the tutorial APTSERVE.HTM
#              file.  For more specific technical details see the comments
#              dispersed throughout the APTSERVE source code.
#
#              See also APTCLIEN.HTM (in the main tutorial directory) for
#              more details on the APTCLIEN client and how it works with
#              APTSERVE.EXE itself.
#
#              In general, to set up your system to build and test the
#              Win32 code samples in this COM Tutorial series, see the
#              global TUTORIAL.HTM file for details.  This MAKEFILE is
#              Microsoft NMAKE compatible and the 'debug' build can be
#              achieved by simply issuing the NMAKE command in a command
#              prompt window.
#
#  Builds:     APTSERVE.EXE
#
#  Origin:     3-20-96: atrent - Editor-inheritance from LOCCLIEN makefile.
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
#  To register server                   nmake register
#  To unregister server                 nmake unregister
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
PGM=aptserve

# Use a temporary sub-directory to store intermediate
# binary files like *.obj, *.res, *.map, etc.
TDIR = TEMP

# The sibling ..\INC and ..\LIB directories are added to the front of
# the INCLUDE and LIB macros to inform the compiler and linker of
# these application-specific locations for include and lib files.
INCLUDE=..\inc;$(INCLUDE)
LIB=..\lib;$(LIB)
LINK = $(link)

REGEXE = ..\register\register.exe

# If UNICODE=1 is defined then define UNICODE during Compiles.
# The default is to compile with ANSI for running under both
# Win95 and WinNT.
!IFDEF UNICODE
LINKFLAGS = $(ldebug) /NOD:libc.lib /NOD:msvcrt.lib /NOD:libcd.lib \
  /NOD:libcmtd.lib /NOD:msvcrtd.lib
CDBG=$(cdebug) -DUNICODE -D_UNICODE
RCFLAGS = -DWIN32 -DRC_INCLUDE -DUNICODE
!ELSE
LINKFLAGS = $(ldebug) /NOD:libc.lib /NOD:msvcrt.lib /NOD:libcd.lib \
  /NOD:libcmtd.lib /NOD:msvcrtd.lib
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
PGMOBJS = $(TDIR)\$(PGM).obj $(TDIR)\server.obj $(TDIR)\factory.obj \
  $(TDIR)\car.obj $(TDIR)\utilcar.obj $(TDIR)\crucar.obj

# The final target.
all: tempdir output

# Make the temporary work sub-directory.
tempdir:
  -mkdir $(TDIR)

# The actual output products.
output: $(PGM).exe
  if exist $(PGM).EXE if exist $(REGEXE) $(REGEXE) /e $(PGM).EXE

# Compilation/Dependency rules for the main source files.
$(TDIR)\$(PGM).obj: $(PGM).cpp $(PGM).h
  $(cc) $(cvarsmt) $(cflags) $(CDBG) -Fo$@ $(PGM).cpp

$(TDIR)\server.obj: server.cpp server.h $(PGM).h
  $(cc) $(cvarsmt) $(cflags) $(CDBG) -Fo$@ server.cpp

$(TDIR)\factory.obj: factory.cpp factory.h server.h $(PGM).h
  $(cc) $(cvarsmt) $(cflags) $(CDBG) -Fo$@ factory.cpp

$(TDIR)\car.obj: car.cpp car.h server.h $(PGM).h
  $(cc) $(cvarsmt) $(cflags) $(CDBG) -Fo$@ car.cpp

$(TDIR)\utilcar.obj: utilcar.cpp utilcar.h server.h $(PGM).h
  $(cc) $(cvarsmt) $(cflags) $(CDBG) -Fo$@ utilcar.cpp

$(TDIR)\crucar.obj: crucar.cpp crucar.h server.h $(PGM).h
  $(cc) $(cvarsmt) $(cflags) $(CDBG) -Fo$@ crucar.cpp

# Compile the resources.
$(TDIR)\$(PGM).res: $(PGM).rc $(PGM).ico $(PGM).h
  rc $(RCFLAGS) -r -fo$@ $(PGM).rc

# Link the object and resource binaries into the final target binary.
$(PGM).exe: $(PGMOBJS) $(TDIR)\$(PGM).res
  $(LINK) @<<
    $(LINKFLAGS)
    -out:$@
    -map:$(TDIR)\$*.map
    $(PGMOBJS)
    $(TDIR)\$*.res
    $(olelibsmt) $(APPLIBS)
<<

# Target to register the server
register:
  if exist $(PGM).EXE if exist $(REGEXE) $(REGEXE) /e $(PGM).EXE

# Target to unregister the server
unregister:
  if exist $(PGM).EXE if exist $(REGEXE) $(REGEXE) /e /u $(PGM).EXE

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
