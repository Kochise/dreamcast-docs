#+---------------------------------------------------------------------------
#
#  Microsoft Windows
#  Copyright (C) Microsoft Corporation, 1992 - 1997.
#
#  File:       olesampl.mak
#
#  Contents:   common makefile for use by the SDK OLE samples
#
#              This makefile is included in place of ntwin32.mak
#              at the top of all the OLE samples.
#
#  History:     8-23-94   stevebl   Created
#
#----------------------------------------------------------------------------

!include <ntwin32.mak>

INCLUDE=$(MSTOOLS)\samples\com\com\include;$(INCLUDE)
INCLUDE=$(MSTOOLS)\samples\com\com\winhlprs;$(INCLUDE)
LIB=$(MSTOOLS)\samples\com\com\common;$(LIB)

olelibs = $(olelibs) sdkutil.lib
olelibsmt = $(olelibsmt) sdkutil.lib
olelibsdll = $(olelibsdll) sdkutil.lib
guilibs = $(guilibs) sdkutil.lib
guilibsmt = $(guilibsmt) sdkutil.lib
guilibsdll = $(guilibsdll) sdkutil.lib
