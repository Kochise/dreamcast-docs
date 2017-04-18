# Makefile for sample remote server

# Nmake macros for building Windows 32-Bit apps
APPVER=4.0
!include <win32.mak>

!IFDEF MAPISAMP
HOME   = $(MAPISAMP)\remote.srv^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

WINDS_SERVICE=windssrv
WINDS_ADMIN=windsadm

all: $(WINDS_SERVICE).exe  $(WINDS_ADMIN).exe

# Define project specific macros
!IFDEF NODEBUG
TRACES_FILE = 
TRACES_DEP =
!ELSE
TRACES_FILE = traces.obj
TRACES_DEP = $(COMMON)traces.h
!ENDIF

EXTRA_LIBS = rpcrt4.lib ole32.lib comctl32.lib
WINDS_SERVICE_OBJS  = $(TRACES_FILE) common.obj wdsadm_s.obj winds_s.obj rxprpc.obj \
                      rabrpc.obj rmsrpc.obj storage.obj support.obj notify.obj \
                      radmrpc.obj service.obj
WINDS_SERVICE_GLOBAL_DEP = _winds.h windsrc.h $(TRACES_DEP) windsgbl.h common.h winds.h wdsadm.h
WINDS_SERVICE_RC_DEP     = $(HOME)windsrc.h $(HOME)winds.ico

WINDS_ADMIN_OBJS  = $(TRACES_FILE) common.obj wdsadm_c.obj admin.obj \
                    admmbox.obj admdlist.obj admnotif.obj adminui.obj
COMMON_OBJS = wrap3d.obj
WINDS_ADMIN_GLOBAL_DEP = resource.h $(TRACES_DEP) windsgbl.h common.h wdsadm.h admin.h
WINDS_ADMIN_RC_DEP     = $(HOME)resource.h $(HOME)windsadm.ico $(HOME)icons.bmp $(HOME)toolbar.bmp $(HOME)windsadm.bmp

# Dependencies
#winds_s.obj: 	winds_s.c   winds.h
#wdsadm_s.obj:   wdsadm_s.c  wdsadm.h
#wdsadm_c.obj:   wdsadm_c.c  wdsadm.h
#common.obj:     common.cpp  wdsadm.h
#traces.obj:  	$(COMMON)traces.cpp  $(COMMON)traces.h
#service.obj:    service.cpp     $(WINDS_SERVICE_GLOBAL_DEP)
#rxprpc.obj:  	rxprpc.cpp      $(WINDS_SERVICE_GLOBAL_DEP)
#rabrpc.obj:  	rabrpc.cpp      $(WINDS_SERVICE_GLOBAL_DEP)
#rmsrpc.obj:  	rmsrpc.cpp      $(WINDS_SERVICE_GLOBAL_DEP)
#radmrpc.obj:    radmrpc.cpp     $(WINDS_SERVICE_GLOBAL_DEP)
#support.obj:  	support.cpp     $(WINDS_SERVICE_GLOBAL_DEP)
#storage.obj:  	storage.cpp     $(WINDS_SERVICE_GLOBAL_DEP)
#notify.obj:  	notify.cpp      $(WINDS_SERVICE_GLOBAL_DEP)
#admin.obj:  	admin.cpp       $(WINDS_ADMIN_GLOBAL_DEP)
#adminui.obj:    adminui.cpp     $(WINDS_ADMIN_GLOBAL_DEP)
#admmbox.obj:  	admmbox.cpp     $(WINDS_ADMIN_GLOBAL_DEP)
#admdlist.obj:   admdlist.cpp    $(WINDS_ADMIN_GLOBAL_DEP)

#winds.h winds_c.c winds_s.c : winds.idl winds.acf
#    midl /ms_ext winds.idl

#wdsadm.h wdsadm_c.c wdsadm_s.c : wdsadm.idl wdsadm.acf
#    midl /ms_ext wdsadm.idl

# Inference rule for updating the object files
{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvars) $(HOME)$*.c

{$(HOME)}.cpp.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvars) $(HOME)$*.cpp

traces.obj: $(COMMON)traces.cpp $(COMMON)traces.h
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsdll) -GX -Utry $(COMMON)traces.cpp

wrap3d.obj: $(COMMON)wrap3d.c $(COMMON)wrap3d.h
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsdll) -GX -Utry $(COMMON)wrap3d.c

# Build rule for resource file
$(WINDS_SERVICE).RES: $(HOME)$(WINDS_SERVICE).RC $(WINDS_SERVICE_RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(WINDS_SERVICE).RES $(HOME)$(WINDS_SERVICE).RC

# Build rule for EXE
$(WINDS_SERVICE).EXE: $(WINDS_SERVICE_OBJS) $(COMMON_OBJS) $(WINDS_SERVICE).RES
    $(link) $(linkdebug) $(guilflags) \
    $(WINDS_SERVICE_OBJS) $(COMMON_OBJS) $(WINDS_SERVICE).RES $(guilibs) $(EXTRA_LIBS) \
    -out:$(WINDS_SERVICE).EXE $(MAPFILE)
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF

# Build rule for resource file
$(WINDS_ADMIN).RES: $(HOME)$(WINDS_ADMIN).RC $(WINDS_ADMIN_RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(WINDS_ADMIN).RES $(HOME)$(WINDS_ADMIN).RC

# Build rule for EXE
$(WINDS_ADMIN).EXE: $(WINDS_ADMIN_OBJS) $(COMMON_OBJS) $(WINDS_ADMIN).RES
    $(link) $(linkdebug) $(guilflags) \
    $(WINDS_ADMIN_OBJS) $(COMMON_OBJS) $(WINDS_ADMIN).RES \
	$(guilibs) $(EXTRA_LIBS) \
    -out:$(WINDS_ADMIN).EXE $(MAPFILE)
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF


# Rules for cleaning out those old files
clean:
    -del *.bak
    -del *.pdb
    -del *.obj
    -del *.res
    -del *.exp
    -del *.map
    -del *.sbr
    -del *.bsc
