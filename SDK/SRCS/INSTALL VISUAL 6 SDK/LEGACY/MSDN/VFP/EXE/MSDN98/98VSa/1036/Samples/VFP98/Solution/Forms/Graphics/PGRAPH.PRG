* Plot graph (Polar).
* Parameter:
* 1) cEquation (For radius) in terms of X.  TYPE = Character.
* 2) nFrom. Where to stop counting for X.  TYPE = Numeric.
* 3) nTo. Where to start counting for X.  TYPE = Numeric.
* 4) nStepInc.  Step increment.  TYPE = Numeric.
* 5) nEquColor.  TYPE = Numeric.
* 6) lConnect.  If the previous point is connected to the cuurnt point with a line.  TYPE = Logical.
* 7) nXCenter.  Point on form where x = 0.  TYPE = Numeric.
* 8) nYCenter.  Point on form where y = 0.  TYPE = Numeric.
* 9) lAddCoords.  If you should add coordinate lines.  TYPE = Logical.
* 10) frmFormName.  Name for form to write on.  TYPE = Character.
* 11) nEquScale. Scale.  TYPE = Numeric.
PARAMETER cEquation,nFrom,nTo,nStepInc,nEquColor,lConnect,nXCenter,nYCenter,lAddCoords,frmFormName,nEquScale
	PRIVATE nOldY,m.nOldX,nTempMaxNum
	m.nTempMaxNum = 30000

IF PARAMETERS()	< 10
	#define PGRAPH_LOC "Ce programme requiert des paramètres multiples."
	WAIT WINDOW PGRAPH_LOC
	RETURN
ENDIF

	IF TYPE('nEquScale') <> "N"
		nEquScale = 1
	ENDIF	

	IF lAddCoords
		* Add coordinate lines.  R=0.
		frmFormName.forecolor = rgb(0,0,0)
		frmFormName.line(m.nXCenter,0,m.nXCenter,frmFormName.height)
		frmFormName.line(0,m.nYCenter,frmFormName.width,m.nYCenter)
	ENDIF	

	** Calcuate old values for x,y (m.nOldX,m.nOldY).  Used if connect is True.

	m.X = m.nFrom
	m.nR = eval(m.cEquation)
	m.nOldX = m.nR*cos(x)*nEquScale
	m.nOldY = m.nR*sin(x)*nEquScale

 	** Calculate all radius and angle vales by ranging x from the "FROM" nTo the "nTo" parameters.

	frmFormName.forecolor = m.nEquColor
	FOR m.x = nFrom to nTo STEP m.nStepInc
		m.nR = eval(m.cEquation)
		tempplotx = m.nR*cos(m.x)*nEquScale
		tempploty = m.nR*sin(m.x)*nEquScale
		IF m.lConnect
			IF m.nYCenter-m.nOldY < m.nTempMaxNum and m.nYCenter-tempploty < m.nTempMaxNum and m.nYCenter-m.nOldY > m.nTempMaxNum*-1 and m.nYCenter-tempploty > m.nTempMaxNum*-1
				frmFormName.line(m.nOldX+m.nXCenter,m.nYCenter-m.nOldY,tempplotx+m.nXCenter,m.nYCenter-tempploty)
			ENDIF
		ELSE
			IF m.nYCenter-tempploty < m.nTempMaxNum and m.nYCenter-tempploty > m.nTempMaxNum*-1
				frmFormName.pset(tempplotx+m.nXCenter,m.nYCenter-tempploty)
			ENDIF
		ENDIF
		m.nOldX = tempplotx
		m.nOldY = tempploty
	ENDFOR
	frmFormName.forecolor = rgb(0,0,0)
RETURN


