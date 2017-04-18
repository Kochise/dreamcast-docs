//---------------------------------------------------------------------------
// Spr.h
//---------------------------------------------------------------------------
// Sprite handler
//---------------------------------------------------------------------------
// (C) Copyright 1992-1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------
#define SPR_brdINLEFT       0x0001
#define SPR_brdINTOP        0x0002
#define SPR_brdINRIGHT      0x0004
#define SPR_brdINBOTTOM     0x0008
#define SPR_brdIN           0x000F
#define SPR_brdOUTLEFT      0x0010
#define SPR_brdOUTTOP       0x0020
#define SPR_brdOUTRIGHT     0x0040
#define SPR_brdOUTBOTTOM    0x0080
#define SPR_brdOUT          0x00F0
#define SPR_brdALL          0x00FF
#define SPR_brdLEFT         0x0011
#define SPR_brdTOP          0x0022
#define SPR_brdRIGHT        0x0044
#define SPR_brdBOTTOM       0x0088

#define MAS_X               0x0001
#define MAS_Y               0x0002
#define MAS_POS             0x0004
#define MAS_VEL             0x0008
#define MAS_ACCEL           0x0010
#define MAS_RECIPDIST       0x0020
#define MAS_REMEMBER        0x0080


//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------
#define tickOFSEC(sec)              ((int)(20*(sec)))
#define PuserDEREF(type, pspr)      ((type)((pspr)->m_bUser))
#define SPRITEOFI(psprite)          ((CSprite *)(void *)(psprite))


//---------------------------------------------------------------------------
// Typedefs
//---------------------------------------------------------------------------
class CDisplay;
class CSpriteClass;
class CSprite;
typedef UINT BRD;
typedef WORD IDBMP;
typedef struct tagIMG *PIMG;
typedef void (*PFNCOLLIDE)(CSprite *, CSprite *, int);
#define FLOAT float
#define FULLOFFLOAT(r8)   ((long)((r8) * (FLOAT)0x10000))
#define FLOATOFFULL(i4)   ((FLOAT)(i4) / (FLOAT)0x10000)
#define FIXED(full, sub, super) \
  union                         \
    {                           \
    long full;                  \
    struct                      \
      {                         \
      USHORT sub;               \
      SHORT super;              \
      };                        \
    }


//---------------------------------------------------------------------------
// Image description
//---------------------------------------------------------------------------
typedef struct tagIMG
  {
  int   iimgNext;
  int   x,  y;
  int   cx, cy;
  PIMG  pimgNext;
  } IMG;
#define iimgNONE      (-1)
#define iimgREMOVE    (-2)


//---------------------------------------------------------------------------
// Display surface for sprites
//---------------------------------------------------------------------------
class CDisplay
  {
  friend class CSprite;
  friend class CSpriteClass;

public:
  CDisplay(HINSTANCE hinst, HWND hwnd, HDC hdc, IUnknown *pparent, PFNCOLLIDE pfncollide, int cimg, PIMG prgimg, UINT idbmp);
  ~CDisplay(void);

  void DestroyAll(void);
  void Timer(void);
  void Paint(HDC hdc);
  void Refresh(void);
  void SetBackColor(COLORREF c);
  void FireCollide(CSprite *psprLowId, CSprite *psprHighId, int);

  HINSTANCE  m_hinst;
  HWND       m_hwnd;
  HDC        m_hdc;
  int        m_cx, m_cy;
  PFNCOLLIDE m_pfnCollide;    // Routine to handle spr collisions
  CSprite   *m_psprFirst;
  CSprite   *m_psprLast;
  IUnknown  *m_punkParent;    // For get_Parent() on SpriteClass
  COLORREF   m_colorBack;
  HBRUSH    m_hbrushBack;

protected:
  int       m_cimg;
  int       m_csc;
  PIMG      m_prgimg;
  IDBMP     m_idbmp;
  HBITMAP   m_hbmp;

  // DEBUG info
  #define SIG_Display 'Disp'
  DECLARE_SIGNATURE(SIG_Display);
  };


