// This is a sample DTrace tags file.  Please modify for your own needs.

TAG_FILE_START

TAG_RANGE_START(TAG_RANGE_APP	, "My Dreamcast Game" )

	TAG_SUBRANGE( APP_Frame, "Per Frame Code" )
		TAG_FN( GameLogic, "Game Logic including physics and simulation","","" )
		TAG_FN( Rendering, "D3DIM rendering the 3D scene","","" )
		TAG_FN( Flipping, "Page flip between front buffer and back buffer","","" )

	TAG_SUBRANGE( APP_Initialization, "Game Initialization Code" )
		TAG_FN( DirectXInit, "DirectX Initialization","","" )
		TAG_FN( TextureInit, "Loading textures","","" )
		TAG_FN( SoundInit, "Loading sound clips","","" )

TAG_RANGE_END


TAG_FILE_END

/*

****************************
Sample usage:
****************************

***** application file1.cpp: *****

#include <DTrace.h>

#include "DTags.h"                  // this has to be included exactly once per application

main()
{
    LOG_INIT;                       // This must be called once per app or new thread before logging any events
    
    InitApp();
}


InitApp()
{
    LOG_ENTER( DirectXInit )  // Log entry into a function
    .....
    LOG_EXIT( DirectXInit )   // Log exit from a function
}

*/
