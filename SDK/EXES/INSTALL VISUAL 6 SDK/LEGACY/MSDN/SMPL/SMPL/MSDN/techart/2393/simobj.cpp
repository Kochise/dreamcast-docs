// WOSA/XRT XRTFrame Sample Application Version 1.01
//
// Copyright (c) 1993-94 Microsoft Corporation, All Rights Reserved.
//
//      This is a part of the Microsoft Source Code Samples. 
//      This source code is only intended as a supplement to 
//      Microsoft Development Tools and/or WinHelp documentation.
//      See these sources for detailed information regarding the 
//      Microsoft samples programs.
//
// simobj.cpp
//
// Implementation of the market simulation object.  This object
// simulates a real-time stock market data feed.
//
// It is intended that a vendor who wanted to use the XRTFrame sample
// as a 'framework' for building their own WOSA/XRT DataObject 
// would remove this file and replace it with code that actually
// interfaces with a real data feed.
//
// Concious effort has been made to make the implementation of 
// this "simulated data feed" as simple as possible as to avoid
// too many dependancies in other parts of XRTFrame on the
// simulation.
//
// NOTE:
//    The code in simobj.cpp and simobj.h can be compiled for
//      UNICODE.  If you are wondering what the TEXT() macro
//      is and what the TCHAR, LPTSTR etc.. types are, they abstract
//      away UNICODE dependancies so the code will compile for
//      both UNICODE and ANSI.  XRTFrame is an ANSI app.
//
// Revisions:
//  October 29, 1993 cek Created
//
#include "stdafx.h"
#include "xrtframe.h"
#include "doc.h"
#include "simobj.h"

#define LPTSTR LPSTR   
#ifndef TEXT
#define TEXT(a) a
#endif

LONG WINAPI ParseOffNumber( LPTSTR FAR *lplp, LPINT lpConv ) ;

CSimulation::CSimulation()
{
    m_cUpdatesPerTick = 0 ;
    m_uiMarketTimeOut = 0 ;
    
    m_pData = NULL ;

    // When XRTFrame starts up (e.g. the CMainFrame window is created)
    // one CSimulation object is created.   This one instance is
    // passed to each CDataObject.  Each DataObject, in turn, calls into
    // the simulation object 'registering itself'.   The m_rgClients
    // member contains a list of registered DataObjects
    //
    for (UINT i = 0 ; i < MAX_CLIENTS ; i++)
        m_rgClients[i] = NULL ;

    Reset() ;
}

CSimulation::~CSimulation()
{
    if (m_pData != NULL)
        free(m_pData );
}

