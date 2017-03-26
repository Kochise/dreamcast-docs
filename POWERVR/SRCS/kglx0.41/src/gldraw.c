/*
   KGL-x 0.4

   gldraw.c
   (c) 2002-2003 heinrich tillack

   derived version from
   KallistiGL for KOS 1.1.9

   gldraw.c
   (c)2001 Dan Potter
   and
   gldraw.c (c) 2002 BERO
*/


/* XXX- Please note there is a include at the end of this file ! */

#include <GL/gl.h>
#include <GL/glu.h>


#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <dc/pvr.h>

#include "glinternal.h"
#include "glmacros.h"


#define CHECK_VALUE
#define CHECK_INBEGIN
#define CHECK_BEGIN

#define alloca __builtin_alloca

CVSID("$Id: gldraw.c,v 1.22 2002/06/24 02:54:35 axlen Exp $");

/* internal prototypes */
INLINE void send_user_clip();

/* It is important to align the vertex buffers for use with the
   the direct render API. I found 8192 gave the best results, but 32,
   64, and 1024 also worked well. To see cache thrashing in action try
   setting the alignment to 16384 or 32768. The polys per second will
   drop by about half.

   mat_transform seems to work best when the source and destination buffers
   are seperate.  Therefore we have a pre and post transform vertex buffer */

/* Pre-xformed vertex buffer */
static gl_vertex_t opaque_vtxbuf[VBUF_SIZE] __attribute__((aligned(8192)));
gl_vertex_t *vtxbuf;
/* Post-xformed vertex buffer */
int vbuf_top,vbuf_size;


/* Drawing functions */

/* This portion of the pipeline will change drastically */

/* Current vertex attributes (move to global?) */
GLuint vert_rgba = 0xffffffff;
GLfloat vert_u = 0.0f, vert_v = 0.0f;
GLfloat nx,ny,nz;

/* Make sure the proper matrices are in the matrix registers */
static void fix_matrices() {
    if (gl_matrix_dirty) {
        mat_identity();
        glKosMatrixApply(GL_KOS_SCREENVIEW);
        glKosMatrixApply(GL_PROJECTION);
        glKosMatrixApply(GL_MODELVIEW);

        gl_matrix_dirty = GL_FALSE;
    }
}

/* NEAR_Z CLIPPING STUFF START */


#define mat_rot_single4(x, y, z, w) { \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	register float __w __asm__("fr3") = (w); \
	__asm__ __volatile__( \
		"ftrv	xmtrx,fv0\n" \
		: "=f" (__x), "=f" (__y), "=f" (__z),"=f" (__w) \
		: "0" (__x), "1" (__y), "2" (__z), "3" (__w) \
		); \
	x = __x; y = __y; z = __z; w = __w; \
}


#define mat_rot_single3(x, y, z) { \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	__asm__ __volatile__( \
		"fldi1	fr3\n" \
		"ftrv	xmtrx,fv0\n" \
		"fmov	fr3,fr2" \
		: "=f" (__x), "=f" (__y), "=f" (__z) \
		: "0" (__x), "1" (__y), "2" (__z) \
		: "fr3" ); \
	x = __x; y = __y; z = __z;  \
}

#undef	mat_trans_single
#define mat_trans_single(x, y, z) { \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	__asm__ __volatile__( \
		"fldi1	fr3\n" \
		"ftrv	xmtrx,fv0\n" \
		"fldi1	fr2\n" \
		"fdiv	fr3,fr2\n" \
		"fmul	fr2,fr0\n" \
		"fmul	fr2,fr1\n" \
		: "=f" (__x), "=f" (__y), "=f" (__z) \
		: "0" (__x), "1" (__y), "2" (__z) \
		: "fr3" ); \
	x = __x; y = __y; z = __z; \
}

static void transform(gl_vertex_t *vbuf,size_t size) {
    if ((size) ||(gl_prim_type<GL_NT_FLATFAN))
        do {
            // float x = vbuf[0].x, y = vbuf[0].y, z = vbuf[0].z,
            //   float w=vbuf[0].w;
            //   mat_rot_single4(vbuf[0].x, vbuf[0].y, vbuf[0].z, vbuf[0].w);
            // vbuf[0].z = vbuf[0].w;
            mat_rot_single3(vbuf[0].x, vbuf[0].y, vbuf[0].z);


            vbuf++;
        } while(--size);
}

