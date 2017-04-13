// FILLFILE.H

#ifndef FILLFILE_INCLUDED
#define FILLFILE_INCLUDED

LONG    		GetLBText           	(HWND, PTCHAR);
BOOL			myIsDirectory			(LPTSTR);
BOOL 			SeparatePathName		(LPTSTR, LPTSTR, LPTSTR);
BOOL 			SeparatePathName2		(LPTSTR, LPTSTR, LPTSTR);
BOOL 			FillFile				(LPCINFO, HWND);
BOOL 			CFilerIsDirectory		(LPTSTR);
BOOL 			IsEncrypted				(LPTSTR);
BOOL 			IsLegalToAdd			(LPTSTR);
BOOL 			BuildSigTable			(TABLE);

#endif // #ifdef FILLFILE_INCLUDED
