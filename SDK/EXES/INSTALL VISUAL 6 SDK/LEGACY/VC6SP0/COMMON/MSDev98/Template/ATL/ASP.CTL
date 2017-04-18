[!newguid(InterfaceGUID)]
[!set(Attributes, "00000100000")]

[!Dialog("Names98", "ObjDlg98", "DenaliDlg98")]
[!if=(ConnectionPointsEnabled, "TRUE")]
[!newguid(InterfaceGUIDCP)]
[!endif]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "asp.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "asp.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "asp.rgs")]

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

