#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "animate.h"

class AFX_EXT_CLASS CGLImage 
{
	public:
		CGLImage() ;
		~CGLImage() ;

		enum TRANSLATEMETHOD {TRANS_DIY, TRANS_GDI, TRANS_BOTH} ;

		BOOL Load(LPCTSTR filename, TRANSLATEMETHOD enumMethod = TRANS_BOTH) ;
		BOOL Load(WORD wResId, TRANSLATEMETHOD enumMethod = TRANS_BOTH) ;

		void DrawPixels(CGL* pGL) ;
		void TexImage2D(CGL* pGL) ;

		int GetWidth() {return m_iWidth;}
		int GetHeight() {return m_iHeight;}

  		void* GetBitsPtr() {return m_pBits;}

		void SpecialCreate(int w, int h, void* pBits) ;

		BOOL TexMapScalePow2(CGL* pGL) ;
	protected:
		int m_iHeight ;
		int m_iWidth ;
		void* m_pBits ;
		GLenum m_PixelFormat ;
		TRANSLATEMETHOD m_enumMethod ;

		// Translation methods.
		void Translate(CDIB& aDib, TRANSLATEMETHOD enumMethod) ;
		void TranslateByYourself(CDIB& aDib, CDIBPal& aPalSrc) ;
		void TranslateByGDI(CDIB& aDib, CDIBPal& aPalSrc) ;
		void TranslateByBoth(CDIB& aDib, CDIBPal& aPalSrc) ;

		void CleanUp() ;
};

#endif //__IMAGE_H__
