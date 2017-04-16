* testing
#DEFINE CrLf CHR(13)+CHR(10)
#DEFINE MCOOKIE STRTRAN(STRTRAN(time()+padl(seconds(),10,'0'),":",""),".","")
* cmd /k e:\inetsrv\scripts\timer.bat
clear
set talk on
close data all
public ox
ox=crea("t2")
ox.show
*?ox.simplecall("1","2")
*?left(ox.cmd(MCOOKIE+"command=dir","dd"),800)
*?left(ox.startup("","dd"),800)
*?left(ox.skipit("&jj=kk &Cookie=kcookiek","dd"),800)
*pp="&jj=kk &Cookie=kcookiek &Company = theco"
*?ox.cmd("Cmd=dir+%5C","")
*?ox.cmd("%COOKIE%?Cmd=dir+%5C","")
*?ox.getval(pp,"Cookie")
*?ox.getval(pp,"Company")
*rele ox

DEFINE CLASS t2 AS t1
	width = 500
	caption="OLE Custom Server Demo"
	ADD OBJECT lbl1 AS label WITH ;
		caption="Company"
	ADD OBJECT lbl2 AS label WITH ;
		caption="Contact",top = 30
	ADD OBJECT lbl3 AS label WITH ;
		caption="Address",top = 60
	ADD OBJECT cmdQuit AS commandButton WITH ;
		caption="Quit",cancel=.t.
	ADD OBJECT txt1 AS textbox WITH ;
		left = 80,width=200,top = 0
	ADD OBJECT txt2 AS textbox WITH ;
		left = 80,width=200,top = 30
	ADD OBJECT txt3 AS textbox WITH ;
		left = 80,width=200,top=60
	ADD OBJECT txtCust_id AS TEXTBOX WITH ;
		top = 5,left = 300,readonly = .t.,disabled=.t.
	ADD OBJECT cmdNext AS commandButton WITH ;
		caption="Next",top = 120
	ADD OBJECT cmdPrev AS commandButton WITH ;
		caption="Prev",top = 120,left=110
	ADD OBJECT cmdSave AS commandButton WITH ;
		caption="Save",top = 120,left=220
	PROCEDURE init
		t1::init
		thisform.txt1.controlsource="customer.company"
		thisform.txt2.controlsource="customer.contact"
		thisform.txt3.controlsource="customer.address"
		thisform.txtCust_ID.controlsource="customer.cust_id"
	procedure cmdSave.click
		REPLACE customer.company WITH  thisform.txt1.value
		REPLACE customer.contact WITH  thisform.txt2.value
		REPLACE customer.address WITH  thisform.txt3.value
		UNLOCK
	procedure cmdNext.Click
		thisform.skipit(1)
	procedure cmdPrev.Click
		thisform.skipit(-1)
	procedure skipit(nn)
		SKIP nn IN customer
		thisform.refresh
	procedure cmdQuit.init
		this.top = thisform.height-20
		this.left = thisform.width - 90
	procedure cmdQuit.click
		thisform.release	

ENDDEFINE

