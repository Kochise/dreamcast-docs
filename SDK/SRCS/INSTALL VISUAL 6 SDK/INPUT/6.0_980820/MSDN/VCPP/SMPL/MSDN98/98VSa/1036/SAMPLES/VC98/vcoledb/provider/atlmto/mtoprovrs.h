// MtoProvRS.h : Declaration of the CMtoProvRowset
#ifndef __CMtoProvRowset_H_
#define __CMtoProvRowset_H_

#include "resource.h"       // main symbols
#include "parser.h"
#include "atlmto.h"
#include "params.h"

class CMtoProvRowset;

class CRemoteArray
{
public:
	CRemoteArray()
	{
		RemoveAll();
	}
	void RemoveAll()
	{
		m_cbElemSize = 0;
		m_nSize = 0;
		m_bstrData.Empty();
	}
	void SetBstrResultSet(int cRows,  BSTR bstrData)
	{
		m_bstrData.Empty();
		m_nSize = cRows;
		m_bstrData.Attach(bstrData);
	}
	int GetSize() const
	{
		return m_nSize;
	}
	BYTE& operator[] (int nIndex) const
	{
		ATLASSERT(nIndex >= 0 && nIndex < m_nSize);
		ATLASSERT(m_bstrData != NULL);
		return  *((BYTE*)(m_bstrData.m_str) + (nIndex * m_cbElemSize));
	}

	int      m_cbElemSize;
	int      m_nSize;
	CComBSTR m_bstrData;
};

class CRemoteRecord
{
public:
	template <class T>
	static ATLCOLUMNINFO* GetColumnInfo(T* pT, ULONG* pcCols)
	{
		CComQIPtr<ICommand> spCommand = pT->GetUnknown();
		if (spCommand == NULL)
		{
			if (pcCols != NULL)
				*pcCols = pT->m_rgColInfo.GetSize();
			return pT->m_rgColInfo.m_aT;
		}
		CComPtr<IRowset> pRowset;
		if (pT->m_rgColInfo.m_aT == NULL)
		{
			LONG cRows;
			HRESULT hr = spCommand->Execute(NULL, IID_IRowset, NULL, &cRows, (IUnknown**)&pRowset);
		}
		if (pcCols != NULL)
			*pcCols = pT->m_rgColInfo.GetSize();
		return pT->m_rgColInfo.m_aT;
	}
};

// CMtoProvCommand
class ATL_NO_VTABLE CMtoProvCommand :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IAccessorImpl<CMtoProvCommand>,
	public ICommandTextImpl<CMtoProvCommand>,
	public ICommandPropertiesImpl<CMtoProvCommand>,
	public IObjectWithSiteImpl<CMtoProvCommand>,
	public IConvertTypeImpl<CMtoProvCommand>,
	public IColumnsInfoImpl<CMtoProvCommand>,
	public ICommandPrepare
{
public:

BEGIN_COM_MAP(CMtoProvCommand)
	COM_INTERFACE_ENTRY(ICommand)
	COM_INTERFACE_ENTRY(ICommandPrepare)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IAccessor)
	COM_INTERFACE_ENTRY(ICommandProperties)
	COM_INTERFACE_ENTRY2(ICommandText, ICommand)
	COM_INTERFACE_ENTRY(IColumnsInfo)
	COM_INTERFACE_ENTRY(IConvertType)
END_COM_MAP()

