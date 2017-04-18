/*
 *  S M H P S . C
 *  
 *  Sample mail handling sub-string search functions
 *  Uses Rabin/Karp algorythms to find sub-strings
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"
#include "smhnls.h"

#define ulPrime ((ULONG) 0x00FF00F1)
#define ulBase  ((ULONG) 0x00000100)

BOOL
FRKFindSubpb (LPBYTE pbTarget,
    ULONG cbTarget,
    LPBYTE pbPattern,
    ULONG cbPattern)
{
    UINT    i;
    LPBYTE  pbTargetMax = pbTarget + cbTarget;
    LPBYTE  pbPatternMax = pbPattern + cbPattern;
    ULONG   ulBaseToPowerMod = 1;
    ULONG   ulHashPattern = 0;
    ULONG   ulHashTarget = 0;

    if (cbPattern > cbTarget)
        return FALSE;

    // Compute the power of the left most character in base ulBase
    for (i = 1; i < cbPattern; i++)
        ulBaseToPowerMod = (ulBase * ulBaseToPowerMod) % ulPrime;

    // Calculate the hash function for the src (and the first dst)
    while (pbPattern < pbPatternMax)
    {
        ulHashPattern = (ulHashPattern*ulBase+*pbPattern) % ulPrime;
        ulHashTarget = (ulHashTarget*ulBase+*pbTarget) % ulPrime;
        pbPattern++;
        pbTarget++;
    }

    // Dynamically produce hash values for the string as we go
    for ( ;; )
    {
        // Remember to do the memcmp for the off-chance it doesn't work
        // according to probability
        if (    ulHashPattern == ulHashTarget
            && !memcmp(pbPattern-cbPattern, pbTarget-cbPattern,
            (UINT)cbPattern))
            return TRUE;

        // Assert because this is very unprobable
#ifdef DEBUG
        if (ulHashPattern == ulHashTarget)
            DebugTrace("This is very unprobable!\n");
#endif

        if (pbTarget == pbTargetMax)
            return FALSE;

        ulHashTarget = (ulHashTarget+ulBase*ulPrime-
            *(pbTarget-cbPattern)*ulBaseToPowerMod) % ulPrime;
        ulHashTarget = (ulHashTarget*ulBase+*pbTarget) % ulPrime;
        pbTarget++;
    }
}

BOOL
FRKFindSubpsz (LPSTR pszTarget,
    ULONG cbTarget,
    LPSTR pszPattern,
    ULONG cbPattern,
    ULONG ulFuzzyLevel)
{
    UINT    i;
    ULONG   ulBaseToPowerMod = 1;
    ULONG   ulHashPattern = 0;
    ULONG   ulHashTarget = 0;
    LCID    lcid = GetUserDefaultLCID();
    LPBYTE  pbTarget;
    LPBYTE  pbPattern;
    LPBYTE  pbTargetMax;
    LPBYTE  pbPatternMax;
    BOOL    fResult = FALSE;
    CHAR    *rgchHash;

    // Validate parameters

    switch (ulFuzzyLevel & (FL_IGNORECASE | FL_IGNORENONSPACE))
    {
      case 0:       
      default:
        rgchHash = rgchCsds;
        break;
        
      case FL_IGNORECASE:
        rgchHash = rgchCids;
        break;
        
      case FL_IGNORENONSPACE:
        rgchHash = rgchCsdi;
        break;
        
      case FL_IGNORECASE | FL_IGNORENONSPACE:
        rgchHash = rgchCidi;
        break;
    }

    if (ulFuzzyLevel & FL_LOOSE)
        rgchHash = rgchCids;

    pbTarget = (LPBYTE) pszTarget;
    pbPattern = (LPBYTE) pszPattern;
    pbTargetMax = pbTarget + cbTarget;
    pbPatternMax = pbPattern + cbPattern;

    if (cbPattern > cbTarget)
        goto end;

    // Compute the power of the left most character in base ulBase
    for (i = 1; i < cbPattern; i++)
        ulBaseToPowerMod = (ulBase * ulBaseToPowerMod) % ulPrime;

    // Calculate the hash function for the src (and the first dst)
    while (pbPattern < pbPatternMax)
    {
        ulHashPattern = (ulHashPattern*ulBase+rgchHash[*pbPattern]) % ulPrime;
        ulHashTarget = (ulHashTarget*ulBase+rgchHash[*pbTarget]) % ulPrime;
        pbPattern++;
        pbTarget++;
    }

    // Dynamically produce hash values for the string as we go
    for ( ;; )
    {
        if (ulHashPattern == ulHashTarget)
        {
            if (CompareStringA(lcid,
                ((ulFuzzyLevel & FL_IGNORECASE) ? NORM_IGNORECASE : 0) |
                ((ulFuzzyLevel & FL_LOOSE) ? NORM_IGNORECASE : 0) |
                ((ulFuzzyLevel & FL_IGNORENONSPACE) ? NORM_IGNORENONSPACE : 0),
                pbPattern-cbPattern, (UINT)cbPattern,
                pbTarget-cbPattern, (UINT)cbPattern) == 2)
            {
                fResult = TRUE;
                goto end;
            }
        }

#ifdef DEBUG
        if (ulHashPattern == ulHashTarget)
            DebugTrace ("This is very unprobable, unless you are doing "
                "FL_EXACT and an case insensitive match came up "
                "(or you are on DBCS)\n");
#endif

        if (pbTarget == pbTargetMax)
            goto end;

        ulHashTarget = (ulHashTarget+ulBase*ulPrime-
            rgchHash[*(pbTarget-cbPattern)]*ulBaseToPowerMod) % ulPrime;
        ulHashTarget = (ulHashTarget*ulBase+rgchHash[*pbTarget]) % ulPrime;
        pbTarget++;
    }

end:
    return fResult;
}
