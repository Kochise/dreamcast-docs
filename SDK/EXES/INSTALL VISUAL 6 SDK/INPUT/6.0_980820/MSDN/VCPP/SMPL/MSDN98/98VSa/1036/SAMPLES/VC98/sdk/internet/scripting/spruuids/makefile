Proj = Spruuids

cDefines = -IInc_Ext

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <INetSDK.Mak>

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\Game.Exe : $(@R).Obj         $(@D)\App.Obj     $(@D)\GameOA.Obj  \
                     $(@D)\Guids.Obj   $(@D)\MsgLoop.Obj $(@D)\OleAuto.Obj \
                     $(@D)\Score.Obj   $(@D)\Spr.Obj     $(@D)\SprOA.Obj   \
                     $(@D)\$(Proj).Res

$(ObjDir)\$(Proj).Exe: $(ObjDir)\Game.Exe
 Copy $? $@

$(ObjDir)\$(Proj).h $(ObjDir)\$(Proj).Tlb: $(Proj).Odl
  $(MkDest)
  MkTypLib /DWIN32 -IInc_Ext /h $(ObjDir)\$(Proj).h /tlb $(ObjDir)\$(Proj).tlb $(Proj).Odl

$(ObjDir)\App.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h     \
        Helpers.h OleAuto.h App.h MsgLoop.h Game.h

$(ObjDir)\Game.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h                \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h OleAuto.h \
        Game.h App.h Spr.h Score.h SpruuidP.h SpruuidP.hh SpruuidP.pix

$(ObjDir)\GameOA.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h    \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h \
        OleAuto.h Game.h App.h Spr.h Score.h DispIDs.h

$(ObjDir)\Guids.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h     \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h \
        OleAuto.h Game.h

$(ObjDir)\MsgLoop.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h   \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h \
        OleAuto.h MsgLoop.h

$(ObjDir)\Score.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h     \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h \
        OleAuto.h Score.h Spr.h Game.h

$(ObjDir)\Spr.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h       \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h \
        OleAuto.h Spr.h

$(ObjDir)\SprOA.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h     \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h \
        OleAuto.h Spr.h DispIDs.h

$(ObjDir)\OleAuto.Obj : Main.h Inc_Ext/MultInfo.h Inc_Ext/VBSGuids.h   \
        Inc_Ext/CompMgr.h Resource.h $(@D)\Spruuids.h Debug.h Helpers.h OleAuto.h
