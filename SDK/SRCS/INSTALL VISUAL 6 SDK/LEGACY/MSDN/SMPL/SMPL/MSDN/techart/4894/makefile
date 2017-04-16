Proj = SurfBear

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=wininet.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

Use_MFC=1
!include <inetsdk.mak>

all: $(ObjDir)\$(Proj).Exe

# itemize all of the required Object files

Objs=   $(ObjDir)\$(Proj).Obj  \
        $(ObjDir)\IThread.Obj  \
        $(ObjDir)\SBearDlg.Obj \
        $(ObjDir)\ATypeDlg.Obj \
        $(ObjDir)\StdAfx.Obj   \
        $(ObjDir)\$(Proj).Res  \

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe : $(Objs)

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes) Res\$(Proj).Ico Res\msdn.Ico Res\books.avi Res\bmp00001.bmp Res\helpimag.bmp Res\SurfBear.rc2

$(ObjDir)\$(TARGET).Obj : $(@B).Cpp $(Includes)
$(ObjDir)\IThread.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\SBearDlg.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\ATypeDlg.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\StdAfx.Obj    : $(@B).Cpp $(Includes)
