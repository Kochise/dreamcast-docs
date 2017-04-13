/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       dxa.cpp
 *
 *  This file contains functions that make use of DirectX Animation
 *  to render animation to a ddraw surface.
 *
 ***************************************************************************/

#include "dxa.h"

IDAViewPtr DXA::_view = NULL;

/*
 * StartOle
 *
 * Start the Ole services.
 */
struct StartOle {
    StartOle() { CoInitialize( NULL ); }
    ~StartOle() { CoUninitialize(); }
} _inst_StartOle;

/*
 * dump_com_error
 *
 * Dump the com error should an exception occurs in InitDXAViewObj.
 * This is mainly for debugging purpose.
 */
void dump_com_error( _com_error &e )
{
    char buf[2048];

    sprintf(buf, _T( "Oops - hit an error!\n\tCode = %08lx\n\tCode meaning = %s\n" ),
            e.Error(), e.ErrorMessage());
    OutputDebugString(buf);
}

/*
 * initDXAViewObj
 *
 * Create the DAView object, construct the model, then start the model.
 *
 */
BOOL DXA::initDXAViewObj(IUnknown *ddsurf)
{
    try {
        IDAStaticsPtr e;

        // Create the statics object
        e.CreateInstance( L"DirectAnimation.DAStatics" );
        
        // Create and establish the view
        _view.CreateInstance( L"DirectAnimation.DAView" );

        // Import Media (images in this case).  The
		// GetCurrentDirectory() (which will return the path to either 
		// the debug or release sub directory) is used as a starting
		// point for relative file importing.
        TCHAR szMediaBase[_MAX_PATH];
		TCHAR szImg[_MAX_PATH];
		TCHAR szHead[_MAX_PATH];
	//	TCHAR szTest[_MAX_PATH];
        
        GetCurrentDirectory(sizeof(szMediaBase),szMediaBase);

		_tcscat(szMediaBase,_T("\\..\\..\\..\\..\\..\\media\\"));

		_tcscpy(szImg,szMediaBase);

		_tcscat(szImg,_T("image\\"));
		_tcscpy(szHead,szImg);
		_tcscat(szHead,_T("shingle.jpg"));
	//	_tcscat(szTest,_T("shingle.jpg"));
        
        _bstr_t headPath = _bstr_t( szHead );
    //    _bstr_t testPath = _bstr_t( szTest );

		IDAImagePtr head = e->ImportImage( headPath );
		//IDAImagePtr test = e->ImportImage( testPath );
        
        // Construct a new image by overlaying atop an empty image that
        // has an infinite bounding box.  This allows subsequent crops
        // to retain the "see-through-ness" that we're trying to
        // achieve. 
        head = e->Overlay( head, e->DetectableEmptyImage );

		// Construct four time varying values representing a rectangle
        // whose position is changing, and whose size is changing.  x,
        // y, width, and height.
        IDANumberPtr xPos = myRange(-0.03,0.01,0.8,e);
        IDANumberPtr yPos = myRange(-0.03,0.01,0.4,e);
        IDANumberPtr width = myRange(0.01,0.07,1.5,e);
        IDANumberPtr height = myRange(0.01,0.07,1.5,e);

        // Combine these numbers into points at the corners of a
        // rectangle. 
        IDAPoint2Ptr hMin = e->Point2Anim( xPos, yPos );
        IDAPoint2Ptr hMax =
            e->Point2Anim( e->Add( xPos, width ), e->Add( yPos, height ) );
        
        // Apply this rectangle as the cropping rectangle
        IDAImagePtr croppedHead = head->Crop( hMin, hMax );
        
        // Infinitely tile the result.  
        IDAImagePtr headTiles = croppedHead->Tile();
        
        // Build up a time-varying transform...
        IDATransform2Ptr xf1 = e->Translate2Anim( e->Mul( e->DANumber( 0.03 ),
            e->Sin( e->LocalTime ) ), e->Mul( e->DANumber( 0.03 ),
            e->Cos( e->Mul( e->LocalTime, e->DANumber( 0.3 ) ) ) ) );
        
        // ... and apply it to the head tiles to move the whole tiling
        // around.   This completes our top image.
        IDAImagePtr topIm = headTiles->Transform( xf1 );
        
        
        ////// Bottom Image
        
        // build up a time-varying transform to apply to the bottom image.
        IDATransform2Ptr xf2 = e->Translate2Anim( e->Mul( e->DANumber( 0.01 ),
            e->Sin( e->LocalTime ) ), e->Mul( e->DANumber( 0.01 ),
            e->Cos( e->LocalTime ) ) );
        
        // Construct two time varying colors that cycle through the
        // hues. 
        IDAColorPtr col1 = e->ColorHslAnim( e->Mul( e->LocalTime,
            e->DANumber( 0.5 ) ), e->DANumber( 0.5 ), e->DANumber( 0.5 ) );
        
        IDAColorPtr col2 = e->ColorHslAnim( e->Mul( e->LocalTime,
            e->DANumber( 0.43 ) ), e->DANumber( 0.5 ), e->DANumber( 0.5 ) );
        
        // Use these to construct a unit-sized gradient image with black
        // and white at two corners, and these time-varying colors at
        // the other two corners.
        IDAImagePtr gradImg = e->GradientSquare( col1, e->Black,
            col2, e->White );
        
        // Now scale this way down.
        gradImg = gradImg->Transform( e->Scale2UniformAnim( e->DANumber( 0.065 ) ) );
        
        // Create the bottom image by transforming the gradient image
        // around. 
        IDAImagePtr botImg = gradImg->Transform( xf2 );
        
        ////// Entire model
        
        // Finally, overlay the top over the bottom over a solid white
        // image. 
        IDAImagePtr model = e->Overlay( topIm, e->Overlay( botImg, 
	      e->SolidColorImage( e->White ) ) );
        
        // Set the size of the viewport.  Not doing this  (as done in this
		// case) will render the animation accross the entire primary surface.
		_view->SetViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		// Let the view draw to the primary surface.
        _view->IDirectDrawSurface = ddsurf;
		_view->CompositeDirectlyToTarget = FALSE;
		// Start the model on the view.
        _view->StartModel(model, e->Silence, 0);

    } catch (_com_error &e) {
        dump_com_error( e );
        return false;
    }
    return true;
}
/* myRange
 * For constructing a time-varying range.  This function
 * generates a time varying number bvr provided min and max
 * values, and a rate (number of cycles per second).
 */
