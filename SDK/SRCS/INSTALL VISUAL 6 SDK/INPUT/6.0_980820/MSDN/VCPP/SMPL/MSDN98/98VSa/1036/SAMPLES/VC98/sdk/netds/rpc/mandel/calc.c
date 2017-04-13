
/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992, 1993, 1994- 1996
                        mandel Example

    FILE:       calc.c

    PURPOSE:    Server side of the RPC distributed application Mandel

    FUNCTIONS:  MandelCalc() - Do the calculations for the Windows
                               Mandelbrot Set distributed drawing program.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#ifdef RPC
#include "mdlrpc.h"
#endif
#include "mandel.h"


short calcmand(double, double, short);


void MandelCalc(PCPOINT    pcptLL,
                PLONGRECT  prcDraw,
                double     precision,
                DWORD      ulThreshold,
                LINEBUF *  pbBuf)
{
    DWORD   h, height, width;
    double  dreal, dimag, dimag2;
    short   maxit = 0;
    short * pbPtr;

    pbPtr = *pbBuf;   // LINEBUF is an array of shorts

    dreal = pcptLL->real + ((double)prcDraw->xLeft * precision);
    dimag = pcptLL->imag + ((double)prcDraw->yBottom * precision);

    maxit = (short) ulThreshold;

    height = (prcDraw->yTop - prcDraw->yBottom) + 1;
    width = (prcDraw->xRight - prcDraw->xLeft) + 1;

    for ( ; width > 0; --width, dreal += precision) {
        for (dimag2 = dimag, h = height; h > 0; --h, dimag2 += precision) {
            if ((dreal > 4.0) || (dreal < -4.0) ||
                (dimag2 > 4.0) || (dimag2 < -4.0))
                *(pbPtr++) = 0;
            else
                *(pbPtr++) = calcmand(dreal, dimag2, maxit);
        }
    }
}


/* C version of the assembly language program */
short calcmand(double dreal,
               double dimag,
               short  maxit)
{
    double x, y, xsq, ysq;
    short k;

    k = maxit;
    x = dreal;
    y = dimag;

    while (1) {
        xsq = x * x;
        ysq = y * y;
        y = 2.0 * x * y + dimag;
        x = (xsq - ysq) + dreal;
        if (--k == 0)
            return((short) (maxit - k));
        if ((xsq + ysq) > 4.0)
            return((short) (maxit - k));
    }
}
