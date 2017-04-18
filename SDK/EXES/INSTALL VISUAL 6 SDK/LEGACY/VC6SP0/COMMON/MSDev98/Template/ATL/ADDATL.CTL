[!Debug()]
[!newguid(TypelibGUID)]

[!AddSymbolToString(MIDLHeader, "\"", ProjectName)]
[!AddStringToSymbol(MIDLHeader, MIDLHeader, "_i.h\"")]

[!AddSymbolToString(MIDLC, "\"", ProjectName)]
[!AddStringToSymbol(MIDLC, MIDLC, "_i.c\"")]

[!if!(ProjectNameHeader)]
[!AddStringToSymbol(ProjectNameHeader, ProjectName, ".h")]
[!endif]

[!if!(ProjectNameCPP)]
[!AddStringToSymbol(ProjectNameCPP, ProjectName, ".cpp")]
[!endif]


[!set(INITGUIDH, "<initguid.h>")]

[!AddIncludeFile(ProjectNameHeader,  MIDLHeader)]
[!AddIncludeFile(ProjectNameCPP,  INITGUIDH)]
[!AddIncludeFile(ProjectNameCPP,  MIDLC)]

[!AddStringToSymbol(stdafxinclude, GalleryPath, "aatlsdt.h")]
[!AddStringToSymbol(stdafxcpptemplate, GalleryPath, "aatlsdt.cpp")]
[!if!(STDAFXCPP)]
[!AddStringToSymbol(STDAFXCPP, ProjectDirectory, "stdafx.cpp")]
[!endif]
[!AddStringToSymbol(IDLTemplate, GalleryPath, "addatl.idl")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "addatl.rgs")]
[!AddSymbolToSymbol(RGSName, ProjectDirectory, ProjectName)]
[!AddStringToSymbol(RGSName, RGSName, ".rgs")]
[!strcpy(UpperProjectNameSafe, ProjectNameSafe)]
[!toupper(UpperProjectNameSafe)]
[!AddSymbolToString(IDR_REGISTRYID, "IDR_", UpperProjectNameSafe)]

[!if=(MFCCTL, "0")]
[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "AfxOleInit", MFCOLE)]
[!else]
[!set(MFCOLE, "1")]
[!endif]


[!if!(ProjectHadIDL)]
	[!AddStringToSymbol(IDLProject, ProjectName, ".idl")]
	[!target(IDLProject)]
	[!include(IDLTemplate)]
	[!target()]
	[!AddFileToProject(IDLProject)]
[!endif]

[!newguid(AppIDGUID)]

[!target(RGSName)]
[!include(RGSTemplate)]
[!target()]
[!AddRegistryToRC(RGSName, IDR_REGISTRYID)]


[!target(STDAFXH)]
	[!include(stdafxinclude)]
[!target()]

[!target(STDAFXCPP)]
	[!include(stdafxcpptemplate)]
[!target()]

[!if=(ProjectType, "EXE")]
	[!AddStringToSymbol(projectheadertemplate, GalleryPath, "aatlproj.h")]
	[!AddStringToSymbol(projectcpptemplate, GalleryPath, "aatlproj.cpp")]


	[!AddMemberVariable(CWinApp, "m_bATLInited", "BOOL", "ACCESS_PRIVATE", "1", ATLINITED)]

	[!ExistsMemberFunction(CWinApp, "int ExitInstance()", ExitInstance)]

	[!if=(ExitInstance, "1")]
		[!AddToMemberFunction(CWinApp, "int ExitInstance()", projectcpptemplate, InsertIntoExitInstance, BEFORESEARCH, "CWinApp::ExitInstance", )]
	[!else]
		[!AddMemberFunction(CWinApp, "ExitInstance", "virtual int", "", "ACCESS_PUBLIC", projectcpptemplate, 1, AddExitInstance)]
	[!endif]

	[!RemoveSymbol("ExitInstance")]

	[!AddMemberFunction(CWinApp, "InitATL", "BOOL", "", "ACCESS_PRIVATE", projectcpptemplate, 0, INITATL, BEFORESEARCH)]

	[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "AfxEnableControlContainer();", ACTIVEXCTLSUPPORT)]
	[!if=(ACTIVEXCTLSUPPORT, "1")]
		[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertInInitInstance, BEFORESEARCH, "AfxEnableControlContainer")]
	[!else]
		[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertInInitInstance, BEGIN)]
	[!endif]

	[!if=(MFCOLE, "0")]
		[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "ParseCommandLine(cmdInfo);", PARSECOMMANDINFO)]
		[!if=(PARSECOMMANDINFO, "0")]
			[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "AfxEnableControlContainer();", AFXENABLECONTROLCONTAINER)]
			[!if=(AFXENABLECONTROLCONTAINER, "0")]
				[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertAfterAfxEnableControlContainer, BEGIN)]
			[!else]
				[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertAfterAfxEnableControlContainer, AFTERSEARCH, "AfxEnableControlContainer();")]
			[!endif]
		[!else]
			[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertAfterParseCommand, AFTERSEARCH, "ParseCommandLine(cmdInfo);")]
		[!endif]

	[!else]
		[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "COleTemplateServer::RegisterAll();", REGISTERALL)]
		[!if=(REGISTERALL, "1")]
			[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, REGCLASSOBJ, AFTERSEARCH, "COleTemplateServer::RegisterAll();")]
		[!else]
			[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "AfxEnableControlContainer();", AFXENABLECONTROLCONTAINER)]
			[!if=(AFXENABLECONTROLCONTAINER, "0")]
				[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, REGCLASSOBJ, BEGIN)]
			[!else]
				[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, REGCLASSOBJ, AFTERSEARCH, "AfxEnableControlContainer();")]
			[!endif]
		[!endif]

		[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)", CMDINFO)]
		[!if=(CMDINFO, "0")]
			[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "ParseCommandLine(cmdInfo);", PARSECOMMANDINFO)]
			[!if=(PARSECOMMANDINFO, "1")]
				[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, IFOLE, AFTERSEARCH, "ParseCommandLine(cmdInfo);")]
			[!endif]
		[!endif]

		[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "m_server.UpdateRegistry(OAT_INPLACE_SERVER);", UPDATEREGISTRY)]
		[!if=(UPDATEREGISTRY, "1")]
			[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, REGSVR, AFTERSEARCH, "m_server.UpdateRegistry(OAT_INPLACE_SERVER);")]
		[!else]
			[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "ParseCommandLine(cmdInfo);", PARSECOMMANDINFO)]
			[!if=(PARSECOMMANDINFO, "1")]
				[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, REGSVR, AFTERSEARCH, "ParseCommandLine(cmdInfo);")]
			[!endif]
		[!endif]

	[!endif]

