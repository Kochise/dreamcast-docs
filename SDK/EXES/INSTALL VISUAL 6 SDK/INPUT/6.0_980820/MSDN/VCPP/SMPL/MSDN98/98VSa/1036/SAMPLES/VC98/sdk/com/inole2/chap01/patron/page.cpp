/*
 * PAGE.CPP
 * Patron Chapter 1
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
    m_dwID=dwID;
    return;
    }

CPage::~CPage(void)
    {
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
