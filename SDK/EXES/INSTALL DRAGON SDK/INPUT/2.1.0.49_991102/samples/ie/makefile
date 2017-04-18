all: dbg rtl

clean dbg rtl:
    cd htmlsamp
    nmake $(@B)
    cd ..\reshelp
    nmake $(@B)
    cd ..\ieui
    nmake $(@B)
    cd ..\wininetui
    nmake $(@B)
    cd ..\vibectrl
    nmake $(@B)
    cd ..\mailto
    nmake $(@B)
    cd ..
