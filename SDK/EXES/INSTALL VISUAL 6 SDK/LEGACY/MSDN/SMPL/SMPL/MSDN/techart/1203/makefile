##### Module Macro #####
NAME	= sprites
SRC1    = main.c init.c debug.c help.c file.c dib.c
SRC2    = print.c bkgnd.c palette.c draw.c sprite.c 
SRCS	= $(SRC1) $(SRC2)
ASRCS   = ppdbg.asm fast32.asm

##### C7 #####
C7     =  1

##### Library Macro #####
!if $(C7)
LIBS	= libw mlibcew commdlg shell oldnames mmsystem
!else
LIBS	= libw mlibcew commdlg shell mmsystem
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
DDEF	= -DDEBUG -DPPDBG
CLOPT	= -Zid -Od -DSTRICT
MOPT	= -Zi
LOPT	= /CO /LI /MAP /NOPACKC
!else
DDEF	=
CLOPT	= -Os -DSTRICT
LOPT	=
!endif

##### General Macros #####
DEF	=

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
goal: $(NAME).exe $(NAME).hlp

##### Dependents For Goal and Command Line #####
$(NAME).exe: $(SRCS:.c=.obj) $(ASRCS:.asm=.obj) app.def app.res
    $(LINK) @<<
    $(SRCS:.c=.obj) $(ASRCS:.asm=.obj),
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
    mapsym $(NAME).map
!endif

$(NAME).hlp: help.hpj help.rtf 
    $(HC) help.hpj
    -del $(NAME).hlp
    ren help.hlp $(NAME).hlp

##### Dependents #####
$(SRCS:.c=.obj): $(INCLS)
app.res: $(RCFILES) $(INCLS)

##### Clean Directory #####
clean:
    -del *.obj
    -del app.res
    -del *.map
    -del *.sym
    -del *.ph
