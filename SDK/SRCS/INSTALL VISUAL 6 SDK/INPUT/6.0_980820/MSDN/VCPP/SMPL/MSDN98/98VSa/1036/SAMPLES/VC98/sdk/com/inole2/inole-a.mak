#
# INOLE-A.MAK
# Common Compiler Flags and Definitions
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#
# This makefile (and inole-b.mak) builds Win16/Win32, Unicode/ANSI,
# MDI/SDI, and DEBUG/NODEBUG versions.  The default build is Win32,
# Unicode, MDI, DEBUG.
#
# To build different versions set the appropriate environment
# variable below with "SET <variable>=1:
#
#   Variable    Effect
#   -------------------------------
#   UNICODE     Build Unicode version
#   CLEAN       Cleans up compiled files, overriding all other functions
#   NODEBUG     Build non-debug version
#   SDI         Build SDI version
#   WIN16       Build 16-bit version
#
# In addition, other makefiles control other compilation
# aspects with these variables:
#
#   Variable    Effect
#   -------------------------------------------
#   TARGET      The main filename (no extension) of the project
#   DLL         Switches compiler/linker flags for a DLL.
#   OUTFILE     The final output filename
#   PCHINC      Alternate header to precompile (default is $(TARGET).H
#   TLBHEAD     Name of a type library output header file with /h
#   NODOC       Disables SDI/MDI differences
#   NOPRECOMP   Suppresses creation of precompiled header
#   NOUILIB     Prevents inclusion of UI library during linking
#   NOCLASSLIB  Prevents inclusion of class libraries during linking
#   NOBOOKLIB   Prevents includion of INOLE.LIB
#   NOOCLIB     Prevents includion of OLE Controls run-time
#



!ifdef WIN16
DEFUNICODE =
TLBDEFU    =
!else
!ifdef UNICODE
DEFUNICODE = -DUNICODE -D_UNICODE
TLBDEFU    = -DUNICODE
#Comment the next line and remove the comment from the next one
#for compiling on Windows NT 3.5.
UILIB32    = oledlg.lib
#UILIB32    = mfcuiw32.lib
!else
DEFUNICODE = -DWIN32ANSI
TLBDEFU    =
#Comment the next line and remove the comment from the next one
#for compiling on Windows NT 3.5.
UILIB32    = oledlg.lib
#UILIB32    = mfcuia32.lib
!endif
!endif

!ifdef NOBOOKLIB
BOOKLIB =
!else
BOOKLIB =  ..\..\lib\inole.lib 
!endif #NOBOOKLIB


!ifndef WIN16

CL32    = -G3s
WX      =

!ifdef DLL
LINKDLL = /DLL
DEFDLL  = -D_DLL
ENTRY   = -entry:LibMain32
!else
LINKDLL =
DEFDLL  =
ENTRY   = ""
!endif  #DLL

!ifdef NOUILIB
UILIB   =
!else
#MFCUI*32.LIB both map to OLEDLG.DLL when available
UILIB   = $(UILIB32)
!endif #NOUILIB

!ifdef NOOCLIB
OCLIB   =
!else
!ifdef UNICODE
OCLIB   = OLEPRO32.LIB
!else
OCLIB   = OLEPRO32.LIB
!endif

!endif #NOOCLIB


LINKD32 = -debug:full $(LINKDLL) -debugtype:cv
LINKN32 = -debug:none $(LINKDLL)
DEFS32  = -DWIN32 $(DEFDLL) -D_X86_=1 $(DEFUNICODE)
TLBDEFS = -DWIN32
LIBS32A = msvcrt.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib
LIBS32B = ole32.lib oleaut32.lib uuid.lib $(UILIB) $(OCLIB)
LIBS32  = $(LIBS32A) $(LIBS32B) $(BOOKLIB)

!else  #!WIN32

WX      = wx /w

!ifdef DLL
CL32    = -G2s -AL -GD /I$(MSTOOLS)\SAMPLES\OLE\INOLE2\INC /I ..\..\INC /I ..\INC
!else
CL32    = -G2s -AL -Gx -GA /I$(MSTOOLS)\SAMPLES\OLE\INOLE2\INC /I ..\..\INC /I ..\INC
!endif #DLL

LINKD32 = /al:16/ONERROR:NOEXE/CO
LINKN32 = /al:16/ONERROR:NOEXE
DEFS32  = -DWIN16
TLBDEFS = -DWIN16