#define	ARGB_A(c)	(c>>24)
#define	ARGB_R(c)	((c>>16)&0xff)
#define	ARGB_G(c)	((c>>8)&0xff)
#define	ARGB_B(c)	(c&0xff)

#define	CLIP_Z	0.001f
#define	Z_NEAR_VALUE CLIP_Z



/* return number of z<=0 point */
INLINE int check_w(gl_vertex_t *vert, int n) {
    int i,ret;

    ret = 0;
    for(i=0; i<n; i++)
        if (vert[i].z <= 0) ret++;
    return ret;
}





/* return number of z<=0 point */
INLINE int check_precomp_w(gl_vertex_t *vert, int n) {
    int i,ret;

    ret = 0;
    for(i=0; i<n; i++)
        if (vert[i].flags) ret++;
    return ret;
}

INLINE GLuint mix_color(GLuint argb0,GLuint argb1,float d)
{
    if (argb0 == argb1) {
        return argb0;
    } else {
        int a,r,g,b;
        a = ARGB_A(argb0) + (int)((ARGB_A(argb1) - ARGB_A(argb0))*d);
        r = ARGB_R(argb0) + (int)((ARGB_R(argb1) - ARGB_R(argb0))*d);
        g = ARGB_G(argb0) + (int)((ARGB_G(argb1) - ARGB_G(argb0))*d);
        b = ARGB_B(argb0) + (int)((ARGB_B(argb1) - ARGB_B(argb0))*d);

        return (((a<<8) | r)<<16) | (g<<8) | (b);
    }
}




INLINE void ClipZ(gl_vertex_t *nv,gl_vertex_t *v0,gl_vertex_t *v1)
{
    float d;

    d = (CLIP_Z - v0->z)/(v1->z - v0->z);

    nv->x = v0->x + (v1->x - v0->x)*d;
    nv->y = v0->y + (v1->y - v0->y)*d;
    nv->z = CLIP_Z;
    nv->u = v0->u + (v1->u - v0->u)*d;
    nv->v = v0->v + (v1->v - v0->v)*d;
    nv->argb = mix_color(v0->argb,v1->argb,d);
    nv->oargb = mix_color(v0->oargb,v1->oargb,d);
}



INLINE void *pvr_commit_init(void)
{
    QACR0 = ((((uint32)PVR_TA_INPUT) >> 26) << 2) & 0x1c;
    QACR1 = ((((uint32)PVR_TA_INPUT) >> 26) << 2) & 0x1c;
    return (void*)0xe0000000;
}

INLINE void _pvr_commit(volatile pvr_vertex_t *vert,const gl_vertex_t *vbuf)
{
    float rhw;
    vert->flags = vbuf->flags;
    rhw = 1/vbuf->z;
    vert->x = vbuf->x * rhw;
    vert->y = vbuf->y * rhw;
    vert->z = rhw;
    vert->u = vbuf->u;
    vert->v = vbuf->v;
    vert->argb = vbuf->argb;
    vert->oargb = vbuf->oargb;
    pvr_dr_commit(vert);
}

static volatile pvr_vertex_t *_pvr_commit_n(volatile pvr_vertex_t *vert,gl_vertex_t *vbuf,size_t n)
{

    while (n--)
    {
        float rhw;
        vert->flags = (n==0) ? PVR_CMD_VERTEX_EOL : PVR_CMD_VERTEX;
        rhw = 1/vbuf->z;
        vert->x = vbuf->x * rhw;
        vert->y = vbuf->y * rhw;
        vert->z = rhw;
        vert->u = vbuf->u;
        vert->v = vbuf->v;
        vert->argb = vbuf->argb;
        vert->oargb = vbuf->oargb;
        pvr_dr_commit(vert); (uint32)vert^=32;
        vbuf++;
    } ;
    return vert;
}

#define	pvr_commit_n(vert,vbuf,n)	vert = _pvr_commit_n(vert,vbuf,n)
#define	pvr_commit(vert,vbuf)	do { _pvr_commit(vert,vbuf); (uint32)vert^=32; } while(0)

INLINE void v_copy(gl_vertex_t *vert,const gl_vertex_t *vbuf)
{
    *vert = *vbuf;
}


