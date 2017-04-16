
extern "C"
{

HRESULT CountArgsInFormat(LPCTSTR pszFmt, UINT FAR *pn);
LPCTSTR GetNextVarType(LPCTSTR pszFmt, VARTYPE FAR* pvt);
HRESULT CreateObject(LPOLESTR pszProgID, IDispatch FAR* FAR* ppdisp);

OLECHAR * MakeCellIndex(char *letter, int iIndex)
{
 char szBuf[6];   // BUGBUG - don't hardcode
 wsprintf(szBuf,"%s%d",letter,iIndex);
 return ConvertToUnicode(szBuf);
};

}
