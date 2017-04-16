#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "fmtconst.h"
#include "errmsg.h"


/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsConstSection[] =
{
	CFmtListConst::tagDefine,           "define",
	CFmtListConst::tagOutput,           "output",
    -1,        NULL,
};


/******************************************************/
// Format class
/******************************************************/

CFmtConst::CFmtConst(void) : CFmtBase(1)
{
}



CFmtConst::CFmtConst(const char *szName, const char *szText) : CFmtBase(1)
{
    m_sName = szName;
    
    m_aFmtStrings[0] = new CString(szText);
}



int CFmtConst::Match(CFmtSrchBase *psrch)
{
	CFmtSrchConst *psrchConst = (CFmtSrchConst *)psrch;

	ASSERT(psrchConst);

    // See if tag names match

    return _strcmpi(psrchConst->m_sName, m_sName) == 0;
}

#ifdef _DEBUG
void CFmtConst::Dump(CDumpContext &dc) const
{
	CFmtBase::Dump(dc);

	dc << "\tName: "<< m_sName;
}
#endif





/******************************************************/
// List class
/******************************************************/

TAGSPEC *CFmtListConst::FmtTagList(void)
{
	return gtagsConstSection;
}
	

int CFmtListConst::ParseEntry(CFmtInput &in)
{
	CFmtConst *pNew;
    const char *sz;
    const char *szEnd;
    static char szNameTerm[] = "\t ";
	int nRet;
    
	switch(m_nTag)
	{
	// Parent

	case tagOutput:
		
		// Expect: .output = output

		if(in.m_nTokens != 1)
			return fmterrBadEntryCount;

		CheckOutputType(in, 0);

        break;

    case tagDefine:
        // expect: .define=name , format string

    	if(m_nState.Skip)
    		return 0;

		if(in.m_nTokens < 2)
			return fmterrBadEntryCount;

        // Make a new one

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

		m_pNew = pNew = new CFmtConst;

		m_nState.Tag = TRUE;

        // Get the constant name.

        if((sz = SeekLetter(in.m_aszTokens[0])) == NULL)
            return fmterrExpectedName;
    
        szEnd = SeekEnd(sz, szNameTerm, MAXTAGSIZE);
        if(szEnd == NULL)
            return fmterrBadTagName;

        pNew->m_sName = CString(sz, szEnd-sz);

        sz = szEnd;

        // Record source file information.

        pNew->SetSource(in.m_nFile, in.m_lCurLine);
		
		// Set the format string.

		nRet = SetFmtString(in, 1);

		if(nRet)
			return nRet;
		break;

    default:
        return fmterrBadFmtEntry;
    }

    return 0;
}

