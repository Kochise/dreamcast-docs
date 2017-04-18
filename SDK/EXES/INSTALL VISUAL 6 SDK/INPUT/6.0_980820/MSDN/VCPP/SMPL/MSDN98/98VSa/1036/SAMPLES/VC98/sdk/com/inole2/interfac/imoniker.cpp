/*
 * IMONIKER.CPP
 *
 * Template IMoniker interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "imoniker.h"


/*
 * CImpIMoniker::CImpIMoniker
 * CImpIMoniker::~CImpIMoniker
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIMoniker::CImpIMoniker(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIMoniker::~CImpIMoniker(void)
    {
    return;
    }



/*
 * CImpIMoniker::QueryInterface
 * CImpIMoniker::AddRef
 * CImpIMoniker::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIMoniker.
 */

STDMETHODIMP CImpIMoniker::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIMoniker::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIMoniker::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }







/*
 * CImpIMoniker::GetClassID
 *
 * Purpose:
 *  Return the CLSID of the moniker.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store the CLSID.
 */

STDMETHODIMP CImpIMoniker::GetClassID(LPCLSID pClsID)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMoniker::IsDirty
 *
 * Purpose:
 *  Answers whether the state of the moniker itself is dirty.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         S_TRUE if the moniker is dirty, S_FALSE if not.
 *                  Possibly a failure code.
 */

