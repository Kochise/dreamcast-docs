all: dbg rtl

clean dbg rtl:
    cd Lightgun
    nmake $(@B)
    cd ..\VibrationPack
    nmake $(@B)
    cd ..\VMU_Flash
    nmake $(@B)
    cd ..\VMU_LCD
    nmake $(@B)
    cd ..\VMU_Timer
    nmake $(@B)
    cd ..
