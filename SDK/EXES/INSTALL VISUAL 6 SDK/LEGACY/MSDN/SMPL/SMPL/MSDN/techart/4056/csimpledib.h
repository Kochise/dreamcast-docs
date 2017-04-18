#ifndef __CSimpleDIB_H__
#define __CSimpleDIB_H__

//
// CSimpleDIB -
//
// Implements a simple encapsulation of a DIB section and a DC.
//
class CSimpleDIB
{
	public:
		// Construction
		CSimpleDIB() ;
		virtual ~CSimpleDIB() ;

      // Create a CSimpleDIB object. Create can be called multiple times.
		void Create(int cx, int cy, int ibitcount ) ;

      // Draw the DIB onto the destination DC. 
		void Draw(CDC* pdcDest, int x, int y) ;

      // Set the palette used in the DIB.
		void SetPalette(CPalette* pPal) ;

		CDC* GetDC() {return m_pdc;}
		HBITMAP GetHandle() {return m_hbmp;}


	protected:
		HBITMAP m_hbmp ;
		HBITMAP m_hbmOld ;
		void* m_pBits ;		// Pointer to the bits.
		CSize m_sizeDIB ;
		CDC* m_pdc ;
	
		void destroy() ; 	// Destruction helper.
	
};
#endif 
