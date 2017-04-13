# APITstDb makefile
# Copyright 1997 Microsoft Corporation

!ifdef nodebug
MakeOpts = $(MakeOpts) VERSION=SHIP
!endif

all: makefile apitstdb.cpp
 nmake -f apitstdb.cpp /$(MAKEFLAGS) MSDEVDIR= VCBIN= MSVCDIR= _vcbin_= _msdevbin_= $(MakeOpts)
