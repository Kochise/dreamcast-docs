/*
    pmgrpapi.h

    Exported functions from pmgrpapi

*/

extern BOOL FAR PASCAL pmCreateGroup(LPSTR lpszGroup, LPSTR lpszPath);
extern BOOL FAR PASCAL pmDeleteGroup(LPSTR lpszGroup);
extern BOOL FAR PASCAL pmShowGroup(LPSTR lpszGroup, WORD wCmd);
extern BOOL FAR PASCAL pmAddItem(LPSTR lpszCmdLine,
                                 LPSTR lpszCaption,
                                 LPSTR lpszIconPath,
                                 WORD wIconIndex);
extern BOOL FAR PASCAL pmDeleteItem(LPSTR lpszItem);
extern BOOL FAR PASCAL pmReplaceItem(LPSTR lpszItem);
extern BOOL FAR PASCAL pmReload(LPSTR lpszGroup);
extern BOOL FAR PASCAL pmExit(BOOL bSaveGroups);

