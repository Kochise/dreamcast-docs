/*
 * KOALA.CPP
 * Koala Object with Custom Interface, Chapter 6
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

    //CHAPTER6MOD
    m_pImpIAnimal=NULL;
    m_pImpIKoala=NULL;

    m_fJustAte=FALSE;
    m_cSleepAfterEat=0;
    //End CHAPTER6MOD

    return;
    }


CKoala::~CKoala(void)
    {
    //CHAPTER6MOD
    DeleteInterfaceImp(m_pImpIKoala);
    DeleteInterfaceImp(m_pImpIAnimal);
    //End CHAPTER6MOD
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
    //CHAPTER6MOD
    IUnknown   *pUnkOuter=m_pUnkOuter;

    if (NULL==pUnkOuter)
        pUnkOuter=this;

    m_pImpIAnimal=new CImpIAnimal(this, pUnkOuter);

    if (NULL==m_pImpIAnimal)
        return FALSE;

    m_pImpIKoala=new CImpIKoala(this, pUnkOuter);

    if (NULL==m_pImpIKoala)
        return FALSE;
    //End CHAPTER6MOD

    return TRUE;
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

    //CHAPTER6MOD
    if (IID_IAnimal==riid)
        *ppv=m_pImpIAnimal;

    if (IID_IKoala==riid)
        *ppv=m_pImpIKoala;
    //End CHAPTER6MOD

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




//CHAPTER6MOD

//IAnimal implementation


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
    //Koalas aren't don't care what you tell them, they eat one thing
   #ifdef WIN32ANSI
    lstrcpyn(pszFoodEaten, "Eucalyptus Leaves", cchEaten);
   #else
    _tcsncpy(pszFoodEaten, TEXT("Eucalyptus Leaves"), cchEaten);
   #endif
    m_pObj->m_fJustAte=TRUE;
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
    /*
     * Koalas welcome the opportunity to sleep, and will probably
     * sleep longer than you tell them, so return more time than
     * we were told based on IKoala::SleepAfterEating.
     */
    *pcMinutes=*pcMinutes+m_pObj->m_cSleepAfterEat;
    m_pObj->m_fJustAte=FALSE;     //Probably want to eat again
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
    DWORD       dw;
    SCODE       sc=S_FALSE;

    /*
     * Koalas like to reproduce when they damn well please and
     * not when someone else tells them, so we'll just check
     * the current time, and if it's appropriate, we'll reproduce.
     * (Simulation:  use GetTickCount to get the system time, then
     * divide by 100 to filter out resolution concerns, then see if
     * the result is an even multiple of 10).
     *
     * Also, Koalas only produce one offspring at a time.  If
     * this was a rabbit, we might get anywhere from 2-20 offspring.
     */

    dw=GetTickCount()/100;

    if ((dw/10)*10==dw)
        {
        *pcOffspring=1;
        sc=S_OK;
        }
    else
        *pcOffspring=0;

    return ResultFromScode(sc);
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
    //Nothing to demonstrate...
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
    //Nothing to demonstrate...
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
    m_pObj->m_cSleepAfterEat=cMinutes;
    return NOERROR;
    }

//End CHAPTER6MOD
