class CFmtDiagram;
class CFmtListDiagram;

class CFmtDiagram : public CFmtTag
{
friend CFmtListDiagram;

public:
	CFmtDiagram(void);
    ~CFmtDiagram(void);
#ifdef _DEBUG
	void CFmtDiagram::Dump(CDumpContext &dc) const;
#endif

    CStrArray &GetNullParas(void) { return m_asNullParas; }
    const char *GetDiagramItem(void) { return m_sItem; }

private:
	// Member data items here

    CString   m_sItem;
    CStrArray m_asNullParas;
};


class CFmtListDiagram  : public CFmtListTag
{
protected:
	// Override to return the list
	TAGSPEC *FmtTagList(void);
	
	int ParseEntry(CFmtInput &in);

public:
	enum DiagramTags { \
		tagPre, \
		tagPost, \
        tagFormat, \
        tagFormatFirst,\
        tagFormatLast,\
        tagTag,\
        tagIf,\
        tagNullParas, };
};
