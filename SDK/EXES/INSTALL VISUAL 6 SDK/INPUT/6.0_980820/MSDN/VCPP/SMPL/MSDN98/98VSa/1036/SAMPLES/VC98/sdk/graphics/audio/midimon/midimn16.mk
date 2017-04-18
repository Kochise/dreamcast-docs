#===========================================================================;
#
#   Midimon - 16 bit makefile
#
#
#############################################################################
#
#   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
#   KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
#   PURPOSE.
#
#   Copyright (c) 1993 - 1995  Microsoft Corporation.  All Rights Reserved.
#
#############################################################################

TARGETBASE	=midimon
DLLBASE         =callback
EXT		=exe
TARGETNAME	=midimn16
DLLNAME         =midimncb
LOBJ		=win16
LIBS		=libw mlibcew commdlg mmsystem vfw
LIBSDLL         =libw mdllcew mmsystem
OBJS		=$(LOBJ)\$(TARGETBASE).obj $(LOBJ)\prefer.obj $(LOBJ)\instdata.obj \
$(LOBJ)\filter.obj $(LOBJ)\display.obj $(LOBJ)\circbuf.obj $(LOBJ)\about.obj
DLLOBJS         =$(LOBJ)\$(DLLBASE).obj

GOALS		=$(LOBJ)\$(TARGETNAME).$(EXT) \
                 $(LOBJ)\$(TARGETNAME).sym \
                 $(LOBJ)\$(DLLNAME).dll \
                 $(LOBJ)\$(DLLNAME).sym

!if "$(DEBUG)" == "NO"
DEF		=
CDEBUG		=$(DEF)
LDEBUG		=
!else
DEF		=-DDEBUG
CDEBUG		=-Zi $(DEF)
LDEBUG		=/CO/LI
!endif

TARGETWARN	=-W3 -WX
TARGETOPT	=-Ox
CFLAGS		=$(TARGETWARN) $(TARGETOPT) -Z7dp -AM -GsA3 $(CDEBUG) -I..\include -Fo$@
CFLAGSDLL       =$(TARGETWARN) $(TARGETOPT) -Z7dp -AMnw -GsD3 $(CDEBUG) -I..\include -Fo$@
RCFLAGS		=-z -r -I..\include $(RDEBUG)
LFLAGS		=/L/MAP/NOPACKCODE/NOE/NOD/ONERROR:NOEXE/ALIGN:16$(LDEBUG)
RESFLAGS	=-t
RC		=rc -nologo
CC		=cl -c -nologo
LINK		=link /nologo
MAPSYM		=mapsym -nologo
MFLAGS		=
IMPLIB          =implib -nologo

goal:	makedirs $(GOALS)
	@echo ***** Finished making $(TARGETBASE) *****

makedirs:
!if !exists($(LOBJ))
	@md $(LOBJ) >nul
!endif

clean:
!if exists($(LOBJ))
	@echo y | del $(LOBJ) >nul
	@rd $(LOBJ) >nul
!endif
	@echo ***** Finished cleaning $(TARGETBASE) *****

$(LOBJ)\prefer.obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGS)
$(@B).c
<<

$(LOBJ)\instdata.obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGS)
$(@B).c
<<

$(LOBJ)\about.obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGS)
$(@B).c
<<

$(LOBJ)\filter.obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGS)
$(@B).c
<<

$(LOBJ)\display.obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGS)
$(@B).c
<<

$(LOBJ)\circbuf.obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGS)
$(@B).c
<<

$(LOBJ)\$(DLLBASE).obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGSDLL)
$(@B).c
<<



$(LOBJ)\$(TARGETBASE).obj:	$$(@B).c $$(@B).h
	@$(CC) @<<
$(CFLAGS)
$(@B).c
<<

$(LOBJ)\$(TARGETNAME).sym:	$$(@R).map
	@$(MAPSYM) $(MFLAGS) -mo $@ $*.map

$(LOBJ)\$(TARGETBASE).res: $$(@B).rc $$(@B).rcv $$(@B).h
	@$(RC) $(RCFLAGS) -fo$@ $(@B).rc

$(LOBJ)\$(TARGETNAME).$(EXT) $(LOBJ)\$(TARGETNAME).map: $(OBJS) $$(@D)\$(TARGETBASE).res $$(@B).def $(LOBJ)\$(DLLNAME).lib
	@$(LINK) $(LFLAGS) @<<
$(OBJS),
$(@R).$(EXT),
$(@R).map,
$(LIBS) $(LOBJ)\$(DLLNAME).lib,
$(@B).def
<<
	@$(RC) $(RESFLAGS) $(@D)\$(TARGETBASE).res $*.$(EXT)

$(LOBJ)\$(DLLNAME).sym: $(LOBJ)\$(DLLNAME).map
        @$(MAPSYM) $(MFLAGS) -mo $@ $*.map

$(LOBJ)\$(DLLNAME).lib: $(LOBJ)\$(DLLNAME).dll
        @$(IMPLIB) $(@R).lib $(@B).def

$(LOBJ)\$(DLLNAME).dll $(LOBJ)\$(DLLNAME).map: $(DLLOBJS) $$(@B).def
        @$(LINK) $(LFLAGS) @<<
$(DLLOBJS),
$(@R).dll,
$(@R).map,
$(LIBSDLL),
$(@B).def
<<

       
