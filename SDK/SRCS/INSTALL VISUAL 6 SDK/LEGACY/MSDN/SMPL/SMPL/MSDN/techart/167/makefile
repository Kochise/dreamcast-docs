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
PROJ    = HLSAMPLE

!IF "$(CPU)" != ""

OS      = NT
ENV     = WIN32
EXENAME = HLSAMP32

!ELSE

OS      = DOS
ENV     = WIN16
OUTDIR  = OBJ16
EXENAME = HLSAMPLE

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
  $(cc) $(cflags) $(cvars) $(cdebug) -Fo$(OUTDIR)\ $*.c

.rc.res:
    $(rc) $(rcvars) -r -fo$(OUTDIR)\$*.res $(cvars) $*.rc

.rc.rbj:
    $(rc) $(rcvars) -r -fo$(OUTDIR)\$*.res $(cvars) $*.rc
    cvtres -$(CPU) $(OUTDIR)\$*.res -o $*.rbj


#### Module Macro #####
SRCS    = hlsample.c hldialog.c hierdraw.c
OBJS    = $(OUTDIR)\hlsample.obj $(OUTDIR)\hldialog.obj $(OUTDIR)\hierdraw.obj

##### Include Macro #####
INCLS   = $(PROJ).h

###### Resource Macro #####
RCFILES = $(PROJ).rc $(PROJ).ico $(PROJ).dlg

##### Main (default) Target #####
goal: $(OUTDIR) $(OUTDIR)\$(EXENAME).exe

$(OUTDIR):
   -mkdir $(OUTDIR)


###### Dependents For Goal and Command Line #####

$(OUTDIR)\hlsample.exe: $(PROJ).def $(OUTDIR)\$(PROJ).res $(OBJS)
    $(link) @<<
    $(OBJS),
    $(OUTDIR)\$(EXENAME).exe,
    $(EXENAME).map,
    $(guilibs),
    $(EXENAME).def
<<
    $(RC) -T $(OUTDIR)\$(PROJ).res $(OUTDIR)\$(EXENAME).exe


$(OUTDIR)\hlsamp32.exe:  $(OBJS) $(OUTDIR)\$(PROJ).rbj $(EXENAME).def
# This is for Windows NT:
   $(link) $(linkdebug) $(guiflags) $(OBJS) $(guilibs) VERSION.LIB \
   $(OUTDIR)\$(PROJ).rbj -out:$(OUTDIR)\$(EXENAME).exe

##### Dependents #####
#$(SRCS:.c=.obj): $(INCLS)

$(OUTDIR)\hlsample.obj: hlsample.c $(INCLS)
  $(cc) $(cflags) $(cvars) $(cdebug) -Fo$(OUTDIR)\ hlsample.c

$(OUTDIR)\hldialog.obj: hldialog.c $(INCLS)
  $(cc) $(cflags) $(cvars) $(cdebug) -Fo$(OUTDIR)\ hldialog.c

$(OUTDIR)\hierdraw.obj: hierdraw.c $(INCLS)
  $(cc) $(cflags) $(cvars) $(cdebug) -Fo$(OUTDIR)\ hierdraw.c

$(OUTDIR)\$(PROJ).res: $(INCLS) $(RCFILES)
    $(rc) $(rcvars) -r -fo$(OUTDIR)\$(PROJ).res $(cvars) $(PROJ).rc

$(OUTDIR)\$(PROJ).rbj: $(INCLS) $(RCFILES)
    $(rc) $(rcvars) -r -fo$(OUTDIR)\$(PROJ).res $(cvars) $(PROJ).rc
    cvtres -$(CPU) $(OUTDIR)\$(PROJ).res -o $(OUTDIR)\$(PROJ).rbj

###### Clean Directory #####
clean:
    -del $(OUTDIR)\*.*