static int clip_n(gl_vertex_t *dst,gl_vertex_t *src,size_t n)
{
	gl_vertex_t *v0,*v1;
	int i,out = 0;
	for(i=0,v0=src;i<n;i++,v0++) {
		if (i!=(n-1)) v1=v0+1;
		else v1 = src;

		if (v0->z>0) {
			dst[out++] = *v0;
			if (v1->z<=0) {
				ClipZ(&dst[out++],v0,v1);
			}
		} else {
			if (v1->z>0) {
				ClipZ(&dst[out++],v0,v1);
			}
		}
	}
	return out;
}

static inline void CopyV(gl_vertex_t *vertold, gl_vertex_t *vertnew) {

    *vertnew = *vertold;
}


#define LESS_Z	1	// <z bad vert clipping outcodes
#define GEQUAL_Z 0  // >= z good vert

inline static int PreComputeClipCodes(gl_vertex_t v[],uint32 nbindices){
    uint result=0;
    while(nbindices--){
        if (v[nbindices].z < Z_NEAR_VALUE){ //FIXME?!: < 0
            //HACK: I use v.flags for my clipcode var`s
            //because at the Commit stage I do not use "flags"
            v[nbindices].flags=LESS_Z;
            result++;
        }
        else
            v[nbindices].flags=GEQUAL_Z;


    }
    return result;
}




static int ZClip(gl_vertex_t *vert)
/* returns 0 for full clip, 3 for triangle output and 4 for quad output
   based on sutherland-hodgeman clip algorithm */
{
    uint i,j;
    gl_vertex_t tempvert[4]  __attribute__((aligned(32)));



    //     if ( ((vert[0].flags)||
    //             (vert[1].flags) ||
    //             (vert[2].flags))
    //        )

    {/* one or more parts behind camera */
        j=0;
        CopyV(&vert[0],&vert[3]);/* copy first to next after last to make cyclic */

        i=0;
        while(i<3){

            if (vert[i].flags){
                if(!vert[i+1].flags){
                    /* this out, next in */
                    CopyV(&vert[i],&tempvert[j]);
                    ClipZ(&tempvert[j],&vert[i],&vert[i+1]);
                    j++;

                }//else{/* both out, ignore */}
            }else
                if(vert[i+1].flags)
                {
                    /* this in, next out */
                    CopyV(&vert[i],&tempvert[j]);
                    CopyV(&vert[i+1],&tempvert[j+1]);
                    ClipZ(&tempvert[j+1],&vert[i],&vert[i+1]);
                    j+=2;
                }
                else{
                    /* both in */
                    CopyV(&vert[i],&tempvert[j]);
                    j++;
                }
            i++;
        }



        switch (j) {
        case 3:

            CopyV(&tempvert[0],&vert[0]);
            CopyV(&tempvert[1],&vert[1]);
            CopyV(&tempvert[2],&vert[2]);

            return 3;
        case 4:

            CopyV(&tempvert[0],&vert[0]);
            CopyV(&tempvert[1],&vert[1]);
            CopyV(&tempvert[2],&vert[3]);
            CopyV(&tempvert[3],&vert[2]);

            return 4;
        }/* if j==0 we return 0 which we are about to do anyway */

    }
    //     else{/* is all in front of camera */
    //         return 3;
    //     }

    //   return 0;/* if it isn't one of the above it is an invalid poly or completely behind camera */
}


static volatile pvr_vertex_t *pvr_commit_poly(volatile pvr_vertex_t *vert,gl_vertex_t *vtxbuf,size_t n)
{
	int i;
	switch(n) {
	case 0:
	case 1:
	case 2:
		break;
	case 3:
		vtxbuf[2].flags = PVR_CMD_VERTEX_EOL;
		pvr_commit_n(vert,vtxbuf,3);
		break;
	case 4:
		vtxbuf[2].flags = PVR_CMD_VERTEX_EOL;
		pvr_commit(vert,vtxbuf);
		pvr_commit(vert,vtxbuf+1);
		pvr_commit(vert,vtxbuf+3);
		pvr_commit(vert,vtxbuf+2);
		break;
	case 5:
		vtxbuf[3].flags = PVR_CMD_VERTEX_EOL;
		pvr_commit(vert,vtxbuf);
		pvr_commit(vert,vtxbuf+1);
		pvr_commit(vert,vtxbuf+4);
		pvr_commit(vert,vtxbuf+2);
		pvr_commit(vert,vtxbuf+3);
		break;
	default:
		vtxbuf[(n+1)/2].flags = PVR_CMD_VERTEX_EOL;
		pvr_commit(vert,vtxbuf);
		for(i=1;i<(n+1)/2;i++) {
			pvr_commit(vert,vtxbuf+i);
			pvr_commit(vert,vtxbuf+n-i);
		}
		if ((n&1)==0) {
			pvr_commit(vert,vtxbuf+i);
		}
		break;
	}
	return vert;
}