// CSimulation::Reset()
// 
// Resets the simulation to it's start state.   All simulation informaiton
// is read out of the XRTFRAME.INI file.   This file has the following format:
/*
[Simulation] 
UpdatesPerTick = 5  ; Number of instrument changes per timer tick.
                    ; Each time a timer event fires the simulation object
                    ; calls into each 'client' (DataObject) UpdatesPerTick
                    ; times

MarketTimeout=500   ; Number of milliseconds between market changes
                    ; in the simulation. 
                    ; (actually read in in CMainFrame)

UpdateTimeout =     ; Default "UpdateFrequency" value.
                    ; See the WOSA/XRT Design Spec for a description of
                    ; the UpdateFrequency value.
                    ; (actually read in in CDataObject)
                    
[Quotes]
; This section contains lists of instruments represented in the
; simulation.  The format of entries is
;       Name=LastPrice,Volume
; Where Name is the name of the instrument, LastPrice is 
; the last price of the instrument times 1000, and Volume
; is the current trade volume. 
;
*/
//
BOOL CSimulation::Reset()
{
    m_cUpdatesPerTick =  AfxGetApp()->GetProfileInt( TEXT("Simulation"), TEXT("UpdatesPerTick"), 5 ) ;
    m_fBullMarket = TRUE ;

    if (m_pData != NULL)
        free( m_pData );

    // [Quotes] secton of INI file contains entries like this:
    // MSFT=last,volume
    //
    TCHAR * lpbuf = new TCHAR[16000] ;  
    TCHAR szVal[80] ;
    if (::GetPrivateProfileString( TEXT("Quotes"), NULL, TEXT(""), lpbuf, 16000, AfxGetApp()->m_pszProfileName ))
    {
        int c ;
        LPTSTR pszKey ;
        for (pszKey = lpbuf, c = 0;
                *pszKey != TEXT('\0'); pszKey += lstrlen(pszKey) + 1) 
            c++ ;

        m_pData = (LPSIMSTOCKS)malloc( (c * sizeof(SIMSTOCK)) + sizeof(SIMSTOCKS) ) ;
        m_pData->cStocks = c ;
        
        LPTSTR lp ;
        int nConv ;
        for (pszKey = lpbuf, c = 0 ; *pszKey != TEXT('\0'); pszKey += lstrlen(pszKey) + 1) 
        {
            ::GetPrivateProfileString(TEXT("Quotes"), pszKey, TEXT("0,0"), szVal, sizeof(szVal)/ sizeof(TCHAR),AfxGetApp()->m_pszProfileName ) ;
            lstrcpy( m_pData->rgStocks[c].szSymbol, pszKey ) ;
            lp = szVal ;
            m_pData->rgStocks[c].ulLast = ParseOffNumber( (LPTSTR FAR *)&lp, &nConv );
            m_pData->rgStocks[c].ulHigh = m_pData->rgStocks[c].ulLast ;
            m_pData->rgStocks[c].ulLow = m_pData->rgStocks[c].ulLast ;
            m_pData->rgStocks[c].ulVolume = ParseOffNumber( (LPTSTR FAR *)&lp, &nConv );
            m_pData->rgStocks[c].uiMembers = F_SIM_ALL ;
            m_pData->rgStocks[c].uiIndex = c ;
            c++ ;
        }            
    }
    else
    {
        m_pData = (LPSIMSTOCKS)malloc( sizeof(SIMSTOCKS) ) ;
        m_pData->cStocks = 0 ;
        
        AfxMessageBox( "There are no stocks listed in the XRTFRAME.INI file!\nMake sure you copy the "
                       "XRTFRAME.INI out of the SAMPLES\\XRTFRAME directory into your WINDOWS "
                       "directory before running XRTFrame!" ) ;
    }
    delete lpbuf ;

    
    // Reset the random number generator
    //
    srand( (unsigned)time( NULL ) );

    return TRUE ;
}

UINT CSimulation::GetCount()
{
    ASSERT(m_pData) ;
    return m_pData->cStocks ;
}   

PSIMSTOCK CSimulation::GetStock( UINT n )
{
    ASSERT( m_pData ) ;
    ASSERT( n < m_pData->cStocks ) ;
    
    return &m_pData->rgStocks[n] ;
}

// GetData
//
// This just returns a pointer to the simulation object.  
//
PSIMSTOCKS CSimulation::GetData()
{
    return m_pData ;
}

// OnTick
//
// Each timer tick generate random stock data.
//
void CSimulation::OnTick( void ) 
{
    int change ;
    LPSIMSTOCK    lpQ ;
    int i ;

    if (m_pData == NULL || m_pData->cStocks <= 0)
        return ;

    //TRACE("OnTick\r\n") ;

    // Generate a new data point m_cUpdatesPerTick times
    //
    UINT n = m_cUpdatesPerTick ;
    while (n--)
    {
        i = (int)((rand() / (double)RAND_MAX) * (double)m_pData->cStocks) ;
        
        //TRACE("Random stock #%d\r\n", i ) ;
    
        lpQ = &m_pData->rgStocks[i] ;
    
        // Randomize last price and volume
        //
        // There is no user interface associated with the m_fBullMarket
        // flag, but there could be...
        //
        // Notice that whan m_fBullMarket is set the last price is
        // more likely to go up than down.  Don't you wish you could
        // control markets like this in real life?
        // 
        if (m_fBullMarket) // tend to go up
            change = (rand() < (RAND_MAX / 2)) ? 250 : -125 ;
        else
            change = (rand() < (RAND_MAX / 2)) ? -250 : 125 ;
    
        if ((LONG)lpQ->ulLast + change > (LONG)0)
            lpQ->ulLast += change ;
        lpQ->uiMembers |= F_SIM_LAST ;

        if (lpQ->ulLast > lpQ->ulHigh)
        {
            lpQ->ulHigh = lpQ->ulLast ;
            lpQ->uiMembers |= F_SIM_HIGH ;
        }    
        if (lpQ->ulLast < lpQ->ulLow)
        {
            lpQ->ulLow = lpQ->ulLast ;
            lpQ->uiMembers |= F_SIM_LOW ;
        }
        
        // Pump up the volume
        //        
        lpQ->ulVolume += (abs(change)/2) ;
        lpQ->uiMembers |= F_SIM_VOLUME ;
    
        // Call the OnUpdateData members of all CStocksObject objects who
        // have registered with us.
        //
        for (UINT ui = 0 ; ui < MAX_CLIENTS ; ui++)
        {
            if (m_rgClients[ui] != NULL)
                ((CDataObject*)m_rgClients[ui])->OnStockChange( lpQ ) ;
        }
        lpQ->uiMembers = 0 ;
    }
}


