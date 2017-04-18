//@doc FMTTOKEN

class CFmtToken;
class CFmtListToken;

struct TOKEN
{
    char chToken;
    CString sOutput;
    TOKEN *next;
};

class CFmtToken : public CFmtBase
{
friend CFmtListToken;

public:
	CFmtToken(void);
    ~CFmtToken(void);

    int Validate(void);

#ifdef _DEBUG
	void Dump(CDumpContext &dc) const;
#endif
	CString &GetToken(char ch);
	CString &GetHighCharMask(void)  { return m_sHighCharMask; }
    BOOL IsToken(char ch) { return m_sControlChars.Find(ch) != -1; }
    CString &GetExtension(void) { return m_sExtension; }

private:
	// Member data items here

    CString   m_sControlChars;
	CString   m_sHighCharMask;
    CString   m_sExtension;
    TOKEN *m_ptok;
};


class CFmtListToken  : public CFmtList
{
public:
    int Validate(void);

protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum TokenTags { tagToken, tagOutput, tagHighCharMask, tagExtension, };
};
