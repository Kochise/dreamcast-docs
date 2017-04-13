!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=stretch3

OBJ_LIST = $(OBJ_DIR)\$(proj).obj ..\misc\$(OBJ_DIR)\ddmm.obj \
           ..\misc\$(OBJ_DIR)\ddutil2.obj

mycflag=/I "..\misc"

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  stretch.cpp resource.h ..\misc\ddutil2.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) stretch.cpp
	
..\misc\$(OBJ_DIR)\ddutil2.obj:  ..\misc\ddutil2.cpp ..\misc\ddutil2.h
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\ddutil2.obj $(mycflag) \
    $(cvars) ..\misc\ddutil2.cpp

..\misc\$(OBJ_DIR)\ddmm.obj: ..\misc\ddmm.cpp
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\ddmm.obj $(mycflag) \
    $(cvars) ..\misc\ddmm.cpp

$(OBJ_DIR)\$(proj).res: stretch3.rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res stretch3.rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) stretch3.def $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib dxguid.lib

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
