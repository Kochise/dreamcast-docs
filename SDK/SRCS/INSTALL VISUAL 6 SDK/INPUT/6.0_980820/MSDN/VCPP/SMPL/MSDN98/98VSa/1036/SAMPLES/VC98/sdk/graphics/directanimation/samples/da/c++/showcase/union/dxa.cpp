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

        // Import Media (images and sound in this case).  The
		// GetCurrentDirectory() (which will return the path to either 
		// the debug or release sub directory) is used as a starting
		// point for relative file importing.
        TCHAR szMediaBase[_MAX_PATH];
		TCHAR szImg[_MAX_PATH];
		TCHAR szGeo[_MAX_PATH];
		TCHAR szSnd[_MAX_PATH];
        
        GetCurrentDirectory(sizeof(szMediaBase),szMediaBase);

		_tcscat(szMediaBase,_T("\\..\\..\\..\\..\\..\\media\\"));

		_tcscpy(szImg,szMediaBase);
		_tcscpy(szGeo,szMediaBase);
		_tcscpy(szSnd,szMediaBase);

		_tcscat(szImg,_T("image\\"));
		_tcscat(szGeo,_T("geometry\\"));
		_tcscat(szSnd,_T("sound\\"));
      
      IDAGeometryPtr rawSphere = 
        e->ImportGeometry( _bstr_t(szGeo) + _bstr_t( "sphere.wrl" ) );
      IDAGeometryPtr rawCube = 
        e->ImportGeometry( _bstr_t(szGeo) + _bstr_t( "cube.wrl" ) );
      IDAGeometryPtr rawCone = 
        e->ImportGeometry( _bstr_t(szGeo) + _bstr_t( "cone.wrl" ) );
      IDAGeometryPtr rawCylinder = 
        e->ImportGeometry( _bstr_t(szGeo) + _bstr_t( "cylinder.wrl" ) );

      // Import a sound, supply null as the second argument since we don't
      // want a length. 
      IDASoundPtr snd = e->ImportSound(  _bstr_t(szSnd) + _bstr_t( "etherial.mp2" ) )->Sound->Loop();

	  // Size the objects down.
      IDATransform3Ptr scaler = e->Scale3UniformAnim( e->DANumber( 0.25 ) );
      IDAGeometryPtr sphere   = rawSphere->Transform( scaler );
      IDAGeometryPtr cube     = rawCube->Transform( scaler );
      IDAGeometryPtr cone     = rawCone->Transform( scaler );
      IDAGeometryPtr cylinder = rawCylinder->Transform( scaler );

      IDAGeometryPtr xcone    = cone->Transform( e->Rotate3Anim(
        e->GetXVector3(), e->DANumber( 3.1415927 ) ) );

      IDAColorPtr color1 = myColor( 0, 2, e );
      IDAColorPtr color2 = myColor( 0.25, 3, e );
      IDAColorPtr color3 = myColor( 0.5, 4, e );
      IDAColorPtr color4 = myColor( 0.75, 1, e );

      // Shapes to start with (many with time varying colors)
      IDAGeometryPtr shapes[] = {
        sphere->DiffuseColor( color1 ),
        sphere->DiffuseColor( color1 ),
        cone->DiffuseColor( color2 ),
        xcone->DiffuseColor( color2 ),
        cube->DiffuseColor( color3 ),
        cube->DiffuseColor( color3 ),
        cylinder->DiffuseColor( color4 ) };

      // Places to Translate them to.
      double tls[][3] = { { 0.75, 0, 0 },
                         { -0.75, 0, 0 },
                         { 0, 0.75, 0 },
                         { 0, -0.75, 0 },
                         { 0, 0, 0.75 },
                         { 0, 0, -0.75 },
                         { 0, 0, 0 } };

      // Go ahead and accumulate up the Translated geometry by cycling
      // through the arrays.
      IDAGeometryPtr geo = e->EmptyGeometry;
      for ( int i = 0; i < sizeof( shapes ) / sizeof( shapes[0] ); i++ ) {
        IDATransform3Ptr xf = e->Translate3Anim( e->DANumber( tls[i][0] ),
          e->DANumber( tls[i][1] ), e->DANumber( tls[i][2] ) );
        geo = e->UnionGeometry( geo, shapes[i]->Transform( xf ) );
      }

      // Set the whole thing in motion
      IDATransform3Ptr xf =
          e->Compose3( e->Rotate3Anim( e->GetXVector3(), e->LocalTime ),
            e->Compose3( e->Rotate3Anim( e->GetZVector3(), e->Mul( e->LocalTime, e->DANumber( 1.9 ) ) ),
              e->Compose3( e->Rotate3Anim( e->GetYVector3(), e->Mul( e->LocalTime, e->DANumber( 3.1415927 ) ) ),
                e->Scale3UniformAnim( e->DANumber( 0.75 ) ) ) ) );

      geo = geo->Transform( xf );

      // Render into an image, and overlay atop a solid image.
      IDAImagePtr geoIm = geometryImage( e->UnionGeometry( geo, e->DirectionalLight ), e );

      IDAImagePtr model = e->Overlay( geoIm, e->SolidColorImage( e->White ) );
      
      // Set the size of the viewport.  Not doing this  (as done in this
      // case) will render the animation accross the entire primary surface.
	  _view->SetViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	  // Let the view draw to the primary surface.
      _view->IDirectDrawSurface = ddsurf;
	  _view->CompositeDirectlyToTarget = FALSE;
	  // Start the model on the view.
      _view->StartModel(model, snd, 0);

    } catch (_com_error &e) {
        dump_com_error( e );
        return false;
    }
    return true;
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
 * geometryImage
 * Renders a geometry as an image
 */
IDAImagePtr DXA::geometryImage( IDAGeometryPtr geo, IDAStaticsPtr e ) {
    IDACameraPtr cam = e->PerspectiveCameraAnim( e->DANumber( 1 ),
      e->DANumber( 0 ) )->Transform( e->Translate3Anim(
      e->DANumber( 0 ), e->DANumber( 0 ), e->DANumber( 2 ) ) );
    IDATransform2Ptr sc = e->Scale2UniformAnim( e->DANumber( 0.1 ) );

    return geo->Render( cam )->Transform( sc );
  }

/*
 * myColor
 * Create a animated color whose saturation varies over time.
 */
IDAColorPtr DXA::myColor( double hue, double saturationRate,
    IDAStaticsPtr e ) {
    IDANumberPtr sat = e->Add( e->Mul( e->Sin( e->Mul( e->LocalTime,
      e->DANumber( saturationRate ) ) ), e->DANumber( 0.5 ) ), e->DANumber( 0.5 ) );

    return e->ColorHslAnim( e->DANumber( hue ), sat, e->DANumber( 0.5 ) );
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