static inline volatile pvr_vertex_t *pvr_commit_poly_clip(volatile pvr_vertex_t *vert,gl_vertex_t *dst,gl_vertex_t *src,size_t n)
{
	n = clip_n(dst,src,n);
	return pvr_commit_poly(vert,dst,n);
}
/* NEAR_Z CLIPPING STUFF END */

static short xor[2][2] ={
                            {1,0}, /* FFCW, FFCCW */
                            {0,1}  /* BFCW, BFCCW */
                        };
/* GL_POINTS always visible! */
INLINE void end_points(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    int i,j;
    volatile pvr_vertex_t	*vert;

    float size1 = (xor[(gl_cull_mode == GL_BACK)][(gl_front_face == GL_CCW)]) ? gl_point_size : -gl_point_size;
    float size2 = ABS(size1);
    struct {
        float x,y;
    } offset[4];

    /* Should be one point in the buffer */
    assert(vbuf_top >= 1);

    offset[0].x = size1;
    offset[0].y = size2;
    offset[1].x = size1;
    offset[1].y = -size2;
    offset[2].x = -size1;
    offset[2].y = size2;
    offset[3].x = -size1;
    offset[3].y = -size2;

    vert = pvr_commit_init();

    /* Throw it all to the TA using direct render */
    for(i=0;i<vbuf_top;i++,vtxbuf++) {
        if (vtxbuf->z>0) {
            float x,y,rhw;
            rhw = 1/vtxbuf->z;
            x = vtxbuf->x*rhw;
            y = vtxbuf->y*rhw;
            for (j=0; j<4; j++) {
                vert->flags = (i!=3)?vtxbuf[0].flags:PVR_CMD_VERTEX_EOL;
                vert->x     = x + offset[j].x;
                vert->y     = y + offset[j].y;
                vert->z     = rhw;
                vert->u     = vtxbuf->u;
                vert->v     = vtxbuf->v;
                vert->argb  = vtxbuf->argb;
                vert->oargb = vtxbuf->oargb;
                pvr_dr_commit(vert);
                (uint32)vert ^= 32;
            }
        }
    }
}



INLINE void end_triangles(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    int i,j,n;
    volatile pvr_vertex_t	*vert;

    /* Should be three points in the buffer */
    assert_msg(((vbuf_top%3)==0), "Wrong number of vertices.");

    vert = pvr_commit_init();

    if (n==0) return;

    /* Throw it all to the TA using direct render */
    for(i=0;i<vbuf_top;i+=3,vtxbuf+=3) {
        //precompute clipping codes
        n=PreComputeClipCodes(vtxbuf,3);
        if (n==0) {
            pvr_commit_n(vert,vtxbuf,3);
        }
        else if (n!=3) {
            gl_vertex_t v[4]  __attribute__((aligned(32)));
            if(!ZCLIP_ENABLED) return;

            CopyV(&vtxbuf[0],&v[0]);
            CopyV(&vtxbuf[1],&v[1]);
            CopyV(&vtxbuf[2],&v[2]);
            pvr_commit_n(vert,v, ZClip(v));


        }
    }

}




static void end_triangle_strip(gl_vertex_t *vbuf,size_t vbuf_top) {
    int n;
    volatile pvr_vertex_t	*vert;

    /* Should be at least 3 points in the buffer */

    assert_msg(vbuf_top>=3, "Wrong number of vertices.");

    vert = pvr_commit_init();
    //precompute clipping codes
    n=PreComputeClipCodes(vbuf,vbuf_top);
    if (n==0) {
        pvr_commit_n(vert,vbuf,vbuf_top);
    } else if (n!=vbuf_top) {

        if(!ZCLIP_ENABLED) return;

        int i=vbuf_top-2;

        gl_vertex_t v[4],vtmp[4]  __attribute__((aligned(32)));

        while(i>1){
            n=check_precomp_w(vbuf,4);
            if (n==0) {
                pvr_commit_n(vert,vbuf,4);
            } else if (n!=4) {

                CopyV(&vbuf[0],&v[0]);
                CopyV(&vbuf[1],&v[1]);
                CopyV(&vbuf[2],&v[2]);
                CopyV(&vbuf[3],&v[3]);

                CopyV(&v[1],&vtmp[0]);
                CopyV(&v[2],&vtmp[1]);
                CopyV(&v[3],&vtmp[2]);

                pvr_commit_n(vert,v, ZClip(v));
                pvr_commit_n(vert,vtmp, ZClip(vtmp));


            }

            i-=2;
            vbuf+=2;
        }

        if (i) {
            n=check_precomp_w(vbuf,3);
            if (n==0) {
                pvr_commit_n(vert,vbuf,3);
            } else if (n!=3) {

                pvr_commit_n(vert,vbuf, ZClip(vbuf));

            }
        }
    }


}

