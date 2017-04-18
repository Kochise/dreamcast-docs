typedef float	km_vector[3];

typedef struct tagTRANSFORM
{
	float Matrix[3][4];
	float Inverse[3][4];
} TRANSFORM;

void MatrixIdentity  (TRANSFORM *);
void MatrixRotate    (TRANSFORM *, km_vector, float);
void MatrixScale     (TRANSFORM *, km_vector);
void MatrixTranslate (TRANSFORM *, km_vector);
