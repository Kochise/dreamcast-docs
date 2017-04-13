//---------------------------------------------------------------------------
// Game.h
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
// Forward Delcares
//---------------------------------------------------------------------------
class CDisplay;
class CSpriteClass;
class CSprite;
class CScore;
class CGameOA;


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
DEFINE_GUID(IID_IGameSubObjects, 0xb54f3741, 0x5b07, 0x11cf, 0xa4, 0xb0, 0x0, 0xaa, 0x0, 0x4a, 0x55, 0xe8);


//---------------------------------------------------------------------------
// the CGame class
//---------------------------------------------------------------------------
class CGame : public COleAuto, 
              public IActiveScriptSite, public IActiveScriptSiteWindow,
              public IProvideMultipleClassInfo
  {
  friend class CGameOA;

public:
  static HRESULT CGame::CreateGame(HINSTANCE hinst, HWND hwnd, HWND hwndPS, HWND hwndStat,
                                   IOleComponentManager *pcm, CGame **ppgameOut);
  CGame(HINSTANCE hinst, HWND hwnd, HWND hwndPS, HWND hwndStat, IOleComponentManager *pcm);
  ~CGame();
  void Close(void);

  // *** IUnknown methods ***
  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);
  inline IUnknown  *GetUnknown(void)  {return (IDispatch *)(COleAuto *)this;};
  inline IDispatch *GetDispatch(void) {return (IDispatch *)(COleAuto *)this;};

  // *** IDispatch methods ***
  STDMETHOD(GetTypeInfoCount)(UINT *pctinfo)
    { return COleAuto::GetTypeInfoCount(pctinfo); };
  STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo **pptinfoOut)
    { return COleAuto::GetTypeInfo(itinfo, lcid, pptinfoOut); };
  STDMETHOD(GetIDsOfNames)(REFIID iid, OLECHAR **rgszNames, UINT cnames, LCID lcid, DISPID *rgdispid);
  STDMETHOD(Invoke)(DISPID dispid, REFIID iid, LCID lcid, WORD wFlags, DISPPARAMS *pdispparams, VARIANT *pVarResult, EXCEPINFO *pexcepinfo, UINT *puArgErr);

  // Override required by COleAuto:
  virtual ITypeInfo **GetTinfoClsAddr(void) { return &g_ptinfoClsGame; };
  virtual ITypeInfo **GetTinfoIntAddr(void) { return &g_ptinfoIntGame; };
  virtual HRESULT GetTypeLibInfo(HINSTANCE *phinstOut, const GUID **pplibidOut, 
                                 SHORT *pwMajLibOut, SHORT *pwMinLibOut,
                                 const CLSID **ppclsidOut, const IID **ppiidOut,
                                 ITypeLib ***ppptlOut);
  virtual IDispatch *GetPrimary() {return this->GetDispatch(); };

  // *** IProvideClassInfo methods ***
  STDMETHOD(GetClassInfo)(ITypeInfo** pptinfoOut);
  // *** IProvideClassInfo2 methods ***
  STDMETHOD(GetGUID)(DWORD dwGuidKind, GUID* pGUID);
  // *** IProvideMultipleClassInfo methods ***
  STDMETHOD(GetMultiTypeInfoCount)(ULONG *pcti);
  STDMETHOD(GetInfoOfIndex)(ULONG iti, DWORD dwFlags, ITypeInfo** pptiCoClass, DWORD* pdwTIFlags, ULONG* pcdispidReserved, IID* piidPrimary, IID* piidSource);

// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
  // *** IActiveScriptSite methods ***
  STDMETHOD(GetLCID)(LCID *plcid);
  STDMETHOD(GetItemInfo)(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown **ppiunkItem, ITypeInfo **ppti);
  STDMETHOD(GetDocVersionString)(BSTR *pszVersion);
  STDMETHOD(RequestItems)(void);
  STDMETHOD(RequestTypeLibs)(void);
  STDMETHOD(OnScriptTerminate)(const VARIANT *pvarResult, const EXCEPINFO *pexcepinfo);
  STDMETHOD(OnStateChange)(SCRIPTSTATE ssScriptState);
  STDMETHOD(OnScriptError)(IActiveScriptError *pscripterror);
  STDMETHOD(OnEnterScript)(void);
  STDMETHOD(OnLeaveScript)(void);

  // *** IActiveScriptSiteWindow methods ***
  STDMETHOD(GetWindow)(HWND *phwnd);
  STDMETHOD(EnableModeless)(BOOL fEnable);
