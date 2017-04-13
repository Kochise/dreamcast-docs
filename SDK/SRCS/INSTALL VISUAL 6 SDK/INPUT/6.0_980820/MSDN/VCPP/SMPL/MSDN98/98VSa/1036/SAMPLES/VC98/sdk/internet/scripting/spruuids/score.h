//---------------------------------------------------------------------------
// Score.h
//---------------------------------------------------------------------------
// Score object to track score, # lives, level.
//---------------------------------------------------------------------------
// (C) Copyright 1992-1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Score class
//---------------------------------------------------------------------------
class CScore
  {
public:
  // *** Constructor / Destructor ***
  static HRESULT CreateScore(HINSTANCE hinst, HWND hwnd, HWND hwndPS, HWND hwndStat,
                             long scoreFirst1Up, long scoreSecond1Up, long dscoreNext1Up,
                             int cship, WORD idbmpShip, WORD idbmpPlus,
                             CScore **ppscoreOut);
  CScore(HINSTANCE hinst, HWND hwnd, HWND hwndPS, HWND hwndStat, long scoreSecond1Up, long scoreFirst1Up, long dscoreNext1Up, int cship, WORD idbmpShip, WORD idbmpPlus);
  ~CScore();

  // *** Public methods ***
  void NewGame(void);
  void Add(long d);
  void Paint(HDC hdc);
  void SetStatusText(const char *pszText);
  void Size(int cx, int cy);

  // *** Public accessor methods ***
  inline long GetScore(void)      {return m_score;};
  inline void SetScore(int s)     {m_score = s;   InvalidateRect(m_hwnd, &m_rectScore, TRUE);};
  inline long GetLevel(void)      {return m_lvl;};
  inline long GetCShip(void)      {return m_cship;};
  inline void SetLevel(int lvl)   {m_lvl = lvl;   InvalidateRect(m_hwnd, &m_rectLvl,  TRUE);};
  inline void NextLevel(void)     {m_lvl++;       InvalidateRect(m_hwnd, &m_rectLvl,  TRUE);};
  inline void SetCShip(int cship) {m_cship=cship; InvalidateRect(m_hwnd, &m_rectShip, TRUE);};
  inline void ShipKilled(void)    {m_cship--;     InvalidateRect(m_hwnd, &m_rectShip, TRUE);};
  inline int  GetSize(void)       {return m_cyMax;};

  // Public members
  long      m_scoreFirst1Up;
  long      m_scoreSecond1Up;
  long      m_dscoreNext1Up;
  short     m_cshipStart;
  long      m_scoreNext1Up; // Inits to m_scoreFirst1Up

private:
  // *** Private member variables ***
  // Reset at NewGame()
  long      m_score;        // Inits to 0
  short     m_cship;        // Inits to m_cshipStart
  short     m_lvl;          // Inits to 1

  // Static state passed into contructor
  HINSTANCE m_hinst;
  HWND      m_hwnd;
  HWND      m_hwndPS;
  HWND      m_hwndStat;

  // State calculated from static state
  RECT      m_rectScore;
  RECT      m_rectShip;
  RECT      m_rectLvl;
  HBITMAP   m_hbmpShip;
  HBITMAP   m_hbmpPlus;
  int       m_cyMax,  m_cyStat;
  int       m_cxShip, m_cyShip;
  int       m_cxPlus, m_cyPlus;

  // Set if constructor fails
  static HRESULT s_hr;

  // DEBUG info
  #define SIG_Score 'Scor'
  DECLARE_SIGNATURE(SIG_Score);
  };

//--- EOF -------------------------------------------------------------------
