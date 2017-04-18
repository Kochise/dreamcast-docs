/*
 * CLIENT.CPP
 * Freeloader Chapter 11
 *
 * Implementation of the CFreeloaderClient class that just makes
 * sure we get a CFreeloaderDoc on doc creation and that we
 * initialize fully.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "freeload.h"


/*
 * CFreeloaderClient::CFreeloaderClient
 * CFreeloaderClient::~CFreeloaderClient
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame to the frame object.
 */

CFreeloaderClient::CFreeloaderClient(HINSTANCE hInst
    , PCFrame pFR)
    : CClient(hInst, pFR)
    {
    return;
    }


CFreeloaderClient::~CFreeloaderClient(void)
    {
    return;
    }



/*
 * CFreeloaderClient::CreateCDocument
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

PCDocument CFreeloaderClient::CreateCDocument(void)
    {
    return (PCDocument)(new CFreeloaderDoc(m_hInst, m_pFR, m_pAdv));
    }
