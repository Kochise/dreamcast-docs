(NOTE: this file contains extended ASCII and may not appear
       correctly if your font does not support extended ASCII
       characters.  This file will appear correctly in the
       MS-DOS Editor.)

This effect uses palette animation.

Here is how it works:

Imagine a 4x4 display using 4 colors.  We could set the colors
up to look something like this:

   1 2 3 4
   1 2 3 4
   1 2 3 4
   1 2 3 4

Now we can cycle all of the colors in each row to the right. (The
one on the right will wrap-around to the left.)

   4 1 2 3
   4 1 2 3
   4 1 2 3
   4 1 2 3

If we continue this cycling we would get animated lines moving
to the right.  The same can be done to animate the lines going
down. i.e.

   1 1 1 1      4 4 4 4
   2 2 2 2  ->  1 1 1 1
   3 3 3 3  ->  2 2 2 2
   4 4 4 4      3 3 3 3

Now if we expand our palette to 16 color we can combine moving
down and right at the same time.

   Move right:

       1  2  3  4       4  1  2  3
       5  6  7  8  ->   8  5  6  7
       9 10 11 12  ->  12  9 10 11
      13 14 15 16      16 13 14 15

   Move down:

       1  2  3  4      13 14 15 16
       5  6  7  8  ->   1  2  3  4
       9 10 11 12  ->   5  6  7  8
      13 14 15 16       9 10 11 12

   Move right and down:

       1  2  3  4       4  1  2  3      16 13 14 15
       5  6  7  8  ->   8  5  6  7  ->   4  1  2  3
       9 10 11 12  ->  12  9 10 11  ->   8  5  6  7
      13 14 15 16      16 13 14 15      12  9 10 11

Now if you tile these 4x4 blocks end to end and cycle the colors
as above, you get a moving checkerboard.

    
    ²±° ²±° ²±° ²±°       ° ²±° ²±° ²±° ²±      ²±° ²±° ²±° ²±°  
    ±° ²±° ²±° ²±° ²       ²±° ²±° ²±° ²±°      ±° ²±° ²±° ²±° ²
    ° ²±° ²±° ²±° ²±      ²±° ²±° ²±° ²±°       ° ²±° ²±° ²±° ²±
     ²±° ²±° ²±° ²±°  ->  ±° ²±° ²±° ²±° ²  ->   ²±° ²±° ²±° ²±°
    ²±° ²±° ²±° ²±°   ->  ° ²±° ²±° ²±° ²±  ->  ²±° ²±° ²±° ²±°  
    ±° ²±° ²±° ²±° ²       ²±° ²±° ²±° ²±°      ±° ²±° ²±° ²±° ²
    ° ²±° ²±° ²±° ²±      ²±° ²±° ²±° ²±°       ° ²±° ²±° ²±° ²±
     ²±° ²±° ²±° ²±°      ±° ²±° ²±° ²±° ²       ²±° ²±° ²±° ²±° 


Wormhole does the same thing, except it uses 15x15 blocks (225
colors) and instead of tiling the blocks end to end on a flat
plane, it tiles them in 3D converging at the center of the
wormhole.

The following code will generate the 3D wormhole using the 
aforementioned 15x15 grids.

//Do all the work!
//convert r,theta,z to x,y,x to screen x,y
//plot the point
//z=-1.0+(log(2.0*j/DIVS) is the line that sets the math eqn for plot
//Feel free to try other functions!
//Cylindrical coordinates, i.e. z=f(r,theta)

#define STRETCH 25
#define PI      3.14159265358979323846
#define XCENTER 160
#define YCENTER 50
#define DIVS    1200
#define SPOKES  2400

void transarray(void)
	{
	float x,y,z;
	int i,j,color;
	for(j=1;j<DIVS+1;j++)
		for(i=0;i<SPOKES;i++)
			{
			z=-1.0+(log(2.0*j/DIVS));
			x=(320.0*j/DIVS*cos(2*PI*i/SPOKES));
			y=(240.0*j/DIVS*sin(2*PI*i/SPOKES));
			y=y-STRETCH*z;
			x+=XCENTER;
			y+=YCENTER;
			color=((i/8)%15)+15*((j/6)%15)+1;
			if ((x>=0)&&(x<=320)&&(y>=0)&&(y<=200))
				plot((int) x,(int) y,color);
			}
	}

After loading the bitmap to a direct draw surface, all that is
left to do is rotate the colors and you have a wormhole!

