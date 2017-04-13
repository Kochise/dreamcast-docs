/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: control.cpp
 *
 ***************************************************************************/

// Includes....
#include "rm.h"
#include "control.h"
#include "directx.h"

// Defines....
#define MOVE_NORMAL                     D3DVAL(10)
#define MOVE_FAST                       D3DVAL(20)

#define MIN_DIST_TO_OPPONENT            D3DVAL(100)

#define PLAYER_MOVE_FORWARD             VK_UP
#define PLAYER_MOVE_BACKWARD            VK_DOWN
#define PLAYER_BLOCK                    VK_CONTROL
#define PLAYER_ATTACK                   VK_SPACE

#define CAM_BOTH_IN_VIEW                VK_F1
#define CAM_OVER_THE_SHOULDER           VK_F2
#define CAM_PILOT                       VK_F3

#define NUM_BOB_FRAMES                  D3DVAL(30)
#define NUM_DEAD_FRAMES                 D3DVAL(66)
#define NUM_PUNCH_FRAMES                D3DVAL(29)
#define NUM_BEEN_HIT_FRAMES             D3DVAL(14)
#define NUM_BLOCKING_FRAMES             D3DVAL(16)
#define NUM_VICTORY_FRAMES              D3DVAL(55)

#define BOB_START                       D3DVAL(1)
#define DEAD_START                      D3DVAL(94)
#define DEAD_HIT_GROUND                 D3DVAL(115)
#define PUNCH_START                     D3DVAL(31)
#define PUNCH_ARM_COCKED                D3DVAL(50)
#define BLOCK_START                     D3DVAL(77)
#define BEEN_HIT_START                  D3DVAL(62)
#define HEAD_RETURNING                  D3DVAL(68)
#define VICTORY_START                   D3DVAL(161)

#define EDGE_LEFT                       D3DVAL(-600)
#define EDGE_RIGHT                      D3DVAL(600)

// Globals....

// States
AppState                g_appState = DOING_INTRO;
PlayerState             g_oppState = CAUTIOUS;
CameraState             g_camState = BOTH_IN_VIEW;

PlayerActionState       g_player1State = BOBBING;
PlayerActionState       g_player2State = BOBBING;

AnimArgs                g_player1AnimArgs;
AnimArgs                g_player2AnimArgs;

BOOL                    g_bPlayer1Attacking = FALSE;
BOOL                    g_bPlayer1Blocking  = FALSE;

DWORD                   g_player1health = 100;
DWORD                   g_player2health = 100;

// Timed lengths for each animation in milliseconds
#define BOB_TIME_MS     D3DVAL(500)
#define PUNCH_TIME_MS   D3DVAL(600)
#define BLOCK_TIME_MS   D3DVAL(500)
#define HIT_TIME_MS     D3DVAL(500)
#define DEAD_TIME_MS    D3DVAL(4000)
#define VICTORY_TIME_MS D3DVAL(3000)

// Timing deltas, used for scaling animation to frame rate
D3DVALUE                g_bobDelta     = NUM_BOB_FRAMES / BOB_TIME_MS;
D3DVALUE                g_attackDelta  = NUM_PUNCH_FRAMES / PUNCH_TIME_MS;
D3DVALUE                g_blockDelta   = NUM_BLOCKING_FRAMES / BLOCK_TIME_MS;
D3DVALUE                g_hitDelta     = NUM_BEEN_HIT_FRAMES / HIT_TIME_MS;
D3DVALUE                g_deadDelta    = NUM_DEAD_FRAMES / DEAD_TIME_MS;
D3DVALUE                g_victoryDelta = NUM_DEAD_FRAMES / DEAD_TIME_MS;

// Externals....
extern LPDIRECT3DRM             g_lpD3DRM;
extern LPDIRECT3DRMFRAME        g_lpScene;
extern LPDIRECT3DRMFRAME        g_lpCamera;
extern LPDIRECT3DRMFRAME        g_lpPlayer1;
extern LPDIRECT3DRMFRAME        g_lpPlayer1HeadFrame;
extern LPDIRECT3DRMFRAME        g_lpPlayer2;
extern LPDIRECT3DRMFRAME        g_lpPlayer2HeadFrame;
extern LPDIRECT3DRMFRAME        g_lpTmp;
extern LPDIRECT3DRMANIMATION    g_lpAnim;
extern LPDIRECT3DRMMESHBUILDER  g_lpRedDebris;
extern LPDIRECT3DRMMESHBUILDER  g_lpBlueDebris;
extern Debris                   g_debris[NUM_DEBRIS];
extern LPDIRECTSOUND3DLISTENER  g_lpDs3dListener; // Defined in DIRECTX.CPP


//----------------------------------------------------------------------
// 
// Function     : IsKeyDown()
//
// Purpose      : Returns TRUE if specified key is being pressed
//
//----------------------------------------------------------------------

BOOL IsKeyDown(int virtKeyCode)
{
    if (GetAsyncKeyState(virtKeyCode) & 0x8000) return TRUE;

    return FALSE;
}

//----------------------------------------------------------------------
// 
// Function     : Player1AnimationCallback()
//
// Purpose      : Animation call back for player 1
//
//----------------------------------------------------------------------

