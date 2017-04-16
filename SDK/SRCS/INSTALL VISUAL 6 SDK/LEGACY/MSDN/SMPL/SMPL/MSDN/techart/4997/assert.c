//
// assert.c
//
// Provides basic assert services for C and C++ source modules.
//

#include <windows.h>
#include "assert.h"

#ifdef _DEBUG
CHAR szText [256];

void AssertFailedLine(LPCSTR lpszFilename, int nLine)
{
    wsprintf (szText, "File: %s, Line: %d", lpszFilename, nLine);
    MessageBox (NULL, szText, "ASSERT", MB_APPLMODAL | MB_ICONERROR);
}
#endif // DEBUG