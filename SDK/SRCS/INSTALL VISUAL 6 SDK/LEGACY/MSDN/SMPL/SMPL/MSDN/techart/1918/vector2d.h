#define MPOINT2POINT(mpt, pt)   ((pt).x = (mpt).x, (pt).y = (mpt).y)
#define POINT2MPOINT(pt, mpt)   ((mpt).x = (SHORT)(pt).x, (mpt).y = (SHORT)(pt).y)
#define POINTS2VECTOR2D(pt0, pt1, vect) ((vect).x = (double)((pt1).x - (pt0).x), \
                                         (vect).y = (double)((pt1).y - (pt0).y))
typedef struct tagVECTOR2D  {
        double     x;
		double     y;
} VECTOR2D, *PVECTOR2D, FAR *LPVECTOR2D; 

typedef struct tagPROJECTION  {
        VECTOR2D   ttProjection;
		VECTOR2D   ttPerpProjection;
        double     LenProjection;
		double     LenPerpProjection;
} PROJECTION, *PPROJECTION, FAR *LPPROJECTION; 

typedef struct tagPOINTNORMAL  {
        VECTOR2D   vNormal;
		double     D;
} POINTNORMAL, *PPOINTNORMAL, FAR *LPPOINTNORMAL;

PVECTOR2D  APIENTRY vSubtractVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v);
PVECTOR2D  APIENTRY vAddVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v);
PVECTOR2D  APIENTRY vScaleVector(PVECTOR2D v0, double dScaling, PVECTOR2D v);
PVECTOR2D  APIENTRY vLinearCombination(PVECTOR2D ptScale, PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v);
double     APIENTRY vVectorSquared(PVECTOR2D v0);
double     APIENTRY vVectorMagnitude(PVECTOR2D v0);
void       APIENTRY vNormalizeVector(PVECTOR2D ptN);
double     APIENTRY vDotProduct(PVECTOR2D v, PVECTOR2D v1);
PVECTOR2D  APIENTRY vNormalVector(PVECTOR2D v0, PVECTOR2D v);
BOOL       APIENTRY vPointNormalForm(POINT pt0, POINT pt1, PPOINTNORMAL ppnPointNormal);
void       APIENTRY vProjectAndResolve(PVECTOR2D v0, PVECTOR2D v1, PPROJECTION ppProj);
BOOL       APIENTRY vIsPerpendicular(PVECTOR2D v0, PVECTOR2D v1);
double     APIENTRY vVectorAngle(PVECTOR2D v0, PVECTOR2D v1);
double     APIENTRY vDistFromPointToLine(LPPOINT pt0, LPPOINT pt1, LPPOINT ptTest);
