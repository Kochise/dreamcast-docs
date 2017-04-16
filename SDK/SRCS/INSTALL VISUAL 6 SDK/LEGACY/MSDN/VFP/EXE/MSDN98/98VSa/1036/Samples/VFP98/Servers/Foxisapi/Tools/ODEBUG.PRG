# ifdef thisisacomment
This program will allow you to test the VFP Automation servers called from Foxisapi

It is called by an EVAL("odebug(<parms>)") from foxisapi.DLL

To use, change the line in FOXISAPI.INI to say foxis.employee=0 as documented in the UPDATE.TXT file.
Then hit your web site with a browser using the normal URL to start the server.
FOXISAPI.DLL will then do the equivalent of these 2 lines:

		ox= CreateObject("visualfoxpro.application")
		return ox.eval("oDebug([foxis.employee.methodname('a','b')])")


You can SET STEP ON in any VFP code and it will trigger a breakpoint and bring up the debugger.
You usually do not have to rebuild the EXE or DLL server. While debugging, the EXE/DLL is only read for OLEPUBLIC class info.
You can also switch to the interactive VFP session, open up the VFP debugger, 
and set breakpoints/trace through code



To test if this debugging environment is working:

		ox= CreateObject("visualfoxpro.application")
		?ox.eval("oDebug('foxis.employee.startup()')")

*?odebug("foxis.employee.startup('a','b',0)")

* Make sure the PJX file is not in use by any session of VFP
* Also, If you're using FOXIS.EMPLOYEE, 

		modify class isform of isapi method load
look for the lines:
		#DEFINE HKEY_LOCAL_MACHINE       BITSET(0,31)+2 &&   -2147483646  && BITSET(0,31)+2
		#define REGFILE home()+"\samples\classes\registry"
		IF _VFP.startmode = 0
			set proc to REGFILE additive
		ENDIF
		
and change
		IF _VFP.startmode = 0
to 
		IF _VFP.startmode < 2

#endif		&& end of comment

**********************************************************
**********************************************************
**********************************************************


#DEFINE REGFILE		home()+"SAMPLES\CLASSES\REGISTRY"
#DEFINE SERVERKEY	"\LocalServer32"
#DEFINE CLSIDKEY		"CLSID"


	LPARAMETERS p1
	LOCAL m.rv
	IF TYPE("p1") = 'L'	&& called directly
		p1 = 'foxis.employee.startup("a","b",9)'	&& default arg
	endif
	?
	?time() + m.p1
	_oDebug = Create("MyDebugOle")
	m.rv =_oDebug.Doit(m.p1)
**	?m.rv	&& optionally print the returned HTML
	RETURN m.rv

DEFINE CLASS MyDebugOle AS custom
	ox = null
	cError=""
	Proc Error ( nError,cMethod,nLine)
		LOCAL m.rv
		m.rv = "HTTP/1.0 200 OK" + CHR(13)+CHR(10)
		m.rv = m.rv + "Content-Type: text/html" + CHR(13)+CHR(10)
		m.rv = m.rv + "Expires: Sunday 15-May-94 14:00:01 GMT" + CHR(13)+CHR(10) + CHR(13)+CHR(10)