[!else] 
	[!AddStringToSymbol(projectheadertemplate, GalleryPath, "aatldll.h")]
	[!AddStringToSymbol(projectcpptemplate, GalleryPath, "aatldll.cpp")]

	[!if=(MFCCTL, "1")]
		[!comment (// MFC ActiveX Control)]
		[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertIntoInitInstance, AFTERSEARCH, "COleControlModule::InitInstance")]
		[!AddToMemberFunction(CWinApp, "int ExitInstance()", projectcpptemplate, InsertIntoExitInstance, BEFORESEARCH, "COleControlModule::ExitInstance()")]
		[!AddToMemberFunction(NULLSTR, "STDAPI DllRegisterServer(void)", projectcpptemplate, InsertInDllRegisterServer, BEFORESEARCH, "return NOERROR")]
		[!AddToMemberFunction(NULLSTR, "STDAPI DllUnregisterServer()", projectcpptemplate, InsertInDllUnregisterServer, BEFORESEARCH, "return NOERROR")]
		[!AddMemberFunction(CWinApp, "InitATL", "BOOL", "", "ACCESS_PRIVATE", projectcpptemplate, 0, INITATL, BEFORESEARCH)]
	[!else]
		[!if=(MFCCTL, "0")]
		[!ExistsInMemberFunction(CWinApp, "BOOL InitInstance()", "COleObjectFactory::RegisterAll();", MFCOLE)]
		[!endif]

		[!if=(MFCOLE, "1")]
			[!comment (// MFC Regular DLL with Automation)]
			[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertIntoInitInstance, AFTERSEARCH, "COleObjectFactory::RegisterAll();")]

			[!ExistsMemberFunction(CWinApp, "int ExitInstance()", ExitInstance)]

			[!if=(ExitInstance, "1")]
				[!AddToMemberFunction(CWinApp, "int ExitInstance()", projectcpptemplate, InsertIntoExitInstance, BEFORESEARCH, "CWinApp::ExitInstance", )]
			[!else]
				[!AddMemberFunction(CWinApp, "ExitInstance", "virtual int", "", "ACCESS_PUBLIC", projectcpptemplate, 1, AddExitInstance)]
			[!endif]
			[!RemoveSymbol("ExitInstance")]


			[!AddToMemberFunction(NULLSTR, "STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)", projectcpptemplate, InsertInDllGetClassObject, BEFORESEARCH, "AfxDllGetClassObject")]
			[!AddToMemberFunction(NULLSTR, "STDAPI DllCanUnloadNow()", projectcpptemplate, InsertInDllCanUnloadNow, BEFORESEARCH, "AfxDllCanUnloadNow()")]
			[!AddToMemberFunction(NULLSTR, "STDAPI DllRegisterServer()", projectcpptemplate, InsertInDllRegisterServer, AFTERSEARCH, "COleObjectFactory::UpdateRegistryAll()")]
			[!AddMemberFunction(CWinApp, "InitATL", "BOOL", "", "ACCESS_PRIVATE", projectcpptemplate, 0, INITATL, BEFORESEARCH)]
		[!else]
			[!ExistsMemberFunction(CWinApp, "BOOL InitInstance()", InitInstance)]

			[!if=(InitInstance, "1")]
				[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", projectcpptemplate, InsertIntoInitInstance, BEFORESEARCH, "CWinApp::InitInstance", )]
			[!else]
				[!AddMemberFunction(CWinApp, "InitInstance", "virtual BOOL", "", "ACCESS_PUBLIC", projectcpptemplate, 1, AddInitInstance)]
			[!endif]
			[!RemoveSymbol("InitInstance")]

			[!ExistsMemberFunction(CWinApp, "int ExitInstance()", ExitInstance)]

			[!if=(ExitInstance, "1")]
				[!AddToMemberFunction(CWinApp, "int ExitInstance()", projectcpptemplate, InsertIntoExitInstance, BEFORESEARCH, "CWinApp::ExitInstance", )]
			[!else]
				[!AddMemberFunction(CWinApp, "ExitInstance", "virtual int", "", "ACCESS_PUBLIC", projectcpptemplate, 1, AddExitInstance)]
			[!endif]
			[!RemoveSymbol("ExitInstance")]

			[!AddMemberFunction(CWinApp, "InitATL", "BOOL", "", "ACCESS_PRIVATE", projectcpptemplate, 0, INITATL, BEFORESEARCH)]
		[!endif]
	[!endif]
[!endif]

[!set(InsertAfterApp, "1")]

[!target(ProjectNameCPP)]
	[!include(projectcpptemplate)]
[!target()]

[!RemoveSymbol(InsertAfterApp)]

[!Commit()]
[!IDLSettingsForATL()]