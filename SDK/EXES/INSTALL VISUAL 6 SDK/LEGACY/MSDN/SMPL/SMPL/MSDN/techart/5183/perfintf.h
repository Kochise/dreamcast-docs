//
// PerfIntf.h
//
    
    interface DECLSPEC_UUID("3DBD6FB0-FFA7-11d0-9F8C-400004491341")
    IPerfmonObject : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHelp( 
            /* [retval][out] */ BSTR __RPC_FAR *pHelp) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIndex( 
            /* [retval][out] */ long __RPC_FAR *pIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumCounters( 
            /* [retval][out] */ long __RPC_FAR *pNumCounters) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCounters( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pCounters) = 0;
        
    };

	interface DECLSPEC_UUID("3DBD6FB1-FFA7-11d0-9F8C-400004491341")
    IPerfmonCounter : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Collect( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHelp( 
            /* [retval][out] */ BSTR __RPC_FAR *pHelp) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIndex( 
            /* [retval][out] */ long __RPC_FAR *pIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDataType( 
            /* [retval][out] */ short __RPC_FAR *pDataType) = 0;
        
    };
