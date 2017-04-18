// [!HeaderName] : Declaration of the [!ClassName] class
[!crlf]
[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!endif]
[!crlf]
class [!Accessor]
{
public:
[!DTLVariables]
[!crlf]
[!if=(DTLProcedure, "TRUE")]
BEGIN_PARAM_MAP([!Accessor])
[!DTLParameterAccessor]
END_PARAM_MAP()
[!crlf]
[!endif]
[!if=(DTLColumnMap, "TRUE")]
BEGIN_COLUMN_MAP([!Accessor])
[!DTLAccessor]
END_COLUMN_MAP()
[!crlf]
[!endif]
[!if=(DTLType, "Command")]
DEFINE_COMMAND([!Accessor], _T("[!DTLCommand]"))
[!endif]
[!crlf]
	// You may wish to call this function if you are inserting a record and wish to
	// initialize all the fields, if you are not going to explicitly set all of them.
	void ClearRecord()
	{
		memset(this, 0, sizeof(*this));
	}
};
[!crlf]
[!if=(DTLType, "Command")]
class [!ClassName] : public CCommand<CAccessor<[!Accessor]> >
[!else]
class [!ClassName] : public CTable<CAccessor<[!Accessor]> >
[!endif]
{
public:
	HRESULT Open()
	{
		HRESULT		hr;
[!crlf]
		hr = OpenDataSource();
		if (FAILED(hr))
			return hr;
[!crlf]
		return OpenRowset();
	}
	HRESULT OpenDataSource()
	{
		HRESULT		hr;
		CDataSource db;
		CDBPropSet	dbinit(DBPROPSET_DBINIT);
[!crlf]
[!DTLOpen]
[!if!=(DTLService,"")]
[!crlf]
		// The provider does not support updatability natively, 
		// but does support SQL. The OLE DB service components 
		// will be invoked to provide updatability via SQL.
[!endif]
		hr = db.Open[!DTLService](_T("[!DTLProgID]"), &dbinit);
		if (FAILED(hr))
			return hr;
[!crlf]
		return m_session.Open(db);
	}
	HRESULT OpenRowset()
	{
[!if!=(DTLUpdate, "")]
		// Set properties for open
		CDBPropSet	propset(DBPROPSET_ROWSET);
		propset.AddProperty(DBPROP_IRowsetChange, true);
		propset.AddProperty(DBPROP_UPDATABILITY, [!DTLUpdate]);
[!crlf]
[!endif]
[!if=(DTLNoService, "TRUE")]
		// The provider is read only so the property change code has
		// not been generated.
[!endif]
[!if=(DTLType, "Command")]
[!if!=(DTLUpdate,"")]
		return CCommand<CAccessor<[!Accessor]> >::Open(m_session, NULL, &propset);
[!else]
		return CCommand<CAccessor<[!Accessor]> >::Open(m_session);
[!endif]
[!else]
[!if!=(DTLUpdate,"")]
		return CTable<CAccessor<[!Accessor]> >::Open(m_session, _T("[!DTLCommand]"), &propset);
[!else]
		return CTable<CAccessor<[!Accessor]> >::Open(m_session, _T("[!DTLCommand]"));
[!endif]
[!endif]
	}
	CSession	m_session;
};
[!crlf]
[!if=(FileExists, "FALSE")]
#endif // __[!UpperShortName]_H_
[!endif]
