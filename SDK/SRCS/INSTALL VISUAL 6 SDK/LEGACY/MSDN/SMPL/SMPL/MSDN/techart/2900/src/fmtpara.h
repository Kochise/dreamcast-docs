class CFmtPara;
class CFmtListPara;

#define PARSE_PARA_BASE 100

class CFmtSrchPara : public CFmtSrchTag
{
};

class CMapPara
{
public:
    NAMETOKEN m_name[MAXNUMFIELDS];
	CString m_sName;
	CMapPara();
};

typedef CTypedPtrList<CPtrList, CMapPara *> CMapParaList;

class CFmtPara : public CFmtTag
{
friend CFmtListPara;

public:
	CFmtPara(void);
	~CFmtPara(void);


#ifdef _DEBUG
	void CFmtPara::Dump(CDumpContext &dc) const;
#endif

	//@enum Para source parsing options
	enum ParaParseType
	{
		parseMember = PARSE_PARA_BASE + 1,  //@emem Class member
		parseField,							//@emem Structure field
		parseParam, 						//@emem Parameter
        parseParamOpt,                      //@emem Optional parameter
		parseEmem,							//@emem Enumeration member
		parseBparam,						//@emem Basic parameter
		parseBfield,						//@emem Basic field
		parseMeth,							//@emem Method (no copy parm list)
	};

    int GetParseType() { return m_nParseType; }
    int IsExampleTag() { return m_nFlags.isExample; }
	int GetLevel()	   { return m_nLevel; }
	NAMETOKEN *GetMap(const char *szTag);

	CMapParaList m_mapPara;

private:
	// Member data items here

	int     m_nLevel;
    struct {
        unsigned isExample : 1;
    }       m_nFlags;

    int     m_nParseType;
};


class CFmtListPara  : public CFmtListTag
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum ParaTags { \
		tagPre, \
		tagPost, \
        tagFormat, \
        tagTag, \
		tagSrcParse,\
		tagIf,\
		tagMap};
};
