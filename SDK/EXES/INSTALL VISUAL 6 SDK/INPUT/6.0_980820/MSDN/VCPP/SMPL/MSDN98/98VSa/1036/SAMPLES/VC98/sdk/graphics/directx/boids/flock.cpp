/*
**-----------------------------------------------------------------------------
**	File:		flock.cpp 
**	Purpose:	-- where the boids are
**	Notes:
**
**  Copyright (c) 1995 - 1997 by Microsoft, all rights reserved.
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
** Include Files
**-----------------------------------------------------------------------------
*/

#include "Common.h"
#include "Debug.h"
#include "d3dutils.h"
#include "boids.h"



/*
**-----------------------------------------------------------------------------
** Constants
**-----------------------------------------------------------------------------
*/

const float InfluenceRadius = 20.0f;
const float InfluenceRadiusSquared = InfluenceRadius * InfluenceRadius;
const float CollisionFraction = 0.8f;
const float InvCollisionFraction = 1.0f/(1.0f-CollisionFraction);

const float NormalSpeed = 0.1f;
const float	AngleTweak = 0.02f;
const float PitchToSpeedRatio = 0.002f;



/*
**-----------------------------------------------------------------------------
** Functions
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
** Name:	UpdateFlock
** Purpose:	Update posiiton of each boid in flock
**-----------------------------------------------------------------------------
*/

void	
UpdateFlock (Flock flock)
{
	int		i, j;
	float	dist;

	// first update the dist array 0.0..1.0 with 0.0 being furthest away
	for (i=0; i<flock.num_boids; i++) {
		for (j=i+1; j<flock.num_boids; j++) {
			dist = SquareMagnitude(flock.boids[i].loc - flock.boids[j].loc);
			dist = InfluenceRadiusSquared - dist;
			if (dist < 0.0f) {
				dist = 0.0f;
			} else {
				dist /= InfluenceRadiusSquared;
			}
			flock.dist[i][j] = flock.dist[j][i] = dist;
		}
		flock.dist[i][i] = 0.0f;
		flock.boids[i].delta_dir = D3DVECTOR(0.0f);
		flock.boids[i].delta_pos = D3DVECTOR(0.0f);
		flock.boids[i].delta_cnt = 0;
	}

	for (i=0; i<flock.num_boids; i++) {
		for (j=i+1; j<flock.num_boids; j++) {
			// if i is near j have them influence each other
			if (flock.dist[i][j] > 0.0) {
				D3DVECTOR	diff = Normalize(flock.boids[i].loc - flock.boids[j].loc);
				D3DVECTOR	delta;
				float		col = 0.0f;		// collision weighting

				// only do collision testing against the nearest ones
				if (flock.dist[i][j] - CollisionFraction > 0.0f) {
					col = (flock.dist[i][j] - CollisionFraction) * InvCollisionFraction;
				}

				// add in a little flock centering
				if (flock.dist[i][j] - (1.0-CollisionFraction) > 0.0f) {
					col -= flock.dist[i][j] * (1.0f-col);
				}

				delta = col * diff;

				// add in the collision avoidance
				flock.boids[i].delta_pos += delta;
				flock.boids[j].delta_pos -= delta;

				// add in the velocity influences
				flock.boids[i].delta_dir += flock.boids[j].dir * flock.dist[i][j];
				flock.boids[j].delta_dir += flock.boids[i].dir * flock.dist[i][j];
				flock.boids[i].delta_cnt++;
				flock.boids[j].delta_cnt++;
			}
		}
	}

	// update the boids
	for (i=0; i<flock.num_boids; i++) {
		if (flock.boids[i].delta_cnt) {
			flock.boids[i].delta_dir /= (float)flock.boids[i].delta_cnt;
			flock.boids[i].delta_dir -= flock.boids[i].dir;
			flock.boids[i].delta_dir *= 1.5f;
		}
		D3DVECTOR	delta = flock.boids[i].delta_dir + flock.boids[i].delta_pos; // + 0.1f * D3DVECTOR(rnd()-rnd(), rnd()-rnd(), rnd()-rnd());
		D3DVECTOR	offset;

		//delta = Normalize(delta);

		// add in the influence of the global goal
		D3DVECTOR	goal = 0.5f * Normalize(flock.goal-flock.boids[i].loc);
		delta += goal;

		// add in any obstacles
		for (j=0; j<flock.num_obs; j++) {
			D3DVECTOR	ob = flock.boids[i].loc - flock.obs[j].loc;
			float		radius = flock.obs[j].radius;
			float		dist = Magnitude(ob);

			if (dist > 2*radius)
				continue;

			ob /= dist;	// normalize
			dist = 1.0f - dist/(2.0f*radius);
			delta += dist * ob * 5.0f;
		}

		// first deal with pitch changes
		if (delta.y > 0.01) {			// we're too low
			flock.boids[i].pitch += AngleTweak;
			if (flock.boids[i].pitch > 0.8f)
				flock.boids[i].pitch = 0.8f;
		} else if (delta.y < -0.01) {	// we're too high
			flock.boids[i].pitch -= AngleTweak;
			if (flock.boids[i].pitch < -0.8f)
				flock.boids[i].pitch = -0.8f;
		} else {
			// add damping
			flock.boids[i].pitch *= 0.98f;
		}

		// speed up or slow down depending on angle of attack
		flock.boids[i].speed -= flock.boids[i].pitch * PitchToSpeedRatio;
		// damp back to normal
		flock.boids[i].speed = (flock.boids[i].speed-NormalSpeed)*0.99f + NormalSpeed;

		if (flock.boids[i].speed < NormalSpeed/2) {
			flock.boids[i].speed = NormalSpeed/2;
		}
		if (flock.boids[i].speed > NormalSpeed*5) {
			flock.boids[i].speed = NormalSpeed*5;
		}

		// now figure out yaw changes
		offset = delta;
		offset.y = 0.0f;
		delta = flock.boids[i].dir;
		offset = Normalize(offset);
		float	dot = DotProduct(offset, delta);
		// speed up slightly if not turning much
		if (dot > 0.7f) {
			dot -= 0.7f;
			flock.boids[i].speed += dot * 0.005f;
		}
		offset = CrossProduct(offset, delta);
		dot = (1.0f-dot)/2.0f * 0.07f;
		if (offset.y > 0.05f) {
			flock.boids[i].dyaw = (flock.boids[i].dyaw*19.0f + dot) * 0.05f;
		} else if (offset.y < -0.05f) {
			flock.boids[i].dyaw = (flock.boids[i].dyaw*19.0f - dot) * 0.05f;
		} else {
			flock.boids[i].dyaw *= 0.98f;	// damp it
		}
		flock.boids[i].yaw += flock.boids[i].dyaw;
		flock.boids[i].roll = -flock.boids[i].dyaw * 20.0f;


	}

}	// end of UpdateFlock()


/*
**-----------------------------------------------------------------------------
** End of File
**-----------------------------------------------------------------------------
*/


