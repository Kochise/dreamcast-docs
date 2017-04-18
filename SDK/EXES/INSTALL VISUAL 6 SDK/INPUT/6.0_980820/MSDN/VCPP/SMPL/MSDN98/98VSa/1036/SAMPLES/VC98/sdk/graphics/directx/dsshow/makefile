!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=dsshow

OBJ_LIST = $(OBJ_DIR)\wave.obj $(OBJ_DIR)\shell.obj $(OBJ_DIR)\dsenum.obj \
           $(OBJ_DIR)\wassert.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\wave.obj: wave.c wave.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\wave.obj $(cvars) wave.c

$(OBJ_DIR)\shell.obj: shell.c shell.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\shell.obj $(cvars) shell.c 

$(OBJ_DIR)\dsenum.obj: dsenum.c dsenum.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dsenum.obj $(cvars) dsenum.c 

$(OBJ_DIR)\wassert.obj: wassert.c wassert.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\wassert.obj $(cvars) wassert.c


$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(proj).def $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) dsound.lib winmm.lib msacm32.lib ole32.lib uuid.lib \
           comctl32.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
