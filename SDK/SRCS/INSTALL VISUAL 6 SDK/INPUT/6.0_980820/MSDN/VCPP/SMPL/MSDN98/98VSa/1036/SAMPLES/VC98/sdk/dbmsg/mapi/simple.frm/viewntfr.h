/*
 *  VIEWNTFR.H
 *  
 *  Helper class for supporting event notifications
 *
 *  Copyright (c) 1995, Microsoft Corporation.
 *  All rights reserved.
 */


#ifndef _VIEWNTFR_H_
#define _VIEWNTFR_H_

#define MAXSINKS    32

class CViewNotifier
{
private:
    LPMAPIVIEWADVISESINK    m_aryAdviseSink [MAXSINKS];

public:

    CViewNotifier  (void);
    ~CViewNotifier ();

    BOOL        Initialize (void);

    HRESULT     Advise (LPMAPIVIEWADVISESINK pAdvise, ULONG * pulConnection);
    HRESULT     Unadvise (ULONG ulConnection);

    void        OnShutdown (void);
    void        OnNewMessage (void);
    HRESULT        OnPrint (ULONG ulPageNumber, HRESULT hrStatus);
    void        OnSubmitted (void);
    void        OnSaved (void);
};

#endif //_VIEWNTFR_H_
