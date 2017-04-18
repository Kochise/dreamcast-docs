#include "vsp_asc.h"
#include "vsctop.h"
#include "vs_asc.pro"

#define EOF (-1)

/************************** ROUTINES *****************************************/

/******************************************************************************
*				ASC_INIT				      *
*	Initialize the data union data structure				   *
******************************************************************************/
VW_ENTRYSC  SHORT  VW_ENTRYMOD	VwStreamOpenFunc (fp, FileId, FileName, FilterInfo, hProc)
SOFILE	fp;
SHORT	FileId;
BYTE VWPTR	*FileName;
SOFILTERINFO	VWPTR	*FilterInfo;
HPROC	hProc;
{
	char	chread[10];
	SHORT	ch;
	SHORT	chCount;
	SHORT	done;
	SHORT	locText;

	if ( FilterInfo != NULL )
	{
		FilterInfo->wFilterCharSet = SO_PC;
		strcpy ( FilterInfo->szFilterName, VwStreamIdName[0].FileDescription );
	}

	Proc.AscSave.SeekSpot = 0L;
	Proc.AscSave.lastchar = 0;
	Proc.bFileIsText = FALSE;

	Proc.hFile = _lopen ( (LPCSTR) FileName, OF_READ | OF_SHARE_DENY_WRITE );
	if (Proc.hFile == HFILE_ERROR)
		return -1;

	_llseek (Proc.hFile, 0L, 0);

	chCount	= 0;
	done		= FALSE;
	locText	= TRUE;

	do {
		if (chCount >= 512)
			break;

		if (0==_lread (Proc.hFile, chread, 1) )
			ch=EOF;
		else
			ch=chread[0];

		chCount ++;
		switch (ch)
			{
			case EOF:
				done=TRUE;
				break;

			case 0x0d:		// CR
			case 0x08:		// Backspace
			case 0x0a:		// NL
			case 0x09:		// TAB
			case 0x0c:		// NEW PAGE
			case 0x1a:	   // ASCII EOF
			case 0x00:		// NULL
			case 0xc6:		// 850 - a tilde
			case 0xc7: 		// 850 - A tilde
				break;

			default:
				if ( (ch>=0x20) && (ch<=0x7F) )
					break;
				if ( ch >= 0x80 && ch <= 0xA5 )
					break;
				if ( ch >= 0xD0 && ch <= 0xD8 )
					break;
				if ( ch >= 0xE0 && ch <= 0xEF )
					break;
				if ( ch >= 0xB5 && ch <= 0xB7 )
					break;
				locText = FALSE;
				done = TRUE;
			}

		}while (done == FALSE);

	if (locText)
		Proc.bFileIsText = TRUE;

	_llseek (Proc.hFile, 0L, 0);

	return ( 0 );
}

VW_ENTRYSC VOID VW_ENTRYMOD VwStreamCloseFunc(SOFILE hFile, HPROC hProc)
{
	_lclose ( Proc.hFile );
}

VW_ENTRYSC SHORT VW_ENTRYMOD VwStreamSeekFunc(hFile,hProc)
SOFILE	hFile;
HPROC	hProc;
{
	return((SHORT)_llseek(Proc.hFile,Proc.VwStreamSaveName.SeekSpot,0));
}

VW_ENTRYSC SHORT VW_ENTRYMOD VwStreamTellFunc(hFile,hProc)
SOFILE	hFile;
HPROC	hProc;
{
	Proc.VwStreamSaveName.SeekSpot = _llseek(Proc.hFile,0L, 1);
	return(0);
}

/******************************************************************************
*				ASC_SECTION_FUNC			      *
******************************************************************************/
VW_ENTRYSC  SHORT  VW_ENTRYMOD	VwStreamSectionFunc (fp, hProc)
SOFILE	fp;
HPROC	hProc;
{
	SOPutSectionType ( SO_PARAGRAPHS, hProc );
	return(0);
}

VW_ENTRYSC  SHORT  VW_ENTRYMOD	VwStreamReadFunc (fp, hProc)
SOFILE	fp;
HPROC	hProc;
{
	SHORT	ch;
	char  chread[10];
	SHORT	chCount;
	SHORT	chTabs;
	SHORT	type, done;

	type = SO_PARABREAK;

	do {
		chCount	= 0;
		chTabs	= 0;
		done		= FALSE;

		do {
			if (0==_lread (Proc.hFile, chread, 1) )
				ch=EOF;
			else
				ch=chread[0];

			if ((ch >= 0x20) && (ch <= 0x7e))
				{
				chCount++;
				SOPutChar ( ch, hProc );
				}
			else if (ch == 0x09)
				{
				chCount++;
				chTabs++;
				SOPutSpecialCharX ( SO_CHTAB, SO_COUNT, hProc );
				}
			else if (ch == 0x0c)
				{
				chCount++;
				SOPutSpecialCharX ( SO_CHHPAGE, SO_COUNT, hProc );
				}
			else if (ch == EOF)
				{
				type = SO_EOFBREAK;
				done = TRUE;
				}
			else if (ch == 0x0a)
				{
				if (Proc.AscSave.lastchar != 0x0d)
					{
					done = TRUE;
					}
				else
					{
					ch = 0x00;
					}
				}
			else if (ch == 0x0d)
				{
				if (Proc.AscSave.lastchar != 0x0a)
					{
					done = TRUE;
					}
				else
					{
					ch = 0x00;
					}
				}
			else if (Proc.bFileIsText)
				{
				// Put out logical extended TEXT characters ...
				if ( ( ch >= 0x80 && ch <= 0xA5 ) ||
					  ( ch >= 0xD0 && ch <= 0xD8 ) ||
					  ( ch >= 0xB5 && ch <= 0xB7 ) ||
					  ( ch == 0xC6) ||
					  ( ch == 0xC7) ||
					  ( ch >= 0xE0 && ch <= 0xEF ) )

					{
					chCount++;
					SOPutChar ( ch, hProc );
					}
				}

			if (chCount > 2048 || chTabs > 10)
				done = TRUE;

			Proc.AscSave.lastchar = ch;

			} while ( !done );

		} while ( SOPutBreak (type, (LONG) NULL, hProc) != SO_STOP );

	return ( 0 );

}  /** end of file **/