//---------------------------------------------------------------------------
// Class description of different types of sprites
//---------------------------------------------------------------------------
class CSpriteClass : public ISpriteClass, public COleAuto,
                     public IProvideClassInfo, public IConnectionPointContainer
  {
  friend class CDisplay;
  friend class CSprite;

public:
  // *** Constructor/Destructor methods ***
  static HRESULT Create(CDisplay *pdisp, CSpriteClass **ppscOut);
  CSpriteClass(CDisplay *pdisp);
  ~CSpriteClass(void);
  void Close(void);

  // *** Event methods ***
  void FireInit(  CSprite *pspr, VARIANT *pvarUser);
  void FireTick(  CSprite *pspr);
  void FireBorder(CSprite *pspr, BRD brd);
  void FireTerm(  CSprite *pspr);
  void FireLastTerm(void);

  // *** IUnknown methods ***
  STDMETHOD(QueryInterface)(REFIID iid, void** ppvObjOut);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);
  inline IUnknown  *GetUnknown(void)  {return (ISpriteClass *)this;};
  inline IDispatch *GetDispatch(void) {return (ISpriteClass *)this;};

  // *** IDispatch methods ***
  DECLARE_STANDARD_DISPATCH();
  // Override required by COleAuto:
  virtual ITypeInfo **GetTinfoClsAddr(void) { return &g_ptinfoClsSpriteClass; };
  virtual ITypeInfo **GetTinfoIntAddr(void) { return &g_ptinfoIntSpriteClass; };
  virtual HRESULT GetTypeLibInfo(HINSTANCE *phinstOut, const GUID **pplibidOut, 
                                 SHORT *pwMajLibOut, SHORT *pwMinLibOut,
                                 const CLSID **ppclsidOut, const IID **ppiidOut,
                                 ITypeLib ***ppptlOut);
  virtual IDispatch *GetPrimary() {return this->GetDispatch(); };

  // *** ISpriteClass methods ***
  STDMETHOD(get_Application)(ISpruuidsApp** ppRet);
  STDMETHOD(get_Parent)(IGame** ppRet);
  STDMETHOD(CreateSprite)(int x, int y, VARIANT arg, ISprite** ppRet);
  STDMETHOD(get_Tag)(VARIANT* pRet);
  STDMETHOD(put_Tag)(VARIANT val);
  STDMETHOD(get_Image)(int* pRet);
  STDMETHOD(put_Image)(int val);
  STDMETHOD(get_Border)(int* pRet);
  STDMETHOD(put_Border)(int val);
  STDMETHOD(get_Collide)(int* pRet);
  STDMETHOD(put_Collide)(int val);
  STDMETHOD(get_MaximumVelocity)(float* pRet);
  STDMETHOD(put_MaximumVelocity)(float val);
  STDMETHOD(get_Friction)(float* pRet);
  STDMETHOD(put_Friction)(float val);
  STDMETHOD(get_MaximumAcceleration)(float* pRet);
  STDMETHOD(put_MaximumAcceleration)(float val);
  STDMETHOD(get_AccelerationFriction)(float* pRet);
  STDMETHOD(put_AccelerationFriction)(float val);
  STDMETHOD(get_SpriteCount)(int* pRet);

  // *** IProvideClassInfo methods ***
  STDMETHOD(GetClassInfo)(ITypeInfo** pptinfoOut);
  // *** IProvideClassInfo2 methods ***
  STDMETHOD(GetGUID)(DWORD dwGuidKind, GUID* pGUID);

  // *** IConnectionPointContainer methods ***
  STDMETHOD(EnumConnectionPoints)(LPENUMCONNECTIONPOINTS* ppEnum);
  STDMETHOD(FindConnectionPoint)(REFIID iid, LPCONNECTIONPOINT* ppCP);

  class XCP : public IConnectionPoint
    {
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
#define SC_cADVISE 5
    IDispatch *m_rgpdisp[SC_cADVISE];     // Array of pdisps to call.
    } m_cp;

  // *** Member Variables ***
  CDisplay *m_pdisp;
  int       m_id;
  int       m_brd;         // Mask indicates which borders to check collision with
  int       m_maskCollide; // Mask indicates which other sprites can collide with
  int       m_iimg;
  int       m_cspr;
  VARIANT   m_varTag;
  FLOAT     m_friction;
  FLOAT     m_frictionAccel;
  BOOL      m_fFrictionAccel;
  ULONG     m_cref;
  FIXED(    m_vFullMax, m_vSubMax, m_vMax);
  FIXED(    m_aFullMax, m_aSubMax, m_aMax);

private:
  // DEBUG info
  static HRESULT s_hr;
  #define SIG_SpriteClass 'SCls'
  DECLARE_SIGNATURE(SIG_SpriteClass);
  };


