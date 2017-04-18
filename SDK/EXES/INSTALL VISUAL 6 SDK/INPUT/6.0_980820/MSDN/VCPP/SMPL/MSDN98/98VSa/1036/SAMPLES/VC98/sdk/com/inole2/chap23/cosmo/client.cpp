/*
 * CLIENT.CPP
 * Cosmo Chapter 23
 *
 * Implementation of the CCosmoClient class that just makes sure
 * we get a CCosmoDoc on doc creation and that we initialize fully.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CCosmoClient::CCosmoClient
 * CCosmoClient::~CCosmoClient
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame to the frame object.
 */

CCosmoClient::CCosmoClient(HINSTANCE hInst, PCFrame pFR)
    : CClient(hInst, pFR)
    {
    return;
    }


CCosmoClient::~CCosmoClient(void)
    {
    return;
    }





/*
 * CCosmoClient::CreateCDocument
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

PCDocument CCosmoClient::CreateCDocument(void)
    {
    return (PCDocument)(new CCosmoDoc(m_hInst, m_pFR, m_pAdv));
    }







/*
 * CCosmoClient::NewDocument
 *
 * Purpose:
 *  Small override of the CClient::NewDocument that we have just
 *  to check the initial line selection on new document creation.
 *
 * Parameters:
 *  fVisible        BOOL indicating if the document is to be
 *                  visible or not.
 *
 * Return Value:
 *  PCDocument      Pointer to the new document object.
 */

PCDocument CCosmoClient::NewDocument(BOOL fVisible)
    {
    PCDocument  pDoc;

    //Perform default NewDocument first
    pDoc=CClient::NewDocument(fVisible);

    //We know that m_pFR is actually a CCosmoFrame, so type is safe.
    ((PCCosmoFrame)m_pFR)->CheckLineSelection(IDM_LINESOLID);

    return pDoc;
    }
