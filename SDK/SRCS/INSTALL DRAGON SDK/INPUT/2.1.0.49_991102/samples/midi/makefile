all: dbg rtl

clean dbg rtl:
    cd PlayMIDI
    nmake $(@B)
    cd ..\PlayMultipleMIDI
    nmake $(@B)
    cd ..\Format1
    nmake $(@B)
    cd ..
