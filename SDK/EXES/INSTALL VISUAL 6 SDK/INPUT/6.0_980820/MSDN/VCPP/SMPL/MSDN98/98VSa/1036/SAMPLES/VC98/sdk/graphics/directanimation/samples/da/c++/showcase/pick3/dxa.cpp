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

        // Define constants
        SIZE = e->Scale3Uniform(0.25);
        PICKEVENT = e->LeftButtonDown;
		SPEED = e->DANumber(0.07);
		PI = 3.14159265359;


		// Import the geometries.
        IDAGeometryPtr rawCube = 
          e->ImportGeometry( _bstr_t(szGeo) + _bstr_t( "cube.wrl" ) );
        rawCube = rawCube->Transform(SIZE);

        IDAGeometryPtr rawCylinder = 
		    e->ImportGeometry(_bstr_t(szGeo) + _bstr_t("cylinder.wrl"));
        rawCylinder = rawCylinder->Transform(SIZE);

        IDAGeometryPtr rawCone = 
			e->ImportGeometry(_bstr_t(szGeo) + _bstr_t("cone.wrl"));
        rawCone = rawCone->Transform(SIZE);

        // Make the geometries pickable.
        IDAGeometryPtr cone1 = activate(rawCone, e->Green, e);

        IDAGeometryPtr cube1 = activate(rawCube, e->Magenta, e);

        IDAGeometryPtr cube2 = activate(rawCube, e->ColorHslAnim(e->Div(e->LocalTime,
          e->DANumber(8)), e->DANumber(1), e->DANumber(0.5)), e);

        IDAGeometryPtr cylinder = activate(rawCylinder, e->ColorRgb(0.8,0.4,0.4), e);

        // Construct the final geometry, scale and rotate it.
        IDAGeometryPtr multigeo = e->UnionGeometry(cone1->Transform(e->Translate3(0,1,0)),
          e->UnionGeometry(cube1->Transform(e->Translate3(0,0,1)),
            e->UnionGeometry(cube2->Transform(e->Translate3(0,0,-1)),cylinder)));

        IDAGeometryPtr geo = multigeo->Transform(e->Scale3Anim(e->Add(e->Abs(e->Sin(e->Mul(e->LocalTime,
          e->DANumber(0.2)))),e->DANumber(0.5)),e->Add(e->Abs(e->Sin(e->Mul(e->LocalTime,
            e->DANumber(0.26)))),e->DANumber(0.5)),e->Add(e->Abs(e->Sin(e->Mul(e->LocalTime,
              e->DANumber(0.14)))),e->DANumber(0.5))));
 
        IDATransform3Ptr transform1 = e->Rotate3Anim(e->ZVector3,
          e->Mul(e->DANumber(0.07), e->Mul(e->LocalTime, e->DANumber(1.9))));

        IDATransform3Ptr transform2 = e->Rotate3Anim(e->YVector3,
          e->Mul(e->DANumber(0.07), e->Mul(e->LocalTime, e->DANumber(PI))));

        IDAImagePtr movingGeoImg = geometryImage(geo->Transform(e->Compose3(e->Rotate3Anim(e->ZVector3,
          e->Mul(e->DANumber(0.07),e->Mul(e->LocalTime,e->DANumber(1.9)))), e->Rotate3Anim(e->YVector3,
            e->Mul(e->DANumber(0.07),e->Mul(e->LocalTime,e->DANumber(PI)))))), e);

		IDAImagePtr model = e->Overlay( movingGeoImg, e->SolidColorImage( e->Black ) );

      // Set the size and position of the viewport.
      //_view->SetViewport(100, 100, 300, 300);
      // Let the view draw to the primary surface.
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


IDAGeometryPtr DXA::activate(IDAGeometryPtr unpickedGeo, IDAColorPtr col, IDAStaticsPtr e)  {
  //IDAEventPtr pickEvent = e->Timer(3); // Hack for now until picking works.
  //IDAPickableResultPtr pickGeo = unpickedGeo->Pickable();
  //e->AndEvent(e->LeftButtonDown, pickGeo->PickEvent);
  
  IDANumberPtr numcyc;
  numcyc.CreateInstance( L"DirectAnimation.DANumber");
  numcyc->Init(e->Until(e->DANumber(0),PICKEVENT,
    e->Until(e->DANumber(1), PICKEVENT, numcyc)));

  IDAColorPtr colcyc;
  colcyc.CreateInstance( L"DirectAnimation.DAColor");
  colcyc->Init(e->Until(e->White, PICKEVENT, e->Until(col, PICKEVENT, colcyc)));

  IDATransform3Ptr xf = e->Rotate3Anim(e->XVector3, e->Integral(numcyc));

  return unpickedGeo->DiffuseColor(colcyc)->Transform(xf);

  //return pickGeo->Geometry->DiffuseColor(colcyc)->Transform(xf);

}

/* 
 * geometryImage
 * Renders a geometry as an image
 */
IDAImagePtr DXA::geometryImage(IDAGeometryPtr geo, IDAStaticsPtr e)  {
  IDANumberPtr scaleFactor = e->DANumber(0.02);

  IDATransform3Ptr perspTransform;
  perspTransform.CreateInstance( L"DirectAnimation.DATransform3");
  perspTransform->Init(e->Until(e->Compose3(e->Rotate3Anim(e->XVector3,
    e->Mul(SPEED,e->LocalTime)),e->Translate3(0, 0, 0.2)),PICKEVENT, 
      e->Until(e->Rotate3Anim(e->XVector3, e->Mul(SPEED,e->LocalTime)),
        PICKEVENT, perspTransform)));

  IDAGeometryPtr myLight = 
    e->UnionGeometry(e->DirectionalLight->Transform(perspTransform), e->DirectionalLight);

  IDACameraPtr perspectiveCam = (e->PerspectiveCamera(1,0))->Transform(e->Compose3(e->Rotate3Anim(e->XVector3,
    e->Mul(SPEED,e->LocalTime)),e->Translate3(0,0,0.2)));

  IDACameraPtr parallelCam = (e->ParallelCamera(1))->Transform(e->Rotate3Anim(e->XVector3,
    e->Mul(SPEED,e->LocalTime)));

  IDACameraPtr camera;
  camera.CreateInstance( L"DirectAnimation.DACamera");
  camera->Init(e->Until(perspectiveCam, PICKEVENT,
    e->Until(parallelCam, PICKEVENT, camera)));

  return e->UnionGeometry(geo->Transform(e->Scale3UniformAnim(scaleFactor)),
    myLight)->Render(camera);
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