public:

	CMtoProvCommand() : m_Parser(this)
	{
		m_bIsPrepared = FALSE;
		m_pFuncDesc = NULL;
	}

	~CMtoProvCommand()
	{
		for (int i = 0; i < m_rgParams.GetSize(); i++)
			delete m_rgParams[i];
	}
	STDMETHOD(Prepare)(ULONG /*cRunsExpected*/)
	{
		ATLTRACE("ICommandPrepare::Unprepare\n");
		USES_CONVERSION;

		if (m_bNoCommand)
			return DB_E_NOCOMMAND;

		if (!FAquireDefaultDispatch())
			return PostError(E_FAIL);

		if (!m_Parser.FParseSQLCall(OLE2CT(m_strCommandText)))
			return PostError(DB_E_ERRORSINCOMMAND);

		OLECHAR* szMethod = T2OLE((LPTSTR)m_Parser.GetMethod());

		if (!FAquireDispatchId(szMethod))
		{
			ATLTRACE("FAquireDispatchId Failed!\n");
			return PostError(E_FAIL);
		}

		if (!FAquireDefaultTypeInfo())
			return PostError(E_FAIL);

		if (!FAquireFuncDesc(szMethod))
		{
			ATLTRACE("FAquireFuncDesc failed for Method %s\n", m_Parser.GetMethod());
			return PostError(E_FAIL);
		}

		int cParamsToAlloc = (m_pIData != NULL) ? m_Parser.CParamsWORetval() + 1 :
												 m_Parser.CParamsWORetval();

		m_dispparams.rgvarg = new VARIANTARG[cParamsToAlloc];

		for (int iVar = 0; iVar < cParamsToAlloc; iVar++)
			VariantInit(&m_dispparams.rgvarg[iVar]);

		m_dispparams.cArgs = cParamsToAlloc;
		m_dispparams.cNamedArgs = 0;
		m_bIsPrepared = TRUE;
		return S_OK;
	}
	STDMETHOD(Unprepare)()
	{
		ATLTRACE("ICommandPrepare::Unprepare\n");
		// nothing for now
		m_bIsPrepared = FALSE;
		return S_OK;
	}
	STDMETHOD(SetCommandText)(REFGUID /*rguidDialect*/,LPCOLESTR pwszCommand)
	{
		ATLTRACE("ICommandTextImpl::SetCommandText\n");
		Lock();
		m_strCommandText = pwszCommand;
		Unlock();
		m_bNoCommand = (pwszCommand == NULL || lstrcmpiW(m_strCommandText, OLESTR("")) == 0);
		return S_OK;
	}
	HRESULT PostError(HRESULT hrToPost)
	{
		//lame for now
		return hrToPost;
	}
	int CParamsWithHidden()
	{
		ATLASSERT(m_pDisp != NULL);

		return (m_pIData != NULL) ? m_Parser.CBindableParameters() + 1:
									 m_Parser.CBindableParameters();
	}


	BSTR BSTRCrackCookieData(BSTR bstrCookie, CMtoProvRowset* pRowset);


	HRESULT FinalConstruct()
	{
		m_bNoCommand = TRUE;
		HRESULT hr = CConvertHelper::FinalConstruct();
		if (FAILED (hr))
			return hr;
		hr = IAccessorImpl<CMtoProvCommand>::FinalConstruct();
		if (FAILED(hr))
			return hr;
		return CUtlProps<CMtoProvCommand>::FInit();
	}
	void FinalRelease()
	{
		IAccessorImpl<CMtoProvCommand>::FinalRelease();
	}
	HRESULT WINAPI Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams,
						  LONG * pcRowsAffected, IUnknown ** ppRowset);
	static ATLCOLUMNINFO* GetColumnInfo(CMtoProvCommand* pv, ULONG* pcInfo)
	{
		return CRemoteRecord::GetColumnInfo(pv,pcInfo);
	}

	BOOL FAquireDefaultDispatch()
	{
		_ASSERTE(m_guidCoClass != GUID_NULL);
		_ASSERTE(m_guidLib != GUID_NULL);

		if (m_pDisp != NULL)
			return TRUE;

		if (FAILED(CoCreateInstance(m_guidCoClass, NULL, CLSCTX_INPROC_SERVER,
									IID_IDispatch, (void **) &m_pDisp)))
		{
			ATLTRACE("Failed to aquire default Dispatch\n");
			return FALSE;
		}

		_ASSERTE(m_pDisp != NULL);

		if (SUCCEEDED(m_pDisp->QueryInterface(IID_IMTOData, (void**)&m_pIData)))
			ATLTRACE("IMTOData found\n");
		else
			m_pIData = NULL; // Just making sure

		return TRUE;
	}

	BOOL FAquireDefaultTypeInfo()
	{
		if (m_pTInfo != NULL)
			return TRUE;

		CComPtr<ITypeLib> ptlib;

		if (FAILED(LoadRegTypeLib(m_guidLib, 1, 0, 0, &ptlib)))
		{
			ATLTRACE("Failed To load TypeLib\n");
			return FALSE;
		}

		if (FAILED(ptlib->GetTypeInfoOfGuid(m_guidInterface, &m_pTInfo)))
		{
			ATLTRACE("Failed to aquire ITypeInfo for CoClass\n");
			return FALSE;
		}
		return TRUE;
	}

	STDMETHOD(SetSite)(IUnknown* pSite)
	{
		HRESULT hr;
		USES_CONVERSION;

		hr = IObjectWithSiteImpl<CMtoProvCommand>::SetSite(pSite);

		if (FAILED(hr))
			return hr;

		CComPtr<IGetDataSource> pGetSrc;

		hr = pSite->QueryInterface(IID_IGetDataSource, (void**) &pGetSrc);
		if (SUCCEEDED(hr))
		{
			CComPtr<IDBProperties> pProps;
			hr = pGetSrc->GetDataSource(IID_IDBProperties, (IUnknown**)&pProps);
			if (SUCCEEDED(hr))
			{
				DBPROPID id = DBPROP_INIT_DATASOURCE;
				DBPROPIDSET idSet;
				DBPROPSET* pSet;
				ULONG cIdSets = 1;
				ULONG cSets;
				idSet.cPropertyIDs = 1;
				idSet.guidPropertySet = DBPROPSET_DBINIT;
				idSet.rgPropertyIDs = &id;
				hr = pProps->GetProperties(1, &idSet, &cSets, &pSet);
				if (FAILED(hr))
					return hr;
				_ASSERTE(pSet != NULL);
				_ASSERTE(pSet->cProperties == 1);
				_ASSERTE(pSet->rgProperties[0].dwPropertyID == DBPROP_INIT_DATASOURCE);
				_ASSERTE(pSet->rgProperties[0].vValue.vt == VT_BSTR);

				BSTR bstrDS = pSet->rgProperties[0].vValue.bstrVal;
				LPTSTR szDS = OLE2T(bstrDS);
				CRegKey rkDS;
				TCHAR szKeyToOpen[_MAX_PATH*2];
				lstrcpy(szKeyToOpen, _T("CLSID\\{E3CE8A61-8B11-11D1-9EBB-000000000000}\\DataSources\\"));
				lstrcat(szKeyToOpen, szDS);
				LONG lRes = rkDS.Open(HKEY_CLASSES_ROOT, szKeyToOpen, KEY_READ);
				if (lRes != ERROR_SUCCESS)
					return E_FAIL;

				TCHAR szValue[_MAX_PATH];
				DWORD cchValue = _MAX_PATH;
				if (rkDS.QueryValue(szValue, _T("CoClassGUID"), &cchValue) != ERROR_SUCCESS)
					return E_FAIL;
				hr = CLSIDFromString(T2OLE(szValue), &m_guidCoClass);
				if (FAILED(hr))
					return hr;
				if (rkDS.QueryValue(szValue, _T("LibGUID"), &cchValue) != ERROR_SUCCESS)
					return E_FAIL;
				hr = CLSIDFromString(T2OLE(szValue), &m_guidLib);
				if (FAILED(hr))
					return hr;
				if (rkDS.QueryValue(szValue, _T("InterfaceGUID"), &cchValue) != ERROR_SUCCESS)
					return E_FAIL;
				hr = CLSIDFromString(T2OLE(szValue), &m_guidInterface);
				if (FAILED(hr))
					return hr;
				if (!FAquireDefaultTypeInfo() || !FAquireDefaultDispatch())
				{
					ATLTRACE("Failed to get TI or DISPATCH/IData\n");
					return E_FAIL;
				}
			}
		}
		return hr;
	}

	BOOL FAquireDispatchId(OLECHAR* szTarget)
	{
		if FAILED(m_pDisp->GetIDsOfNames(IID_NULL, &szTarget, 1,
										 LOCALE_SYSTEM_DEFAULT, &m_dispid))
		{
			ATLTRACE("Failed to aquire DISPID for method %s\n", szTarget);
			PostError(E_FAIL);
			return FALSE;
		}
		return TRUE;
	}

	BOOL FAquireFuncDesc(OLECHAR* pszMethod)
	{
		MEMBERID    memid;
		BOOL        fDone = FALSE;

		if (FAILED(m_pTInfo->GetIDsOfNames(&pszMethod, 1, &memid)))
		{
			ATLTRACE("Failed to Get IDs of Names\n");
			return FALSE;
		}

		if (NULL != m_pFuncDesc)
			m_pTInfo->ReleaseFuncDesc(m_pFuncDesc);

		TYPEATTR* pAttr = NULL;

		if (FAILED(m_pTInfo->GetTypeAttr(&pAttr)))
		{
			ATLTRACE("Failed to get TypeAttr\n");
			return FALSE;
		}

		int iFunc = 0;

		if (pAttr->cFuncs <= iFunc)
		{
			ATLTRACE("No functions exist on this TypeInfo\n");
			m_pTInfo->ReleaseTypeAttr(pAttr);
			return FALSE;
		}

		while (!fDone) //Find the correct FuncDesc
		{

			if (FAILED(m_pTInfo->GetFuncDesc(iFunc, &m_pFuncDesc)))
			{
				ATLTRACE("Failed to aquire FuncDesc for iFunc = %i\n", iFunc);
				return FALSE;
			}

			if (!(fDone = m_pFuncDesc->memid == memid)) // Got It?
				m_pTInfo->ReleaseFuncDesc(m_pFuncDesc); // Release the allocated func desc

			iFunc++;
		}

		return TRUE;
	}


