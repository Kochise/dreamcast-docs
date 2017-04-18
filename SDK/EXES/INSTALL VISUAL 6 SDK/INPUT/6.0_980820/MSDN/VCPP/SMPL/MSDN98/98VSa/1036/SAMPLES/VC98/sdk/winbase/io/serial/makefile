# Windows-32 TTY Example
# Copyright 1992 - 1997 Microsoft Corporation

!include <WIN32.MAK>

proj = TTY

all: $(proj).exe

# Update the resource if necessary
$(proj).res: $(proj).rc resource.h
    rc -r -fo $(proj).res $(cvars) $(proj).rc


# Update the object file if necessary
$(proj).obj: $(proj).c $(proj).h
    $(cc) $(cdebug) $(cflags) $(cvars) $(proj).c


# Update the EXE
$(proj).exe: $(proj).obj $(proj).res $(proj).def
    $(link) $(linkdebug) $(guiflags) $(proj).obj  $(guilibs) VERSION.LIB $(proj).res -out:$(proj).exe
