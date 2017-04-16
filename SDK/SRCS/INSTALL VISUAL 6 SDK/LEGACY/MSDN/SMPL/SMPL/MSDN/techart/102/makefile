##### APP Macros #####
APPNAME    = smart
APPSRCS    = $(APPNAME).c
APPOBJS    =

##### DLL Macros #####
DLLNAME   = smartdll
DLLSRCS   = $(DLLNAME).c 
DLLOBJS   = 

##### C7 Macro #####
C7	   = 1

##### APP Library Macros #####
APPLIBS    = $(DLLNAME) llibcew libw
APPMOD	   = -AL

##### DLL Library Macros #####
DLLLIBS    = libw ldllcew
DLLMOD	   = -ALw

##### APP/DLL Include Macros #####
APPINCLS   = $(APPNAME).h resource.h
DLLINCLS  = 
#$(DLLNAME).h 

##### APP/DLL Resource Macros #####
APPRCFILES = $(APPNAME).ico $(APPNAME).rc $(APPNAME).dlg
DLLRCFILES =

##### DEBUG Version Built #####
DEBUG	= 1

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
DEF	= -DSTRICT

##### Tool Macros #####
ASM	= masm -Mx $(MOPT) $(DDEF) $(DEF)
CC	= cl -nologo -c $(APPMOD) -GA -GEs -Gx -Gt65500 -Zp -W3 $(CLOPT) $(DDEF) $(DEF)
CC2	= cl -nologo -c $(DLLMOD) -GD -G2s -Zp -W3 $(CLOPT) $(DDEF) $(DEF)
LINK	= link /NOD /NOE $(LOPT)
RC	= rc $(DDEF) $(DEF)
HC	= hc

##### Inference Rules #####
.c.obj:
    $(CC2) $*.c

.asm.obj:
    $(ASM) $*.asm;

.rc.res:
    $(RC) -r $*.rc

##### Main (default) Target #####
goal:  $(DLLNAME).lib $(APPNAME).exe

##### Dependents For Goal and Command Lines #####
##### APP Built Separately #####
smart.obj: smart.c
    $(CC) $*.c

$(APPNAME).exe: $(APPSRCS:.c=.obj) $(APPNAME).def $(APPNAME).res
    $(LINK) @<<
    $(APPSRCS:.c=.obj) $(APPOBJS),
    $(APPNAME).exe,
    $(APPNAME).map,
    $(APPLIBS),
    $(APPNAME).def
<<
    $(RC) -T $(APPNAME).res
!if $(DEBUG)
!if !$(C7)
    cvpack -p $(APPNAME).exe
!endif
    mapsym $(APPNAME).map
!endif

##### DLL Built Separately #####
$(DLLNAME).dll: $(DLLSRCS:.c=.obj) $(DLLNAME).def  ###$(DLLNAME).res
    $(LINK) @<<
    $(DLLSRCS:.c=.obj) $(DLLOBJS),
    $(DLLNAME).dll,
    $(DLLNAME).map,
    $(DLLLIBS),
    $(DLLNAME).def
<<
	$(RC) -T $(DLLNAME).dll

!if $(DEBUG)
!if !$(C7)
    cvpack -p $(DLLNAME).dll
!endif
    mapsym $(DLLNAME).map
!endif

$(DLLNAME).lib: $(DLLNAME).dll
    implib $(DLLNAME).lib $(DLLNAME).dll

##### Dependents #####
$(APPSRCS:.c=.obj): $(APPINCLS)
$(APPNAME).res: $(APPINCLS) $(APPRCFILES)

$(DLLSRCS:.c=.obj): $(DLLINCLS)


##### Clean Directory #####
clean:
    -del *.obj
    -del *.res
    -del *.map
    -del *.sym
    -del *.lib
