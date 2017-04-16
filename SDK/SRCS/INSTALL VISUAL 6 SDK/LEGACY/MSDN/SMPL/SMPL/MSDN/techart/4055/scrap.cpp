
void CSceneView::OnTimeIdentity() 
{
	CClientDC dc(this) ;
	CDC* pDC = &dc ;

	CDC* pdcTemp;
	CPalette* pPalTemp;

	//
	// Use Nigel's Animation Library CDIBSection and make an Identity palette
	//
	aDIBSurfaceIdent.Create(300, 300, NULL) ; //sizeBitmap.cx, sizeBitmap.cy, NULL) ;
	pdcTemp = aDIBSurfaceIdent.GetDC() ;

	aSceneCI.Create(pdcTemp) ;

	pPalTemp = aSceneCI.GetPalette() ;
	if (pPalTemp)
	{
		aDIBSurfaceIdent.SetPalette(pPalTemp) ;
	}

	aSceneCI.Resize(300,300) ;//sizeBitmap.cx, sizeBitmap.cy) ; //Doesn't resize?!!!!
	aSceneCI.Init() ;
	aSceneCI.Render() ;


	int iColors = 0;
    pPalTemp->GetObject(sizeof(iColors), &iColors) ;

	PALETTEENTRY PalEntries[256];
	PALETTEENTRY* pPalEntry = PalEntries;
	pPalTemp->GetPaletteEntries(0,iColors,PalEntries) ;

//----------------------------------------------------
#if 0
	BOOL bBkgnd = FALSE ;
	CRect aRect(0,0,300,300) ;
	CRect* pRect = &aRect ;
    CPalette *pOldPal = pDC->SelectPalette(pPalTemp, bBkgnd);
    pDC->RealizePalette();
	int icolors = iColors ;
    int i, j, top, left, bottom, right;
    for (j=0, top=0; j<16 && icolors; j++, top=bottom) {
        bottom = (j+1) * pRect->bottom / 16 + 1;
        for(i=0, left=0; i<16 && icolors; i++, left=right) {
            right = (i+1) * pRect->right / 16 + 1;
            CBrush br (PALETTEINDEX(j * 16 + i));
            CBrush *brold = pDC->SelectObject(&br);
            pDC->Rectangle(left-1, top-1, right, bottom);
            pDC->SelectObject(brold);
            icolors--;
        }
    }
    pDC->SelectPalette(pOldPal, FALSE);
#endif
//----------------------------------------------------
#if 0
	RGBQUAD RGB[256] ;
	RGBQUAD* pRGB = RGB;
	for(int k = 0 ; k < iColors ; k++)
	{
		pRGB->rgbRed 	= pPalEntry->peRed ;
		pRGB->rgbGreen 	= pPalEntry->peGreen ;
		pRGB->rgbBlue 	= pPalEntry->peBlue ;
		pRGB->rgbReserved = 0 ;
		pRGB++ ;
		pPalEntry++ ;
	}
	CDIBPal aIdentPal ;
	BOOL bResult = aIdentPal.Create(RGB, iColors) ; // can't use aDIBSurfaceIdent
#else
    // allocate a log pal and fill it with the color table info
    LOGPALETTE *pPal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE) + iColors * sizeof(PALETTEENTRY));
    PALETTEENTRY* pe = pPal->palPalEntry ;
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = (WORD) iColors; // table size
	pPalTemp->GetPaletteEntries(0,iColors, pe) ;
    int iSysColors = pDC->GetDeviceCaps(NUMCOLORS);
	int i ;
	for (i = 0; i < iSysColors/2; i++) {
        pe[i].peFlags = 0;
    }
    for (; i < iColors-iSysColors/2; i++) {
        pe[i].peFlags = PC_NOCOLLAPSE;
    }
    for (; i < iColors; i++) {
        pe[i].peFlags = 0;
    }

	CDIBPal aIdentPal ;
    BOOL bResult = aIdentPal.CreatePalette(pPal);
    free (pPal);
#endif
	
	ASSERT(bResult) ;

//	aIdentPal.GetPaletteEntries(0,iColors, PalEntries) ; // changed
//	aIdentPal.Draw(pDC,&CRect(100,0,400,300));
//	GdiFlush() ;
	aIdentPal.SetSysPalColors() ;

	//aDIBSurfaceIdent.SetPalette(&aIdentPal) ;
	//aDIBSurfaceIdent.Draw(pDC) ; //WORKS

	aIdentPal.Draw(pDC,&CRect(100,0,400,300));
//	GdiFlush() ;
//	AfxMessageBox("Wait!!!") ;

}

