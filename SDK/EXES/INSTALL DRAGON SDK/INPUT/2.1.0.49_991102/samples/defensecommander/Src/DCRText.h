/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCRText.h

Abstract:

    Text rendering routines.

-------------------------------------------------------------------*/

#define FONT_SIZE_TINY		6
#define FONT_SIZE_SMALL		8
#define FONT_SIZE_MEDIUM	10
#define FONT_SIZE_MEDIUMLARGE 13
#define FONT_SIZE_LARGE		16

void RenderTextBegin(void);
void RenderTextEnd(void);
void RenderText(TCHAR *Text, float X, float Y, float Size, DWORD Color=0xFFFFFFFF);
int  GetNumLines(TCHAR *String);
int  GetMaxLineLength(TCHAR *String);