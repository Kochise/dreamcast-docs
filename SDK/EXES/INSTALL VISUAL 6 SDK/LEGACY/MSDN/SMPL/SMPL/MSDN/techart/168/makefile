#   Windows Edit Control Text Test App
#   Makefile
#


#Remove '#' from next line for "silent" operation
!CMDSWITCHES +s

#Compiler and assembler flags
CFLAGS=-c -Gsw -W2 -AS -Od -Zp
AFLAGS  = -MX -Z -Zi -L

#Standard definitions.
DEFS=-DDEBUG


#Files on which every C file depends.  Add others as appropriate
INCLS=aligned.h

.SUFFIXES: .h .c .asm .obj .exe .cxx .res .rc .bas

goal:  aligned.exe


OBJS   =aligned.obj
RCFILES=aligned.ico

#####

.c.obj:
    echo ++++++++++
    echo Compiling $*.c
    cl $(CFLAGS) $(DEFS) $*.c


.asm.obj:
    echo +++++++++
    echo ASSEMBLING $*.asm
    masm $(AFLAGS) $(DEFS) $*.asm


.rc.res:
    echo +++++++++
    echo Compiling Resources
    rc -r $*.rc


aligned.exe : $(OBJS) aligned.res
    link @<<
	   aligned
	   aligned /al:16
	   /map/li
	   libw slibcew/NOD/NOE
	   aligned.def
<<
    rc aligned.res




##### Dependencies #####

aligned.obj    : aligned.c    $(INCLS)
aligned.res    : aligned.rc   $(INCLS) $(RCFILES)

clean:
    -del *.obj
    -del *.res
    -del *.sym
    -del *.map
