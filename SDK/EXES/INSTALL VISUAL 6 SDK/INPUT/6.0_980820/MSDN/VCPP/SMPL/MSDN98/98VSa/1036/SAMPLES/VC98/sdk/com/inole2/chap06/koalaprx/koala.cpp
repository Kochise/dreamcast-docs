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
 * CKoala::CKoala
 * CKoala::~CKoala
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of a controlling unknown.
 *  pfnDestroy      PFNDESTROYED to call when an object
 *                  is destroyed.
 */

CKoala::CKoala(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;

    m_pImpIAnimal=NULL;
    m_pImpIKoala=NULL;
    m_pImpIMarshal=NULL;

    m_fJustAte=FALSE;
    m_cSleepAfterEat=0;

    return;
    }


CKoala::~CKoala(void)
    {
    DeleteInterfaceImp(m_pImpIMarshal);
    DeleteInterfaceImp(m_pImpIKoala);
    DeleteInterfaceImp(m_pImpIAnimal);
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
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CKoala::Init(void)
    {
    IUnknown   *pUnkOuter=m_pUnkOuter;

    if (NULL==pUnkOuter)
        pUnkOuter=this;

    m_pImpIAnimal=new CImpIAnimal(this, pUnkOuter);

    if (NULL==m_pImpIAnimal)
        return FALSE;

    m_pImpIKoala=new CImpIKoala(this, pUnkOuter);

    if (NULL==m_pImpIKoala)
        return FALSE;

    m_pImpIMarshal=new CImpIMarshal(this, pUnkOuter);

    if (NULL==m_pImpIMarshal)
        return FALSE;

    return TRUE;
    }




/*
 * CKoala::CallLocal
 *
 * Purpose:
 *  Sends or posts a message to the local object.
 *
 * Parameters:
 *  iMsg            UINT identifying the function to call
 *  lParam          LPARAM containing extra information
 *  fAsync          BOOL indicating if this is a Post (TRUE) or
 *                  a send (FALSE).
 *
 * Return Value:
 *  DWORD           Return value from the function or an HRESULT
 *                  on failure.
 */

DWORD CKoala::CallLocal(UINT iMsg, LPARAM lParam, BOOL fAsync)
    {
    DWORD   dwRet=0;

    if (fAsync)
        PostMessage(m_hWndLocal, WM_COMMAND, (WPARAM)iMsg, lParam);
    else
        {
        dwRet=SendMessage(m_hWndLocal, WM_COMMAND, (WPARAM)iMsg
            , lParam);
        }

    return dwRet;
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

    /*
     * The only calls for IUnknown are either in a nonaggregated
     * case or when created in an aggregation, so in either case
     * always return our IUnknown for IID_IUnknown.
     */
    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IAnimal==riid)
        *ppv=m_pImpIAnimal;

    if (IID_IKoala==riid)
        *ppv=m_pImpIKoala;

    if (IID_IMarshal==riid)
        *ppv=m_pImpIMarshal;

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

    /*
     * If this is the last Release, then we have to tell
     * the server to free its object too.  This is an async
     * call as we don't need to hang around for it to quit.
     */
    CallLocal(MSG_RELEASE, 0, TRUE);

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }





//Proxy-side IAnimal implementation


/*
 * CImpIAnimal::CImpIAnimal
 * CImpIAnimal::~CImpIAnimal
 *
 * Constructor Parameters:
 *  pObj            PCKoala of the object containing us.
 *  pUnkOuter       LPUNKNOWN to which we blindly delegate
 *                  all IUnknown calls.
 */

