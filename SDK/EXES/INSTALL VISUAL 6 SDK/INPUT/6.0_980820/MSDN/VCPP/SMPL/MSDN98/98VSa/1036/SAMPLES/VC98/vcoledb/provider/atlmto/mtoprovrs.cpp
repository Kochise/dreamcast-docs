// Implementation of the CMtoProvCommand
#include "stdafx.h"
#include "MtoProvRS.h"
/////////////////////////////////////////////////////////////////////////////
// CMtoProvCommand

HRESULT CMtoProvCommand::Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams,
								 LONG * pcRowsAffected, IUnknown ** ppRowset)
{
	HRESULT hr;
	if (m_bNoCommand)
		return DB_E_NOCOMMAND;

	if (!m_bIsPrepared)
	{
		hr = Prepare(999);
		if (FAILED(hr))
			return hr;
	}

	CMtoProvRowset* pRowset;
	hr = CreateRowset(pUnkOuter, riid, pParams, pcRowsAffected, ppRowset, pRowset);
	if (FAILED(hr))
		return hr;

	if (!FAquireDefaultDispatch())
		return PostError(E_FAIL);

	if (m_pTInfo  == NULL || m_pFuncDesc == NULL)
		return PostError(E_FAIL);

	//Since we are here we have a cookie as one of the parameters
	ELEMDESC* pDesc;

	// Deep copy parameters

	for (int iParam = 0; iParam < m_rgParams.GetSize(); iParam++)
	{

		pDesc = &(m_pFuncDesc->lprgelemdescParam[iParam]);

		ATLASSERT(pDesc != NULL);

		if (VT_VOID == pDesc->tdesc.vt)
			continue;

		DWORD    iVarArg = CParamsWithHidden() - m_rgParams[iParam]->Index();
		VARIANT& varDest = m_dispparams.rgvarg[iVarArg];
		VARIANT  varTemp;

		VariantInit(&varTemp);

		varTemp.vt = pDesc->tdesc.vt;

		if (!m_rgParams[iParam]->FToVariant(varTemp))
		{
			ATLTRACE("Unable to convert Parameter!!\n");
			return PostError(E_FAIL);
		}

		VariantCopy(&varDest, &varTemp);

	}


	VARIANT         varResult;
	EXCEPINFO       eInfo;
	unsigned int    iArgError;
	BSTR            bstrCookie = NULL;

	VariantInit(&varResult);

	if (m_pIData != NULL)
	{
		m_dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
		m_dispparams.rgvarg[0].pbstrVal = &bstrCookie;
	}

	if (FAILED(hr = m_pDisp->Invoke(m_dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT,
							   DISPATCH_METHOD, &m_dispparams,
							   &varResult, &eInfo, &iArgError)))
	{
		ATLTRACE("Invoke failed on Dispatch\n");
		return PostError(E_FAIL);
	}

	// Put retvals
//    if (NULL != m_pRetVal)
//        ConvertVariantToC(varResult, m_pRetVal);

	if (m_pIData != NULL) //Crack the cookie
	{
		BSTR    bstrContext;
		BSTR    bstrRowset;

		ATLTRACE("Received cookie\n");

		pRowset->m_rgRowData.RemoveAll();

		if ((bstrContext=BSTRCrackCookieData(bstrCookie, pRowset)) == NULL)
		{
			ATLTRACE("Failed to crack Cookie\n");
			return PostError(E_FAIL);
		}
		int cMaxRow = 50000;

		if (FAILED(m_pIData->GetData(&cMaxRow, &bstrContext, &bstrRowset)))
		{
			ATLTRACE("Failed to get data off of IData\n");
			return PostError(E_FAIL);
		}

		pRowset->m_rgRowData.SetBstrResultSet(cMaxRow, bstrRowset);
		for (int iCol = 0; iCol < m_rgColInfo.GetSize(); iCol++)
			pRowset->m_rgColInfo.Add(m_rgColInfo[iCol]);

		// cMaxRows

	}

	// Handle other out params
	return hr;

}

template <class T> void CookieDataIterator(T& dest, BYTE* pData, unsigned int& iData)
{
	dest = *((T*)(pData + iData));
	iData += sizeof(T);
}

BSTR CMtoProvCommand::BSTRCrackCookieData(BSTR bstrCookie, CMtoProvRowset* pRowset)
{
	unsigned int    iCookie = 0;
	unsigned int    cCols;
	DWORD           cbData;
	int             cbName;
	DBBINDING       bindCur;


	BYTE*   pByte = (BYTE*)(bstrCookie);

	CookieDataIterator(cCols, pByte, iCookie);
	CookieDataIterator(cbData, pByte, iCookie);

	pRowset->m_rgRowData.m_cbElemSize = cbData;

	for (unsigned int iCol = 0; iCol < cCols; iCol++)
	{
		USES_CONVERSION;
		CookieDataIterator(cbName, pByte, iCookie);

		LPTSTR szName = (LPTSTR)_alloca((cbName + 1) * sizeof(TCHAR));
		lstrcpyn(szName, (LPTSTR)(pByte + iCookie), cbName);
		iCookie += cbName;
		CookieDataIterator(bindCur, pByte, iCookie);

		ATLCOLUMNINFO colInfo;
		memset(&colInfo, 0, sizeof(ATLCOLUMNINFO));
		colInfo.pwszName = ::SysAllocString(T2OLE(szName));
		colInfo.iOrdinal = bindCur.iOrdinal;
		colInfo.dwFlags = DBCOLUMNFLAGS_ISFIXEDLENGTH;
		colInfo.ulColumnSize = bindCur.cbMaxLen;
		colInfo.wType = bindCur.wType;
		colInfo.bPrecision = bindCur.bPrecision;
		colInfo.bScale = bindCur.bScale;
		colInfo.columnid.uName.pwszName = colInfo.pwszName;
		colInfo.cbOffset = bindCur.obValue;
		m_rgColInfo.Add(colInfo);

	}

	unsigned int cbCookie = SysStringLen(bstrCookie) * sizeof(OLECHAR);

	if (cbCookie <= iCookie)
	{
		ATLTRACE("Bad Cookie Data\n");
		return NULL;
	}

	unsigned int cbRemain = cbCookie - iCookie;

	return SysAllocStringByteLen((LPSTR)(pByte + iCookie), cbRemain);
}