//---------------------------------------------------------------------------
// Definition of sprite
//---------------------------------------------------------------------------
class CSprite : ISprite, COleAuto
  {
  friend class CDisplay;
  friend class CSpriteClass;

public:
  // *** Constructor/Destructor methods ***
  CSprite(CSpriteClass *psc, int x, int y, CSprite *psprPrev, VARIANT *pvarUser);
  ~CSprite();

  // *** General Routines ***
  CSprite *PsprMutate(CSpriteClass *psc, VARIANT *pvarUser);
  void MarkFree();
  BOOL MoveToFull(long xFull,  long yFull,  BOOL fCollide);
  BOOL MoveByFull(long dxFull, long dyFull, BOOL fCollide);
  BOOL DoMoveAt(CSprite *psprAt, float dMax, float scale, long flags, BOOL fCollide);

  // *** IUnknown methods ***
  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj);
  STDMETHOD_(ULONG, AddRef)(void);
  STDMETHOD_(ULONG, Release)(void);
  inline IUnknown  *GetUnknown(void)  {return (ISprite *)this;};
  inline IDispatch *GetDispatch(void) {return (ISprite *)this;};

  // *** IDispatch methods ***
  DECLARE_STANDARD_DISPATCH();
  // Override required by COleAuto:
  virtual ITypeInfo **GetTinfoClsAddr(void) { return &g_ptinfoClsSprite; };
  virtual ITypeInfo **GetTinfoIntAddr(void) { return &g_ptinfoIntSprite; };
  virtual HRESULT GetTypeLibInfo(HINSTANCE *phinstOut, const GUID **pplibidOut, 
                                 SHORT *pwMajLibOut, SHORT *pwMinLibOut,
                                 const CLSID **ppclsidOut, const IID **ppiidOut,
                                 ITypeLib ***ppptlOut);
  virtual IDispatch *GetPrimary() {return this->GetDispatch(); };

  // *** ISprite methods ***
  STDMETHOD(get_Application)(ISpruuidsApp** ppRet);
  STDMETHOD(get_Parent)(ISpriteClass** ppRet);
  STDMETHOD(MoveTo)(FLOAT x, FLOAT y);
  STDMETHOD(MoveBy)(FLOAT dx, FLOAT dy);
  STDMETHOD(MoveAtSprite)(ISprite *sprite, FLOAT dMax, FLOAT scale, long flags);
  STDMETHOD(Remove)(void);
  STDMETHOD(Refresh)(void);
  STDMETHOD(IgnoreMove)(void);
  STDMETHOD(get_Left)(FLOAT* pRet);
  STDMETHOD(put_Left)(FLOAT val);
  STDMETHOD(get_Top)(FLOAT* pRet);
  STDMETHOD(put_Top)(FLOAT val);
  STDMETHOD(get_Vx)(FLOAT* pRet);
  STDMETHOD(put_Vx)(FLOAT val);
  STDMETHOD(get_Vy)(FLOAT* pRet);
  STDMETHOD(put_Vy)(FLOAT val);
  STDMETHOD(get_Ax)(FLOAT* pRet);
  STDMETHOD(put_Ax)(FLOAT val);
  STDMETHOD(get_Ay)(FLOAT* pRet);
  STDMETHOD(put_Ay)(FLOAT val);
  STDMETHOD(get_FrictionX)(FLOAT* pRet);
  STDMETHOD(put_FrictionX)(FLOAT val);
  STDMETHOD(get_FrictionY)(FLOAT* pRet);
  STDMETHOD(put_FrictionY)(FLOAT val);
  STDMETHOD(get_Image)(int* pRet);
  STDMETHOD(put_Image)(int val);
  STDMETHOD(get_TickMove)(int* pRet);
  STDMETHOD(put_TickMove)(int val);
  STDMETHOD(get_TickEvent)(int* pRet);
  STDMETHOD(put_TickEvent)(int val);
  STDMETHOD(get_Visible)(VARIANT_BOOL* pRet);
  STDMETHOD(put_Visible)(VARIANT_BOOL val);
  STDMETHOD(get_Tag)(VARIANT* pRet);
  STDMETHOD(put_Tag)(VARIANT val);
  STDMETHOD(get_Width)(int* pRet);
  STDMETHOD(get_Height)(int* pRet);

  // *** Member Variables ***
  CDisplay     *m_pdisp;
  CSpriteClass *m_psc;
  CSprite      *m_psprNext;
  CSprite      *m_psprPrev;
  FIXED(       m_xFull,  m_xSub,  m_x);
  FIXED(       m_yFull,  m_ySub,  m_y);
  FIXED(       m_vxFull, m_vxSub, m_vx);
  FIXED(       m_vyFull, m_vySub, m_vy);
  FIXED(       m_axFull, m_axSub, m_ax);
  FIXED(       m_ayFull, m_aySub, m_ay);
  BOOL         m_fFriction;
  FLOAT        m_fx;    // Friction
  FLOAT        m_fy;
  long         m_tickEvt, m_tickEvtMax, m_tickMove, m_tickMoveMax;
  int          m_iimg;
  PIMG         m_pimg;
  VARIANT      m_varTag;

  // Support for MoveAtSprite()
  CSprite     *m_psprAt;
  float        m_dMaxAt;
  float        m_scaleAt;
  long         m_flagsAt;


protected:
  // *** Internal Routines ***
  BOOL _FDraw(BOOL fCollide);
  void _Erase();
  void _Link();
  void _Unlink(BOOL fFireEvt);

  // *** Member Variables ***
  BOOL    m_fNeedRefresh:1;
  BOOL    m_fFree:1;
  BOOL    m_fIgnoreMove:1;
  BOOL    m_fLinked:1;
  BOOL    m_fHidden;            // 2 = Implicitly hidden for _Init event
  ULONG   m_cref;

  // DEBUG info
  #define SIG_Sprite 'Spr '
  DECLARE_SIGNATURE(SIG_Sprite);
  };

//--- EOF -------------------------------------------------------------------
