#######################################################################
# Copyright (C) 1995 by Microsoft Corporation.
#
#  Makefile for test programs for SMS APIs.
#
#               Jonathan Shuval       12-Oct-94
#               ===============================
#
# Tailored for pdf.exe. To build just type 'nmake'.
#
# CAVEATS:
#    Read the following comment (about setting your environment).
#
#######################################################################


# !!!IMPORTANT!!!
# !!!IMPORTANT!!!
# !!!IMPORTANT!!!
# !!!IMPORTANT!!!
# ====================================================
# The user must set these to suit their environment!!!
# ====================================================
#
#       TOOLSDIR -      location of tools (cl, link, rc etc)
#       INCDIR   -      location of system header files
#       MFCINC   -      location of MFC header files
#       SMSINC   -      name of the SMS sdk include directory (backoffice\include)
#       SMSLIB   -      name of the SMS sdk lib directory (backoffice\lib)
#       DEST     -      destination directory where the resulting .objs
#                       and .exe will be built.
#
TOOLSDIR=
INCDIR=
MFCINC=
SMSINC=
SMSLIB=

!include ..\paths.vc4



# ----------------------------------------------------
# Inference rules
# ----------------------------------------------------
.SUFFIXES:
.SUFFIXES: .cpp .obj .exe .rc .res

.cpp{$(DEST)}.obj:
    $(CL) $(CPPFLAGS) /Fo$*.obj $(CINC) $<



# ----------------------------------------------------
# Include locations and compiler flags
# ----------------------------------------------------

CINC=-I$(SMSINC) -I$(MFCINC) -I$(INCDIR)

OTHERFLAGS=-D_CONSOLE=1
CPPFLAGS=/c /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$*.pch" /YX  /Fd$(DEST)
CPPFLAGS=$(CPPFLAGS) $(OTHERFLAGS)



# ----------------------------------------------------
# Tools used in building the sample.
# ----------------------------------------------------
CL=$(TOOLSDIR)\cl
LINKER=$(TOOLSDIR)\link
CVPACK=$(TOOLSDIR)\cvpack

# ----------------------------------------------------
# Libraries to link with.
# ----------------------------------------------------

LIBS=$(SMSLIB)\smsapi.lib \
     $(SMSLIB)\objectty.lib



# ----------------------------------------------------
# Targets
# ----------------------------------------------------
TGT=pdf

all: $(DEST)\$(TGT).exe



OBJS= $(DEST)\$(TGT).obj


####################################################################
#
# Build the target exe into the $(DEST) directory.
#
####################################################################
$(DEST)\$(TGT).exe: $(OBJS)
    $(LINKER) -link       \
 $(LIBS) \
 /subsystem:console \
 /incremental:yes \
 /pdb:$*.pdb \
 /debug \
 /machine:I386 \
 $(OBJS) \
 /out:$*.exe


# EOF: makefile
