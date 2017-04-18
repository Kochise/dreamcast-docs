#include <afx.h>
#include <afxtempl.h>
#include "input.h"
#include "errmsg.h"
#include "parse.h"

/**************************************************************************/

//@doc FILE ADINPUT

//@mfunc Constructs the input file object, zeroes the line
// buffer.

CAdInput::CAdInput(void)
{
	ZeroMem(&m_szLineBuf, MAXLINEBUFSIZE+1);
	m_lCurLine 	= 0;
	m_nAdState.Reuse = FALSE;
    m_nAdState.Append = FALSE;
	m_nAdState.EndOfFile = FALSE;
}




/***********************************************************/
// Input operations
/***********************************************************/

//@mfunc Gets a line from the input file and stores it in
// <md .m_szLineBuf>. If the Reuse state is set in <md .m_nAdState>
// the function simply returns without refreshing the buffer.
//
//@rdesc Zero or a file exception error from <c CFileException>.

int CAdInput::GetLine(void)
{
TRY
{
	ASSERT(m_hFile != NULL);
    char *sz;
    int  n;

	if(m_nAdState.Reuse)
	{
		m_nAdState.Reuse = FALSE;
		return 0;
	}

    if(m_nAdState.Append)
    {
        m_nAdState.Append = FALSE;

        n = strlen(m_szLineBuf);

		if(n >= 2 && m_szLineBuf[n-1] == '\n')
		{
			n -= 2;
			sz -= 2;
		}

        if(MAXLINEBUFSIZE - n <= 0) 
            return errMultilineOverflow;

        sz = m_szLineBuf + n;
    }
    else
    {
		ZeroMem(m_szLineBuf, MAXLINEBUFSIZE+1);

        n = 0;
        sz = m_szLineBuf;
    }

    if(ReadString(sz, MAXLINEBUFSIZE - n) == NULL)
		m_nAdState.EndOfFile = TRUE;
    
	m_lCurLine++;
        
    return 0;
}
CATCH(CFileException, e)
{
    return e->m_cause;
}
END_CATCH
}


//@mfunc Resets the <md .m_nAdState> variable.

void CAdInput::ResetState(void)
{
    ZeroMem(&m_nAdState, sizeof(m_nAdState)); 
}
