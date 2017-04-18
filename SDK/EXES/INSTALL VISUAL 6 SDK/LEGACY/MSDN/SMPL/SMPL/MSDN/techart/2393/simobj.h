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
// simobj.h
//
//
#ifndef _SIMOBJ_H_
#define _SIMOBJ_H_

#define MAX_CLIENTS     16

#define F_SIM_SYMBOL 0x0001
#define F_SIM_HIGH   0x0002
#define F_SIM_LOW    0x0004
#define F_SIM_LAST   0x0008
#define F_SIM_VOLUME 0x0010
#define F_SIM_ALL    0xFFFF

typedef struct tagSIMSTOCK
{
    UINT        uiIndex ;
    UINT        uiMembers ;     // F_SIM_ flags
    TCHAR       szSymbol[16] ;  // F_SIM_SYMBOL 0x0001    NOTE! Unicode!
    ULONG       ulHigh ;        // F_SIM_HIGH   0x0002
    ULONG       ulLow ;         // F_SIM_LOW    0x0004
    ULONG       ulLast;         // F_SIM_LAST   0x0008
    ULONG       ulVolume ;      // F_SIM_VOLUME 0x0010
} SIMSTOCK, *PSIMSTOCK, FAR *LPSIMSTOCK ;

typedef struct tagSIMSTOCKS
{
    UINT        cStocks ;
    SIMSTOCK    rgStocks[1] ; // pointer access only
} SIMSTOCKS, *PSIMSTOCKS, FAR *LPSIMSTOCKS ;


class CSimulation : public CObject
{
public:
    CSimulation() ;
    ~CSimulation() ;

    BOOL    Reset( void ) ;     // resets to startup state
    void    OnTick( void ) ;    // move to next state
    UINT    RegisterClient( LPVOID pObj ) ;
    BOOL    UnRegisterClient( UINT index ) ;
    PSIMSTOCKS  GetData() ;
    
    UINT        GetCount() ;            // Get the number of stocks
    PSIMSTOCK   GetStock( UINT n ) ;    // Get a specific stock
    
    BOOL        StartSimulation( CWnd* pTimerWnd ) ;
    void        StopSimulation() ;

    BOOL        DoOptionsDialog( CWnd* pParent ) ;
private:
    UINT        m_cUpdatesPerTick ; // number of items to change per tick
    UINT        m_uiMarketTimeOut ;
    BOOL        m_fBullMarket ;     // if TRUE market tends to go up
    PSIMSTOCKS  m_pData ;           // our database

    CWnd*       m_pwndTimer ;
    UINT        m_nIDTimerEvent ;

    // client info
    LPVOID      m_rgClients[MAX_CLIENTS] ;

} ;

/////////////////////////////////////////////////////////////////////////////
// CSimOptsDlg dialog

class CSimOptsDlg : public CDialog
{
// Construction
public:
    CSimOptsDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
    //{{AFX_DATA(CSimOptsDlg)
    enum { IDD = IDD_SIMOPTS };
    UINT    m_uiMarketTimeOut;
    UINT    m_uiUpdatesPerTick;
    BOOL    m_fReset;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CSimOptsDlg)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // _SIMOBJ_H_


