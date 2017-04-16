**************************************************************************
**************************************************************************
* 	Summary of Classes:
*
*	CSEngine - base engine
*
*		Setup - save environment
*		Clearnup - restore environment
*		Error - common error handling
*		Alert - displays MessageBox alert
*		GetOS - returns operating system code (see #DEFINES)
*		JustPath - returns path of file name
*		JustStem - returns stem of file name (name only with no extension)
*		JustFName - returns file name
*		ForceExt - forces file to have certain extension
*		AddBs - adds backslash (colon for Macs) to file path if needed
*		GetDBCAlias - returns DBC alias
**************************************************************************

#INCLUDE csdefs.h
******************************************************************************
DEFINE CLASS CSEngine AS custom
******************************************************************************

	* Globals
	Start = .F.				&& start app or cancel
	iHelpContextID = 0		&& used as default
	cDBCName = ""			&&DBC name
	cDBCAlias = ""			&&DBC Alias name
	cDBCTable = ""			&&DBC Table name
	SetErrorOff = .F.		&&bypass normal Error handling
	HadError = .f.			&&error occurred
	iError = -1				&&error number
	cMessage = ''			&&error message
	ThermRef = ""			&&reference to thermometer
	nCurrentOS = 0			&&operating system code
	oServer = null			&&Middle Tire Server

	DatabaseName = CS_DATABASE
	DatabaseFile = ""
	DatabaseIsOpened = .F.
	ShowOpenDatabase = .T.
	CursorAlias = ""
	CursorType = NO_CURSOR
	RowConflict = .T.
	ConflictAlias = ""
	CurrentPage = 1
    OnlineStatus = ""               
	dimension aEnvironment[1]
	
	* middle-tire server procedures
	PROCEDURE ServerStart
		this.oServer = createobj('Bizrules.Salaryrule')
		IF !this.ServerIsStarted()
			* Let's try to register the server
			RUN /N BIZRULES.EXE /RegServer
			this.oServer = createobj('Bizrules.Salaryrule')
			IF !this.ServerIsStarted()	
				this.oServer = .null.
				RETURN .F.
			ENDIF
		ENDIF
	ENDPROC

	PROCEDURE ServerStop
		this.oServer = .null.
	ENDPROC

	FUNCTION ServerIsStarted
		RETURN (TYPE('this.oServer') == 'O' AND !ISNULL(this.oServer))
	ENDFUNC

	FUNCTION ServerValidateRow
		PARAMETER llReturn
		LOCAL lcError
		PRIVATE cTitle,nSalary,dBirth,dHire,cCountry

		cTitle = Title
		nSalary = Salary
		dBirth = Birth_date
		dHire = Hire_date
		cCountry = Country

		lcError = this.oServer.validate(m.cTitle, m.nSalary, m.dBirth, m.dHire, m.cCountry)
		IF !EMPTY(m.lcError)
			this.Alert(m.lcError, MB_ICONEXCLAMATION + MB_OK, BIZRULEERROR_LOC)
			RETURN .F.
		ENDIF
		RETURN .T.
	ENDFUNC

	procedure Destroy
		this.Cleanup
	endproc
	
	procedure Init
		this.Setup()
	endproc
	
	procedure Setup
		clear program
		dimension this.aEnvironment[30, 1]
		this.aEnvironment[1,1] = SET("TALK")
		SET TALK OFF
		this.aEnvironment[2,1] = on('escape')
		this.aEnvironment[3,1] = set('escape')
		push key clear
		this.aEnvironment[4,1] = set("compatible")
		set compatible off noprompt
		this.aEnvironment[6,1] = select()
		this.aEnvironment[7,1] = set("exclusive")
		this.aEnvironment[8,1] = set("message", 1)
		this.aEnvironment[9,1] = set("safety")
		set safety off
		this.aEnvironment[10,1] = set("path")
		this.aEnvironment[12,1] = set("fields")
		set fields off
		this.aEnvironment[13,1] = set("fields", 2)
		set fields local
		this.aEnvironment[14,1] = on("error")
		this.aEnvironment[15,1] = set('point')
		this.aEnvironment[16,1] = set("deleted")
		this.aEnvironment[18,1] = SET("database")
		this.aEnvironment[19,1] = set("exact")
		set exact on
		this.aEnvironment[20,1] = set("echo")
		set echo off
		this.aEnvironment[21,1] = set("memowidth")
		this.aEnvironment[22,1] = set("udfparms")
		set udfparms to value
		this.aEnvironment[23,1] = set("near")
		set near off
		this.aEnvironment[24,1] = set("unique")
		set unique off
		this.aEnvironment[25,1] = set("ansi")
		set ansi off
		this.aEnvironment[26,1] = set("carry")
		set carry off
		this.aEnvironment[27,1] = set("cpdialog")
		set cpdialog off
		this.aEnvironment[28,1] = set("status bar")
		this.aEnvironment[29,1] = sys(5) + curdir()
		IF TYPE("m.cCSDir")="C" AND !EMPTY(m.cCSDir)
			cCSDir = THIS.justpath(m.cCSDir)
			SET DEFAULT TO (m.cCSDir)
		ENDIF
		this.aEnvironment[30,1] = set("date")

		on key label f1 oEngine.Help
		ON ERROR oEngine.Error
	endproc
	
	procedure Cleanup
		* copy this.aEnvironment to local aEnvironment so we can macro substitute directly
		local array aEnvironment[alen(this.aEnvironment,1), alen(this.aEnvironment,2)]
		=acopy(this.aEnvironment, aEnvironment)
		on key label f1
		on key
		set compatible &aEnvironment[4,1]
		select (aEnvironment[6,1])
		set exclusive &aEnvironment[7,1]
		set message to [&aEnvironment[8,1]]
		set safety &aEnvironment[9,1]
		if !empty(aEnvironment[10,1])
			set path to &aEnvironment[10, 1]
		else
			set path to
		endif
		set fields &aEnvironment[12,1]
		set fields &aEnvironment[13,1]
		on error &aEnvironment[14,1]
		set point to "&aEnvironment[15,1]"
		set deleted &aEnvironment[16,1]
		if empty(aEnvironment[18,1])
			set database to
		else
			set database to &aEnvironment[18,1]
		endif
		set exact &aEnvironment[19,1]
		set echo &aEnvironment[20,1]
		set memowidth to (aEnvironment[21,1])
		set udfparms to &aEnvironment[22,1]
		set near &aEnvironment[23,1]
		set unique &aEnvironment[24,1]
		set ansi &aEnvironment[25,1]
		set carry &aEnvironment[26,1]
		set cpdialog &aEnvironment[27,1]
		set status bar &aEnvironment[28,1]
		set default to (aEnvironment[29,1])
		set date to &aEnvironment[30,1]
		set escape &aEnvironment[3,1]
		on escape &aEnvironment[2,1]
		set talk &aEnvironment[1,1]
		pop key
	endproc
	
	PROCEDURE Error
		Parameters nError, cMethod, nLine, oObject, cMessage
		local cAction
		THIS.HadError = .T.
		this.iError = m.nError
		this.cMessage = iif(empty(m.cMessage), message(), m.cMessage)
		m.cMessage = iif(empty(m.cMessage), message(), m.cMessage)
		if type('m.oObject') = 'O' .and. .not. isnull(m.oObject) .and. at('.', m.cMethod) = 0
			m.cMethod = m.oObject.Name + '.' + m.cMethod
		endif
		
		IF this.SetErrorOff
			RETURN
		ENDIF
			
		if C_DEBUG
			do case
			case m.cAction='RETRY'
				this.HadError = .f.
				clear typeahead
				set step on
				&cAction
			case m.cAction='IGNORE'
				this.HadError = .f.
				return
			endcase
		else
			m.cAction = this.Alert(message(), MB_ICONEXCLAMATION + MB_OK)
			* m.cAction = this.Alert(ERRORMESSAGE_LOC, MB_ICONEXCLAMATION + ;
			*		MB_OK, ERRORTITLE_LOC)
		endif
	ENDPROC
	
	PROCEDURE Alert
		parameters m.cMessage, m.cOptions, m.cTitle, m.cParameter1, m.cParameter2
		private m.cOptions, m.cResponse
		m.cOptions = iif(empty(m.cOptions), 0, m.cOptions)
		if parameters() > 3 && a parameter was passed
			m.cMessage = [&cMessage]
		endif
		clear typeahead
		if !empty(m.cTitle)
			m.cResponse = MessageBox(m.cMessage, m.cOptions, m.cTitle)
		else
			m.cResponse = MessageBox(m.cMessage, m.cOptions, ALERTTITLE_LOC)
		endif
		do case
		* The strings below should not be localized
		case m.cResponse = 1
			m.cResponse = 'OK'
		case m.cResponse = 6
			m.cResponse = 'YES'
		case m.cResponse = 7
			m.cResponse = 'NO'
		case m.cResponse = 2
			m.cResponse = 'CANCEL'
		case m.cResponse = 3
			m.cResponse = 'ABORT'
		case m.cResponse = 4
			m.cResponse = 'RETRY'
		case m.cResponse = 5
			m.cResponse = 'IGNORE'
		endcase
		return m.cResponse
	ENDPROC
	
	procedure Help
		do case
		case type('_screen.ActiveForm') = 'O' .and. ;
			type('_screen.ActiveForm.HelpContextID') = 'N' .and. ;
			_screen.ActiveForm.HelpContextID <> 0
			help id (_screen.ActiveForm.HelpContextID)
		case this.iHelpContextID <> 0
			help id (this.iHelpContextID)
		otherwise
			help
		endcase
	endproc

	PROCEDURE GetOS
		DO CASE
		CASE _DOS 
			THIS.nCurrentOS = OS_DOS
		CASE _UNIX
			THIS.nCurrentOS = OS_UNIX
		CASE _MAC
			THIS.nCurrentOS = OS_MAC
		CASE ATC("Windows 3",OS(1)) # 0
			THIS.nCurrentOS = OS_W32S
		CASE ATC("Windows NT",OS(1)) # 0
			THIS.nCurrentOS = OS_NT
		OTHERWISE
			THIS.nCurrentOS = OS_WIN95
		ENDCASE
	ENDPROC

	FUNCTION JustPath
		* Returns just the pathname.
		LPARAMETERS m.filname
		LOCAL cdirsep
		cdirsep = IIF(_mac,':','\')
		m.filname = SYS(2027,ALLTRIM(UPPER(m.filname)))
		IF m.cdirsep $ m.filname
		   m.filname = SUBSTR(m.filname,1,RAT(m.cdirsep,m.filname))
		   IF RIGHT(m.filname,1) = m.cdirsep AND LEN(m.filname) > 1 ;
		            AND SUBSTR(m.filname,LEN(m.filname)-1,1) <> ':'
		         filname = SUBSTR(m.filname,1,LEN(m.filname)-1)
		   ENDIF
		   RETURN m.filname
		ELSE
		   RETURN ''
		ENDIF
	ENDFUNC
	
	FUNCTION ForceExt
		* Force filename to have a particular extension.
		LPARAMETERS m.filname,m.ext
		LOCAL m.ext
		IF SUBSTR(m.ext,1,1) = "."
		   m.ext = SUBSTR(m.ext,2,3)
		ENDIF
		m.pname = THIS.justpath(m.filname)
		m.filname = THIS.justfname(UPPER(ALLTRIM(m.filname)))
		IF AT('.',m.filname) > 0
		   m.filname = SUBSTR(m.filname,1,AT('.',m.filname)-1) + '.' + m.ext
		ELSE
		   m.filname = m.filname + '.' + m.ext
		ENDIF
		RETURN THIS.addbs(m.pname) + m.filname
	ENDFUNC
	
	FUNCTION JustFname
		* Return just the filename (i.e., no path) from "filname"
		LPARAMETERS m.filname
		LOCAL clocalfname, cdirsep
		clocalfname = SYS(2027,m.filname)
		cdirsep = IIF(_mac,':','\')
		IF RAT(m.cdirsep ,m.clocalfname) > 0
		   m.clocalfname= SUBSTR(m.clocalfname,RAT(m.cdirsep,m.clocalfname)+1,255)
		ENDIF
		IF AT(':',m.clocalfname) > 0
		   m.clocalfname= SUBSTR(m.clocalfname,AT(':',m.clocalfname)+1,255)
		ENDIF
		RETURN ALLTRIM(UPPER(m.clocalfname))
	ENDFUNC

	FUNCTION AddBS
		* Add a backslash unless there is one already there.
		LPARAMETER m.pathname
		LOCAL m.separator
		m.separator = IIF(_MAC,":","\")
		m.pathname = ALLTRIM(UPPER(m.pathname))
		IF !(RIGHT(m.pathname,1) $ '\:') AND !EMPTY(m.pathname)
		   m.pathname = m.pathname + m.separator
		ENDIF
		RETURN m.pathname
	ENDFUNC

	FUNCTION JustStem
		* Return just the stem name from "filname"
		LPARAMETERS m.filname
		IF RAT('\',m.filname) > 0
		   m.filname = SUBSTR(m.filname,RAT('\',m.filname)+1,255)
		ENDIF
		IF RAT(':',m.filname) > 0
		   m.filname = SUBSTR(m.filname,RAT(':',m.filname)+1,255)
		ENDIF
		IF AT('.',m.filname) > 0
		   m.filname = SUBSTR(m.filname,1,AT('.',m.filname)-1)
		ENDIF
		RETURN ALLTRIM(UPPER(m.filname))
	ENDFUNC

	FUNCTION justext
		* Return just the extension from "filname"
		PARAMETERS m.filname
		LOCAL m.ext
		m.filname = this.justfname(m.filname)   && prevents problems with ..\ paths
		m.ext = ""
		IF AT('.', m.filname) > 0
		   m.ext = SUBSTR(m.filname, AT('.', m.filname) + 1, 3)
		ENDIF
		RETURN UPPER(m.ext)
	ENDFUNC

	PROCEDURE GetDbcAlias
		* Takes the current DBC and gets its alias name
		* cDBC - DBC name passed if not current DBC()
		LPARAMETER cDBC
		LOCAL aDBCtmp,cGetDBC,nPos
		IF TYPE("m.cDBC") # "C"
			m.cDBC  =""
		ENDIF
		IF EMPTY(m.cDBC) AND EMPTY(DBC()) 
			RETURN ""
		ENDIF
		m.cGetDBC = IIF(EMPTY(m.cDBC),DBC(),UPPER(m.cDBC))
		DIMENSION aDBCtmp[1,2]
		=ADATA(aDBCtmp)
		m.nPos = ASCAN(aDBCtmp,m.cGetDBC)
	RETURN IIF(m.nPos = 0,"",aDBCtmp[m.nPos-1])
	ENDPROC
	
	FUNCTION TableExists
		PARAMETERS lcTableName
		LOCAL dummy, lcSQuote
		*Checks to see if a table of the same name already exists on the server	
		dummy='x'
		lcSQuote=CHR(39)
			lcSQL="select uid from sysobjects where uid = user_id() and name =" + lcSQuote + lcTableName + lcSQuote
			lcField="uid"
		RETURN this.ExecuteTempSPT(lcSQL)
	ENDFUNC
		
	FUNCTION SingleValueSPT
		PARAMETERS lcSQL, lcReturnValue, lcFieldName, llReturnedOneValue
		LOCAL lcMsg, lcErrMsg, llRetVal, lcCursor, lnOldArea, lnServerError
		* Executes a server query and sees if it return one value or not
		* If it returns one value, that value gets placed in a variable passed by reference		
		lnOldArea=select()
		lcCursor=this.UniqueCursorName("_spt")
		SELECT 0
		IF this.ExecuteTempSPT(lcSQL,@lnServerError,@lcErrMsg,lcCursor) THEN
			IF RECCOUNT(lcCursor)=0 THEN
				llReturnedOneValue= .F.
			ELSE
				lcReturnValue=&lcCursor..&lcFieldName
				llReturnedOneValue=.T.
			ENDIF
			USE
		ELSE
			lcMsg=STRTRAN(QUERY_FAILURE_LOC,"|1",LTRIM(STR(lnServerError)))
			=MESSAGEBOX(lcMsg,ICON_EXCLAMATION,TITLE_TEXT_LOC)
			this.Die
			RETURN
		ENDIF
		SELECT (lnOldArea)
		RETURN llReturnedOneValue
	ENDFUNC
	
	FUNCTION DropTable
		PARAMETERS lcTable
		LOCAL lcSQL
		lcSQL="drop table " + RTRIM(this.UserName) + "." + RTRIM(lcTable)
		lnRetVal=this.ExecuteTempSPT(lcSQL)
		RETURN lnRetVal
	ENDFUNC
	
	FUNCTION ExecuteTempSPT
		parameters lcSQL, lnServerError, lcErrMsg, lcCursor
		LOCAL nRetVal, lcMsg
		
		nRetVal=SQLEXEC(this.MasterConnHand,lcSQL)
	
		DO CASE
			*Success
			CASE nRetVal=1 
				lnServerError=0
				lcErrMsg=""
				RETURN .T.
			
			*Server error occurred
			CASE nRetVal=-1
				=AERROR(aErrArray)
				lnServerError=aErrArray[1]
				lcErrMsg=aErrArray[2]
				
				IF lnServerError=1526 AND !ISNULL(aErrArray[5])THEN
					lnServerError=aErrArray[5]
				ENDIF
				
			
			*Connection level error occurred
			CASE nRetVal=-2
				*This is trouble; continue to generate script if user wants; otherwise bail
				lcMsg=STRTRAN(CONNECT_FAILURE_LOC,"|1",LTRIM(STR(lnServerErr)))
				=MESSAGEBOX(lcMsg,ICON_EXCLAMATION,TITLE_TEXT_LOC)
	
		ENDCASE
	ENDFUNC

ENDDEFINE


