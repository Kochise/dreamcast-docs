APPVER=4.0

!include <win32.mak>

PROJ = soundapp

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = $(PROJ).sym
!endif

all: $(PROJ).exe $(SYM)


# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c


# Build rule for resource file
$(PROJ).res: $(PROJ).rc resource.h
    $(rc) $(rcflags) $(rcvars) /fo $*.res $*.rc


# Build rule for EXE
$(PROJ).EXE (PROJ).map:  $(PROJ).obj $(PROJ).res
    $(link) $(linkdebug) $(guilflags) \
    $(PROJ).obj $(PROJ).res $(guilibs) version.lib winmm.lib -map:$*.map

$(PROJ).SYM: $*.map
	mapsym $*.map

# Rules for cleaning out those old files
clean:
    @if exist soundapp.exe del soundapp.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
