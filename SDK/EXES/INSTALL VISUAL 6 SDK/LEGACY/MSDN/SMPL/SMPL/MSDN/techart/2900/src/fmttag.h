#define MAXNUMIFS 6

class CFmtListTag;

//@doc FMT TAGSEARCH

//@class Tag search class. Provides data members
// to specify name, topic log, etc.
class CFmtSrchTag : public CFmtSrchBase
{
public:
    //@cmember Constructs the query object.
	CFmtSrchTag(void);

    //@cmember Tag name.
	CString m_sName;

    //@cmember Pointer to topic log. Used for lookups.
	CTopicLog *m_pLog;

    //@cmember Pointer to <c CTag> object for the 
    // tag being looked up.

	CTag *m_ptagTag;

    //@cmember Pointer to tag list for topic.

	CTagList *m_plistTags;
};

//@doc FMT TAGBASE

//@class Base class for all tag classes - topic,
// paragraph, and text.

class CFmtTag : public CFmtBase
{
friend CFmtListTag;

public:
    //@cmember Constructs the tag object.

	CFmtTag(int nFmtStrings = 0);

    //@cmember Destructs the tag.

	~CFmtTag(void);

    //@cmember Compares a tag against a <c CFmtSrchTag> object.

	int Match(CFmtSrchBase *psrch);

    //@cmember Returns the field count for the tag.

    int GetNumFields(void) { return m_nNumFields; }

#ifdef _DEBUG
    //@cmember Dumps the tag to the dump context.

    void Dump(CDumpContext &dc) const;
#endif

protected:
	// Member data items here

	int m_nNumFields;           //@cmember Tag field count

    CString m_sName;            //@cmember Tag name

	PIFCONDITION m_apIf[MAXNUMIFS]; //@cmember Array of IF condition lists
	int m_nNumIf;                   //@cmember How many IF condition lists
};


//@doc FMT TAGLIST

//@class Tag list class. Provides helper functions for parsing
// all types of tags.

class CFmtListTag  : public CFmtList
{

protected:
    //@cmember Parse field count value.

	int ParseNumFields(int &nFields, const char *&sz);

    //@cmember Parse IF statement

    int ParseIf(CFmtTag &tag, CFmtInput &in);

    //@cmember Parse tag name.

	int ParseName(CString &sName, const char *&sz);

    //@cmember Parse source parsing specifier.

    int ParseSrcParse(int &nParse, CFmtInput &in, TAGSPEC *pTypes);
};

