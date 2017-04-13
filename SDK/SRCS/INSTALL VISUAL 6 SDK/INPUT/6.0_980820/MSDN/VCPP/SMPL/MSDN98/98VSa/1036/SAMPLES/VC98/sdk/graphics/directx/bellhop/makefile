!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=bellhop

mycflags=/D STRICT

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\lobby.obj $(OBJ_DIR)\dialog.obj $(OBJ_DIR)\cgrptree.obj $(OBJ_DIR)\connset.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp bellhop.h cgrptree.h
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).cpp
	
$(OBJ_DIR)\lobby.obj:  lobby.cpp 
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\lobby.obj $(cvars) lobby.cpp

$(OBJ_DIR)\dialog.obj:  dialog.cpp
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\dialog.obj $(cvars) dialog.cpp

$(OBJ_DIR)\cgrptree.obj:  cgrptree.cpp  cgrptree.h
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\cgrptree.obj $(cvars) cgrptree.cpp

$(OBJ_DIR)\connset.obj:  connset.cpp
    $(cc) $(cdebug) $(cflags) $(mycflags) -Fo$(OBJ_DIR)\connset.obj $(cvars) connset.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) uuid.lib ole32.lib dplayx.lib comctl32.lib gdi32.lib

mkdir:
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@rd Retail
    -@rd Debug