void CDECL Player1AnimationCallback(LPDIRECT3DRMFRAME obj, void* arg, D3DVALUE delta)
{       
    D3DVALUE time = g_player1AnimArgs.time;
    D3DVECTOR player1pos;
    D3DVECTOR player2pos;
    
    // Booleans to help with sound playing
    static BOOL bHitGround              = FALSE;
    static BOOL bPlayedWhoosh   = FALSE;

    // Get the players positions
    g_lpPlayer1->GetPosition(g_lpScene, &player1pos);   
    g_lpPlayer2->GetPosition(g_lpScene, &player2pos);
    
    // Compute distance between players
    D3DVALUE curDist = player2pos.z - player1pos.z;

    // Do something based upon the state of player 1
    switch (g_player1State)
    {
        case BOBBING :
        {       
            // Forward the bobbing animation time
            g_player1AnimArgs.lpAnimSet->SetTime(time);                 
            time += (g_bobDelta * delta);
            
            // Reset if animation has ended
            if (time > BOB_START + NUM_BOB_FRAMES) time = BOB_START;
            
            // Record the new time
            g_player1AnimArgs.time = time;
        }
        break;

        case PUNCHING :
        {
            // Forward the punching animation time
            g_player1AnimArgs.lpAnimSet->SetTime(time);
            time += (g_attackDelta * delta);

            // Play a whoosh sound if player 1's arm has gone back and is about to punch
            if ((time > PUNCH_ARM_COCKED) && (!bPlayedWhoosh))
            {
                // Play the whoosh
                PlaySoundDS(rand() % 2 == 0 ? WHOOSH1 : WHOOSH2,player1pos);                               
                bPlayedWhoosh = TRUE;
            }

            // If the punch has played, see if we hit the opponent
            if (time > PUNCH_START + NUM_PUNCH_FRAMES) 
            {
                // Reset player 1's state to BOBBING
                time               = BOB_START;
                g_player1State = BOBBING;
                bPlayedWhoosh  = FALSE;

                // Play a servo sound
                PlaySoundDS(SERVO_DOWN_1,player1pos);

                // Now, decide whether we have hit the other player
                if (curDist < MIN_DIST_TO_OPPONENT + D3DVAL(20))
                {               
                    // The opponent may be blocking
                    if ((g_player2State == BLOCKING) && 
                        (g_player2AnimArgs.time > BLOCK_START + (NUM_BLOCKING_FRAMES / D3DVAL(2)))) 
                    {
                        // The opponent blocked the punch, so play the block sound
                        PlaySoundDS(BLOCK1 + (rand() % 3),player2pos);
                        break;
                    }

                    // We're within the striking distance
                    if (g_player2health == 0) return;

                    // Add some debris into the scene to register a hit and play a sound        
                    D3DVECTOR debrisOrg = player1pos;
                    D3DVECTOR debrisVel = { D3DVAL(0), D3DVAL(0), D3DVAL(-10) };
                    
                    debrisOrg.x += D3DVAL(40);
                    debrisOrg.y += D3DVAL(40);
                    debrisOrg.z += D3DVAL(90);
                    
                    // Add some debris
                    AddDebris(debrisOrg, debrisVel, g_lpRedDebris);

                    // Decrease the opponents health
                    if (g_player2health > 0) g_player2health -= 10;
                                            
                    if (g_player2health == 0)
                    {
                        // The opponent has died!
                        g_player2State = DEAD;
                        g_player2AnimArgs.time = DEAD_START;
                        g_player2AnimArgs.lpAnimSet->SetTime(DEAD_START);
                        PlaySoundDS(HEAD_SPRING,player2pos);
                        
                        // And the player has victory!
                        g_player1State = VICTORY;
                        g_player1AnimArgs.time = VICTORY_START;
                        g_player1AnimArgs.lpAnimSet->SetTime(VICTORY_START);

                        PlaySoundDS(VICTORY_YEAH,player1pos);

                        return;
                    }

                    // Play a punch sound
                    PlaySoundDS(rand() % 2 == 0 ? PLAYER1_PUNCH1 : PLAYER1_PUNCH2,player2pos);

                    // Recalculate the power bars
                    RecalcPowerBars(g_player1health, g_player2health);
                    
                    // Make sure we force the camera to the correct place
                    PositionCamera();

                    // Setup the opponents animation and state
                    g_player2State = BEEN_HIT;
                    g_player2AnimArgs.time = BEEN_HIT_START;
                    g_player2AnimArgs.lpAnimSet->SetTime(BEEN_HIT_START);
                    
                    // What should the opponent do?
                    if (rand() % 10 < 2)
                    {
                        // Make the opponent defensive
                        g_oppState = DEFENSIVE;
                    }

                    // Play the ouch sound
                    PlaySoundDS(PLAYER2_OUCH,player1pos);
                }
            }

            // Record the new animation time
            g_player1AnimArgs.time = time;
        }
        break;
        
        case BLOCKING : 
        {
            // Forward the blocking animation time
            g_player1AnimArgs.lpAnimSet->SetTime(time);
            
            // Hold the block up if CTRL is held down
            if (GetAsyncKeyState(PLAYER_BLOCK) & 0x8000)
            {
                if (time < BLOCK_START + (NUM_BLOCKING_FRAMES / 2)) time += (g_blockDelta * delta);
            }
            else
            {
                time += (g_blockDelta * delta);
            }

            // Reset player 1's state to BOBBING if the animation has ended
            if (time > BLOCK_START + NUM_BLOCKING_FRAMES) 
            {
                time            = BOB_START;
                g_player1State  = BOBBING;
            }

            // Record the new animation time
            g_player1AnimArgs.time = time;
        }
        break;

        case BEEN_HIT :
        {
            // Forward the been hit animation time
            g_player1AnimArgs.lpAnimSet->SetTime(time);
            time += (g_hitDelta * delta);

            if (player1pos.z > EDGE_LEFT) g_lpPlayer1->SetPosition(g_lpScene, player1pos.x, player1pos.y, player1pos.z - D3DVAL(5));
            PositionCamera();

            // Reset player 1's state to BOBBING if the animation has ended
            if (time > BEEN_HIT_START + NUM_BEEN_HIT_FRAMES) 
            {
                time            = BOB_START;
                g_player1State  = BOBBING;
            }
            
            // Record the new animation time
            g_player1AnimArgs.time = time;
        }
        break;
        
        case DEAD :
        {
            // Forward the death animation time
            g_player1AnimArgs.lpAnimSet->SetTime(time);
            time += (g_deadDelta * delta);

            // Play a crash sound if the animation has passes the DEAD_HIT_GROUND frame
            if ((time > DEAD_HIT_GROUND) && (!bHitGround))
            {
                bHitGround = TRUE;
                PlaySoundDS(BLOCK3,player1pos);
            }

            // Reset player 1's state to BOBBING if the animation has ended
            if (time > DEAD_START + NUM_DEAD_FRAMES) 
            {
                time            = BOB_START;
                g_player1State  = BOBBING;
                g_player1health = 100;
                bHitGround      = FALSE;

                RecalcPowerBars(g_player1health, g_player2health);
            }
            
            // Record the new animation time
            g_player1AnimArgs.time = time;

            // Position the camera correctly
            PositionCamera();
        }
        break;

        case VICTORY :
        {
            // Forward the victory animation time
            g_player1AnimArgs.lpAnimSet->SetTime(time);
            time += (g_victoryDelta * delta);

            if (time > VICTORY_START + NUM_VICTORY_FRAMES) 
            {
                time            = BOB_START;
                g_player1State  = BOBBING;
            }
            g_player1AnimArgs.time = time;

            PositionCamera();
        }
        break;
    }
}