STDMETHODIMP CImpIMoniker::IsDirty(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMoniker::Load
 *
 * Purpose:
 *  Initializes the moniker from the information in a stream.
 *
 * Parameters:
 *  pstm            LPSTREAM containing the moniker's information.
 */

STDMETHODIMP CImpIMoniker::Load(LPSTREAM pstm)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMoniker::Save
 *
 * Purpose:
 *  Instructs the moniker to save its state to a stream.
 *
 * Parameters:
 *  pstm            LPSTREAM in which to save the moniker.
 *  fClearDirty     BOOL indicating if the object is to clear its
 *                  dirty flag after the save.
 */

STDMETHODIMP CImpIMoniker::Save(LPSTREAM pstm, BOOL fClearDirty)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::GetSizeMax
 *
 * Purpose:
 *  Returns the size of a stream the moniker need to store its
 *  persistent state.
 *
 * Parameters:
 *  pcbSize         ULARGE_INTEGER * in which to store the size.
 */

STDMETHODIMP CImpIMoniker::GetSizeMax(ULARGE_INTEGER *pcbSize)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::BindToObject
 *
 * Purpose:
 *  Instructs a moniker to locate and load the object it refereces.
 *
 * Parameters:
 *  pBindCtx        LPBC to the bind context.
 *  pmkLeft         LPMONIKER to the "left" of this moniker.
 *  riid            REFIID of the interface desired on the object
 *  ppvObj          LPVOID * into which to store the bound object's
 *                  interface pointer.
 */

STDMETHODIMP CImpIMoniker::BindToObject(LPBC pBindCtx
    , LPMONIKER pmkLeft, REFIID riid, LPVOID *ppvObj)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::BindToStorage
 *
 * Purpose:
 *  Locates and returns an interface pointer to the storage of
 *  the object referenced by this moniker.
 *
 * Parameters:
 *  pBindCtx        LPBC to the bind context.
 *  pmkLeft         LPMONIKER to the "left" of this moniker.
 *  riid            REFIID of the interface desired on the object
 *  ppvObj          LPVOID * into which to store the bound object's
 *                  interface pointer.
 */

STDMETHODIMP CImpIMoniker::BindToStorage(LPBC pBindCtx
    , LPMONIKER pmkLeft, REFIID riid, LPVOID *ppvObj)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::Reduce
 *
 * Purpose:
 *  Returns a more or equally efficient moniker equivalent to
 *  this moniker.
 *
 * Parameters:
 *  pBindCtx        LPBC to the bind context.
 *  dwHowFar        DWORD indicating how far the reduction should go.
 *  ppmkLeft        LPMONIKER * (in-out) contains initial left moniker
 *                  on input and a new prefix on output (if necessary).
 *  ppmkReduced     LPMONIKER * into which to store the reduced moniker.
 */

STDMETHODIMP CImpIMoniker::Reduce(LPBC pBindCtx, DWORD dwHowFar
    , LPMONIKER *ppmkLeft, LPMONIKER *ppmkReduced)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::ComposeWith
 *
 * Purpose:
 *  Returns a new composite moniker composed with this moniker on
 *  the left and ppmkRight on the right.
 *
 * Parameters:
 *  pmkRight        LPMONIKER of the moniker to store on the right.
 *  fOnlyIfNotGen   BOOL that contrls what should be done if the
 *                  result is not a generic composite.
 *  ppmkComposite   LPMONIKER * in which to store the resulting
 *                  composite.
 */

STDMETHODIMP CImpIMoniker::ComposeWith(LPMONIKER pmkRight
    , BOOL fOnlyIfNotGen, LPMONIKER *ppmkComposite)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::Enum
 *
 * Purpose:
 *  Enumerates the monikers within this moniker if we are a
 *  composite.  Need not be implemented for simple monikers.
 *
 * Parameters:
 *  fForward        Specifies the direction of enumeration, TRUE
 *                  for forward, FALSE for backwards.
 *  ppEnum          LPENUMMONIKER * in which to store the
 *                  enumerator's IEnumMoniker interface.
 */

STDMETHODIMP CImpIMoniker::Enum(BOOL fForward, LPENUMMONIKER *ppEnum)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::IsEqual
 *
 * Purpose:
 *  Compares this moniker to another for equivalence.
 *
 * Parameters:
 *  pmk             LPMONKIER to the other moniker to compare.
 *
 * Return Value:
 *  HRESULT         S_OK or S_FALSE depending on the result of
 *                  the comparison.
 */

STDMETHODIMP CImpIMoniker::IsEqual(LPMONIKER pmk)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::Hash
 *
 * Purpose:
 *  Returns a 32-bit integer associated with this moniker that
 *  can be used in creating moniker tables.  This should only rely
 *  on the internal state of the moniker and not any memory
 *  addresses.
 *
 * Parameters:
 *  pdwHash         LPDWORD in which to store the hash number.
 */

STDMETHODIMP CImpIMoniker::Hash(LPDWORD pdwHash)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::IsRunning
 *
 * Purpose:
 *  Tests if the object associated with this moniker is already
 *  running.
 *
 * Parameters:
 *  pBindCtx        LPBINDCTX to the bind context in use.
 *  pmkLeft         LPMONIKER to the left.
 *  pmkNewlyRunning LPMONIKER most recently added to the running
 *                  object table (can be NULL).  If equivalent to
 *                  this moniker then the object is already running.
 *
 * Return Value:
 *  HRESULT         S_OK or S_FALSE (or an error code)
 */

STDMETHODIMP CImpIMoniker::IsRunning(LPBC pBindCtx
    , LPMONIKER pmkLeft, LPMONIKER pmkNewlyRunning)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::GetTimeOfLastChange
 *
 * Purpose:
 *  Reports the time that the object referenced by this moniker,
 *  such as a file, changed.
 *
 * Parameters:
 *  pBindCtx        LPBINDCTX to the bind context in use.
 *  pmkLeft         LPMONIKER to the left.
 *  pTime           FILETIME * in which to store the last change
 *                  time and date information.
 */

STDMETHODIMP CImpIMoniker::GetTimeOfLastChange(LPBC pBindCtx
    , LPMONIKER pmkLeft, FILETIME *pTime)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::Inverse
 *
 * Purpose:
 *  Creates an inverse of this moniker such that a composite
 *  containing this moniker and its inverse to the right would
 *  annihilate each other.
 *
 * Parameters:
 *  ppmkInverse     LPMONIKER * in which to store the inverse.
 */

STDMETHODIMP CImpIMoniker::Inverse(LPMONIKER *)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMoniker::CommonPrefixWith
 *
 * Purpose:
 *  Determines if this moniker and another have a common prefix
 *  (left elements) that can be separated out into another
 *  moniker.
 *
 * Parameters:
 *  pmk             LPMONIKER to the other moniker.
 *  ppmkPrefix      LPMONIKER * in which to store the prefix moniker
 *                  if there is one, otherwise receives NULL.
 */

STDMETHODIMP CImpIMoniker::CommonPrefixWith(LPMONIKER, LPMONIKER *)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMoniker::RelativePathTo
 *
 * Purpose:
 *  Returns another moniker that contains the relative path between
 *  this moniker and another.
 *
 * Parameters:
 *  pmk             LPMONIKER of the other moniker.
 *  ppmkRelative    LPMONIKER * in which to store a moniker that
 *                  contains the relative path.
 */

STDMETHODIMP CImpIMoniker::RelativePathTo(LPMONIKER, LPMONIKER *)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMoniker::GetDisplayName
 *
 * Purpose:
 *  Returns a human-readable name suitable for display of this
 *  moniker.
 *
 * Parameters:
 *  pBindCtx        LPBC to the current bind context.
 *  pmkLeft         LPMONIKER to the left.
 *  ppszName        LPOLESTR * in which to store the display name.
 *                  Output can be NULL if there is no name.
 */

STDMETHODIMP CImpIMoniker::GetDisplayName(LPBC, LPMONIKER, LPOLESTR *)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMoniker::ParseDisplayName
 *
 * Purpose:
 *  Pparses the moniker's remaining display name. The pszDisplayName
 *  parameter is the yet-to-be-parsed tail of the display name.  This
 *  function parses as much of the remaining tail as is appropriate
 *  for a display name within the object identified by
 *  (pmkToLeft * (the receiver)) and returns the corresponding
 *  moniker.
 *
 * Parameters:
 *  pBindCtx        LPBC to the current bind context.
 *  pmkLeft         LPMONIKER to the left.
 *  pszDisplayName  LPOLESTR to the display name to be parsed.
 *  pchEaten        ULONG * with the number of characters of the
 *                  input name this parse consumed.
 *  ppmkOut         LPMONIKER in whic to store the resulting
 *                  moniker.
 *
 */

STDMETHODIMP CImpIMoniker::ParseDisplayName(LPBC pBindCtx
    , LPMONIKER pmkLeft, LPOLESTR pszDisplayName, ULONG *pchEaten
    , LPMONIKER *ppmkOut)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMoniker::IsSystemMoniker
 *
 * Purpose:
 *  Returns whether or not this is a system-implemented moniker
 *  whose implemented semantics are important for the binding
 *  process.
 *
 * Parameters:
 *  pdwType         LPDWORD in which to return the system moniker
 *                  type, from the MKSYS enumeration if S_OK is
 *                  returned.
 *
 * Return Value:
 *  HRESULT         S_OK or S_FALSE.
 */

STDMETHODIMP CImpIMoniker::IsSystemMoniker(LPDWORD)
    {
    return ResultFromScode(E_NOTIMPL);
    }
