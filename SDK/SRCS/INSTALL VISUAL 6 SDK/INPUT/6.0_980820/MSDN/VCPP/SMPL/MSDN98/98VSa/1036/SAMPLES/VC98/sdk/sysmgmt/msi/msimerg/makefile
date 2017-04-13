# MSIMerg makefile
# Copyright 1997 Microsoft Corporation

!ifdef nodebug
MakeOpts = $(MakeOpts) VERSION=SHIP
!endif

all: makefile MSIMerg.cpp
 nmake -f MSIMerg.cpp /$(MAKEFLAGS) MSDEVDIR= VCBIN= MSVCDIR= _vcbin_= _msdevbin_= $(MakeOpts)
