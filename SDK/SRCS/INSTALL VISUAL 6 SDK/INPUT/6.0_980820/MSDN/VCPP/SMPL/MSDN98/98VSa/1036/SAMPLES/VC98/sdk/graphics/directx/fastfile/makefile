!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

all: mkdir $(OBJ_DIR)\fastfile.lib $(OBJ_DIR)\ffcreate.exe

$(OBJ_DIR)\fastfile.obj:  fastfile.c fastfile.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\fastfile.obj $(cvars) fastfile.c
	

$(OBJ_DIR)\fastfile.lib: $(OBJ_DIR)\fastfile.obj
    $(implib) $(OBJ_DIR)\fastfile.Obj -name:fastfile.Lib \
    -out:$(OBJ_DIR)\fastfile.lib

$(OBJ_DIR)\ffcreate.obj:  ffcreate.c ffent.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\ffcreate.obj $(cvars) ffcreate.c

$(OBJ_DIR)\ffcreate.exe: $(OBJ_DIR)\ffcreate.obj  ffcreate.def  
    $(link) $(linkdebug) $(conflags) -out:$(OBJ_DIR)\ffcreate.exe \
           $(OBJ_DIR)\ffcreate.obj \
           $(conlibs)

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
