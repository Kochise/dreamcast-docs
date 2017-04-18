//-------------------------------------------------------------------------
// Readme.txt
//-------------------------------------------------------------------------
// Spruuids: A sample ActiveX Scripting host, which hosts VB Script.
//-------------------------------------------------------------------------
// (C) Copyright 1992-1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//-------------------------------------------------------------------------

FILES SUPPLIED
	EXTERNAL HEADER FILES
		ActivScp.h  -- ActiveX Scripting header file, used by Game.cpp
		VBSGuids.h  -- Defines CLSID for VB Script, used by Game.cpp
		CompMgr.h   -- Component Manager interfaces, used by App.cpp, MsgLoop.cpp
	PROGRAM FILES
		App.cpp, App.h
            -- Implements Main App window via a dialog.  CApp is responsible
               for creating the CMsgLoop object, and CGame object.
		MsgLoop.cpp, MsgLoop.h
            -- Implements .exe's message loop via IOleComponentManager.  CApp
               acts as a client to the ComponentManager, implementing
               IOleComponent.
		OleAuto.cpp, OleAuto.h
            -- Small framework for creating OLE Automation objects which have
               dual interfaces.
		Game.cpp, Game.h
            -- Orchestrates the show, responsible for creating and coordinating
               CScore, CDisplay (from Spr.cpp), and CSpriteClass's.  Handles
               high-level game behaviors, such as starting and ending games,
               the menus, and creating, loading, and managing VB Script through
               ActiveX Scripting.
		GameOA.cpp
            -- OLE Automation implementation for "Game" object in object model.
		Score.cpp, Score.h
            -- Tracks score, level, # ships left.
		Spr.cpp, Spr.h
            -- Core "sprite" engine, implementing CDisplay, CSpriteClass, and
               CSprite.
            -- CDisplay implements the display surface on which the
               sprites are drawn, and handles drawing the sprites, updating
               their positions on timer ticks, and tracking collisions between
               the sprites.
            -- CSpriteClass implements a set of functionality shared between
               common kinds of sprites, such as the starting image used, how
               sprites of this class interact with the border, etc.
            -- CSprite implements a "sprite" which basically a repository for
               position, velocity, image, etc.
		SprOA.cpp
            -- Implements the "SpriteClass" and "Sprite" OLE Automation
               interfaces for the CSpriteClass and CSprite classes,
               respectively.
		Guids.cpp, Guids.h
            -- Simple file to get all necessary GUIDs to the linker.
		Helpers.h
            -- Implements some obligatory ANSI/Unicode helpers.
		Main.h
            -- Main include file included by everyone.
		SpruuidP.Pix, SpruuidP.hh, SpruuidP.h
            -- Helper files which tells the sprite engine about the graphics
               found within the main sprite bitmap, Spruuids.bmp
		DispIDs.h
            -- Defines the DISPIDs used for events.
		Spruuids.odl
            -- Declares the object model for the Spruuids.exe application.
    BITMAPS
        Spruuids.bmp  -- Contains all of the interesting images.
        Ship.bmp      -- Contains the image used to display the # ships left.
        Plus.bmp      -- Graphics used to display a "+" when not enough room
                         to display # ships left.
	SAMPLE SPRITE.EXE INPUT FILES
		Game1.txt     -- Simple samples illustrating how to use some
		Game2.txt        primitives from the Game object model.
		Game3.txt
		GameFull.txt  -- Complete fun-to-play game.

    CLASSES IN SPRUUIDS' IMPLEMENTATION
	    CApp implements
            IUnknown
            IDispatch Using COleAuto
		    SpruuidsApp
            IOleComponent
	    CGame implements
            IUnknown
            IDispatch Using COleAuto
		    Game
		    IActiveScriptSite
            IProvideClassInfo
            IProvideClassInfo2
            IConnectionPointContainer
            IConnectionPoint via an embedded class
	    CMsgLoop implements
		    IOleComponentManager
	    CScore
	    CDisplay
	    CSpriteClass implements
            IUnknown
            IDispatch Using COleAuto
		    SpriteClass
            IProvideClassInfo
            IProvideClassInfo2
            IConnectionPointContainer
            IConnectionPoint via an embedded class
	    CSprite
            IUnknown
            IDispatch Using COleAuto
		    Sprite

RUNNING SPRUUIDS.EXE
	Command Line:
		Spruuids <VB Script File>
	where
		<VB Script File> is the relative or full path to a VB Script
	file containing the source code which Spruuids is to load and run.  See
	Game*.txt for samples of VB Script programs written against Spruuids.exe.

