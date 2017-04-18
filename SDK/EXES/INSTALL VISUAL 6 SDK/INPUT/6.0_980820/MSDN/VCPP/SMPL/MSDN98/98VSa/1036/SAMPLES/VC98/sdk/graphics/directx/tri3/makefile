!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

mycflag=-DD3DRMDEMO -DD3D_OVERLOADS

proj=tri3

OBJ_LIST = $(OBJ_DIR)\triangle.obj $(OBJ_DIR)\d3dapp.obj \
           $(OBJ_DIR)\ddcalls.obj $(OBJ_DIR)\d3dcalls.obj \
           $(OBJ_DIR)\texture.obj $(OBJ_DIR)\misc.obj \
           $(OBJ_DIR)\d3dmain.obj $(OBJ_DIR)\stats.obj \
           $(OBJ_DIR)\lclib.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\triangle.obj:  triangle.c 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\triangle.obj $(mycflag) \
    $(cvars) triangle.c

$(OBJ_DIR)\d3dapp.obj:  d3dapp.c d3dapp.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\d3dapp.obj $(mycflag) \
    $(cvars) d3dapp.c

$(OBJ_DIR)\ddcalls.obj:  ddcalls.c 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\ddcalls.obj $(mycflag) \
    $(cvars) ddcalls.c

$(OBJ_DIR)\d3dcalls.obj:  d3dcalls.c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\d3dcalls.obj $(mycflag) \
    $(cvars) d3dcalls.c

$(OBJ_DIR)\texture.obj:  texture.c 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\texture.obj $(mycflag) \
    $(cvars) texture.c

$(OBJ_DIR)\misc.obj:  misc.c 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\misc.obj $(mycflag) \
    $(cvars) misc.c

$(OBJ_DIR)\d3dmain.obj:  d3dmain.cpp d3dmain.h
    $(cc) $(cdebug) -Fo$(OBJ_DIR)\d3dmain.obj $(cflags) $(mycflag) \
    $(cvars) d3dmain.cpp

$(OBJ_DIR)\stats.obj:  stats.cpp 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\stats.obj $(mycflag) \
    $(cvars) stats.cpp

$(OBJ_DIR)\lclib.obj:  lclib.c lclib.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\lclib.obj $(mycflag) \
    $(cvars) lclib.c

$(OBJ_DIR)\d3dmain.res: d3dmain.rc
   rc -i..\misc -r -fo  $(OBJ_DIR)\d3dmain.res d3dmain.rc
	

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\d3dmain.res $(proj).def  
     $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\d3dmain.res \
           $(guilibs) ddraw.lib d3drm.lib

mkdir:
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@echo y | del Retail
    -@echo y | del Debug
    -@rd Retail
    -@rd Debug           
    -@rd Retail
    -@rd Debug           
