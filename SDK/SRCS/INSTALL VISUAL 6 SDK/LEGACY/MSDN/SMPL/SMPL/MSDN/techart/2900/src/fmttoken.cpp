#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "fmtToken.h"
#include "errmsg.h"




/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsTokenSection[] =
{
	CFmtListToken::tagOutput, 		"output",
    CFmtListToken::tagExtension,    "extension",
    CFmtListToken::tagToken,        "token",
	CFmtListToken::tagHighCharMask, "highcharmask",
    -1,        NULL,
};

TAGSPEC gtagsTokenTypes[] =
{
	-1, NULL,
};

const int gnTokens = 0;


/******************************************************/
// Format class
/******************************************************/

CFmtToken::CFmtToken(void) : CFmtBase(gnTokens)
{
    m_ptok = NULL;
}



CFmtToken::~CFmtToken(void)
{
    TOKEN *ptok, *ptokNext;

    for(ptok = m_ptok; ptok; ptok = ptokNext)
    {
        ptokNext = ptok->next;
        delete ptok;
    }
}


int CFmtToken::Validate(void)
{
    TOKEN *ptok;

    for(ptok = m_ptok; ptok; ptok = ptok->next)
        m_sControlChars += ptok->chToken;

    return 0;
}


CString &CFmtToken::GetToken(char ch)
{
    extern CString sEmpty;

    TOKEN *ptok;

    for(ptok = m_ptok; ptok; ptok = ptok->next)
        if(ptok->chToken == ch)
            return ptok->sOutput;

    return sEmpty;
}


#ifdef _DEBUG
void CFmtToken::Dump(CDumpContext &dc) const
{
	CFmtBase::Dump(dc);

	dc << "\tControl:\t\t\t[" << m_sControlChars << "]\n"
	   << "\tHigh char mask:\t\t[" << m_sHighCharMask << "]\n\n";
}
#endif



/******************************************************/
// List class
/******************************************************/

TAGSPEC *CFmtListToken::FmtTagList(void)
{
	return gtagsTokenSection;
}

int CFmtListToken::ParseEntry(CFmtInput &in)
{
	CFmtToken *pNew;
    const char *sz;
    static char szNameTerm[] = "\t ";
	int nRet;
	const char *szEnd;
    TOKEN *ptokNext;

	pNew = (CFmtToken *)m_pNew;
	    
	switch(m_nTag)
	{
	// Parent
	case tagOutput:
		
		// Expect: .output = output, extension

		if(in.m_nTokens != 2)
			return fmterrBadEntryCount;

		if(!CheckOutputType(in, 0))
			return 0;

        sz = EatWhite(in.m_aszTokens[1]);
        szEnd = SeekEnd(sz, szNameTerm, MAXTAGSIZE);
        if(szEnd == NULL)
            return fmterrBadFilenameExtension;

        // Make a new one

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

		m_pNew = pNew = new CFmtToken;

		m_nState.Tag = TRUE;

        // Record source file information.

        pNew->SetSource(in.m_nFile, in.m_lCurLine);
        pNew->m_sExtension = CString(sz, szEnd-sz);

        break;

	case tagToken:
		if(m_nState.Skip)
			return 0;

		if(!m_nState.Tag)
			return fmterrOrphanedTag;

       	// expect: .token=c, text

		if(in.m_nTokens != 2)
			return fmterrBadEntryCount;

        sz = EatWhite(in.m_aszTokens[0]);
        char ch;

        if(*sz == chCaret)
        {
            switch(sz[1])
            {
            case 'p': case 'P':
                ch = chNewline;
                break;

            case 't': case 'T':
                ch = chTab;
                break;

            default:
                return fmterrBadTokenCode;
            }
            sz++;
        }
        else
        {
            ch = *sz;
        }
        sz = EatWhite(++sz);
        if(*sz)
            return fmterrBadTokenCode;

        ptokNext = pNew->m_ptok ? pNew->m_ptok : NULL;

        pNew->m_ptok = new TOKEN;
        pNew->m_ptok->next = ptokNext;

        pNew->m_ptok->chToken = ch;
        pNew->m_ptok->sOutput = in.m_aszTokens[1];
        if(chNewline == ch)
            pNew->m_ptok->sOutput += "\r\n";
        
		break;

	case tagHighCharMask:
       
		if(m_nState.Skip)
			return 0;

		if(!m_nState.Tag)
			return fmterrOrphanedTag;

       	// expect: .highcharmask=text

		if(in.m_nTokens != 1)
			return fmterrBadEntryCount;

		// Assign mask.

		pNew->m_sHighCharMask = EatWhite(in.m_aszTokens[0]);

		break;

    default:
        return fmterrBadFmtEntry;
    }

    return 0;
}



int CFmtListToken::Validate(void)
{
    if(m_listTags.GetCount() == 0)
        return fmterrNoTokenDefinitions;

    return 0;
}
