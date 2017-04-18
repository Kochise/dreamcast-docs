!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=dsstream

OBJ_LIST = $(OBJ_DIR)\debug.obj $(OBJ_DIR)\wassert.obj \
           $(OBJ_DIR)\dsstream.obj $(OBJ_DIR)\dstrenum.obj \
           $(OBJ_DIR)\dstrwave.obj $(OBJ_DIR)\notify.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\debug.obj: debug.c debug.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\debug.obj $(cvars) debug.c

$(OBJ_DIR)\wassert.obj: wassert.c wassert.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\wassert.obj $(cvars) wassert.c 

$(OBJ_DIR)\dsstream.obj: dsstream.c dsstream.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dsstream.obj $(cvars) dsstream.c 

$(OBJ_DIR)\dstrenum.obj: dstrenum.c dsstream.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dstrenum.obj $(cvars) dstrenum.c

$(OBJ_DIR)\dstrwave.obj: dstrwave.c dsstream.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dstrwave.obj $(cvars) dstrwave.c

$(OBJ_DIR)\notify.obj: notify.c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\notify.obj $(cvars) notify.c


$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(proj).def $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) winmm.lib dsound.lib comctl32.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
