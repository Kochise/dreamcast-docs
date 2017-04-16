#include "stdafx.h"
#include "cgl.h"

//
//
//
void CGL::MakeCurrent()
{
	ASSERT(m_hrc) ;
	ASSERT(m_pdc) ;
	
	if (m_pPal && !m_bDrawToBitmap)
	{
   		m_pdc->SelectPalette(m_pPal, 0);
   		m_pdc->RealizePalette();
	}

	if (m_hrc != wglGetCurrentContext())
	{
		//
		// Make the rendering context m_hrc current
		//
    	BOOL bResult = wglMakeCurrent(m_pdc->m_hDC, m_hrc);
		if (!bResult)
		{
			TRACE("wglMakeCurrent Failed %x\r\n", GetLastError() ) ;
			return ;
		}
	}
}

//
//
//
void CGL::OutputGlError(char* label) 
{
	GLenum errorno = glGetError() ;
	if (errorno != GL_NO_ERROR)
		TRACE("%s had error: #(%d) %s\r\n", label, errorno, gluErrorString(errorno)) ;
}



