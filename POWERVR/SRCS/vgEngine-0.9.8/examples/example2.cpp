//
// C++ Implementation: example3
//
// Description: Draws the famous 'tiger' picture from OpenVG Reference Implementation (khronos.org)
//
//
// Author: Marian Krivos <nezmar@tutok.sk>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "vgEngine.h"
#include "vgBitmapFile.h"

#include "tiger.h"

/*--------------------------------------------------------------*/

float				pixelScale = 1.f;
float				aspectRatio;
int					initialWidth;
int					initialHeight;
float				mousex, mousey;
int					mouseButton = 0;
int					window;

VGBitmapFile bmp;
VGContext context;

/*--------------------------------------------------------------*/

typedef struct
{
	VGFillRule		m_fillRule;
	VGPaintMode		m_paintMode;
	VGCapStyle		m_capStyle;
	VGJoinStyle		m_joinStyle;
	float			m_miterLimit;
	float			m_strokeWidth;
	unsigned char	m_strokePaint[4];
	unsigned char	m_fillPaint[4];
	VGPath			m_path;
} PathData;

typedef struct
{
	PathData*			m_paths;
	int					m_numPaths;
} PS;

PS* PS_construct(const char* commands, int commandCount, const float* points, int pointCount)
{
	PS* ps = (PS*)malloc(sizeof(PS));
	int p = 0;
	int c = 0;
	int i = 0;
	int paths = 0;
	int maxElements = 0;

	while(c < commandCount)
	{
		int elements, e;
		c += 4;
		p += 8;
		elements = (int)points[p++];
		assert(elements > 0);
		if(elements > maxElements)
			maxElements = elements;
		for(e=0;e<elements;e++)
		{
			switch(commands[c])
			{
			case 'M': p += 2; break;
			case 'L': p += 2; break;
			case 'C': p += 6; break;
			case 'E': break;
			default:
				break;
//				assert(0);		//unknown command
			}
			c++;
		}
		paths++;
	}

	ps->m_numPaths = paths;
	ps->m_paths = (PathData*)malloc(paths * sizeof(PathData));

	i = 0;
	p = 0;
	c = 0;
	while(c < commandCount)
	{
		int elements, startp, e;
		VGPath path;
		int debug = 1;
				
		//fill type
		int paintMode = 0;
		ps->m_paths[i].m_fillRule = VG_NON_ZERO;
		switch( commands[c] )
		{
		case 'N':
			break;
		case 'F':
			ps->m_paths[i].m_fillRule = VG_NON_ZERO;
			paintMode |= VG_FILL_PATH;
			break;
		case 'E':
			ps->m_paths[i].m_fillRule = VG_EVEN_ODD;
			paintMode |= VG_FILL_PATH;
			break;
		default:
			break;
		}
		c++;

		//stroke
		switch( commands[c] )
		{
		case 'N':
			if (debug) printf("FILL ");
			break;
		case 'S':
			paintMode |= VG_STROKE_PATH;
			if (debug) printf("FILL+STROKE ");
			break;
		default:
			break;		//unknown command
		}
		ps->m_paths[i].m_paintMode = (VGPaintMode)paintMode;
		c++;

		//line cap
		switch( commands[c] )
		{
		case 'B':
			ps->m_paths[i].m_capStyle = VG_CAP_BUTT;
			break;
		case 'R':
			ps->m_paths[i].m_capStyle = VG_CAP_ROUND;
			break;
		case 'S':
			ps->m_paths[i].m_capStyle = VG_CAP_SQUARE;
			break;
		default:
			break;
		}
		c++;

		//line join
		switch( commands[c] )
		{
		case 'M':
			ps->m_paths[i].m_joinStyle = VG_JOIN_MITER;
			break;
		case 'R':
			ps->m_paths[i].m_joinStyle = VG_JOIN_ROUND;
			break;
		case 'B':
			ps->m_paths[i].m_joinStyle = VG_JOIN_BEVEL;
			break;
		default:
			break;
		}
		c++;

		//the rest of stroke attributes
		ps->m_paths[i].m_miterLimit = points[p++];
		ps->m_paths[i].m_strokeWidth = points[p++];

		ps->m_paths[i].m_strokePaint[0] = (unsigned char)(points[p++] * 255);
		ps->m_paths[i].m_strokePaint[1] = (unsigned char)(points[p++] * 255);
		ps->m_paths[i].m_strokePaint[2] = (unsigned char)(points[p++] * 255);
		ps->m_paths[i].m_strokePaint[3] = 255;

		ps->m_paths[i].m_fillPaint[0] = (unsigned char)(points[p++] * 255);
		ps->m_paths[i].m_fillPaint[1] = (unsigned char)(points[p++] * 255);
		ps->m_paths[i].m_fillPaint[2] = (unsigned char)(points[p++] * 255);
		ps->m_paths[i].m_fillPaint[3] = 255;

		//read number of elements

		elements = (int)points[p++];
		assert(elements > 0);
		startp = p;
		const float* r = points+startp;
		
		path = ps->m_paths[i].m_path = vgCreatePath();
		
		for(e=0;e<elements;e++)
		{
			switch( commands[c] )
			{
			case 'M':
				if (debug) printf("vgMoveTo(path, %f, %f );\n", r[0], r[1]);  
				vgMoveTo(path, r[0], r[1]);
				p += 2;
				r += 2;
				break;
			case 'L':
				if (debug) printf("vgLineTo(path, %f, %f );\n", r[0], r[1]);
				vgLineTo(path, r[0], r[1]);
				p += 2;
				r += 2;
				break;
			case 'C':
				if (debug) printf("vgCubicTo(path, %f, %f, %f, %f, %f, %f );\n", r[0], r[1], r[2], r[3], r[4], r[5]);
				vgCubicTo(path, r[0], r[1], r[2], r[3], r[4], r[5]);
				r += 6;
				p += 6;
				break;
			case 'E':
				vgClosePath(path);
				if (debug) printf("vgClosePath(path);\n");
				break;
			default:
				break;
			}
			c++;
		}
		i++;
	}
	return ps;
}

