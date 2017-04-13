Basic demonstration of DirectDraw page flipping.  Renders a spinning cube
to the back buffer, then flips.

App Note:
The palette chosen for 8bpp is Red, Green and Blue wash. There isn't enough
room for Yellow, Orange, and Purple. The code in the sample app itself
decides to map Yellow, Orange and Purple to Red. If you specify "DrawWithGDI"
with the Cube menu, then Yellow/Orange/Purple are drawn without very many
shades (because it's using system colors and there are only a few shades
of yellow/orange/purple are available). 

