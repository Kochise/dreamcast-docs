typedef struct{float x,y,z;} NJS_POINT3;
outerp0(p0,p1,p2,op) NJS_POINT3*p0,*p1,*p2,*op;
{	NJS_POINT3 v0,v1;
	v0.x = p1->x - p0->x;
	v0.y = p1->y - p0->y;
	v0.z = p1->z - p0->z;
	v1.x = p2->x - p0->x;
	v1.y = p2->y - p0->y;
	v1.z = p2->z - p0->z;
	op->x = v0.y * v1.z - v0.z * v1.y;
	op->y = v0.z * v1.x - v0.x * v1.z;
	op->z = v0.x * v1.y - v0.y * v1.x;
}

#define PopV(p,a,b,c) a=*p++; b=*p++; c=*p++
#define StoreV(a,b,c, p) p[0]=a; p[1]=b; p[2]=c
#define SubV(x0,y0,z0, x1,y1,z1) x1-=x0; y1-=y0; z1-=z0
#define Determinant(a,b,c,d) a*d-b*c
outerp1(P0,P1,P2,OP) NJS_POINT3*P0,*P1,*P2,*OP;
{	float*p0=(float*)P0,*p1=(float*)P1,
	     *p2=(float*)P2,*op=(float*)OP;
	float  x0,y0,z0, x1,y1,z1;
	float  x2,y2,z2;
	PopV(p0, x0,y0,z0);
	PopV(p1, x1,y1,z1);
	SubV(x0,y0,z0, x1,y1,z1);
	PopV(p2, x2,y2,z2);
	SubV(x0,y0,z0, x2,y2,z2);
	x0 = Determinant(y1,z1,y2,z2);
	y0 = Determinant(z1,x1,z2,x2);
	z0 = Determinant(x1,y1,x2,y2);
	StoreV(x0,y0,z0, op);
}

