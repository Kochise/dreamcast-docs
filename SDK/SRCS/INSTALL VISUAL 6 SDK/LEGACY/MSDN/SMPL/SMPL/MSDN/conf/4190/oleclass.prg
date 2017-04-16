#INCLUDE "\VFP\FOXPRO.H"

DEFINE CLASS OLEApplication AS Custom
	*-- oOLEApp - Holds reference to the OLE Application Server
	*-- cOLERegName - The name of the server object as found in 
	*--								the registration database. 
	*-- lCloseAppWhenDone - .T. if we started the server for the
	*--											first time within this class
	PROTECTED oOLEApp, ;
				 cOLERegName, ;
				 lCloseAppWhenDone

	oOLEApp = ""
	cOLERegName = ""
	lCloseAppWhenDone = .T.
	
	*-- Methods
	FUNCTION Init()
		*-- First make sure that the user is not trying to create an 
		*-- instance of this class.
		IF EMPTY(this.cOLERegName)
			=MessageBox("Cannot create object directly from class OLEApplication.", ;
							MB_ICONSTOP, ;
							"")
			RETURN .F.
		ENDIF
		
		*-- Attempt to start the application
		*-- First, check to see if app is already running
		IF this.AppRunning()
			*-- Grab the current instance
			this.oOLEApp = this.GetCurrentInstance()
		ELSE
			*-- Create a new instance.
			this.oOLEApp = this.CreateNewInstance()
		ENDIF
	ENDFUNC
	
	*-- The following 3 methods, Do(), Get(), and Set(), can be
	*-- used to execute a method, get the value of a property,
	*-- or set a property on the protected reference to the 
	*-- OLE Automation server (this.oOLEApp).

	*-- This method takes a method name as a parameter
	*-- and executes it.
	FUNCTION Do(tcMethod)
		RETURN EVAL("this.oOLEApp." + tcMethod)
	ENDFUNC

	*-- This method takes a property name as a parameter
	*-- and returns its value. (It can even return references
	*-- to container objects).
	*-- For example, to get a ref to the active sheet from the 
	*-- command window:
	*-- oActiveSheet = oExcel.Get("ActiveSheet")
	*-- You could then use the oActiveSheet object directly!
	*-- oActiveSheet.Cells(1,1).Value = 10
	FUNCTION Get(tcProperty)
		RETURN EVAL("this.oOLEApp." + tcProperty)
	ENDFUNC
	
	*-- This method takes a property name and a value as
	*-- paramerters, and sets the value of the property
	*-- to the value parameter. 
	FUNCTION Set(tcProperty, tuValue)
		LOCAL lcCommand
		lcCommand = "this.oOLEApp." + tcProperty + "="
		lcCommand = lcCommand + this.ConvertToChar(tuValue)
		&lcCommand
	ENDFUNC
	
	*-- Protected functions
	PROTECTED FUNCTION AppRunning()
		*-- Returns .T. if app is already running
		LOCAL lcOldError, ;
				llRunning

		llRunning = .T.
		lcOldError = ON("ERROR")
		ON ERROR llRunning = .F.
		*-- Attempt to get a reference to a running application
		=GETOBJECT(.NULL., this.cOLERegName)
		ON ERROR &lcOldError
		
		this.lCloseAppWhenDone = !llRunning
		RETURN llRunning
	ENDFUNC

	PROTECTED FUNCTION CreateNewInstance()
		RETURN CREATEOBJECT(this.cOLERegName)
	ENDFUNC
	
	PROTECTED FUNCTION GetCurrentInstance()
		RETURN GETOBJECT(.NULL., this.cOLERegName)
	ENDFUNC	

	*-- Takes a parameter of any type and converts it
	*-- a character string for use in the Set method. 
	PROTECTED FUNCTION ConvertToChar(tuParam)
		LOCAL lcRetVal, ;
				lcType
		lcRetVal = ""
		lcType = TYPE("tuParam")
		DO CASE
			CASE lcType = "C"
				lcRetVal = "'" + tuParam + "'"
			CASE INLIST(lcType, "N", "B")
				lcRetVal = STR(tuParam)
			CASE lcType = "L"
				lcRetVal = IIF(tuParam, ".T.", ".F.")
		ENDCASE
		RETURN lcRetVal
	ENDFUNC

ENDDEFINE

DEFINE CLASS Excel AS OLEApplication
	*-- Inherited properties
	cOLERegName = "Excel.Application"
	
	*-- Inherited Methods
	FUNCTION Destroy()
		IF TYPE("this.oOLEApp") == "O" AND ;
			this.lCloseAppWhenDone
				this.oOLEApp.Quit()
		ENDIF
	ENDFUNC
ENDDEFINE

DEFINE CLASS WinWord AS OLEApplication
	*-- Inherited properties
	cOLERegName = "Word.Basic"
	
	PROTECTED FUNCTION AppRunning()
		LOCAL lnChannel, ;
				llRunning, ;
				llDDEOldSafety
		
		llDDEOldSafety = DDESETOPTION("Safety")

		*-- Prevent the prompt to start the application
		=DDESETOPTION("Safety", .F.)
		*-- Try to establish a link on the System topic
		lnChannel = DDEINITIATE("WinWord", "System")
		IF lnChannel <> -1
			*-- It's running
			this.lCloseAppWhenDone = .F.
			=DDETERMINATE(lnChannel)
			llRunning = .T.
		ENDIF

		=DDESETOPTION("Safety", llDDEOldSafety)
		
		RETURN llRunning
		
	PROTECTED FUNCTION GetCurrentInstance()
		RETURN GETOBJECT("", this.cOLERegName)
	ENDFUNC	

	PROTECTED FUNCTION CreateNewInstance()
		LOCAL loWord
		loWord = CREATEOBJECT(this.cOLERegName)
		loWord.AppActivate(_screen.Caption)
		loWord.FileNew
		RETURN loWord
	ENDFUNC
	
	*-- New Methods
	FUNCTION Insert(tcText)
		this.oOLEApp.Insert(tcText)
	ENDFUNC
			
ENDDEFINE
