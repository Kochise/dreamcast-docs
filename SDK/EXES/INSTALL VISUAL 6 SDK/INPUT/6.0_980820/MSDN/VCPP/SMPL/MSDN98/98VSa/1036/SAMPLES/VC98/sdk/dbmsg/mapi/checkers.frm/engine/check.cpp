/* function prototyping for internal functions */
long CheckMiniMaxAlphaBeta(BOARD b, int t, int j, int d, long c, long p);

#define JUMP_CONT_DEEPER 1

/* --------------------------------------------------------------------------
true if previous level should prune
else false

note: it would be possible to not prune equal qualities becuase they
      may be used to increase the number of available suggestions

statistics: 02:42:00  3-13-1994
            if this function is return 0, six levels takes 33 seconds
            if this function is implemented, six levels takes 9 seconds
-------------------------------------------------------------------------- */
inline int AlphaBeta(int t,long q, long c)
{
    pdebug(stddbg,"alpha-beta pruning t=%d q=%ld c=%ld %s(%d)\n",t,q,c,__FILE__,__LINE__);

    if (c > 0)
        {
        if (computer_color & t)
            {
            if (q > c)
                {
                pdebug(stddbg,"alpha-beta COMP pruning t=%d q=%ld c=%ld %s(%d)\n",t,q,c,__FILE__,__LINE__);
                return 1;
                }
            }
        else
            {
            if (q < c)
                {
                pdebug(stddbg,"alpha-beta USER pruning t=%d q=%ld c=%ld %s(%d)\n",t,q,c,__FILE__,__LINE__);
                return 1;
                }
            }
        }
    return 0;
}


/* --------------------------------------------------------------------------
The algorithm is basically a min-max tree
This function takes care of whether or no we remember the Min or the Max
In checkers terms this means the following:
    if it is my (the computers) move, pick the move that results in the highest quality
    if it is your move, remember the move that does the most damage (min quality)

Parameters:
    t    - whos turn it is (RED or BLACK)
    type - the move type.  this parameter should be a constant from check.h
           it says if it the move is a black or red move, and if the move is
           a sliding or jumping move.  This also indicates if the move is a
           move towards the left or towards the right.
    number - this is the index into the move table derived from 'type'
    d      - current recursion depth (debugging purposes only)
    besttype    - type corresponding with bestquality
    bestnumber  - number corresponding with bestquality
    bestquality - either a min or a max of qualities depending on current turn
-------------------------------------------------------------------------- */
inline void RememberMove(int t,int type, int number, long q,int d,
                         int* besttype, int* bestnumber, long* bestquality,
                         long c, long p, int* fBreak)
{
    *fBreak = AlphaBeta(t,q,c);
    if (q == *bestquality)
        {
        pdebug(stddbg,"evaluation (equal move) t=%d type=%d num=%d q=%ld d=%d %s(%d)\n",t,type,number,q,d,__FILE__,__LINE__);
        if (1 & rand()) return;
        }
    else if (computer_color & t)
        {
        pdebug(stddbg,"evaluation (computer) t=%d type=%d num=%d q=%ld d=%d %s(%d)\n",t,type,number,q,d,__FILE__,__LINE__);
        if (q < *bestquality) return;
        }
    else
        {
        pdebug(stddbg,"evaluation (opponent) t=%d type=%d num=%d q=%ld d=%d %s(%d)\n",t,type,number,q,d,__FILE__,__LINE__);
        if (*bestquality > 0 && q > *bestquality) return;
        }

    pdebug(stddbg,"RememberMove! evaluated t=%d type=%d num=%d q=%ld d=%d %s(%d)\n",t,type,number,q,d,__FILE__,__LINE__);
    *besttype = type;
    *bestnumber = number;
    *bestquality = q;
    return;
}

