all: dbg rtl

clean:
    nmake /f "ShadowVolumes.mak" CFG="ShadowVolumes - Win32 (WCE SH4) Release" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" CLEAN
    nmake /f "ShadowVolumes.mak" CFG="ShadowVolumes - Win32 (WCE SH4) Debug" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" CLEAN

dbg:
    nmake /f "ShadowVolumes.mak" CFG="ShadowVolumes - Win32 (WCE SH4) Debug" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" 

rtl:
    nmake /f "ShadowVolumes.mak" CFG="ShadowVolumes - Win32 (WCE SH4) Release" CEConfigName="Dreamcast" CEVersion="212" CESubsystem="windowsce,2.12" 
