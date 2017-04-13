// Checking_Account.H : Declaration of the CChecking_Account class

#ifndef __CHECKING_ACCOUNT_H_
#define __CHECKING_ACCOUNT_H_


template <class T>
void Write(CVirtualBytes& stream, const T& value)
{
	// REVIEW: ChrisBe This is inefficient - use a function object
	BYTE* pType = (BYTE*) &value;
	for (int i=0; i<sizeof(T); i++)
		stream.Write(pType[i]);
}

class CChecking_AccountAccessor
{
public:
	char m_Account[14];
	short m_Owner_ID;
	double m_Balance;
	char m_Backup_Account[14];

BEGIN_COLUMN_MAP(CChecking_AccountAccessor)
	COLUMN_ENTRY_TYPE(1, DBTYPE_STR, m_Account)
	COLUMN_ENTRY_TYPE(2, DBTYPE_I2, m_Owner_ID)
	COLUMN_ENTRY_TYPE(3, DBTYPE_R8, m_Balance)
	COLUMN_ENTRY_TYPE(4, DBTYPE_STR, m_Backup_Account)
END_COLUMN_MAP()
};

class CChecking_Account : public CCommand< CAccessor<CChecking_AccountAccessor>, CArrayRowset<CChecking_AccountAccessor> >
{
public:
	HRESULT Open(double fAmount)
	{
		HRESULT     hr;

		if (m_session.m_spOpenRowset == NULL)
		{
			hr = OpenDataSource();
			if (FAILED(hr))
				return hr;
		}
		TCHAR szOpen[256];
		szOpen[0] = NULL;
		_stprintf(szOpen, _T("SELECT * FROM Checking_Account where Balance > %f"), fAmount);
		return OpenRowset(szOpen);
	}
	HRESULT WriteMetaData(CVirtualBytes& stream)
	{
		ULONG nCols;
		bool bAuto;
		_OutputColumnsClass::_GetBindEntries(&nCols, NULL, 0, NULL);

		DBBINDING* pBindings = (DBBINDING*)_alloca(sizeof(DBBINDING)* nCols);
		// Now get the bind entries
		HRESULT hr = _OutputColumnsClass::_GetBindEntries(&nCols, pBindings, 0, &bAuto);
		if (FAILED(hr))
			return hr;

		::Write(stream, nCols);
		::Write(stream, sizeof(CChecking_AccountAccessor));
		BYTE* pStart = 0;
		for (ULONG i=0; i<nCols; i++)
		{
			TCHAR szCol[256];

			szCol[0] = NULL;
			wsprintf(szCol, _T("Column%d"), i);
			int cBytes = lstrlen(szCol);
			::Write(stream, ++cBytes);
			for(int j=0; j<cBytes; j++)
				::Write(stream, szCol[j]);
			::Write(stream, pBindings[i]);
		}
		return S_OK;
	}
		HRESULT OpenDataSource()
	{
		HRESULT     hr;
		CDataSource db;
		CDBPropSet  dbinit(DBPROPSET_DBINIT);

		dbinit.AddProperty(DBPROP_INIT_DATASOURCE, "Accounts");
		dbinit.AddProperty(DBPROP_INIT_LCID, (long)1033);
		dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);
		dbinit.AddProperty(DBPROP_INIT_TIMEOUT, (long)0);
		hr = db.Open(_T("MSDASQL"), &dbinit);
		if (FAILED(hr))
			return hr;

		return m_session.Open(db);
	}
	HRESULT OpenRowset(LPCTSTR szCommand)
	{
		return CCommand< CAccessor<CChecking_AccountAccessor>, CArrayRowset<CChecking_AccountAccessor> >::Open(m_session, szCommand);
	}
	CSession    m_session;
};


#endif // __CHECKING_ACCOUNT_H_
