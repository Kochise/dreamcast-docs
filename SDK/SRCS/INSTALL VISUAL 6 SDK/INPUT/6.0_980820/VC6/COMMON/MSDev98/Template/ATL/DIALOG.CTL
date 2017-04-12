[!set(ComponentType, "11110000")]
[!Dialog("Names98")]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "dialog.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "dialog.cpp")]

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
[!set(atlwin.h, "<atlwin.h>")]
[!AddIncludeFile(stdafx.h, atlwin.h)]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]

[!AddSymbolToString(IDD_DIALOGID, "IDD_", UpperShortName)]

[!AddStringToSymbol(RCFile, GalleryPath, "dialog.rc")]
[!AddResourceFromFile(RCFile, IDD_DIALOGID, "DIALOG")]
[!if(VC)]
[!Commit()]
[!OpenDialog(IDD_DIALOGID)]
[!endif]