//----------------------------------------------------------------------
// 
// Function     : Player2AnimationCallback()
//
// Purpose      : Animation call back for player 2
//
//----------------------------------------------------------------------

void CDECL Player2AnimationCallback(LPDIRECT3DRMFRAME obj, void* arg, D3DVALUE delta)
{
    D3DVALUE time = g_player2AnimArgs.time;
    D3DVECTOR player1pos;
    D3DVECTOR player2pos;

    // Booleans to help with sound playing
    static BOOL bHitGround              = FALSE;
    static BOOL bPlayedWhoosh   = FALSE;

    // Get the players positions
    g_lpPlayer1->GetPosition(g_lpScene, &player1pos);   
    g_lpPlayer2->GetPosition(g_lpScene, &player2pos);

    // Compute distance between players
    D3DVALUE curDist = player2pos.z - player1pos.z;

    // Do something based upon the state of player 1
    switch (g_player2State)
    {
        case BOBBING :
        {       
            // Forward the bobbing animation time
            g_player2AnimArgs.lpAnimSet->SetTime(time);
            time += (g_bobDelta * delta);

            // Reset if animation has ended
            if (time > BOB_START + NUM_BOB_FRAMES) time = BOB_START;

            // Record the new time
            g_player2AnimArgs.time = time;
        }
        break;

        case PUNCHING :
        {
            // Forward the punching animation time
            g_player2AnimArgs.lpAnimSet->SetTime(time);
            time += (g_attackDelta * delta);

            // Play a whoosh sound if player 2's arm has gone back and is about to punch
            if ((time > PUNCH_ARM_COCKED) && (!bPlayedWhoosh))
            {
                // Play the whoosh
                PlaySoundDS(rand() % 2 == 0 ? WHOOSH1 : WHOOSH2,player2pos);                               
                bPlayedWhoosh = TRUE;
            }
    
            // If the punch has played, see if we hit the opponent
            if (time > PUNCH_START + NUM_PUNCH_FRAMES) 
            {
                time = BOB_START;
                g_player2State = BOBBING;
                bPlayedWhoosh  = FALSE;
                
                // Play a servo sound
                PlaySoundDS(SERVO_DOWN_2,player2pos);

                // Now, decide whether we have hit the other player
                if (curDist < MIN_DIST_TO_OPPONENT + D3DVAL(20))
                {               
                    // The opponent may be blocking
                    if ((g_player1State == BLOCKING) && 
                        (g_player1AnimArgs.time > BLOCK_START + (NUM_BLOCKING_FRAMES / D3DVAL(2)))) 
                    {
                        // The opponent blocked the punch, so play the block sound
                        PlaySoundDS(BLOCK1 + (rand() % 3),player1pos);
                        break;
                    }

                    // We're within the striking distance
                    if (g_player1health <= 0) return;

                    // We're within the striking distance
                    // Add some debris into the scene to register a hit and play a sound        
                    D3DVECTOR debrisOrg = player1pos;
                    D3DVECTOR debrisVel = { D3DVAL(0), D3DVAL(0), D3DVAL(10) };
                    
                    debrisOrg.x += D3DVAL(-40);
                    debrisOrg.y += D3DVAL(40);
                    debrisOrg.z += D3DVAL(-10);
                    
                    // Add some debris
                    AddDebris(debrisOrg, debrisVel, g_lpBlueDebris);

                    // Play a punch sound
                    PlaySoundDS(rand() % 2 == 0 ? PLAYER2_PUNCH1 : PLAYER2_PUNCH2,player1pos);

                    // Decrease the opponents health
                    if (g_player1health > 0) g_player1health -= 10;

                    if (g_player1health == 0)
                    {
                        // The player has died!
                        g_player1State = DEAD;
                        g_player1AnimArgs.time = DEAD_START;
                        g_player1AnimArgs.lpAnimSet->SetTime(DEAD_START);
                        PlaySoundDS(HEAD_SPRING,player1pos);

                        // And the opponent has victory!
                        g_player2State = VICTORY;
                        g_player2AnimArgs.time = VICTORY_START;
                        g_player2AnimArgs.lpAnimSet->SetTime(VICTORY_START);

                        // The crowd is not happy....
                        PlaySoundDS(VICTORY_BOO,player2pos);

                        return;
                    }

                    // Recalculate the power bars
                    RecalcPowerBars(g_player1health, g_player2health);
                    
                    // Force a camera positional update
                    PositionCamera();
                    
                    if (g_player1State != BEEN_HIT)
                    {
                        // Change player 1's state to BEEN_HIT,
                        g_player1State = BEEN_HIT;

                        // And set the animation time
                        g_player1AnimArgs.time = BEEN_HIT_START;
                        g_player1AnimArgs.lpAnimSet->SetTime(BEEN_HIT_START);                                           
                    }

                    // Play the ouch sound
                    PlaySoundDS(PLAYER1_OUCH,player1pos);
                }
            }

            // Record the new animation time
            g_player2AnimArgs.time = time;
        }
        break;

        case BEEN_HIT :
        {
            // Forward the been hit animation time
            g_player2AnimArgs.lpAnimSet->SetTime(time);
            time += (g_hitDelta * delta);
            
            // Move the player
            if (player2pos.z < EDGE_RIGHT) g_lpPlayer2->SetPosition(g_lpScene, player2pos.x, player2pos.y, player2pos.z + D3DVAL(5));
            
            // Force a camera position update
            PositionCamera();

            // Reset to BOBBING if animation has ended
            if (time > BEEN_HIT_START + NUM_BEEN_HIT_FRAMES) 
            {
                time = BOB_START;
                g_player2State = BOBBING;
            }
            
            // Record the new animation time
            g_player2AnimArgs.time = time;
        }
        break;

        case BLOCKING : 
        {
            // Forward the blocking animation time
            g_player2AnimArgs.lpAnimSet->SetTime(time);
            time += (g_blockDelta * delta);

            // Reset to BOBBING if animation has ended
            if (time > BLOCK_START + NUM_BLOCKING_FRAMES) 
            {
                time            = BOB_START;
                g_player2State  = BOBBING;
                g_oppState      = AGGRESSIVE;
            }
            
            // Record the new animation time
            g_player2AnimArgs.time = time;
        }
        break;

        case DEAD :
        {
            // Forward the death animation time
            g_player2AnimArgs.lpAnimSet->SetTime(time);
            time += (g_deadDelta * delta);

            // Play the BLOCK3 sound when the opponent hits the ground
            if ((time > DEAD_HIT_GROUND) && (!bHitGround))
            {
                bHitGround = TRUE;
                PlaySoundDS(BLOCK3,player2pos);
            }

            // Reset to BOBBING if the animation has ended
            if (time > DEAD_START + NUM_DEAD_FRAMES) 
            {
                time            = BOB_START;
                g_player2State  = BOBBING;
                g_player2health = 100;
                bHitGround      = FALSE;

                // Recalculate the power bars
                RecalcPowerBars(g_player1health, g_player2health);
            }
            // Record the new animation time
            g_player2AnimArgs.time = time;

            // Force a camera position update
            PositionCamera();
        }
        break;

        case VICTORY :
        {
            // Forward the victory animation time
            g_player2AnimArgs.lpAnimSet->SetTime(time);
            time += (g_victoryDelta * delta);

            if (time > VICTORY_START + NUM_VICTORY_FRAMES) 
            {
                time            = BOB_START;
                g_player2State  = BOBBING;
            }
            
            // Record the new animation time
            g_player2AnimArgs.time = time;

            // Force a camera position update
            PositionCamera();
        }
        break;
    }
}

