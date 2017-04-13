# CustExe1 makefile
# Copyright 1997 Microsoft Corporation

!ifdef nodebug
MakeOpts = $(MakeOpts) VERSION=SHIP
!endif

all: makefile CustExe1.cpp
 nmake -f CustExe1.cpp /$(MAKEFLAGS) MSDEVDIR= VCBIN= MSVCDIR= _vcbin_= _msdevbin_= $(MakeOpts)
