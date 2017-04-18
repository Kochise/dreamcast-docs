#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "fmtfile.h"
#include "errmsg.h"


/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsFileSection[] =
{
    CFmtListFile::tagPre,    "pre",
    CFmtListFile::tagPost,   "post",
    CFmtListFile::tagOutput, "output",
    -1,        NULL,
};




/******************************************************/
// List class
/******************************************************/


TAGSPEC *CFmtListFile::FmtTagList(void)
{
	return gtagsFileSection;
}
	

int CFmtListFile::ParseEntry(CFmtInput &in)
{
	int nRet;

	switch(m_nTag)
	{
	// Parent

	case tagOutput:
		
		// Expect: .output = output_type

		if(in.m_nTokens != 1)
			return fmterrFileOutputNum;

		if(!CheckOutputType(in, 0))
			return 0;

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

		m_pNew = new CFmtFile;

        m_pNew->SetSource(in.m_nFile, in.m_lCurLine);

		m_nState.Tag = TRUE;

		break;

    // RTF file header and footer

    case tagPre:
    case tagPost:

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



