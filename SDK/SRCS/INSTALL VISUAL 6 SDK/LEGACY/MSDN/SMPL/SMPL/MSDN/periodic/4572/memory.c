// MEMORY.C: Boring memory manager stuff

#include "windonut.h"

LPVOID MEMORY_New ( DWORD dwSize )
{
  LPVOID lpv;
  HGLOBAL hMem = GlobalAlloc (GHND, dwSize);
  if (!hMem) return NULL;
  lpv = (LPVOID)GlobalLock(hMem);
  if (!lpv) GlobalFree(hMem);
  return lpv;
}

BOOL MEMORY_Delete ( LPVOID lpv )
{
  HGLOBAL hMem = GlobalHandle (lpv);
  if (hMem)
    {
    GlobalFree(hMem);
    return TRUE;
    }
  return FALSE;
}
