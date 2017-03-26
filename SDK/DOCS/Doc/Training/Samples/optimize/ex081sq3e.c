typedef struct{float x,y,z;}NJS_POINT3;
typedef struct PolyInfo {
	int polatflg;		/* polygon attr (attrflags) */
	float ndlenmax2;	/* polygon node length max */
	struct PolyInfo *next;  /* next polyinfo pointer */
	NJS_POINT3 vrt[3];	/* polygon vertexies */
} PolyInfo;  /* size = 30H (byte) */

#define NULL 0
#define NORM2(p) ((p)->x*(p)->x + (p)->y*(p)->y + (p)->z*(p)->z)
#define PopV(p,a,b,c) a=*p++; b=*p++; c=*p++
#define PushV(a,b,c, p) *--p=c; *--p=b; *--p=a
#define SubV(x0,y0,z0, x1,y1,z1) x1-=x0; y1-=y0; z1-=z0
#define Norm2(x,y,z) x*x+y*y+z*z

SubVector(p,q) float*p,*q;
{	float x0,y0,z0, x1,y1,z1;

	PopV(p,x0,y0,z0);
	PopV(q,x1,y1,z1);
	SubV(x0,y0,z0, x1,y1,z1);
	PushV(x1,y1,z1, p);
}
int func1(p,rad) PolyInfo*p;float rad;
{
	PolyInfo*pirp;
	int count;
	for (pirp = p; pirp != NULL; pirp = pirp->next) {
		float d0,d1,d2;
		NJS_POINT3 dv0,dv1,dv2;

		dv0 = pirp->vrt[0];
		dv1 = pirp->vrt[1];
		SubVector(&dv1, &dv0);
		d0 = NORM2(&dv1);
		dv2 = pirp->vrt[2];
		SubVector(&dv2, &dv0);
		d1 = NORM2(&dv2);
		SubVector(&dv1, &dv2);
		d2 = NORM2(&dv1);
		if (d0+d1+d2 > rad)	continue;
		count++;
	}
	return count;
}
int func2(p,ctp,rad) PolyInfo*p;NJS_POINT3*ctp;float rad;
{
	int count=0;
	PolyInfo*pirp;
	for (pirp = p; pirp != NULL; pirp = pirp->next) {
		float d0,d1,d2;
		float x0,y0,z0, x1,y1,z1, x2,y2,z2;
		float*q=(float*)pirp->vrt;

		PopV(q,x0,y0,z0);
		PopV(q,x1,y1,z1);
		SubV(x0,y0,z0,x1,y1,z1);
		d0=Norm2(x1,y1,z1);
		PopV(q,x2,y2,z2);
		SubV(x0,y0,z0,x2,y2,z2);
		d1=Norm2(x2,y2,z2);
		SubV(x2,y2,z2,x1,y1,z1);
		d2=Norm2(x1,y1,z1);
		if (d0+d1+d2 > rad)	continue;
		count++;
	}
	return count;
}

