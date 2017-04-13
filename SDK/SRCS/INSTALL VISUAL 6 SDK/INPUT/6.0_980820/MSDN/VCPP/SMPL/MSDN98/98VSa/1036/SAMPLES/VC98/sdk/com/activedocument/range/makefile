Proj = Range

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=urlmon.lib wininet.lib uuid.lib 

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

console=1

!include <inetsdk.mak>

all: $(ObjDir)\$(Proj).Exe

# itemize all of the required Object files

Objs=   $(ObjDir)\Range.Obj    \
        $(ObjDir)\Cache.Obj    \
        $(ObjDir)\RecvBuf.Obj \
        $(ObjDir)\Callback.Obj \
        $(ObjDir)\Download.Obj \

Includes = Range.h Callback.hpp RecvBuf.hpp

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe : $(Objs)

$(ObjDir)\Cache.Obj     : $(@B).Cpp $(Includes)
$(ObjDir)\RecvBuf.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\Download.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\Callback.Obj  : $(@B).Cpp $(Includes)
