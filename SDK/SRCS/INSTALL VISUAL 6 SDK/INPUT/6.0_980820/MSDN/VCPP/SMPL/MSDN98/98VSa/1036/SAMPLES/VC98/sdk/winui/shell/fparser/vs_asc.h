
typedef	struct	view_asc_save
{
	LONG	SeekSpot;
	// DWORD	dwNumLines;
	SHORT	lastchar;

} VIEW_ASC_SAVE;

typedef	struct	view_asc_data
{
	VIEW_ASC_SAVE	AscSave;
	SHORT	hFile;
	BOOL				bFileIsText;
} VIEW_ASC_DATA;

