#
# MAKEFILE
# IKoala Interface DLL Chapter 6
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

TARGET  = ikoala
OUTFILE = ikoala.dll
DLL     = 1

NODOC      = 1
NOUILIB    = 1
NOOCLIB    = 1
NOPRECOMP  = 1
NOCLASSLIB = 1

INCLS   =

OBJS1   = ikoala_i.obj ikoala_p.obj
OBJS2   = dlldata.obj libmain.obj
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2)

RCFILES = ikoala.rc

!include "..\\..\\inole-a.mak"
LIBS    = rpcrt4.lib
!include "..\\..\\inole-b.mak"


#Run MIDL.EXE to produce the source code
ikoala.h ikoala_p.c ikoala_i.c dlldata.c: ikoala.idl
    midl /ms_ext /app_config /c_ext ikoala.idl


##### Dependencies #####
ikoala_i.obj  : ikoala_i.c ikoala.h
ikoala_p.obj  : ikoala_p.c ikoala.h
dlldata.obj   : dlldata.c
libmain.obj   : libmain.cpp

$(TARGET).res : $(TARGET).rc $(RCFILES)