static void end_triangle_fan(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    int i;
    volatile pvr_vertex_t	*vert;

    gl_vertex_t *vbuf,v[4],vtmp[3];

    /* Should be three points in the buffer */
    //assert_msg((vbuf_top=>3), "Wrong number of vertices.");

    vert = pvr_commit_init();

    vtxbuf[0].flags = PVR_CMD_VERTEX_EOL;
    
  

    /* Throw it all to the TA using direct render */
    for(i=1,vbuf=vtxbuf+1;i<vbuf_top-1;i++,vbuf++) {
        if (vtxbuf[0].z>0 && vbuf[0].z>0 && vbuf[1].z>0) {
            /* all inside */
            pvr_commit(vert,vbuf);
            pvr_commit(vert,vbuf+1);
            pvr_commit(vert,vtxbuf);

        } else if (vtxbuf[0].z<CLIP_Z && vbuf[0].z<CLIP_Z && vbuf[1].z<CLIP_Z) {
            /* all outside */
        } else {
            if(!ZCLIP_ENABLED)return;
            //XXX TO DO
            #if 0
            v_copy(vtmp,vbuf);
            v_copy(vtmp+1,vbuf+1);
            v_copy(vtmp+2,vtxbuf);
            vtmp[2].flags = PVR_CMD_VERTEX;
            vert = pvr_commit_poly_clip(vert,v,vtmp,3);
            #endif
        }
    }
}

static void end_quads(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    int i;
    volatile pvr_vertex_t	*vert;

    /* Should be four points in the buffer */

    assert_msg(!(vbuf_top%4), "Wrong number of vertices.");

    vert = pvr_commit_init();
    
      gl_vertex_t v[4],vtmp[4]  __attribute__((aligned(32)));

    /* Throw it all to the TA using direct render */
    for (i=0; i<vbuf_top; i+=4,vtxbuf+=4) {
        int n = check_w(vtxbuf,4);
       //precompute clipping codes
    
        if (n==0) { /* all inside */
            vtxbuf[2].flags = PVR_CMD_VERTEX_EOL;
            pvr_commit(vert,vtxbuf);
            pvr_commit(vert,vtxbuf+1);
            pvr_commit(vert,vtxbuf+3);
            pvr_commit(vert,vtxbuf+2);
        } else if (n!=4) {
           gl_vertex_t v[4]  __attribute__((aligned(32)));
            if(!ZCLIP_ENABLED) return;
            
            	int n=PreComputeClipCodes(vtxbuf,4);
    	

            CopyV(&vtxbuf[0],&v[0]);
            CopyV(&vtxbuf[1],&v[1]);
            CopyV(&vtxbuf[2],&v[2]);
            pvr_commit_n(vert,v, ZClip(v));
            
            
            CopyV(&vtxbuf[0],&v[0]);
            CopyV(&vtxbuf[2],&v[1]);
            CopyV(&vtxbuf[3],&v[2]);
            pvr_commit_n(vert,v, ZClip(v));
            

        }
    }
}


