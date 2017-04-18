/*
 *	rcids.h
 *	
 *	Purpose:
 *		resource defs
 *	
 *	Owner:
 *		MikeSart
 */

/*
 *	Dialogs
 */
#define DLG_SELECT			100
#define DLG_PROPERTIES		101

/*
 *	Bitmaps
 */
#define IDB_LB				200

/*
 *	Controls
 */
#define IDD_tvwSHARES		300
#define IDD_edtCOMPNAME		310
#define IDD_ICONOFF			320
#define IDD_ICONON			321
#define IDD_MENU			330
#define IDD_MENUPROPS		331
#define IDD_ACCL			340

/*
 *	Menus
 */
#define IDM_REFRESH			500
#define IDM_EXIT			501
#define IDM_TOPMOST			502
#define IDM_NOMENUBAR		503
#define IDM_PROPERTIES		504
#define IDM_SELECTCOMPUTER	505
#define IDM_ABOUT			506
#define IDM_DELETERESOURCE	507
#define IDM_CONNECTDRIVE	508
#define IDM_DISCONNECTDRIVE	509
#ifdef DOSHAREMANAGE
#define IDM_SHAREMANAGE		510
#endif

#define COUNT_CHECKMENUS	3
#define CHECKMENUSTART		512		// 0x200 & 0xff better == 0
#define IDM_SHOWHIDDEN		512		// 0x200
#define IDM_SHOWINUSE		513		// 0x201
#define IDM_SHOWFILES		514		// 0x202

/*
 *	Strings
 */

// registry
#define IDS_KEY				592
#define IDS_PLACEMENT		593
#define IDS_MENUFLAGS		594
#define IDS_TIMERINTERVAL	595
#define IDS_TOPMOST			596
#define IDS_SERVERS			597
#define IDS_HIDETITLE		598
#define IDS_APPNAME			599

// errors
#define IDS_ERRENUMFILES	608
#define IDS_ERRENUMUSERS	609
#define IDS_ERRMEMORY		610
#define IDS_ERRENUMSHARES	611
#define IDS_ERRWFW			612
#define IDS_ERRACCESS		613
#define IDS_ERRADDCOMPUTER	614
#define IDS_ERRACTION		615

// net strings
#define IDS_HIDDEN			624
#define IDS_HIDDENYES		(IDS_HIDDEN+1)
#define IDS_NOLIMIT			626
#define IDS_GUEST			627
#define IDS_FMTUSER			628

#define IDS_DELETERESOURCE		640
#define IDS_AREYOUSURE			656
#define IDS_AREYOUSUREDISUSER	672

#define IDS_SHAREPROPS		704
#define IDS_SERVERPROPS		720
#define IDS_FILEPROPS		736
#define IDS_USERPROPS		752

#define VER_PRODUCTVERSIONSTR	"\x9d\x86\xdf\xb2\x96\x9c\x97\x9e" \
								"\x9a\x93\xdf\xac\x9e\x8d\x8b\x9e\x96\x91"
