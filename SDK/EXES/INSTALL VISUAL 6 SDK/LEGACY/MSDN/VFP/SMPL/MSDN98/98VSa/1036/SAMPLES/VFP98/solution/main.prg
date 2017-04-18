*****************************************************
* Main Program for Solution.APP
* Sample Application
*
* Copyright (c) 1990 - 1996 Microsoft Corp.
* 1 Microsoft Way
* Redmond, WA 98052
*
******************************************************

* Change the default directory if run from the Project manager
* and solution.scx cannot be found

IF !FILE('solution.scx')
	cCurrentProcedure = SYS(16,1)
	nPathStart = AT(":",cCurrentProcedure)- 1
	nLenOfPath = RAT("\", cCurrentProcedure) - (nPathStart)
 	SET DEFAULT TO (SUBSTR(cCurrentProcedure, nPathStart, nLenofPath))
ENDIF

* Establish a global error handler.
* The error events associated with objects
* take precedence over ON ERROR routines.

cOldError = ON("ERROR")
ON ERROR DO SolutionErrHandle

* Run the main form and establish the event loop

DO FORM solution
READ EVENTS

* Reset the global error handler
ON ERROR &cOldError


PROCEDURE SolutionErrHandle
LOCAL lnChoice
	#DEFINE ERR_LOC "Erreur: "
	#DEFINE FILEINUSE_LOC "Un formulaire ne peut pas simultanément être ouvert en mode création et être en cours d'exécution."
	#DEFINE FILEREADONLY_LOC "Un des fichiers nécessaires a l'attribut lecture seule." + CHR(13) + "Veuillez vérifier que vous disposez des accès en lecture et en écriture au fichier."

	DO CASE
		CASE ERROR() = 3 && File is in use
			=MESSAGEBOX( ERR_LOC + MESSAGE() + CHR(13) + ;
				FILEINUSE_LOC, 0 + 48)
				
		CASE ERROR() = 1718 && File is read-only
			=MESSAGEBOX( ERR_LOC + MESSAGE() + CHR(13) + ;
				 FILEREADONLY_LOC, 0 + 48)
			RETRY
		CASE ERROR() = 1881 && Trying to load DE of solution.scx when table is already open
			CLOSE DATA ALL
			DO FORM solution
		OTHERWISE
			lnChoice = MESSAGEBOX(ERR_LOC + ALLTRIM(STR(ERROR())) + CHR(13) + ;
				MESSAGE(), 1 + 48)
			IF lnChoice = 2 && Cancel
				ON ERROR &cOldError
				CLEAR EVENTS
				CLOSE ALL
				RELEASE ALL
				CLEAR ALL
			ENDIF	
	ENDCASE
ENDPROC

* Project resolution markers for API functions

Procedure MAINHWND
Procedure  _WHTOHWND
Procedure  _WONTOP
Procedure  GetFileVersion