DEFINE CLASS t1 AS form OLEPUBLIC
	dbfname="e:\vfp\samples\data\customer"
	htmlname="e:\inetsrv\scripts\html.dbf"
	cookiename="e:\inetsrv\scripts\cookies.dbf"
	datasession=2
	cookie = ""
	ErrorHtml=""
	PROTECTED PROCEDURE Init
		SET EXCLUSIVE OFF
		IF GETENV("COMPUTERNAME")="CALVIN4"
			this.dbfname="c:\vfp\samples\data\customer"
			this.htmlname="d:\inetsrv\scripts\html.dbf"
			this.cookiename="d:\inetsrv\scripts\cookies.dbf"
		ENDIF
		IF !USED("customer")
			USE (this.dbfname) ORDER 1
			USE (this.htmlname) ORDER 1 ALIAS html IN 2
			SELECT 3
			USE (this.cookiename) alias cookies ORDER 1
		ENDIF
	PROTECTED PROC destroy
		this.writeCookie
	PROTECTED PROC WriteCookie
		IF !EMPTY(this.cookie)
			SELECT cookies
			SEEK this.cookie
			IF !FOUND()
				INSERT INTO cookies (cookie) VALUES ;
						(this.cookie)
			ENDIF
			REPLACE rnum WITH recno("customer")
		ENDIF
	PROCEDURE startup(p1,p2)
	*called when client first visits: generate a cookie
		this.cookie = MCOOKIE
		return this.GenHTML("FORM","aa")
	
	procedure Getval(cstr,cVal)
		LOCAL n1,c2
		n1 = AT(m.cVal,m.cStr)
		IF n1 = 0
			return ""
		ENDIF
		c2 = ALLTRIM(SUBSTR(m.cStr,n1 + LEN(m.cVal)))
		IF LEFT(m.c2,1) = '='
			c2 = SUBSTR(m.c2,2)
		ENDIF
		IF "&"$c2
			RETURN ALLTRIM(LEFT(m.c2,AT('&',m.c2)-1))
		ELSE
			RETURN ALLTRIM(m.c2)
		ENDIF
	PROC FixURL(m.cStr)
		LOCAL m.n1,m.rv
		m.cstr=STRTRAN(m.cstr,"+"," ")
		m.rv = ""
		DO WHILE .T.
			IF "%" $ m.cStr
				m.n1 = AT('%',m.cStr)
				IF m.n1 > LEN(m.cStr) - 2
					m.rv = m.rv + m.cStr
					EXIT
				ENDIF
				IF !ISDIGIT(SUBSTR(m.cStr,m.n1+1))
					m.rv = m.rv + LEFT(m.cStr,m.n1)
					m.cStr = SUBSTR(m.cStr,m.n1+1)
					LOOP
				ENDIF
				m.rv = m.rv + LEFT(m.cStr,m.n1-1) + ;
					CHR(EVAL("0x"+SUBSTR(m.cStr,m.n1+1,2)))
				IF LEN(m.cStr) > m.n1 + 2
					m.cStr = SUBSTR(m.cStr,m.n1+3)
				ELSE
					EXIT
				ENDIF
			ELSE
				m.rv = m.rv + m.cStr
				EXIT
			ENDIF
		ENDDO
		m.cStr = m.rv
		RETURN m.rv
	protected procedure GetCookie(cstr)
		this.FixURL(@m.cStr)
		IF EMPTY(this.cookie)
			IF "Cookie="$ m.cStr
				this.cookie=this.getval(m.cStr,"Cookie")
			ELSE
				this.cookie= LEFT(m.cstr,LEN(MCOOKIE))
			ENDIF
		ENDIF
		cstr= STRTRAN(m.cstr,this.cookie,"")
		IF !SEEK(this.cookie,"cookies")
			INSERT INTO cookies (cookie) VALUES ;
					(this.cookie)
		ELSE
			GOTO (cookies.rnum) IN customer
		ENDIF
		return m.cstr
	proc cmd(p1,p2)
		LOCAL m.cmd,rv
		this.FixURL(@m.p1)
		m.cmd=SUBSTR(m.p1,AT('=',m.p1)+1)
		IF !EMPTY(m.cmd)
			IF "FOXCMD"$m.p1
				m.p2 = EVAL(m.cmd)
				DO CASE
				CASE TYPE("m.p2") = 'N'
					IF INT(m.p2) # m.p2
						m.p2 = STR(m.p2,15,3)
					ELSE
						m.p2 = STR(m.p2)
					ENDIF
				CASE TYPE("m.p2") = 'D'
					m.p2 = DTOC(m.p2)
				ENDCASE
			ELSE
				creat curs temp (dat m)
				append blank
				m.cmd = UPPER(m.cmd)
				IF m.cmd = "DEL" OR m.cmd="FORMAT" OR m.cmd ="ERASE"
					REPLACE dat WITH "You do not have rights"
				ELSE
					! &cmd >c:\t.txt
					append memo dat from c:\t.txt
				ENDIF
				p2 = "<hr><p><pre>"+temp.dat+"<hr><p></pre>"
				use in temp
			ENDIF
		ELSE
			p2 = "No command given"			
		ENDIF
		p2 = STRTRAN(m.p2,"<DIR>","(DIR)")
		p2 = left(m.p2,3500)
		rv = THIS.GenHTML("CMD",m.p2)
		IF "FOXCMD"$m.p1
			rv = strtran(m.rv,"%CMDTYPE%","Fox Expression")
		ELSE
			rv = strtran(m.rv,"%CMDTYPE%","DOS Command")
		ENDIF
		rv = strtran(m.rv,"%COMMAND%",m.cmd)
		rv = strtran(m.rv,"%RESULTS%",m.p2)
		RETURN m.rv
	procedure skipit(p1,p2)
		this.GetCookie(@m.p1)
		IF ATC("prev",m.p1)>0
			skip -1 in customer
		ELSE
			skip in customer
		ENDIF
		this.writeCookie
		return THIS.GenHTML("FORM","b")

	PROCEDURE DoGet(request,Response)
	    Return THIS.CreateStdResponse("using the GET method", request)

	PROCEDURE DoPost(request,Response)
		IF EMPTY(Response)
			Response = ""
		ENDIF
	    Return THIS.CreateStdResponse("using the POST method", request)
	PROTECTED PROCEDURE Error(nError,cMethod,nLine)
		LOCAL rv
		rv = THIS.GenHTML("ERROR","")
		rv = strtran(m.rv,"%METHOD%",m.cMethod)
		rv = strtran(m.rv,"%ERRORNO%",STR(m.nError,4))
		rv = strtran(m.rv,"%ERRORMSG%",Message(1))
		rv = strtran(m.rv,"%LINENO%",STR(m.nLine,4))
		THIS.ErrorHTML = m.rv
		RETURN
	PROCEDURE DoSave(p1,p2)
		LOCAL m.tt
		this.GetCookie(@m.p1)
		REPLACE customer.company WITH  this.GetVal(m.p1,"Company")
		REPLACE customer.contact WITH  this.GetVal(m.p1,"Contact")
		REPLACE customer.address WITH  this.GetVal(m.p1,"Address")
		return THIS.GenHTML("FORM",m.p1)
	PROCEDURE GenHTML(p1,p2)
		LOCAL rv
		IF !EMPTY(THIS.ErrorHTML)
			RETURN this.ErrorHtml
		ENDIF
		=SEEK(m.p1,"html")
		rv = html.html
		rv = strtran(m.rv,"%COOKIE%",this.cookie)
		rv = strtran(m.rv,"%TEST%","t2")
		rv = strtran(m.rv,"%VERSION%",vers(1))
		rv = strtran(m.rv,"%DATE%",dtoc(date()))
		rv = strtran(m.rv,"%TIME%",time())
		rv = strtran(m.rv,"%CUST_ID%",customer.cust_id)
		rv = strtran(m.rv,"%RECNO%",STR(RECNO("customer"),4))
		rv = strtran(m.rv,"%COMPANY%",customer.company)
		rv = strtran(m.rv,"%CONTACT%",customer.contact)
		rv = strtran(m.rv,"%ADDRESS%",customer.address)
		rv = strtran(m.rv,"%TESTP1%","calvin")
		rv = strtran(m.rv,"%TESTP2%",m.p2)
	    RETURN m.rv

	Function CreateStdResponse(cMethod,cRequest)
	    LOCAL CreateStdResponse 
		IF EMPTY(Response)
			Response = ""
		ENDIF
	    CreateStdResponse = "Content-Type: text/html" + CrLf + CrLf ;
	        + "<body><h1>This is a test response " + m.cMethod + ".</h1>" ;
	        + "<p><b>Parameters: </b>" + m.cRequest + "</body>"
	    RETURN CreateStdResponse 
ENDDEFINE

