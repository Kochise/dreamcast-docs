all:    debug wbpost


debug:
    nmake /f wbpost.mak INCLUDE="..\..\..\..\include;.;$(INCLUDE)" CFG="wbpost - Win32 Debug"

wbpost:
    nmake /f wbpost.mak INCLUDE="..\..\..\..\include;.;$(INCLUDE)" CFG="wbpost - Win32 Release"

clean:
    nmake /f wbpost.mak CFG="wbpost - Win32 Debug" clean
    nmake /f wbpost.mak CFG="wbpost - Win32 Release" clean



