!include <ntwin32.mak>


cvars=-DNT -DWIN -DWIN32
obj=obj
mycflag = -Fo.\$(obj)\\

all: iconpro.exe iconpro.hlp

# Update the object file if necessary

$(obj)\iconpro.obj: iconpro.c iconpro.h resource.h icons.h mdichild.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) iconpro.c

$(obj)\dib.obj: dib.c dib.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) dib.c

$(obj)\icons.obj: icons.c iconpro.h resource.h icons.h dib.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) icons.c

$(obj)\mdichild.obj: mdichild.c iconpro.h resource.h icons.h mdichild.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) mdichild.c

# Update the resources if necessary

$(obj)\iconpro.res: iconpro.rc iconpro.h resource.h
    rc -r -fo .\$(obj)\iconpro.res iconpro.rc

# Build the help file if necessary

iconpro.hlp: iconpro.hpj iconpro.rtf
    $(hc) iconpro.hpj

# Update the executable file if necessary, and if so, add the resource back in.

iconpro.exe: $(obj)\iconpro.obj \
	$(obj)\mdichild.obj \
	$(obj)\icons.obj \
	$(obj)\dib.obj \
	     $(obj)\iconpro.res
    $(link) $(linkdebug) $(guiflags) -out:iconpro.exe	 \
    $(obj)\iconpro.obj \
    $(obj)\mdichild.obj \
    $(obj)\icons.obj \
    $(obj)\dib.obj \
    $(obj)\iconpro.res $(guilibs) shell32.lib
