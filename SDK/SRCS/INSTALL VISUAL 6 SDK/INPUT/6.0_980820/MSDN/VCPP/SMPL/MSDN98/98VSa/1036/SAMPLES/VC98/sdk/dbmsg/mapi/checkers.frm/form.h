HRESULT HrStartOleAndRegisterClassFactory(void);
HRESULT HrStopForms(void);

#define NOTPURE
#define MAX_ADVISE 48

/*
 *  Types
 */

// ----- class factory
class FRMFAC : public IClassFactory
{
  protected:
    ULONG       cRef;
    CLSID       clsid;

    ~FRMFAC(void);

  public:
    FRMFAC();

    // *** IUnknown methods
    STDMETHOD(QueryInterface)   (THIS_ REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG,AddRef)    (THIS);
    STDMETHOD_(ULONG,Release)   (THIS);

    // *** IClassFactory methods
    STDMETHOD(CreateInstance)   (THIS_ LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR* ppvObject);
    STDMETHOD(LockServer)       (THIS_ BOOL fLock);
};

class FRMFMR : public FRMFAC
{
  public:
    FRMFMR();
};

// ----- The minimal interface a form can support
class FRM : public IPersistMessage, public IMAPIForm
{
  protected:
    ULONG                   cRef;               // Reference count
    CLSID                   clsid;

    BOOL                    fDirty;             // Is our message dirty?
    BOOL                    fNoScribble;        // Are we in no-scribble mode?
    BOOL                    fSentMessage;       // Are we reading a sent message?

    // advise handling

    BOOL                    afAdvisee[MAX_ADVISE];
    LPMAPIVIEWADVISESINK    aAdvisePtrs[MAX_ADVISE];

    // data

    SQUARE                  b[SQRS_MAX];        // The board
    int                     turn;               // Who's turn it is
    long                    movenum;
    long                    score;

    ~FRM(void);

  public:
    LPMESSAGE               pMessage;
    LPMAPIMESSAGESITE       pMessageSite;
    LPMAPISESSION           pSession;

    LPMAPIFORMMGR           pFormMgr;
    LPMAPIFORMINFO          pFormInfo;

    FRM(REFCLSID clsid);

    MAPI_IUNKNOWN_METHODS(NOTPURE)
    MAPI_GETLASTERROR_METHOD(NOTPURE)
    MAPI_IPERSISTMESSAGE_METHODS(NOTPURE)
    MAPI_IMAPIFORM_METHODS(NOTPURE)

    HRESULT ShowCurrentMessage(ULONG ulhwndParent);
    HRESULT LaunchReplyMessage(ULONG ulhwndParent);
    VOID FRM::GetCheckersData(SQUARE* out_b, int* out_turn, long* out_movenum, long* out_score);
    VOID FRM::SetCheckersData(SQUARE* in_b, int in_turn, long in_movenumber, long in_score);
    HRESULT FRM::Remember(LPMAPIMESSAGESITE pmsite, LPMESSAGE pmsg);
    HRESULT FRM::Forget(VOID);
    HRESULT SendForm(VOID);
    HRESULT FRM::AddressForm(HWND hwnd, BOOL fDontShowIfRecipsExist);
    SCODE FRM::ScGetRecipientAdrlist(LPMESSAGE pmsg, LPADRLIST * ppal);

};

/*
 *  Macros
 */

#define ADVISE(X)                        \
   for (LONG i = 0; i < MAX_ADVISE; i++) \
      if (afAdvisee[i])                  \
         aAdvisePtrs[i]->X

#define ReleaseObj(_pobj) \
        if (_pobj) \
                (_pobj)->Release()

/*
 *  Dependencies specific to this form
 */

#define CHKR_FORM
extern HWND hMainWnd;

#define PR_BOARD        PROP_TAG( PT_BINARY,    0x6800)
#define PR_TURN         PROP_TAG( PT_LONG,      0x6801)
#define PR_MOVENUMBER   PROP_TAG( PT_LONG,      0x6802)
#define PR_SCORINGFUNC  PROP_TAG( PT_LONG,      0x6803)

