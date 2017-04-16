
//===============================================================
//  MODULE: dprintf()
//
//  HISTORY:
//  Tom McConnell   01/18/93    Created.
//  raypa           07/09/93    ifdef DEBUG.
//===============================================================

#include <string.h>
#include <stdio.h>
#include <windows.h>

#ifdef DEBUG

//===============================================================
//  dprintf()
//	
//  Handles dumping info to OutputDebugString
//
//  HISTORY:
//
//  Tom McConnell   1/18/93     Created
//===============================================================

static void dprintf(char *format, ...)
{
  va_list args;
  char    buffer[255];

  va_start(args,format);

  strcpy(buffer + vsprintf(buffer,format,args), "\r\n");

  OutputDebugString(buffer);
}

#endif