static void end_quad_strip(gl_vertex_t *vbuf,size_t vbuf_top) {
    int n;
    volatile pvr_vertex_t	*vert;


    assert_msg(1, "GL_QUAD_STRIP is currently not working.");
#if 0
    /* Should be at least 4 points in the buffer */
    assert_msg(vbuf_top >= 4, "Need at least four vertices.");
    /* OpenGL specs that any dangling vertex be chopped, which
    we have to do since we're rendering as a tri-strip. */
    if(vbuf_top & 0x0001)
        vbuf_top--;


    vert = pvr_commit_init();

    n = check_w(vbuf,vbuf_top);
    if (n==0) {
        pvr_commit_n(vert,vbuf,vbuf_top);
    } else if (n!=vbuf_top) {
        int i;

        if(!ZCLIP_ENABLED) return;

        gl_vertex_t v[4],vtmp[3];
        for(i=0;i<vbuf_top-3;i+=2,vbuf+=2) {
            n=check_w(vbuf,4);
            if (n==0) {
                pvr_commit_n(vert,vbuf,4);
            } else if (n!=4) {



                vert = pvr_commit_poly_clip(vert,v,vbuf,3);
                v_copy(vtmp,vbuf+2);
                v_copy(vtmp+1,vbuf+3);
                v_copy(vtmp+2,vbuf+1);
                vert = pvr_commit_poly_clip(vert,v,vtmp,3);
            }
        }
        if ((vbuf_top&1)==0) {
            n=check_w(vbuf,3);
            if (n==0) {
                pvr_commit_n(vert,vbuf,3);
            } else if (n!=3) {
                vert = pvr_commit_poly_clip(vert,v,vbuf,3);
            }
        }
    }
#endif
}

static void end_polygon(gl_vertex_t *vtxbuf,size_t vbuf_top)
{
    assert_msg(1, "GL_POLYGON is currently not working.");
}



//Like end_trianglefan without 3d->2D Transformation
static void end_GL_NTflatfan(gl_vertex_t *vtxbuf,size_t vbuf_top)
{
    int i,n;
    volatile pvr_vertex_t	*vert;
    //int outpoint;
    gl_vertex_t *vbuf;//,v[4],vtmp[3];

    /* Should be three points in the buffer */
    assert_msg(vbuf_top>=3, "Wrong number of vertices.");

    vert = pvr_commit_init();

    vtxbuf[0].flags = PVR_CMD_VERTEX_EOL;

    /* Throw it all to the TA using direct render */
    for(i=1,vbuf=vtxbuf+1;i<vbuf_top-1;i++,vbuf++) {
        if (vtxbuf[0].z>0 && vbuf[0].z>0 && vbuf[1].z>0) {
            /* all inside */
            pvr_commit(vert,vbuf);
            pvr_commit(vert,vbuf+1);
            pvr_commit(vert,vtxbuf);
        }
    }
}
//Like end_triangle_strip without 3d->2D Transformation
static void end_GL_NTflatstrip(gl_vertex_t *vbuf,size_t vbuf_top) {
    int n;
    volatile pvr_vertex_t	*vert;

    /* Should be at least 3 points in the buffer */
    assert_msg(vbuf_top>=3, "Wrong number of vertices.");

    vert = pvr_commit_init();

    //TO DO: disable check_w?! cause z>=0 !!!!
    n = check_w(vbuf,vbuf_top);
    if (n==0) {
        pvr_commit_n(vert,vbuf,vbuf_top);
    }

    if ((vbuf_top&1)==0) {
        n=check_w(vbuf,3);
        if (n==0) {
            pvr_commit_n(vert,vbuf,3);

        }

    }

}


//Like end_quads without 3d->2D Transformation

static void end_GL_NTquads(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    int i;
    volatile pvr_vertex_t	*vert;

    /* Should be four points in the buffer */

    assert_msg(!(vbuf_top%4), "Wrong number of vertices.");

    vert = pvr_commit_init();

    /* Throw it all to the TA using direct render */
    for (i=0; i<vbuf_top; i+=4,vtxbuf+=4) {
        int n = check_w(vtxbuf,4);
        if (n==0) { /* all inside  (Z>0) */
            vtxbuf[2].flags = PVR_CMD_VERTEX_EOL;
            pvr_commit(vert,vtxbuf);
            pvr_commit(vert,vtxbuf+1);
            pvr_commit(vert,vtxbuf+3);
            pvr_commit(vert,vtxbuf+2);
        }

    }
}

static pvr_poly_hdr_t polyhdr;

