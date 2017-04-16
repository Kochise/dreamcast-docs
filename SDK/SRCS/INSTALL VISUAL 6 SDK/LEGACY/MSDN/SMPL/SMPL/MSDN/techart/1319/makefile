##### Module Macro #####
NAME	= flicker
SRCS	= main.c init.c flicker.c noflick.c
OBJS	=

##### C7 #####
C7     =  1

##### Library Macro #####
!if $(C7)
LIBS	= libw mlibcew oldnames
!else
LIBS	= libw mlibcew shell
!endif
MOD	= -AM

##### Include Macro #####
INCLS	= global.h

##### Resource Macro #####
RCFILES = app.ico app.rc

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
goal: $(NAME).exe

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