//----------------------------------------------------------------------
// 
// Function     : CheckInputAndUpdate()
//
// Purpose      : Checks input, updates scene, moves player(s)
//
//----------------------------------------------------------------------

void CheckInputAndUpdate()
{               
    D3DVECTOR player1pos;
    D3DVECTOR player2pos;
    D3DVECTOR camPos;

    // Run intro
    if (g_appState == DOING_INTRO)
    {
            RunIntro();
            return;
    }

    // Transition camera
    if (g_appState == BETWEEN_CAM_VIEWS)
    {
            TransitionCamera();
            return;
    }

    // Get the players positions
    g_lpPlayer1->GetPosition(g_lpScene, &player1pos);   
    g_lpPlayer2->GetPosition(g_lpScene, &player2pos);

    // Get the camera's position
    g_lpCamera->GetPosition(g_lpScene, &camPos);

    // Calculate distance between players
    D3DVALUE curDist = player2pos.z - player1pos.z;

    // Move player forward
    if ((IsKeyDown(PLAYER_MOVE_FORWARD)) && (g_player1State != VICTORY) && (g_player1State != DEAD))
    {
            // Make sure the player can only move so close to the opponent
            if (curDist > MIN_DIST_TO_OPPONENT)
            {
                    // Move the player
                    g_lpPlayer1->SetPosition(g_lpScene, player1pos.x, player1pos.y, player1pos.z + MOVE_NORMAL);

                    // Force a camera position update
                    PositionCamera();

                    // Play a servo sound
                    PlaySoundDS(SERVO_UP_3,player1pos);
                    
                    // Play a walk sound
                    PlaySoundDS(PLAYER1_WALK,player1pos);
            }
    }

    // Move player backward
    if ((IsKeyDown(PLAYER_MOVE_BACKWARD)) && (g_player1State != VICTORY) && (g_player1State != DEAD))
    {
            // Make sure the player can't run off the arena
            if (player1pos.z > EDGE_LEFT)
            {
                    // Move the player
                    g_lpPlayer1->SetPosition(g_lpScene, player1pos.x, player1pos.y, player1pos.z - MOVE_NORMAL);
                    
                    // Force a camera position update
                    PositionCamera();

                    // Play a servo sound
                    PlaySoundDS(SERVO_UP_3,player1pos);

                    // Play a walk sound
                    PlaySoundDS(PLAYER1_WALK,player1pos);
            }
    }

    // Initiate a player attack
    if ((!g_bPlayer1Attacking) && (!g_bPlayer1Blocking) && (IsKeyDown(PLAYER_ATTACK)))
    {
            if ((g_player1State != PUNCHING) && (g_player1State != DEAD) && (g_player1State != VICTORY))
            {
                    // Set the player state to punching
                    g_player1State = PUNCHING;
                    
                    // Set up the correct time for the animation
                    g_player1AnimArgs.time = D3DVAL(PUNCH_START);
                    g_player1AnimArgs.lpAnimSet->SetTime(D3DVAL(PUNCH_START));
                                    
                    g_bPlayer1Attacking = TRUE;
                    
                    // Play a servo sound
                    PlaySoundDS(SERVO_UP_1,player1pos);
            }
    }

    // Reset the attacking flag if the PLAYER_ATTACK key is not pressed anymore
    if ((g_bPlayer1Attacking) && (!IsKeyDown(PLAYER_ATTACK)))
    {
            g_bPlayer1Attacking = FALSE;
    }

    // Initiate a player block
    if ((!g_bPlayer1Blocking) && (!g_bPlayer1Attacking) && (IsKeyDown(PLAYER_BLOCK)))
    {
            if ((g_player1State != BLOCKING) && (g_player1State != DEAD) && (g_player1State != VICTORY))
            {
                    // Set the player state to blocking
                    g_player1State = BLOCKING;
                    
                    // Set up the correct time for the animation
                    g_player1AnimArgs.time = D3DVAL(BLOCK_START);
                    g_player1AnimArgs.lpAnimSet->SetTime(D3DVAL(BLOCK_START));
                            
                    // Don't allow any more blocking
                    g_bPlayer1Blocking = TRUE;
                    
                    // Play a servo sound
                    PlaySoundDS(SERVO_UP_1,player1pos);
            }   
    }

    // Reset the blocking flag if the PLAYER_BLOCK key is no longer held down
    if ((g_bPlayer1Blocking) && (!IsKeyDown(PLAYER_BLOCK)))
    {
            g_bPlayer1Blocking = FALSE;
    }

    // Transition to the BOTH_IN_VIEW camera view
    if ((IsKeyDown(CAM_BOTH_IN_VIEW)) && (g_camState != BOTH_IN_VIEW))
    {
            // Create transition animation
            if (!FAILED(g_lpD3DRM->CreateAnimation(&g_lpAnim)))
            {
                    // Setup the animation options
                    g_lpAnim->SetOptions(D3DRMANIMATION_OPEN | 
                                                             D3DRMANIMATION_LINEARPOSITION | 
                                                             D3DRMANIMATION_POSITION);

                    // Make midway vector between both players, this is what the camera will focus on
                    D3DVECTOR vMidPoint;
                    vMidPoint.x = 0.0f;
                    vMidPoint.y = 0.0f;
                    vMidPoint.z = (player1pos.z + player2pos.z) / D3DVAL(2);
                    
                    // Calculate vector that will keep both players in sight
                    D3DVECTOR vNewCam;
                    vNewCam.x = (float)abs((int)player2pos.z - (int)player1pos.z) + D3DVAL(300);
                    vNewCam.y = camPos.y;
                    vNewCam.z = vMidPoint.z;
                    
                    // Add the keyframes to the animation
                    g_lpAnim->AddPositionKey(D3DVAL(0), camPos.x, camPos.y, camPos.z);
                    g_lpAnim->AddPositionKey(D3DVAL(1), vNewCam.x, vNewCam.y, vNewCam.z);
                    
                    // Setup the initial position
                    g_lpTmp->SetPosition(g_lpScene, vMidPoint.x, vMidPoint.y, vMidPoint.z);
                    
                    // And attach the camera to the animation
                    g_lpAnim->SetFrame(g_lpCamera);

                    g_appState = BETWEEN_CAM_VIEWS;
            }
            else
            {
                    // Create animation failed so just set the camera position
                    g_lpCamera->SetPosition(g_lpScene, D3DVAL(200), D3DVAL(100), player1pos.z + MOVE_NORMAL - D3DVAL(400));
                    g_lpCamera->LookAt(g_lpPlayer2, g_lpScene, D3DRMCONSTRAIN_Z);               
                    PositionCamera();                   
            }

            g_camState = BOTH_IN_VIEW;
    }
    
    // Transition to the OVER_SHOULDER camera view
    if ((IsKeyDown(CAM_OVER_THE_SHOULDER)) && (g_camState != OVER_SHOULDER))
    {
        if (!FAILED(g_lpD3DRM->CreateAnimation(&g_lpAnim)))
        {
            // Setup the animation options
            g_lpAnim->SetOptions(D3DRMANIMATION_OPEN | 
                                 D3DRMANIMATION_LINEARPOSITION | 
                                 D3DRMANIMATION_POSITION);

            // Add the keyframes to the animation                       
            g_lpAnim->AddPositionKey(D3DVAL(0), camPos.x, camPos.y, camPos.z);
            g_lpAnim->AddPositionKey(D3DVAL(1), D3DVAL(200), D3DVAL(100), player1pos.z - D3DVAL(300));
            
            // Setup the initial position
            g_lpTmp->SetPosition(g_lpScene, player2pos.x, player2pos.y, player2pos.z);
            
            // And attach the camera to the animation
            g_lpAnim->SetFrame(g_lpCamera);

            g_appState = BETWEEN_CAM_VIEWS;
        }
        else
        {
            // Create animation failed so just set the camera position
            PositionCamera();
        }
                                
        g_camState = OVER_SHOULDER;
    }

    // Transition to the PILOT_VIEW camera view
    if ((IsKeyDown(CAM_PILOT)) && (g_camState != PILOT_VIEW))
    {
        PositionCamera();
        g_camState = PILOT_VIEW;
    }

    // Update the opponent
    UpdateOpponent();

    // Update any debris in the world
    UpdateDebris();
}

