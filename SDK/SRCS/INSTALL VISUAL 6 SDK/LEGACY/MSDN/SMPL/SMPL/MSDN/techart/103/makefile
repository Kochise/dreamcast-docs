# Makefile : Builds the helloapp application
#

cprog1.exe: cprog1.obj cprog1.def
	link /NOD /ONERROR:NOEXE cprog1,,,safxcw libw slibcew,cprog1.def;
	rc /t cprog1.exe

cprog1.obj: cprog1.cpp
	cl /Zp /Od /c /W3 cprog1.cpp

clean:
	-del cprog1.exe
	-del cprog1.obj
