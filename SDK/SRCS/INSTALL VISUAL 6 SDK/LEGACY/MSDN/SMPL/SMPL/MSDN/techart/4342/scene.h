#ifndef __CSCENE_H__
#define __CSCENE_H__

const int MSDN_DISPLAYLIST = 2000 ;
const char MSDN_STRING[] = "MSDN" ;
const int MSDN_COUNT = sizeof(MSDN_STRING) - 1  ;

class CScene : public CGL
{
public:	
	CScene() ;
	virtual ~CScene() ;

	// Rotation members
	void Rotate() ;
	CSize m_angle;

	// 
	GLYPHMETRICSFLOAT m_agmfMSDN[MSDN_COUNT] ;
   double m_dCenterOffset ;

	// Font Support
	int m_iFormat ;
	float m_fDeviation ;
	float m_fExtrusion ;
	CString m_theString ;
	CFont* m_pFontSelected ;

	int m_iFormatDefault ;
	float m_fDeviationDefault ;
	float m_fExtrusionDefault ;
	CString m_theStringDefault ;

	LOGFONT m_logFontDefault ;
	CFont m_FontDefault ;	

	int m_iFirstChar ;
	int m_iLastChar ;
	int m_iNumberChars ;
	int m_iDisplayListStart ;
	int m_iDisplayListBase ;

	void Create3DFont() ;

	void DoDialog(CWnd* pWnd) ;

	// Conversions To/From Radio Btns in Dialog.
	int FormatAsInt(int format) 
		{ return ( format == WGL_FONT_POLYGONS ? 0 : 1 );}

	int IntAsFormat(int BtnNum)
		{ return ( BtnNum == 0 ? WGL_FONT_POLYGONS : WGL_FONT_LINES) ;}

					   
protected:

	// Override
	virtual BOOL OnResize(int cx, int cy) ;
	virtual BOOL OnInit() ;
	virtual BOOL OnRender() ;	

} ;
#endif 
