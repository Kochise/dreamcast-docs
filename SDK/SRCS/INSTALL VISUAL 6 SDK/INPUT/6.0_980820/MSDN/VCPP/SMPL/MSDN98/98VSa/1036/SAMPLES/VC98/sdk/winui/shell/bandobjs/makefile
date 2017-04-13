Proj = BandObjs
dll = 1

_WIN32_IE = 0x0400 

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=shell32.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <inetsdk.mak>

# itemize all of the required Object files

Objs =   $(ObjDir)\$(Proj).Obj  \
         $(ObjDir)\ClsFact.Obj \
         $(ObjDir)\CommBand.Obj \
         $(ObjDir)\DeskBand.Obj \
         $(ObjDir)\ExplrBar.Obj

# itemize all of the required include files

Includes =  ClsFact.h \
            CommBand.h \
            DeskBand.h \
            ExplrBar.h \
            Globals.h \
            Guid.h

# add the .def file to the link flags
linkflags = $(linkflags) -def:BandObjs.def

$(ObjDir)\BandObjs.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\ClsFact.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\CommBand.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\DeskBand.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\ExplrBar.Obj  : $(@B).Cpp $(Includes)

$(ObjDir)\$(Proj).dll   : $(Objs)

All: $(ObjDir)\$(Proj).dll 
   regsvr32.exe /s /c $(ObjDir)\$(Proj).dll >> $(ObjDir)\Register.Out

