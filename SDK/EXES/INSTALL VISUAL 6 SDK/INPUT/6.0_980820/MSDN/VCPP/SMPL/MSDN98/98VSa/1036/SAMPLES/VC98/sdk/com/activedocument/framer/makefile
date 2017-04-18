dll = 1

Proj = Framer

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=uuid.lib 

!ifdef UNICODE
cDefines = -DUNICODE -D_UNICODE
!endif

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <inetsdk.mak>

all: $(ObjDir)\$(Proj).Exe


# itemize all of the required Object files

Objs=   $(ObjDir)\$(Proj).Obj  \
        $(ObjDir)\$(Proj).Res  \
        $(ObjDir)\IAdvSink.Obj \
        $(ObjDir)\ICliSite.Obj \
        $(ObjDir)\IDocSite.Obj \
        $(ObjDir)\IIpSite.Obj  \
        $(ObjDir)\Site.Obj

Includes    = $(Proj).h site.h resource.h

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe : $(Objs)

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes) $(Proj).Ico

$(ObjDir)\$(TARGET).Obj : $(@B).Cpp $(Includes)
$(ObjDir)\IAdvSink.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\ICliSite.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\IDocSite.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\IIpSite.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\Site.Obj      : $(@B).Cpp $(Includes)