void send_poly_hdr(void) {

    if (TXR_ENABLED) {
        memcpy(&gl_poly_cxt.txr, &gl_cur_texture->txr, sizeof(gl_poly_cxt.txr));
    }

    switch(gl_active_list) {
    case GL_LIST_OPAQUE_POLY:
        gl_poly_cxt.gen.alpha = PVR_ALPHA_DISABLE;
        gl_poly_cxt.txr.alpha = PVR_TXRALPHA_ENABLE;
        gl_poly_cxt.blend.src = PVR_BLEND_ONE;
        gl_poly_cxt.blend.dst = PVR_BLEND_ZERO;
        break;
    case GL_LIST_OPAQUE_MOD:
        break;
    case GL_LIST_TRANS_POLY:
    case GL_LIST_PUNCHTHRU:
        gl_poly_cxt.gen.alpha = PVR_ALPHA_ENABLE;
        gl_poly_cxt.txr.alpha = PVR_TXRALPHA_ENABLE;
        gl_poly_cxt.blend.src = gl_blend_src;
        gl_poly_cxt.blend.dst = gl_blend_dst;
        break;
    case GL_LIST_TRANS_MOD:
        break;
    }
    /* Set states that we couldn't before */
    if (gl_cull_face)
    {
        if (gl_cull_mode == GL_BACK)
            if (gl_front_face == GL_CW)
                gl_poly_cxt.gen.culling = PVR_CULLING_CCW;
            else
                gl_poly_cxt.gen.culling = PVR_CULLING_CW;
        else
            if (gl_front_face == GL_CCW)
                gl_poly_cxt.gen.culling = PVR_CULLING_CCW;
            else
                gl_poly_cxt.gen.culling = PVR_CULLING_CW;
    } else
        gl_poly_cxt.gen.culling = PVR_CULLING_NONE;

    pvr_poly_compile(&polyhdr, &gl_poly_cxt);
    pvr_prim(&polyhdr, sizeof(pvr_poly_hdr_t));
}

/* This can be used for KGL Direct Rendering */
void glKosPolyHdrSend() {
    send_poly_hdr();
}


static uint32 old_cur_texture=-1;



void glopBegin(GLParam * p) {

    //int mode = p[1].i;

    vtxbuf = opaque_vtxbuf;
    vbuf_size = VBUF_SIZE;
    vbuf_top = 0;

    /* Submit the user clip rectangle (if necessary) */
    if (gl_scissor_dirty) {
        send_user_clip();
        gl_scissor_dirty = GL_FALSE;
    }

    /* Submit the poly buffer (if necessary) */
    if (!gl_pbuf_submitted) {
        send_poly_hdr();
        gl_pbuf_submitted = GL_TRUE;
    }

    fix_matrices();

    gl_prim_type = p[1].i;
    vbuf_top = 0;


}


static void end_dmy(gl_vertex_t *vtxbuf,size_t vbuf_top) {}
static void end_lines(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    assert_msg(0,"GL_LINES not implemented");}
static void end_line_loop(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    assert_msg(0,"GL_LINE_LOOP not implemented");}
static void end_line_strip(gl_vertex_t *vtxbuf,size_t vbuf_top) {
    assert_msg(0,"GL_LINE_STRIP not implemented");}



typedef void (*drawfunc)(gl_vertex_t *vtxbuf,size_t vbuf_top);


const static drawfunc drawfuncs[] = {
                                        end_dmy,	/* 0 */
                                        end_points,	/* GL_POINTS */
                                        end_lines,	/* GL_LINES */
                                        end_line_loop,	/* GL_LINE_LOOP */
                                        end_line_strip,	/* GL_LINE_STRIP */
                                        end_triangles,	/* GL_TRIANGLES */
                                        end_triangle_strip,	/* GL_TRIANGLES */
                                        end_triangle_fan,	/* GL_TRIANGLE_FAN */
                                        end_quads,	/* GL_QUADS */
                                        end_quad_strip,	/* GL_QUAD_STRIP */
                                        end_polygon,	/* GL_POLYGON */
                                        end_GL_NTflatfan,	/* GL_NT_FLATFAN */
                                        end_GL_NTflatstrip,	/* GL_NT_FLATSTRIP */
                                        end_GL_NTquads,	/* GL_NT_QUADS */
                                    };


void glopEnd(GLParam * p) {
    transform(vtxbuf,vbuf_top);
    drawfuncs[gl_prim_type](vtxbuf,vbuf_top);
    gl_prim_type = 0;
}

static float autouv[4][2] = {
                                {0.0f, 0.0f},
                                {1.0f, 0.0f},
                                {1.0f, 1.0f},
                                {0.0f, 1.0f}
                            };


INLINE void submit_them() {


    //printf("Submit them...\n");

    transform(vtxbuf,vbuf_top);
    drawfuncs[gl_prim_type](vtxbuf,vbuf_top);


    //allow restart
    fix_matrices();


    vtxbuf = opaque_vtxbuf; //XXX
    vbuf_top = 0;

}


