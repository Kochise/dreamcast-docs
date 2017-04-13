#include <windows.h>

//BUGBUG - eventually load these out of the resource file

LPTSTR gpszImagEdit    = "imagedit %1";
#ifdef DBCS // Load string dynamically
LPTSTR gpszAniFilter;
#else
LPTSTR gpszAniFilter   = "Animated Cursor\0*.ani\0All Files\0*.*\0";
#endif
LPTSTR gpszCUR         = "cur";
LPTSTR gpszANI         = "ani";
#ifdef DBCS // Load string dynamically
LPTSTR gpszUnknownError;
LPTSTR gpszCurFilter;
LPTSTR gpszUntitled;
LPTSTR gpszImport;
#else
LPTSTR gpszUnknownError = "Unknown Error";
LPTSTR gpszCurFilter   = "Cursor files\0*.cur\0Icon files\0*.ico\0All Files\0*.*\0";
LPTSTR gpszUntitled    = "(Untitled)";
LPTSTR gpszImport      = "Import Frame";
#endif
