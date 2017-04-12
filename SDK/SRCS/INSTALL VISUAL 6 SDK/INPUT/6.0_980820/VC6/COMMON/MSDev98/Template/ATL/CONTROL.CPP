[!if=(FileExists, "FALSE")]
// [!CPPName] : Implementation of [!ClassName]
[!crlf]
#include "stdafx.h"
#include "[!ProjectName].h"
#include "[!HeaderName]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddStringToSymbol(ProjectName.h, ProjectName, ".h")]
[!AddIncludeFile(TargetFile, ProjectName.h)]
[!AddIncludeFile(TargetFile, HeaderName)]
[!endif]

[!if=(SubclassWindow, "SysListView32")]#pragma comment(lib, "comctl32.lib")[!endif]
[!if=(SubclassWindow, "SysTreeView32")]#pragma comment(lib, "comctl32.lib")[!endif]
[!if=(SubclassWindow, "SysAnimate32")]#pragma comment(lib, "comctl32.lib")[!endif]
[!if=(SubclassWindow, "SysHeader32")]#pragma comment(lib, "comctl32.lib")[!endif]
[!if=(SubclassWindow, "SysTabControl32")]#pragma comment(lib, "comctl32.lib")[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]
[!crlf]
