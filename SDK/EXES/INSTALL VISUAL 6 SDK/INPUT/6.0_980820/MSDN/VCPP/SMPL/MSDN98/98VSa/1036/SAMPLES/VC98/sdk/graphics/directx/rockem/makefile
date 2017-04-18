!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=rockem3d

OBJ_LIST = $(OBJ_DIR)\control.obj $(OBJ_DIR)\directx.obj \
           $(OBJ_DIR)\midi.obj $(OBJ_DIR)\winmain.obj $(OBJ_DIR)\rm.obj

mycflag=-DD3DRMDEMO

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\control.obj: control.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\control.obj $(cvars) control.cpp

$(OBJ_DIR)\directx.obj: directx.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\directx.obj $(cvars) directx.cpp

$(OBJ_DIR)\midi.obj: midi.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\midi.obj $(cvars) midi.cpp

$(OBJ_DIR)\rm.obj: rm.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\rm.obj $(cvars) rm.cpp

$(OBJ_DIR)\winmain.obj: winmain.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\winmain.obj $(cvars) winmain.cpp

$(OBJ_DIR)\rockem3d.res: rockem3d.rc
   $(rc) -r -fo $(OBJ_DIR)\rockem3d.res  rockem3d.rc
	

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\rockem3d.res 
     $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\rockem3d.res \
           $(guilibs) ddraw.lib dsound.lib winmm.lib d3drm.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
