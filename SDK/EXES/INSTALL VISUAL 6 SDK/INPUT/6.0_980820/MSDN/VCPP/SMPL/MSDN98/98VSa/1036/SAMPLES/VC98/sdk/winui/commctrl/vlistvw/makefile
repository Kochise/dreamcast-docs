Proj = VListVw

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=comctl32.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <inetsdk.mak>

# itemize all of the required Object files

Objs =   $(ObjDir)\$(Proj).Obj  \
         $(ObjDir)\$(Proj).Res

# itemize all of the required include files

Includes =  resource.h

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes) windows.ico disk.ico

$(ObjDir)\$(Proj).Obj   : $(@B).C $(Includes)

$(ObjDir)\$(Proj).Exe   : $(Objs)

