/* --------------------------------------------------------------------------
returns the value of the board from 'computer_colors' perspective
-------------------------------------------------------------------------- */
long QualityOfBoard(BOARD b,int t)
{
    /* ----- constants (to be tweaked) ----- */
    const int wKing            = 32 + 256;
    const int wPiece           = 256;
    const int wBlank           = 1;
    const int wMoveTheory      = 32;
    const int wCenterPos       = 4;
    const int wDoubleCorner    = 2;
    const int wHoldingKingRow  = 2;
    const int wEdges           = -1;

    /* ----- variable factors ----- */
    long q=50000; /* quality */

    #define co_kings  (pieces[computer_color | KING]       )
    #define op_kings  (pieces[next(computer_color) | KING] )
    #define co_pieces (pieces[computer_color]              )
    #define op_pieces (pieces[next(computer_color)]        )
    #define blanks    (pieces[0]                           )

    int pieces[7];
    BOARD pb = b + 32;
    int mtpis = 0; // movetheory pieces in system

    /* ----- number of pieces ----- */
    memset(pieces,0,sizeof(pieces));
    for (;;)
        {
        ++pieces[pb[0]];
        --pb;
        Assert(pb >= b);
        ++pieces[pb[0]];
        --pb;
        Assert(pb >= b);
        ++pieces[pb[0]];
        --pb;
        Assert(pb >= b);
        ++pieces[pb[0]];
        --pb;
        if (pb <= b) break;
        }
    q += (co_kings  * wKing);    /* multiply piece count factor by weights */
    q -= (op_kings  * wKing);
    q += (co_pieces * wPiece);
    q -= (op_pieces * wPiece);
    q += (blanks    * wBlank);

    /* ----- move theory ----- */
    if (co_pieces == op_pieces && 0==co_kings && 0==op_kings)
        {
        int base_of_system=0;
        if (BLACK == next(t)) base_of_system=4;
        for (;base_of_system < 32; base_of_system += 8)
            {
            if (b[1+base_of_system]) mtpis++;
            if (b[2+base_of_system]) mtpis++;
            if (b[3+base_of_system]) mtpis++;
            if (b[4+base_of_system]) mtpis++;
            }
        mtpis &= 1;
        q += wMoveTheory;
        if (next(t) == computer_color)
            {
            if (!mtpis) /* opponent has the move */
                q -= (wMoveTheory * 2);
            }
        else
            {
            if (mtpis) /* opponent has the move */
                q -= (wMoveTheory * 2);
            }
        }

    /* ----- position of pieces ----- */
    static const long weightTable[][3] = {         {0,0,0},
        {0, wDoubleCorner, -wDoubleCorner},        {0,0,0}, {0,0,0}, {0,0,0},
        {0, wDoubleCorner, -wDoubleCorner},        {0,0,0}, {0,0,0}, {0,0,0},
        {0,0,0}, {0,0,0}, {0,0,0},                 {0, wEdges, -wEdges},
        {0, wEdges, -wEdges},                      {0, wCenterPos, -wCenterPos},
        {0, wCenterPos, -wCenterPos},              {0,0,0}, {0,0,0},
        {0, wCenterPos, -wCenterPos},              {0, wCenterPos, -wCenterPos},
        {0, wEdges, -wEdges},                      {0, wEdges, -wEdges},
        {0,0,0}, {0,0,0}, {0,0,0},                 {0,0,0}, {0,0,0}, {0,0,0},
        {0, wDoubleCorner, -wDoubleCorner},        {0,0,0}, {0,0,0}, {0,0,0},
        {0, wDoubleCorner, -wDoubleCorner},        {0,0,0}, {0,0,0}, {0,0,0},
        {0,0,0}, {0,0,0}, {0,0,0}                  };
    long q_posfactor = 0;
    q_posfactor += weightTable[  1][b[  1] & 3];
    q_posfactor += weightTable[  5][b[  5] & 3];
    q_posfactor += weightTable[ 12][b[ 12] & 3];
    q_posfactor += weightTable[ 13][b[ 13] & 3];
    q_posfactor += weightTable[ 14][b[ 14] & 3];
    q_posfactor += weightTable[ 15][b[ 15] & 3];
    q_posfactor += weightTable[ 18][b[ 18] & 3];
    q_posfactor += weightTable[ 19][b[ 19] & 3];
    q_posfactor += weightTable[ 20][b[ 20] & 3];
    q_posfactor += weightTable[ 21][b[ 21] & 3];
    q_posfactor += weightTable[ 28][b[ 28] & 3];
    q_posfactor += weightTable[ 32][b[ 32] & 3];
    if (BLACK == computer_color)
        q_posfactor = -q_posfactor;
    q += q_posfactor;

    /* ----- king row ----- */
    if ((0 == (KING & b[1])) && 0 != b[1])   {if (b[1] & computer_color)  q+=wHoldingKingRow; else q-=wHoldingKingRow;}
    if ((0 == (KING & b[3])) && 0 != b[3])   {if (b[3] & computer_color)  q+=wHoldingKingRow; else q-=wHoldingKingRow;}
    if ((0 == (KING & b[30])) && 0 != b[30]) {if (b[30] & computer_color) q+=wHoldingKingRow; else q-=wHoldingKingRow;}
    if ((0 == (KING & b[32])) && 0 != b[32]) {if (b[32] & computer_color) q+=wHoldingKingRow; else q-=wHoldingKingRow;}

    /* ----- return the results ----- */
    pdebug(stddbg,"QualityOfBoard=%ld %s(%d)\n",q,__FILE__,__LINE__);
    AssertSz(q > 0,"queue too small");
    #ifndef HIGH_PERFORMANCE
    if (0==rConfig.iGameType) return q;
    if (1==rConfig.iGameType) return 100000-q;
    AssertSz(0,"what kind of game are you playing anyway?");
    #endif
    return q;
}
