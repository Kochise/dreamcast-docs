!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=boids
cflags = -DUSE_FLOAT -DD3DDEMO $(cflags)

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\d3dwin.obj \
           $(OBJ_DIR)\drvmgr.obj $(OBJ_DIR)\winproc.obj \
           $(OBJ_DIR)\debug.obj $(OBJ_DIR)\winmain.obj \
           $(OBJ_DIR)\d3dutils.obj $(OBJ_DIR)\getdxver.obj \
           $(OBJ_DIR)\flock.obj $(OBJ_DIR)\d3dtex.obj

mycflag=/I "..\misc"

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp resource.h 
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) $(proj).cpp

$(OBJ_DIR)\d3dwin.obj:  d3dwin.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\d3dwin.obj $(mycflag) \
    $(cvars) d3dwin.cpp

$(OBJ_DIR)\drvmgr.obj:  drvmgr.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\drvmgr.obj $(mycflag) \
    $(cvars) drvmgr.cpp

$(OBJ_DIR)\debug.obj:  debug.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\debug.obj $(mycflag) \
    $(cvars) debug.cpp

$(OBJ_DIR)\winmain.obj:  winmain.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\winmain.obj $(mycflag) \
    $(cvars) winmain.cpp

$(OBJ_DIR)\winproc.obj:  winproc.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\winproc.obj $(mycflag) \
    $(cvars) winproc.cpp

$(OBJ_DIR)\d3dutils.obj:  d3dutils.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\d3dutils.obj $(mycflag) \
    $(cvars) d3dutils.cpp
        
$(OBJ_DIR)\getdxver.obj:  getdxver.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\getdxver.obj $(mycflag) \
    $(cvars) getdxver.cpp

$(OBJ_DIR)\flock.obj:  flock.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\flock.obj $(mycflag) \
    $(cvars) flock.cpp

$(OBJ_DIR)\d3dtex.obj:  d3dtex.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\d3dtex.obj $(mycflag) \
    $(cvars) d3dtex.cpp

$(OBJ_DIR)\$(proj).res: boids2.rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res boids2.rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib winmm.lib
mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@rd Retail
    -@rd Debug

