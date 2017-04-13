#/*+=========================================================================
#  File:       MAKEFILE
#
#  Summary:    Makefile for building the DCDSERVE.EXE executable.
#              DCDSERVE is a COM out-of-process local server
#              providing a component version of the COPaper COM object.
#
#              DCDSERVE is meant to work in conjunction with the
#              DCOMDRAW.EXE client application produced in the
#              DCOMDRAW lesson.
#
#              This Makefile creates a subdirectory (TEMP) for the
#              .OBJ and .RES files used during the build process.  It also
#              automatically registers the newly built EXE server
#              as a COM server in the system Registry.  Since the build of
#              this makefile does this registration you must build the
#              REGISTER.EXE utility first (in sibling directory REGISTER).
#
#              For a comprehensive tutorial code tour of DCDSERVE's
#              contents and offerings see the tutorial DCDSERVE.HTM
#              file.  For more specific technical details see the comments
#              dispersed throughout the DCDSERVE source code.
#
#              See also DCOMDRAW.HTM (in the main tutorial directory)
#              for more details on the DCOMDRAW client application and how
#              it works with DCDSERVE.EXE.
#
#              In general, to set up your system to build and test the
#              Win32 code samples in this COM Tutorial series, see the
#              global TUTORIAL.HTM file for details.  This MAKEFILE is
#              Microsoft NMAKE compatible and the 'debug' build can be
#              achieved by simply issuing the NMAKE command in a
#              command prompt window.
#
#  Builds:     DCDSERVE.EXE.
#
#  Origin:     8-23-96: atrent - Editor-inheritance from LOCSERVE makefile.
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
TARGETOS=WINNT
!include <win32.mak>

# Assign the main program name macros.
PGM = dcdserve

# Use a temporary sub-directory to store intermediate
# binary files like *.obj, *.res, *.map, etc.
TDIR = TEMP

# Assign destination and consumer sibling directories.
IDIR = ..\inc
LDIR = ..\lib

REGEXE = ..\register\register.exe

# The sibling ..\INC and ..\LIB directories are added to the front of
# the INCLUDE and LIB macros to inform the compiler and linker of
# these application-specific locations for include and lib files.
INCLUDE=$(IDIR);$(INCLUDE)
LIB=$(LDIR);$(LIB)

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
PGMOBJS = $(TDIR)\$(PGM).obj $(TDIR)\server.obj $(TDIR)\factory.obj \
  $(TDIR)\connect.obj $(TDIR)\paper.obj

# The final target.
all: input tempdir output

# Check if prior builds were done.
input:
  @IF NOT EXIST $(REGEXE) echo !!!!!! You must build REGISTER first !!!!!!

# Make the temporary work sub-directory.
tempdir:
  -mkdir $(TDIR)

# The actual output products.
# Register the server after it's EXE is built.
output: $(PGM).exe
  if exist $(PGM).EXE if exist $(REGEXE) $(REGEXE) /e $(PGM).EXE

# Compilation/Dependency rules for the main source files.
#
$(TDIR)\$(PGM).obj: $(PGM).cpp $(PGM).h server.h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ $(PGM).cpp

$(TDIR)\server.obj: server.cpp server.h $(PGM).h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ server.cpp

$(TDIR)\factory.obj: factory.cpp factory.h server.h $(PGM).h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ factory.cpp

$(TDIR)\connect.obj: connect.cpp connect.h server.h $(PGM).h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ connect.cpp

$(TDIR)\paper.obj: paper.cpp paper.h server.h $(PGM).h
  $(cc) $(cvars) $(cflags) $(CDBG) -Fo$@ paper.cpp

# Compile the resources.
$(TDIR)\$(PGM).res: $(PGM).rc $(PGM).ico $(PGM).h
  rc $(RCFLAGS) -r -fo$@ $(PGM).rc

# Link the object and resource binaries into the target EXEL binary.
# Build the import LIB file so apps can link to and use this EXE.
$(PGM).exe: $(PGMOBJS) $(TDIR)\$(PGM).res
    $(LINK)  @<<
    $(LINKFLAGS)
    -out:$@
    -map:$(TDIR)\$*.map
    $(PGMOBJS)
    $(TDIR)\$*.res
    $(olelibs) $(APPLIBS)
<<


# Target to register the server
register:
  if exist $(PGM).EXE if exist $(REGEXE) $(REGEXE) /e $(PGM).EXE

# Target to unregister the server
unregister:
  if exist $(PGM).EXE if exist $(REGEXE) $(REGEXE) /e /u $(PGM).EXE

# Target to clean up binaries.
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
