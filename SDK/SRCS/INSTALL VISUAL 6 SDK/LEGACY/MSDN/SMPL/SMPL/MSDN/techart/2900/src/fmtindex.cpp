#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "fmtindex.h"
#include "errmsg.h"


/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsIndexSection[] =
{
	CFmtListIndex::tagPre,              "pre",
	CFmtListIndex::tagPost,             "post",
    CFmtListIndex::tagPreName,          "prename",
    CFmtListIndex::tagPostName,         "postname",
    CFmtListIndex::tagPreContext,       "precontext",
    CFmtListIndex::tagPostContext,      "postcontext",
    CFmtListIndex::tagOutput,           "output",
    -1,        NULL,
};


/******************************************************/
// Format class
/******************************************************/

CFmtIndex::CFmtIndex(void) : CFmtBase(6)
{
}


/******************************************************/
// List class
/******************************************************/


TAGSPEC *CFmtListIndex::FmtTagList(void)
{
	return gtagsIndexSection;
}
	

int CFmtListIndex::ParseEntry(CFmtInput &in)
{
	int nRet;

	CFmtIndex *pNew;

	pNew = (CFmtIndex *)m_pNew;

	switch(m_nTag)
	{
	// Parent

	case tagOutput:
		
		// Expect: .output = output

		if(in.m_nTokens != 1)
			return fmterrBadEntryCount;

		if(!CheckOutputType(in, 0))
			return 0;

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

        // Make a new one

		m_pNew = pNew = new CFmtIndex;

		m_nState.Tag = TRUE;

        // Record source file information.

        pNew->SetSource(in.m_nFile, in.m_lCurLine);

        break;

    case tagPre:
    case tagPost:
    case tagPreName:
    case tagPostName:
    case tagPreContext:
    case tagPostContext:
		// expect: .pre= format string

		nRet = SetFmtString(in, 0);

		if(nRet)
			return nRet;
		break;

    default:
        return fmterrBadFmtEntry;
    }

    return 0;
}

