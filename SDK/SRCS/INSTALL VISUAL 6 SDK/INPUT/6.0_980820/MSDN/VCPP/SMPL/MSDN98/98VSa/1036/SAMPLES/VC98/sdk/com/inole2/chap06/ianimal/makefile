#
# MAKEFILE
# IAnimal Interface DLL Chapter 6
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

!ifdef WIN16
!ERROR This sample only compiles and runs under Win32
!endif

TARGET  = ianimal
OUTFILE = ianimal.dll
DLL     = 1

NODOC      = 1
NOUILIB    = 1
NOOCLIB    = 1
NOPRECOMP  = 1
NOCLASSLIB = 1

INCLS   =

OBJS1   = ianimal_i.obj ianimal_p.obj
OBJS2   = dlldata.obj libmain.obj
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2)

RCFILES = ianimal.rc

!include "..\\..\\inole-a.mak"
LIBS    = rpcrt4.lib
!include "..\\..\\inole-b.mak"


#Run MIDL.EXE to produce the source code
ianimal.h ianimal_p.c ianimal_i.c dlldata.c: ianimal.idl
    midl /ms_ext /app_config /c_ext ianimal.idl


##### Dependencies #####
ianimal_i.obj : ianimal_i.c
ianimal_p.obj : ianimal_p.c ianimal.h
dlldata.obj   : dlldata.c
libmain.obj   : libmain.cpp

$(TARGET).res : $(TARGET).rc $(RCFILES)
