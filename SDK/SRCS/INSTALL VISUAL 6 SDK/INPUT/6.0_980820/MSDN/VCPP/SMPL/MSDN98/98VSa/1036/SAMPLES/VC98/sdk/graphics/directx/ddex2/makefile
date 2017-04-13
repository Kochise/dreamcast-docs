!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=ddex2

OBJ_LIST = $(OBJ_DIR)\$(proj).obj ..\misc\$(OBJ_DIR)\ddutil.obj

mycflag=/I "..\misc"

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).cpp resource.h ..\misc\ddutil.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) $(proj).cpp
	
..\misc\$(OBJ_DIR)\ddutil.obj:  ..\misc\ddutil.cpp ..\misc\ddutil.h
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\ddutil.obj $(mycflag) \
    $(cvars) ..\misc\ddutil.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(proj).def $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    if not exist ..\misc\$(OBJ_DIR)\NUL md ..\misc\$(OBJ_DIR)

# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -echo y | del ..\misc\Retail
    -echo y | del ..\misc\Debug
    -rd Retail
    -rd Debug
    -rd ..\misc\Retail
    -rd ..\misc\Debug
