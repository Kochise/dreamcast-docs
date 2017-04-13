/* --------------------------------------------------------------------------
This function is qsort's callback
to sort the moves based on quality
-------------------------------------------------------------------------- */
int __cdecl cmpgle(const void* elem1, const void* elem2)
{
    if (    (*(struct _piece_order_struct *)elem1).q     >
            (*(struct _piece_order_struct *)elem2).q     )
        return -1;
    else if (    (*(struct _piece_order_struct *)elem1).q     <
                 (*(struct _piece_order_struct *)elem2).q     )
        return 1;
    else
        return 0;
}

/* --------------------------------------------------------------------------
THIS IS THE CHECKERS ENGINE::

b           - is the start board - it will be changed on return to
              reflect the move or moves (in the case of a double jump)
              made
t           - is whos turn it is RED or BLACK
j           - is jump continuation - must be 0
prune_depth - how many levels to recurse to determine what to prune
prune_size  - how many branches of the pruned tree to pursue (note:
              each piece is considered as one branch even though it
              it results in as many as four actual branches
max_depth   - after the tree has been pruned how far should it recurse
              must be greater than the prune_depth

side effects:
            Calls PrintBoard (debugio.cpp)

note: we may wish to use iterative deepening here and base things on time
-------------------------------------------------------------------------- */
long PlayBestMove(BOARD b, int t, int j, int d,
                    int prune_depth, int prune_size, int max_depth)
{
    /* ----- stack variables ----- */
    int  moves_made        =  0;
    int  best_move_type    = -1;
    int  best_move_number  = -1;
    long best_move_quality = -1;
    long alpha_beta_c      = -1;
    int  fBreak            = 0;
    int  i;

    #ifdef DEBUG
    int  jumps_made        =  0;
    #endif

    AssertSz(prune_size <= SQRS_MAX, "me. prune size is way to big");
    AssertSz(prune_size > 1, "how much? prune size is way to small");
    AssertSz(0 == b[0], "b sub zero should equal zero");
    AssertSz(0 == b[SQRS_MAX-1], "b sub MAX-1 should equal zero");

    /* ----- debug ----- */
    if (debug && d < 3) PrintBoard(b,d);

    /* ----- initialize tables and variables ----- */
    depth_maximum = max_depth;
    computer_color = t;
    for (i=0; i<SQRS_MAX; i++)
        {
        piece_order[i].m = (SQUARE) i;
        piece_order[i].q = -1;
        }

    /* ----- seed the random number generator ----- */
    #ifdef DEBUG
    srand( 0 );
    #else
    #ifdef TEST
    srand( 0 );
    #else
    srand( (unsigned)time( NULL ) );
    #endif
    #endif

    /* ----- iterate through all possible moves AT PRUNE_DEPTH ----- */
    if (prune_depth > 0)
        {
        depth_maximum = prune_depth;
        pdebug(stddbgmin,"PlayBestMove d=%d %s(%d)\n",d,__FILE__,__LINE__);
        for (i=0;i<SQRS_MAX; i++)
            {
            int piece;
            piece = (int) piece_order[i].m;
            if (0 == (b[piece] & t)) continue; /* not our piece */
            moves_made += IterateJumps(b,piece,t,d,&best_move_type,&best_move_number,&piece_order[i].q,alpha_beta_c,best_move_quality,&fBreak);
            AssertSz(0 == fBreak,"I must not prune at the root level of the tree");
            #ifdef DEBUG
            jumps_made += moves_made;
            #endif
            }
        if (0 == moves_made /* enforce the must jump rule */
            #ifndef HIGH_PERFORMANCE
                || 0==rConfig.iMustJump
            #endif
            )
            {
            pdebug(stddbgmin,"could not find a jumping move to make %s(%d)\n",__FILE__,__LINE__);
            for (i=0;i<SQRS_MAX; i++)
                {
                int piece;
                piece = (int) piece_order[i].m;
                if (0 == (b[piece] & t)) continue; /* not our piece */
                moves_made += IterateMoves(b,piece,t,d,&best_move_type,&best_move_number,&piece_order[i].q,alpha_beta_c,best_move_quality,&fBreak);
                AssertSz(0 == fBreak,"I ought not prune at the root level of the tree");
                }
            }
        if (0 == moves_made)
            {
            pdebug(stddbgmin,"could not find a move to make (error not handled) %s(%d)\n",__FILE__,__LINE__);
            AssertSz(0, "I give up... why don't you go instead");
            }
        }
    else
        {
        moves_made = 1000;
        prune_size = SQRS_MAX;
        }

    /* ----- if we only have one move to make, dont recurse again ----- */
    if (moves_made > 1)
        {
        /* ----- shuffle the moves ----- */
        for (i=SQRS_MAX-1; i > 0; i--)
            {
            int r;
            struct _piece_order_struct temp;

            /* ----- pick a random interchange ----- */
            r = ((unsigned int)rand()) % ((unsigned int) i);

            /* ----- swap the order ----- */
            temp = piece_order[i];
            piece_order[i] = piece_order[r];
            piece_order[r] = temp;
            }

        /* ----- sort the move table based on the move qualities
                of each move that we tried ----- */
        pdebug(stddbgmin,"sorting... %s(%d)\n",__FILE__,__LINE__);
        qsort(piece_order,SQRS_MAX, sizeof(struct _piece_order_struct), cmpgle);
        pdebug(stddbgmin,"done sorting. %s(%d)\n",__FILE__,__LINE__);


        /* ----- recurse the pruned board to a deeper level ----- */
continue_jump:
        moves_made = 0;
        depth_maximum = max_depth;
        pdebug(stddbgmin,"recursing pruned PlayBestMove d=%d %s(%d)\n",d,__FILE__,__LINE__);
        for (i=0;i<prune_size; i++)
            {
            int piece;
            piece = (int) piece_order[i].m;
            if (0 == (b[piece] & t)) continue; /* not our piece */
            moves_made += IterateJumps(b,piece,t,d,&best_move_type,&best_move_number,&best_move_quality,alpha_beta_c,best_move_quality,&fBreak);
            AssertSz(0 == fBreak,"x2 I must not prune at the root level of the tree");
            #ifdef DEBUG
            jumps_made += moves_made;
            #endif
            }
        if ((0 == moves_made
            #ifndef HIGH_PERFORMANCE
                || 0==rConfig.iMustJump
            #endif
            )&& 0 == j) /* enforce the must jump rule */
            {
            pdebug(stddbgmin,"could not find a jumping move to make %s(%d)\n",__FILE__,__LINE__);
            for (i=0;i<prune_size; i++)
                {
                int piece;
                piece = (int) piece_order[i].m;
                pdebug(stddbgmin,"Next move piece=%d i=%d %s(%d)\n",piece,i,__FILE__,__LINE__);
                if (0 == (b[piece] & t)) continue; /* not our piece */
                moves_made += IterateMoves(b,piece,t,d,&best_move_type,&best_move_number,&best_move_quality,alpha_beta_c,best_move_quality,&fBreak);
                AssertSz(0 == fBreak,"x3 I must not prune at the root level of the tree");
                }
            }
        if (0 == moves_made)
            {
            pdebug(stddbgmin,"could not find a move to make (error ! handled) %s(%d)\n",__FILE__,__LINE__);
            #ifdef DEBUG
            AssertSz(jumps_made, "Your turn.  I mean.  Can I move or something? .. nevermind .. why don't you just go");
            #endif
            }
        }

    /* ----- do the first step of any jumps ----- */
    if (best_move_type > TYPE_BLACK2)
        {
        switch (best_move_type)
            {
            case TYPE_RED_JUMP0   :
                j = red_jump_lut[best_move_number][1]  ;
                piece_order[0].m = (SQUARE) j;
                MakeMoveNoKing_RED_JUMP0(b,best_move_number);
                if (0 != red_jump_lut[best_move_number][4] && !(KING & b[red_jump_lut[best_move_number][1]])) goto no_jump;
                break;

            case TYPE_RED_JUMP2   :
                j = red_jump_lut[best_move_number][3]  ;
                piece_order[0].m = (SQUARE) j;
                MakeMoveNoKing_RED_JUMP2(b,best_move_number);
                if (0 != red_jump_lut[best_move_number][4] && !(KING & b[red_jump_lut[best_move_number][3]])) goto no_jump;
                break;

            case TYPE_BLACK_JUMP0 :
                j = black_jump_lut[best_move_number][1];
                piece_order[0].m = (SQUARE) j;
                MakeMoveNoKing_BLACK_JUMP0(b,best_move_number);
                if (0 != black_jump_lut[best_move_number][4] && !(KING & b[black_jump_lut[best_move_number][1]])) goto no_jump;
                break;

            case TYPE_BLACK_JUMP2 :
                j = black_jump_lut[best_move_number][3];
                piece_order[0].m = (SQUARE) j;
                MakeMoveNoKing_BLACK_JUMP2(b,best_move_number);
                if (0 != black_jump_lut[best_move_number][4] && !(KING & b[black_jump_lut[best_move_number][3]])) goto no_jump;
                break;

            default:
                AssertSz(0, "end case");
                break;
            }

        /* ----- re-initialize ----- */
        prune_size        =  1; /* ! force it to use only the jump destination as a move */
        moves_made        =  0;
        best_move_type    = -1;
        best_move_number  = -1;
        best_move_quality = -1;

        goto continue_jump;
        }
no_jump:

    switch (best_move_type)
        {
        case TYPE_RED0        :
            MakeMove_RED0(b,best_move_number);
            break;

        case TYPE_RED2        :
            MakeMove_RED2(b,best_move_number);
            break;

        case TYPE_BLACK0      :
            MakeMove_BLACK0(b,best_move_number);
            break;

        case TYPE_BLACK2      :
            MakeMove_BLACK2(b,best_move_number);
            break;

        case TYPE_RED_JUMP0   :
        case TYPE_RED_JUMP2   :
        case TYPE_BLACK_JUMP0 :
        case TYPE_BLACK_JUMP2 :
            pdebug(stddbgmin,"skipping a jump move in IO %s(%d)\n",__FILE__,__LINE__);
            break;

        default:
            pdebug(stddbgmin,"printmove did not make the move on the board %s(%d)\n",__FILE__,__LINE__);
            pdebug(stddbgmin,"this could be a jump continuation %s(%d)\n",__FILE__,__LINE__);
            break;
        }

    // make sure everything is kinged (in case we jumped to this point)
    if (RED & b[1]) b[1] |= KING;
    if (RED & b[2]) b[2] |= KING;
    if (RED & b[3]) b[3] |= KING;
    if (RED & b[4]) b[4] |= KING;
    if (BLACK & b[32]) b[32] |= KING;
    if (BLACK & b[31]) b[31] |= KING;
    if (BLACK & b[30]) b[30] |= KING;
    if (BLACK & b[29]) b[29] |= KING;

    /* ----- return to caller ----- */
    return best_move_quality;
}