// CSimulation::RegisterClient
//
// CDataObjects who wish to be notified when data is
// generated call this member to 'register'. 
//
UINT CSimulation::RegisterClient( LPVOID pObj )
{
    for (UINT i = 0 ; i < MAX_CLIENTS ; i++)
    {
        if (m_rgClients[i] == NULL)
        {
            m_rgClients[i] = pObj ;
            return i + 1 ;
        }
    }
    return 0 ;
}

// CSimulation::UnRegisterClient
//
// CDataObjects who registered with RegisterClient
// call this member to 'unregister'. 
//
BOOL CSimulation::UnRegisterClient( UINT index )
{
    if (index > 0)
        m_rgClients[index-1] = NULL ;
    else
        return FALSE ;

    return TRUE ;
}


BOOL CSimulation::StartSimulation( CWnd* pParent )
{
    m_pwndTimer = pParent ;
    m_uiMarketTimeOut = AfxGetApp()->GetProfileInt( TEXT("Simulation"), TEXT("MarketTimeout"), 250 ) ;
    m_nIDTimerEvent = m_pwndTimer->SetTimer( m_nIDTimerEvent, m_uiMarketTimeOut, NULL ) ;
    return (m_nIDTimerEvent > 0) ;
}

void CSimulation::StopSimulation()
{
    if (m_pwndTimer && m_nIDTimerEvent != NULL)
        m_pwndTimer->KillTimer( m_nIDTimerEvent ) ;
    m_pwndTimer = NULL ;
}

BOOL CSimulation::DoOptionsDialog( CWnd* pParent )
{
    CSimOptsDlg dlg( pParent ) ;
    
    dlg.m_uiMarketTimeOut = m_uiMarketTimeOut ;
    dlg.m_uiUpdatesPerTick = m_cUpdatesPerTick ;
    if (IDOK == dlg.DoModal())
    {
        m_uiMarketTimeOut = dlg.m_uiMarketTimeOut ;
        m_cUpdatesPerTick = dlg.m_uiUpdatesPerTick ;
        AfxGetApp()->WriteProfileInt( TEXT("Simulation"), TEXT("MarketTimeout"), m_uiMarketTimeOut ) ;
        AfxGetApp()->WriteProfileInt( TEXT("Simulation"), TEXT("UpdatesPerTick"), m_cUpdatesPerTick ) ;

        CWnd *pwnd = m_pwndTimer ;
        StopSimulation() ;
        if (pwnd)
            StartSimulation( pwnd ) ;
        
        if (dlg.m_fReset)
        {
            Reset() ;
        }        
        return TRUE ;
    }
    return FALSE ;
}

/////////////////////////////////////////////////////////////////////////////
// CSimOptsDlg dialog


CSimOptsDlg::CSimOptsDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSimOptsDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CSimOptsDlg)
    m_uiMarketTimeOut = 0;
    m_uiUpdatesPerTick = 0;
    m_fReset = FALSE;
    //}}AFX_DATA_INIT
}

void CSimOptsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSimOptsDlg)
    DDX_Text(pDX, IDC_MARKETTIMEOUT, m_uiMarketTimeOut);
    DDX_Text(pDX, IDC_UPDATESPERTICK, m_uiUpdatesPerTick);
    DDV_MinMaxUInt(pDX, m_uiUpdatesPerTick, 0, 1000);
    DDX_Check(pDX, IDC_RESET, m_fReset);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimOptsDlg, CDialog)
    //{{AFX_MSG_MAP(CSimOptsDlg)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSimOptsDlg message handlers
