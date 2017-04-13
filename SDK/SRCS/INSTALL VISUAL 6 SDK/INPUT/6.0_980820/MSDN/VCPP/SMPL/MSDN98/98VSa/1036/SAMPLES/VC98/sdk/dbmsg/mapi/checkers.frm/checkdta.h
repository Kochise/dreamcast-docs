// Some more defines

#define PLAYER1         BLACK
#define PLAYER2         RED

// Game type definitions

#define GAME_CHECKERS   0       
#define GAME_GIVEAWAY   1

// Cursor states

#define UNDEFINED_CURSOR    -1
#define NORMAL_CURSOR       1
#define RESIZE_CURSOR       2

#define RESIZE_RANGE        10      // How far from bottom right should resize
                                    // cursor be shown.

// Data structures for Checkers.

struct rGameStateRec
{
    int iPlayerTurn;                // Who's turn
    BOOL fPlayAsForm;               // If we are currently a form
    BOOL fInitDone;                 // Game initialization over (when to use timer).
    BOOL fContinuable;              // Is the turn continuable?
    BOOL fSetupMode;                // Game in setup mode? Need for button processing
    BOOL fThinking;                 // Is the computer thinking?
    BOOL fPaused;                   // Is the game paused?
    BOOL fGameInProgress;           // Did the game start? How to react to "File:New"
    BOOL fLMouseButtonDown;         // Is the left mouse button currently down?
    BOOL fRMouseButtonDown;         // Is the right mouse button currently down?
    BOOL fMoveInProgress;           // Is the user in the middle of a move?
    BOOL fComputerBusy;             // Is the computer thinking?
    BOOL fGameOver;                 // Is the game over?
    BOOL fMouseResizeInProgress;    // Is the user resizing the board with the mouse?
    int iCursorState;               // What state is the cursor in (resize, normal?)
};

struct rPlayerRec
{
    int iPlayerType;                // (ENUM) Human/Computer/Network
    int iUseOpeningBook;            // (BOOL) Use the opening-book moves
    int iMemPositions;              // (BOOL) Use memorized positions?
    int iUseMoveTheory;             // (BOOL) Use move theory?
    int iUseMoveShuffling;          // (BOOL) Use move shuffling
    int iUseEqualMoveSkipping;      // (BOOL) Use Equal move skipping
    long lUseGoodMoveSkipping;      // (LONG) Use Good move skipping

    int iMaxRecursionDepth;             // (LONG) Max recursion depth
    int iUseAlphaBetaPruning;           // (BOOL) Use alpha-beta pruning
    long lAlphaPruningOriginalDepth;    // (LONG) Alpha pruning original depth
    long lAlphaPruningWidth;            // (LONG) Alpha pruning width
};

struct rCheckConfigRec
{
    int iGameType;                      // (INT) enum game type (Checkers/FoxGoose)
    int iMustJump;                      // (BOOL) Player must jump when available?
    int iBoardFlipped;                  // (BOOL) Board flipped?
    int iSquareSize;                    // (INT) Size of board square
    int iSetupPurgeBoards;              // (BOOL) Purge boards after setup?
    int iMaxMoves;

    struct rPlayerRec   rPlayer[3];       // Config info for players
};
