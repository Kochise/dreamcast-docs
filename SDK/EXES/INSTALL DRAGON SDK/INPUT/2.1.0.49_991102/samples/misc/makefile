all: dbg rtl

clean dbg rtl:
    cd Passport
    nmake $(@B)
    cd ..\Reboot
    nmake $(@B)
    cd ..\RAS
    nmake $(@B)
    cd ..\VRAMLayout
    nmake $(@B)
    cd ..\DesktopCompat
    nmake $(@B)
    cd ..
