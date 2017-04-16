#ifndef _INC_PICKER
#define _INC_PICKER

//Header file for applications calling the Picker DLL

#define CLASSNAMESIZE 80
#define PATHNAMESIZE 80
#define CAPTIONSIZE 80
#define FILENAMESIZE 9

typedef struct {
	char szPathname[PATHNAMESIZE] ;
	char szClassname[CLASSNAMESIZE];
	char szCaption[CAPTIONSIZE];
	char szFilename[FILENAMESIZE];
	HWND hwnd;	
} PICKER_STRUCT ;

typedef 	PICKER_STRUCT FAR *		LP_PICKER_STRUCT;

int DLL_EXP Picker_Do(HWND hwndOwner, LP_PICKER_STRUCT lpPicker);

#endif // !_INC_PICKER
