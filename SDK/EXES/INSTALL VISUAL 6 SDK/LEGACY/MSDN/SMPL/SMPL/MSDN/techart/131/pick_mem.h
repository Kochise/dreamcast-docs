#ifndef _INC_PICK_MEM
#define _INC_PICK_MEM

//------------------------------------------------------------------------
//Unpacked Structures Follow
#pragma pack(4)

typedef struct {
	BOOL bPicking ;
	LP_PICKER_STRUCT lpPicker ;
	PICKER_STRUCT picker ;
	char szJunk[PATHNAMESIZE]; //For use with _splitpath
} GLOBAL_PICKER ;

typedef GLOBAL_PICKER NEAR * NP_GLOBAL_PICKER ;

#pragma pack()	//Revert to command line packing

//----------------------------------------------------------------------


NP_GLOBAL_PICKER GLOBAL allocMem(HWND hwnd,LP_PICKER_STRUCT lpPicker);

NP_GLOBAL_PICKER GLOBAL getMem(HWND hwnd);

void GLOBAL freeMem(HWND hwnd);

#endif
