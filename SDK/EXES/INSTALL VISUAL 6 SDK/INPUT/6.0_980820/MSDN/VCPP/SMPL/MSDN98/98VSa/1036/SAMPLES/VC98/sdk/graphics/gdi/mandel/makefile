# some NT Win32 nmake macros

!include <ntwin32.mak>

cvars=-DNT -DWIN -DWIN32
objs=obj
mycflag = -Fo.\$(objs)\\

all: julia.exe

# Update the object file if necessary

$(objs)\julia.obj: julia.c julia.h jtypes.h bndscan.h dibmp.h
    IF NOT EXIST $(objs) md $(objs)
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) julia.c

$(objs)\savebmp.obj: savebmp.c jtypes.h
    IF NOT EXIST $(objs) md $(objs)
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) savebmp.c

$(objs)\loadbmp.obj: loadbmp.c jtypes.h
    IF NOT EXIST $(objs) md $(objs)
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) loadbmp.c

$(objs)\dibmp.obj: dibmp.c jtypes.h dibmp.h
    IF NOT EXIST $(objs) md $(objs)
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) dibmp.c

$(objs)\bndscan.obj: bndscan.c bndscan.h jtypes.h
    IF NOT EXIST $(objs) md $(objs)
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) bndscan.c

$(objs)\printer.obj: printer.c printer.h
    IF NOT EXIST $(objs) md $(objs)
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) printer.c

# Update the resources if necessary

!IF ("$(TARGETLANG)" == "LANG_JAPANESE")
$(objs)\julia.res: julia.rc julia.h jtypes.h bndscan.h dibmp.h
    rc $(rcflags) $(rcvars) -c 932 -r -fo .\$(objs)\julia.res julia.rc
!ELSE
$(objs)\julia.res: julia.rc julia.h jtypes.h bndscan.h dibmp.h
    rc $(rcflags) $(rcvars) -r -fo .\$(objs)\julia.res julia.rc
!ENDIF

# Update the executable file if necessary, and if so, add the resource back in.

julia.exe: $(objs)\julia.obj   \
           $(objs)\loadbmp.obj \
           $(objs)\savebmp.obj \
           $(objs)\dibmp.obj   \
           $(objs)\bndscan.obj \
           $(objs)\printer.obj \
           $(objs)\julia.res
    $(link) $(linkdebug) $(guiflags) -out:julia.exe	 \
           $(objs)\julia.obj   \
           $(objs)\savebmp.obj \
           $(objs)\loadbmp.obj \
           $(objs)\dibmp.obj   \
           $(objs)\bndscan.obj \
           $(objs)\printer.obj \
           $(objs)\julia.res   \
           $(guilibs) shell32.lib
