#=--------------------------------------------------------------------------=
# Makefile
#=--------------------------------------------------------------------------=
# Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#=--------------------------------------------------------------------------=
#
# Makefile for the ToDoSvr control
#

USE_BASECTL = 1

Proj = ToDoSvr

# itemize all of the required object files

ObjList= $(ObjDir)\CDocObj.Obj \
         $(ObjDir)\DoReg.Obj   \
         $(ObjDir)\Guids.Obj   \
         $(ObjDir)\IODoc.Obj   \
         $(ObjDir)\IODocVw.Obj \
         $(ObjDir)\Menu.Obj    \
         $(ObjDir)\ToDoctl.Obj \
         $(ObjDir)\ToDoppg.Obj \
         $(ObjDir)\ToDosvr.Obj \
         $(ObjDir)\ToDosvr.Res

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <INetSDK.Mak>

all: $(ObjDir)\$(Proj).Ocx Register

# define the dependencies

$(ObjDir)\$(Proj).Ocx: $(ObjList)

$(ObjDir)\$(Proj).Obj: $(@B).Cpp $(ObjDir)\$(Proj)Ifc.h Localobj.h CDocObj.h Resource.h ToDoctl.h DispIds.h ToDoppg.h Guids.h

$(ObjDir)\Guids.Obj: $(@B).Cpp $(ObjDir)\$(Proj)Ifc.h $(@B).h

$(ObjDir)\$(Proj).Res: $(@B).Rc $(ObjDir)\$(Proj)Ifc.h $(@R).Tlb

$(ObjDir)\CDocObj.Obj: $(@B).Cpp $(@B).h

$(ObjDir)\DoReg.Obj: $(@B).Cpp CDocObj.h

$(ObjDir)\iodoc.Obj: $(@B).Cpp CDocObj.h

$(ObjDir)\iodocvw.Obj: $(@B).Cpp CDocObj.h

$(ObjDir)\Menu.Obj: $(@B).Cpp CDocObj.h

$(ObjDir)\ToDoctl.Obj: $(@B).Cpp Guids.h ToDoctl.h CDocObj.h DispIds.h Localobj.h Resource.h

$(ObjDir)\ToDoppg.Obj: $(@B).Cpp Localobj.h $(@B).h Resource.h Guids.h ToDoctl.h CDocObj.h DispIds.h $(ObjDir)\$(Proj)Ifc.h
