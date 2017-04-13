!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=dpslots

mycflags=/D STRICT

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\lobby.obj $(OBJ_DIR)\dialog.obj $(OBJ_DIR)\client.obj $(OBJ_DIR)\server.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp dpslots.h
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).cpp
	
$(OBJ_DIR)\client.obj:  client.cpp
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\client.obj $(cvars) client.cpp

$(OBJ_DIR)\server.obj:  server.cpp
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\server.obj $(cvars) server.cpp

$(OBJ_DIR)\lobby.obj:  lobby.cpp 
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\lobby.obj $(cvars) lobby.cpp

$(OBJ_DIR)\dialog.obj:  dialog.cpp
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\dialog.obj $(cvars) dialog.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) uuid.lib ole32.lib winmm.lib

mkdir:
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@rd Retail
    -@rd Debug
