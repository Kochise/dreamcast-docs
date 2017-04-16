class CFmtTopic;
class CFmtListTopic;

#define PARSE_TOPIC_BASE 200

class CFmtSrchTopic : public CFmtSrchTag
{
};

class CFmtTopic : public CFmtTag
{
friend CFmtListTopic;

public:
	CFmtTopic(void);
    CFmtTopic::~CFmtTopic(void);

#ifdef _DEBUG
	void CFmtTopic::Dump(CDumpContext &dc) const;
#endif

	//@enum Topic source parsing options
	enum TopicParseType
	{
		parseFunc = PARSE_TOPIC_BASE + 1,	//@emem C function - type and name
		parseMfunc,		//@emem C++ member function - type, class, name
		parseClass,		//@emem C++ class - name
		parseEnum,		//@emem C enumeration type
		parseConstant,  //@emem C enumeration type
		parseBsub,		//@emem Basic subroutine
		parseBfunc,		//@emem Basic function
		parseStruct,	//@emem Structure - new C++ style tag name
		parseBtype,		//@emem Basic type
		parseUnion,		//@emem C++ style union declaration
	};

    void PrintName(char *szNameBuf, CTag *ptag);
    void PrintContext(char *szCtxBuf, CTag *ptag);
    int GetSortWeight(void) { return m_nSortWeight; }
    int GetParseType() { return m_nParseType; }

	CList<CString *, CString *&> m_listParaTags;

private:
	// Member data items here

    int m_nSortWeight;

    NAMETOKEN m_aNameTok[MAXTOPICNAMETOKENS];
	int m_nNameTokens;
    NAMETOKEN m_aCtxTok[MAXTOPICNAMETOKENS];
	int m_nCtxTokens;

    int m_nParseType;

    long m_lExtractNumber;
};


class CFmtListTopic  : public CFmtListTag
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum TopicTags { \
		tagPre, \
		tagPost, \
        tagTag, \
		tagContext, \
		tagTopicOrder, \
		tagSrcParse,\
		tagIf};
};
