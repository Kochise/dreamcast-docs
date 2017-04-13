##########################################################################
#
# Makefile for OLESTD.LIB
#
# Usage:    NMAKE           (builds DEBUG library)
#    or:    NMAKE RELEASE=1 (builds RELEASE library -- no debug symbols)
#
# Environment variables:
#       DEVROOT_DIR=<path>  (root dir for sample code development)
#
##########################################################################

!include <olesampl.mak>

!IF "$(TARGETLANG)" == "LANG_JAPANESE"
LANG=JPN
!ELSE
LANG=USA
!ENDIF

!ifndef LIBRARY
LIBRARY=olestd
!endif

RESOURCE=res

all: $(LIBRARY).lib

# ----------------------------------------------------------------------------
#                      O B J E C T   F I L E   L I S T
# ----------------------------------------------------------------------------

UI_COBJS = dballoc.obj  \
           dbgutil.obj  \
           drawicon.obj \
           geticon.obj  \
           hatch.obj    \
           msgfiltr.obj \
           enumfetc.obj \
           enumstat.obj \
           objfdbk.obj  \
           ole2ui.obj   \
           olestd.obj   \
           targtdev.obj \
           oleutl.obj   \
           regdb.obj    \
           stdpal.obj   \
           suminfo.obj  \
           malspy.obj   \
           utility.obj


# ----------------------------------------------------------------------------
#                       R E S O U R C E   L I S T
# ----------------------------------------------------------------------------
RES =      \
           common.h                         \
           $(RESOURCE)\STATIC\egares.bmp    \
           $(RESOURCE)\STATIC\hivgares.bmp  \
           $(RESOURCE)\STATIC\vgares.bmp    \
           $(RESOURCE)\$(LANG)\strings.rc

# ----------------------------------------------------------------------------
#                 D E B U G   M A K E   P A R A M E T E R S
# ----------------------------------------------------------------------------

OLE_FLAGS =

!ifndef NODEBUG
#OLE_FLAGS = $(OLE_FLAGS) /DDBG /D_DEBUG
OLE_FLAGS = $(OLE_FLAGS) /DDBG /D_DEBUG /DTRACEMEM
!endif



.SUFFIXES: .c .asm .obj .res .rc .def .bmp .ico .exe .dll .cod .str

# ----------------------------------------------------------------------------
#                     I N F E R E N C E   R U L E S
# ----------------------------------------------------------------------------
# compile C file without precompiled headers into object directory\NOPC
# dont compile c files etc for lcoalized builds.

.c.obj:
    @echo Compiling $(@B).c
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS) $(@B).c

.rc.res:
    @echo Resource Compiling $(@B).res
    $(rc) -I $(RESOURCE)\$(LANG);$(RESOURCE)\static;$(RESOURCE) -FO $(@B).res -R $(RFLAGS) $(@B).rc

.c.cod:
    @echo Making $(@B).cod
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS) -f- -Fc $(@B).c

# ----------------------------------------------------------------------------
#                        G O A L   T A R G E T S
# ----------------------------------------------------------------------------
suminfo.obj: suminfo.cpp suminfo.h wn_dos.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS) $(@B).cpp

dballoc.obj: dballoc.cpp dballoc.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS) $(@B).cpp

ole2ui.res: ole2ui.rc $(RES)

ole2ui.rc : $(RESOURCE)\$(LANG)\strings.rc


#
# Build .LIB static library
#

$(LIBRARY).lib: $(UI_COBJS) ole2ui.res
    lib -out:$*.lib ole2ui.res -machine:$(CPU) $(UI_COBJS)
    if not exist ..\lib mkdir ..\lib
    copy $(LIBRARY).LIB ..\lib

clean:
    -del *.obj
    -del *.res
    -del *.lib
    -del *.exp
    -del *.map
