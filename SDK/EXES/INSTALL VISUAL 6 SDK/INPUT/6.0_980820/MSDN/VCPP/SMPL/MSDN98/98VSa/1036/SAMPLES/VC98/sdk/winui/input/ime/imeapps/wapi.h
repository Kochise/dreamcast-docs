/* Unicode/Ansi stubs */
#ifdef USEWAPI
typedef LPWSTR            LPMYSTR;
typedef WCHAR             MYCHAR;
#define MYTEXT(x)         L ## x
#define Mylstrlen(x)      lstrlenW(x)
#define Mylstrcpy(x, y)   MylstrcpyW((x), (y))
#define Mylstrcat(x, y)   MylstrcatW((x), (y))
#define Mylstrcmp(x, y)   MylstrcmpW((x), (y))
#define MyCharPrev(x, y)  MyCharPrevW((x), (y))
#define MyCharNext(x)     MyCharNextW(x)
#define LPMYIMEMENUITEMINFO LPIMEMENUITEMINFOW
#define MYIMEMENUITEMINFO IMEMENUITEMINFOW
#define MyImmGetImeMenuItems  ImmGetImeMenuItemsW
#define MyImmGetCompositionString ImmGetCompositionStringW
#else
typedef LPTSTR            LPMYSTR;
typedef TCHAR             MYCHAR;
#define MYTEXT(x)         x
#define Mylstrlen(x)      lstrlen(x)
#define Mylstrcpy(x, y)   lstrcpy((x), (y))
#define Mylstrcat(x, y)   lstrcat((x), (y))
#define Mylstrcmp(x, y)   lstrcmp((x), (y))
#define MyCharPrev(x, y)  AnsiPrev((x), (y))
#define MyCharNext(x)     AnsiNext(x)
#define LPMYIMEMENUITEMINFO LPIMEMENUITEMINFO
#define MYIMEMENUITEMINFO IMEMENUITEMINFO
#define MyImmGetImeMenuItems  ImmGetImeMenuItems
#define MyImmGetCompositionString ImmGetCompositionString
#endif

#ifdef USEWAPI
int PASCAL MylstrcmpW(LPWSTR lp0, LPWSTR lp1);
int PASCAL MylstrcpyW(LPWSTR lp0, LPWSTR lp1);
int PASCAL MylstrcatW(LPWSTR lp0, LPWSTR lp1);
LPWSTR PASCAL MyCharPrevW(LPWSTR lpStart, LPWSTR lpCur);
LPWSTR PASCAL MyCharNextW(LPWSTR lp);
#endif
