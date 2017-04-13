/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: control.h
 *
 ***************************************************************************/

#ifndef __CONTROL_H_
#define __CONTROL_H_

// Type to define what app is currently doing
typedef enum
{
    DOING_INTRO,
    PLAYING_DEMO,
    BETWEEN_CAM_VIEWS,
}
AppState;

// Type to define what state the opponent is in
typedef enum
{
    DEFENSIVE,
    CAUTIOUS,
    AGGRESSIVE,
}
PlayerState;

// Type to define what kind of camera angles were using
typedef enum
{
    OVER_SHOULDER,
    BOTH_IN_VIEW,
    PILOT_VIEW,
}
CameraState;

// Type to define what action the player is doing
typedef enum
{
    BOBBING,
    WALKING,
    PUNCHING,
    BLOCKING,
    BEEN_HIT,
    DEAD,
    VICTORY,
    DISABLED,
}
PlayerActionState;

// Structures
struct AnimArgs
{
    LPDIRECT3DRMANIMATIONSET	lpAnimSet;
    D3DVALUE			time;
};

void Player1AnimationCallback(LPDIRECT3DRMFRAME obj, void* arg, D3DVALUE delta);
void Player2AnimationCallback(LPDIRECT3DRMFRAME obj, void* arg, D3DVALUE delta);

void CheckInputAndUpdate();
void UpdateOpponent();
void UpdateDebris();
void RunIntro();
void PositionCamera();
void TransitionCamera();
void AddDebris(D3DVECTOR vOrg, D3DVECTOR vVel, LPDIRECT3DRMMESHBUILDER pDebris);

#endif

