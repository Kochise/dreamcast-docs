/*
 * PAGE.CPP
 * Patron Chapter 7
 *
 * Implementation of the CPage class to manage a single page.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CPage::CPage
 * CPage::~CPage
 *
 * Constructor Parameters:
 *  dwID            DWORD identifier for this page.
 */

CPage::CPage(DWORD dwID)
    {
    //CHAPTER7MOD
    m_dwID     =dwID;
    m_pIStorage=NULL;
    //End CHAPTER7MOD
    return;
    }

CPage::~CPage(void)
    {
    //CHAPTER7MOD
    Close(FALSE);
    //End CHAPTER7MOD
    return;
    }



/*
 * CPage::GetID
 *
 * Return Value:
 *  DWORD           dwID field in this page.
 */

DWORD CPage::GetID(void)
    {
    return m_dwID;
    }




//CHAPTER7MOD

/*
 * CPage::Open
 *
 * Purpose:
 *  Retrieves the IStorage associated with this page.  The IStorage
 *  is owned by the page and thus the page always holds a reference
 *  count.  The caller should call Close or delete this page to
 *  match this open.
 *
 *  This function may be called multiple times resulting in
 *  additional reference counts on the storage each of which must be
 *  matched with a call to Close.  The last Close can be done
 *  through delete.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE in which this page lives.
 *
 * Return Value:
 *  BOOL            TRUE if opening succeeds, FALSE otherwise.
 */

BOOL CPage::Open(LPSTORAGE pIStorage)
    {
    BOOL        fNULL=FALSE;
    HRESULT     hr=NOERROR;
    DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
                    | STGM_SHARE_EXCLUSIVE;
    OLECHAR     szTemp[32];

    if (NULL==m_pIStorage)
        {
        fNULL=TRUE;

        if (NULL==pIStorage)
            return FALSE;

        /*
         * Attempt to open the storage under this ID.  If none,
         * create one.  In either case, the IStorage is either
         * saved in pPage or released.
         */

        GetStorageName(szTemp);

        hr=pIStorage->OpenStorage(szTemp, NULL, dwMode, NULL, 0
            , &m_pIStorage);

        if (FAILED(hr))
            {
            hr=pIStorage->CreateStorage(szTemp, dwMode, 0, 0
                , &m_pIStorage);
            }
        }
    else
        m_pIStorage->AddRef();

    if (FAILED(hr))
        {
        if (fNULL)
            m_pIStorage=NULL;

        return FALSE;
        }

    return TRUE;
    }




/*
 * CPage::Close
 *
 * Purpose:
 *  Possibly commits the storage, then releases it reversing the
 *  reference count from Open.
 *
 * Parameters:
 *  fCommit         BOOL indicating if we're to commit.
 *
 * Return Value:
 *  None
 */

void CPage::Close(BOOL fCommit)
    {
    if (NULL==m_pIStorage)
        return;

    if (fCommit)
        Update();

    if (0L==m_pIStorage->Release())
        m_pIStorage=NULL;

    return;
    }




/*
 * CPage::Update
 *
 * Purpose:
 *  Forces a common on the page if it's open.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            Always TRUE for now.
 */

BOOL CPage::Update(void)
    {
    if (NULL!=m_pIStorage)
        m_pIStorage->Commit(STGC_DEFAULT);

    return TRUE;
    }





/*
 * CPage::Destroy
 *
 * Purpose:
 *  Removes this page from the given storage.  The caller should
 *  eventually delete this Page object to free the storage.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE contianing this page on which to call
 *                  DestroyElement
 *
 * Return Value:
 *  None
 */

void CPage::Destroy(LPSTORAGE pIStorage)
    {
    if (NULL!=pIStorage)
        {
        OLECHAR szTemp[32];

        Close(FALSE);
        GetStorageName(szTemp);
        pIStorage->DestroyElement(szTemp);
        }

    return;
    }




/*
 * CPage::GetStorageName
 *
 * Parameters:
 *  pszName         LPOLESTR to a buffer in which to store the
 *                  storage name for this page.
 *
 * Return Value:
 *  UINT            Number of characters stored.
 */

UINT CPage::GetStorageName(LPOLESTR pszName)
    {
   #ifdef WIN32ANSI
    char        szTemp[32];
    UINT        cch;

    cch=wsprintf(szTemp, "Page %lu", m_dwID);
    MultiByteToWideChar(CP_ACP, 0, szTemp, -1, pszName, 32);
    return cch;
   #else
    return wsprintf(pszName, TEXT("Page %lu"), m_dwID);
   #endif
    }

//End CHAPTER7MOD
