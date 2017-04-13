//---------------------------------------------------------------------------
// App.h
//---------------------------------------------------------------------------
// Sample spr program
//---------------------------------------------------------------------------
// (C) Copyright 1992-1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------
extern class CApp *g_papp;
extern char       *g_pszCodeFile;
extern char       *g_pszRecFile;
extern int         g_mode;

#define MODE_NORMAL     0
#define MODE_PLAYBACK   1
#define MODE_RECORD     2


//---------------------------------------------------------------------------
// Events on client of App
//---------------------------------------------------------------------------
BOOL    AppEvt_Pause(int pause);
BOOL    AppEvt_FQueryTerminate(BOOL fPromptUser);
void    AppEvt_NewGame();
BOOL    AppEvt_DlgProc(  HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT AppEvt_PSWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);


//---------------------------------------------------------------------------
// App class
//---------------------------------------------------------------------------
class CApp : public ISpruuidsApp, public IOleComponent, public COleAuto
  {
public:
  // *** Constructor / Descructor ***
  static HRESULT CreateApp(HINSTANCE hinst);
  CApp(HINSTANCE hinst);
  ~CApp();

  // *** IUnknown methods ***
  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);
  inline IUnknown  *GetUnknown(void)  {return (ISpruuidsApp *)this;};
  inline IDispatch *GetDispatch(void) {return (ISpruuidsApp *)this;};

  // *** IDispatch methods ***
  DECLARE_STANDARD_DISPATCH();
  // Overrides required by COleAuto:
  virtual ITypeInfo **GetTinfoClsAddr(void) { return &m_ptinfoCls; };
  virtual ITypeInfo **GetTinfoIntAddr(void) { return &m_ptinfoInt; };
  virtual HRESULT GetTypeLibInfo(HINSTANCE *phinstOut, const GUID **pplibidOut, 
                                 SHORT *pwMajLibOut, SHORT *pwMinLibOut,
                                 const CLSID **ppclsidOut, const IID **ppiidOut,
                                 ITypeLib ***ppptlOut);
  virtual IDispatch *GetPrimary() {return this->GetDispatch(); };

  // *** SpruuidsApp methods ****
  STDMETHOD(get_Application)(ISpruuidsApp** lppaReturn);
  STDMETHOD(get_Parent)(ISpruuidsApp** lppaReturn);
  STDMETHOD(Quit)(void);
  STDMETHOD(get_Game)(IGame** lppaReturn);

  // *** IComponent methods ***
  STDMETHOD_(BOOL, FPreTranslateMessage)(MSG* pMsg);
  STDMETHOD_(void, OnEnterState)(ULONG uStateID, BOOL fEnter);
  STDMETHOD_(void, OnAppActivate)(BOOL fActive, DWORD dwOtherThreadID);
  STDMETHOD_(void, OnLoseActivation)(void);
  STDMETHOD_(BOOL, FDoIdle)(DWORD grfidlef);
  STDMETHOD_(BOOL, FContinueMessageLoop)(ULONG uReason, void* pvLoopData);
  STDMETHOD_(BOOL, FQueryTerminate)(BOOL fPromptUser);
  STDMETHOD_(void, Terminate)(void);

  // *** Public methods ***
  HRESULT MainMsgLoop(void);
  HRESULT LoadGame(void);
  void    CloseGame(void);
  void    CausePause(int p);
  HRESULT CheckTypeInfo(UINT itinfo);
  HRESULT Playback(void);

  // *** Public member variables ***
  class CMsgLoop *m_pmsgloop;
  class CGame    *m_pgame;
  HWND       m_hwndDlg;
  HWND       m_hwndPS;
  HWND       m_hwndStat;
  HWND       m_hwndAbout;
  HINSTANCE  m_hinst;
  DWORD      m_idcomp;
  BOOL       m_fRegisteredComp;
  ULONG      m_cmodal;
  BOOL       m_fQuit;
  ULONG      m_cref;
  ITypeInfo *m_ptinfoCls;   // This OLE Automation object's coclass   TypeInfo
  ITypeInfo *m_ptinfoInt;   // This OLE Automation object's interface TypeInfo

  // DEBUG info
  static HRESULT s_hr;
  #define SIG_App 'App '
  DECLARE_SIGNATURE(SIG_App);
  };

//--- EOF -------------------------------------------------------------------
