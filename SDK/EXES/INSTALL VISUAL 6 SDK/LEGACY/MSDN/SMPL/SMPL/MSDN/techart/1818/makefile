#########################################################################
#
#  For WIN16 application no define is needed.
#
#  nmake
#
#  For WIN32 application the make needs to know if it's an INTEL or MIPS
#  CPU
#
#  nmake CPU=i386
#  nmake CPU=MIPS
#
#  By Default this builds an application with debugging information. To 
#  turn this off use:
#	nmake nodebug=1
#
#
#########################################################################
PROJ	= THREAD

!IF "$(CPU)" != ""

OS      = NT
ENV     = WIN32
EXENAME = THRD32

!ELSE

OS      = DOS
ENV     = WIN16
OUTDIR  = OBJ16
EXENAME = THREAD

!ENDIF

!IF "$(CPU)" == "i386"
OUTDIR = OBJi32
!ENDIF

!IF "$(CPU)" == "MIPS"
OUTDIR = OBJm32
!ENDIF

!include <$(OS)$(ENV).MAK>


###### Inference Rules #####
.c.obj:
  $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fo$(OUTDIR)\ $*.c

.rc.res:
    $(rc) $(rcvars) -r -fo$(OUTDIR)\$*.res $(cvars) $*.rc

.rc.rbj:
    $(rc) $(rcvars) -r -fo$(OUTDIR)\$*.res $(cvars) $*.rc
    cvtres -$(CPU) $(OUTDIR)\$*.res -o $*.rbj


#### Module Macro #####
SRCS    = hlsample.c hldialog.c hierdraw.c
OBJS	= $(OUTDIR)\main.obj $(OUTDIR)\noflick.obj $(OUTDIR)\init.obj

##### Include Macro #####
INCLS	= global.h

###### Resource Macro #####
RCFILES = $(PROJ).rc $(PROJ).ico $(PROJ).dlg

##### Main (default) Target #####
goal: $(OUTDIR) $(OUTDIR)\$(EXENAME).exe

$(OUTDIR):
   -mkdir $(OUTDIR)


###### Dependents For Goal and Command Line #####

$(OUTDIR)\Thread.exe: $(PROJ).def $(OUTDIR)\$(PROJ).res $(OBJS)
	$(link) $(linkdebug) @<<
    $(OBJS),
    $(OUTDIR)\$(EXENAME).exe,
    $(EXENAME).map,
	$(guilibs) mmsystem.lib,
    $(EXENAME).def
<<
    $(RC) -T $(OUTDIR)\$(PROJ).res $(OUTDIR)\$(EXENAME).exe


$(OUTDIR)\Thrd32.exe:  $(OBJS) $(OUTDIR)\$(PROJ).rbj $(EXENAME).def
# This is for Windows NT:
   $(link) $(linkdebug) $(guiflags) $(OBJS) $(guilibsmt) winmm.lib VERSION.LIB \
   $(OUTDIR)\$(PROJ).rbj -out:$(OUTDIR)\$(EXENAME).exe

##### Dependents #####
#$(SRCS:.c=.obj): $(INCLS)

$(OUTDIR)\MAIN.OBJ: MAIN.C
  $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fo$(OUTDIR)\ main.c

$(OUTDIR)\INIT.OBJ: INIT.C
  $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fo$(OUTDIR)\ init.c

$(OUTDIR)\NOFLICK.OBJ: NOFLICK.C
  $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fo$(OUTDIR)\ noflick.c

$(OUTDIR)\$(PROJ).res: $(INCLS) $(PROJ).rc
	$(rc) $(rcvars) -r -fo$(OUTDIR)\$(PROJ).res $(cvars) $(PROJ).rc

$(OUTDIR)\$(PROJ).rbj: $(INCLS) $(PROJ).rc
	$(rc) $(rcvars) -r -fo$(OUTDIR)\$(PROJ).res $(cvars) $(PROJ).rc
    cvtres -$(CPU) $(OUTDIR)\$(PROJ).res -o $(OUTDIR)\$(PROJ).rbj

###### Clean Directory #####
clean:
    -del $(OUTDIR)\*.*
