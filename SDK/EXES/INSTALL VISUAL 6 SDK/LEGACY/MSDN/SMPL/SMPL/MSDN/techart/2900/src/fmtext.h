class CFmtExt;
class CFmtListExt;

enum SOURCETYPES
{
    sourceC = 1,            //@emem C/C++ source file.
    sourceBas,              //@emem Basic source file.
    sourceAsm,              //@emem Assembly source file.
};

class CFmtSrchExt : public CFmtSrchBase
{
public:
    CString m_sExt;
};

class CFmtExt : public CFmtBase
{
friend CFmtListExt;

public:
	CFmtExt(void);
    int Match(CFmtSrchBase *p);
#ifdef _DEBUG
	void Dump(CDumpContext &dc) const;
#endif

    int GetSourceType(void) { return m_nSrcType; }

private:
	// Member data items here

    CString m_sExt;
    int m_nSrcType;
};


class CFmtListExt  : public CFmtList
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum ExtTags { tagExt, };
};
