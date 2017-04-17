all: dbg rtl

clean dbg rtl:
    cd BasicD3DIM
    nmake $(@B)
    cd ..\BumpMapping
    nmake $(@B)
    cd ..\MipMapping
    nmake $(@B)
    cd ..\Optimal
    nmake $(@B)
    cd ..\LoadTexture
    nmake $(@B)
    cd ..\ShadowVolumes
    nmake $(@B)
    cd ..\RearViewMirror
    nmake $(@B)
    cd ..\Portal
    nmake $(@B)
    cd ..\ComplexModifierVolumes
    nmake $(@B)
    cd ..
