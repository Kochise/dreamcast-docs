/* --------------------------------------------------------------------------
Print Board is a debugging routine and should not be used for any other purpose
-------------------------------------------------------------------------- */

int p(BOARD b, int x)
{
    int c=' '; /* empty square */
    if (b[x] & RED)   c = 'r';
    if (b[x] & BLACK) c = 'b';
    if (b[x] & KING)  c = toupper(c);
    return c;
}

void PrintBoard(BOARD b, int d)
{
    const unsigned char rs=254; /* red square */
    static char buf[256];

    pdebug(stddbg," ");
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",( rs),     (p(b, 1)), ( rs),     (p(b, 2)), ( rs),     (p(b, 3)), ( rs),     (p(b, 4)) );
    pdebug(stddbg,buf);
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",(p(b, 5)), ( rs),     (p(b, 6)), ( rs),     (p(b, 7)), ( rs),     (p(b, 8)), ( rs)     );
    pdebug(stddbg,buf);
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",( rs),     (p(b, 9)), ( rs),     (p(b,10)), ( rs),     (p(b,11)), ( rs),     (p(b,12)) );
    pdebug(stddbg,buf);
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",(p(b,13)), ( rs),     (p(b,14)), ( rs),     (p(b,15)), ( rs),     (p(b,16)), ( rs)     );
    pdebug(stddbg,buf);
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",( rs),     (p(b,17)), ( rs),     (p(b,18)), ( rs),     (p(b,19)), ( rs),     (p(b,20)) );
    pdebug(stddbg,buf);
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",(p(b,21)), ( rs),     (p(b,22)), ( rs),     (p(b,23)), ( rs),     (p(b,24)), ( rs)     );
    pdebug(stddbg,buf);
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",( rs),     (p(b,25)), ( rs),     (p(b,26)), ( rs),     (p(b,27)), ( rs),     (p(b,28)) );
    pdebug(stddbg,buf);
    wsprintf(buf,"  %c%c%c%c%c%c%c%c",(p(b,29)), ( rs),     (p(b,30)), ( rs),     (p(b,31)), ( rs),     (p(b,32)), ( rs)     );
    pdebug(stddbg,buf);
    pdebug(stddbg," ");

}

/* --------------------------------------------------------------------------
TextizeBoard produces a text version of the board for people who did
not install this form.
-------------------------------------------------------------------------- */
char* TextizeBoard(BOARD b)
{
    const unsigned char rs='='; /* red square */
    static char buf[2048];


    wsprintf(buf,
        "IPM.Checkers\r\n\r\n"
        "  %c%c%c%c%c%c%c%c\r\n"
        "  %c%c%c%c%c%c%c%c\r\n"
        "  %c%c%c%c%c%c%c%c\r\n"
        "  %c%c%c%c%c%c%c%c\r\n"
        "  %c%c%c%c%c%c%c%c\r\n"
        "  %c%c%c%c%c%c%c%c\r\n"
        "  %c%c%c%c%c%c%c%c\r\n"
        "  %c%c%c%c%c%c%c%c\r\n",


    ( rs),     (p(b, 1)), ( rs),     (p(b, 2)), ( rs),     (p(b, 3)), ( rs),     (p(b, 4)) ,
    (p(b, 5)), ( rs),     (p(b, 6)), ( rs),     (p(b, 7)), ( rs),     (p(b, 8)), ( rs)     ,
    ( rs),     (p(b, 9)), ( rs),     (p(b,10)), ( rs),     (p(b,11)), ( rs),     (p(b,12)) ,
    (p(b,13)), ( rs),     (p(b,14)), ( rs),     (p(b,15)), ( rs),     (p(b,16)), ( rs)     ,
    ( rs),     (p(b,17)), ( rs),     (p(b,18)), ( rs),     (p(b,19)), ( rs),     (p(b,20)) ,
    (p(b,21)), ( rs),     (p(b,22)), ( rs),     (p(b,23)), ( rs),     (p(b,24)), ( rs)     ,
    ( rs),     (p(b,25)), ( rs),     (p(b,26)), ( rs),     (p(b,27)), ( rs),     (p(b,28)) ,
    (p(b,29)), ( rs),     (p(b,30)), ( rs),     (p(b,31)), ( rs),     (p(b,32)), ( rs)     );

    return buf;

}
