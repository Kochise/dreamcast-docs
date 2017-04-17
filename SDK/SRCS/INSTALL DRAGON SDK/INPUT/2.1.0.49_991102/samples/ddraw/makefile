all: dbg rtl

clean dbg rtl:
    cd AlphaBlt
    nmake $(@B)
    cd ..\BasicDDraw
    nmake $(@B)
    cd ..\Palettes
    nmake $(@B)
    cd ..\VQSurfaces
    nmake $(@B)
    cd ..

