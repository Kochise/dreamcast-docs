/*
 * CLIENT.CPP
 * Cosmo Chapter 14
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
    m_pAutoFigures=NULL;
    return;
    }


CCosmoClient::~CCosmoClient(void)
    {
    //CHAPTER14MOD
    DeleteInterfaceImp(m_pAutoFigures);
    //End CHAPTER14MOD
    return;
    }



/*
 * CCosmoClient::Init
 *
 * Purpose:
 *  Performs default initialization then creates the Figures
 *  collection object stored here.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CCosmoClient::Init(HMENU hMenuWindow, LPRECT pRect)
    {
    if (!CClient::Init(hMenuWindow, pRect))
        return FALSE;

    //Create the 'figures' collection.
    m_pAutoFigures=new CAutoFigures(this);

    if (NULL==m_pAutoFigures)
        return FALSE;

    if (!m_pAutoFigures->Init(FALSE))
        return FALSE;

    return TRUE;
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



//CHAPTER14MOD
/*
 * CCosmoClient::AutoFigures
 *
 * Purpose:
 *  Returns the 'figures' collection automation object pointer
 *
 * Return Value:
 *  PCAutoFigures   Pointer to the figures collection object
 */

PCAutoFigures CCosmoClient::AutoFigures(void)
    {
    return m_pAutoFigures;
    }
//End CHAPTER14MOD
