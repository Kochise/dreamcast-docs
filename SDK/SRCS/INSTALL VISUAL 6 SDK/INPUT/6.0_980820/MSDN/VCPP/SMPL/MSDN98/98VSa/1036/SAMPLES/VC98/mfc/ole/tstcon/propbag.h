class CPropertyBagItem :
   public CObject
{
   DECLARE_DYNAMIC( CPropertyBagItem );

public:
   CPropertyBagItem( LPCOLESTR pszName, VARIANT* pvarValue );

public:
   CString m_strName;
   COleVariant m_varValue;
};

typedef CTypedPtrList< CObList, CPropertyBagItem* > CPropertyBagItemList;

class CPropertyBag :
   public IPropertyBag
{
public:
   CPropertyBag();
   ~CPropertyBag();

   POSITION GetFirstItemPosition() const;
   CPropertyBagItem* GetNextItem( POSITION& posItem ) const;

// IUnknown
public:
   STDMETHOD_( ULONG, AddRef )();
   STDMETHOD_( ULONG, Release )();
   STDMETHOD( QueryInterface )( REFIID iid, void** ppInterface );

// IPropertyBag
public:
   STDMETHOD( Read )( LPCOLESTR pszPropName, VARIANT* pvarValue,
	  IErrorLog* pErrorLog );
   STDMETHOD( Write )( LPCOLESTR pszPropName, VARIANT* pvarValue );

protected:
   ULONG m_nRefCount;
   CPropertyBagItemList m_lpItems;
};
