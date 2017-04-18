class CFmtConst;
class CFmtListConst;

class CFmtSrchConst : public CFmtSrchBase
{
public:
    CString m_sName;
};

class CFmtConst : public CFmtBase
{
friend CFmtListConst;

public:
	CFmtConst(void);
	CFmtConst(const char *szName, const char *szText);
 	int Match(CFmtSrchBase *psrch);
#ifdef _DEBUG
	void Dump(CDumpContext &dc) const;
#endif

private:
	// Member data items here

    CString m_sName;
};


class CFmtListConst  : public CFmtList
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum ConstTags { \
		tagDefine, \
		tagOutput, \
    };
};
