!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=flipcube

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\tri.obj $(OBJ_DIR)\dumb3d.obj

all: mkdir $(OBJ_DIR)\flip2d.exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).cpp

$(OBJ_DIR)\tri.obj:  tri.cpp 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\tri.obj $(cvars) tri.cpp

$(OBJ_DIR)\dumb3d.obj:  dumb3d.cpp dumb3d.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dumb3d.obj $(cvars) dumb3d.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc
	

$(OBJ_DIR)\flip2d.exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res 
     $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\flip2d.exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib winmm.lib dinput.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
