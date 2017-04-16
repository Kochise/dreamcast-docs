// OLDBROW.CPP - Implementation file for your Internet Server
//    OldBrow Filter


class COldBrowFilter : public CHttpFilter
{
public:
	COldBrowFilter();
	~COldBrowFilter();

	BOOL GetFilterVersion(PHTTP_FILTER_VERSION pVer);

	DWORD OnUrlMap(CHttpFilterContext* pCtxt,
		PHTTP_FILTER_URL_MAP pMapInfo);

	// TODO: Add your own overrides here
};
