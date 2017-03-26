//
// C++ Implementation: example3
//
// Description: Animation example from Zack Rusin's OpenVG implementation (generate 20 bmp files)
//
//
// Author: Marian Krivos <nezmar@tutok.sk>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "vgEngine.h"
#include "vgBitmapFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

VGdouble gear1Rotation = 35;
VGdouble gear2Rotation = 24;
VGdouble gear3Rotation = 33.5;

VGBitmapFile bmp;
VGContext context;

#define LINEWIDTH 3
#define STROKE_R (26)
#define STROKE_G (191)
#define STROKE_B (26)
#define STROKE_OPACITY (1)

#define WIDTH		640
#define HEIGHT		480

#define NUMPTS 6
VGdouble animpts[NUMPTS * 2];
VGdouble deltas[NUMPTS * 2];

static inline double drand()
{
    return (double)rand()/(double)RAND_MAX;
}

VGPath gearsPath(double inner_radius, double outer_radius, int teeth, double tooth_depth)
{
    int i;
    double r0, r1, r2;
    double angle, da;

    r0 = inner_radius;
    r1 = outer_radius - tooth_depth / 2.0;
    r2 = outer_radius + tooth_depth / 2.0;

    da = 2.0 * M_PI / (VGdouble) teeth / 4.0;

    angle = 0.0;
    
	VGPath path = vgCreatePath();
	
	vgMoveTo(path, r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da));

    for (i = 1; i <= teeth; i++) {
        angle = i * 2.0 * M_PI / (VGdouble)teeth;

        vgLineTo(path, r1 * cos(angle), r1 * sin(angle));
        vgLineTo(path, r2 * cos(angle + da), r2 * sin(angle + da));
        vgLineTo(path, r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da));

        if (i < teeth)
            vgLineTo(path, r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da));
    }

    vgClosePath(path);

    vgMoveTo(path, r0 * cos(angle + 3 * da), r0 * sin(angle + 3 * da));

    for (i = 1; i <= teeth; i++) {
        angle = i * 2.0 * M_PI / (VGdouble) teeth;

        vgLineTo(path, r0 * cos(angle), r0 * sin(angle));
    }

    vgClosePath(path);
    return path;
}

void setup(int w, int h)
{
    int i;

    for (i = 0; i < (NUMPTS * 2); i += 2) {
        animpts[i + 0] = (VGdouble) (drand() * w);
        animpts[i + 1] = (VGdouble) (drand() * h);
        deltas[i + 0] = (VGdouble) (drand() * 6.0 + 4.0);
        deltas[i + 1] = (VGdouble) (drand() * 6.0 + 4.0);
        if (animpts[i + 0] > w / 2.0) {
            deltas[i + 0] = -deltas[i + 0];
        }
        if (animpts[i + 1] > h / 2.0) {
            deltas[i + 1] = -deltas[i + 1];
        }
    }
}

void animate(VGdouble *pts, VGdouble *deltas,
             int index, int limit)
{
    VGdouble newpt = pts[index] + deltas[index];

    if (newpt <= 0) {
        newpt = -newpt;
        deltas[index] = (VGdouble) (drand() * 4.0 + 2.0);
    } else if (newpt >= (VGdouble) limit) {
        newpt = 2.0 * limit - newpt;
        deltas[index] = - (VGdouble) (drand() * 4.0 + 2.0);
    }
    pts[index] = newpt;
}

void animateStep(int w, int h)
{
    int i;

    for (i = 0; i < (NUMPTS * 2); i += 2) {
        animate(animpts, deltas, i + 0, w);
        animate(animpts, deltas, i + 1, h);
    }
}

void pathRender()
{
    VGdouble *ctrlpts = animpts;
    int len = (NUMPTS * 2);
    VGdouble prevx = ctrlpts[len - 2];
    VGdouble prevy = ctrlpts[len - 1];
    VGdouble curx = ctrlpts[0];
    VGdouble cury = ctrlpts[1];
    VGdouble midx = (curx + prevx) / 2.0;
    VGdouble midy = (cury + prevy) / 2.0;

    animateStep(WIDTH,HEIGHT);

    VGPath path2 = vgCreatePath();
    vgMoveTo(path2, midx, midy);

    for (int i = 2; i <= (NUMPTS * 2); i += 2) {
        VGdouble x2, x1 = (midx + curx) / 2.0;
        VGdouble y2, y1 = (midy + cury) / 2.0;

        prevx = curx;
        prevy = cury;
        if (i < (NUMPTS * 2)) {
            curx = ctrlpts[i + 0];
            cury = ctrlpts[i + 1];
        } else {
            curx = ctrlpts[0];
            cury = ctrlpts[1];
        }
        midx = (curx + prevx) / 2.0;
        midy = (cury + prevy) / 2.0;
        x2 = (prevx + midx) / 2.0;
        y2 = (prevy + midy) / 2.0;
        vgCubicTo(path2, x1, y1, x2, y2, midx, midy);
    }
    vgClosePath(path2);

    vgLineColor(context, STROKE_R, STROKE_G, STROKE_B, STROKE_OPACITY);
    vgFillColor(context, 0,0,0,255);

    vgLineWidth(context, LINEWIDTH);

    vgDrawPath(context, path2, VG_STROKE_PATH | VG_FILL_PATH);

    vgDestroyPath(path2);
}

void repaint()
{
	vgClearColor(context, 255,255,255,255 );
	vgClear(context);

    VGPath gear1 = gearsPath(30.0, 120.0, 20, 20.0);
    VGPath gear2 = gearsPath(15.0, 75.0, 12, 20.0);
    VGPath gear3 = gearsPath(20.0, 90.0, 14, 20.0);
    
    vgFillColor(context, 0, 0, 0, 77);

    vgLoadIdentity(context);
    vgTranslate(context, 170, 330);
    vgRotate(context, gear1Rotation);
    vgDrawPath(context, gear1, VG_FILL_PATH);

    vgLoadIdentity(context);
    vgTranslate(context, 369, 330);
    vgRotate(context, gear2Rotation);
    vgDrawPath(context, gear2, VG_FILL_PATH);

    vgLoadIdentity(context);
    vgTranslate(context, 170, 116);
    vgRotate(context, gear3Rotation);
    vgDrawPath(context, gear3, VG_FILL_PATH);

    vgLoadIdentity(context);
    pathRender();

    vgDestroyPath(gear1);
    vgDestroyPath(gear2);
    vgDestroyPath(gear3);

    gear1Rotation += 1;
    gear2Rotation -= (20.0 / 12.0);
    gear3Rotation -= (20.0 / 14.0);
}

int main(int argc, char **argv)
{
	bmp = vgCreateBitmapFile(WIDTH,HEIGHT);
	context = vgCreateContext( WIDTH, HEIGHT, vgGetBitmapFileFormat(bmp), vgGetBitmapFileRawData(bmp) );
	
	setup(WIDTH,HEIGHT);

	for(int i = 0; i< 30; i++)
	{
		char name[32];
		sprintf(name, "shot%02d.bmp", i);
		repaint();
		vgSaveBitmapFile(bmp, name);
	}
	
	vgDestroyContext(context);
	vgDestroyBitmapFile( bmp );
    
	return 0;
}
