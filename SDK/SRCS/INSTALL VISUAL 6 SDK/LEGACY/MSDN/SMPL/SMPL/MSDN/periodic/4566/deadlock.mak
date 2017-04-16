CC_OPTS = /MT /D_MT /O2 /c /YX

all: deadlockexe.exe

deadlockdll.lib: deadlockdll.dll

deadlockdll.dll: deadlockdll.obj
    link /DLL /IMPLIB:deadlockdll.lib /EXPORT:FunctionInADLL deadlockdll.obj

deadlockdll.obj: deadlockdll.h deadlockdll.cpp
    cl $(CC_OPTS) deadlockdll.cpp

deadlockexe.exe: deadlockdll.lib deadlockexe.obj
    link deadlockexe.obj deadlockdll.lib

deadlockexe.obj: deadlockdll.h deadlockexe.cpp
    cl $(CC_OPTS) $(DLLIMPORT) deadlockexe.cpp

Pietrek
Under the Hood
10/03/95
2:05 PM

1


