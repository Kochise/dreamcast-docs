#ifndef BOIDS_H
#define BOIDS_H
/*
**-----------------------------------------------------------------------------
**  File:       Boids.h
**  Purpose:    Sample showing DrawPrimitive functionality 
**
**	Copyright (C) 1995 - 1997 Microsoft Corporation. All Rights Reserved.
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**	Include files
**-----------------------------------------------------------------------------
*/

#include "Common.h"


/*
**-----------------------------------------------------------------------------
**	Typedefs
**-----------------------------------------------------------------------------
*/

typedef struct t_boid {
	D3DVECTOR	loc;
	D3DVECTOR	dir;		// cur direction
	D3DVECTOR	delta_pos;	// change in position from flock centering
	D3DVECTOR	delta_dir;	// change in direction
	int			delta_cnt;	// number of boids that influence this delta_dir
	float		speed;
	float		yaw, pitch, roll, dyaw;
	D3DVECTOR	color;
} Boid;

typedef struct t_obstacle {
	D3DVECTOR	loc;
	float		radius;
} Obstacle;

typedef struct t_flock {
	int			num_boids;
	Boid		*boids;
	int			num_obs;
	Obstacle	*obs;
	float		**dist;	// 2-d array of boid distances, yuk what a waste
	D3DVECTOR	goal;
} Flock;



/*
**-----------------------------------------------------------------------------
**	Function Prototypes
**-----------------------------------------------------------------------------
*/

// Boids Functions
void UpdateFlock (Flock flock);


/*
**----------------------------------------------------------------------------
** End of File
**----------------------------------------------------------------------------
*/
#endif // BOIDS_H


