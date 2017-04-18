!include <win32.MAK>

proj = wsock

#detect build time environment
!IF "$(OS)" == "Windows_NT"
all: $(proj).exe
!else
all: WARN_MSG
!endif

WARN_MSG:
  @echo "This sample will work correctly only on Windows NT because of AcceptEx"


# Update the resource if necessary
$(proj).res: $(proj).rc $(proj).dlg $(proj).h
    rc -r -fo $(proj).res $(cvars) $(proj).rc


# Update the object files if necessary
$(proj).obj: $(proj).c $(proj).h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(proj).c

dialogs.obj: dialogs.c $(proj).h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) dialogs.c

# Since the link line has some severe differences depending on what
# platform we are running on, we need to special case this so that
# we execute the correct commands:

$(proj).exe: $(proj).obj dialogs.obj $(proj).res $(proj).def
    $(link) $(linkdebug) $(guiflags) $(proj).obj dialogs.obj $(guilibsmt) $(proj).res -out:$(proj).exe


# Clean up everything
clean :
    -del *.res
    -del *.res
    -del *.exe
    -del *.obj
