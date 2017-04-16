#DEFINE CRLF	CHR(13)+CHR(10)
#DEFINE HKEY_LOCAL_MACHINE       BITSET(0,31)+2 		&&   -2147483646  && BITSET(0,31)+2
#DEFINE COMPNAME_KEY		"SYSTEM\CurrentcontrolSet\control\ComputerName\Computername"

DEFINE CLASS server AS CUSTOM OLEPUBLIC

cError = ""

PROCEDURE Init
	* GetPrivateProfileString function is used to read INI file passed by
	* FOXISAPI.DLL to the automation server as 2nd parameter.
	*
	DECLARE INTEGER GetPrivateProfileString IN win32api String,String,String,;
	  String @, integer,string
ENDPROC

PROCEDURE Delay
	* This is a sample method that delays execution for amount of time
	* passed by 1st parameter. It can be used to test pooling.
	*
	* ex. http://mywebserver/scripts/foxisapi.dll/foxweb.server.delay?10
	* ex. http://mywebserver/scripts/foxisapi.dll/myfoxweb.delay?10 -- if you set this section in FOXISAPI.INI
	*
	LPARAMETERS p1,p2,nPersistInstance
	LOCAL retval,stop
	nPersistInstance = 0		&& signal the client to not release this instance
	IF TYPE("m.p1")#"C"
		p1 = "5"
	ENDIF
	IF TYPE("m.p2")#"C"
		p2 = ""
	ENDIF
	
	retval = [<HTML>] + CRLF + [<HEAD>] + CRLF
	retval = m.retval + [<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">] + CRLF
	retval = m.retval + [<META NAME="Generator" CONTENT="">] + CRLF
	retval = m.retval + [<TITLE>Foxweb Delay!</TITLE>] + CRLF
	retval = m.retval + [</HEAD>] + CRLF
	IF !EMPTY(m.p2) AND FILE(m.p2)
		retval = m.retval + [<body bgcolor="aqua">] + CRLF
		retval = m.retval + [<h1>Local Server Delay</h1>] + CRLF
	ELSE 
		retval = m.retval + [<body bgcolor="green">] + CRLF
		retval = m.retval + [<h1>Remote Server Delay</h1>] + CRLF
	ENDIF
	retval = m.retval + [<P>] + [Computername: ] + THIS.GetCompName() + CRLF
	retval = m.retval + [<P>] + [Delay: ] + m.p1 + CRLF
	retval = m.retval + [<p>] + TIME() + CRLF
	retval = m.retval + [</Body>] + CRLF
	retval = m.retval + [</HTML>]
	stop = SECONDS() + VAL(m.p1)
	DO WHILE SECONDS() < m.stop
	ENDDO
	RETURN THIS.cError + m.retval 
ENDPROC

PROCEDURE Reset
	* This is a sample method releases the running server instance
	* because the output parameter, nPersistInstance, is not set to 0.
	*
	* ex. http://mywebserver/scripts/foxisapi.dll/foxweb.server.reset
	*
	LPARAMETERS p1,p2,nPersistInstance
	LOCAL retval
	retval = [<HTML>] + CRLF + [<HEAD>] + CRLF
	retval = m.retval + [<TITLE>FoxWeb Server</TITLE>] + CRLF
	retval = m.retval + [</HEAD>] + CRLF + [<BODY>] + CRLF
	retval = m.retval + [<FONT SIZE=2><P>Releasing FoxWeb Server</P>] + CRLF
	retval = m.retval + [</HTML>] + CRLF
 	RETURN THIS.cError + m.retval
ENDPROC

PROCEDURE Hello
	* This is a sample method that delays execution for amount of time
	* passed by 1st parameter. It can be used to test pooling.
	*
	* ex. http://mywebserver/scripts/foxisapi.dll/foxweb.server.hello?fred
	*
	LPARAMETERS p1,p2,nPersistInstance
	LOCAL retval,buf,nlen
	nPersistInstance = 0
	p1 = ALLTRIM(p1)
	IF TYPE("m.p1")#"C" OR EMPTY(m.p1)
		m.p1 = "World"
	ENDIF
	IF TYPE("m.p2")#"C"
		m.p2 = ""
	ENDIF
	retval = [<HTML>] + CRLF + [<HEAD>] + CRLF
	retval = m.retval + [<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">] + CRLF
	retval = m.retval + [<META NAME="Generator" CONTENT="">] + CRLF
	retval = m.retval + [<TITLE>Hello World!</TITLE>] + CRLF
	retval = m.retval + [</HEAD>] + CRLF + [<BODY bgColor=fuchsia>] + CRLF
	retval = m.retval + [<FONT SIZE=2><P>] + [HeLlO ] + m.p1 + [!] + [</P>] + CRLF + CRLF
	retval = m.retval + [<P>This is some sample formatted text: <B>Bold Text</P></B></FONT></BODY>] +  CRLF
	retval = m.retval + [<P>]	+ TTOC(DATETIME()) + [</P>] + CRLF
	retval = m.retval + [<P>]	+ m.p2 + [</P>] + CRLF
	IF !EMPTY(m.p2) AND FILE(m.p2)
		buf = SPACE(500)
		nlen = GetPrivateProfileString("FOXISAPI","Server Name","default7",@buf,LEN(buf),m.p2)
		retval = m.retval + [<P>]	+ [Server Name = ] + LEFT(m.buf,m.nlen) + [</P>] + CRLF
	ELSE
		retval = m.retval + [<P>]	+ [INI file not found. Remote Server] + [</P>] + CRLF
	ENDIF
	retval = m.retval + [</Body>] + CRLF
	retval = m.retval + [</HTML>] + CRLF
 	RETURN THIS.cError + m.retval
ENDPROC

PROCEDURE Error
	* Your FOXISAPI automation servers should always have an error
	* routine which returns HTML information regarding the nature of error.
	* 
	LPARAMETERS nError, cMethod, nLine
	LOCAL retval 
	retval = [HTTP/1.0 200 OK] + CRLF
	retval = m.retval + [Content-Type: text/html] + CRLF
	retval = m.retval + [Expires: Sunday 15-May-94 14:00:01 GMT] + CRLF + CRLF
	retval = m.retval + [<HTML>] + CRLF + [Error: ] + MESSAGE() + CRLF + ;
		MESSAGE(1) + [ at ] + m.cMethod + [ at line ] + STR(m.nLine,5) + CRLF
	retval = m.retval + [</HTML>] + CRLF
	THIS.cError = m.retval
	RETURN m.retval 
ENDPROC

PROCEDURE GetCompName
	* This routine returns the computer name
	*
	LOCAL oreg,cValue,nErr
	cValue = ""
	oreg = NewObject('registry','registry.prg')
	nErr=oReg.GetRegKey("ComputerName", @cValue, COMPNAME_KEY, HKEY_LOCAL_MACHINE)
	RETURN IIF(nErr = 0, m.cValue, "")
ENDPROC

ENDDEFINE