// #####  END  ACTIVEX SCRIPTING SUPPORT #####

  class CGameOA *m_pgameoa;

  // *** General Methods ***
  BOOL    DlgProc(  HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
  LRESULT PSWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
  void    NewLevel(void);
  void    NewGame(void);
  BOOL    Pause(int pause);
  BOOL    FQueryTerminate(BOOL fPromptUser);
  void    GameOver(void);
  HRESULT ParseFile(char *pszFileName, LPCOLESTR pstrItemName);
  HRESULT CreateScriptEngine(LPCOLESTR pstrItemName);
  HRESULT BuildTypeInfo(void);

  // *** Member Variables ***
  HINSTANCE  m_hinst;
  HWND       m_hwndDlg;
  HWND       m_hwndPS;
  HWND       m_hwndStat;
  CScore    *m_pscore;
  CDisplay  *m_pdisp;
  UINT       m_cref;
  VARIANT    m_varTag;
  IOleComponentManager *m_pcm;
// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
  IActiveScript        *m_ps;
  IActiveScriptParse   *m_psp;
// #####  END  ACTIVEX SCRIPTING SUPPORT #####

  CLSID          m_clsidEngine;
  static char   *s_pszError;

  // Sub-Object support
#define csubobjMAX    30
  int           m_csubobj;
  LPOLESTR      m_rgpwszSubObjs[csubobjMAX];   // Should really dynamically allocate this array
  IDispatch    *m_rgpdispSubObjs[csubobjMAX];  // Should really dynamically allocate this array
  CSpriteClass *m_rgpsc[csubobjMAX];
  GUID          m_libidSubObj;
  CLSID         m_clsidSubObj;
  IID           m_iidSubObj;

  // These reset every new game
  BOOL m_fPaused:1;
  BOOL m_fShipDead:1;
  BOOL m_fShipRestart:1;
  BOOL m_fGameOver:1;

  // DEBUG info
  static HRESULT s_hr;
  #define SIG_Game 'Game'
  DECLARE_SIGNATURE(SIG_Game);
  };


