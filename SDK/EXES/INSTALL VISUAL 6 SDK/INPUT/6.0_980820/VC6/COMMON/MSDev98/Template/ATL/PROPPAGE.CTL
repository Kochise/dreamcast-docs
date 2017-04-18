[!set(ComponentType, "1111011")]
[!set(Attributes,    "00000000010")]
[!Dialog("Names98", "ObjDlg98", "PropDlg98")]
[!if=(ConnectionPointsEnabled, "TRUE")]
[!newguid(InterfaceGUIDCP)]
[!endif]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddSymbolToString(IDS_TITLE, "IDS_TITLE", ShortName)]
[!AddSymbolToString(IDS_HELPFILE, "IDS_HELPFILE", ShortName)]
[!AddSymbolToString(IDS_DOCSTRING, "IDS_DOCSTRING", ShortName)]
[!AddStringResource(IDS_TITLE, PropTitle)]
[!AddStringResource(IDS_HELPFILE, PropHelpFile)]
[!AddStringResource(IDS_DOCSTRING, PropDocString)]


[!AddStringToSymbol(HeaderTemplate, GalleryPath, "proppage.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "proppage.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "proppage.rgs")]
[!AddStringToSymbol(IDLTemplate, GalleryPath, "proppage.idl")]

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

[!AddStringToSymbol(IDLCoClass, GalleryPath, "proppage.idl")]
[!AddCoClassToIDL(IDLProject, IDLCoClass)]

[!AddToObjectMap(CoClassName, ClassName)]

[!AddSymbolToString(header, "\"", HeaderName)]
[!AddStringToSymbol(header, header, "\"")]
[!AddImportFile(IDLProject, "oaidl.idl")]
[!AddIncludeFile(ProjectNameCPP,  header)]

[!if!(stdafx.h)]
[!set(stdafx.h, "stdafx.h")]
[!endif]
[!if!(stdafx.cpp)]
[!set(stdafx.cpp, "stdafx.cpp")]
[!endif]
[!set(atlctl.h, "<atlctl.h>")]
[!set(atlwin.h, "<atlwin.h>")]
[!AddIncludeFile(stdafx.h, atlctl.h)]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]

[!AddSymbolToString(IDD_DIALOGID, "IDD_", UpperShortName)]

[!AddStringToSymbol(RCFile, GalleryPath, "propdlg.rc")]
[!AddResourceFromFile(RCFile, IDD_DIALOGID, "DIALOG")]
[!if(VC)]
[!Commit()]
[!OpenDialog(IDD_DIALOGID)]
[!endif]
