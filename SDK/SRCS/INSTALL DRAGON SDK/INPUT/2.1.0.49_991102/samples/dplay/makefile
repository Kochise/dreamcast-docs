all: dbg rtl

clean dbg rtl:
    cd Client
    nmake $(@B)
    cd ..\Server
    nmake $(@B)
    cd ..\PeerToPeer
    nmake $(@B)
    cd ..
