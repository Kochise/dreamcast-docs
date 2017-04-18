#import "danim.dll" \
  exclude( "_RemotableHandle", "IMoniker", "IPersist", "ISequentialStream", \
  "IParseDisplayName", "IOleClientSite", "_FILETIME", "tagSTATSTG" ) \
  rename( "GUID", "DAGUID" ) \
  rename_namespace( "DAnim" )

#include <stdio.h>
#include <sys\timeb.h>
#include <tchar.h>

#define WINDOW_WIDTH    300
#define WINDOW_HEIGHT   300

using namespace DAnim;

// Create the DirectAnimation class that will render to the primary DirectDraw
// surface.
class DXA  {
  
  public:
	BOOL initDXAViewObj(IUnknown *ddsurf);
	BOOL resetDXASurfaces(IUnknown *ddsurf);
	void tick();
  protected:
	static IDAViewPtr _view;
	IDAEventPtr PICKEVENT; // Hack for now until picking works.
	IDANumberPtr SPEED;
    IDATransform3Ptr SIZE;
	double PI;
	IDAImagePtr geometryImage(IDAGeometryPtr geo, IDAStaticsPtr e);
    IDAGeometryPtr activate(IDAGeometryPtr unpickedGeo, IDAColorPtr col, IDAStaticsPtr e);
};