//----------------------------------------------------------------------
// 
// Function     : UpdateOpponent()
//
// Purpose      : Updates opponent
//
//----------------------------------------------------------------------

void UpdateOpponent()
{
    D3DVECTOR player1pos;
    D3DVECTOR player2pos;       

    if (g_player2State != BOBBING) return;

    // Random value to determine what the opponent should do based upon its state
    int r = rand() % 100;

    // Get the players positions
    g_lpPlayer1->GetPosition(g_lpScene, &player1pos);   
    g_lpPlayer2->GetPosition(g_lpScene, &player2pos);

    // Calculate distance betweens players
    D3DVALUE curDist = player2pos.z - player1pos.z;
    
    // There is always a chance to block the player
    if ((r < 15) && (g_player1State == PUNCHING) && (g_player2State == BOBBING))
    {
        // Set the opponents state to BLOCKING ans start the animation
        g_player2State = BLOCKING;
        g_player2AnimArgs.time = BLOCK_START;
        g_player2AnimArgs.lpAnimSet->SetTime(BLOCK_START);
        
        // Play a servo sound
        PlaySoundDS(SERVO_UP_2,player2pos);
        return;
    }

    switch (g_oppState)
    {
        case DEFENSIVE:
        {                       
            // Decide whether to move opponent backwards
            if (r < 25)
            {
                // Move the opponent backwards
                g_lpPlayer2->SetPosition(g_lpScene, player2pos.x, player2pos.y, player2pos.z + MOVE_NORMAL);
                
                // Play a walk sound
                PlaySoundDS(PLAYER2_WALK,player2pos);
                
                // Play a servo sound
                PlaySoundDS(SERVO_DOWN_3,player2pos);
            }
            PositionCamera();                   

            // Decide whether to go from DEFENSIVE to cautious
            if (r < 10) g_oppState = CAUTIOUS;
        }
        break;

        case CAUTIOUS:
        {
            // Decide whether to go from CAUTIOUS to AGGRESSIVE
            if (r < 5)
            {
                // Make the opponent become aggresive
                g_oppState = AGGRESSIVE;
            }
        }
        break;

        case AGGRESSIVE:
        {                       
            // Decide whether to move the opponent towards the player
            if (r < 50)
            {
                // Move the opponent towards the player
                if (curDist > MIN_DIST_TO_OPPONENT)
                {
                    g_lpPlayer2->SetPosition(g_lpScene, player2pos.x, player2pos.y, player2pos.z - MOVE_NORMAL);
                    PositionCamera();

                    // Play a walk sound
                    PlaySoundDS(PLAYER2_WALK,player2pos);
                    
                    // Play a servo sound
                    PlaySoundDS(SERVO_DOWN_3,player2pos);                          
                }
            }

            // Decide whether or not to attack the player
            if ((r < 15) && (g_player2State == BOBBING) && 
                (g_player1State != DEAD) && (curDist < MIN_DIST_TO_OPPONENT + D3DVAL(50)))
            {
                // Set the opponent's state to PUNCHING
                g_player2State = PUNCHING;
                g_player2AnimArgs.time = PUNCH_START;
                g_player2AnimArgs.lpAnimSet->SetTime(PUNCH_START);
                
                // Play a servo sound
                PlaySoundDS(SERVO_UP_2,player2pos);
            }

            // Decide whether or not to move the opponent backwards out of the way if the player
            // is punching
            if ((g_player1State == PUNCHING) && (r > 50) && (g_player2State == BOBBING) && (curDist < MIN_DIST_TO_OPPONENT + 50))
            {
                // Move the opponent out of the way, making sure its still in the arena
                if (player2pos.z < EDGE_RIGHT) 
                {
                    g_lpPlayer2->SetPosition(g_lpScene, player2pos.x, player2pos.y, player2pos.z + D3DVAL(5));
                    
                    // Play a servo sound
                    PlaySoundDS(SERVO_DOWN_3,player1pos);
                }
            }
        }
        break;
    }
}