COMPILING SPRITE.EXE
	Use MkTypLib.exe to compile "Spruuids.odl" into "Spruuids.h" and
        "Spruuids.tlb".  NOTE THAT Spruuids.tlb MUST BE GENERATED BEFORE THE .RC
        FILE CAN BE COMPILED WITH RC.EXE!
	Compile each of the *.cpp files.
	Use RC.exe to compile the "Spruuids.rc" into "Spruuids.res", noting that
		"Spruuids.tlb" must be included as a resource of type "TYPELIB",
		so it must have been created first.
	Link everything togther, and use RC.exe to add the .res to the .exe.

SPRUUIDS' OBJECT MODEL
	Application As SpruuidsApp
        R/O Properties
            Application - Returns the Application object (returns itself).
            Parent - Returns the Application object (returns itself).
            Game - Returns the "Game" object, described below.
        Methods
            Quit() - Causes Spruuids to terminate.

	Game As Game
        R/O Properties
            Application - Returns the Application object.
            Parent - Returns the Application object.
            ShipClass As SpriteClass - Returns the SpriteClass for the ship.
            BubbleClass As SpriteClass - Returns the SpriteClass for bubbles.
            AmmoClass As SpriteClass - Returns the SpriteClass for ammo.
            ExtraClass As SpriteClass - Returns the SpriteClass for extra,
                special effects, or general use.
       R/W Properties
            Caption As String - Sets the caption of the main Spruuids window.
            StatusText As String - Sets the status text of Spruuids.
            Width As Integer - Width, in pixels, of the display area.
            Height As Integer - Height, in pixels, of the display area.
            Paused As Boolean - Sets or clears the paused game.
            Score As Integer - Current score.  Setting this will not compute
                extra ships gained.  Use AddScore() to ensure this calcualtion.
            Level As Integer - Current level.
            ShipCount As Integer - Current number of ships left.
            ScoreFirst1Up As Integer - Score at which the first extra ship is
                awarded.
            ScoreSecond1Up As Integer - Score at which the second extra ship
                is awarded.
            DScoreNext1Up As Integer - Delta score for each extra ship award
                after the second.
            ShipsStart As Integer - Number of ships to start game with.
            Tag As Variant - General storage for the user.
        Methods
            StartGame() - Starts a new game, propting the user first, if a
                game is already in progress.
            EndGame() - Ends the current game.
            RemoveAllSprites() - Destroys all sprites.
            NextLevel() - Increments the Level number, updating the level
                display
            Refresh() - Forces the display to be refreshed.
            AddScore(amt As Integer) - Adds the given amount to the score,
                rounding up to zero, if necessary.  Also computes to see
                if an extra ship should be awarded.
            StdBorderBounce(s As Sprite, brd As Integer) - Ensures that
                the sprite's velocities will cause the sprite to bounce.
            StdBorderWrap(s As Sprite, brd As Integer) - Move the sprite
                to the other edge of the screen.
            StdInitRand(s As Sprite, u As Variant) - Moves the sprite to some
                random location on the display at least u pixels away from
                the center.  Ensures that the sprite does not start out
                overlapping a sprite it would cause a Collide event with.
            StdInitEdge(s As Sprite, u As Variant) - Moves the sprite to some
                random location around the edge of the display.  u is ignored. 
        Events
            NewGame() - Fired when a new game is started.
            NewLevel() - Fired when NextLevel is called.
            NewShip() - Fired when a new ship is awarded.
            Tick() - Fired every timer tick.
            Collide(s1 As Sprite, s2 As Sprite, coll As Integer) - Fired when
                two sprites move so they overlap.  S1 is always the sprite
                with the lower id (ShipClass < BubbleClass < AmmoClass <
                ExtraClass).  Coll is the bit-wise AND of s1.Parent.Collide
                with s2.Parent.Collide.  So with judicious setting of the
                Collide propertis, coll is enough to tell what types of 
                sprites collided, and what s1 and s2 are.  Bit 1 is special
                and is used to indicate that a sprite should generate this
                event when it hits sprites of its own class.
            KeyDown(vk As Integer) - Fired when key is depressed.  vk contains
                the virtual key code, as defined in Windows.h.
            KeyPress(ascii As Integer) - Fired when key is depressed.  ascii
                contains the ascii value of the key pressed.
            KeyUp(vk As Integer) - Fired when key is released.  vk contains
                the virtual key code, as defined in Windows.h.
            MouseMove(x As Integer, y As Integer, keys As Integer, button As
                Integer) - Fired when mouse moves over the play surface of
                Spruuids.  x and y are the pixel location of the mouse relative
                to the upper left corner of the play surface.  keys indicates
                whether the SHIFT key is depressed (bit 1) or the CONTROL key
                is depressed (bit 2).  button indicates which buttons are
                currently depressed (any combination of: 1=left, 2=right,
                4=middle).
            MouseDown(x As Integer, y As Integer, keys As Integer, button As
                Integer) - Fired when the user depresses a mouse button. 
                button indicates which button was depressed (one of: 1=left,
                2=right, 4=middle).
            MouseUp(x As Integer, y As Integer, keys As Integer, button As
                Integer) - Fired when the user releases a mouse button. 
                button indicates which button was released (one of: 1=left,
                2=right, 4=middle).

    SpriteClass Objects
        R/O Properties
            Application - Returns the Application object.
            Parent - Returns the Game object.
            SpriteCount As Integer - The number of existing sprites of
                this kind.
        R/W Properties
            Image As Integer - A number indicating the default graphic
                to be used for sprites of this class.
            Brd As Integer - A bitfield indicating the display borders with
                which sprites of this class are interested in being notified
                (via the Border event) when then touch them.  See Spr.h for
                the definition of this bitfield.
            Collide As Integer - a bitfield used to determine whether to fire
                the Game_Collide event, as described above.
            Friction As Single - Indicates the amount of friction sprites of
                this class should default to.  Values 0<n<1 slow the ship.  The
                value 1 is the same as no friction (default).  Values >1 will
                cause the ship to automatically accelerate.  Values <0, who
                knows?
            Tag As Variant - General storage for the user.
        Methods
            CreateSprite(Left As Integer, Top As Integer, u As Variant) As Sprite
                A function which creates a new instance of a sprite of this
                class, at the given location.  U is passed to the Init event,
                allowing the user to pass information into that event.  This
                function returns a reference to the sprite object created.
        Events
                Init(s As Sprite, u As Variant) - Fired when sprite is first
                    created.  U is the parameter passed to CreateSprite().
                Tick(s As Sprite) - Fired every s.TickEvt timer ticks.
                Border(s As Sprite, brd As Border) - Fired when sprite touches
                    a display border indicated by the Brd property.  Calling
                    s.IgnoreMove() during this event will cause the sprite
                    to return to its position it was at before the move which
                    caused this event.
                Term(s As Sprite) - Called before sprite object is destroyed.
                LastTerm() - Fired when no more sprites of this sprite class
                    exist.

    Sprite Objects
        R/O Properties
            Application - Returns the Application object.
            Parent - Returns the Game object.
            Width As Integer - Width of sprite's graphic in pixels.
            Height As Integer - Height of sprite's graphic in pixels.
        R/W Properties
            Left As Single - Left position in pixels (may be fractional).
            Top As Single - Top position in pixels (may be fractional).
            Vx As Single - Horizontal velocity in pixels per TickMove ticks
                (may be fractional).
            Vy As Single - Vertical velocity in pixels per TickMove ticks
                (may be fractional).
            Ax As Single - Horizontal acceleration in pixels per TickMove ticks
                (may be fractional).
            Ay As Single - Vertical accekeration in pixels per TickMove ticks
                (may be fractional).
            FrictionX As Single - Horizontal friction.  See description of
                Friction for SpriteClass (may be fractional).
            FrictionY As Single - Vertical friction.  See description of
                Friction for SpriteClass (may be fractional).
            Image As Integer - Graphic associated with this sprite.  See
                SpruuidP.pix and SpruuidP.hh for a list of numbers and their
                graphics.
            TickMove As Integer - The number of ticks between times the sprite
                engine move this sprite by Vx and Vy.
            TickEvt As Integer - The number of ticks between SpriteClass_Tick
                events.
            Visible As Boolean - Indicates whether this sprite is visible or
                not.  Invisible sprites never cause Collide events.
            Tag As Variant - General storage for the user.
        Methods
            MoveTo(Left As Single, Top As Single) - Move the sprite to the
                given location.
            MoveBy(Left As Single, Top As Single) - Move the sprite by the
                given amount.
            Remove() - Destroys the sprite.
            Refresh() - Forces the sprite to repaint, if it is visible.
            IgnoreMove() - Called from within the Collide or Border events
                to indicate that the move which caused this sprite to collide
                or touch a border should not be made.

//--- EOF -----------------------------------------------------------------
