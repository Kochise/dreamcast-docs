/*
 * CLIENT.CPP
 * Patron Chapter 7
 *
 * Implementation of the CPatronClient class that just makes sure
 * we get a CPatronDoc on doc creation and that we initialize fully.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CPatronClient::CPatronClient
 * CPatronClient::~CPatronClient
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame to the frame object.
 */

CPatronClient::CPatronClient(HINSTANCE hInst, PCFrame pFR)
    : CClient(hInst, pFR)
    {
    return;
    }


CPatronClient::~CPatronClient(void)
    {
    return;
    }





/*
 * CPatronClient::CreateCDocument
 *
 * Purpose:
 *  Constructs a new document specific to the application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCDocument      Pointer to the new document object.
 */

PCDocument CPatronClient::CreateCDocument(void)
    {
    return (PCDocument)(new CPatronDoc(m_hInst, m_pFR, m_pAdv));
    }
