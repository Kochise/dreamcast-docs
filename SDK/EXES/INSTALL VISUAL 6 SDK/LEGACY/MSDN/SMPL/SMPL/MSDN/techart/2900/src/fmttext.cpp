#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "topiclog.h"
#include "input.h"
#include "fmt.h"
#include "fmtif.h"
#include "fmttag.h"
#include "fmttext.h"
#include "errmsg.h"


/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsTextSection[] =
{
    CFmtListText::tagTag,	  		"tag",
    CFmtListText::tagFormat,   		"format",
    CFmtListText::tagIf,	  		"if",
    -1,        NULL,
};


/******************************************************/
// Format class
/******************************************************/

CFmtText::CFmtText(void) : CFmtTag(1)
{
}

/******************************************************/
// List class
/******************************************************/

TAGSPEC *CFmtListText::FmtTagList(void)
{
	return gtagsTextSection;
}
	

int CFmtListText::ParseEntry(CFmtInput &in)
{
	int nRet;

	CFmtText *pNew;

	pNew = (CFmtText *)m_pNew;

	switch(m_nTag)
	{
	// Parent

	case tagTag:
		
		// Expect: .tag = name, output, fields

		if(in.m_nTokens != 3)
			return fmterrBadEntryCount;

		if(!CheckOutputType(in, 1))
			return 0;

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

		m_pNew = pNew = new CFmtText;

		m_nState.Tag = TRUE;

        // Record source file information.

        pNew->SetSource(in.m_nFile, in.m_lCurLine);

        // Get the required Name field.
        
		nRet = ParseName(pNew->m_sName, in.m_aszTokens[0]);
		if(nRet)
			return nRet;        

        // Get the required number of fields
        
        nRet = ParseNumFields(pNew->m_nNumFields, in.m_aszTokens[2]);
		if(nRet)
			return nRet;
        
        break;
    
    case tagIf:
        
        nRet = ParseIf(*pNew, in);
        if(nRet)
           return nRet;

        break;

    // Text formatting string

    case tagFormat:

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

