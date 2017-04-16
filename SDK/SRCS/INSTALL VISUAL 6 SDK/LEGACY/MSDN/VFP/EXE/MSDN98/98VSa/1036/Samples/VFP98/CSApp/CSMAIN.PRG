#DEFINE CS_CONNECTION1					"CONNECTION DESIGNER - emp_connection"

* Save some settings
private cClassLib, cSaveProc, cCSDir
public oEngine,oCSApp
cClassLib = set('classlib')
cSaveProc = set('procedure')
cCSDir = FULLPATH(SYS(16))
set classlib to sample additive
set procedure to csprocs

* Create and verify that oEngine instantiation was successful
* to see whether to continue with instantiation
oEngine = createobj("csengine")
IF TYPE('oEngine')#'O' OR ISNULL(m.oEngine)
	Resetenv()
	RETURN
endif

* Create startup form to open DBC
oStartForm = createobj('OpenDBC')
IF TYPE('oStartForm')#'O' OR ISNULL(m.oStartForm)
	Resetenv()
	RETURN
ENDIF
oStartForm.Show

* Create cursor selection form
IF oEngine.Start
	oCSApp = createobject('sampleapp')
	IF TYPE('oCSApp') # 'O' OR ISNULL(m.oCSApp)
		Resetenv()
		RETURN
	ENDIF
	oCSApp.Show
ENDIF

Resetenv()
RETURN


FUNCTION  resetenv
	RELEASE oCSApp
	RELEASE oEngine
	
	IF  EMPTY(m.cClassLib)
		SET CLASSLIB TO
	ELSE
		SET CLASSLIB TO &cClassLib
	ENDIF

	IF WEXIST(CS_CONNECTION1)
		RELEASE WINDOW (CS_CONNECTION1)
	ENDIF
	
	CLOSE PROCEDURE csprocs
	IF  EMPTY(m.cSaveProc)
		SET PROCEDURE TO
	ELSE
		SET PROCEDURE TO &cSaveProc 
	ENDIF
	ON ERROR
ENDFUNC

