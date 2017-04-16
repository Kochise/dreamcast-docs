# Standard Windows make file.  The utility MAKE.EXE compares the
# creation date of the file to the left of the colon with the file(s)
# to the right of the colon.  If the file(s) on the right are newer
# then the file on the left, Make will execute all of the command lines
# following this line that are indented by at least one tab or space.
# Any valid MS-DOS command line may be used.

# This line allows NMAKE to work as well

all: transblt.res transblt.exe

# Update the resource if necessary

transblt.res: transblt.rc transblt.h
    rc -r transblt.rc

# Update the object file if necessary

transblt.obj: transblt.c transblt.h
    cl -c -AS -Gsw -Oas -Zpe transblt.c

# Update the executable file if necessary, and if so, add the resource back in.

transblt.exe: transblt.obj transblt.def
    link /NOD transblt,,, libw slibcew, transblt.def
    rc transblt.res

clean:
    -del *.obj
    -del *.res
    -del *.sym
    -del *.map
