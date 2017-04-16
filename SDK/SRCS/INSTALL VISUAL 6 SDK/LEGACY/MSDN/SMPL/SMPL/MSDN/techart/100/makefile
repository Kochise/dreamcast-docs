# Makefile : Builds the owner application
#
# Usage:     NMAKE option (build owner and ownerdll)
#    or:     NMAKE clean  (erase all compiled files)
#
# options:   DEBUG=[0|1]  (DEBUG not defined is equivalent to DEBUG=0)
#																		
#
# examples: nmake DEBUG=1  Compile owner and ownerdll with the MFC debug libs.
#									Ownder and Ownerdll are compile with codeview info
#									regardless of this switch.
#
!IF "$(DEBUG)"=="1"
DEFS=-D_DEBUG
D=D
!MESSAGE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!MESSAGE ! The debug version of this program will fail	!
!MESSAGE ! an assertion in memory.cpp.  						!
!MESSAGE ! The non-debug version will run fine.				!
!MESSAGE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!ELSE
DEFS=
D=
!ENDIF
#
#Build Application
#
owner.exe: owner.obj owner.def owner.res ownerdll.lib
	link /MAP:FULL /NOD /ONERROR:NOEXE @<<
owner
owner.exe
nul
lafxcw$(D) libw llibcew ownerdll
owner.def;
<<
	rc /t owner.res

owner.res: owner.rc owner.ico

owner.obj: owner.cpp ownerdll.h
	cl $(DEFS) /AL /GA /Zp /Od /c owner.cpp

#
# Build the ownerdll DLL
#
ownerdll.lib: ownerdll.dll 
	implib /NOL ownerdll.lib ownerdll.dll

ownerdll.dll: ownerdll.obj
	link /NOD /MAP:FULL /ONERROR:NOEXE /PACKDATA @<<
ownerdll,
ownerdll.dll,
nul,
lafxdw$(D) libw ldllcew,
ownerdll.def;
<<
	rc /t ownerdll.dll


ownerdll.obj: ownerdll.cpp ownerdll.h 
	cl $(DEFS) /ALw /GD /GEe /Zp /Od /c ownerdll.cpp


clean:
	-del owner.exe
	-del ownerdll.dll
	-del *.obj
	-del *.map
	-del *.sym
	-del *.res
	-del *.lib

