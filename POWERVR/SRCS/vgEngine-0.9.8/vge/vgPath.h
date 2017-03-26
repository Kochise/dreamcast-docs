//
// C++ Interface: vgpath
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "agg_basics.h"
#include "agg_path_storage.h"

class Rasterizer;

typedef agg::path_storage	PathStorage;

class vgPath
{
	public:
	    // A container to store vertices with their flags. 
		// A path consists of a number of contours separated with "move_to" 
		// commands. The path storage can keep and maintain more than one
		// path. 
		// To navigate to the beginning of a particular path, use rewind(path_id);
		// Where path_id is what start_new_path() returns. So, when you call
		// start_new_path() you need to store its return value somewhere else
		// to navigate to the path afterwards.
		//
		// See also: vertex_source concept
		PathStorage path;
		
		vgPath();	//throws bad_alloc
		~vgPath();
		
		unsigned			getNumCoordinates() const { return path.total_vertices(); }
		/// Clear a path;
		void				clear() { path.free_all(); }
		/// Appends a path.
		unsigned			append(vgPath* srcPath);	//throws bad_alloc
		/// Appends a transformed copy of the source path.
		unsigned			transform(vgPath* srcPath, const VGMatrix& matrix);	//throws bad_alloc
		
        void move_to(VGdouble x, VGdouble y) { path.move_to(x,y); }
        void move_rel(VGdouble dx, VGdouble dy) { path.move_rel(dx,dy); }

        void line_to(VGdouble x, VGdouble y) { path.line_to(x,y); }
        void line_rel(VGdouble dx, VGdouble dy) { path.line_rel(dx,dy); }

        void hline_to(VGdouble x) { path.hline_to(x); }
        void hline_rel(VGdouble dx) { path.hline_rel(dx); }

        void vline_to(VGdouble y) { path.vline_to(y); }
        void vline_rel(VGdouble dy) { path.vline_rel(dy); }

        void curve3(VGdouble x_ctrl, VGdouble y_ctrl, 
                    VGdouble x_to,   VGdouble y_to) { path.curve3(x_ctrl, y_ctrl, x_to, y_to) ; }

        void curve3_rel(VGdouble dx_ctrl, VGdouble dy_ctrl, 
                        VGdouble dx_to,   VGdouble dy_to) { path.curve3_rel(dx_ctrl, dy_ctrl, dx_to, dy_to) ; }

        void curve3(VGdouble x_to, VGdouble y_to) { path.curve3(x_to,y_to) ; }

        void curve3_rel(VGdouble dx_to, VGdouble dy_to) { path.curve3_rel(dx_to,dy_to); }

        void curve4(VGdouble x_ctrl1, VGdouble y_ctrl1, 
                    VGdouble x_ctrl2, VGdouble y_ctrl2, 
                    VGdouble x_to,    VGdouble y_to) { path.curve4(x_ctrl1, y_ctrl1, x_ctrl2, y_ctrl2, x_to, y_to); }

        void curve4_rel(VGdouble dx_ctrl1, VGdouble dy_ctrl1, 
                        VGdouble dx_ctrl2, VGdouble dy_ctrl2, 
                        VGdouble dx_to,    VGdouble dy_to) { path.curve4_rel(dx_ctrl1, dy_ctrl1, dx_ctrl2, dy_ctrl2, dx_to, dy_to); }

        void curve4(VGdouble x_ctrl2, VGdouble y_ctrl2, 
                    VGdouble x_to,    VGdouble y_to) { path.curve4(x_ctrl2, y_ctrl2, x_to, y_to); }

        void curve4_rel(VGdouble x_ctrl2, VGdouble y_ctrl2, 
                        VGdouble x_to,    VGdouble y_to) { path.curve4_rel(x_ctrl2, y_ctrl2, x_to, y_to); }


		void end_poly(unsigned flags = agg::path_flags_close) { path.end_poly(flags); }
        void close_polygon(unsigned flags = agg::path_flags_none) { path.close_polygon(flags); }
		
		// ------------- util ----------------------------------------------------------------------
		
		void line(VGdouble x0, VGdouble y0, VGdouble x1, VGdouble y1);
		void arc(VGdouble x,  VGdouble y, VGdouble rx, VGdouble ry, VGdouble start, VGdouble end, VGUArcType arcType, bool ccw);
		void ellipse(VGdouble x,  VGdouble y, VGdouble rx, VGdouble ry);
		void rectangle(VGdouble x,  VGdouble y, VGdouble w, VGdouble h);
		void roundRectangle(VGdouble x,  VGdouble y, VGdouble w, VGdouble h, VGdouble r);
		void polygon(VGPathDatatype dataType, const void* points, VGint count, VGboolean closed);
};

