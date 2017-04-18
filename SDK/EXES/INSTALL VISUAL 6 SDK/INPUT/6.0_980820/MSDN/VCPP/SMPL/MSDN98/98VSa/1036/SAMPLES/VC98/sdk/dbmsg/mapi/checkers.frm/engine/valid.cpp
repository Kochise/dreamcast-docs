/* --------------------------------------------------------------------------
b - board on which to make the move (will be changed on return)
t - RED, BLACK

returns 0 if invalid move
        2 if continuable
else    1 
-------------------------------------------------------------------------- */
int MoveValid(BOARD b, int start, int dest, int t)
{
    int j; /* the piece we are jumping over */
    int restore_depth;
    int must_jump=0;

    AssertSz(start > 0 && start <= 32, "ducks");
    AssertSz(dest > 0 && dest <= 32, "geese");
    AssertSz(t==RED || t==BLACK, "The Tetonkaha Wildabeast");
    AssertSz(b[start], "it means buffalo");
    
    /* destination empty */
    if (0 != b[dest]) return 0;
    pdebug(stddbgmin,"MoveValid destination empty %s(%d)",__FILE__,__LINE__);

    /* if must jump rule is on */
    if (rConfig.iMustJump)
        {
        int besttype, bestnumber;
        long bestquality;
        long c=-1; long p=-1; int fBreak=0;
        int i=0;
        
        restore_depth = depth_maximum;
        depth_maximum = 1;
        for (i=0;i<SQRS_MAX;i++)
            {
            if (b[i] & t)
                {
                must_jump += IterateJumps(b,i,t,0,
                            &besttype, &bestnumber, &bestquality,
                            c,p,&fBreak);
                }
            AssertSz(fBreak==0,"no way samual jones");
            }
        depth_maximum = restore_depth;
        }

    if (t == RED || (b[start] & KING))
        {
        pdebug(stddbgmin,"MoveValid considering RED moves %s(%d)",__FILE__,__LINE__);
        if (red_lut[start][0] == dest) goto slide;
        if (red_lut[start][2] == dest) goto slide;
        if (red_jump_lut[start][1] == dest && (b[red_jump_lut[start][0]]|KING) == (next(t)|KING)) {j=red_jump_lut[start][0]; goto jump;}
        if (red_jump_lut[start][3] == dest && (b[red_jump_lut[start][2]]|KING) == (next(t)|KING)) {j=red_jump_lut[start][2]; goto jump;}
        }
    if (t == BLACK || (b[start] & KING))
        {
        pdebug(stddbgmin,"MoveValid considering BLACK moves %s(%d)",__FILE__,__LINE__);
        if (black_lut[start][0] == dest) goto slide;
        if (black_lut[start][2] == dest) goto slide;
        if (black_jump_lut[start][1] == dest && (b[black_jump_lut[start][0]]|KING) == (next(t)|KING)) {j=black_jump_lut[start][0]; goto jump;}
        if (black_jump_lut[start][3] == dest && (b[black_jump_lut[start][2]]|KING) == (next(t)|KING)) {j=black_jump_lut[start][2]; goto jump;}
        }

    /* illegal position */
    pdebug(stddbgmin,"MoveValid illegal position %s(%d)",__FILE__,__LINE__);
    return 0;

slide:
    pdebug(stddbgmin,"MoveValid found legal sliding move %s(%d)",__FILE__,__LINE__);
    if (must_jump)
        {
        pdebug(stddbgmin,"slide attempt when jumping move is possible %s(%d)",__FILE__,__LINE__);
        return 0;
        }
    b[dest] = b[start];
    b[start] = 0;

    if (RED & b[1]) b[1] |= KING;
    if (RED & b[2]) b[2] |= KING;
    if (RED & b[3]) b[3] |= KING;
    if (RED & b[4]) b[4] |= KING;
    if (BLACK & b[32]) b[32] |= KING;
    if (BLACK & b[31]) b[31] |= KING;
    if (BLACK & b[30]) b[30] |= KING;
    if (BLACK & b[29]) b[29] |= KING;

    return 1;

jump:
    pdebug(stddbgmin,"MoveValid found legal jump %s(%d)",__FILE__,__LINE__);
    b[dest] = b[start];
    b[start] = 0;
    b[j] = 0;

    if (t == BLACK || (b[dest] & KING))
        {
        if (b[black_jump_lut[dest][1]] == 0 && (b[black_jump_lut[dest][0]]|KING) == (next(t)|KING)) {return 2;}
        if (b[black_jump_lut[dest][3]] == 0 && (b[black_jump_lut[dest][2]]|KING) == (next(t)|KING)) {return 2;}
        }

    if (t == RED || (b[dest] & KING))
        {
        if (b[red_jump_lut[dest][1]] == 0 && (b[red_jump_lut[dest][0]]|KING) == (next(t)|KING)) {return 2;}
        if (b[red_jump_lut[dest][3]] == 0 && (b[red_jump_lut[dest][2]]|KING) == (next(t)|KING)) {return 2;}
        }

    pdebug(stddbgmin,"MoveValid found jump is NOT continuable %s(%d)",__FILE__,__LINE__);
    return 1;
}

/* --------------------------------------------------------------------------
GameOver returns

GAME_{WON}|{PLAYABLE}|{DRAWN}
--------------------------------------------------------------------------- */
int GameOver(BOARD b, int t)
{
    int restore_depth;
    int besttype, bestnumber;
    long bestquality;
    long c=-1; long p=-1; int fBreak=0;
    int i=0;                             // Piece I'm on.
    int move_is_possible=0;

    restore_depth = depth_maximum;
    depth_maximum = 1;
    for (i=0;i<SQRS_MAX;i++)
        {
        if (b[i] & t)
            {
            move_is_possible += IterateJumps(b,i,t,0,
                        &besttype, &bestnumber, &bestquality,
                        c,p,&fBreak);
            move_is_possible += IterateMoves(b,i,t,0,
                        &besttype, &bestnumber, &bestquality,
                        c,p,&fBreak);
            if (move_is_possible)
                break;
            }
            AssertSz(fBreak==0,"no way sammy jones");
        }
    depth_maximum = restore_depth;

    /* ----- make sure this isn't a drawn game ----- */
    if (move_is_possible)
    {
        int i=rConfig.iMaxMoves;
        int t=0;
        SQUARE b[SQRS_MAX];

        if (CMoves.GetFirstBoard(b,&t))
            while (CMoves.GetNextBoard(b,&t))
                i--;
        AssertSz(i > -5, "vania lorelle");
        if (i<0) 
            return GAME_DRAWN;
    }

    if (move_is_possible)
        return(GAME_PLAYABLE);
    else
        return(GAME_WON);    

}

