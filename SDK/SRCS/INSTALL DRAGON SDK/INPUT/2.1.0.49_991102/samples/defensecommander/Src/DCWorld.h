/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCWorld.h

Abstract:

	Defines describing the world.    

-------------------------------------------------------------------*/

// 2D constants.
#define DCW_RESX2D							320
#define DCW_RESY2D							240

// 3D constants.
#define DCW_FOV								DC_TO_RADIANS(55.0f)
#define DCW_BASE_ZNEAR						16.0f
#define DCW_FAR_VIS_RADIUS					DCW_SPAWN_RADIUS

// For sky.
#define DCW_SKY_HEIGHT						4000.0f
#define DCW_WORLD_RADIUS					300000.0f

// For sun.
#define DCW_SUN_HEIGHT						(DCW_TERRAIN_OUTER_RADIUS-10)
#define DCW_SUN_RADIUS						1500.0f
#define DCW_SUN_DIR							DCVector(-2.0f,1.0f,1.0f) // This needs to be normalized.

// For lighting.
#define DCW_AMBIENT_INTENSITY				0.333f

// For terrain.
#define DCW_TERRAIN_LOW_HEIGHT				50.0f
#define DCW_TERRAIN_HIGH_HEIGHT				1500.0f
#define DCW_TERRAIN_INNER_RADIUS			150.0f
// This outer radius is not exact. The outer radius is dependent on the
// inner radius, the "tangential scale" and the number of textures used 
// to texture the terrain. This number below is based on inner radius 
// 100, 5 textures radially, 2 textures tangentially, scale 1.5.
#define DCW_TERRAIN_OUTER_RADIUS			4327.0f
#define DCW_TERRAIN_LOW_OUTER_RADIUS		1000.0f
#define DCW_TERRAIN_HIGH_INNER_RADIUS		(DCW_TERRAIN_LOW_OUTER_RADIUS + 2000.0f)
#define DCW_TERRAIN_HIGH_OUTER_RADIUS		(DCW_TERRAIN_OUTER_RADIUS - 1000.0f)
#define DCW_TERRAIN_PERIOD					1000.0f

#define DCW_SPAWN_RADIUS					(DCW_TERRAIN_OUTER_RADIUS+250.0f)

// For AI danger zone.
#define DCW_DANGER_LOW_HEIGHT				200.0f
#define DCW_DANGER_HIGH_HEIGHT				1250.0f
#define DCW_DANGER_LOW_OUTER_RADIUS			(DCW_TERRAIN_LOW_OUTER_RADIUS-100.0f)
#define DCW_DANGER_HIGH_INNER_RADIUS		(DCW_TERRAIN_HIGH_INNER_RADIUS-100.0f)
#define DCW_DANGER_HIGH_OUTER_RADIUS		(DCW_TERRAIN_HIGH_OUTER_RADIUS+200.0f)
#define DCW_DANGER_OUTER_RADIUS				(DCW_SPAWN_RADIUS-100.0f)

// For terrain coloring.
#define DCW_COLOR_DIRT_HIGH_LEVEL			20.0f
#define DCW_COLOR_GRASS_LOW_LEVEL			30.0f
#define DCW_COLOR_GRASS_HIGH_LEVEL			100.0f
#define DCW_COLOR_MOUNTAIN_LOW_LEVEL		500.0f

#define DCW_COLOR_DIRT_GRASS_TRANSITION_PERIOD		100.0f 
#define DCW_COLOR_GRASS_MOUNTAIN_TRANSITION_PERIOD	250.0f 
#define DCW_COLOR_MOUNTAIN_TRANSITION_PERIOD		500.0f

#define DCW_COLOR_GRASS_PERIOD				500.0f
#define DCW_COLOR_GRASS_A					(DCVector(0.3869f,0.4784f,0)*1.65f)
#define DCW_COLOR_GRASS_B					(DCVector(0.2601f,0.2954f,0)*1.65f)

#define DCW_COLOR_MOUNTAIN_PERIOD			500.0f
#define DCW_COLOR_MOUNTAIN_A				(DCVector(0.8902f,0.7412f,0.7451f)*1.10f)
#define DCW_COLOR_MOUNTAIN_B				(DCVector(0.8667f,0.7647f,0.8471f)*1.10f)

#define DCW_COLOR_DIRT_PERIOD				500.0f
#define DCW_COLOR_DIRT_A					(DCVector(0.3902f,0.2176f,0.1373f)*1.65f)
#define DCW_COLOR_DIRT_B					(DCVector(0.8902f,0.7412f,0.7451f)*1.10f)

// For observer collision.
#define DCW_OBSERVER_HEIGHT_MIN				50.0f // Needs to be enough above water to avioid clipping.
#define DCW_OBSERVER_HEIGHT_CENTER_MAX		1000.0f
#define DCW_OBSERVER_HEIGHT_OUTER_MAX		750.0f
#define DCW_OBSERVER_HEIGHT_ABOVE_TERRAIN	50.0f // Needs to be enough above buildings to avoid clipping.
#define DCW_OBSERVER_MAX_RADIUS				(0.5f*(DCW_TERRAIN_LOW_OUTER_RADIUS+DCW_TERRAIN_HIGH_INNER_RADIUS))
