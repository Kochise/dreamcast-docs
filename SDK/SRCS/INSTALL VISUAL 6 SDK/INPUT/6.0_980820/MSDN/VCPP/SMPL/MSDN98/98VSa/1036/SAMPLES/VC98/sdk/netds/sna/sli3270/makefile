USE_SNA=1
console=1

Proj = WSli3270

!include <BkOffice.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!endif

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).exe: $(@D)\Sli3270.obj # can't use default rule since filenames differ
 Link $(LFLAGS) $(linkflags) $** $(LinkLibs) $(LogCmd)
