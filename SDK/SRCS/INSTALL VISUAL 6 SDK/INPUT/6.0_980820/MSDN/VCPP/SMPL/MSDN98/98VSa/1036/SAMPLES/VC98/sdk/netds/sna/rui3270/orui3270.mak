

#
#  You should have previously set LIB and INCLUDE environment variables
#  referencing your C compiler and OS/2 Toolkit subdirectories.
#  Consult your compiler documentation and OS/2 Toolkit documentation
#  for instructions on defining these variables.
#

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing ACS.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing LUA_C.H and ACSSVCC.H"
!endif

C_OPTIONS = -c -AL -G2 -Ongt -W2 -Zlp -DOS2 -DDOS5

LIBLIST = doscalls llibcmt $(ISVLIBS)\acs.lib /NOD
MAP = NUL
LINK_OPTIONS = /EXEPACK /ST:8000 /PMTYPE:vio /CO
INCLUDE = $(ISVINCS);$(INCLUDE);


rui3270: rui3270.exe

rui3270.EXE: rui3270.OBJ
        LINK rui3270.OBJ $(LINK_OPTIONS), $*, $(MAP), $(LIBLIST) , ;

rui3270.OBJ: rui3270.c
        CL $(C_OPTIONS) $*.C