!ifdef NOUILIB
UILIB   =
!else
UILIB   = mfcoleui
!endif #NOUILIB

!ifdef NOOCLIB
OCLIB   =
!else
OCLIB   = OC25.LIB
!endif #NOOCLIB


!ifdef DLL
CRTLIB  = ldllcew
!else
CRTLIB  = llibcew
!endif #DLL

LIBS32A = libw $(CRTLIB) oldnames commdlg shell $(BOOKLIB)
LIBS32B = compobj storage ole2 ole2disp ole2nls typelib $(UILIB)
LIBS32  = $(LIBS32A) $(LIBS32B)

!endif #!WIN32

TLBFLAGS = /cpp_opt "/C /E /D__MKTYPLIB__ $(TLBDEFU) $(TLBDEFS)"



!ifdef NODOC
DOC     =
CLASSLIB= ..\..\lib\classMDI.lib 
!else
!ifdef SDI
DOC     = -DSDI
CLASSLIB= classSDI.lib
!else
DOC     = -DMDI
CLASSLIB= ..\..\lib\classMDI.lib
!endif #SDI
!endif #NODOC

#
# Set up precompiled header flags.  By default we'll look for
# $(TARGET).H but a specific makefile can override by defining
# the symbol PCHINC
#

!ifdef NOPRECOMP
PCHFILE =
PCHFLAGS=
!else

!ifndef PCHINC
PCHINC  = $(TARGET).h
!endif #PCHINC

PCHFILE = precomp.pch
PCHFLAGS= -Yu$(PCHINC) -Fpprecomp.pch
!endif #NOPRECOMP


#
#Compiler flags
#Use "SET NODEBUG=1" from command prompt to compile non-debug version.
#

!ifndef NODEBUG
CFLAGS  = -c -Od -Z7 -Ze -W3 -nologo $(CL32)
LINK    = $(LINKD32) /NOD
DEFS    = $(DEFS32) -DSTRICT -DDEBUG
!else
CFLAGS  = -c -Oat -Ze -W3 -nologo $(CL32)
LINK    = $(LINKN32) /NOD
DEFS    = $(DEFS32) -DSTRICT
!endif #NODEBUG
CFLAGS = $(CFLAGS) /I $(MSTOOLS)\samples\ole\inole2\inc /I ..\..\INC /I ..\INC

!ifdef NOCLASSLIB
LIBS    = $(LIBS32A) $(OCLIB)
CONTIN  =
!else
LIBS    = $(CLASSLIB) $(OCLIB)
CONTIN  = +
!endif #NOCLASSLIB


.SUFFIXES: .h .obj .exe .dll .cpp .res .rc .tlb .odl

!ifdef CLEAN
goal:   clean
!else
goal:   $(PCHFILE) $(OUTFILE)
!endif #CLEAN

clean:
    if exist *.pch del *.pch
    if exist *.obj del *.obj
    if exist *.res del *.res
    if exist *.exe del *.exe
    if exist *.dll del *.dll
    if exist *.pdb del *.pdb
    if exist *.exp del *.exp
    if exist *.lib del *.lib
    if exist *.ilk del *.ilk
    if exist *.map del *.map
    if exist *.vcp del *.vcp
    if exist *.tlb del *.tlb
    if exist *.log del *.log
    if exist *.lrf del *.lrf

Enforce32Bits:
    echo This sample can only be compiled for 32-bit platforms


#####

.c.obj:
    echo ++++++++++
    echo Compiling $*.c
    cl $(CFLAGS) $(PCHFLAGS) $(DEFS) $(DOC) $*.c


.cpp.obj:
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(PCHFLAGS) $(DEFS) $(DOC) $*.cpp


.rc.res:
    echo ++++++++++
    echo Compiling Resources
    rc -r $(DEFS) $(DOC) -fo$@ /I $(MSTOOLS)\SAMPLES\OLE\INOLE2\INC  /I ..\..\INC  /I ..\INC $*.rc

.odl.tlb:
    echo ++++++++++
    echo Compiling $*.odl
    $(WX) mktyplib /nologo $(TLBFLAGS) $(TLBHEAD) /o $*.log $*.odl


precomp.pch : $(INCLS)
    echo ++++++++++
    echo Precompiling $(PCHINC)
    cl $(CFLAGS) $(DEFS) $(DOC) -Yc$(PCHINC) -Fpprecomp.pch -Foprecomp precomp.cpp
