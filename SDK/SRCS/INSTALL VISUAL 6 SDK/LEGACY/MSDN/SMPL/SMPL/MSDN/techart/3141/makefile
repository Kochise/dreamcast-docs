PROJ = Generic
SRC = Generic.C

# Make the apropriate changes in the above to match your projects needs.
#
# 'PROJ' in above controls the name of the resultant executable
#
# 'SRC' in above is a list of the 'C' sources that make up this project
#
# Make sure that your current INCLUDE and LIB environment variables include
# the locations necessary to resolve any additional files necessary to build
# this project. If you don't want your system wide environment variables to
# point to the 'Chicago' SDK components, you can modify, and uncomment the
# below two lines appropriately:
#
#INCLUDE = D:\CHICAGO.SDK\INC32;$(INCLUDE)
#LIB = D:\CHICAGO.SDK\LIB32;$(LIB)

all: $(PROJ).exe $(PROJ).hlp

#DEBUG = 1
# To enable 'DEBUG' mode, you can either uncomment the line above, or
# you can create a local environment variable called 'DEBUG':
#       C:\> set debug=1
# Note that it is merely the existance of this variable that is being
# tested, not the value. Even 'set debug=0' will cause debug mode
# to be used.


# If no CPU designation is set as an environment variable, assume Intel
!IF "$(CPU)" == ""
CPU=i386
!ENDIF


# Compiler Options: --------------------------------------------------------
cc = cl
cflags = /nologo /W3 /DWIN32 /D_WINDOWS /c
cdebug = /G3 /Zi /D_DEBUG /Od
cretail= /Os


# Resource Compiler Options: -----------------------------------------------
rc = rc
rcflags = /dWIN32


# Help Compiler Options: --------------------------------------------------
hc = hc31
hcflags =


# Linker Options: ----------------------------------------------------------
# Note the use of /SUBSYSTEM:windows,4.0 below. This tells 'Chicago' that
# this is a 'Chicago' aware executable. One of the things this will provide,
# is make the default dialog background 'gray' rather then 'white'. If you
# end up needing to run this program on a Win32 system that is not aware of
# the '4.0' specification (ie: it gives you an error message when it tries
# to load) then you will need to remove the ",4.0" portion below.
link = link
libs = user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib version.lib\
       shell32.lib ole32.lib oleaut32.lib uuid.lib olecli32.lib olesvr32.lib
lflags = /SUBSYSTEM:windows,4.0  /MACHINE:$(CPU) /DEF:$(PROJ).DEF
ldebug = /DEBUG
lretail=
objfiles= $(SRC:.C=.OBJ) $(PROJ).RES


# Inference Rules: ---------------------------------------------------------

.c.obj:
!IFDEF DEBUG
    $(cc) $(cflags) $(cdebug) $<
!ELSE
    $(cc) $(cflags) $(cretail) $<
!ENDIF


.rc.res:
    $(rc) $(rcflags) -r $<


$(PROJ).hlp: $(PROJ).hpj $(PROJ).rtf
    $(hc) $(hcflags) $(PROJ).hpj


# Build The Project: -------------------------------------------------------

$(PROJ).exe: $(SRC:.C=.OBJ) $(PROJ).def $(PROJ).res
!IFDEF DEBUG
      $(link) @<<
	  $(lflags) $(ldebug) $(objfiles) $(libs)
<<
!ELSE
      $(link) @<<
	  $(lflags) $(lretail) $(objfiles) $(libs)
<<
!ENDIF
