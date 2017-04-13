/**************************************************************************

    TRI.CPP - Simple triangle rasterizer

 **************************************************************************/
/**************************************************************************

    (C) Copyright 1995-1997 Microsoft Corp.  All rights reserved.

    You have a royalty-free right to use, modify, reproduce and 
    distribute the Sample Files (and/or any modified version) in 
    any way you find useful, provided that you agree that 
    Microsoft has no warranty obligations or liability for any 
    Sample Application Files which are modified. 

 **************************************************************************/

#include <windows.h>
#include "Fixed.h"

#define SWAP(x,y)   ((x)^=(y)^=(x)^=(y))
//SWAP has a compiler generated problem on alpha.... do it the old fashioned way:
#define SWAPPT(a,b) {POINT p; p=a;a=b;b=p;} //(SWAP(a.y,b.y), SWAP(a.x,b.x))

/**************************************************************************

    FillScan8

    fill a scan from x0 to x1 (inclusive) with color c

    does optimal DWORD writes, making sure to stay aligned so
    it is safe for video memory.

 **************************************************************************/
inline void FillScan8(BYTE *p, int x0, int x1, DWORD c)
{
    int dx;
    int z;

    dx = x1-x0+1;
    p += x0;

    if (dx > 4)
    {
        if (z = (DWORD)p & 0x03)
        {
            while (z++ < 4)
            {
                *p++ = (BYTE)c;
                dx--;
            }
        }

        while (dx >= 4)
        {
            *((DWORD*)p) = c;
            p += 4;
            dx -= 4;
        }
    }

    while (dx-- > 0)
    {
        *p++ = (BYTE)c;
    }
}

/**************************************************************************

    Triangle8

    rasterize a solid color triangle into a 8bpp memory buffer.

    NOTE this code does no clipping you better pass

    rasterizes a solid color triangle into a memory buffer with any pitch
    also is careful to always write DWORD aligned, so it is safe to be
    used on video memory (and faster too...)

 **************************************************************************/

void Triangle8(BYTE *p, int next_scan, POINT P0, POINT P1, POINT P2, DWORD c)
{
    Fixed   d,d0;
    Fixed   x,x0;
    int     y;

    //
    // expand the color to a DWORD
    //
    c |= c<<8;
    c |= c<<16;

    //
    //  sort points so P0.y <= P1.y <= P2.y
    //
    if (P0.y > P1.y) SWAPPT(P0,P1);
    if (P1.y > P2.y) SWAPPT(P1,P2);
    if (P0.y > P1.y) SWAPPT(P0,P1);

    //
    //  check for quick out?
    //
    if (P2.y - P0.y == 0)
    {
        return;
    }

    //
    //  compute "long" side walk from P0 to P2
    //
    d = (Fixed)(P2.x - P0.x) / (Fixed)(P2.y - P0.y);

    x  = P0.x;
    y  = P0.y;
    p += P0.y * next_scan;   // point p to correct scan.

    //
    //  do the top
    //
    if (P0.y < P1.y)
    {
        d0 = (Fixed)(P1.x - P0.x) / (Fixed)(P1.y - P0.y);
        x0 = P0.x;

        //
        // check for left or right fill
        //
        if (d < d0)
        {
            while (y < P1.y)
            {
                FillScan8(p, x, x0, c);
                y++;
                p  += next_scan;
                x  += d;
                x0 += d0;
            }
        }
        else
        {
            while (y < P1.y)
            {
                FillScan8(p, x0, x, c);
                y++;
                p  += next_scan;
                x  += d;
                x0 += d0;
            }
        }
    }

    //
    // do the bottom.
    //
    
    if (P2.y - P1.y == 0)
    {
        return;
    }

    d0 = (Fixed)(P2.x - P1.x) / (Fixed)(P2.y - P1.y);
    x0 = P1.x;

    //
    // check for left or right fill
    //
    if (x < x0)
    {
        while (y < P2.y)
        {
            FillScan8(p, x, x0, c);
            y++;
            p  += next_scan;
            x  += d;
            x0 += d0;
        }
    }
    else
    {
        while (y < P2.y)
        {
            FillScan8(p, x0, x, c);
            y++;
            p  += next_scan;
            x  += d;
            x0 += d0;
        }
    }
}
