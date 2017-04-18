#/*+=========================================================================
#  File:       MAKEFILE
#
#  Summary:    Makefile for building the PERSERVE.DLL executable.
#              PERSERVE is a COM Component In-process Server DLL providing
#              a persistent COPageList component. The persistence method
#              used is by implementation of the IPersistStream interface.
#
#              PERSERVE is meant to work in conjunction with the
#              PERCLIEN.EXE client application produced in the
#              PERCLIEN lesson.
#
#              This Makefile creates a subdirectory (TEMP) for the
#              .OBJ and .RES files used during the build process.  It also
#              automatically registers the newly built DLL server
#              as a COM server in the system Registry.  Since the build of
#              this makefile does this registration you must build the
#              REGISTER.EXE utility first (in sibling directory REGISTER).
#
#              For a comprehensive tutorial code tour of PERSERVE's
#              contents and offerings see the tutorial PERSERVE.HTM
#              file.  For more specific technical details see the comments
#              dispersed throughout the PERSERVE source code.
#
#              See also PERCLIEN.HTM (in the main tutorial directory)
#              for more details on the PERCLIEN client application and how
#              it works with PERSERVE.DLL.
#
#              In general, to set up your system to build and test the
#              Win32 code samples in this COM Tutorial series, see the
#              global TUTORIAL.HTM file for details.  This MAKEFILE is
#              Microsoft NMAKE compatible and the 'debug' build can be
#              achieved by simply issuing the NMAKE command in a
#              command prompt window.
#
#  Builds:     PERSERVE.DLL, PERSERVE.LIB
#
#  Origin:     6-10-96: atrent - Editor-inheritance from CONSERVE makefile.
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

# Assign the main program name macros.
DLL = perserve

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

# DLLOBJS is a macro that defines the object files for the DLL.
DLLOBJS = $(TDIR)\$(DLL).obj $(TDIR)\server.obj $(TDIR)\factory.obj \
  $(TDIR)\connect.obj $(TDIR)\pagelist.obj

# The final target.
all: input tempdir output

# Check if prior builds were done.
input:
  @IF NOT EXIST $(REGEXE) echo !!!!!! You must build REGISTER first !!!!!!

# Make the temporary work sub-directory.
tempdir:
  -mkdir $(TDIR)

# The actual output products.
# Register the server after it's DLL is built.
output: $(DLL).dll
  if exist $(DLL).DLL if exist $(REGEXE) $(REGEXE) $(DLL).dll

# Compilation/Dependency rules for the .DLL source files.
#
$(TDIR)\$(DLL).obj: $(DLL).cpp $(DLL).h server.h
  $(cc) $(cvarsdll) $(cflags) $(CDBG) -Fo$@ $(DLL).cpp

$(TDIR)\server.obj: server.cpp server.h $(DLL).h
  $(cc) $(cvarsdll) $(cflags) $(CDBG) -Fo$@ server.cpp

$(TDIR)\factory.obj: factory.cpp factory.h server.h $(DLL).h
  $(cc) $(cvarsdll) $(cflags) $(CDBG) -Fo$@ factory.cpp

$(TDIR)\connect.obj: connect.cpp connect.h server.h $(DLL).h
  $(cc) $(cvarsdll) $(cflags) $(CDBG) -Fo$@ connect.cpp

$(TDIR)\pagelist.obj: pagelist.cpp pagelist.h server.h $(DLL).h
  $(cc) $(cvarsdll) $(cflags) $(CDBG) -Fo$@ pagelist.cpp

# Compile the DLL resources.
$(TDIR)\$(DLL).res: $(DLL).rc $(DLL).ico server.h
  rc $(RCFLAGS) -r -fo$@ $(DLL).rc

# Link the object and resource binaries into the target DLL binary.
# Build the import LIB file so apps can link to and use this DLL.
$(DLL).dll: $(DLLOBJS) $(TDIR)\$(DLL).res
    $(LINK)  @<<
    $(LINKFLAGS) $(dlllflags)
    -out:$@
    -base:0x1C000000
    -def:$*.def
    -implib:$*.lib
    -map:$(TDIR)\$*.map
    $(DLLOBJS)
    $(TDIR)\$*.res
    $(olelibsdll) $(APPLIBS)
<<


# Target to register the server
register:
  if exist $(DLL).DLL if exist $(REGEXE) $(REGEXE) $(DLL).dll

# Target to unregister the server
unregister:
  if exist $(DLL).DLL if exist $(REGEXE) $(REGEXE) /u $(DLL).dll

# Target to clean up binaries.
clean:
  -del $(DLL).exp
  -del $(DLL).lib
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