void CSceneView::OnTimingBlting() 
{
	if (m_bRotate) OnRotateStop() ;

	CClientDC dc(this) ;
	CDC* pDC = &dc ;


	int x = 0 ;
	int y = 0;
	int i ;
	int iReps = 30 ;
	DWORD diff[5] ;

//#define QPC 
#ifdef QPC
    LARGE_INTEGER li, liStart, liEnd;
    QueryPerformanceFrequency(&li); // value in Hz
    
    QueryPerformanceCounter(&liStart); // value in Hz
#else
	timeBeginPeriod(1) ;
	DWORD start;
start = timeGetTime() ;
#endif
	for (i = 0 ; i < iReps; i++)
	{
		aDIBSurface.BitBlt(pDC, x, 0, sizeBitmap.cx, sizeBitmap.cy, 0, 0) ;
		x+=20 ;
	}
	GdiFlush() ;
#ifdef QPC
    QueryPerformanceCounter(&liEnd); // value in Hz
  	diff[0]= liEnd.LowPart - liStart.LowPart;
    if (liEnd.HighPart > liStart.HighPart) {
        diff[0] = ~diff[0] + 1;
    }
#else
diff[0] = timeGetTime() - start ;
#endif
    CPalette *ppalOld = NULL;
	CPalette* pPalScene = aScene.GetPalette() ;
    if(pPalScene) {
        ppalOld = pDC->SelectPalette(pPalScene, 0);
        pDC->RealizePalette();		
    }

	x = 0 ;
	y = 0 ;
	CDC* pdcSrc = aDIBSurface.GetDC() ;
#ifdef QPC
    QueryPerformanceCounter(&liStart); // value in Hz
#else
start = timeGetTime() ;
#endif

	for (i = 0 ; i < iReps; i++)
	{
		pDC->BitBlt(x, 0, sizeBitmap.cx, sizeBitmap.cy, pdcSrc, 0, 0, SRCCOPY) ;
		x+=20 ;
	}
	GdiFlush() ;

#ifdef QPC
    QueryPerformanceCounter(&liEnd); // value in Hz
  	diff[1]= liEnd.LowPart - liStart.LowPart;
    if (liEnd.HighPart > liStart.HighPart) {
        diff[1] = ~diff[1] + 1;
    }
#else
	diff[1] = timeGetTime() - start ;
#endif

	// Do the 8 bpp test first ;
	x = 0 ;
	y = sizeBitmap.cy ;
#ifdef QPC
    QueryPerformanceCounter(&liStart); // value in Hz
#else
start = timeGetTime() ;
#endif

	for (i = 0 ; i < iReps; i++)
	{
		theSimpleDIB[0].Draw(pDC, x, y) ;			
		x+=20 ;
	}
	GdiFlush() ;

#ifdef QPC
    QueryPerformanceCounter(&liEnd); // value in Hz
  	diff[2]= liEnd.LowPart - liStart.LowPart;
    if (liEnd.HighPart > liStart.HighPart) {
        diff[2] = ~diff[2] + 1;
    }
#else
diff[2] = timeGetTime() - start ;
#endif

	x = 0 ;
	y += sizeBitmap.cy ;
#ifdef QPC
    QueryPerformanceCounter(&liStart); // value in Hz
#else
start = timeGetTime() ;
#endif

	for (i = 0 ; i < iReps; i++)
	{
		theSimpleDIB[1].Draw(pDC, x, y) ;			
		x+=20 ;
	}
	GdiFlush() ;

#ifdef QPC
    QueryPerformanceCounter(&liEnd); // value in Hz
  	diff[3]= liEnd.LowPart - liStart.LowPart;
    if (liEnd.HighPart > liStart.HighPart) {
        diff[3] = ~diff[3] + 1;
    }
#else
diff[3] = timeGetTime() - start ;
#endif

	x = 0 ;
	y += sizeBitmap.cy ;

#ifdef QPC
    QueryPerformanceCounter(&liStart); // value in Hz
#else
start = timeGetTime() ;
#endif
	for (i = 0 ; i < iReps; i++)
	{
		theSimpleDIB[2].Draw(pDC, x, y) ;			
		x+=20 ;
	}
	GdiFlush() ;

#ifdef QPC
    QueryPerformanceCounter(&liEnd); // value in Hz
  	diff[4]= liEnd.LowPart - liStart.LowPart;
    if (liEnd.HighPart > liStart.HighPart) {
        diff[4] = ~diff[4] + 1;
    }
#else
diff[4] = timeGetTime() - start ;
timeEndPeriod(1) ;
#endif
    if (ppalOld) pDC->SelectPalette(ppalOld, 0);


	CString aString	;
	aString.Format("Timing Results\n\tCDIBSurface(Select):\t\t%d\n\tCDIBSurface(No Select):\t\t%d\n\tCSimpleDIB(8 bpp):\t\t%d\n\tCSimpleDIB(16 bpp):\t\t%d\n\tCSimpleDIB(24 bpp):\t\t%d\n",
			diff[0],diff[1],diff[2],diff[3],diff[4]) ;

	AfxMessageBox(aString) ;

	Invalidate(FALSE) ;
	UpdateWindow() ;

}

