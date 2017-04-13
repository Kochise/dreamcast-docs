//
//  FORMBASE.H
//  
//  Base form class definition
//
//  Copyright (c) 1986-1996, Microsoft Corporation.
//  All rights reserved.
//


#include        <chsfld.h>

//
//  Form states
//

enum { stateUninit, stateNormal, stateNoScribble, stateHandsOffFromNormal,
        stateHandsOffFromSave, stateDead };

//
//  Message properties held in memory
//

enum { irtTo, irtCc, irtSubject, irtTime, irtFrom, irtClass, irtBody,
        irtNormSubject, irtConvIdx, irtConvTopic, cpropMsg};
#define MESSAGE_TAGS { cpropMsg, \
    { PR_DISPLAY_TO, PR_DISPLAY_CC, PR_SUBJECT, \
      PR_CLIENT_SUBMIT_TIME, PR_SENDER_NAME, PR_MESSAGE_CLASS, \
      PR_BODY, PR_NORMALIZED_SUBJECT, PR_CONVERSATION_INDEX, PR_CONVERSATION_TOPIC } }

//form type
enum { eformRead, eformSend};

//reply type  (this form does not implement reply all)
enum eREPLYTYPE {eREPLY, eFORWARD, eREPLY_ALL}; 

//message class
//has to be the same as MessageClass in smpfrm.cfg
#define FormClassName "IPM.Note.Sample.Simple"



//all the MAPI form interfaces we'll need
class CBaseForm : public IPersistMessage, public IMAPIForm,
                    public IMAPIFormAdviseSink
{
    CBaseForm *         m_pfrmNext;             // Linked list of forms

    ULONG               m_cRef;                 // Reference Count on object
    ULONG               m_state;                //uses state enum
    CLastError          m_lsterr;               // Last Error Implementation


    CClassFactory *     m_pClassFactory;        // The factory that created us
    CViewNotifier       m_viewnotify;

    LPMAPIVIEWCONTEXT   m_pviewctxOverride;
    LPMAPIVIEWCONTEXT   m_pviewctx;             // View context interface

    LPMESSAGE           m_pmsg;                 // our message
    LPMAPIMESSAGESITE   m_pmsgsite;             // our message site
    LPMAPISESSION       m_pses;                 // our MAPI session
    LPADRBOOK           m_pab;                  // our address book

    LPADRLIST           m_padrlist;             // Current recipient list
    LPSPropValue        m_pval;                 // Current message contents

    ULONG               m_ulMsgFlags;           // Message flags
    ULONG               m_ulMsgStatus;          // Message status flags
    ULONG               m_ulSiteStatus;         // Message Site status flags
    ULONG               m_ulViewStatus;         // View context status flags

    ULONG               m_cxMin;                // Minimium size of window
    ULONG               m_cyMin;                //

    int                 m_eFormType;            //read/write

    unsigned int        m_fSameAsLoaded:1;      // Copy of ::Save flag
    unsigned int        m_fRecipientsDirty:1;   // Is the recip list dirty?
    unsigned int        m_fDirty:1;
    unsigned int        m_fConvTopicSet:1;

    ULONG               m_cbConvIdx;
    LPBYTE              m_lpbConvIdx;
    
    HACCEL              m_HAccelTable;

    HMODULE             m_hChsFldDll;
    HRPICKFOLDER        m_lpfnHrPickFolder;
    ULONG               m_cbCFDState;
    LPBYTE              m_pbCFDState;

    
public:
    
    HWND                m_hwnd;
    HWND                m_hwndDialog;

public:
    CBaseForm(CClassFactory *);
    ~CBaseForm(void);

    MAPI_IUNKNOWN_METHODS(IMPL);
    MAPI_GETLASTERROR_METHOD(IMPL);
    MAPI_IPERSISTMESSAGE_METHODS(IMPL);
    MAPI_IMAPIFORM_METHODS(IMPL);
    MAPI_IMAPIFORMADVISESINK_METHODS(IMPL);

    //utility methods

    
    BOOL                TranslateMessage(MSG&);
    LPMESSAGE           Message(void) { return m_pmsg; }
    LPMAPIMESSAGESITE   MsgSite(void) { return m_pmsgsite; }
    LPMAPIVIEWCONTEXT   ViewCtx(void) { return (m_pviewctxOverride ? m_pviewctxOverride:m_pviewctx); }
    void                Address(int);
    void                ClearWindow(void);  
    void                ConfigMenu(HMENU hMenu);
    HRESULT             HrQuerySave (DWORD ulSaveOptions);
    void                SetMinSize(int cx, int cy) { m_cxMin = cx; m_cyMin = cy; return; }
    CBaseForm *         GetNext(void) { return m_pfrmNext; }
    void                DoSubmit(void);
    void                DoSave(void);
    void                DoDelete(void);
    void                DoCopy(void);
    void                DoMove(void);
    void                DoNext(ULONG ulDir);                
    void                DoReply(eREPLYTYPE);

private:
                                            
    void                DisplayMessage(void);
    HRESULT             HrGetMsgDataFromUI(HWND hDlg);
    HRESULT             HrGetMsgDataFromMsg(LPMESSAGE pmsg, ULONG ulMsgFlags);
    BOOL                IsAddressed(void);
    HRESULT             HrReply(eREPLYTYPE eType, HWND hwndParent, LPCRECT rcPos);
    void                DeInitObjects(void);
    HRESULT             HrOpenForm(HWND, LPCRECT, ULONG);
    HRESULT             HrSaveInto(LPMESSAGE);
    void                UpdateRecipientsDisplay(void);
    int                 ShowMessageBox(HWND, LPCTSTR, LPCTSTR, UINT);
    void                ShowError();
    inline void         ConfigWinMenu(void);
    HRESULT             HrSaveToString(LPSTR *);
    void                ClearDirty(void);
    BOOL                FGetFoldChooser(void);

};



//
//  Linked list of form objects
//

extern CBaseForm *      g_PfrmFirst;

//
//  Other globals
//

extern HINSTANCE        g_hinst;
extern LPVOID           g_lpCtl3d;

void FormatTime(FILETIME *pft, LPSTR szTime);
HRESULT GetMsgAdrlist (LPMESSAGE pmsg, LPADRLIST *  ppAdrList, CLastError *);
HRESULT HrStreamInMsgBody(LPMESSAGE pmsg, LPVOID pbase, LPSTR *  pszBody, CLastError * plsterr);
HRESULT HrStreamOutMsgBody(LPMESSAGE pmsg, LPSTR szBody, CLastError * plsterr);


///     CBaseForm::ConfigWinMenu()
//
inline void CBaseForm::ConfigWinMenu()
{
    if(NULL != m_hwnd)
    {
        HMENU hmenu = GetMenu(m_hwnd);
        if(NULL != hmenu)
            ConfigMenu(hmenu);
    }
}
