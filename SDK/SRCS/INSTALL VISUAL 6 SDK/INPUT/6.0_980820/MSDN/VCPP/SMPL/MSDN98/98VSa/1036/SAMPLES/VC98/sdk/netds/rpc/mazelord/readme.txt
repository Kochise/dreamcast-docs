3-D Maze Game


SUMMARY
=======

The Mazelord sample is a 3-D maze game. The objective is to get as high a
score as possible by zapping other players, and by destroying automated
drones which wander around the maze. When there are no other players,
zapping drones still makes an interesting game in itself.

Mazelord is a networked or non-networked game, depending upon how it is
invoked. In both versions, the player is placed in a room of sanctuary in a
palace. In this room, players may not shoot, and drones cannot hurt players.
Once outside of its 3x3 confines, however, anything goes. Your task is to 
hunt down drones and other players and 'zap' them. Zapped players are 
teleported back to the sanctuary, and zapped drones are teleported to a 
random location in the maze.

MORE INFORMATION
================

Drones appear as gray robots. The number and speed of drones is configurable 
under the Options. A suggestion is 20 drones, speed 2.

The controls to Mazelord are simple:

  - UpArrow:    Move one square forward.
  - LeftArrow:  Turn left, stay in same square.
  - RightArrow: Turn right, stay in same square.
  - DownArrow:  Move one square backwards.
  - Space:      Zap whatever is in line of sight.
  - X:          Exit the game.
  - W:          Whisper something. Anyone within the specified # of squares
                of you can hear your message.
  - S:          Shout something. Same as whisper, except people who are
                farther away can hear your message.

To play, ideally you should be running on a 486 or MIPS with lots of memory
and sound enabled, although the game should work on other systems. Note that 
if you don't have sound, you can still play. The important sounds are 
changed to speaker beeps.

Upon invoking Maze, you have several options:

File Menu

    NewGame:   Starts a new game. Make sure you have configured the game
               under the OPTIONS menu unless you want the defaults and want
               to play Locally rather than over the network.
    PauseGame: Pauses the movement of all drones, but you will be a sitting
               duck if someone shoots at you.
    StopGame:  Resets the game.
    Exit:      Exits the game.

Options Menu

    Networked/Local: Determines whether you will be playing against other
               people on your network domain or not. It's fine to run 
               NETWORK'd when there is no one else playing. Default is 
               LOCAL.
    PlayerSettings: Brings up a dialog with two list boxes. The first shows 
               a list of bitmaps you can choose from to be your character.
               Currently, there is a fish and a smiley face, but the number 
               of choices will be increasing. You can also choose a home 
               maze. This isn't used right now, but soon your home maze will 
               be added to a random part of the existing maze, and you will 
               be able to teleport there at will.
    Drones:    Brings up the drones configuration dialog box. Select the 
               number of drones you want and the speed you want them to go, 
               (# of moves per second). Move algorithm is currently ignored, 
               as all drones use the same semi-random algorithm.

The display consists of the following:

  - A 3-D view of the maze. There are drawing bugs in terms of correctness,
    but unless you're watching for them, they generally don't make a 
    difference. If you have doubts about a wall, you can verify its 
    existence on the overhead view.

  - Overhead view: This view is two squares in each direction from where 
    you are located. You can't see other players on the overhead map, but 
    you can see a small triangle in the center, which indicates which way 
    you are facing. This window is an ABSOLUTE view; up is ALWAYS north 
    on the window, regardless of which direction you're facing in the maze.

  - Text window: This gives information about what is happening in the game,
    such as who you zap or who zaps you, and notification when players enter 
    or leave the game. You will also see messages whispered or shouted by 
    other players if they are close enough.

  - Score window. This shows all players active in your domain if you're
    networked. The display includes the bitmap being used by the player, their
    score, and a directional indicator to show the ABSOLUTE direction you 
    need to go to reach the square that player is in. These are updated 
    every time they change.

Have fun with the game!
