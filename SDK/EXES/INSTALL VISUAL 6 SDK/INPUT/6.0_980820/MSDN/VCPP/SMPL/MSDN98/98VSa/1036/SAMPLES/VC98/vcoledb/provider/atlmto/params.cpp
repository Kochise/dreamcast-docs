#include "stdafx.h"
#include "params.h"


CByValParameter::~CByValParameter()
{
	delete [] m_szParameter;
}

BOOL CByValParameter::FToVariant(VARIANT& varDest)
{
	VARIANT var;
	VARIANT varTempDest;

	VariantInit(&varTempDest);
	VariantInit(&var);

	var.vt = VT_BSTR;

	CComBSTR  bstr(m_szParameter);

	var.bstrVal = bstr;

	if (FAILED(VariantChangeType(&varTempDest, &var,
			   VARIANT_NOVALUEPROP, varDest.vt)))
	{
		ATLTRACE("Failed to coerce Bstr to Param\n");
		SysFreeString(var.bstrVal);
		return FALSE;
	}

	VariantCopy(&varDest, &varTempDest);

	return TRUE;
}
