** NOTE **
*-- For now, make sure Word is running before
*-- running this program.

*-- This program reads through all VCX files in a directory 
*-- and sends output to a Word document. A good enhancement
*-- to this program would be a front end that allows the user
*-- to specify the source directory of the VCX files.

*? Put cust props and meths into a table.
CLOSE ALL
SET TALK OFF

#DEFINE TAB						CHR(9)
#DEFINE CR						CHR(13)
#DEFINE CUSTMETHDELIM	"*"

LOCAL lcVCXDir, ;
			lcOldDir, ;
			laVCXs[1], ;
			i, ;
			lnVCXCount, ;
			loWord, ;
			lcCustPropField, ;
			lcClassDescField, ;
			lcTemp, ;
			lnLine, ;
			laProps[1], ;
			laMeths[1], ;
			lnLines, ;
			lcSmartTab, ;
			lnContainCount, ;
			llSkipContainedObjects, ;
			lnOldMemoWidth, ;
			lnProps, ;
			lnMeths

lcVCXDir = "C:\VFP\SAMPLES\MAINSAMP\LIBS\"
lcOldDir = CURDIR()
lcCustPropField = "Reserved3"
lcClassDescField = "Reserved7"
lcTemp = ""
lcSmartTab = ""
lnContainCount = 0
llSkipContainedObjects = .T.
lnOldMemoWidth = SET('MEMOWIDTH')
lnProps = 0
lnMeths = 0

SET PROC TO ..\OLECLASS.PRG
SET MEMOWIDTH TO 256

CD (lcVCXDir)
lnVCXCount = ADIR(laVCXs, lcVCXDir + "*.VCX")

IF lnVCXCount > 0
	loWord = CREA("WinWord")
	loWord.Do("FileNew")

	FOR i = 1 TO lnVCXCount
		USE (FULLPATH(laVCXs[i, 1]))
		loWord.Insert(CR + "CLASSLIB: " + laVCXs[i, 1] + CR)
		SCAN
			IF !EMPTY(class)
				loWord.Insert(CR + lcSmartTab + "Object Name: " + TAB + objname + CR)
				loWord.Insert(lcSmartTab + "Class:" + TAB + TAB + class + ;
											IIF(!EMPTY(classloc), " (" + ALLT(classloc) + ")", "") + CR)
				IF !EMPTY(EVAL(lcClassDescField))
					loWord.Insert(lcSmartTab + "Description:" + TAB + EVAL(lcClassDescField) + CR)
				ENDIF
				
				loWord.Insert(lcSmartTab + "Base Class: " + TAB + baseclass + CR)
				IF !EMPTY(parent)
					loWord.Insert(lcSmartTab + "Parent: " + TAB + TAB + parent + CR)
				ENDIF

				*-- Handle custom properties and methods
				*-- Use a temp var so as not to keep EVAL()ing
				lcTemp = EVAL(lcCustPropField)
				IF !EMPTY(lcTemp)
					*-- Has cust props or methods
					lnLines = MEMLINES(lcTemp)
					*-- Build all props and methods into arrays
					RELEASE laProps, laMeths
					DIMENSION laProps[lnLines]
					DIMENSION laMeths[lnLines]
					STORE 0 TO lnProps, lnMeths
					FOR lnLine = 1 TO lnLines
						IF LEFT(MLINE(lcTemp, lnLine), 1) <> CUSTMETHDELIM
							lnProps = lnProps + 1
							laProps[lnProps] = STRTRAN(MLINE(lcTemp, lnLine), " ", ": ", 1, 1)
						ELSE
							lnMeths = lnMeths + 1
							laMeths[lnMeths] = STRTRAN(SUBSTR(MLINE(lcTemp, lnLine), 2), " ", ": ", 1, 1)
						ENDIF
					ENDFOR
					
					*-- Prepare formatted strings for one big 
					*-- sendoff to Word (1 for ea.)
					lcProps = BuildIt(@laProps)
					lcMeths = BuildIt(@laMeths)
					loWord.Insert(CR)
					
					IF !EMPTY(lcProps)
						loWord.Insert(lcSmartTab + "Custom Properties: " + CR + lcProps + CR)
					ENDIF
					
					IF !EMPTY(lcMeths)
						loWord.Insert(lcSmartTab + "Custom Methods: " + CR + lcMeths + CR)
					ENDIF

				ENDIF && !EMPTY(lcTemp)

				IF !EMPTY(reserved2) AND VAL(reserved2) > 1
					*-- We have contained objects
					*-- Skip for now
					lnContainCount = VAL(reserved2)
				ENDIF
				
				IF llSkipContainedObjects 
					IF lnContainCount > 1
						SKIP lnContainCount - 1
						lnContainCount = 0
					ENDIF
				ENDIF
				
				*-- Determine if we are displaying objects in a container
				*-- If so, indent all contained objects
				lnContainCount = MAX(lnContainCount - 1, 0)
				IF lnContainCount = 0
					lcSmartTab = ""
				ELSE
					lcSmartTab = TAB
				ENDIF

			ENDIF && !EMPTY(class)
		ENDSCAN
	ENDFOR
	
	*? Need code for saving
	*? for now, we always have Word running
	
ENDIF && lnVCXCount > 0

SET PROC TO
SET MEMOWIDTH TO lnOldMemoWidth
CD (lcOldDir)
CLOSE ALL
					

FUNCTION BuildIt(taCust)
	LOCAL lnLine, lcString
	lcString = ""
	FOR lnLine = 1 TO ALEN(taCust)
		IF EMPTY(taCust[lnLine])
			EXIT
		ENDIF
		lcString = lcString + TAB + taCust[lnLine] + CR
	ENDFOR
	RETURN lcString
ENDFUNC