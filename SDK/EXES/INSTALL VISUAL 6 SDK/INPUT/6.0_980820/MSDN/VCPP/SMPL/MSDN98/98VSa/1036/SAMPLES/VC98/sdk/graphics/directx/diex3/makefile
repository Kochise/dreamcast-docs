!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=diex3

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp $(proj).h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).cpp
	
$(OBJ_DIR)\$(proj).res: $(proj).rc
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\$(proj).res \
           $(guilibs) dinput.lib dxguid.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
