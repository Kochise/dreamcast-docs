USE_SNA=1
console=1

Proj = Rui3270

!include <BkOffice.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).exe: $(@R).obj

