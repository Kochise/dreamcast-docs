!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

mycflag=/I "..\misc"

proj=flip3d

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\d3dtex.obj \
           $(OBJ_DIR)\dumb3d.obj


all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  flipcube.cpp flipcube.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) flipcube.cpp

$(OBJ_DIR)\d3dtex.obj:  d3dtex.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\d3dtex.obj $(mycflag) \
    $(cvars) d3dtex.cpp

$(OBJ_DIR)\dumb3d.obj:  dumb3d.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dumb3d.obj $(mycflag) \
    $(cvars) dumb3d.cpp

$(OBJ_DIR)\$(proj).res: flipcube.rc
   rc -r -fo $(OBJ_DIR)\$(proj).res flipcube.rc
	

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res  
     $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib d3drm.lib dxguid.lib winmm.lib
           
mkdir:
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@rd Retail
    -@rd Debug           
