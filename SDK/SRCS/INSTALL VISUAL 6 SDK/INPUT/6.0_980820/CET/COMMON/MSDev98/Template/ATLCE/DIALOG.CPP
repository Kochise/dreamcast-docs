[!if=(FileExists, "FALSE")]
// [!CPPName] : Implementation of [!ClassName]
#include "stdafx.h"
#include "[!HeaderName]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddIncludeFile(TargetFile, HeaderName)]
[!endif]
[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]
