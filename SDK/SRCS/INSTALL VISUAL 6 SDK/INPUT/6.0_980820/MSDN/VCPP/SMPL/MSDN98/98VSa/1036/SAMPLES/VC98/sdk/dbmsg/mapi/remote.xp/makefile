# Makefile for sample remote transport

# Nmake macros for building Windows 32-Bit apps
APPVER=4.0

#REM Key to CPU specific conditions, CPU == i386 || ALPHA || MIPS || PPC     1) cvtres
# 	cvtres -$(CPU) ...
!IF "$(CPU)" == ""
!IF "$(PROCESSOR_ARCHITECTURE)" == "MIPS" || "$(PROCESSOR_ARCHITECTURE)" == "ALPHA" || "$(PROCESSOR_ARCHITECTURE)" == "PPC"
CPU = $(PROCESSOR_ARCHITECTURE)
!ELSE
CPU = i386
!ENDIF
!ENDIF

!include <win32.mak>

!IFDEF MAPISAMP
HOME   = $(MAPISAMP)\remote.xp^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ=xpwdsr

all: $(PROJ)32.dll

# Define project specific macros
!IFDEF NODEBUG
TRACES_FILE = 
TRACES_DEP =
!ELSE
TRACES_FILE = traces.obj
TRACES_DEP = $(COMMON)traces.h
cflags = $(cflags) -DDEBUG -D_DEBUG
!ENDIF

DLL_OBJS   = winds_c.obj $(TRACES_FILE) xpsrvce.obj xpprov.obj \
             xplogon.obj xpstatus.obj xpfolder.obj xplist.obj comwinds.obj \
             xpstream.obj
DLL_DEP    = $(HOME)xpwdsr.h $(HOME)xplist.h $(HOME)resource.h $(TRACES_DEP) \
             $(HOME)comwinds.h $(HOME)windsgbl.h $(HOME)uisrvcs.h
EXTRA_LIBS = mapi32.lib uuid.lib rpcrt4.lib
RC_DEP     = $(HOME)resource.h $(HOME)uisrvcs.h $(HOME)uisrvcs.dlg

# Dependencies
#traces.obj:     $(COMMON)traces.cpp  $(COMMON)traces.h
#winds_c.obj:    $(HOME)winds_c.c           $(HOME)winds.h
#comwinds.obj:   $(HOME)comwinds.cpp        $(HOME)comwinds.h $(HOME)windsgbl.h $(HOME)winds.h
#xpsrvce.obj:    $(HOME)xpsrvce.cpp         $(DLL_DEP)
#xpprov.obj:     $(HOME)xpprov.cpp          $(DLL_DEP)
#xplogon.obj:    $(HOME)xplogon.cpp         $(DLL_DEP)
#xpstatus.obj:   $(HOME)xpstatus.cpp        $(DLL_DEP)
#xpfolder.obj:   $(HOME)xpfolder.cpp        $(DLL_DEP)
#xplist.obj:     $(HOME)xplist.cpp          $(DLL_DEP)
#xpwizard.obj:   $(HOME)xpwizard.cpp        $(DLL_DEP)
#xpstream.obj:   $(HOME)xpstream.cpp        $(DLL_DEP)

#winds.h winds_c.c winds_s.c : $(HOME)winds.idl $(HOME)winds.acf
#    midl /ms_ext $(HOME)winds.idl

# Inference rule for updating the object files
{$(HOME)}.cpp.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) -GX -Utry $**

{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) -GX -Utry $**

traces.obj: $(COMMON)traces.cpp $(COMMON)traces.h
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) -GX -Utry $(COMMON)traces.cpp

# Build rule for the DLL
$(PROJ)32.dll: $(DLL_OBJS) $(PROJ).res
    $(link)			   \
    $(linkdebug) $(dlllflags)	   \
	-machine:$(CPU)		   \
	-out:$(PROJ)32.dll	   \
	-def:$(HOME)$(PROJ)32.DEF  \
    $(PROJ).res 		   \
    $(DLL_OBJS) $(EXTRA_LIBS) $(guilibsmt)
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF


# Build rule for resource file
$(PROJ).res: $(HOME)$(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)$(PROJ).rc



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
#	del winds.h winds_c.c winds_s.c
