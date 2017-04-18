NAME = FDFilter
EXT = EXE

GOALS = $(NAME).$(EXT)

LIBS    =..\..\..\lib\ddraw.lib  ..\..\..\lib\dsound.lib uuid.lib ole32.lib comctl32.lib

OBJS    =  debug.obj fdfilter.obj fdaudio.obj gargle.obj filter.obj
	  
SYS = nt_win

!ifdef DEBUG 
COPT =-DDEBUG -d2
LOPT = debug all
ROPT =-DDEBUG
!else
COPT =-oaxt -d1
LOPT =
ROPT =
!endif

DEF = $(NAME).def
RES = $(NAME).res 

CFLAGS	=$(COPT)
LFLAGS	=$(LOPT)
RCFLAGS =$(ROPT)

!include ..\..\watsdk.mk

$(NAME).$(EXT): $(OBJS) tmp.lib $(NAME).lnk  $(RES)
	$(LINK) $(LFLAGS) library tmp.lib @$(NAME).lnk
	$(RC) $(RES)
	
#
# need this because Watcom's libs don't have the ACM entries and the IMPORT
# statement on the linker doesn't work the way we want
#
tmp.lib : tmp.lbc
	@wlib -q tmp.lib @tmp.lbc > NUL
	
tmp.lbc : ..\$(MAKENAME) 
    @%write tmp.lbc ++_acmMetrics.'MSACM32.DLL'._acmMetrics.acmMetrics
