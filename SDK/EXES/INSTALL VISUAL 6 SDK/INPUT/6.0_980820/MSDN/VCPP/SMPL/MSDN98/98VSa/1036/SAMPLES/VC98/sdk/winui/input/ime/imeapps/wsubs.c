#include "windows.h"

#ifdef USEWAPI
int PASCAL MylstrcmpW(LPWSTR lp0, LPWSTR lp1)
{

    while(*lp0)
    {
        if (*lp0 != *lp1)
        {
            return (-1);
        }
        lp0++;
        lp1++;

    }
    if (!*lp1)
        return 0;

    return 1;
}
int PASCAL MylstrcpyW(LPWSTR lp0, LPWSTR lp1)
{
    int n = 0;

    while(*lp1)
    {
        *lp0 = *lp1;
        lp0++;
        lp1++;
        n++;
    }
    *lp0 = *lp1;
    return n;
}
int PASCAL MylstrcatW(LPWSTR lp0, LPWSTR lp1)
{
    int n = 0;

    while(*lp0)
        lp0++;

    return MylstrcpyW(lp0, lp1);
}
LPWSTR PASCAL MyCharPrevW(LPWSTR lpStart, LPWSTR lpCur)
{
    LPWSTR lpRet = lpStart;
    if (lpCur > lpStart)
        lpRet = lpCur - 1;

    return lpRet;
}
LPWSTR PASCAL MyCharNextW(LPWSTR lp)
{
    return lp++;
}
#endif