IDANumberPtr DXA::myRange( double min, double max, 
						  double rate, IDAStaticsPtr e )  {
    // a = ( 1 + sin( time * rate ) ) * 0.5
    IDANumberPtr a = e->Mul( e->Add( e->DANumber( 1 ),
        e->Sin( e->Mul( e->DANumber( rate ), e->LocalTime ) ) ),
        e->DANumber( 0.5 ) );
    // b = (max - min) * a + min
    IDANumberPtr b = e->Add( e->Mul( e->DANumber( max - min ), a ),
        e->DANumber( min ) );
    return b;
}

BOOL DXA::resetDXASurfaces(IUnknown *ddsurf)
{
    try {
        _view->IDirectDrawSurface = ddsurf;
    } catch (_com_error &e) {
        dump_com_error( e );
        return false;
    }
    return true;
}


/*
 * tick
 * Ask DA to sample and display the model.
 */
void DXA::tick() {
	static double startTime = 0;
    struct _timeb timebuffer;

    if (_view != NULL) {
        _ftime( &timebuffer );
        double thisTime = timebuffer.time + ( timebuffer.millitm / 1000.0 );

        if ( startTime == 0 )  {
            startTime = thisTime;
            thisTime = 0;
        }
        else
            thisTime -= startTime;

        _view->Tick(thisTime);
        _view->Render();
    }
}
