Proj = RegView
dll = 1

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=shell32.lib comctl32.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <inetsdk.mak>

# itemize all of the required Object files

Objs =   $(ObjDir)\$(Proj).Res  \
         $(ObjDir)\$(Proj).Obj  \
         $(ObjDir)\ClsFact.Obj \
         $(ObjDir)\EnumIDL.Obj \
         $(ObjDir)\ShlFldr.Obj \
         $(ObjDir)\ShlView.Obj \
         $(ObjDir)\PidlMgr.Obj \
         $(ObjDir)\InfoTip.Obj \
         $(ObjDir)\ExtrIcon.Obj \
         $(ObjDir)\DockWndw.Obj \
         $(ObjDir)\Utility.Obj

# itemize all of the required include files

Includes =  ClsFact.h \
            EnumIDL.h \
            guid.h \
            ShlFldr.h \
            ShlView.h \
            PidlMgr.h \
            InfoTip.h \
            ExtrIcon.h \
            DockWndw.h \
            Utility.h \
            tools.h \
            resource.h

# add the .def file to the link flags
linkflags = $(linkflags) -def:RegView.def

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes)  RegView.Ico \
                                                Folder.ico \
                                                FolderOp.ico \
                                                String.ico

$(ObjDir)\RegView.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ClsFact.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\EnumIDL.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ShlFldr.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ShlView.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\PidlMgr.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\InfoTip.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ExtrIcon.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\DockWndw.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\Utility.Obj   : $(@B).Cpp $(Includes)

$(ObjDir)\$(Proj).dll   : $(Objs)

All: $(ObjDir)\$(Proj).dll
   regsvr32.exe /s /c $(ObjDir)\$(Proj).dll >> $(ObjDir)\Register.Out


