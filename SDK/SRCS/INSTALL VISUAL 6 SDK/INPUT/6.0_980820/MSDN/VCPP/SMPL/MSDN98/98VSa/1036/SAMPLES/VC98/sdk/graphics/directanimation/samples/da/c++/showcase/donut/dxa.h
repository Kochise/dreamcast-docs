#import "danim.dll" \
  exclude( "_RemotableHandle", "IMoniker", "IPersist", "ISequentialStream", \
  "IParseDisplayName", "IOleClientSite", "_FILETIME", "tagSTATSTG" ) \
  rename( "GUID", "DAGUID" ) \
  rename_namespace( "DAnim" )

using namespace DAnim;

BOOL initDXAViewObj(IUnknown *ddsurf);
BOOL resetDXASurfaces(IUnknown *ddsurf);
void tick(IDAViewPtr view);

extern IDAViewPtr view1, view2;
#define WINDOW_WIDTH    150
#define WINDOW_HEIGHT   150
