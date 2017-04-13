class CTestContainer98Doc;
class CScriptManager;

class CScriptManager :
   public CObject
{
   DECLARE_DYNAMIC( CScriptManager );

public:
   CScriptManager( CTestContainer98Doc* pDoc );
   ~CScriptManager();

   HRESULT AddNamedItem( LPCTSTR pszItemName, IDispatch* pDispatch );
   HRESULT AddNamedItems( IActiveScript* pScript );
   CScript* FindMacro( LPCTSTR pszMacroName );
   POSITION GetFirstScriptPosition() const;
   HRESULT GetItemDispatch( LPCTSTR pszItemName, IUnknown** ppDispatch );
   HRESULT GetItemTypeInfo( LPCTSTR pszItemName, ITypeInfo** ppTypeInfo );
   CScript* GetNextScript( POSITION& posScript );
   int GetNumScripts() const;
   HRESULT LoadScript( LPCTSTR pszFileName, LPCTSTR pszScriptName,
	  CScript** ppScript = NULL );

protected:
   CTestContainer98Doc* m_pDoc;
   CTypedPtrList< CObList, CScript* > m_lpScripts;
   CTypedPtrMap< CMapStringToPtr, CString, IDispatch* > m_mapNamedItems;
};
