//---------------------------------------------------------------------------
// MsgLoop.h
//---------------------------------------------------------------------------
// (C) Copyright 1995-1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// In we need to track per Component.
//---------------------------------------------------------------------------
typedef struct tagCOMP
  {
  IOleComponent *pcomp;
  } COMP;

#define cCOMP     10
#define icompNIL  0xffffffff


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class CMsgLoop : public IOleComponentManager
  {
public:
  // *** Constructor / Destructor ***
  CMsgLoop(HWND hwnd);
  virtual ~CMsgLoop();

  // *** IUnknown methods ***
  STDMETHOD(QueryInterface)(REFIID riid, void **ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);

  // *** IOleComponentManager Methods
  STDMETHOD(QueryService)(REFGUID guidService, REFIID iid, void **ppvObj);
  STDMETHOD_(BOOL, FRegisterComponent)(IOleComponent *piComponent, const CMGRRINFO *pcrinfo, DWORD *pdwComponentID);
  STDMETHOD_(BOOL, FRevokeComponent)(DWORD dwComponentID);
  STDMETHOD_(BOOL, FUpdateComponentRegistration)(DWORD dwComponentID, const CMGRRINFO *pcrinfo);
  STDMETHOD_(void, OnComponentActivate)(DWORD dwComponentID);
  STDMETHOD_(BOOL, FSetTrackingComponent)(DWORD dwComponentID, BOOL fTrack);
  STDMETHOD_(void, OnComponentEnterState)(DWORD dwComponentID, ULONG uStateID, ULONG uContext, ULONG cpicmExclude, IOleComponentManager **rgpicmExclude, DWORD dwReserved);
  STDMETHOD_(BOOL, FOnComponentExitState)(DWORD dwComponentID, ULONG uStateID, ULONG uContext, ULONG cpicmExclude, IOleComponentManager **rgpicmExclude);
  STDMETHOD_(BOOL, FInState)(ULONG uStateID, void *pvoid);
  STDMETHOD_(BOOL, FContinueIdle)(void);
  STDMETHOD_(BOOL, FPushMessageLoop)(DWORD dwComponentID, ULONG uReason, void *pvLoopData);
  STDMETHOD_(BOOL, FCreateSubComponentManager)(IUnknown *piunkOuter, IUnknown *piunkServProv, REFIID riid, void **ppvObj);
  STDMETHOD_(BOOL, FGetParentComponentManager)(IOleComponentManager **ppicm);
  STDMETHOD_(BOOL, FGetActiveComponent)(DWORD dwReserved, IOleComponent **ppic);

  // *** Implementation of FPushMessageLoop from IOleComponentManager
  BOOL PumpMessage(DWORD icomp, ULONG uReason, void *pvLoopData);
  void ProcessMessage(MSG *pmsg);
  void MessageLoop(DWORD icomp, ULONG uReason, void *pvLoopData);
  void DoIdleProcessing(void);
  BOOL DoIdle(void);

  // *** Publicly available state ***
  COMP   m_rgcomp[cCOMP]; // Array of components for our compmgr
  DWORD  m_icompActive;
  BOOL   m_fInState;
  DWORD  m_icompState;
  ULONG  m_uStateID;
  BOOL   m_fScrptReset;
  BOOL   m_fQuitting;
  HWND   m_hwnd;
  HACCEL m_haccel;

private:
  ULONG m_cref;
  ULONG m_cMsgLoop;
  DWORD m_icompMsgLoop;

  // DEBUG info
  #define SIG_MsgLoop 'MsgL'
  DECLARE_SIGNATURE(SIG_MsgLoop);
  };

//--- EOF -------------------------------------------------------------------
