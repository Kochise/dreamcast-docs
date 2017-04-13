Demonstration of the Font Functions


SUMMARY
=======

The TTFONTS sample is an easy-to-use, powerful utility that allows you to 
explore the font system. There is a toolbar on top of the main frame window 
with buttons that allow the following actions:

  - Enumerating all of the fonts installed for the display.
  - Getting TEXTMETRIC & OUTLINETEXTMETRIC information.
  - Creating a font based on an arbitrary LOGFONT structure.
  - Getting "font data" by using the GetFontData function.
  - Enumerating all of the fonts available to the default printer.

MORE INFORMATION
================

This sample is designed to provide the user with an easy interface to the 
function calls related to the font system. It will not protect against 
meaningless values, nor will it hide system oddities. Most of the buttons 
on the toolbar are self explanatory and represent a single system function.

Pressing the EnumFonts button shows all of the face names, listed 
horizontally, and each of the fonts within that face name, listed 
vertically. TrueType fonts are marked with a small colored TT bitmap. Fonts 
that have the DEVICE_FONTTYPE bit are marked with a small bitmap image of a 
printer. When the enumeration windows are showing, you can click the left 
mouse button to copy the information about a selected font into the LOGFONT 
and TEXTMETRIC dialog boxes. You can dismiss this window without changing 
the dialog boxes by clicking the right mouse button or typing any character.

The Display window is able to operate in any one of three modes. These are 
listed in the Display menu. The first just writes Hello in the middle of the 
screen and grids the background. This is useful when utilizing the 
lfEscapement and lfOrientation fields of the LOGFONT structure. The second 
mode writes all of the glyphs between the tmFirstChar and tmLastChar values 
stored in the TEXTMETRIC structure. The final mode is used only for true 
type fonts. It calls GetFontData, finds the cmap table, and displays glyphs 
from the different ranges in this table. Use the horizontal scroll bar in 
the display window to step through the ranges.
