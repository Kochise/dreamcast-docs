/*
 * KOALA.CPP
 * Koala Object with Custom Marshaling, Chapter 6
 *
 * Implementation of the CKoala object with a custom interface
 * to demonstrate local/remote transparency.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "koala.h"


/*
 * ObjectWndProc
 *
 * Purpose:
 *  Standard window class procedure for each object.
 */

LRESULT APIENTRY ObjectWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCKoala     pKoala;

    pKoala=(PCKoala)GetWindowLong(hWnd, OBJECTWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pKoala=(PCKoala)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, OBJECTWL_STRUCTURE, (LONG)pKoala);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_COMMAND:
            //Dispatch the call to the right object
            return pKoala->HandleCall(LOWORD(wParam), lParam);

        default:
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));
        }

    return 0L;
    }





/*
 * CKoala::CKoala
 * CKoala::~CKoala
 *
 * Parameters (Constructor):
 *  pfnDestroy      PFNDESTROYED to call when an object
 *                  is destroyed.
 */

CKoala::CKoala(PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;
    m_pfnDestroy=pfnDestroy;

    m_fJustAte=FALSE;
    m_cSleepAfterEat=0;
    return;
    }


CKoala::~CKoala(void)
    {
    if (NULL!=m_hWnd)
        DestroyWindow(m_hWnd);

    return;
    }



/*
 * CKoala::Init
 *
 * Purpose:
 *  Performs any intiailization of a CKoala that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * Parameters:
 *  hInst           HINSTANCE of the application.
 *  hWndParent      HWND in which to create our window
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CKoala::Init(HINSTANCE hInst, HWND hWndParent)
    {
    //Create our window that receives marshaling calls
    m_hWnd=CreateWindow(TEXT("KoalaObject"), TEXT("KoalaObject")
        , WS_CHILD, 35, 35, 35, 25, hWndParent, NULL
        , hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    return TRUE;
    }





/*
 * CKoala::HandleCall
 *
 * Purpose:
 *  Handles messages sent via custom marshaling from the client
 *  side proxy.
 *
 * Parameters:
 *  iMsg            UINT identifying the call made.
 *  lParam          LPARAM with extra information.
 *
 * Return Value:
 *  DWORD           Value to return to the proxy which it uses
 *                  in whatever way it must to return a value to
 *                  the client.
 */

DWORD CKoala::HandleCall(UINT iMsg, LPARAM lParam)
    {
    DWORD       dw;
    short       iRet=0;

    /*
     * You'll notice that all the important server-side
     * implementation of the object exists here instead of
     * separate interface implementations.  Everything
     * else is contained in the client-side proxy, who knows
     * when there's no point at all in calling a function
     * on the server side (such as with some of the IKoala
     * functions that don't do anything.
     */

    switch (iMsg)
        {
        case MSG_RELEASE:          //Last IUnknown::Release
            /*
             * There is only one reference count from
             * IClassFactory::CreateInstance, which the proxy
             * will own.  The proxy sends this message when
             * it detects the last Release from the client.
             * Otherwise it doesn't forward AddRef/Release calls.
             */
            Release();
            break;

        case MSG_EAT:
            m_fJustAte=TRUE;
            break;

        case MSG_SLEEP:            //IAnimal::Sleep
            //Client's in-parameter in LOWORD(lParam)
            iRet=LOWORD(lParam)+m_cSleepAfterEat;
            m_fJustAte=FALSE;     //Probably want to eat again
            break;

        case MSG_PROCREATE:        //IAnimal::Procreate
            dw=GetTickCount()/100;

            iRet=((dw/10)*10==dw) ? 1 : 0;
            break;

        case MSG_SLEEPAFTEREATING: //IKoala::SleepAfterEating
            m_cSleepAfterEat=LOWORD(lParam);
            break;

        default:
            break;
        }

    return iRet;
    }





/*
 * CKoala::QueryInterface
 * CKoala::AddRef
 * CKoala::Release
 *
 * Purpose:
 *  IUnknown members for CKoala object.
 */

STDMETHODIMP CKoala::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IMarshal==riid
        || IID_IAnimal==riid || IID_IKoala==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CKoala::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CKoala::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }





/*
 * CKoala::GetUnmarshalClass
 *
 * Purpose:
 *  Determines the class of object to be used to create an
 *  uninitalized proxy in the unmarshaling process.
 *
 * Parameters:
 *  riid            REFIID of the interface to be marshaled.
 *  pv              LPVOID to the interface to be marshaled.
 *  dwCtx           DWORD specifying the relation of the processes
 *                  between which the marshaling is occuring, from the
 *                  MSHCTX enumeration.
 *  pvCtx           LPVOID Reserved for future MSHCTX values.
 *  dwFlags         DWORD specifying why marshaling is taking place.
 *  pClsID          LPCLSID in which to store the proxy CLSID.
 */

