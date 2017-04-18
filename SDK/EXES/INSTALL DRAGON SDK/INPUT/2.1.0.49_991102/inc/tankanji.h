/*
    TanKanji IME

    Copyright (c) 1998, Microsoft Corporation

    APIs

    HTK  TKOpen(WCHAR *pwsz)

	This function opens the TanKanji database.  The returned HTK passed to all future calls relating
    to this database.  Note that a single application can open multi TanKanji databases and that multiple
    applications can open the same TanKanji database simultaneously.

    BOOL TKClose(HTK htk)

	End the use of this TanKanji database by this session.	You can call TKOpen to reopen the database,
    but future calls with handle will not work.


    BOOL TKMatch(HTK htk, WCHAR *pwszKana, DWORD cwcKanji, WCHAR *pwszKanji)

	Given a kana pronunciation, return the list of Kanji that match.  pwszKana contains the input
    pronunciation and pwszKanji will contain the null terminated string of Kanji.  cwcKanji gives the
    limit of pwszKanji.

*/

typedef HANDLE	HTK;

#ifdef __cplusplus
extern "C" {
#endif

	HTK  TKOpen(WCHAR *);
	BOOL TKClose(HTK);
	BOOL TKMatch(HTK, WCHAR *, DWORD, WCHAR *);
#ifdef __cplusplus
};
#endif