m.rv = m.rv + "<HTML>" + CHR(13)+CHR(10) + "ODEBUG Error: " + Message() + CHR(13)+CHR(10) + message(1) + " at "+m.cMethod + " at line " + str(m.nLine,5)
		this.cError = m.rv
		return m.rv
	PROC DoIt(p1)
	
		LOCAL m.progid0,p1,oReg,i,buf,mtmp
		SET TALK OFF
		_vfp.visible=.t.
		IF OCCURS(".",p1) > 1	&& parse out the progid/classname
			progid0 = LEFT(m.p1,AT(".",p1)-1)
			p1 = SUBSTR(m.p1,AT(".",m.p1)+1)
			cClass = LEFT(m.p1,AT(".",p1)-1)
			p1 = SUBSTR(m.p1,AT(".",m.p1)+1)
		ENDIF	

		buf = getregentry(m.progid0+'.'+m.cClass)	&&search the registry for the full path of the server
		* buf = c:\inetpub\scripts\foxis.exe /automation
		IF (" "$m.buf)
			buf = LEFT(buf,AT(" ",m.buf)-1)
		ENDIF
		IF ("\"$m.buf)
			buf = LEFT(buf,RAT("\",m.buf)-1)
		ENDIF
		cd (m.buf)	&& change dir to the server's dir
		IF !FILE(m.progid0+".pjx")	&& find the project file for the server
			?"Project " + m.buf+'\'+m.progid0 + " not found"
		ENDIF
		IF WEXIST("project manager - " + m.progid0)	&& if it's open, attempt to release it
			RELEASE WINDOW "project manager - " + m.progid0
		ENDIF
		LOCAL m.nOlePublics, m.mdata, mprogid,m.mClassLib,m.mClassName
		USE (m.progid0+".pjx") SHARED ALIAS pjx
		IF !EMPTY(this.cError)
			return this.cError	&& probably couldn't open the pjx file
		ENDIF
		* Now gather OLEPUBLIC info from the PJX file			
		m.mHomeDir = HomeDir
		mdata = pjx.Reserved2
		m.nOlePublics = VAL(this.parseFld(@mdata))
		mtmp = This.ParseFld(@m.mdata)	&&TLB
		mtmp = This.ParseFld(@m.mdata)	&&libname
		mtmp = This.ParseFld(@m.mdata)	&&Pjxname
		mtmp = This.ParseFld(@m.mdata)	&&PjxDesc
		mtmp = This.ParseFld(@m.mdata)	&&Exe Type
		mtmp = This.ParseFld(@m.mdata)	&&TLBGuid
		FOR i = 1 TO m.nOlePublics
			mtmp = This.ParseFld(@m.mdata)	&&HelpID
			mprogid = UPPER(this.ParseFld(@m.mdata))	&&ProgID
			mtmp = This.ParseFld(@m.mdata)	&&desc
			mtmp = This.ParseFld(@m.mdata)	&&helpfile
			mClassName = This.ParseFld(@m.mdata)	&&classname
			mClassLib = This.ParseFld(@m.mdata)	&&classlib
			mtmp = This.ParseFld(@m.mdata)	&&instancetype
			mtmp = This.ParseFld(@m.mdata)	&&guid
			IF m.mProgId = UPPER(m.progid0 + "." + m.cClass)
				?mprogid,mClassName,mClassLib
				exit
			ENDIF
		ENDFOR
		USE IN pjx
		IF !EMPTY(this.cError)
			return this.cError
		ENDIF
		IF ".VCX"= UPPER(RIGHT(m.mClassLib,4))
			SET CLASSLIB TO (m.mClassLib)
		ELSE
			SET PROCEDURE TO (m.mClassLib)
		ENDIF
		this.ox = CreateObject(m.mClassName)	&& Create the target clas (e.g. "employee")
		IF !EMPTY(this.cError)
			return this.cError
		ENDIF
		SET CLASSLIB TO
		mretval = eval("this.ox." + m.p1)		&& invoke the target method (e.g. "startup")
		return mretval


	protected proc Parsefld(m.mdata)
		IF EMPTY(m.mdata)
			RETURN ""
		ENDIF
		mlen = val(left(m.mdata,4))
		m.str = SUBSTR(m.mdata,5,m.mlen)
		m.mdata = SUBSTR(m.mdata,5 + m.mlen )
		RETURN m.str
ENDDEFINE

proc getregentry(cProgID)

	LOCAL oReg, c,ProgIDKey, cProgIDCLSID, cProcs, nErr, cValue

	IF EMPTY(m.cProgID) OR TYPE("m.cProgID")# "C"
		RETURN ""
	ENDIF

	cProgIDKey = ALLTRIM(m.cProgID)+"\"+CLSIDKEY

	IF "REGISTRY"$SET("PROCEDURE")
		oReg = Create("Registry")
	ELSE
		SET PROC TO REGFILE ADDITIVE
		oReg = Create("Registry")
		RELEASE PROCEDURE REGFILE
	ENDIF
	DIMENSION cValue[1]
	nErr = oReg.EnumOptions(@cValue,m.cProgIDKey ,"",.F.)
	IF m.nErr=0
		cProgIDCLSID =  cValue[1,2]
	ENDIF

	DIMENSION cValue[1]
	cValue = ""
	cProgIDKey = CLSIDKEY +"\"+cProgIDCLSID+SERVERKEY
	nErr = oReg.EnumOptions(@cValue,m.cProgIDKey ,"",.F.)
RETURN cValue[1,2]