/* glopVertex */

inline void glopVertex(GLParam * p) {

    static int a_uv=0;

   //just to make sure we have flags set, cause some
   //methods do not use precompute stuff
     vtxbuf[vbuf_top].flags = PVR_CMD_VERTEX;

    vtxbuf[vbuf_top].x =  p[1].f;
    vtxbuf[vbuf_top].y =  p[2].f;
    vtxbuf[vbuf_top].z =  p[3].f;
    vtxbuf[vbuf_top].w =  p[4].f;
    /* XXX - Must set uv values to zero if texture is disabled!? */
    if (AUTOUV_ENABLED) {
        vert_u = autouv[a_uv][0];
        vert_v = autouv[a_uv++][1];
        if(a_uv>3)a_uv=0;

    }
    vtxbuf[vbuf_top].u = vert_u;
    vtxbuf[vbuf_top].v = vert_v;


    vtxbuf[vbuf_top].argb = vert_rgba;
    vtxbuf[vbuf_top].oargb = 0xff000000;

    //     Normals (still unused stuff)

    //     vtxbuf[vbuf_top].nx = nx;
    //     vtxbuf[vbuf_top].ny = ny;
    //     vtxbuf[vbuf_top].nz = nz;



    vbuf_top++;

}


/* glopNormal */

inline void glopNormal(GLParam * p) {
        nx = p[1].f;
         ny =p[2].f;
         nz =p[3].f;

}

/* glopColor */

#define	SET_COLOR(red,green,blue,alpha)	\
	vert_rgba = ((alpha) << 24) | ((red) << 16) | ((green) << 8) | (blue);



inline void  glopColor(GLParam * p) {

	#define r p[1].f

	#define g p[2].f

	#define b p[3].f

	#define a p[4].f

    SET_COLOR((int)(r*0xff),(int)(g*0xff),(int)(b*0xff),(int)(a*0xff))

  	#undef r
  	#undef b
  	#undef a
  	#undef g

}


/* glopTexCoord */

inline void  glopTexCoord(GLParam * p) {
    vert_u = p[1].f;
    vert_v = p[2].f;
}


static pvr_poly_hdr_t user_clip = {
                                      PVR_CMD_USERCLIP, 0x00000000, 0x00000000, 0x00000000,
                                      0x00000000, 0x00000000, 0x00000000, 0x00000000
                                  };

INLINE void send_user_clip() {
    pvr_prim(&user_clip, sizeof(pvr_poly_hdr_t));
}
/* Setup the hardware user clip rectangle. It will be sent during glBegin.

   The minimum clip rectangle is a 32x32 area which is dependent on the tile
   size use by the tile accelerator. The PVR swithes off rendering to tiles
   outside or inside the defined rectangle dependant upon the 'clipmode'
bits
   in the polygon header.

   Clip rectangles therefore must have a size that is some multiple of 32.

   	glScissor(0, 0, 32, 32) allows only the 'tile' in the lower left
	hand corner of the screen to be modified and glScissor(0, 0, 0, 0)
	disallows modification to all 'tiles' on the screen.
*/
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    GLint minx, miny, maxx, maxy;

    assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
    assert((width >= 0) && (height >= 0));
    gl_scissor_x = x;
    gl_scissor_y = y;
    gl_scissor_width = CLAMP(width, 0, gl_screen_width);
    gl_scissor_height = CLAMP(height, 0, gl_screen_height);

    minx = gl_scissor_x;
    /* force the origin to the lower left-hand corner of the screen */
    miny = /**/(gl_screen_height - gl_scissor_height) - /**/ gl_scissor_y;
    maxx = (gl_scissor_width + minx);
    maxy = (gl_scissor_height + miny);

    /* load command structure while mapping screen coords to TA tiles */
    user_clip.d1 = CLAMP(minx/32, 0, gl_screen_width/32);
    user_clip.d2 = CLAMP(miny/32, 0, gl_screen_height/32);
    user_clip.d3 = CLAMP((maxx/32)-1, 0, gl_screen_width/32);
    user_clip.d4 = CLAMP((maxy/32)-1, 0, gl_screen_height/32);

    gl_scissor_dirty = GL_TRUE;
    gl_pbuf_submitted = GL_FALSE;
}

/* Ihhhh, include of a C file?! Yep, cause inline code of glopVertex etc */

#include "gloparray.c"
