# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT
!include <win32.mak>


!IF "$(TARGETLANG)" == ""
all: mousinfo.exe
!ELSE
all: WARN_MSG
!ENDIF


WARN_MSG:
 @echo "Warning: new mouse functionality not available in beta"



# Update the object file if necessary

mousinfo.obj: mousinfo.c mousinfo.h
    $(cc) $(cflags) $(cvars) $(cdebug) /c mousinfo.c


# Update the resources if necessary

mousinfo.res: mousinfo.rc mousinfo.h
    rc $(rcflags) $(rcvars)  mousinfo.rc

# Update the executable file if necessary, and if so, add the resource back in.

mousinfo.exe: mousinfo.obj  mousinfo.res
    $(link) $(linkdebug) $(guiflags) /out:mousinfo.exe \
	mousinfo.obj mousinfo.res $(guilibs)

clean:
    del *.obj
    del *.res
    del *.vcp
    del *.bak
    del *.bsc
    del *.sbr
