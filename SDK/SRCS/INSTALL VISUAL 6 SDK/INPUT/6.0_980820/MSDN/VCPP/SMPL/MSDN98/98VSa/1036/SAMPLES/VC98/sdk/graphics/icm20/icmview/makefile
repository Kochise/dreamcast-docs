APPVER=5.0

CFLAGS=0x0500
_BITMAPV5=1

!include <win32.mak>

LINK32_OBJS= appinit.obj child.obj debug.obj dialogs.obj dibinfo.obj dibs.obj \
    icmview.obj print.obj regutil.obj icmview.res

ALL : icmview.exe

icmview.res : icmview.rc icmview.ico small.ico resource.h icmview.def
    $(rc) $(rcflags) $(rcvars) $(rcdebug) icmview.rc

appinit.obj : appinit.c appinit.h icmview.h child.h dibinfo.h debug.h resource.h
    $(cc) $(cflags) $(cvars) $(cdebug) appinit.c

child.obj : child.c icmview.h resource.h child.h dialogs.h dibinfo.h dibs.h print.h debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) child.c

debug.obj : debug.c icmview.h debug.h dibinfo.h
    $(cc) $(cflags) $(cvars) $(cdebug) debug.c

dialogs.obj : dialogs.c icmview.h resource.h dialogs.h cderr.h print.h child.h dibinfo.h dibs.h appinit.h debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) dialogs.c

dibinfo.obj : dibinfo.c icmview.h dibinfo.h dibs.h regutil.h print.h debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) dibinfo.c

dibs.obj : dibs.c icmview.h child.h dibinfo.h dibs.h debug.h print.h regutil.h
    $(cc) $(cflags) $(cvars) $(cdebug) dibs.c

icmview.obj : icmview.c icmview.h resource.h print.h dialogs.h appinit.h child.h dibinfo.h debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) icmview.c

print.obj : print.c icmview.h child.h dibinfo.h dibs.h debug.h print.h regutil.h resource.h
    $(cc) $(cflags) $(cvars) $(cdebug) print.c

regutil.obj : regutil.c regutil.h
    $(cc) $(cflags) $(cvars) $(cdebug) regutil.c

icmview.exe : $(DEF_FILE) $(LINK32_OBJS)
    $(link) $(linkdebug) $(guilflags) $(LINK32_OBJS) \
    -out:icmview.exe fdi.lib $(guilibs) shell32.lib comctl32.lib \
    version.lib mscms.lib icmui.lib /def:icmview.def



CLEAN :
    -@erase icmview.exe
    -@erase appinit.obj
    -@erase child.obj
    -@erase debug.obj
    -@erase dialogs.obj
    -@erase dibinfo.obj
    -@erase dibs.obj
    -@erase icmview.obj
    -@erase print.obj
    -@erase regutil.obj
    -@erase icmview.res
    -@erase icmview.lib
    -@erase icmview.exp
