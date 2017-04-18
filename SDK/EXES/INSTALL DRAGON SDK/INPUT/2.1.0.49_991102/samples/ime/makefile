all: dbg rtl

clean dbg rtl:
    cd tkimelib
    nmake $(@B)
    cd ..\tkime
    nmake $(@B)
    cd ..\pime
    nmake $(@B)
    cd ..\tcime
    nmake $(@B)
    cd ..
