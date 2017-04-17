all: dbg rtl

clean dbg rtl:
    cd PlayVideo
    nmake $(@B)
    cd ..\StreamingVideo
    nmake $(@B)
    cd ..\StreamToTexture
    nmake $(@B)
    cd ..
