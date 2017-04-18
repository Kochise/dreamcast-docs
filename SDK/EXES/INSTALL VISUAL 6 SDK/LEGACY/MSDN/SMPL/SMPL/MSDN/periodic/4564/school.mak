###############################################################################
#
#    SCHOOL.MAK -- Make file for School Bus Example
#
#    Use with C9 (32-bit) and MASM 6.11 from DDK
#
###############################################################################

all: school.vxd telepath.vxd

.asm.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -Zi -DDEBUG $*.asm

.c.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.c

.rc.res:
   c:\msvc\bin\rc -r $*.rc   # must use RC16 for this

school.res telepath.res: version.h $*.rc

school.vxd : s_ctl.obj $*.obj $*.def $*.res
   link @<<
-machine:i386 -def:$*.def -out:$@
-debug -debugtype:map
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
s_ctl.obj $*.obj
<<
   c:\winice95\msym $*
   adrc2vxd $*.vxd $*.res

telepath.vxd: t_ctl.obj $*.obj $*.def $*.res
   link @<<
-machine:i386 -def:$*.def -out:$@
-debug -debugtype:map
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
t_ctl.obj $*.obj
<<
   c:\winice95\msym $*
   adrc2vxd $*.vxd $*.res

clean:
   del s_ctl.obj
   del vc20.pch
   del school.obj
   del school.res
   del school.lib
   del school.exp
   del school.map
   del school.wsp
   del t_ctl.obj
   del telepath.obj
   del telepath.res
   del telepath.lib
   del telepath.exp
   del telepath.map
