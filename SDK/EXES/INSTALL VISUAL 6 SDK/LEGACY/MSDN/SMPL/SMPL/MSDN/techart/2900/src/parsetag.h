const chTagFieldSep    = '|';

class CParseText
{
public:
	const char *m_szBase;
	const char *m_szCur;

	CParseText(void) { Set(NULL); }
	CParseText(const char *szBase, const char *szCur = NULL) { m_szBase = szBase; m_szCur = szCur; }
	void Set(const char *szBase) { m_szBase = szBase; m_szCur = NULL; }
};

#define IsExampleField(i, nIsExampleTag, nNumFields) \
    (nIsExampleTag && (i == nNumFields-1))

int ParseTag(CSrcInput &in, FormatInfo &fmt, BOOL bAux, CTag *ptagAuxParent, BOOL bIsTopic);
int ParseSrc(CTag *ptag, CParseText &txt, int nSrcLine, int nParseType, BOOL bReqTerm);
CTag *AddTag(CTagList &listTags, long lLineTag, const char *szTag);

