!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=dpchat

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\lobby.obj $(OBJ_DIR)\dialog.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp dpchat.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).cpp
	
$(OBJ_DIR)\lobby.obj:  lobby.cpp 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\lobby.obj $(cvars) lobby.cpp

$(OBJ_DIR)\dialog.obj:  dialog.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dialog.obj $(cvars) dialog.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) dplayx.lib ole32.lib uuid.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
