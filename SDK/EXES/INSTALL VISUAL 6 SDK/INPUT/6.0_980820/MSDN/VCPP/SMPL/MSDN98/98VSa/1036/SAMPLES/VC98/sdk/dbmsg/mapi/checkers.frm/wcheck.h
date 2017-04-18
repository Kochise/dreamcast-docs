//---[ Global defines ]----------------------------------------------------

#define MAX_SQUARE_SIZE     100
#define MIN_SQUARE_SIZE     15
#define SQUARE_GRANULARITY  2

#define BOARD_TOP       10
#define BOARD_LEFT      10

#define RACK_LEFT       10      // * Square size
#define RACK_TOP        2       // * Square size

#define GAME_WON        0
#define GAME_PLAYABLE   1
#define GAME_DRAWN      2

#define INI_NAME        "WCHECK.INI"
#define APP_NAME        "Checkers"
#define ID_TIMER            1
#define TIMER_GRANULARITY   500

#define HUMAN_PLAYER    0
#define COMPUTER_PLAYER 1
#define NETWORK_PLAYER  2
                         
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK CheckersWndProc        (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About          (HWND, UINT, WPARAM, LPARAM);
void NEAR PASCAL FillBoard(BYTE *pb, HDC hDC);
void DrawBoard(BOARD b);
void NEAR PASCAL CheckGenPieces(HDC hDC);
void NEAR PASCAL CheckCreate();
void NEAR PASCAL CheckPaint(BOARD b, HDC hDC);
BOOL CenterWindow (HWND hwndChild, HWND hwndParent);
void NEAR PASCAL CheckMouseMove(POINT point);
void NEAR PASCAL CheckChar(WORD code);
void NEAR PASCAL CheckMouseClick(POINT point);
void NEAR PASCAL UpdateCursor(HWND hwnd);
void inline vTranslateCurPosToSquare(POINT pntCur, int *pix, int *piy);
void inline vTranslateUIToEngineSquare(int *piEngine, int iX, int iY);
void inline vTranslateEngineToUISquare(int iEngine, int *piX, int *piY);
BOOL fValidPlayerPiece(BOARD b, int ix, int iy);
void vClearMovingPiece(HDC hDC, int iX, int iY);
VOID WriteINI ();
VOID ReadINI ();
long WINAPI ComputerMove();
void _inline DisplayGameOver(HWND hWnd, int iPlayerTurn);
void _inline DisplayGameDrawn(HWND hWnd, int iPlayerTurn);


BOOL FAR PASCAL ConfigDialogProc (HWND hDlg,
                                        WORD wMsgID,
                                        WPARAM wParam,
                                        LPARAM lParam);
BOOL FAR PASCAL PlayersDialogProc (HWND hDlg,
                                        WORD wMsgID,
                                        WPARAM wParam,
                                        LPARAM lParam);
BOOL FAR PASCAL DebugConfigDialogProc (HWND hDlg,
                                        WORD wMsgID,
                                        WPARAM wParam,
                                        LPARAM lParam);
BOOL FAR PASCAL ComputerSettingsDialogProc (HWND hDlg,
                                        WORD wMsgID,
                                        WPARAM wParam,
                                        LPARAM lParam);

int FAR PASCAL PlayerTurnDialogProc (HWND hDlg,
                                        WORD wMsgID,
                                        WPARAM wParam,
                                        LPARAM lParam);

void MessageInt(char *pszText, int iValue);
void inline NormalLButtonUp(HWND hWnd, UINT keyFlags, int x, int y);
void inline SetupLButtonUp(HWND hWnd, UINT keyFlags, int x, int y);
void inline SetupRButtonUp(HWND hWnd, UINT keyFlags, int x, int y);
void inline NormalLButtonDown(HWND hWnd, UINT keyFlags, int x, int y);
void inline SetupLButtonDown(HWND hWnd, UINT keyFlags, int x, int y);
void inline SetupRButtonDown(HWND hWnd, UINT keyFlags, int x, int y);
