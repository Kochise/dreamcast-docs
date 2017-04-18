#=--------------------------------------------------------------------------=
# Makefile
#=--------------------------------------------------------------------------=
# Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
# PARTICULAR PURPOSE.
#=--------------------------------------------------------------------------=
#
# Builds the WebImage Control
#

USE_BASECTL = 1

Proj = WImg

# pull in the master SDK makefile that Defines all of the macros
#  and all of the build rules

!include <INetSDK.Mak>

all: $(ObjDir)\$(Proj).Ocx Register

# itemize all of the required Object files

Objs=$(ObjDir)\CatHelp.Obj \
     $(ObjDir)\DibCls.Obj  \
     $(ObjDir)\Guids.Obj   \
     $(ObjDir)\WImg.Obj    \
     $(ObjDir)\WImgCtl.Obj \
     $(ObjDir)\WImgPPG.Obj \
     $(ObjDir)\$(Proj).Res

# special case the odl file since the output header has a special name

$(Proj)Interfaces.h: $(Proj).Odl
  mktyplib /DWIN32 -I..\BaseCtl\Include /h $(Proj)Interfaces.h /tlb $(Proj).Tlb $(Proj).Odl

# and finally, just Define the dependencies

$(ObjDir)\$(Proj).Ocx: $(Objs)

$(ObjDir)\Guids.Obj: $(@B).Cpp $(Proj)Interfaces.h
