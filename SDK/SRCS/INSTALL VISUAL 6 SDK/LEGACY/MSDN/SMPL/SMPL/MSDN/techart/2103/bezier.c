/***********************************************************************

  MODULE     : BEZIER.C

  PURPOSE    : code for generation of points on a bezier curve

  COMMENTS   : This is public domain code taken from the book Graphics
               Gems, edited by Andrew S. Glassner. It has been modified to 
               work within the context of Win32 for Windows NT

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/
#include    <windows.h>
#include	<stdio.h>
#include	<malloc.h>
#include	<math.h>
#include    "w32pen.h"

/***********************************************************************

  FUNCTION   : NearestPointOnCurve

  PARAMETERS : PVECTOR2D pvTest    -  The user-supplied point  
               PVECTOR2D pvCtrlPts -  Control points of cubic Bezier  

  PURPOSE    : Compute the value of the point on a Bezier curve
               segment closest to some arbitrary user defined point.

  CALLS      : ConvertToBezierForm
               RecursiveSubDivide
			   vVectorSquared
			   vSubtractVectors
			   Bezier

  MESSAGES   : none

  RETURNS    : VECTOR2D - the point on the curve closest to the user
               selected point

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

VECTOR2D NearestPointOnCurve(PVECTOR2D pvTest, PVECTOR2D pvCtrlPts)
{
	PVECTOR2D w;                    //Ctl pts for 5th-degree eqn  
	double	t_candidate[W_DEGREE];	//Possible roots  
	int	n_solutions;	            //Number of roots found  
	double	t;		                //Parameter value of closest pt  
	//
	//Convert problem to 5th-degree Bezier form  
	//
	w = ConvertToBezierForm(pvTest, pvCtrlPts);
	//
	//Find all possible roots of 5th-degree equation  
	//
	n_solutions = RecursiveSubDivide(w, W_DEGREE, t_candidate, 0);
	//free((char *)w);
	free(w);
	//
	//Compare distances of pvTest to all candidates, and to t=0, and t=1  
	//
	{
		double	 dist, new_dist;
		VECTOR2D p;
		VECTOR2D v;
		int	i;
		//
	    //  Check distance to beginning of curve, where t=0  
		//
		dist = vVectorSquared(vSubtractVectors(pvTest, (PVECTOR2D)&pvCtrlPts[0], &v));
		t = 0.0;
		//
	    //Find distances for candidate points  
		//
		for (i = 0; i < n_solutions; i++) 
		{
			p = Bezier(pvCtrlPts, DEGREE, t_candidate[i], NULL, NULL);
		    new_dist = vVectorSquared(vSubtractVectors(pvTest, (PVECTOR2D)&p, &v));
			if (new_dist < dist) {
				dist = new_dist;
				t = t_candidate[i];
			}
		}
		// 
	    //Finally, look at distance to end point, where t = 1.0 
		//
	    new_dist = vVectorSquared(vSubtractVectors(pvTest, (PVECTOR2D)&pvCtrlPts[DEGREE], &v));
		if (new_dist < dist) 
		{
			dist = new_dist;
			t = 1.0;
		}
	}
	//
	//Return the point on the curve at parameter value t 
	//
	return (Bezier(pvCtrlPts, DEGREE, t, NULL, NULL));
}


/***********************************************************************

  FUNCTION   : ConvertToBezierForm

  PARAMETERS : PVECTOR2D P  -  The point to find t for 
               PVECTOR2D pvCtrlPts 	-  The control points	

  PURPOSE    : Given a point and a Bezier curve, generate a 5th-degree
               Bezier format equation whose solution finds the point on the
               curve nearest the user defined point.

  CALLS      : vSubtractVectors
			   malloc

  MESSAGES   : 

  RETURNS    : PVECTOR2D

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

static PVECTOR2D ConvertToBezierForm(PVECTOR2D P, PVECTOR2D pvCtrlPts)
{
	int		   i, j, k, m, n, ub, lb;
	int		   row, column;	         //Table indices	
	VECTOR2D   c[DEGREE+1];	         //pvCtrlPts(i)'s - P	
	VECTOR2D   d[DEGREE];		     //pvCtrlPts(i+1) - pvCtrlPts(i)	
	PVECTOR2D  w;			         //Ctl pts of 5th degree curve 
	double	cdTable[3][4];	         //Dot product of c, d		 
	static     double z[3][4] =      //Precomputed "z" for cubics  
	{
	{1.0, 0.6, 0.3, 0.1},
	{0.4, 0.6, 0.6, 0.4},
	{0.1, 0.3, 0.6, 1.0},
	};
	//
	//Determine the c's    these are vectors created by subtracting
	//point P from each of the control points                    
	//
	for (i = 0; i <= DEGREE; i++) 
	  vSubtractVectors((PVECTOR2D)&pvCtrlPts[i], P, (PVECTOR2D)&c[i]);
	//
	//Determine the d's -- these are vectors created by subtracting
	//each control point from the next                           
	//
	for	(i = 0; i <= DEGREE - 1; i++)
      vScaleVector(vSubtractVectors(&pvCtrlPts[i+1], &pvCtrlPts[i], &d[i]), 3.0, &d[i]);
	//
	//Create the c,d table    this is a table of dot products of the 
	//c's and d's                                    
	//
	for (row = 0; row <= DEGREE - 1; row++) 
	{
	  for (column = 0; column <= DEGREE; column++) 
	  {
	    cdTable[row][column] = vDotProduct(&d[row], &c[column]) ;
	  }
	}
	//
	//Now, apply the z's to the dot products, on the skew diagonal
	//Also, set up the x values, making these "points"            
	//
	w = (PVECTOR2D)malloc((unsigned)(W_DEGREE+1) * sizeof(VECTOR2D));
	for (i = 0; i <= W_DEGREE; i++) 
	{
	  w[i].y = 0.0;
	  w[i].x = (double)(i) / W_DEGREE;
	}
		
	n = DEGREE;
	m = DEGREE-1;

	for (k = 0; k <= n + m; k++) 
	{
	  lb = max(0, k - m);
	  ub = min(k, n);
	  for (i = lb; i <= ub; i++) 
	  {
	  	j = k - i;
		w[i+j].y += cdTable[j][i] * z[j][i];
	  }
	}

	return (w);
}

/***********************************************************************

  FUNCTION   : RecursiveSubDivide

  PARAMETERS : PVECTOR2D w	     - The control points 
               int       degree	 - The degree of the polynomial
               double    *t		 - RETURN candidate t values
               int       depth	 - The depth of the recursion

  PURPOSE    : Given a 5th degree equation in Bernstein Bezier form, find
               all of the roots in the interval [0, 1]. 

  CALLS      : ControlPolygonFlatEnough
			   ComputeXIntercept
			   Bezier
			   RecursiveSubDivide

  MESSAGES   : none

  RETURNS    : Return the number of roots found.

  COMMENTS   : previously called FindRoots in Graphics Gems

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

static int RecursiveSubDivide(PVECTOR2D w, int degree, double *t, int depth)
{
	int		 i;
	VECTOR2D Left [W_DEGREE+1],      //New left and right	
			 Right[W_DEGREE+1];      //control polygons	
	int		 left_count,		     //Solution count from
			 right_count;	         //children		
	double	 left_t[W_DEGREE+1],     //Solutions from kids	
             right_t[W_DEGREE+1];

	switch (CrossingCount(w, degree))  
	{
	  case 0 :	//No solutions here	
	    return 0;
	    break;

	  case 1 : //Unique solution 
	   	//
	  	//Stop recursion when the tree is deep enough	
		//if deep enough, return 1 solution at midpoint	
		//
 		if (depth >= MAXDEPTH) 
 		{
	             t[0] = (w[0].x + w[W_DEGREE].x) / 2.0;
	             return 1;
		}
		if (ControlPolygonFlatEnough(w, degree)) 
		{
			t[0] = ComputeXIntercept(w, degree);
			return 1;
		}
		break;
    }
	//
	//Otherwise, solve recursively after 
	//subdividing control polygon        
	//
	Bezier(w, degree, 0.5, Left, Right);
	left_count  = RecursiveSubDivide(Left, degree, left_t, depth+1);
	right_count = RecursiveSubDivide(Right, degree, right_t, depth+1);
	//
	//Gather solutions together 
	//
	for (i = 0; i < left_count; i++) 
	  t[i] = left_t[i];

	for (i = 0; i < right_count; i++) 
	  t[i+left_count] = right_t[i];
	//
	//Send back total number of solutions	
	//
    return (left_count + right_count);
}

/***********************************************************************

  FUNCTION   : CrossingCount

  PARAMETERS : PVECTOR2D pvCtrlPts - Control pts of Bezier curve
               int       degree    - Degree of Bezier curve

  PURPOSE    : Count the number of times a Bezier control polygon
               crosses the 0-axis. This number is >= the number of roots.

  CALLS      : SGN macro

  MESSAGES   : none

  RETURNS    : int - number of crossings

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

static int CrossingCount(PVECTOR2D pvCtrlPts, int degree)
{
	int	i;
	int	n_crossings = 0; //Number of zero-crossings	
	int	sign, old_sign;  //Sign of coefficients	
										   
	sign = old_sign = SGN(pvCtrlPts[0].y);
	for 	(i = 1; i <= degree; i++) 
	{
	  sign = SGN(pvCtrlPts[i].y);
	  if (sign != old_sign) n_crossings++;
	  old_sign = sign;
	}
	return (n_crossings);
}

/***********************************************************************

  FUNCTION   : ControlPolygonFlatEnough

  PARAMETERS : PVECTOR2D pvCtrlPts - Control points
               int       degree    - Degree of polynomial

  PURPOSE    : Check if the control polygon of a Bezier curve is flat 
               enough for recursive subdivision to bottom out.

  CALLS      : 

  MESSAGES   : none

  RETURNS    : int - 0 : not flat enough
                     1 : flat enough

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

static int ControlPolygonFlatEnough(PVECTOR2D pvCtrlPts, int degree)
{
	int		 i;		             //Index variable	
	double	 *distance;	         //Distances from pts to line	
	double	 max_distance_above; //maximum of these	
	double	 max_distance_below;
	double	 error;	             //Precision of root 
	double	 intercept_1,
			 intercept_2,
			 left_intercept,
			 right_intercept;
	double 	 a, b, c;	         //Coefficients of implicit	   
				                 //eqn for line from pvCtrlPts[0]-pvCtrlPts[deg] 
	//
	//Find the perpendicular distance         
	//from each interior control point to     
	//line connecting pvCtrlPts[0] and pvCtrlPts[degree]      
	//
	distance = (double *)malloc((unsigned)(degree + 1) * sizeof(double));
	{
	  double abSquared;
	  //
	  //Derive the implicit equation for line connecting first 
	  //and last control points 
	  //
	  a = pvCtrlPts[0].y - pvCtrlPts[degree].y;
	  b = pvCtrlPts[degree].x - pvCtrlPts[0].x;
	  c = pvCtrlPts[0].x * pvCtrlPts[degree].y - pvCtrlPts[degree].x * pvCtrlPts[0].y;

	  abSquared = (a * a) + (b * b);

	  for (i = 1; i < degree; i++)  
	  {
	    //
	    //Compute distance from each of the points to that line 
	    //
  	    distance[i] = a * pvCtrlPts[i].x + b * pvCtrlPts[i].y + c;
	    if (distance[i] > 0.0) 
		  distance[i] = (distance[i] * distance[i]) / abSquared;

	    if (distance[i] < 0.0) 
	      distance[i] = -((distance[i] * distance[i]) / abSquared);
	  }
	}
	//
	//Find the largest distance 
	//
	max_distance_above = 0.0;
	max_distance_below = 0.0;
	for (i = 1; i < degree; i++) 
	{
	  if (distance[i] < 0.0) 
	    max_distance_below = min(max_distance_below, distance[i]);
	  if (distance[i] > 0.0) 
	    max_distance_above = max(max_distance_above, distance[i]);
	}

	free ((char *) distance);

	{
	  double	det, dInv;
	  double	a1, b1, c1, a2, b2, c2;
	  //
	  //Implicit equation for zero line 
	  //
	  a1 = 0.0;
	  b1 = 1.0;
	  c1 = 0.0;
	  //
	  //Implicit equation for "above" line 
	  //
	  a2 = a;
	  b2 = b;
	  c2 = c + max_distance_above;

	  det = a1 * b2 - a2 * b1;
	  dInv = 1.0/det;

	  intercept_1 = (b1 * c2 - b2 * c1) * dInv;
	  //
	  //Implicit equation for "below" line 
	  //
	  a2 = a;
	  b2 = b;
	  c2 = c + max_distance_below;

	  det  = a1 * b2 - a2 * b1;
	  dInv = 1.0/det;

	  intercept_2 = (b1 * c2 - b2 * c1) * dInv;
	}
	//
	//Compute intercepts of bounding box 
	//
	left_intercept  = min(intercept_1, intercept_2);
	right_intercept = max(intercept_1, intercept_2);

	error = 0.5 * (right_intercept-left_intercept);
	if (error < EPSILON)  
	  return 1;
	else 
	  return 0;
}

/***********************************************************************

  FUNCTION   : ComputeXIntercept

  PARAMETERS : PVECTOR2D pvCtrlPts - Control points 
               int       degree	   - Degree of curve

  PURPOSE    : Compute intersection of chord from first control point to 
               last with 0-axis. 

  CALLS      : 

  MESSAGES   : none

  RETURNS    : double - X intercept

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/
static double ComputeXIntercept (PVECTOR2D pvCtrlPts, int degree)
{
	double XLK, YLK, XNM, YNM, XMK, YMK;
	double det, detInv;
	double S, T;
	double X, Y;

	XLK = 1.0 - 0.0;
	YLK = 0.0 - 0.0;
	XNM = pvCtrlPts[degree].x - pvCtrlPts[0].x;
	YNM = pvCtrlPts[degree].y - pvCtrlPts[0].y;
	XMK = pvCtrlPts[0].x - 0.0;
	YMK = pvCtrlPts[0].y - 0.0;

	det = XNM*YLK - YNM*XLK;
	detInv = 1.0/det;

	S = (XNM*YMK - YNM*XMK) * detInv;
	T = (XLK*YMK - YLK*XMK) * detInv;

	X = 0.0 + XLK * S;
	Y = 0.0 + YLK * S;

	return X;
}


/***********************************************************************

  FUNCTION   : Bezier

  PARAMETERS : PVECTOR2D pvCtrlPts	- Control pts
               int degree	        - Degree of bezier curve
               double t             - Parameter value
               PVECTOR2D Left       - RETURN left half ctl pts
               PVECTOR2D Right		- RETURN right half ctl pts

  PURPOSE    : Evaluate a Bezier curve at a particular parameter value
               Fill in control points for resulting sub-curves if "Left" and
               "Right" are non-null.

  CALLS      : 

  MESSAGES   : none

  RETURNS    : 

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/
static VECTOR2D Bezier (PVECTOR2D pvCtrlPts, int degree, double t, 
                        PVECTOR2D Left, PVECTOR2D Right)
{
	int	      i, j;                           
	VECTOR2D  Vtemp[W_DEGREE+1][W_DEGREE+1];
	//
	//Copy control points 
	//
	for (j =0; j <= degree; j++) 
	  Vtemp[0][j] = pvCtrlPts[j];
	//
	//Triangle computation 
	//
	for (i = 1; i <= degree; i++) 
	{
	  for (j =0 ; j <= degree - i; j++) {
		Vtemp[i][j].x =
			(1.0 - t) * Vtemp[i-1][j].x + t * Vtemp[i-1][j+1].x;
		Vtemp[i][j].y =
			(1.0 - t) * Vtemp[i-1][j].y + t * Vtemp[i-1][j+1].y;
	  }
	}

	if (Left != NULL) 
	{
	  for (j = 0; j <= degree; j++) 
	    Left[j] = Vtemp[j][0];
	}

	if (Right != NULL) 
	{
	  for (j = 0; j <= degree; j++) 
 		Right[j] = Vtemp[degree-j][j];
	}

	return (Vtemp[degree][0]);
}