CImpIAnimal::CImpIAnimal(PCKoala pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIAnimal::~CImpIAnimal(void)
    {
    return;
    }



/*
 * CImpIAnimal::QueryInterface
 * CImpIAnimal::AddRef
 * CImpIAnimal::Release
 *
 * Purpose:
 *  Delegating IUnknown members for interface implementation.
 */

STDMETHODIMP CImpIAnimal::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIAnimal::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIAnimal::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIAnimal::Eat
 *
 * Purpose:
 *  Instructs the animal to eat something, returning what the animal
 *  actually ate which usually goes against recommendation (which is
 *  true for the human animal, too).
 *
 * Parameters:
 *  pszFoodRecommended  LPTSTR describing the food that the animal
 *                      should eat.
 *  pszFoodEaten        LPTSTR describing the food the animal actually
 *                      ate, which may not, of course, be the same as
 *                      what it should eat.
 *  cchEaten            short containing the lenght of pszFoodEaten.
 *
 * Return Value:
 *  HRESULT             NOERROR if food is eaten, S_FALSE if not.
 */

STDMETHODIMP CImpIAnimal::Eat(LPTSTR pszFoodRecommended
    , LPTSTR pszFoodEaten, short cchEaten)
    {
    /*
     * Koalas aren't don't care what you tell them, they eat one
     * thing.  We can handle the return string for the local
     * object, but we still need to tell it that this was
     * called.
     */

    _tcsncpy(pszFoodEaten, TEXT("Eucalyptus Leaves"), cchEaten);
    m_pObj->CallLocal(MSG_EAT, 0L, FALSE);
    return NOERROR;
    }



/*
 * CImpIAnimal::Sleep
 *
 * Purpose:
 *  Instructs the animal to sleep for a while.
 *
 * Parameters:
 *  pcMinutes      short * (in-out) containing the number of
 *                 minutes to sleep on entry, then number of
 *                 minutes actually slept on exit
 *
 * Return Value:
 *  HRESULT        NOERROR if sleep taken, S_FALSE if not, where
 *                 *pcMinutes should be zero.
 */

STDMETHODIMP CImpIAnimal::Sleep(short *pcMinutes)
    {
    DWORD       dwRet;

    //Pass the client's value
    dwRet=m_pObj->CallLocal(MSG_SLEEP, (LPARAM)*pcMinutes, FALSE);

    if (FAILED((HRESULT)dwRet))
        return (HRESULT)dwRet;

    //Store the return value in the client's variable.
    *pcMinutes=LOWORD(dwRet);
    return NOERROR;
    }



/*
 * CImpIAnimal::Procreate
 *
 * Purpose:
 *  Instructs the animal to procreate.  On entry, the number of
 *  offstring is unknown, so that's an out parameter.
 *
 * Parameters:
 *  pcOffspring     short * (out) in which to store the number
 *                  of new offspring.
 *
 * Return Value:
 *  HRESULT         NOERROR if offspring created, S_FALSE if not
 *                  where *pcOffspring should be zero.
 */

STDMETHODIMP CImpIAnimal::Procreate(short *pcOffspring)
    {
    DWORD       dwRet;

    dwRet=m_pObj->CallLocal(MSG_PROCREATE, 0, FALSE);

    if (FAILED((HRESULT)dwRet))
        return (HRESULT)dwRet;

    *pcOffspring=(short)LOWORD(dwRet);
    return ResultFromScode(0==dwRet ? S_FALSE : S_OK);
    }




/*
 * CImpIAnimal::WhatKindOfAnimal
 *
 * Purpose:
 *  Returns the IID of the specific animal interface that describes
 *  the type of animal this really is (a much more complex
 *  classification scheme might have IAnimal::WhatGenus and
 *  IGenus::WhatSpecies, etc., but we're just being simple here).
 *
 * Parameters:
 *  pIID            IID * in which to store the specific
 *                  animal IID.
 *
 * Return Value:
 *  HRESULT         NOERROR if the animal type is known,
 *                  S_FALSE if not with *pIID set to IID_NULL.
 */

STDMETHODIMP CImpIAnimal::WhatKindOfAnimal(IID *pIID)
    {
    //No need to ask the local object for something we know
    *pIID=IID_IKoala;
    return NOERROR;
    }





//IKoala implementation


/*
 * CImpIKoala::CImpIKoala
 * CImpIKoala::~CImpIKoala
 *
 * Constructor Parameters:
 *  pObj            PCKoala of the object containing us.
 *  pUnkOuter       LPUNKNOWN to which we blindly delegate
 *                  all IUnknown calls.
 */

CImpIKoala::CImpIKoala(PCKoala pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIKoala::~CImpIKoala(void)
    {
    return;
    }



/*
 * CImpIKoala::QueryInterface
 * CImpIKoala::AddRef
 * CImpIKoala::Release
 *
 * Purpose:
 *  Delegating IUnknown members for interface implementation.
 */

STDMETHODIMP CImpIKoala::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIKoala::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIKoala::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIKoala::ClimbEucalyptusTree
 *
 * Purpose:
 *  Tells the Koala to go climb a tree, which means eating, which
 *  a koala is probably more than happy to do.
 *
 * Parameters:
 *  iTree           short identifying the tree to climb.
 *
 * Return Value:
 *  HRESULT         NOERROR if tree climbed, S_FALSE if not.
 */

STDMETHODIMP CImpIKoala::ClimbEucalyptusTree(short iTree)
    {
    //We know the server doesn't need this
    return NOERROR;
    }



/*
 * CImpIKoala::PouchOpensDown
 *
 * Purpose:
 *  Do-nothing function to demonstrate a void argument list.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT             NOERROR
 */

STDMETHODIMP CImpIKoala::PouchOpensDown(void)
    {
    //We know the server doesn't need this
    return NOERROR;
    }



/*
 * CImpIKoala::SleepAfterEating
 *
 * Purpose:
 *  Tells the Koala to sleep an additional number of minutes after
 *  eating.
 *
 * Parameters:
 *  cMinutes        short * (in) containing the number of
 *                  extra minutes to sleep after eating.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIKoala::SleepAfterEating(short cMinutes)
    {
    DWORD   dwRet;

    dwRet=m_pObj->CallLocal(MSG_SLEEPAFTEREATING
        , (LPARAM)cMinutes, TRUE);

    if (FAILED((HRESULT)dwRet))
        return (HRESULT)dwRet;

    return NOERROR;
    }
