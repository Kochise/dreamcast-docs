INCLUDE =.;$(INCLUDE)

##########################################################################
#                                                                                Microsoft Confidential
#       Copyright (C) Microsoft Corporation 1991
#       All Rights Reserved.
#
#       Makefile for the callback VxD
#
##########################################################################

DEVICE          = callback
DYNAMIC         = DYNAMIC
SRCDIR          = .
DEPENDNAME      = depend.mk
TARGETS         = dev
OBJS            = callback.obj helper.obj
LIBS 		= VXDWRAPS.CLB
LFLAGS		= /VXD /NOD

all : callback.vxd

######### Definitions for the debug level #########

DEBUG = 1

!ifdef DEBUG

DDEBUG =-DDEBLEVEL=1 -DDEBUG
CFLAGS =$(CFLAGS) -Oy

!else

DDEBUG =-DDEBLEVEL=0

!endif

########## Definitions for the Assembler ##########

ASM     = ml
AFLAGS  = $(AFLAGS) -DIS_32 -nologo -W2 -Zd -c -Cx -DMASM6
AFLAGS  = $(AFLAGS) $(DDEBUG) -DSysVMIsSpecial 
ASMENV  = ML

########## Definitions for C compiler #############

CL      = cl
CFLAGS  = -nologo -Zdp -Gs -c -DIS_32 -Zl $(CFLAGS)
CFLAGS  = $(CFLAGS) $(DDEBUG) -DSysVMIsSpecial

########## Definitions for VxD linker #############

LINK    = link
LFLAGS  = $(LFLAGS) /MAP /NOLOGO 


########## Base inference rules ###################


#       MASM 6 only inference rules

.asm.obj:
	set $(ASMENV)=$(AFLAGS)
	$(ASM) -Fo$*.obj $<


#       32 bit C compiler inference rules

.c.obj:
	set CL=$(CFLAGS)
	$(CL) -Fo$*.obj $<

############### VxD device section ####################

KEEPFLAG = NOKEEP
VERSION = 4.0

$(DEVICE).sym: $(DEVICE).map
	mapsym -s -o .\$(DEVICE).sym .\$(DEVICE).map

$(DEVICE).map: $(DEVICE).386
						   
$(DEVICE).vxd : $(OBJS) {$(LIB)}$(LIBS) $(STUB)
	$(LINK) $(LFLAGS) @$(DEVICE).lnk
