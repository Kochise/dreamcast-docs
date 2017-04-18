HRESULT CreateObject(LPOLESTR pszProgID, IDispatch FAR* FAR* ppdisp);
HRESULT 
Invoke(LPDISPATCH pdisp, 
    WORD wFlags,
    LPVARIANT pvRet,
    EXCEPINFO FAR* pexcepinfo,
    UINT FAR* pnArgErr, 
    LPOLESTR pszName,
    LPCTSTR pszFmt, 
    ...);
