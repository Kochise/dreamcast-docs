/* Header file for checkers board data */

#define EMPTY   0
#define RED     1           /* you must not change these values */
#define BLACK   2
#define KING    4

#define SQRS_MAX    35  /* number of squares on a board plus some */

#define next(_t)    ((_t&1)+1)
#define CopyBoard(from,to) { int i; for (i=0; i<SQRS_MAX; i++) to[i] = from[i]; } 0

typedef long SQUARE;
typedef SQUARE FAR * BOARD;
typedef unsigned int BOOK_ELEMENT;


#define TYPE_RED0           1
#define TYPE_RED2           2
#define TYPE_BLACK0         3
#define TYPE_BLACK2         4 /* do not change the order of these values */
#define TYPE_RED_JUMP0      5
#define TYPE_RED_JUMP2      6
#define TYPE_BLACK_JUMP0    7
#define TYPE_BLACK_JUMP2    8

#define MakeMove_RED0(_b, _start) \
            _b[red_lut[_start][0]]  = _b[_start];\
            _b[_start]              = 0;\
            _b[red_lut[_start][0]] |= red_lut[_start][1]
#define MakeMove_RED2(_b, _start) \
            _b[red_lut[_start][2]]  = _b[_start];\
            _b[_start]              = 0;\
            _b[red_lut[_start][2]] |= red_lut[_start][3]
#define MakeMove_BLACK0(_b, _start) \
            _b[black_lut[_start][0]]  = _b[_start];\
            _b[_start]                = 0;\
            _b[black_lut[_start][0]] |= black_lut[_start][1]
#define MakeMove_BLACK2(_b, _start) \
            _b[black_lut[_start][2]]  = _b[_start];\
            _b[_start]                = 0;\
            _b[black_lut[_start][2]] |= black_lut[_start][3]

#define MakeMoveNoKing_RED_JUMP0(_b, _start) \
            _b[red_jump_lut[_start][1]]  = _b[_start];\
            _b[_start]                   = 0;\
            _b[red_jump_lut[_start][0]]  = 0
#define MakeMoveNoKing_RED_JUMP2(_b, _start) \
            _b[red_jump_lut[_start][3]]  = _b[_start];\
            _b[_start]                   = 0;\
            _b[red_jump_lut[_start][2]]  = 0
#define MakeMoveNoKing_BLACK_JUMP0(_b, _start) \
            _b[black_jump_lut[_start][1]]  = _b[_start];\
            _b[_start]                     = 0;\
            _b[black_jump_lut[_start][0]]  = 0
#define MakeMoveNoKing_BLACK_JUMP2(_b, _start) \
            _b[black_jump_lut[_start][3]]  = _b[_start];\
            _b[_start]                   = 0;\
            _b[black_jump_lut[_start][2]]  = 0

#define MakeMove_RED_JUMP0(_b, _start) \
            _b[red_jump_lut[_start][1]]  = _b[_start];\
            _b[_start]                   = 0;\
            _b[red_jump_lut[_start][0]]  = 0
#define MakeMove_RED_JUMP2(_b, _start) \
            _b[red_jump_lut[_start][3]]  = _b[_start];\
            _b[_start]                   = 0;\
            _b[red_jump_lut[_start][2]]  = 0
#define MakeMove_BLACK_JUMP0(_b, _start) \
            _b[black_jump_lut[_start][1]]  = _b[_start];\
            _b[_start]                     = 0;\
            _b[black_jump_lut[_start][0]]  = 0
#define MakeMove_BLACK_JUMP2(_b, _start) \
            _b[black_jump_lut[_start][3]]  = _b[_start];\
            _b[_start]                   = 0;\
            _b[black_jump_lut[_start][2]]  = 0



// ----- callable Functions in the engine
long PlayBestMove(BOARD b, int t, int j, int d,
                    int prune_depth, int prune_size, int max_depth);
int GameOver(BOARD b, int t);
int MoveValid(BOARD b, int start, int dest, int t);
long QualityOfBoard(BOARD b,int t);
char* TextizeBoard(BOARD b);

