[!newguid(InterfaceGUID)]

[!Dialog("Names98", "ViperDlg98")]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "msdtx.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "msdtx.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "msdtx.rgs")]

[!AddSymbolToSymbol(RGSName, ProjectDirectory, ShortName)]
[!AddStringToSymbol(RGSName, RGSName, ".rgs")]

[!target(RGSName)]
[!include(RGSTemplate)]
[!target()]

[!AddSymbolToString(IDR_REGISTRYID, "IDR_", UpperShortName)]
[!AddRegistryToRC(RGSName, IDR_REGISTRYID)]

[!target(HeaderName)]
[!include(HeaderTemplate)]
[!target()]

[!target(CPPName)]
[!include(CPPTemplate)]
[!target()]

[!AddStringToSymbol(IDLInterface, GalleryPath, "objint.idl")]
[!AddStringToSymbol(IDLCoClass, GalleryPath, "objco.idl")]
[!AddInterfaceToIDL(IDLProject, IDLInterface)]
[!AddCoClassToIDL(IDLProject, IDLCoClass)]

[!target(IDLName)]
[!include(IDLTemplate)]
[!target()]

[!AddToObjectMap(CoClassName, ClassName)]

[!set(initguid.h, "<initguid.h>")]
[!AddIncludeFile(ProjectNameCPP,  initguid.h)]

[!AddSymbolToString(header, "\"", HeaderName)]
[!AddStringToSymbol(header, header, "\"")]
[!AddImportFile(IDLProject, "oaidl.idl")]
[!AddIncludeFile(ProjectNameCPP,  header)]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]