//----------------------------------------------------------------------
// 
// Function     : RunIntro()
//
// Purpose      : Moves camera along path
//
//----------------------------------------------------------------------

void RunIntro()
{
    static D3DVALUE time = D3DVAL(0.0f);
	D3DVECTOR d3dvPos;			// D3DVECTOR used for 3D position of sound
	d3dvPos.x = D3DVAL(0);		// set the sound at (0,0,0)..
	d3dvPos.y = D3DVAL(0);
	d3dvPos.z = D3DVAL(0);

    // Play the intro sound
    if (time == D3DVAL(0.0f))
    {
        PlaySoundDS(INTRO,d3dvPos);
        PlaySoundDS(CROWD_LOOP,d3dvPos, DSBPLAY_LOOPING);
                SetTimer(NULL,NULL,10000,(TIMERPROC)PlayRandomWave);
    }
    
    // Foward the intro animation
    time += D3DVAL(0.04);

    // Set the animation time
    g_lpAnim->SetTime(time);
    
    // Always look at the origin of the g_lpScene frame
    g_lpCamera->LookAt(g_lpTmp, g_lpScene, D3DRMCONSTRAIN_Z);
    
    // If time has exceeded 1.0 the intro is done, and we can start the demo
    if (time >= D3DVAL(1.0f))
    {
        g_appState = PLAYING_DEMO;
        g_lpAnim->Release();
        g_lpAnim = NULL;
        PositionCamera();
    }
}

