// Movelist.h  -- Maintain forward/back/etc goodies for Wcheck.

struct rBoardNode
{
    SQUARE b[SQRS_MAX];
    int iPlayerTurn;
    struct rBoardNode *prNextBoard;
    struct rBoardNode *prPrevBoard;
};

class CMoveList
{
  private:
    int m_iNumBoards;
    BOOL m_fClassInitialized;
    struct rBoardNode *m_prFirstBoard;
    struct rBoardNode *m_prCurrentBoard;
    struct rBoardNode *m_prCurrentSearchBoard;

  public:
    CMoveList();
    ~CMoveList();
    Init();
    BOOL NewMove(BOARD b, int iPlayerTurn);
    BOOL BackMove(BOARD b, int *piPlayerTurn);
    BOOL ForwardMove(BOARD b, int *piPlayerTurn);
    BOOL PurgeBoards();
    BOOL ClearBoards();
    BOARD GetFirstBoard(BOARD b, int *piPlayerTurn);
    BOARD GetNextBoard(BOARD b, int *piPlayerTurn);
};


