Proj = DOServer

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <inetsdk.mak>

# itemize all of the required Object files

Objs =   $(ObjDir)\$(Proj).Obj  \
         $(ObjDir)\$(Proj).Res  \
         $(ObjDir)\ClsFact.Obj \
         $(ObjDir)\DataObj.Obj \
         $(ObjDir)\OIPAObj.Obj \
         $(ObjDir)\OIPObj.Obj \
         $(ObjDir)\OleDoc.Obj \
         $(ObjDir)\OleDocVw.Obj \
         $(ObjDir)\OleObj.Obj \
         $(ObjDir)\PerFile.Obj \
         $(ObjDir)\PerStor.Obj \
         $(ObjDir)\Utils.Obj

# itemize all of the required include files

Includes =  DOServer.h \
            ClsFact.h \
            DataObj.h \
            OIPAObj.h \
            OIPObj.h \
            OleDoc.h \
            OleDocVw.h \
            OleObj.h \
            PerFile.h \
            PerStor.h \
            Utils.h \
            resource.h

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes) MainIcon.Ico

$(ObjDir)\DOServer.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\ClsFact.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\DataObj.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\OIPAObj.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\OIPObj.Obj    : $(@B).Cpp $(Includes)
$(ObjDir)\OleDoc.Obj    : $(@B).Cpp $(Includes)
$(ObjDir)\OleDocVw.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\OleObj.Obj    : $(@B).Cpp $(Includes)
$(ObjDir)\PerFile.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\PerStor.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\Utils.Obj     : $(@B).Cpp $(Includes)

$(ObjDir)\$(Proj).Exe   : $(Objs)

