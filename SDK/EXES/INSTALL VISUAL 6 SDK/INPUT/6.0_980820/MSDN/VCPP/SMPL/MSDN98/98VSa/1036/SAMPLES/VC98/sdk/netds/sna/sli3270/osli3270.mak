

#
#  You should have previously set LIB and INCLUDE environment variables
#  referencing your C compiler and OS/2 Toolkit subdirectories.
#  Consult your compiler documentation and OS/2 Toolkit documentation
#  for instructions on defining these variables.
#
#
#  Compiler Switches:
#   -c  = Compile only, no link
#   -AL = Using the Large memory model.
#   -Gs = Remove stack probes - Use only on fully debugged program.
#   -Ox = Maximum optimization
#   -Zl = Suppress default library selection.
#   -Zp = Pack structure members - OS/2 API calls expect packed structures.
#   -Ze = Enable special keywords.
#   -W4 = Maximum warning level

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing ACS.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing LUA_C.H and ACSSVCC.H"
!endif

C_OPTIONS = -c -AL -G2 -Ongt -W2 -Zlp -DOS2 -DDOS5

LIBLIST = doscalls llibcmt $(ISVLIBS)\acssvc.lib $(ISVLIBS)\acssli.lib /NOD
MAP = os2.map /map
LINK_OPTIONS = /EXEPACK /ST:8000 /PMTYPE:vio /CO
INCLUDE = $(ISVINCS);$(INCLUDE);


sli3270: sli3270.exe

sli3270.EXE: sli3270.OBJ
        LINK sli3270.OBJ $(LINK_OPTIONS), $*, $(MAP), $(LIBLIST) , ;

sli3270.OBJ: sli3270.c
        CL $(C_OPTIONS) $*.C




