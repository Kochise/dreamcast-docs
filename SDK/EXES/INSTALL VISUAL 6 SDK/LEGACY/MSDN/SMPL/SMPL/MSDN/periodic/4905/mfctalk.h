// MFCTALK.CPP - Implementation file for your Internet Server
//    MFCTalk Extension

class CMFCTalkExtension : public CHttpServer
{
public:
	CMFCTalkExtension();
	~CMFCTalkExtension();

	BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);

protected:
	CCriticalSection m_ListCritical;
	CStringList m_ListContent;

protected:
	void GetCharacter();
	void WriteChatForm(CHttpServerContext* pCtxt);
	void WriteRoomContent(CHttpServerContext* pCtxt, int nTimes);

	void AddComment(LPCTSTR pstrName, LPCTSTR pstrSays);

public:
	void StartContent(CHttpServerContext* pCtxt);

	void Default(CHttpServerContext* pCtxt, int nTimes);
	void Comment(CHttpServerContext* pCtxt, LPCTSTR pstr);
	void Refresh(CHttpServerContext* pCtxt, int nTimes);

	DECLARE_PARSE_MAP()
};

