!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=d3dex1

OBJ_LIST = $(OBJ_DIR)\$(proj).obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).c resource.h
    $(cc) $(cdebug) $(cflags) $(cvars) -Fo$(OBJ_DIR)\$(proj).obj $(proj).c
	
$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc


$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST)  $(proj).def $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)

# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
