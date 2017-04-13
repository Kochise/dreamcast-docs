
TARGETOS=WINNT

# define compile & link options
!include <win32.mak>

all: cfiler.exe cf.hlp

OBJS=cfiler.obj crp.obj drvproc.obj enumdrv.obj expdir.obj fillfile.obj table.obj


# Update the resource if necessary
cfiler.res: cfiler.rc  *.bmp *.ico
    $(rc) $(rcvars) -r cfiler.rc


# Build rule for converting c files to obj files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c


# Update the online help file
cf.hlp: cf.hpj cf.rtf
    $(hc) cf.hpj


# Update the executable file
cfiler.exe: $(OBJS) cfiler.res
    $(link) $(linkdebug)  $(guiflags) -out:$*.exe $** $(guilibsmt)
