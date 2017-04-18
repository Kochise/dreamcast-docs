##### Module Macros #####
NAME	= multipal
SRCS	= multipal.c
OBJS	=

##### C7 Macro #####
C7     =  1

##### Library Macros #####
!if $(C7)
LIBS	= libw slibcew
!else
LIBS	= libw snocrt
!endif
MOD	= -AS

##### Include Macro #####
INCLS	= $(NAME).h

##### Resource Macro #####
RCFILES = mdiframe.ico mdichild.ico

##### DEBUG Macro Defined #####
DEBUG	=  1

##### Build Option Macros #####
!if $(DEBUG)
DDEF	= -DDEBUG
CLOPT	= -Zid -Od
MOPT	= -Zi
LOPT	= /CO /LI /MAP
!else
DDEF	=
CLOPT	= -Os
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
    $(CC) -NT _$* $*.c

.asm.obj:
    $(ASM) $*.asm;

.rc.res:
    $(RC) -r $*

##### Main (default) Target #####
goal: $(NAME).exe

##### Dependents For Goal and Command Line #####
multipal.obj: multipal.c $(INCLS)
    $(CC) -NT _TEXT $*.c

$(NAME).exe: $(SRCS:.c=.obj) $(NAME).def $(NAME).res
    $(LINK) @<<
    $(SRCS:.c=.obj) $(OBJS),
    $(NAME).exe,
    $(NAME).map,
    $(LIBS) commdlg.lib,
    $(NAME).def
<<
    $(RC) -T $(NAME).res
!if $(DEBUG)
!if !$(C7)
    cvpack -p $(NAME).exe
!endif
    mapsym $(NAME).map
!endif

##### Dependents #####
$(SRCS:.c=.obj): $(INCLS)
$(NAME).res: $(INCLS) $(RCFILES)

##### Clean Directory #####
clean:
    -del *.obj
    -del *.res
    -del *.map
    -del *.sym
