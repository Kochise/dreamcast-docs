/********************************************************************
 *  Copyright (C) 1996 Microsoft Corporation.
 *
 *  File:       OUTPUT.CPP
 *  Content:    Text output for DINPUT sample program, using a
                  non-scrolling window
 *  Author:     Peter Donnelly
 *  Tool:       Visual C++ 4.0
 *
 ********************************************************************/

#include <WINDOWS.H>
#include "output.h"

static int TextY = 0;    // location of the current line

void TextToScreen(HWND hwnd, char *z)
  {
     HDC         hdc;
     TEXTMETRIC  textmetric;
     RECT        windowrect;
     
     hdc = GetDC(hwnd);
     GetTextMetrics(hdc, &textmetric);
     GetClientRect(hwnd, &windowrect);
     if (TextY >= (windowrect.bottom - textmetric.tmHeight))
       ClearScreen(hwnd);
     TextOut(hdc, 5, TextY, z, strlen(z));
     TextY += (textmetric.tmHeight + textmetric.tmExternalLeading);
     ReleaseDC(hwnd, hdc);
  }

void ClearScreen(HWND hwnd)
  {
  HDC         hdc;

  hdc = GetDC(hwnd);
  InvalidateRect(hwnd, NULL, TRUE);
  SendMessage(hwnd, WM_PAINT, (WPARAM) hdc, NULL);
  TextY = 0; 
  ReleaseDC(hwnd, hdc);
  }
