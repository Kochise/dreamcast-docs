* Plot graph.
* Parameter:
* 1) cEquation in terms of X.  Will plot the answer as Y.  TYPE = Character.
* 2) nStepInc.  Step increment.  TYPE = Numeric.
* 3) nEquColor.  TYPE = Numeric.
* 4) lConnect.  If the previous point is connected to the current point with a line.  TYPE = Logical.
* 5) nXCenter.  Point on form where x = 0.  TYPE = Numeric.
* 6) nYCenter.  Point on form where y = 0.  TYPE = Numeric.
* 7) lAddCoords.  If you should add coordinate lines.  TYPE = Logical.
* 8) frmFormName.  Name for form to write on.  TYPE = Character.
* 9) nEquScale. Scale to graph equation.  TYPE = Numeric.

PARAMETER cEquation,nStepInc,nEquColor,lConnect,nXCenter,nYCenter,lAddCoords,frmFormName,nEquScale
	PRIVATE nOldY,nOldX,nTempMaxNum
	
IF PARAMETERS()	< 9
	#define CGRAPH_LOC "Ce programme requiert des paramètres multiples."
	WAIT WINDOW CGRAPH_LOC
	RETURN
ENDIF

	** Set maxiumn values of plotting.
	nTempMaxNum = 30000
	IF TYPE('nEquScale') <> "N"
		nEquScale = 1
	ENDIF	

	IF lAddCoords
		* Add coordinate lines.  X=0 and Y=0.
		frmFormName.forecolor = rgb(0,0,0)
		frmFormName.line(m.nXCenter,0,m.nXCenter,frmFormName.height)
		frmFormName.line(0,m.nYCenter,frmFormName.width,m.nYCenter)
	ENDIF	

	
	** Calcuate old values for x,y (nOldX,nOldY).  Used if connect is True.
	nOldX = (0-m.nXCenter)/m.nEquScale
	** Need to use x for the eval of m.cEquation.
	m.x = nOldX
 	nOldY = EVALUATE(m.cEquation)*m.nEquScale
	

	frmFormName.forecolor = m.nEquColor
 	** Loop from left to right all values of x and calculate the y value.
	FOR m.nXTemp = (0-m.nXCenter)/m.nEquScale TO (frmFormName.width-m.nXCenter)/m.nEquScale step m.nStepInc/m.nEquScale
		m.x = m.nXTemp
		nY = EVALUATE(m.cEquation)*m.nEquScale
		IF m.lConnect
			IF m.nYCenter-nOldY < m.nTempMaxNum and m.nYCenter-m.nY < m.nTempMaxNum and m.nYCenter-nOldY > m.nTempMaxNum*-1 and m.nYCenter-nY > m.nTempMaxNum*-1
				frmFormName.line(m.nXCenter+(nOldX*m.nEquScale),m.nYCenter-nOldY,m.nXCenter+(m.nXTemp*m.nEquScale),m.nYCenter-m.nY)
			ENDIF
		ELSE
			IF m.nYCenter-m.nY < m.nTempMaxNum and m.nYCenter-m.nY > m.nTempMaxNum*-1
				frmFormName.pset(m.nXCenter+(m.nXTemp*m.nEquScale),m.nYCenter-y)
			ENDIF
		ENDIF
		nOldX = m.nXTemp
		nOldY = m.nY 
	ENDFOR
	frmFormName.forecolor = rgb(0,0,0)
RETURN


