#
# INOLE2A.MAK
# Common Compiler Flags and Definitions
#
# Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#
# This makefile (and inole2b.mak) builds Win16/Win32,
# and DEBUG/NODEBUG versions.  The default build is Win32 DEBUG.
#
# To build different versions set the appropriate environment
# variable below with "SET <variable>=1:
#
#   Variable    Effect
#   -------------------------------
#   CLEAN       Cleans up compiled files, overriding all other functions
#   NODEBUG     Build non-debug version
#   WIN16       Build 16-bit version
#
# In addition, other makefiles control other compilation
# aspects with these variables:
#
#   Variable    Effect
#   -------------------------------------------
#   DEFFILE     The .DEF file to use
#   TARGET      The main filename (no extension) of the project
#   NOPRECOMP   Suppresses creation of precompiled header
#   PCHINC      Alternate header to precompile (default is $(TARGET).H
#

!ifndef WIN16
DEFUNICODE = -DUNICODE -D_UNICODE
!else
DEFUNICODE =
!endif

!ifndef WIN16
CL32    = -G3s
LINKD32 = -debug:full -debugtype:cv
LINKN32 = -debug:none
DEFS32  = -DWIN32 -D_X86_=1 $(DEFUNICODE)
LIBS32A = crtdll.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib
LIBS32B = ole32.lib uuid.lib bookui32.lib
LIBS32  = $(LIBS32A) $(LIBS32B)

!else

CL32    = -G2s -AL -Gx -GA
LINKD32 = /al:16/ONERROR:NOEXE/CO
LINKN32 = /al:16/ONERROR:NOEXE
DEFS32  = -DWIN16

CRTLIB  = llibcew
LIBS32  = libw $(CRTLIB) commdlg compobj storage ole2 bookui

!endif

CLASSLIB= classMDI.lib

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
!endif

PCHFILE = precomp.pch
PCHFLAGS= -Yu$(PCHINC) -Fpprecomp.pch
!endif


#
#Compiler flags
#Use "SET NODEBUG=1" from command prompt to compile non-debug version.
#

!ifndef NODEBUG
CFLAGS  = -c -Od -Z7 -Ze -W3 -nologo $(CL32)
LINK    = $(LINKD32) /NOD
DEFS    = $(DEFS32) -DSTRICT -DMDI -DDEBUG
LIBS    = bttncur.lib gizmobar.lib stastrip.lib $(CLASSLIB)
!else
CFLAGS  = -c -Oat -Ze -W3 -nologo $(CL32)
LINK    = $(LINKN32) /NOD
DEFS    = $(DEFS32) -DSTRICT -DMDI
LIBS    = bttncur.lib gizmobar.lib stastrip.lib $(CLASSLIB)
!endif

.SUFFIXES: .h .obj .exe .dll .cpp .res .rc

!ifdef CLEAN
goal:   clean
!else
goal:   $(PCHFILE) $(OUTFILE)
!endif

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



#####

.c.obj:
    echo ++++++++++
    echo Compiling $*.c
    cl $(CFLAGS) $(PCHFLAGS) $(DEFS) $*.c


.cpp.obj:
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(PCHFLAGS) $(DEFS) $*.cpp


.rc.res:
    echo +++++++++
    echo Compiling Resources
    rc -r $(DEFS) $(DOC) -fo$@ $*.rc


precomp.pch : $(INCLS)
    echo +++++++++
    echo Precompiling $(PCHINC)
    cl $(CFLAGS) $(DEFS) $(DOC) -Yc$(PCHINC) -Fpprecomp.pch -Foprecomp precomp.cpp
