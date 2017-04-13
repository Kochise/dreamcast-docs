NAME = dpslots
EXT = exe

GOALS = $(NAME).$(EXT)

LIBS    = ..\..\..\lib\dplayx.lbw

OBJS    = dpslots.obj client.obj server.obj dialog.obj lobby.obj
	  
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

RES = $(NAME).res 

CFLAGS	=$(COPT) -I..\..\misc
LFLAGS	=$(LOPT)
RCFLAGS =$(ROPT)

!include ..\..\watsdk.mk

$(NAME).$(EXT): $(OBJS) $(NAME).lnk  $(RES)
	$(LINK) $(LFLAGS) @$(NAME).lnk
	$(RC) $(RES)
