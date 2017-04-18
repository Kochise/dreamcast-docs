//-----------------------------------------------------------------------------
// File: WinMain.cpp
//
// Desc: Windows management for DirectMusic sample
//
//
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include <windows.h>
#include "PlayPri.h"

#define IS_SPACE(c)   ((c) == TEXT(' ') || (c) == TEXT('\r') || (c) == TEXT('\n') || (c) == TEXT('\t'))

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    RetailOutput

Description:

    Simple Retail Output mechanism.  If the function outputs
    the passed-in String and variables to the debug output stream.

Arguments:

    TCHAR *tszDest       - TEXT String to output

    ... (variable arg)   - List of variable arguments to embed in output
                           (similar to printf format)

Return Value:

    None

-------------------------------------------------------------------*/
void RetailOutput(TCHAR *tszErr, ...)
{
    TCHAR tszErrOut[256];

    va_list valist;

    va_start(valist,tszErr);
    wvsprintf(tszErrOut, tszErr, valist);
    OutputDebugString(tszErrOut);
    va_end (valist);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pszCmdLine, int nCmdShow)
{
    HRESULT hr;
    LPTSTR pszPath = TEXT("\\Windows");
    LPTSTR pszSegment;
    int nRepeats = 0;

    while(*pszCmdLine == TEXT('-'))
	{
        ++pszCmdLine;

        switch(*pszCmdLine)
		{
        case TEXT('P'):
        case TEXT('p'):                 // set the default path
            {
                TCHAR c = *pszCmdLine;

                // Skip over any non-whitespace we ignored from the last token
                while(!IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
				{
                    ++pszCmdLine;
				}

                while(IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
                {
                    ++pszCmdLine;
                }
                pszPath = pszCmdLine;
                break;
			}
			break;
        case TEXT('R'):
        case TEXT('r'):                 // set the number of repeats
            {
                TCHAR c = *pszCmdLine;

                // Skip over any non-whitespace we ignored from the last token
                while(!IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
				{
                    ++pszCmdLine;
				}

                while(IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
                {
                    ++pszCmdLine;
                }
                nRepeats = _ttoi(pszCmdLine);
                break;
			}
			break;
        case TEXT('?'):
        case TEXT('h'):
        case TEXT('H'):
            {
                RetailOutput(TEXT("Usage: playprimary [-p searchpath] [-r #repeats] [segment]\r\n")
                             TEXT("       default search path: \\Windows\r\n")
                             TEXT("       default segment: Sample.sgt\r\n\r\n")
                             TEXT("Important: See the readme.txt for this sample for more information.\r\n"));
                return 0;
            }
			break;
        }

        // Skip to next token
		// Skip over any non-whitespace we ignored from the last token
        while(!IS_SPACE(*pszCmdLine) && (*pszCmdLine != TEXT('\0')))
		{
            ++pszCmdLine;
		}
        if(*pszCmdLine == TEXT('\0'))
        {
            break;
        }
        *pszCmdLine++ = TEXT('\0');

        // Skip over white space between tokens
        while(IS_SPACE(*pszCmdLine))
		{
            ++pszCmdLine;
		}
    }

    pszSegment = pszCmdLine;
    if(*pszSegment == TEXT('\0'))
    {
        pszSegment = TEXT("sample.sgt");
    }

    hr = InitDirectMusic(pszPath);
    if(FAILED(hr))
    {
        FreeDirectMusic();
        return FALSE;
    }

    PlaySegment(pszSegment, nRepeats);

    FreeDirectMusic();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));
    return TRUE;
}
