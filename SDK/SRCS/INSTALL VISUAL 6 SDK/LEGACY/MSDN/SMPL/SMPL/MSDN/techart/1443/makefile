##### Module Macro #####
NAME	= tbss
SRCS	= main.c init.c debug.c help.c file.c clip.c print.c object.c
OBJS	=

##### C7 #####
C7     =  1

##### Library Macro #####
LIBSET  = libw mlibcew commdlg shell ole2 storage
!if $(C7)
LIBS	= $(LIBSET) oldnames
!else
LIBS	= $(LIBSET)
!endif
MOD	= -AM

##### Include Macro #####
INCLS	= global.h

##### Resource Macro #####
RCFILES = app.ico app.rc dialogs.dlg

##### DEBUG Defined #####
DEBUG	= 1

##### Build Option Macros #####
!if $(DEBUG)
DDEF	= -DDEBUG
CLOPT	= -Zid -Od -DSTRICT
MOPT	= -Zi
LOPT	= /CO /LI /MAP
!else
DDEF	=
CLOPT	= -Os -DSTRICT
LOPT	=
!endif

##### General Macros #####
DEF	= -I..\inc

##### Tool Macros #####
ASM	= masm -Mx $(MOPT) $(DDEF) $(DEF)
CC	= cl -nologo -c $(MOD) -G2sw -Zp -W3 $(CLOPT) $(DDEF) $(DEF)
LINK	= link /NOD /NOE $(LOPT)
RC	= rc $(DDEF) $(DEF)
HC	= hc

##### Inference Rules #####
.c.obj:
    $(CC) $*.c

.asm.obj:
    $(ASM) $*.asm;

.rc.res:
    $(RC) -r $*.rc

##### Main (default) Target #####
goal: $(NAME).exe $(NAME).hlp copy

##### Dependents For Goal and Command Line #####
$(NAME).exe: $(SRCS:.c=.obj) app.def app.res
    $(LINK) @<<
    $(SRCS:.c=.obj) $(OBJS),
    $(NAME).exe,
    $(NAME).map,
    $(LIBS),
    app.def
<<
    $(RC) -T app.res $(NAME).exe
!if $(DEBUG)
!if !$(C7)
    cvpack -p $(NAME).exe
!endif
#   mapsym $(NAME).map
!endif

$(NAME).hlp: help.hpj help.rtf 
    $(HC) help.hpj
    -del $(NAME).hlp
    ren help.hlp $(NAME).hlp

##### Dependents #####
# BUGBUG $(SRCS:.c=.obj): $(INCLS)
# BUGBUG app.res: $(RCFILES) $(INCLS)

##### Clean Directory #####
clean:
    -del *.obj
    -del app.res
    -del *.map
    -del *.sym
    -del *.ph

copy:
    copy *.exe ..\bin
