PUBLIC ox

=sys(1075)
close data
IF !FILE("frames.dbf")
	CREATE TABLE frames (frameno i,objno i,x1 i,y1 i,x2 i,y2 i)
ELSE
	USE frames
ENDIF
ox = Create("myForm")


ox.show



DEFINE CLASS myForm AS FORM
	pendown = .f.
	oldx = -1
	oldy = 0
	frameno = 1
	objno = 1
	add object cmdQuit as Commandbutton WITH ;
		caption= "Quit",cancel=.t.,width = 60
	add object cmdErase as Commandbutton WITH ;
		caption= "Erase",left = 80,width = 60
	add object cmdPlay as Commandbutton WITH ;
		caption= "\<Play",left = 160,width = 60
	add object cmdNextFrame as Commandbutton WITH ;
		caption= "NextFrame",left = 240,width = 80
	proc mousemove(btn,shft,m.x,m.y)
		if this.pendown
			this.drawmode = 10
			if this.oldx # -1
				thisform.line(this.oldx,this.oldy,this.currentx,this.currenty)
			endif
			thisform.line(this.oldx,this.oldy,m.x,m.y)
			this.drawmode = 1
		endif
	proc mousedown(btn,shft,m.x,m.y)
		LOCAL lx,ly
		if m.btn = 2
			this.drawmode = 10
			thisform.line(this.oldx,this.oldy,this.currentx,this.currenty)
			this.drawmode = 1
			this.pendown = .f.
			this.currentx = m.x
			this.currenty = m.y
			this.objno = this.objno + 1
			retu
		endif
		if this.pendown
			lx = this.currentx
			ly = this.currenty
			INSERT INTO frames (frameno,objno,x1,y1,x2,y2) values ;
				(this.frameno,this.objno,this.oldx,this.oldy,m.x,m.y)
				
			this.oldx = m.x
			this.oldy = m.y
		ELSE
			this.currentx = m.x
			this.currenty = m.y
			this.oldx = m.x
			this.oldy = m.y
			this.pendown = .t.
		ENDIF
	proc cmdquit.click
		thisform.release
	proc cmdErase.click
		thisform.pendown = .f.
		thisform.oldx = -1
		thisform.frameno = 1
		thisform.objno = 1
		zap
		thisform.cls
	proc cmdPlay.click
		nBetween = 15
		thisform.pendown = .f.
		thisform.oldx = -1
		thisform.cls
		LOCATE
		THISFORM.objno = 1
		THISFORM.frameno = frameno
		USE frames AGAIN IN 0 ALIAS frames2
		SELECT frames2
		LOCATE FOR frameno # frames.frameno
		SELECT frames
		DO WHILE !EOF("frames2")
			mr = recno()
			mr2 = recno("frames2")
			FOR nb = 1 TO nBetween && changed 0 to 1 in the loop -- RKH
				thisform.cls
				GO mr
				IF mr2 < RECCOUNT("frames2")
					GO mr2 IN frames2
				ENDIF
				nFrames1 = frames.frameno
				nFrames2 = frames2.frameno
				SCAN WHILE frames.frameno = nFrames1
					nx1 = frames.x1 + nb * (frames2.x1 - frames.x1) / nBetween
					ny1 = frames.y1 + nb * (frames2.y1 - frames.y1) / nBetween
					nx2 = frames.x2 + nb * (frames2.x2 - frames.x2) / nBetween
					ny2 = frames.y2 + nb * (frames2.y2 - frames.y2) / nBetween
					thisform.line(nx1,ny1,nx2,ny2)
					IF !EOF("frames2")
						SKIP IN frames2
						IF frames2.frameno # nFrames2
							SKIP -1 IN frames2
						ENDIF
					ENDI
				ENDSCAN
				SELECT frames2
				IF !EOF()
					SKIP
					LOCATE REST FOR frames2.Frameno # nFrames2
				ENDIF
				SELECT frames
				wait wind "" time .05
			ENDFOR
		ENDDO
		USE IN frames2
		SCAN REST
			thisform.line(x1,y1,x2,y2)
		ENDSCAN
		thisform.frameno = nFrames1 + 1
	proc cmdNextFrame.click
		thisform.frameno = thisform.frameno + 1
		thisform.cls
		thisform.objno = 1
ENDDEFINE

DEFINE CLASS myshape AS shape
	backcolor = rgb(255,0,0)
	visible = .t.
	top = 50
	width = 6
	height = 9
	left = 100
	proc mouseup(btn,shft,m.x,m.y)
		thisform.mouseup(btn,shft,m.x,m.y)
	proc mousedown(btn,shft,m.x,m.y)
		thisform.mousedown(btn,shft,m.x,m.y)
	proc mousemove(btn,shft,m.x,m.y)
		thisform.mousemove(btn,shft,m.x,m.y)
ENDDEFINE


DEFINE CLASS cPoint AS custom
	x = 0
	y = 0
ENDDEFINE

DEFINE CLASS cLine AS custom
	oP1 = .NULL.
	oP2 = .NULL.
ENDDEFINE