STDMETHODIMP CKoala::GetUnmarshalClass(REFIID riid
    , LPVOID pv, DWORD dwCtx, LPVOID pvCtx, DWORD dwFlags
    , LPCLSID pClsID)
    {
   #ifdef WIN32
    /*
     * If the context is on a different machine we cannot use
     * our custom marshaling based on SendMessage.
     */
    if (dwCtx & MSHCTX_DIFFERENTMACHINE)
        return ResultFromScode(E_FAIL);
   #endif

    //Same proxy for all interfaces.
    *pClsID=CLSID_KoalaProxy;
    return NOERROR;
    }




/*
 * CKoala::GetMarshalSizeMax
 *
 * Purpose:
 *  Returns the upper memory bound needed to write data into a stream
 *  for IMarshal::MarshalInterface.
 *
 * Parameters:
 *  riid            REFIID of the interface to be marshaled.
 *  pv              LPVOID of the interface to be marshaled.
 *  dwDestCtx       DWORD with the destination context from MSHCTX.
 *  pvDestCtx       LPVOID reserved for future MSHCTX flags.
 *  dwFlags         DWORD specifying why marshaling is taking place.
 *  pdwSize         LPDWORD in which the size is returned.
 */

STDMETHODIMP CKoala::GetMarshalSizeMax(REFIID riid, LPVOID pv
    , DWORD dwDestCtx, LPVOID pvDestCtx, DWORD dwFlags
    , LPDWORD pdwSize)
    {
   #ifdef WIN32
    if (dwDestCtx & MSHCTX_DIFFERENTMACHINE)
        return ResultFromScode(E_FAIL);
   #endif

    *pdwSize=sizeof(KOALAMARSHAL);
    return NOERROR;
    }





/*
 * CKoala::MarshalInterface
 *
 * Purpose:
 *  Stores a marshaling packet in a stream for use by a client-side
 *  proxy.
 *
 * Parameters:
 *  pStm            LPSTREAM into which to marshal the interface.
 *  riid            REFIID of the interface to be marshaled.
 *  pv              LPVOID of the interface to be marshaled.
 *  dwDestCtx       DWORD with the destination context from MSHCTX.
 *  pvDestCtx       LPVOID reserved for future MSHCTX flags.
 *  dwFlags         DWORD specifying why marshaling is taking place.
 */

STDMETHODIMP CKoala::MarshalInterface(LPSTREAM pstm
    , REFIID riid, LPVOID pv, DWORD dwDestCtx, LPVOID pvDestCtx
    , DWORD dwFlags)
    {
    KOALAMARSHAL        km;

   #ifdef WIN32
    if (dwDestCtx & MSHCTX_DIFFERENTMACHINE)
        return ResultFromScode(E_FAIL);
   #endif

    //Proxy only needs to know where to send messages
    km.hWnd=m_hWnd;

    //This is for the client who will call Release when needed
    AddRef();

    //Write the marshaling packet to the stream
    return pstm->Write((void *)&km, sizeof(KOALAMARSHAL), NULL);
    }





/*
 * CKoala::UnmarshalInterface
 *
 * Purpose:
 *  Initializes a newly created proxy the marshaling packet in
 *  the stream created in the server-side implementation of
 *  MarshalInterface.  This is the primary member of this interface
 *  used on the client side proxy.
 *
 * Parameters:
 *  pStm            LPSTREAM to the stream containing marshal
 *                  data.
 *  riid            REFIID of the interface to be marshaled.
 *  pv              LPVOID of the interface to be marshaled.
 */

STDMETHODIMP CKoala::UnmarshalInterface(LPSTREAM pstm
    , REFIID riid, LPVOID *pv)
    {
    //No need to implement on server side
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CKoala::ReleaseMarshalData
 *
 * Purpose:
 *  Destroy a marshaled data packet, client-side only.
 *
 * Parameters:
 *  pStm            LPSTREAM containing the data to release.
 */

STDMETHODIMP CKoala::ReleaseMarshalData(LPSTREAM pstm)
    {
    //Client-side function
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CKoala::Disconnect
 *
 * Purpose:
 *  Instructs an object with custom marshaling that it's being
 *  disconnected.
 *
 * Parameters:
 *  dwReserved      DWORD reserved.
 */

STDMETHODIMP CKoala::DisconnectObject(DWORD dwReserved)
    {
    /*
     * This is generated from within CoDisconnectObject, which
     * our server doesn't call itself.  This would give the object
     * a chance to close its connection and cleanup before going
     * away since the proxy will no longer be calling it.
     * This should also be used to block any additional calls
     * made after this point.
     */

    return NOERROR;
    }
