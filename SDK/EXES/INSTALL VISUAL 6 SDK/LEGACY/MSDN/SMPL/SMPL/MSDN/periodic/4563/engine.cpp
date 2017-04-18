DECLARE_INTERFACE_(_DAODBEngine, _DAO)
{
  STDMETHOD(get_Version)         (THIS_ BSTR FAR* pbstr) PURE;
  STDMETHOD(get_IniPath)         (THIS_ BSTR FAR* pbstr) PURE;
  STDMETHOD(put_IniPath)         (THIS_ BSTR path) PURE;
  STDMETHOD(put_DefaultUser)     (THIS_ BSTR user) PURE;
  STDMETHOD(put_DefaultPassword) (THIS_ BSTR pw) PURE;
  STDMETHOD(get_LoginTimeout)    (THIS_ short FAR* ps) PURE;
  STDMETHOD(put_LoginTimeout)    (THIS_ short Timeout) PURE;
  STDMETHOD(get_Workspaces)      (THIS_ DAOWorkspaces FAR* FAR* ppworks) PURE;
  STDMETHOD(get_Errors)          (THIS_ DAOErrors FAR* FAR* pperrs) PURE;
  STDMETHOD(CompactDatabase)     (THIS_ BSTR SrcName, BSTR DstName, 
     VARIANT DstConnect, VARIANT Options, VARIANT SrcConnect) PURE;
  STDMETHOD(CreateWorkspace)     (THIS_ BSTR Name, BSTR UserName, 
     BSTR Password, DAOWorkspace FAR* FAR* ppwrk) PURE;
  STDMETHOD(OpenDatabase)        (THIS_ BSTR Name, VARIANT Exclusive, 
     VARIANT ReadOnly, VARIANT Connect, DAODatabase FAR* FAR* ppdb) PURE;
  STDMETHOD(CreateDatabase)      (THIS_ BSTR Name, BSTR Connect, 
     VARIANT Option, DAODatabase FAR* FAR* ppdb) PURE;
};
