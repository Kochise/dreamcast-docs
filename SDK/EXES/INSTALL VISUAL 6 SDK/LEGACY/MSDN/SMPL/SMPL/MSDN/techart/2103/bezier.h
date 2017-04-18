#define SGN(a) (((a)<0) ? -1 : 0)

#define MAXDEPTH  64	                  //Maximum depth for recursion  
#define	EPSILON	 (ldexp(1.0,-MAXDEPTH-1)) //Flatness control value 
#define	DEGREE	 3		                  //Cubic Bezier curve  		
#define	W_DEGREE 5		                  //Degree of eqn to find roots of  

VECTOR2D  NearestPointOnCurve(PVECTOR2D pvTest, PVECTOR2D pvControl);
PVECTOR2D ConvertToBezierForm(PVECTOR2D P, PVECTOR2D V);
int       RecursiveSubDivide(PVECTOR2D w, int degree, double *t, int depth);
int       CrossingCount(PVECTOR2D V, int degree);
int       ControlPolygonFlatEnough(PVECTOR2D V, int degree);
double    ComputeXIntercept (PVECTOR2D V, int degree);
VECTOR2D  Bezier (PVECTOR2D V, int degree, double t, PVECTOR2D Left, PVECTOR2D Right);
