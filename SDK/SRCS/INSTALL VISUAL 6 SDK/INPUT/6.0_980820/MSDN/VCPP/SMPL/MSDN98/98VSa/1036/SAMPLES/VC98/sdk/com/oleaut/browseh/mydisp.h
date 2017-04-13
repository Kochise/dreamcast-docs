class FAR CMyDispatch : public IDispatch
{
public:
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(THIS);
    STDMETHOD_(ULONG, Release)(THIS);

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo);

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);
      
      CMyDispatch();
      virtual ~CMyDispatch();
      
    /* CMyDispatch methods */
    STDMETHOD(LoadTypeInfo)(REFCLSID clsid);
    STDMETHOD_(void, RaiseException)(int nID);
    STDMETHOD_(REFCLSID, GetInterfaceID)() PURE;
      
private:
    LPTYPEINFO m_ptinfo;         // Type information of interface.
    ULONG m_cRef;                // Reference count.
    EXCEPINFO m_excepinfo;       // Information to raise an exception on error.
    BOOL m_bRaiseException;      // Properties and methods use this to signal an exception to be raised.

#ifdef _DEBUG 
public:
    TCHAR m_szClassName[100]; 
#endif  
};  
