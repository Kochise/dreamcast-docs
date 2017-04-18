#
# Makefile : Builds the OLE 2.0 Outline series sample apps
#

!include <olesampl.mak>

all: $(APP).exe

OLE_FLAGS =

!ifndef NO_DEBUG
OLE_FLAGS = $(OLE_FLAGS) -DDBG -D_DEBUG
!endif

OLELIBS   = ole32.lib uuid.lib oleaut32.lib oledlg.lib ..\..\lib\olestd.lib ..\..\lib\gizmobar.lib ..\..\lib\bttncur.lib

PCHFLAGS  = -Yuoutline.h -Fp$(APP).pch

COMMONINCL =  ..\outline.h ..\frametls.h ..\outlrc.h ..\status.h ..\cntroutl.h ..\cntrrc.h ..\svroutl.h ..\oleoutl.h

!if "$(USE_MSGFILTER)"=="1"
OLE_FLAGS  = $(OLE_FLAGS) /DUSE_MSGFILTER
!endif

PRECOMPOBJ = $(APP).obj


##########################################################################
#
# main obj lists; add new obj files here
#

!if "$(APP)" == "cntroutl"
OLE_FLAGS = $(OLE_FLAGS) /DOLE_CNTR
APP_OBJS = main.obj memmgr.obj status.obj frametls.obj \
       dialogs.obj debug.obj \
       outlapp.obj outldoc.obj heading.obj \
       outllist.obj outlline.obj outltxtl.obj \
       outlntbl.obj outlname.obj \
       oleapp.obj oledoc.obj classfac.obj debug2.obj \
       dragdrop.obj clipbrd.obj linking.obj \
       cntrbase.obj cntrline.obj
!else

!if "$(APP)" == "svroutl"
OLE_FLAGS = $(OLE_FLAGS) /DOLE_SERVER
APP_OBJS = main.obj memmgr.obj status.obj frametls.obj \
       dialogs.obj debug.obj \
       outlapp.obj outldoc.obj heading.obj \
       outllist.obj outlline.obj outltxtl.obj \
       outlntbl.obj outlname.obj \
       oleapp.obj oledoc.obj classfac.obj debug2.obj \
       dragdrop.obj clipbrd.obj linking.obj \
       svrbase.obj svrpsobj.obj
!else

!if "$(APP)" == "icntrotl"
OLE_FLAGS = $(OLE_FLAGS) /DOLE_CNTR /DINPLACE_CNTR
APP_OBJS = main.obj memmgr.obj status.obj frametls.obj \
       dialogs.obj debug.obj \
       outlapp.obj outldoc.obj heading.obj \
       outllist.obj outlline.obj outltxtl.obj \
       outlntbl.obj outlname.obj \
       oleapp.obj oledoc.obj classfac.obj debug2.obj \
       dragdrop.obj clipbrd.obj linking.obj \
       cntrbase.obj cntrline.obj cntrinpl.obj
!else

!if "$(APP)" == "isvrotl"
OLE_FLAGS = $(OLE_FLAGS) /DOLE_SERVER /DINPLACE_SVR
APP_OBJS = main.obj memmgr.obj status.obj frametls.obj \
       dialogs.obj debug.obj \
       outlapp.obj outldoc.obj heading.obj \
       outllist.obj outlline.obj outltxtl.obj \
       outlntbl.obj outlname.obj \
       oleapp.obj oledoc.obj classfac.obj debug2.obj \
       dragdrop.obj clipbrd.obj linking.obj \
       svrbase.obj svrpsobj.obj svrinpl.obj
!else
APP_OBJS = main.obj memmgr.obj status.obj frametls.obj \
       dialogs.obj debug.obj \
       outlapp.obj outldoc.obj heading.obj \
       outllist.obj outlline.obj outltxtl.obj debug2.obj \
       outlntbl.obj outlname.obj

!endif
!endif
!endif
!endif


##########################################################################
#
# create precomiled header
#
$(APP).pch : ..\$(APP).c $(COMMONINCL)
    @echo Precompiling outline.h ...
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS) -Ycoutline.h -Fp$(APP).pch -Fo$(APP) ..\$(APP).c

##########################################################################
#
# link/res commands

$(APP).exe: $(APP).pch $(APP_OBJS) ..\$(APP).def $(APP).res ..\..\lib\gizmobar.lib ..\..\lib\bttncur.lib ..\..\lib\olestd.lib
    $(link) $(linkdebug) $(guilflags) $(PRECOMPOBJ) $(APP_OBJS) $(APP).res -out:$@ -map:$*.map $(OLELIBS) $(guilibs) advapi32.lib shell32.lib
    if not exist ..\..\bin mkdir ..\..\bin
    copy $(APP).exe ..\..\bin

$(APP).res: ..\$(APP).rc ..\outlrc.h ..\cntrrc.h ..\dialogs.dlg ..\debug.rc
    rc -r -DWIN32 $(RCFLAGS) -I.. -fo$@ ..\$(APP).rc


##########################################################################
#
# build rules for src directory
#

{..}.c.obj:
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS) $(PCHFLAGS) ..\$*.c


##########################################################################
#
# clean (erase) generated files

clean:
    -del *.obj
    -del *.res
    -del *.exe
    -del *.map
    -del *.pch


#########################################################
# Dependencies
#########################################################

main.obj : ..\main.c $(COMMONINCL)
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS) ..\main.c

outlapp.obj : ..\outlapp.c $(COMMONINCL)

outldoc.obj : ..\outldoc.c $(COMMONINCL)

outllist.obj : ..\outllist.c $(COMMONINCL)

outlline.obj : ..\outlline.c $(COMMONINCL)

outltxtl.obj : ..\outltxtl.c $(COMMONINCL)

outlntbl.obj : ..\outlntbl.c $(COMMONINCL)

outlname.obj : ..\outlname.c $(COMMONINCL)

classfac.obj : ..\classfac.c $(COMMONINCL)

oleapp.obj : ..\oleapp.c $(COMMONINCL)

oledoc.obj : ..\oledoc.c $(COMMONINCL)

dragdrop.obj : ..\dragdrop.c $(COMMONINCL)

clipbrd.obj : ..\clipbrd.c $(COMMONINCL)

linking.obj : ..\linking.c $(COMMONINCL)

cntrbase.obj : ..\cntrbase.c $(COMMONINCL)

cntrline.obj : ..\cntrline.c $(COMMONINCL)

cntrinpl.obj : ..\cntrinpl.c $(COMMONINCL)

svrpsobj.obj : ..\svrpsobj.c $(COMMONINCL)

svrinpl.obj : ..\svrinpl.c $(COMMONINCL)

svrbase.obj : ..\svrbase.c $(COMMONINCL)

status.obj : ..\status.c $(COMMONINCL) ..\message.h ..\status.h

memmgr.obj : ..\memmgr.c
    $(cc) $(cflags) $(cvars) $(cdebug) $(OLE_FLAGS)  ..\memmgr.c

frametls.obj : ..\frametls.c $(COMMONINCL)

heading.obj : ..\heading.c $(COMMONINCL)

dialogs.obj : ..\dialogs.c $(COMMONINCL)

debug.obj : ..\debug.c $(COMMONINCL)

debug2.obj : ..\debug2.c $(COMMONINCL)