//----------------------------------------------------------------------
// 
// Function     : PostionCamera()
//
// Purpose      : Positions camera based upon camera state
//
//----------------------------------------------------------------------

void PositionCamera()
{       
    D3DVECTOR player1pos;
    D3DVECTOR player2pos;
    D3DVECTOR camPos;

    // Don't position the camera if we are transitioning between camera views
    if (g_appState == BETWEEN_CAM_VIEWS) return;

    // Get the players positions
    g_lpPlayer1->GetPosition(g_lpScene, &player1pos);   
    g_lpPlayer2->GetPosition(g_lpScene, &player2pos);

    // Get the camera's position
    g_lpCamera->GetPosition(g_lpScene, &camPos);

    switch (g_camState)
    {
        case OVER_SHOULDER:
        {
            // Position the camera such that it looks over the shoulder of the player and
            // keeps the opponent in view
            g_lpCamera->SetPosition(g_lpScene, camPos.x, camPos.y, D3DVAL(player1pos.z) + MOVE_NORMAL - 300);                   
            g_lpCamera->LookAt(g_lpPlayer2, g_lpScene, D3DRMCONSTRAIN_Z);
	    if (g_lpDs3dListener)
	    {
                // Set the listener position to where the camera is
		g_lpDs3dListener->SetPosition(camPos.x, camPos.y, D3DVAL(player1pos.z) + MOVE_NORMAL - 300,DS3D_DEFERRED);
		// Change listener's orientation vector
		g_lpDs3dListener->SetOrientation(D3DVAL(0),D3DVAL(0),D3DVAL(1),D3DVAL(0),D3DVAL(1),D3DVAL(0),DS3D_DEFERRED);
	    }
        }
        break;

        case BOTH_IN_VIEW:
        {
            // Position the camera such that it looks at both players all the time

            // Make midway point, this is what the camera will focus on
            D3DVECTOR vMidPoint;
            vMidPoint.x = 0.0f;
            vMidPoint.y = 0.0f;
            vMidPoint.z = (player1pos.z + player2pos.z) / D3DVAL(2);
            
            // Calculate vector that will keep both players in sight
            D3DVECTOR vNewCam;
            vNewCam.x = (float)abs((int)player2pos.z - (int)player1pos.z) + D3DVAL(300);
            vNewCam.y = camPos.y;
            vNewCam.z = vMidPoint.z;

            g_lpCamera->SetPosition(g_lpScene, vNewCam.x, vNewCam.y, vNewCam.z);
                            
            g_lpTmp->SetPosition(g_lpScene, vMidPoint.x, vMidPoint.y, vMidPoint.z);
            g_lpCamera->LookAt(g_lpTmp, g_lpScene, D3DRMCONSTRAIN_Z);
	    if (g_lpDs3dListener)
	    {
                // Set the listener position to where the camera is
		g_lpDs3dListener->SetPosition(vNewCam.x, vNewCam.y, vNewCam.z,DS3D_DEFERRED);
		// Change listener's orientation vector
		g_lpDs3dListener->SetOrientation(-D3DVAL(1),D3DVAL(0),D3DVAL(0),D3DVAL(0),D3DVAL(1),D3DVAL(0),DS3D_DEFERRED);
	    }
        }
        break;

        case PILOT_VIEW:
        {                                               
            // Position the camera such that it looks through the eyes of the player
            // and fixes on the origin of the head frame of the opponent

            g_lpCamera->SetPosition(g_lpPlayer1HeadFrame, D3DVAL(0), D3DVAL(-10), D3DVAL(0));
            g_lpTmp->SetPosition(g_lpPlayer2HeadFrame, D3DVAL(0), D3DVAL(-10), D3DVAL(0));
            g_lpCamera->LookAt(g_lpTmp, g_lpScene, D3DRMCONSTRAIN_Z);
	    if (g_lpDs3dListener)
	    {
                // Set the listener position to where the camera is
		g_lpDs3dListener->SetPosition(player1pos.x, D3DVAL(0), player1pos.z,DS3D_DEFERRED);
		// Change listener's orientation vector
		g_lpDs3dListener->SetOrientation(D3DVAL(0),D3DVAL(0),D3DVAL(1),D3DVAL(0),D3DVAL(1),D3DVAL(0),DS3D_DEFERRED);
	    }
        }
        break;
    }
	// Commit the changes to the listener's orientation and position..
	if (g_lpDs3dListener)
	    g_lpDs3dListener->CommitDeferredSettings();
}