void PS_destruct(PS* ps)
{
	int i;
	assert(ps);
	for(i=0;i<ps->m_numPaths;i++)
	{
		vgDestroyPath(ps->m_paths[i].m_path);
	}
	free(ps->m_paths);
	free(ps);
}

void PS_render(PS* ps)
{
	int i;
	assert(ps);
//	vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);

	for(i=0;i<ps->m_numPaths;i++)
	{
		vgFillRule(context, ps->m_paths[i].m_fillRule);
		vgFillColor(context, ps->m_paths[i].m_fillPaint[0], ps->m_paths[i].m_fillPaint[1], ps->m_paths[i].m_fillPaint[2], 255);

		if(ps->m_paths[i].m_paintMode & VG_STROKE_PATH)
		{
			vgLineWidth(context, ps->m_paths[i].m_strokeWidth);
			vgLineCapStyle(context, ps->m_paths[i].m_capStyle);
			vgLineJoinStyle(context, ps->m_paths[i].m_joinStyle);
			vgLineMiter(context, ps->m_paths[i].m_miterLimit);
			vgLineColor(context, ps->m_paths[i].m_strokePaint[0], ps->m_paths[i].m_strokePaint[1], ps->m_paths[i].m_strokePaint[2], 255);
		}

		vgDrawPath(context, ps->m_paths[i].m_path, ps->m_paths[i].m_paintMode);
	}
	assert(vgGetError(context) == VG_NO_ERROR);
}

PS* tiger = NULL;

/*--------------------------------------------------------------*/

int main(void)
{
	aspectRatio = 1; (tigerMaxY - tigerMinY) / (tigerMaxX - tigerMinX);
	initialWidth = 1280;
	initialHeight = 1024;

	bmp = vgCreateBitmapFile(initialWidth,initialHeight);
	context = vgCreateContext( initialWidth, initialHeight, vgGetBitmapFileFormat(bmp), vgGetBitmapFileRawData(bmp) );
	
	tiger = PS_construct(tigerCommands, tigerCommandCount, tigerPoints, tigerPointCount);

	int w = initialWidth;
	int h = initialHeight;
	
	float scale = 1; // w / (tigerMaxX - tigerMinX);

	vgClearColor(context, 255, 255, 255, 255);
	vgClear(context);

	vgLoadIdentity(context);
	vgScale(context, scale, scale);
	vgTranslate(context, -tigerMinX, -tigerMinY + 0.5f * (h / scale - (tigerMaxY - tigerMinY)));

	PS_render(tiger);
	
	vgSaveBitmapFile(bmp, "tiger.bmp");
	
	vgDestroyContext(context);
	vgDestroyBitmapFile( bmp );
	return 0;
}

/*--------------------------------------------------------------*/
