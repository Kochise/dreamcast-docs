!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=fdfilter

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\debug.obj \
           $(OBJ_DIR)\fdaudio.obj $(OBJ_DIR)\gargle.obj \
           $(OBJ_DIR)\filter.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp resource.h ..\misc\ddutil.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).cpp
	
$(OBJ_DIR)\debug.obj:  debug.c debug.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\debug.obj $(cvars) debug.c

$(OBJ_DIR)\fdaudio.obj:  fdaudio.cpp fdaudio.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\fdaudio.obj $(cvars) fdaudio.cpp

$(OBJ_DIR)\gargle.obj:  gargle.cpp
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\gargle.obj $(cvars) gargle.cpp

$(OBJ_DIR)\filter.obj:  filter.cpp filter.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\filter.obj $(cvars) filter.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(proj).def $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib dsound.lib uuid.lib winmm.lib comctl32.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
