
Playing Card Sample Control
===========================
This sample ActiveX Control implements a standard playing card, with the
ability to show the standard 52 card deck, two jokers, and 13 different
card backs.  This control is a Windowless control, which uses transparency 
to create the missing card corner effect.  

Building
--------
To build card.ocx, the FrameWrk sample must first be built. First run 
\inetsdk\setenv.bat to be sure the ActiveX SDK include, bin, and lib
directories are included (first) in your environment. Run the 'nmake'
to build a debug version (built to the Debug subdirectory) or
'nmake nodebug=1' to build a retail (nodebug) directory into the
Retail subdirectory.

After building the FrameWrk library you can build the Card
control by running 'nmake' or 'nmake nodebug=1'.

Sample: ActiveX Video Poker
---------------------------
Included is a sample application which uses card.ocx: ActiveX
Video Poker.  To run this application, open poker\poker.htm.
This application also depends on the ielabel control and 
ietimer control.

To debug and work with this example, open poker\main.htm.  This
file can be used outside of the framesets provided by poker.htm.

Sample: ActiveX Solitaire
-------------------------
Included is a sample application which uses card.ocx: ActiveX
Solitaire.  To run this application, open solitair\sol.htm.
This application also depends on the ietimer control and the
HTML Layout Control.

Using the Card Control
----------------------
The Card control is itself controlled through 3 properties:

	Suite		-- Enum:  0 = Invisible (card not drawn)
				  1 = Clubs
				  2 = Spades
				  3 = Hearts
				  4 = Diamonds
				  -1 to -13 = Card Backs

	Number		-- Enum:  1 = Ace
				  2 to 10 = Number Cards
				  11 = Jack
				  12 = Queen
				  13 = King
				  14 = Joker

	Invert		-- Boolean: controls drawing the card inverted,
	  			    to indicate selection

	CardAlignment   -- Enum:  0 = Top Left
				  1 = Top Center
				  2 = Top Right
				  3 = Center Left
				  4 = Center
				  5 = Center Right
				  6 = Bottom Left
				  7 = Bottom Center
				  8 = Bottom Right
				  9 = Stretch

By default the card starts in the transparent state.  Setting the 
Suite to any value other than zero will draw the card.

A property page is also included with the control, which can simply 
picking the right property values.

The card control will also fire the following events:

	Click		-- Mouse Click
	DblClick	-- Mouse Double Click
	MouseDown	-- Mouse down
	MouseUp		-- Mouse up
	MouseMove	-- Mouse move

How it Works
------------
To keep the size of the control to a minimum, to minimize internet download
time, each card is created from the ground up.  The only resources included
in the control are the basic symbols needed to create the cards, one half
of each face cards center, and the card backs.  Where possible, monochrome
and compressed bitmaps are used.

The card control caches all card images after they have been created the
first time.  For games such as Solitaire in which the cards move
across one another, and most of the cards in a deck are displayed on the 
screen at the same time, caching all the cards of course yields the best 
animations.  To keep memory usage low, 4-bit DIB bitmaps are used to
store the cached images.

This control is a Windowless control, which uses transparency to create the 
missing card corner effect.  When used with Internet Explorer, the control
is Windowed, and the ambient background color is used to fill in the corners.
When used in the HTML Layout Control, or another Windowless control host,
the corners are transparent and the card or background beneath can be seen.

