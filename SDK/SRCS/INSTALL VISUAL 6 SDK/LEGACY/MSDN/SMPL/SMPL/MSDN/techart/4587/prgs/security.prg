*------------------------------------------
* Security.prg - Main program for security
*------------------------------------------
SET TALK OFF
SET ECHO OFF
SET DELE ON
SET EXCL ON
PUBLIC pUserID, pUserPW, pSupervisor
LOCAL LoggedIn
pUserID     = SPACE( 4)
pUserPW     = SPACE(10)
pSupervisor = .F.
LoggedIn 	= .F.
PageName	= ""
DO FORM Login TO LoggedIn
IF LoggedIn
   PUSH MENU _MSYSMENU
   DO Security.mpr
   READ EVENTS
ENDIF	
CLOSE DATA
CLEAR WINDOW
IF FILE("S_"+ALLT(pUserID)+".dbf")
	IF USED( "UserRght" )
	   USE IN UserRght
	ENDIF	
	DELE FILE ("S_"+ALLT(pUserID)+".dbf")
	DELE FILE ("S_"+ALLT(pUserID)+".cdx")
ENDIF	
POP MENU _MSYSMENU
*------------------------------------------
