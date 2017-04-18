///////////////////////////////////////////////////////////////////////////////
//
//  FILE: textcopy.h
//              
//      Header for text and image copy application
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

// function prototypes
int Cleanup (PDBPROCESS);
extern "C" int ErrorHandler (PDBPROCESS, INT, INT, INT, LPCSTR, LPCSTR);
extern "C" int MessageHandler (PDBPROCESS, DBINT, INT, INT, LPCSTR, LPCSTR, LPCSTR, DBUSMALLINT);
int DisplayUsage (void);

#define D(a) if (bDebug) { cout << dbg; (a); }

const char* const err = "ERROR: ";
const char* const dbg = "  debug: ";

inline void cinstr (CString& s, int n) { cin.getline (s.GetBuffer (n), n); s.ReleaseBuffer(); };
inline void cinstr (CString& s) { cin.getline (s.GetBuffer (100), 100); s.ReleaseBuffer(); };
