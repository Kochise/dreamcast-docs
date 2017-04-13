
#
#  This makefile is intended for use for the Microsoft C Compiler,
#  version 6.0.
#
#  You should have previously set LIB and INCLUDE environment variables
#  referencing your C compiler subdirectories.  Consult your compiler
#  documentation for instructions on defining these variables.
#

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing DOSACS.LIB
!endif

!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINRUI.H and WINCSV.H"
!endif

C_OPTIONS=/c /AS /Gc0s /Zp /W2 /D PDOS
LIBLIST = $(ISVLIBS)\dosacs.lib slibce.lib
INCLUDE = $(ISVINCS);$(INCLUDE);

MAP = nul
LINK_OPTIONS = /NOD /EXEPACK

drui3270.EXE: rui3270.OBJ drui3270.mak
        LINK rui3270.OBJ $(LINK_OPTIONS), $*, $(MAP), $(LIBLIST) , ;

rui3270.OBJ: rui3270.c drui3270.mak
        CL $(C_OPTIONS) $*.C