//---------------------------------------------------------------------------
// the CGameOA class; Ole automation implementation for static members
// of the IGame interface.
//---------------------------------------------------------------------------
class CGameOA : public IGame, public COleAuto, public IProvideClassInfo,
                public IConnectionPointContainer
  {
public:
  // *** Constructor / Destructor ***
  CGameOA::CGameOA(CGame *);

  // *** IUnknown methods ***
  STDMETHOD(QueryInterface)(REFIID iid, void** ppvObj) {return m_pgame->QueryInterface(iid, ppvObj);};
  STDMETHOD_(ULONG, AddRef) (void)                     {return m_pgame->AddRef();};
  STDMETHOD_(ULONG, Release)(void)                     {return m_pgame->Release();};
  inline IDispatch *GetDispatch(void) {return (IGame *)this;};

  // *** IDispatch methods ***
  DECLARE_STANDARD_DISPATCH();
  // Override required by COleAuto:
  virtual ITypeInfo **GetTinfoClsAddr(void) { return &g_ptinfoClsGameOA; };
  virtual ITypeInfo **GetTinfoIntAddr(void) { return &g_ptinfoIntGameOA; };
  virtual HRESULT GetTypeLibInfo(HINSTANCE *phinstOut, const GUID **pplibidOut, 
                                 SHORT *pwMajLibOut, SHORT *pwMinLibOut,
                                 const CLSID **ppclsidOut, const IID **ppiidOut,
                                 ITypeLib ***ppptlOut);
  virtual IDispatch *GetPrimary() {return this->GetDispatch(); };

  // *** IProvideClassInfo methods ***
  STDMETHOD(GetClassInfo)(ITypeInfo** pptinfoOut);

  // *** IConnectionPointContainer methods ***
  STDMETHOD(EnumConnectionPoints)(LPENUMCONNECTIONPOINTS* ppEnum);
  STDMETHOD(FindConnectionPoint)(REFIID iid, LPCONNECTIONPOINT* ppCP);

  // *** IGame methods ***
  STDMETHOD(get_Caption)(BSTR* lpbstrReturn);
  STDMETHOD(put_Caption)(BSTR bstr);
  STDMETHOD(get_Application)(ISpruuidsApp** lppaReturn);
  STDMETHOD(get_Parent)(ISpruuidsApp** lppaReturn);
  STDMETHOD(StartGame)(void);
  STDMETHOD(EndGame)(void);
  STDMETHOD(RemoveAllSprites)(void);
  STDMETHOD(NextLevel)(void);
  STDMETHOD(Refresh)(void);
  STDMETHOD(AddScore)(int val);
  STDMETHOD(StdBorderBounce)(ISprite* pspr, int brd);
  STDMETHOD(StdBorderWrap)(  ISprite* pspr, int brd);
  STDMETHOD(StdInitRand)(ISprite* pspr, VARIANT user);
  STDMETHOD(StdInitEdge)(ISprite* pspr, VARIANT user);
  STDMETHOD(get_Paused)(VARIANT_BOOL* pRet);
  STDMETHOD(put_Paused)(VARIANT_BOOL val);
  STDMETHOD(get_Width)(int* pRet);
  STDMETHOD(put_Width)(int val);
  STDMETHOD(get_Height)(int* pRet);
  STDMETHOD(put_Height)(int val);
  STDMETHOD(get_BackColor)(long* pRet);
  STDMETHOD(put_BackColor)(long val);
  STDMETHOD(get_Score)(int* pRet);
  STDMETHOD(put_Score)(int val);
  STDMETHOD(get_Level)(int* pRet);
  STDMETHOD(put_Level)(int val);
  STDMETHOD(get_ShipCount)(int* pRet);
  STDMETHOD(put_ShipCount)(int val);
  STDMETHOD(get_ScoreFirst1Up)(int* pRet);
  STDMETHOD(put_ScoreFirst1Up)(int val);
  STDMETHOD(get_ScoreSecond1Up)(int* pRet);
  STDMETHOD(put_ScoreSecond1Up)(int val);
  STDMETHOD(get_DScoreNext1Up)(int* pRet);
  STDMETHOD(put_DScoreNext1Up)(int val);
  STDMETHOD(get_ShipsStart)(int* pRet);
  STDMETHOD(put_ShipsStart)(int val);
  STDMETHOD(get_Tag)(VARIANT* pRet);
  STDMETHOD(put_Tag)(VARIANT val);
  STDMETHOD(get_StatusText)(BSTR* lpbstrReturn);
  STDMETHOD(put_StatusText)(BSTR bstr);

  class XCP : public IConnectionPoint
    {
    inline CGameOA *PGAMEOA(void) { return ((CGameOA *)((char *)this - (char *)&(((CGameOA *)0)->m_cp))); }

  public:
    XCP();
    void Close(void);

    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)(REFIID iid, void** ppvObjOut);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void);
    inline IUnknown *GetUnknown(void) {return (IConnectionPoint *)this;};

    // *** IConnectionPoint methods ***
    STDMETHOD(GetConnectionInterface)(IID* piid);
    STDMETHOD(GetConnectionPointContainer)(IConnectionPointContainer** ppCPC);
    STDMETHOD(Advise)(IUnknown* punkSink, DWORD* pdwCookie);
    STDMETHOD(Unadvise)(DWORD dwCookie);
    STDMETHOD(EnumConnections)(LPENUMCONNECTIONS* ppEnum);

    // *** Member Variables ***
    ULONG     m_cref;
#define GAME_cADVISE 5
    IDispatch *m_rgpdisp[GAME_cADVISE];     // Array of pdisps to call.
    } m_cp;

  // *** Event Methods ***
  void FireNewGame(void);
  void FireNewLevel(void);
  void FireNewShip(void);
  static void FireCollide(CSprite *psprMoved, CSprite *psprHit, int);
  void FireTick(void);
  void FireKeyDown(int vk);
  void FireKeyPress(int ascii);
  void FireKeyUp(int vk);
  void FireMouseMove(int x, int y, long mk);
  void FireMouseDown(int x, int y, long mk, long button);
  void FireMouseUp(  int x, int y, long mk, long button);

  // *** Member Variable ***
  CGame *m_pgame;
  };

//--- EOF -------------------------------------------------------------------
