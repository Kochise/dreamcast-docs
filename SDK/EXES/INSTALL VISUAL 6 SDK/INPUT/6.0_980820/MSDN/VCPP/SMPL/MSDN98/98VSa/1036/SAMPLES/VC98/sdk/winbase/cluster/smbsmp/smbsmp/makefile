!include <win32.mak>

#NODEBUG=1

TARGETNAME=SmbSmp
OBJS=$(TARGETNAME).obj $(TARGETNAME).res

EXTRACFLAGS=/D _WINDOWS /D _WINDLL
EXTRALINKFLAGS=-dll
EXTRALIBS=clusapi.lib resutils.lib netapi32.lib

!IFNDEF NODEBUG
EXTRACFLAGS=$(EXTRACFLAGS) $(cdebug)
EXTRALINKFLAGS=$(EXTRALINKFLAGS) $(linkdebug)
EXTRALIBS=$(EXTRALIBS) msvcrtd.lib
!ENDIF

.c.obj:
    $(cc) $(cflags) $(EXTRACFLAGS) $(cvarsdll) $*.c

all: $(TARGETNAME).dll

$(TARGETNAME).res: $(TARGETNAME).rc
    $(rc) -r -fo $(TARGETNAME).res $(TARGETNAME).rc

$(TARGETNAME).dll: $(OBJS) $(TARGETNAME).def
    $(link) $(EXTRALINKFLAGS) $(dlllflags) -out:$(TARGETNAME).dll -def:$(TARGETNAME).def $(OBJS) $(EXTRALIBS) $(guilibsdll)

clean:
    erase $(OBJS) $(TARGETNAME).dll $(TARGETNAME).exp $(TARGETNAME).lib
