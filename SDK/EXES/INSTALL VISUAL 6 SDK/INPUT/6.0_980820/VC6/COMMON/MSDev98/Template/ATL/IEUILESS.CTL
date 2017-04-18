[!newguid(InterfaceGUID)]
[!set(IOBJECTWITHSITE, "TRUE")]

[!Dialog("Names98", "ObjDlg98")]
[!if=(ConnectionPointsEnabled, "TRUE")]
[!newguid(InterfaceGUIDCP)]
[!endif]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "object.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "object.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "object.rgs")]
[!AddStringToSymbol(HTMTemplate, GalleryPath, "default.htm")]

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

[!AddStringToSymbol(HTMName, ShortName, ".htm")]

[!target(HTMName)]
[!include(HTMTemplate)]
[!target()]

[!AddStringToSymbol(IDLInterface, GalleryPath, "objint.idl")]
[!AddStringToSymbol(IDLCoClass, GalleryPath, "objco.idl")]
[!AddInterfaceToIDL(IDLProject, IDLInterface)]
[!AddCoClassToIDL(IDLProject, IDLCoClass)]

[!target(IDLName)]
[!include(IDLTemplate)]
[!target()]

[!AddToObjectMap(CoClassName, ClassName)]

[!AddSymbolToString(header, "\"", HeaderName)]
[!AddStringToSymbol(header, header, "\"")]
[!AddImportFile(IDLProject, "oaidl.idl")]
[!AddImportFile(IDLProject, "ocidl.idl")]
[!AddIncludeFile(ProjectNameCPP,  header)]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]