BEGIN_PROPSET_MAP(CMtoProvCommand)
	BEGIN_PROPERTY_SET(DBPROPSET_ROWSET)
		PROPERTY_INFO_ENTRY(IAccessor)
		PROPERTY_INFO_ENTRY(IColumnsInfo)
		PROPERTY_INFO_ENTRY(IColumnsRowset)
		PROPERTY_INFO_ENTRY(IConnectionPointContainer)
		PROPERTY_INFO_ENTRY(IConvertType)
		PROPERTY_INFO_ENTRY(IRowset, )
		PROPERTY_INFO_ENTRY(IRowsetChange)
		PROPERTY_INFO_ENTRY(IRowsetIdentity)
		PROPERTY_INFO_ENTRY(IRowsetInfo)
		PROPERTY_INFO_ENTRY(IRowsetLocate)
		PROPERTY_INFO_ENTRY(IRowsetResynch)
		PROPERTY_INFO_ENTRY(IRowsetScroll)
		PROPERTY_INFO_ENTRY(IRowsetUpdate)
		PROPERTY_INFO_ENTRY(ISupportErrorInfo)
		PROPERTY_INFO_ENTRY(ISequentialStream)
		PROPERTY_INFO_ENTRY(ABORTPRESERVE)
		PROPERTY_INFO_ENTRY(BLOCKINGSTORAGEOBJECTS)
		PROPERTY_INFO_ENTRY(BOOKMARKS)
		PROPERTY_INFO_ENTRY(BOOKMARKSKIPPED)
		PROPERTY_INFO_ENTRY(BOOKMARKTYPE)
		PROPERTY_INFO_ENTRY(CANFETCHBACKWARDS)
		PROPERTY_INFO_ENTRY(CANHOLDROWS)
		PROPERTY_INFO_ENTRY(CANSCROLLBACKWARDS)
		PROPERTY_INFO_ENTRY(CHANGEINSERTEDROWS)
		PROPERTY_INFO_ENTRY(COLUMNRESTRICT)
		PROPERTY_INFO_ENTRY(COMMANDTIMEOUT)
		PROPERTY_INFO_ENTRY(COMMITPRESERVE)
		PROPERTY_INFO_ENTRY(DELAYSTORAGEOBJECTS)
		PROPERTY_INFO_ENTRY(IMMOBILEROWS)
		PROPERTY_INFO_ENTRY(LITERALBOOKMARKS)
		PROPERTY_INFO_ENTRY(LITERALIDENTITY)
		PROPERTY_INFO_ENTRY(MAXOPENROWS)
		PROPERTY_INFO_ENTRY(MAXPENDINGROWS)
		PROPERTY_INFO_ENTRY(MAXROWS)
		PROPERTY_INFO_ENTRY(NOTIFICATIONPHASES)
		PROPERTY_INFO_ENTRY(NOTIFYCOLUMNSET)
		PROPERTY_INFO_ENTRY(NOTIFYROWDELETE)
		PROPERTY_INFO_ENTRY(NOTIFYROWFIRSTCHANGE)
		PROPERTY_INFO_ENTRY(NOTIFYROWINSERT)
		PROPERTY_INFO_ENTRY(NOTIFYROWRESYNCH)
		PROPERTY_INFO_ENTRY(NOTIFYROWSETRELEASE)
		PROPERTY_INFO_ENTRY(NOTIFYROWSETFETCHPOSITIONCHANGE)
		PROPERTY_INFO_ENTRY(NOTIFYROWUNDOCHANGE)
		PROPERTY_INFO_ENTRY(NOTIFYROWUNDODELETE)
		PROPERTY_INFO_ENTRY(NOTIFYROWUNDOINSERT)
		PROPERTY_INFO_ENTRY(NOTIFYROWUPDATE)
		PROPERTY_INFO_ENTRY(OTHERINSERT)
		PROPERTY_INFO_ENTRY(OTHERUPDATEDELETE)
		PROPERTY_INFO_ENTRY(OWNINSERT)
		PROPERTY_INFO_ENTRY(OWNUPDATEDELETE)
		PROPERTY_INFO_ENTRY(QUICKRESTART)
		PROPERTY_INFO_ENTRY(REENTRANTEVENTS)
		PROPERTY_INFO_ENTRY(REMOVEDELETED)
		PROPERTY_INFO_ENTRY(REPORTMULTIPLECHANGES)
		PROPERTY_INFO_ENTRY(RETURNPENDINGINSERTS)
		PROPERTY_INFO_ENTRY(ROWRESTRICT)
		PROPERTY_INFO_ENTRY(ROWTHREADMODEL)
		PROPERTY_INFO_ENTRY(SERVERCURSOR)
		PROPERTY_INFO_ENTRY(STRONGIDENTITY)
		PROPERTY_INFO_ENTRY(TRANSACTEDOBJECT)
		PROPERTY_INFO_ENTRY(UPDATABILITY)
	END_PROPERTY_SET(DBPROPSET_ROWSET)
END_PROPSET_MAP()

	GUID                    m_guidCoClass;
	GUID                    m_guidLib;
	GUID                    m_guidInterface;
	CComPtr<IDispatch>      m_pDisp;
	CComPtr<ITypeInfo>      m_pTInfo;
	CComPtr<IMTOData>       m_pIData;
	CParser                 m_Parser;
	DISPID                  m_dispid;
	DISPPARAMS              m_dispparams;
	FUNCDESC*               m_pFuncDesc;
	BOOL                    m_bNoCommand;
	BOOL                    m_bIsPrepared;


	CSimpleArray<ATLCOLUMNINFO>     m_rgColInfo;
	CSimpleValArray<CParameter*>    m_rgParams;
};

class CMtoProvRowset :
	public CRowsetImpl< CMtoProvRowset, CRemoteRecord, CMtoProvCommand, CRemoteArray>
{
public:
	HRESULT Execute(DBPARAMS * pParams, LONG* pcRowsAffected)
	{
		USES_CONVERSION;
		return S_OK;
	}
	CSimpleArray<ATLCOLUMNINFO>     m_rgColInfo;


};


#endif //__CMtoProvRowset_H_
