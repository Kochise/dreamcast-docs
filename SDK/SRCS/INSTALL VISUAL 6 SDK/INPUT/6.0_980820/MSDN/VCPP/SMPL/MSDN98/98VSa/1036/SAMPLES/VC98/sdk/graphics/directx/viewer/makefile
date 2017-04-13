!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=viewer

OBJ_LIST  = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\sel.obj $(OBJ_DIR)\file.obj \
	    $(OBJ_DIR)\color.obj $(OBJ_DIR)\rodcone.obj \
	    $(OBJ_DIR)\getdxver.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp  $(proj).h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).cpp
	
$(OBJ_DIR)\sel.obj:  sel.cpp  sel.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\sel.obj $(cvars) sel.cpp

$(OBJ_DIR)\file.obj:  file.cpp  
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\file.obj $(cvars) file.cpp

$(OBJ_DIR)\color.obj: color.cpp  
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\color.obj $(cvars) color.cpp

$(OBJ_DIR)\rodcone.obj:  rodcone.cpp  rodcone.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\rodcone.obj $(cvars) rodcone.cpp

$(OBJ_DIR)\getdxver.obj:  getdxver.cpp  viewer.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\getdxver.obj $(cvars) getdxver.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc 
   rc -i..\misc -r -fo  $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
	   $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
	   $(guilibs) ddraw.lib  d3drm.lib comdlg32.lib winmm.lib msvcrt.lib

mkdir:
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@rd Retail
    -@rd Debug
