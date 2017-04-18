[!if=(FileExists, "FALSE")]
// Implementation of the [!Command]

#include "stdafx.h"
#include "[!ProjectName].h"
#include "[!RowsetFile]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddStringToSymbol(ProjectName.h, ProjectName, ".h")]
[!AddIncludeFile(TargetFile, ProjectName.h)]
[!AddIncludeFile(TargetFile, RowsetFile)]
[!endif]

/////////////////////////////////////////////////////////////////////////////
// [!Command]

HRESULT [!Command]::Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams, 
								 LONG * pcRowsAffected, IUnknown ** ppRowset)
{
	[!Rowset]* pRowset;
	return CreateRowset(pUnkOuter, riid, pParams, pcRowsAffected, ppRowset, pRowset);
}

