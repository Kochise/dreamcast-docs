[!newguid(InterfaceGUID)]
[!set(ThreadingModel, "Single")]
[!Dialog("Names98", "AddInDlg98")]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "addin.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "addin.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "addin.rgs")]

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

[!AddStringToSymbol(IDLInterface, GalleryPath, "addinint.idl")]
[!AddStringToSymbol(IDLCoClass, GalleryPath, "addinco.idl")]
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

[!if!(stdafx.h)]
[!set(stdafx.h, "stdafx.h")]
[!endif]
[!set(addauto.h, "<ObjModel\addauto.h>")]
[!set(appdefs.h, "<ObjModel\appdefs.h>")]
[!set(appauto.h, "<ObjModel\appauto.h>")]
[!set(blddefs.h, "<ObjModel\blddefs.h>")]
[!set(bldauto.h, "<ObjModel\bldauto.h>")]
[!set(textdefs.h, "<ObjModel\textdefs.h>")]
[!set(textauto.h, "<ObjModel\textauto.h>")]
[!set(dbgdefs.h, "<ObjModel\dbgdefs.h>")]
[!set(dbgauto.h, "<ObjModel\dbgauto.h>")]
[!AddIncludeFile(stdafx.h, addauto.h)]
[!AddIncludeFile(stdafx.h, appdefs.h)]
[!AddIncludeFile(stdafx.h, appauto.h)]
[!AddIncludeFile(stdafx.h, blddefs.h)]
[!AddIncludeFile(stdafx.h, bldauto.h)]
[!AddIncludeFile(stdafx.h, textdefs.h)]
[!AddIncludeFile(stdafx.h, textauto.h)]
[!AddIncludeFile(stdafx.h, dbgdefs.h)]
[!AddIncludeFile(stdafx.h, dbgauto.h)]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]


[!DoubleSlash(DGalleryPath, GalleryPath)]

[!AddSymbolToString(IDB_TOOLBAR_LARGE, "IDB_TOOLBAR_LARGE_", UpperShortName)]
[!GetTemporaryFileName(RCTemp)]
[!target(RCTemp)]
BITMAP	MOVEABLE PURE	"[!DGalleryPath]TBarLrge.bmp"
[!target()]
[!AddResourceFromFile(RCTemp, IDB_TOOLBAR_LARGE, "BITMAP")]
[!DeleteFile(RCTemp)]

[!AddSymbolToString(IDB_TOOLBAR_MEDIUM, "IDB_TOOLBAR_MEDIUM_", UpperShortName)]
[!GetTemporaryFileName(RCTemp)]
[!target(RCTemp)]
BITMAP	MOVEABLE PURE	"[!DGalleryPath]TBarMedm.bmp"
[!target()]
[!AddResourceFromFile(RCTemp, IDB_TOOLBAR_MEDIUM, "BITMAP")]
[!DeleteFile(RCTemp)]
