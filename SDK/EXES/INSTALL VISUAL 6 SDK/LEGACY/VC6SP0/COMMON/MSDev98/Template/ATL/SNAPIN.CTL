[!set(ComponentType, "11111011")]
[!newguid(SnapInGUID)]
[!newguid(SnapInAboutGUID)]
[!newguid(SnapInNodeType)]
[!set(ThreadingModel, "Apartment")]

[!Dialog("Names98", "SnapInObj98")]

[!DoubleSlash(DGalleryPath, GalleryPath)]
[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(RGSTemplate, GalleryPath, "snapin.rgs")]
[!AddSymbolToSymbol(RGSName, ProjectDirectory, ShortName)]
[!AddStringToSymbol(RGSName, RGSName, ".rgs")]

[!target(RGSName)]
[!include(RGSTemplate)]
[!target()]

[!AddStringToSymbol(BMPTemplate16, DGalleryPath, "SnapIn16.bmp")]
[!AddStringToSymbol(BMPTemplate32, DGalleryPath, "SnapIn32.bmp")]

[!AddSymbolToString(IDB_SNAPIN16, "IDB_", UpperShortName)]
[!AddStringToSymbol(IDB_SNAPIN16, IDB_SNAPIN16, "_16")]
[!GetTemporaryFileName(RCTemp)]
[!target(RCTemp)]
BITMAP  DISCARDABLE     "[!BMPTemplate16]"
[!target()]
[!AddResourceFromFile(RCTemp, IDB_SNAPIN16, "BITMAP")]
[!DeleteFile(RCTemp)]

[!AddSymbolToString(IDB_SNAPIN32, "IDB_", UpperShortName)]
[!AddStringToSymbol(IDB_SNAPIN32, IDB_SNAPIN32, "_32")]
[!GetTemporaryFileName(RCTemp)]
[!target(RCTemp)]
BITMAP  DISCARDABLE     "[!BMPTemplate32]"
[!target()]
[!AddResourceFromFile(RCTemp, IDB_SNAPIN32, "BITMAP")]
[!DeleteFile(RCTemp)]

[!if=(IExtendContextMenu, "TRUE)]
[!AddSymbolToString(IDR_MENU, "IDR_", UpperShortName)]
[!AddStringToSymbol(IDR_MENU, IDR_MENU, "_MENU")]
[!GetTemporaryFileName(RCTemp)]
[!target(RCTemp)]
MENU DISCARDABLE 
BEGIN
    POPUP "TOP"
    BEGIN
        MENUITEM SEPARATOR
    END
    POPUP "NEW"
    BEGIN
        MENUITEM SEPARATOR
    END
    POPUP "TASK"
    BEGIN
        MENUITEM SEPARATOR
    END
    POPUP "VIEW"
    BEGIN
        MENUITEM SEPARATOR
    END
END
[!target()]
[!AddResourceFromFile(RCTemp, IDR_MENU, "MENU")]
[!DeleteFile(RCTemp)]
[!endif]

[!if=(IExtendPropertySheet, "TRUE)]
[!AddSymbolToString(IDD_PROPPAGE, "IDD_", UpperShortName)]
[!comment(Add directives to add a property page template)]
[!AddStringToSymbol(DLGTemplate, GalleryPath, "snapin.rc")]
[!AddResourceFromFile(DLGTemplate, IDD_PROPPAGE, "DIALOG")]
[!endif]

[!if=(ISnapinAbout, "TRUE")]
[!AddSymbolToString(IDS_DESC, "IDS_", UpperShortName)]
[!AddStringToSymbol(IDS_DESC, IDS_DESC, "_DESC")]
[!AddSymbolToString(IDS_PROVIDER, "IDS_", UpperShortName)]
[!AddStringToSymbol(IDS_PROVIDER, IDS_PROVIDER, "_PROVIDER")]
[!AddSymbolToString(IDS_VERSION, "IDS_", UpperShortName)]
[!AddStringToSymbol(IDS_VERSION, IDS_VERSION, "_VERSION")]
[!AddStringToSymbol(DESC, ShortName, " Description")]
[!AddStringToSymbol(PROVIDER, ShortName, " Provider")]
[!AddStringToSymbol(VERSION, ShortName, " Version 1.0")]

[!AddStringResource(IDS_DESC, DESC)]
[!AddStringResource(IDS_PROVIDER, PROVIDER)]
[!AddStringResource(IDS_VERSION, VERSION)]
[!endif]

[!AddStringToSymbol(SnapInCoClass, GalleryPath, "snapin.idl")]
[!AddCoClassToIDL(IDLProject, SnapInCoClass)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "snapin.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "snapin.cpp")]
[!AddSymbolToString(IDR_REGISTRYID, "IDR_", UpperShortName)]
[!AddRegistryToRC(RGSName, IDR_REGISTRYID)]

[!target(HeaderName)]
[!include(HeaderTemplate)]
[!target()]

[!target(CPPName)]
[!include(CPPTemplate)]
[!target()]

[!if!(stdafx.h)]
[!set(stdafx.h, "stdafx.h")]
[!endif]
[!if!(stdafx.cpp)]
[!set(stdafx.cpp, "stdafx.cpp")]
[!endif]
[!set(atlwin.h, "<atlwin.h>)]
[!AddIncludeFile(stdafx.h, atlwin.h)]

[!AddSymbolToString(header, "\"", HeaderName)]
[!AddStringToSymbol(header, header, "\"")]
[!AddIncludeFile(ProjectNameCPP,  header)]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]
[!AddToObjectMap(CoClassName, ClassName)]

[!if=(ISnapinAbout, "TRUE")]
[!AddStringToSymbol(AboutClassName, ClassName, "About")]
[!AddStringToSymbol(AboutClassNameCLSID, CoClassName, "About")]
[!AddToObjectMap(AboutClassNameCLSID, AboutClassName)]
[!endif]