/* --------------------------------------------------------------------------
This function calls recurse for each possible jumping move for t's turn
starting from the start position

Note: there is special logic to crown men since landing in a crown position
      can not continue the jump, but having a man that is already a king land
      in a crown position can continue a jump.
If the piece I am moving is a king, I look at both BLACK and RED moves.

Parameters:
    b     - board (value is not changed)
    start - starting position
    t     - whos turn it is (RED or BLACK)
    besttype    - type corresponding with bestquality
    bestnumber  - number corresponding with bestquality
    bestquality - either a min or a max of qualities depending on current turn
-------------------------------------------------------------------------- */
int IterateJumps(BOARD b, int start, int t, int d,
                 int* besttype, int* bestnumber, long* bestquality,
                 long c, long p, int *fBreak)
{
    int moves_made=0;
    long q;
    SQUARE play_board[SQRS_MAX];

    if ((RED == t) || (KING & b[start]))
        {
        AssertSz(b[start] & t, "chicken");
        if (0 == b[red_jump_lut[start][1]] && red_jump_lut[start][1] && (next(t) & b[red_jump_lut[start][0]]))
            {
            pdebug(stddbg,"trying RED_JUMP0 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMoveNoKing_RED_JUMP0(play_board,start);
            if (0 == red_jump_lut[start][4] || (KING & play_board[red_jump_lut[start][1]]))
                {
                q = CheckMiniMaxAlphaBeta(play_board,t,red_jump_lut[start][1],JUMP_CONT_DEEPER+d,c,p);
                }
            else
                {
                AssertSz(play_board[red_jump_lut[start][1]], "what the?");
                play_board[red_jump_lut[start][1]] |= red_jump_lut[start][4];
                q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
                }
            RememberMove(t,TYPE_RED_JUMP0,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        if (0 == b[red_jump_lut[start][3]] && red_jump_lut[start][3] && (next(t) & b[red_jump_lut[start][2]]))
            {
            pdebug(stddbg,"trying RED_JUMP2 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMoveNoKing_RED_JUMP2(play_board,start);
            if (0 == red_jump_lut[start][4] || (KING & play_board[red_jump_lut[start][3]]))
                {
                q = CheckMiniMaxAlphaBeta(play_board,t,red_jump_lut[start][3],JUMP_CONT_DEEPER+d,c,p);
                }
            else
                {
                AssertSz(play_board[red_jump_lut[start][3]], "this stupid piece");
                play_board[red_jump_lut[start][3]] |= red_jump_lut[start][4];
                q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
                }
            RememberMove(t,TYPE_RED_JUMP2,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        }
    if ((BLACK == t) || (KING & b[start]))
        {
        AssertSz(b[start] & t, "but... I thought it was my turn");
        if (0 == b[black_jump_lut[start][1]] && black_jump_lut[start][1] && (next(t) & b[black_jump_lut[start][0]]))
            {
            pdebug(stddbg,"trying BLACK_JUMP0 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMoveNoKing_BLACK_JUMP0(play_board,start);
            if (0 == black_jump_lut[start][4] || (KING & play_board[black_jump_lut[start][1]]))
                {
                q = CheckMiniMaxAlphaBeta(play_board,t,black_jump_lut[start][1],JUMP_CONT_DEEPER+d,c,p);
                }
            else
                {
                AssertSz(play_board[black_jump_lut[start][1]], "you thought it was who's turn?");
                play_board[black_jump_lut[start][1]] |= black_jump_lut[start][4];
                q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
                }
            RememberMove(t,TYPE_BLACK_JUMP0,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        if (0 == b[black_jump_lut[start][3]] && black_jump_lut[start][3] && (next(t) & b[black_jump_lut[start][2]]))
            {
            pdebug(stddbg,"trying BLACK_JUMP2 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMoveNoKing_BLACK_JUMP2(play_board,start);
            if (0 == black_jump_lut[start][4] || (KING & play_board[black_jump_lut[start][3]]))
                {
                q = CheckMiniMaxAlphaBeta(play_board,t,black_jump_lut[start][3],JUMP_CONT_DEEPER+d,c,p);
                }
            else
                {
                AssertSz(play_board[black_jump_lut[start][3]], "maggots");
                play_board[black_jump_lut[start][3]] |= black_jump_lut[start][4];
                q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
                }
            RememberMove(t,TYPE_BLACK_JUMP2,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        }
    return moves_made;
}

/* --------------------------------------------------------------------------
This function calls recurse after making each possible sliding move for t's turn
starting from the start position

If the piece I am moving is a king, I look at both BLACK and RED moves.

Parameters:
    b     - board (value is not changed)
    start - starting position
    t     - whos turn it is (RED or BLACK)
    besttype    - type corresponding with bestquality
    bestnumber  - number corresponding with bestquality
    bestquality - either a min or a max of qualities depending on current turn
-------------------------------------------------------------------------- */
int IterateMoves(BOARD b, int start, int t, int d,
                 int* besttype, int* bestnumber, long* bestquality,
                 long c, long p, int *fBreak)
{
    int moves_made=0;
    long q;
    SQUARE play_board[SQRS_MAX];

    if ((RED == t) || (KING & b[start]))
        {
        AssertSz(b[start] & t, "I wish I could fly");
        if (0 == b[red_lut[start][0]] && red_lut[start][0])
            {
            pdebug(stddbg,"trying RED0 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMove_RED0(play_board,start);
            q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
            RememberMove(t,TYPE_RED0,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        if (0 == b[red_lut[start][2]] && red_lut[start][2])
            {
            pdebug(stddbg,"trying RED2 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMove_RED2(play_board,start);
            q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
            RememberMove(t,TYPE_RED2,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        }


    if ((BLACK == t) || (KING & b[start]))
        {
        AssertSz(b[start] & t, "what are you... ");
        if (0 == b[black_lut[start][0]] && black_lut[start][0])
            {
            pdebug(stddbg,"trying BLACK0 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMove_BLACK0(play_board,start);
            q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
            RememberMove(t,TYPE_BLACK0,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        if (0 == b[black_lut[start][2]] && black_lut[start][2])
            {
            pdebug(stddbg,"trying BLACK2 std move %d %s(%d)\n",start,__FILE__,__LINE__);
            CopyBoard(b,play_board);
            MakeMove_BLACK2(play_board,start);
            q = CheckMiniMaxAlphaBeta(play_board,next(t),0,1+d,p,*bestquality);
            RememberMove(t,TYPE_BLACK2,start,q,d,besttype,bestnumber,bestquality,c,p,fBreak);
            ++moves_made;
            }
        }
    return moves_made;
}


/* --------------------------------------------------------------------------

RECURSIVE MIN MAX ALGORITHM

Parameters:
    b - pointer to the board
    t - whos turn it is (RED or BLACK)
    j - space on board in which jump landed or zero if this
        is not a jump continuation
    d - depth of recursion

    alpha-beta pruning parameters:

    c - cutoff value for min max algorithm
    p - threshold to be passed on to next level

always returns the value of the best outcome of the board

note: this function is to be called from within the checkers engine only
note: this function evaluates moves based on the piece order structure defined
      in lut.cpp.  The reason for this is that we gain two things by looking
      at the best moves first:
        1) pruning is more effective
        2) if we must give up due to time constraint, we have already
           evaluated some of the best moves.

-------------------------------------------------------------------------- */
long CheckMiniMaxAlphaBeta(BOARD b, int t, int j, int d, long c, long p)
{
    /* ----- stack variables ----- */
    int  moves_made        = 0;
    int  best_move_type    = -1;
    int  best_move_number  = -1;
    long best_move_quality = -1;
    int  fBreak            = 0;

    /* ----- debug ----- */
    #ifdef DEBUG
    debug=1;
    if (debug && d < 7) PrintBoard(b,d);
    #endif

    AssertSz(b[0] == 0, "no b for my b my for my be my");
    AssertSz(d >= 0, "i am so tired of this");

    /* ----- if we have reached maximum depth, return now ----- */
    if (d >= depth_maximum) return QualityOfBoard(b,next(t));

    /* ----- iterate through all possible moves ----- */
    if (0 == j)
        {
        int i;
        pdebug(stddbg,"standard iteration d=%d %s(%d)\n",d,__FILE__,__LINE__);
        for (i=0;i<SQRS_MAX; i++)
            {
            int piece;
            piece = (int) piece_order[i].m;
            if (0 == (b[piece] & t)) continue; /* not our piece */
            moves_made += IterateJumps(b,piece,t,d,&best_move_type,&best_move_number,&best_move_quality,c,p,&fBreak);
            if (fBreak)
                {
                AssertSz(moves_made,"I'm pruning something I have not looked at...");
                break;
                }
            }
        if (0 == moves_made /* enforce the must jump rule */
            #ifndef HIGH_PERFORMANCE
                || 0==rConfig.iMustJump
            #endif
            )
            {
            pdebug(stddbg,"could not find a jumping move to make %s(%d)\n",__FILE__,__LINE__);
            for (i=0;i<SQRS_MAX; i++)
                {
                int piece;
                piece = (int) piece_order[i].m;
                if (0 == (b[piece] & t)) continue; /* not our piece */
                moves_made += IterateMoves(b,piece,t,d,&best_move_type,&best_move_number,&best_move_quality,c,p,&fBreak);
                if (fBreak)
                    {
                    AssertSz(moves_made,"to Scottland, I have not been");
                    break;
                    }
                }
            }
        if (0 == moves_made)
            {
            pdebug(stddbg,"could not find a move to make (error not handled) %s(%d)\n",__FILE__,__LINE__);
            return QualityOfBoard(b,next(t));
            }

        return best_move_quality;
        }

    /* ----- handle jump continuation ----- */
    pdebug(stddbg,"jump continuation d=%d %s(%d)\n",d,__FILE__,__LINE__);
    moves_made = IterateJumps(b,j,t,d,&best_move_type,&best_move_number,&best_move_quality,c,p,&fBreak);
    // AssertSz(0==fBreak,"is this a valid assert?");
    if (0==moves_made)
        {
        return CheckMiniMaxAlphaBeta(b,next(t),0,d,p,best_move_quality);
        }
    return best_move_quality;

} /* end CheckMiniMaxAlphaBeta */