//----------------------------------------------------------------------
// 
// Function     : TransitionCamera()
//
// Purpose      : Positions camera based upon camera state
//
//----------------------------------------------------------------------

void TransitionCamera()
{
    static D3DVALUE time = D3DVAL(0.0f);

    // Forward the transition animation time
    time += D3DVAL(0.04);

    // Set the time for the transitional animation
    g_lpAnim->SetTime(time);

    // Look at the g_lpScene frame
    g_lpCamera->LookAt(g_lpTmp, g_lpScene, D3DRMCONSTRAIN_Z);

    // If the animation has ended, run the demo
    if (time >= D3DVAL(1.0f))
    {
        g_appState = PLAYING_DEMO;
        g_lpAnim->Release();
        g_lpAnim = NULL;
        time = D3DVAL(0);
        PositionCamera();               
    }

    // Update debris so any debris in the scene doesn't just sit there doing nothing
    UpdateDebris();
}

//----------------------------------------------------------------------
// 
// Function     : AddDebris()
//
// Purpose      : Adds some debris to the scene
//
//----------------------------------------------------------------------

void AddDebris(D3DVECTOR vOrg, D3DVECTOR vVel, LPDIRECT3DRMMESHBUILDER pDebris)
{
    // vOrg is the origin of the debris, find first open spot and add 5 bits of debris
    int count = 0;

    for (int i = 0; i < NUM_DEBRIS; i ++)
    {
        // Find some debris that is not in use yet
        if (!g_debris[i].m_bInUse)
        {
            // Add some debris 
            g_debris[i].m_pFrame->AddVisual(pDebris);
            g_debris[i].m_pFrame->SetPosition(g_lpScene, vOrg.x, vOrg.y, vOrg.z);
            g_debris[i].m_pFrame->SetRotation(g_lpScene, D3DVAL(0.5), D3DVAL(0.5), D3DVAL(0.5), D3DVAL(0.5));
            g_debris[i].m_life = 0;

            // Setup velocity and acceleration
            g_debris[i].m_vel.x = D3DVAL(-10 + (rand() % 20)) + vVel.x;
            g_debris[i].m_vel.y = D3DVAL(8) + D3DVAL(rand() % 10) + vVel.y;
            g_debris[i].m_vel.z = D3DVAL(-10 + (rand() % 20)) + vVel.z;

            g_debris[i].m_acc.x = D3DVAL(0);
            g_debris[i].m_acc.y = D3DVAL(-2);
            g_debris[i].m_acc.z = D3DVAL(0);                    

            // This piece of debris is now in use
            g_debris[i].m_bInUse = TRUE;
            g_debris[i].m_pMeshBuilder = pDebris;
            
            count ++;                   
        }

        // Return if we've added NUM_HIT_DEBRIS bits of debris
        if (count == NUM_HIT_DEBRIS) return;
    }   
}

//----------------------------------------------------------------------
// 
// Function     : UpdateDebris()
//
// Purpose      : Updates debris
//
//----------------------------------------------------------------------

void UpdateDebris()
{
    D3DVECTOR vPos;

    // Go through the array of debris and update any debris that is in use

    for (int i = 0; i < NUM_DEBRIS; i ++)
    {
        if (g_debris[i].m_bInUse)
        {
            // If the debris's life has not yet expired
            if (g_debris[i].m_life < DEBRIS_LIFE)
            {
                // Move the debris
                g_debris[i].m_pFrame->GetPosition(g_lpScene, &vPos);
                
                g_debris[i].m_vel.x += g_debris[i].m_acc.x;
                g_debris[i].m_vel.y += g_debris[i].m_acc.y;
                g_debris[i].m_vel.z += g_debris[i].m_acc.z;

                vPos.x += g_debris[i].m_vel.x;
                vPos.y += g_debris[i].m_vel.y;
                vPos.z += g_debris[i].m_vel.z;

                // Check to see whether the debris is below the floor
                if (vPos.y < D3DVAL(-60))
                {
                        // Bounce the debris
                        vPos.y = D3DVAL(-60);
                        g_debris[i].m_vel.y = -g_debris[i].m_vel.y / D3DVAL(1.5);
                }

                // Update the position of the debris
                g_debris[i].m_pFrame->SetPosition(g_lpScene, vPos.x, vPos.y, vPos.z);
            }
            else
            {
                // Remove the debris from the world
                g_debris[i].m_pFrame->DeleteVisual(g_debris[i].m_pMeshBuilder);
                g_debris[i].m_bInUse = FALSE;
            }

            // Age the debris
            g_debris[i].m_life ++;
        }
    }
}

