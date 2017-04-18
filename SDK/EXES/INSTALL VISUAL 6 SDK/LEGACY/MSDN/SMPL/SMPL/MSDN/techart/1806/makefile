PROJ	= STYLES32

OS      = NT
ENV     = WIN32
EXENAME = STYLES32

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
SRCS	= styles.c
OBJS	= $(OUTDIR)\styles.obj

##### Include Macro #####
INCLS	= styles.h

###### Resource Macro #####
RCFILES = styles.rc styles.ico create.dlg

##### Main (default) Target #####
goal: $(OUTDIR) $(OUTDIR)\$(EXENAME).exe

$(OUTDIR):
   -mkdir $(OUTDIR)


###### Dependents For Goal and Command Line #####
$(OUTDIR)\Styles32.exe:  $(OBJS) $(OUTDIR)\styles.rbj styles.def
   $(link) $(linkdebug) $(guiflags) $(OBJS) $(guilibsmt) \
   $(OUTDIR)\styles.rbj -out:$(OUTDIR)\$(EXENAME).exe

##### Dependents #####
#$(SRCS:.c=.obj): $(INCLS)

$(OUTDIR)\styles.OBJ: styles.C
  $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fo$(OUTDIR)\ styles.c

$(OUTDIR)\styles.rbj: $(INCLS) styles.rc
	$(rc) $(rcvars) -r -fo$(OUTDIR)\styles.res $(cvars) styles.rc
	cvtres -$(CPU) $(OUTDIR)\styles.res -o $(OUTDIR)\styles.rbj

###### Clean Directory #####
clean:
    -del $(OUTDIR)\*.*













.rc.res:
    rc -dWIN31 -r $*.rc

.c.obj:
    cl -DWIN31 -DSTRICT -D_WINDOWS /DCTLAPIS -W3 -u -c -AS -G2sw -Od -Zipe $*.c


all: styles.exe

styles.res: styles.rc styles.h styles.ico create.dlg

styles.obj: styles.c styles.h

styles.exe: styles.obj styles.def styles.res
    link /NOD styles,styles.exe/align:16,, libw slibcew, styles.def /CO
    rc styles.res
