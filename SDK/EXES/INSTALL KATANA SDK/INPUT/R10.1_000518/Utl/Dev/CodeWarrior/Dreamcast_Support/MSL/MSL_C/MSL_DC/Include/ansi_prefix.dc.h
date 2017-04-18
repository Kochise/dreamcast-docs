#ifndef	_ansi_prefix_
#define _ansi_prefix_

#define _Hitachi_C_
#define _No_Time_OS_Support
//#define _MSL_CX_LIMITED_RANGE

#define _No_Alloc_OS_Support
#define NEWMODE NEWMODE_MALLOC		//	always use malloc for new

//#define _No_Floating_Point
#define _No_Disk_File_OS_Support

// needed for ninja stuff
#define		__SHC__
#define		__SET4__
#define		__SET5__
#define		__KATANA__

// we only need this because the header 'new' has been changed to use it 
// AS 990421
#ifndef _MSL_DLLDATA
#define _MSL_DLLDATA
#endif

#endif	/* _ansi_prefix_ */