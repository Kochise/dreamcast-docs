# CustAct1 makefile
# Copyright 1997 Microsoft Corporation

!ifdef nodebug
MakeOpts = $(MakeOpts) VERSION=SHIP
!endif

all: makefile CustAct1.cpp
 nmake -f CustAct1.cpp /$(MAKEFLAGS) MSDEVDIR= VCBIN= MSVCDIR= _vcbin_= _msdevbin_= $(MakeOpts)
