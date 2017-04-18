/*
	Ninja Library
	
	COPYRIGHT (C) SEGA ENTERPRISES,LTD.
*/

#ifndef _NINJA_API_H_
#define _NINJA_API_H_


/*--------------------------------------*/
/*      Prototype                       */
/*--------------------------------------*/

/************************/
/*	System				*/
/************************/
void	njSetTextureMemorySize(Uint32 size );
void	njChangeTextureMemorySize(Uint32 size );
void	njSetVertexBuffer(Uint32 *buffer,Sint32 size);
void	njInitSystem( Int, Int, Int );
void	njInitVertexBuffer( Sint32 op, Sint32 om, Sint32 tp, Sint32 tm ,Sint32 pt);
Uint32	njInitVertexBufferMP( NJS_VERTEXBUFFER_INFO *pVBInfo );
void	njContinuePass( void );
void	njWaitVSync( void );
void    njRenderStart( void );
void	njFlipFrameBuffer( void );
void 	njSetEORFunction( void (*func)(void) );
void 	njSetEORCallBackFunction( void (*func)(void) );
void	njSetVSyncFunction( void (*func)(void) );
Uint32	njVersion( void );
void	njExitSystem( void );
void	njSetBackColor( Uint32 col1, Uint32 col2, Uint32 col3 );
void	njTextureFilterMode( Int mode );
void	njTextureClampMode( Int mode );
void	njTextureFlipMode( Int mode );
void	njMipmapAdjust( Int level );
void	njSuperSampleMode( Int mode );
void    njPolygonCullingSize( Float size );
void    njPolygonCullingMode( Int mode );
void    njColorBlendingMode( Int target, Int mode );
void    njSpecularMode( Int mode );
void    njAlphaMode( Int mode );
void    njIgnoreTextureAlphaMode( Int mode );
void    njTextureShadingMode( Int mode );
void    njSetCheapShadowMode( Int mode );
void	njUserClipping(Int mode ,NJS_POINT2 *p);
void    njGetSystemAttr(NJS_SYS_ATTR *attr);
void    njSetSystemAttr(NJS_SYS_ATTR *attr);
void    njStopDisplay(void);
void    njChangeSystem( Int mode, Int frame, Int count );
void 	njColorClampMode( Int mode );
void 	njSetColorClamp(Uint32 MaxARGB,Uint32 MinARGB );
void	njAdjustDisplay(Sint32 xadjust,Sint32 yadjust );
void	njSetBorderColor(Uint32 color );
void	njZBufferMode( Int mode );
void	njGetSystemInfo(NJS_SYSTEMINFO	*info);
void	njSetWaitVsyncCount(Int count);
void	njSetWaitVSyncFunction( void (*func)(void*) ,void *arg);

/************************/
/*	Draw				*/
/************************/
void	njDrawPolygon( NJS_POLYGON_VTX *polygon, Int count, Int trans );
void	njDrawTexture( NJS_TEXTURE_VTX *polygon, Int count, Int tex, Int flag );
void	njDrawTextureMemList( NJS_TEXTURE_VTX *polygon, Int count, Int tex, Int flag );
void	njDrawTextureH( NJS_TEXTUREH_VTX *polygon, Int count, Int tex, Int flag );

void	njDrawPolygon3DEx( NJS_POLYGON_VTX *p, Int count, Int trans );
void	njDrawPolygon3DExStart(Int trans);
void	njDrawPolygon3DExSetData( NJS_POLYGON_VTX *p, Int count);
void	njDrawPolygon3DExEnd(void);

void	njDrawTexture3DEx( NJS_TEXTURE_VTX *p, Int count, Int trans );
void	njDrawTexture3DExStart(Int trans);
void	njDrawTexture3DExSetData( NJS_TEXTURE_VTX *p, Int count);
void	njDrawTexture3DExEnd(void);

void	njDrawTexture3DHEx( NJS_TEXTUREH_VTX *p, Int count, Int trans );
void	njDrawTexture3DHExStart(Int trans);
void	njDrawTexture3DHExSetData( NJS_TEXTUREH_VTX *p, Int count);
void	njDrawTexture3DHExEnd(void);

void	njQuadTextureStart( Sint32 trans );
void	njQuadTextureEnd( void );
void	njSetQuadTexture( Sint32 texid, Uint32 col );
void	njSetQuadTextureG( Sint32 gid, Uint32 col );
void	njSetQuadTextureColor( Uint32 col );
void	njDrawQuadTexture( NJS_QUAD_TEXTURE *q, Float z );
void	njDrawQuadTextureEx( NJS_QUAD_TEXTURE_EX *q );

/************************/
/*	Model				*/
/************************/
void	njInit3D( NJS_VERTEX_BUF *vbuf, Int vn );
void	njDrawModel( NJS_MODEL *model );
void	njDrawObject( NJS_OBJECT *obj );
void	njFastDrawModel( NJS_MODEL *model );
void	njFastDrawObject( NJS_OBJECT *obj );
void	njSimpleDrawModel( NJS_MODEL *model );
void	njSimpleDrawObject( NJS_OBJECT *obj );
void	njControl3D( Uint32 flag );
void	njSetConstantAttr( Uint32 and_attr, Uint32 or_attr );
void	njSetConstantMaterial( NJS_ARGB *mat );
void	njSetDepthQueue( Float dnear, Float dfar );

void	njEasyDrawModel( NJS_MODEL *model );
void	njEasyDrawObject( NJS_OBJECT *obj );
void	njSetEasyLight( Float x,Float y,Float z );
void	njSetEasyLightIntensity( Float inten, Float ambient );
void	njSetEasyLightColor( Float r,Float g,Float b );

/************************/
/*	Motion				*/
/************************/
void	njAction( NJS_ACTION *action, Float frame );
void	njDrawMotion( NJS_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njFastAction( NJS_ACTION *action, Float frame );
void	njFastDrawMotion( NJS_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njSimpleAction( NJS_ACTION *action, Float frame );
void	njSimpleDrawMotion( NJS_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njEasyAction( NJS_ACTION *action, Float frame );
void	njEasyDrawMotion( NJS_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njSetMotionCallback( void (*func)(NJS_OBJECT *obj) );

void	njCnkDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkSimpleDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkSimpleMultiDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkEasyDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkEasyMultiDrawMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkDrawMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkSimpleDrawMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkSimpleMultiDrawMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkEasyDrawMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkEasyMultiDrawMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njCnkSetMotionCallback( void (*func)(NJS_CNK_OBJECT *cnkobj) );

void	njActionLink( NJS_ACTION_LINK *actionlink, Float frame );
void	njDrawMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njFastActionLink( NJS_ACTION_LINK *actionlink, Float frame );
void	njFastDrawMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njSimpleActionLink( NJS_ACTION_LINK *actionlink, Float frame );
void	njSimpleDrawMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njEasyActionLink( NJS_ACTION_LINK *actionlink, Float frame );
void	njEasyDrawMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );

void	njInitShape(Float *buf);
void	njDrawShapeMotion( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njDrawShapeMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njFastDrawShapeMotion( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njFastDrawShapeMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njSimpleDrawShapeMotion( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njSimpleDrawShapeMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njEasyDrawShapeMotion( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njEasyDrawShapeMotionLink( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );

void	njActionOld( NJS_ACTION *action, Float frame );
void	njDrawMotionOld( NJS_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njFastActionOld( NJS_ACTION *action, Float frame );
void	njFastDrawMotionOld( NJS_OBJECT *object, NJS_MOTION *motion, Float frame );
void	njSimpleActionOld( NJS_ACTION *action, Float frame );
void	njSimpleDrawMotionOld( NJS_OBJECT *object, NJS_MOTION *motion, Float frame );

void	njActionLinkOld( NJS_ACTION_LINK *actionlink, Float frame );
void	njDrawMotionLinkOld( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njFastActionLinkOld( NJS_ACTION_LINK *actionlink, Float frame );
void	njFastDrawMotionLinkOld( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njSimpleActionLinkOld( NJS_ACTION_LINK *actionlink, Float frame );
void	njSimpleDrawMotionLinkOld( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );

void	njDrawShapeMotionOld( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njDrawShapeMotionLinkOld( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njFastDrawShapeMotionOld( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njFastDrawShapeMotionLinkOld( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njSimpleDrawShapeMotionOld( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njSimpleDrawShapeMotionLinkOld( NJS_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );

void	njMotionTransform( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionTransformZXY( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionTranslate( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionRotateXYZ( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionRotateZXY( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionScale( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njGetMotionTranslate( Float *pos, Int spline_flag );
void	njGetMotionRotate( Angle *ang, Int spline_flag );
void	njGetMotionScale( Float *scl, Int spline_flag );
void	njSetNextMotionNode( void );
void	njSetCurrentMotion(NJS_MOTION *motion, Float frame );
void	njMotionTransformOld( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionTransformZXYOld( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionRotateXYZOld( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njMotionRotateZXYOld( NJS_MATRIX *m, NJS_OBJECT *obj, Int spline_flag );
void	njGetMotionRotateOld( Angle *ang, Int spline_flag );

Int		njCnkGetShape(NJS_CNK_OBJECT *cnkobj, Float *buffer, Int spline_flag);
void	njCnkSetCurrentShape(NJS_MOTION *shape, Int type, Float frame );

void	njLightAction( NJS_LACTION *laction, Float frame );
void	njLightMotion( NJS_LIGHT *light, NJS_MOTION *motion, Float frame );
void	njCameraAction(NJS_CACTION *caction, Float frame );
void	njCameraMotion(NJS_CAMERA *camera, NJS_MOTION *motion, Float frame );

void	njCameraMotionOld(NJS_CAMERA *camera, NJS_MOTION *motion, Float frame );
void	njCameraActionOld(NJS_CACTION *caction, Float frame );

void	njGetAction( NJS_ACTION *action, NJS_MOTION_DATA *data, Float frame );
void	njGetDrawMotion( NJS_OBJECT *object, NJS_MOTION *motion, NJS_MOTION_DATA *data, Float frame );

void	njCnkDrawShapeMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkDrawShapeMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkSimpleDrawShapeMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkSimpleDrawShapeMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkEasyDrawShapeMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkEasyDrawShapeMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkSimpleMultiDrawShapeMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkSimpleMultiDrawShapeMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkEasyMultiDrawShapeMotion( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );
void	njCnkEasyMultiDrawShapeMotionOld( NJS_CNK_OBJECT *object, NJS_MOTION *motion, NJS_MOTION *shape, Float frame );

void	njCnkDrawMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkDrawShapeMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkSimpleDrawMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkSimpleDrawShapeMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkEasyDrawMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkEasyDrawShapeMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkSimpleMultiDrawMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkSimpleMultiDrawShapeMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkEasyMultiDrawMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkEasyMultiDrawShapeMotionLink( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );

void	njCnkDrawMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkDrawShapeMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkSimpleDrawMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkSimpleDrawShapeMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkEasyDrawMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkEasyDrawShapeMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkSimpleMultiDrawMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkSimpleMultiDrawShapeMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );
void	njCnkEasyMultiDrawMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, Float frame );
void	njCnkEasyMultiDrawShapeMotionLinkOld( NJS_CNK_OBJECT *object, NJS_MOTION_LINK *motionlink, NJS_MOTION_LINK *shapelink, Float frame );

void	njSetCnkCurrentMotion(NJS_MOTION *motion, Float frame );
void	njCnkMotionTransform( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njCnkMotionTransformZXY( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njCnkMotionTransformQuaternion( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njCnkMotionTranslate( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njCnkMotionRotateXYZ( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njCnkMotionRotateZXY( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njCnkMotionQuaternion( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njCnkMotionScale( NJS_MATRIX *m, NJS_CNK_OBJECT *obj, Int spline_flag );
void	njGetCnkMotionTranslate( Float *pos, Int spline_flag );
void	njGetCnkMotionRotate( Angle *ang, Int spline_flag );
void	njGetCnkMotionQuaternion( NJS_QUATERNION *qua, Int spline_flag );
void	njGetCnkMotionScale( Float *scl, Int spline_flag );
void	njSetCnkNextMotionNode( void );

void	njGetCameraAction( NJS_CACTION *caction, NJS_CMOTION_DATA *data, Float frame );
void	njGetCameraMotion( NJS_CAMERA *camera,NJS_MOTION *motion, NJS_CMOTION_DATA *data, Float frame );

void	njGetLightAction( NJS_LACTION *laction, NJS_LMOTION_DATA *data,Float frame );
void	njGetLightMotion( NJS_LIGHT *light, NJS_MOTION *motion, NJS_LMOTION_DATA *data, Float frame );

/************************/
/*	Memory				*/
/************************/
void	njMemCopy(  void *dst, const void *src, Sint32 num );
void	njMemCopy2( void *dst, const void *src, Sint32 num );
void	njMemCopy4( void *dst, const void *src, Sint32 num );
void	njMemCopy8( void *dst, const void *src, Sint32 num );
void	njMemCopy16( void *dst, const void *src, Sint32 num );
void	njMemCopy32( void *dst, const void *src, Sint32 num );
void	njMemCopySQ( void *dst, const void *src, Sint32 num );

/************************/
/*	 Malloc Funcion		*/
/************************/
void	*njMalloc(unsigned nbytes);
void	njFree(void *ap);

/************************/
/*	Draw2D				*/
/************************/

void	njDrawPoint2D(NJS_POINT2COL *p, Int n, Float pri, Uint32 attr);
void	njDrawLine2D(NJS_POINT2COL *p, Int n, Float pri, Uint32 attr);
void	njDrawTriangle2D(NJS_POINT2COL *p, Int n, Float pri, Uint32 attr);
void	njDrawPolygon2D(NJS_POINT2COL *p, Int n, Float pri, Uint32 attr);
void	njDrawCircle2D(NJS_POINT2COL *p, Int n, Float pri, Uint32 attr);

/************************/
/*	Math				*/
/************************/

#if 0
#define	njAbs(n) ((Float)fabs((Double)(n)))
#define njArcCos(n) (NJM_RAD_ANG(acos((Double)(n))))
#define njArcCosec(n) (NJM_RAD_ANG(asin(1.0/(Double)(n))))
#define njArcCot(n) (NJM_RAD_ANG(atan(1.0/(Double)(n))))
#define njArcSec(n) (NJM_RAD_ANG(acos(1.0/(Double)(n))))
#define njArcSin(n) (NJM_RAD_ANG(asin((Double)(n))))
#define njArcTan(n) (NJM_RAD_ANG(atan((Double)(n))))
#define njArcTan2(y,x) (NJM_RAD_ANG(atan2((Double)(y),(Double)(x))))
#define njCeil(n) ((Float)ceil((Double)(n)))
#define njCosech(n) ((Float)(1.0 / sinh((Double)NJM_ANG_RAD(n))))
#define njCosh(n) ((Float)cosh((Double)NJM_ANG_RAD(n)))
#define njCoth(n) ((Float)(1.0 / tanh((Double)NJM_ANG_RAD(n))))
#define njFloor(n) ((Float)floor((Double)(n)))
#define njInvertSqrt(n) (Float)(1.0 / njSqrt(n))
#define njLog(n) ((Float)log((Double)(n)))
#define njLog10(n) ((Float)log10((Double)(n)))
#define njLog2(n) (njLog(n) / njLog(2.f))
#define njPow(n1,n2) ((Float)pow((Double)(n1), (Double)(n2)))
#define njSech(n) ((Float)(1.0 / cosh((Double)NJM_ANG_RAD(n))))
#define njSinh(n) ((Float)sinh((Double)NJM_ANG_RAD(n)))
#define njTanh(n) ((Float)tanh((Double)NJM_ANG_RAD(n)))
#define njHypot(x,y) (njSqrt((x) * (x) + (y) * (y)))
#define njExp(x) ((Float)exp(x))
#define njRandomSeed(n)	(srand(n))

Float	njCos(Angle n);
Float	njCosec(Angle n);
Float	njCot(Angle n);
Float	njFraction(Float n);
Float	njRandom(void);
Float	njRoundOff(Float n);
Float	njRoundUp(Float n);
Float	njSec(Angle n);
Float	njSin(Angle n);
Float	njSqrt(Float n);
Float	njTan(Angle n);

#else
#define njAbs(n)         ((Float)fabsf   ((Float)(n)))
#define njArcCos(n)      ((Angle)NJM_RAD_ANG(acosf  ((Float)(n)) ))
#define njArcCosec(n)    ((Angle)NJM_RAD_ANG(asinf  (1.0f/(Float)(n)) ))
#define njArcCot(n)      ((Angle)NJM_RAD_ANG(atanf  (1.0f/(Float)(n)) ))
#define njArcSec(n)      ((Angle)NJM_RAD_ANG(acosf  (1.0f/(Float)(n)) ))
#define njArcSin(n)      ((Angle)NJM_RAD_ANG(asinf  ((Float)(n)) ))
#define njArcTan(n)      ((Angle)NJM_RAD_ANG(atanf  ((Float)(n)) ))
#define njArcTan2(y,x)   ((Angle)NJM_RAD_ANG(atan2f ((Float)(y),(Float)(x)) ))

#define njCeil(n)        ((Float)ceilf   ((Float)(n)))
#define njCosech(n)      ((Float)( 1.0f / sinhf((Float)NJM_ANG_RAD(n)) ))
#define njCosh(n)        ((Float)coshf   ((Float)NJM_ANG_RAD(n)))
#define njCoth(n)        ((Float)( 1.0f / tanhf((Float)NJM_ANG_RAD(n)) ))
#define njExp(x)         ((Float)expf((x)))
#define njFloor(n)       ((Float)floorf  ((Float)(n)))
#define njHypot(x,y)     ((Float)njSqrt  ( (x)*(x) + (y)*(y) ))
#define njLog(n)         ((Float)logf    ((Float)(n)))
#define njLog10(n)       ((Float)log10f  ((Float)(n)))
#define njLog2(n)        ((Float)( njLog((n)) / njLog(2.f) ))
#define njPow(n1,n2)     ((Float)powf    ((Float)(n1),(Float)(n2)))
#define njSech(n)        ((Float)( 1.0 / coshf((Float)NJM_ANG_RAD(n)) ))
#define njSinh(n)        ((Float)sinhf   ((Float)NJM_ANG_RAD(n)))
#define njTanh(n)        ((Float)tanhf   ((Float)NJM_ANG_RAD(n)))
#define njRandom()       ((Float)((Float)rand()/(Float)(RAND_MAX+1)))
#define njRandomSeed(n)  (srand((Uint32)(n)))

Float	njCos       (Angle n);
Float	njCosec     (Angle n);
Float	njCot       (Angle n);
Float	njFraction  (Float n);
Float	njInvertSqrt(Float n);
Float	njRoundOff  (Float n);
Float	njRoundUp   (Float n);
Float	njSec       (Angle n);
Float	njSin       (Angle n);
Float	njSqrt      (Float n);
Float	njTan       (Angle n);

#endif

Int		njCombination(Int n, Int k);
void	njLinear(Float *idata, Float *odata, NJS_SPLINE *attr, Float frame);
void	njHermiteSpline(Float *idata, Float *odata, NJS_SPLINE *attr, Float frame);
void	njCardinalSpline(Float *idata, Float *odata, NJS_SPLINE *attr, Float frame);
void	njOverhauserSpline(Float *idata, Float *odata, NJS_SPLINE *attr, Float frame);
void	njKochanekSpline(Float *idata, Float *odata, NJS_SPLINE *attr, Float frame);
void	njCubicBezierSpline(Float *idata, Float *odata, NJS_SPLINE *attr, Float frame);
void	njBezierSpline(Float *idata, Float *odata, NJS_SPLINE *attr, Float frame);

/************************/
/*	Matrix				*/
/************************/

void	njInitMatrix(NJS_MATRIX *m, Sint32 n, Int flag);
void	njCalcPoints(NJS_MATRIX *m, NJS_POINT3 *ps, NJS_POINT3 *pd, Int num);
void	njCalcVectors(NJS_MATRIX *m, NJS_VECTOR *vs, NJS_VECTOR *vd, Int num);
void    njGetTranslation(NJS_MATRIX *m, NJS_POINT3 *p);
void    njUnitTransPortion(NJS_MATRIX *m);
void    njUnitRotPortion(NJS_MATRIX *m);
void    njClearMatrix(void);
Bool	njPushMatrix(NJS_MATRIX *m);
Bool	njPopMatrix(Uint32 n);
void	njUnitMatrix(NJS_MATRIX *m);
void	njSetMatrix(NJS_MATRIX *md, NJS_MATRIX *ms);
void	njGetMatrix(NJS_MATRIX *m);
void	njAddMatrix(NJS_MATRIX *md, NJS_MATRIX *ms);
void	njSubMatrix(NJS_MATRIX *md, NJS_MATRIX *ms);
void	njMultiMatrix(NJS_MATRIX *md, NJS_MATRIX *ms);
void	njTranslate(NJS_MATRIX *m, Float x, Float y, Float z);
void	njTranslateV(NJS_MATRIX *m, NJS_VECTOR *v);
void	njRotateX(NJS_MATRIX *m, Angle ang);
void	njRotateY(NJS_MATRIX *m, Angle ang);
void	njRotateZ(NJS_MATRIX *m, Angle ang);
void	njRotateXYZ(NJS_MATRIX *m, Angle angx, Angle angy, Angle angz);
void	njRotateZXY(NJS_MATRIX *m, Angle angx, Angle angy, Angle angz);
void	njRotate(NJS_MATRIX *m, NJS_VECTOR *v, Angle ang);
void	njScale(NJS_MATRIX *m, Float sx, Float sy, Float sz);
void	njScaleV(NJS_MATRIX *m, NJS_VECTOR *v);
Bool	njInvertMatrix(NJS_MATRIX *m);
void	njTransposeMatrix(NJS_MATRIX *m);
Float	njDetMatrix(NJS_MATRIX *m);
void	njResMatrix(NJS_MATRIX *m, Angle *ang,NJS_VECTOR *scale,NJS_VECTOR *trans);
void	njProject(NJS_MATRIX *m,NJS_PLANE *pl);
void    njProject2(NJS_MATRIX *m, NJS_PLANE *pl, NJS_POINT3 *v, NJS_POINT3*p);
void	njMirror(NJS_MATRIX *m,NJS_PLANE *pl);

void	njCalcPoint(NJS_MATRIX *m, NJS_POINT3 *ps, NJS_POINT3 *pd);
void	njAddVector(NJS_VECTOR *vd, NJS_VECTOR *vs);
void	njSubVector(NJS_VECTOR *vd, NJS_VECTOR *vs);
void	njCalcVector(NJS_MATRIX *m, NJS_VECTOR *vs, NJS_VECTOR *vd);
Float	njUnitVector(NJS_VECTOR *v);
Float	njScalor(NJS_VECTOR *v);
Float	njScalor2(NJS_VECTOR *v);
void	njProjectScreen(NJS_MATRIX *m, NJS_POINT3 *p3, NJS_POINT2 *p2);
Float	njOuterProduct(NJS_VECTOR *v1, NJS_VECTOR *v2, NJS_VECTOR *ov);
Float	njInnerProduct(NJS_VECTOR *v1, NJS_VECTOR *v2);

/************************/
/*	 Matrix Ex Funcion  */
/************************/
void njTranslateEx(NJS_VECTOR *v);
void njRotateEx( Angle *ang, Sint32 lv );
void njScaleEx(NJS_VECTOR *v);
Bool njPushMatrixEx( void );
Bool njPopMatrixEx( void );
void njQuaternionEx(NJS_QUATERNION *qua);

/************************/
/*	Collision   		*/
/************************/

Bool	njIsParalellL2L(NJS_LINE *l1, NJS_LINE *l2);
Bool	njIsParalellL2PL(NJS_LINE *l, NJS_PLANE *pl);
Bool	njIsParalellPL2PL(NJS_PLANE *pl1, NJS_PLANE *pl2);
Float	njDistanceP2P(NJS_POINT3 *p1, NJS_POINT3 *p2);
Float	njDistanceP2L(NJS_POINT3 *p, NJS_LINE *l, NJS_POINT3 *cp);
Float	njDistanceP2PL(NJS_POINT3 *p, NJS_PLANE *pl, NJS_POINT3 *cp);
Float	njDistanceL2L(NJS_LINE *l1, NJS_LINE *l2, NJS_POINT3 *cp1, NJS_POINT3 *cp2);
Float	njDistanceL2PL(NJS_LINE *l, NJS_PLANE *pl, NJS_POINT3 *cp);
Float	njDistancePL2PL(NJS_PLANE *pl1, NJS_PLANE *pl2, NJS_LINE *l);
void	njGetPlaneNormal(NJS_POINT3 *p, NJS_VECTOR *v);
void	njGetPlaneNormal2(NJS_POINT3 *p0, NJS_POINT3 *p1, NJS_POINT3 *p2, NJS_VECTOR *v);
Int     njCollisionCheckBB(NJS_BOX *h1, NJS_BOX *h2);
Int     njCollisionCheckSS(NJS_SPHERE *sphere1, NJS_SPHERE *sphere2);
Int     njCollisionCheckCC(NJS_CAPSULE *h1, NJS_CAPSULE *h2);
Int     njCollisionCheckSC(NJS_SPHERE *sphere, NJS_CAPSULE *capsule);
Int     njCollisionCheckBS(NJS_BOX *box, NJS_SPHERE *sphere);
Int     njCollisionCheckBC(NJS_BOX *box, NJS_CAPSULE *capsule);


/************************/
/*	View				*/
/************************/

void    njSetScreen(NJS_SCREEN *s);
void    njSetScreenDist(Float dist);
void	njSetPerspective(Angle ang);
void    njSetAspect(Float ax, Float ay);
void    njInitView(NJS_VIEW *v);
void    njSetView(NJS_VIEW *v);
/* çÌèúó\íË */
void    njUnitViewMatrix(NJS_VIEW *v);
void    njMultiViewMatrix(NJS_VIEW *v, NJS_MATRIX *m);
void    njRotateViewX(NJS_VIEW *v, Angle ang);
void    njRotateViewY(NJS_VIEW *v, Angle ang);
void    njRotateViewZ(NJS_VIEW *v, Angle ang);
void    njRotateViewXYZ(NJS_VIEW *v, Angle ax, Angle ay, Angle az);
void    njTranslateView(NJS_VIEW *v, Float x, Float y, Float z);
void    njTranslateViewV(NJS_VIEW *v, NJS_POINT3 *p);
/* Ç±Ç±Ç‹Ç≈ */
void    njRotateViewXRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewYRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewZRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewXYZRelative(NJS_VIEW *v, Angle ax, Angle ay, Angle az);
void    njTranslateViewRelative(NJS_VIEW *v, Float x, Float y, Float z);
void    njTranslateViewVRelative(NJS_VIEW *v, NJS_POINT3 *p);
void    njForwardViewRelative(NJS_VIEW *v, Float x);
void    njRotateViewXAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewYAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewZAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewXYZAbsolute(NJS_VIEW *v, Angle ax, Angle ay, Angle az);
void    njTranslateViewAbsolute(NJS_VIEW *v, Float x, Float y, Float z);
void    njTranslateViewVAbsolute(NJS_VIEW *v, NJS_POINT3 *p);
void    njForwardViewAbsolute(NJS_VIEW *v, Float x);
void    njSetBaseView(NJS_VIEW *v);
void    njReturn2BaseView(NJS_VIEW *v);
void	njLookAtView(NJS_VIEW *v, Float x, Float y, Float z);
void	njLookAtViewV(NJS_VIEW *v, NJS_POINT3 *p);
void    njClip2D(NJS_POINT2 *v);
void    njClipZ(Float n, Float f);
int     njCalcScreen(NJS_POINT3 *p, Float *sx, Float *sy);
void    njRotateViewPosXRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewPosYRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewPosZRelative(NJS_VIEW *v, Angle ang);
void    njRotateViewPosXAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewPosYAbsolute(NJS_VIEW *v, Angle ang);
void    njRotateViewPosZAbsolute(NJS_VIEW *v, Angle ang);
void    njUnitViewVector(NJS_VIEW *v);

/************************/
/*	Graphics3D			*/
/************************/

void    njDrawPoint3D(NJS_POINT3COL *p, Int n, Uint32 attr);
void    njDrawLine3D(NJS_POINT3COL *p, Int n, Uint32 attr);
void    njDrawTriangle3D(NJS_POINT3COL *p, Int n, Uint32 attr);
void    njDrawPolygon3D(NJS_POINT3COL *p, Int n, Uint32 attr);

/************************/
/*	 Light Funcion		*/
/************************/
void	njCreateLight(NJS_LIGHT_PTR, Int);
void	njDeleteLight(NJS_LIGHT_PTR);
void	njLightOn(NJS_LIGHT_PTR);
void	njLightOff(NJS_LIGHT_PTR);
void	njSetLight(NJS_LIGHT_PTR);

void	njSetLightLocation(NJS_LIGHT_PTR, Float, Float, Float);
void	njSetLightDirection(NJS_LIGHT_PTR, Float, Float, Float);
void	njSetLightColor(NJS_LIGHT_PTR, Float, Float, Float);
void	njSetLightAlpha(NJS_LIGHT_PTR, Float);
void	njSetLightIntensity(NJS_LIGHT_PTR, Float, Float, Float);
void	njSetLightAngle(NJS_LIGHT_PTR, Angle, Angle);
void	njSetLightRange(NJS_LIGHT_PTR, Float, Float);
void	njSetUserLight(NJS_LIGHT_PTR, NJF_LIGHT_FUNC);

void	njMultiLightMatrix(NJS_LIGHT_PTR, NJS_MATRIX*);
void	njRotateLightXYZ(NJS_LIGHT_PTR, Angle, Angle, Angle);
void	njRotateLightX(NJS_LIGHT_PTR, Angle);
void	njRotateLightY(NJS_LIGHT_PTR, Angle);
void	njRotateLightZ(NJS_LIGHT_PTR, Angle);
void	njTranslateLightV(NJS_LIGHT_PTR, NJS_VECTOR*);
void	njTranslateLight(NJS_LIGHT_PTR, Float, Float, Float);
void	njUnitLightMatrix(NJS_LIGHT_PTR);

void	njDeleteAllLight(void);
void	njLightAllOff(void);
void	njLightAllOn(void);

void    njCnkSetAmbient(Float r, Float g, Float b);

/************************/
/*	 Texture Funcion	*/
/************************/
void	njInitTextureBuffer(Sint8 *addr,Uint32 size);
void	njInitTexture(NJS_TEXMEMLIST *addr,Uint32 n);
void	njInitTextureGlobalIndex(Uint32 globalIndex);
void	njExitTexture(void);
void	njInitCacheTextureBuffer(Sint8 *addr,Uint32 size);
Sint32	njLoadTexture(NJS_TEXLIST *texlist);
Sint32	njLoadTextureNum(Uint32 n);
Sint32	njSetTexture(NJS_TEXLIST *texlist);
Sint32	njSetTextureNum(Uint32 n);
Sint32	njSetTextureNumG(Uint32 globalIndex);
Uint32	njGetTextureNumG(void);
void	njReleaseTextureAll(void);
Sint32	njReleaseTexture(NJS_TEXLIST *texlist);
Sint32	njReleaseTextureNum(Uint32 n);
Sint32	njReleaseTextureNumG(Uint32 globalIndex);
void	njReleaseCacheTextureAll(void);
Sint32	njReleaseCacheTextureNum(Uint32 n);
Sint32	njReleaseCacheTextureNumG(Uint32 globalIndex);
Uint32	njCalcTexture(Uint32 flag);
Sint32	njLoadCacheTexture(NJS_TEXLIST *texlist);
Sint32	njLoadCacheTextureNum(Uint32 n);
Sint32	njLoadCacheTextureNumG(Uint32 globalIndex);
void	njSetTexturePath(const char *path);
void	njSetTextureInfo(NJS_TEXINFO *info,Uint16 *tex,Sint32 Type,Sint32 nWidth,Sint32 nHeight);
void	njSetTextureName(NJS_TEXNAME *texname,void *addr,Uint32 globalIndex,Uint32 attr);
Sint32	njReLoadTextureNum(Uint32 n,void *texaddr,Uint32 attr,Uint32 lod);
Sint32	njReLoadTextureNumG(Uint32 globalIndex,void *texaddr,Uint32 attr,Uint32 lod);
void	njRenderTextureNum(Uint32 n);
void	njRenderTextureNumG(Uint32 globalIndex);
void	njSetRenderWidth(Uint32 nWidth);
void	njFrameBufferBmp(char *bmp,char *buffer);
void	njSetPvmTextureList(NJS_TEXLIST *texlist,NJS_TEXNAME *texname,char *filename,Sint32 size);
Sint32	njLoadTexturePvmFile(const char *filename,NJS_TEXLIST *texlist);
Sint32 	njLoadTexturePvmMemory(Uint8 *addr,NJS_TEXLIST *texlist);
void 	njSetPaletteBankNum(Uint32 n,Sint32 bank);
void 	njSetPaletteBankNumG(Uint32 globalIndex,Sint32 bank);
void 	njSetPaletteMode(Uint32 mode);
Uint32	njGetPaletteMode(void);
void 	njSetPaletteData(Sint32 offset,Sint32 count,void* data);
void	njGetPaletteData(Sint32 offset,Sint32 count,void* data);
Sint32 	njLoadPaletteFile(const char *filename,NJS_TEXPALETTE *pl);
Sint32 	njReLoadVQCodebookNum(Uint32 n,void *texaddr,Uint32 attr);
Sint32 	njReLoadVQCodebookNumG(Uint32 globalIndex,void *texaddr,Uint32 attr);
void 	njTwiddledTexture(Sint16 *dst,Sint16* src,Sint32 size);
Sint32	njReLoadRectangleTexturePartNum(Uint32 n,void *texaddr,Uint32 attr,Uint32 *p);
Sint32	njReLoadRectangleTexturePartNumG(Uint32 globalIndex,void *texaddr,Uint32 attr,Uint32 *p);
Sint32	njReLoadTexturePartNum(Uint32 n,Sint8 *addr,Uint32 offset,Uint32 size);
Sint32	njReLoadTexturePartNumG(Uint32 globalIndex,Sint8 *addr,Uint32 offset,Uint32 size);
Sint32	njLoadTextureReq(NJS_TEXLIST *texlist);
Sint32	njLoadTextureReqStop(void);
void	njSetSizeYUV420(Uint32 nWidth,Uint32 nHeight);
Sint32	njLoadTextureYUV420Num(Uint32 n,Uint32 *data);
Sint32	njLoadTextureYUV420NumG(Uint32 globalIndex,Uint32 *data);
void	njGarbageTexture(NJS_TEXMEMLIST *addr,Uint32 n);
NJS_TEXERRSTAT *njGetTextureErrStat(void);
Sint32	njReadTextureNum(Uint32 n,Sint8 *addr);
Sint32	njReadTextureNumG(Uint32 globalIndex,Sint8 *addr);
Sint32	njReadTexturePartNum(Uint32 n,Sint8 *addr,Uint32 offset,Uint32 size);
Sint32	njReadTexturePartNumG(Uint32 globalIndex,Sint8 *addr,Uint32 offset,Uint32 size);

Uint32	njCalcTextureSize(Uint32 nWidth,Uint32 nHeight,Uint32 nTextureType);
void	njSetTextureParam(NJS_TEXMEMLIST *texmemlist);

Uint32 *njLoadPvrHeader(NJS_PVRHEADERDATA *pvrh,Uint32 *globalIndex,Uint32 *pTexture);
Sint32 njGetTexSurface(NJS_TEXMEMLIST* texmemlist,NJS_PVRHEADERDATA *pvrh);
Sint32 njLoadTexturePartLow(NJS_TEXMEMLIST* texmemlist,Uint32 *pTexture,Uint32 offset,Uint32 size);
Sint32 njLoadTexturePartLowOld(NJS_TEXMEMLIST* texmemlist,Uint32 *pTexture,Uint32 offset,Uint32 size);
Sint32 njReleaseTextureLow(NJS_TEXMEMLIST* texmemlist);
Sint32 njLoadTextureFinishDMA(void);
Sint32 njReadTexturePartLow(NJS_TEXMEMLIST* texmemlist,Uint32 *pTexture,Uint32 offset,Uint32 size);

Sint32 njReadRectangleTexturePartNum(Uint32 n,void *texaddr,Uint32 *p);
Sint32 njReadRectangleTexturePartNumG(Uint32 globalIndex,void *texaddr,Uint32 *p);
Sint32 njLoadTextureSetG(NJS_TEXLIST *texlist);

/************************/
/*	 Scroll Funcion		*/
/************************/
void	njDrawScroll(NJS_SCROLL *scl);


/************************/
/*	 Debug Font Funcion	*/
/************************/
void 	njInitPrint(Uint32 *texture,Uint32 size,Uint32 attr);
void 	njExitPrint(void);
void	njPrintSize(Uint16 size);
void	njPrintColor(Uint32 c);
void	njPrintC(Int loc,const char *s);
void	njPrintD(Int loc,Int val,Int digit);
void	njPrintB(Int loc,Uint32 val,Int digit);
void	njPrintH(Int loc,Uint32 val,Int digit);
void	njPrintF(Int loc,Float val,Int digit);
void	njPrint(Int loc,const char *fmt, ...);

/************************/
/*	 Sprite				*/
/************************/
void	njDrawSprite2D( NJS_SPRITE *sp, Int n, Float pri, Uint32 attr );
void	njDrawSprite3D( NJS_SPRITE *sp, Int n, Uint32 attr );

/************************/
/*	 Fog				*/
/************************/
void	njFogEnable(void);
void	njFogDisable(void);
void	njSetFogDensity(Uint32 density);
void	njSetFogColor(Uint32 c);
void	njSetFogTable(NJS_FOG_TABLE fog);
void	njGenerateFogTable(NJS_FOG_TABLE fog);
void	njGenerateFogTable2(NJS_FOG_TABLE fog, Float f);
void	njGenerateFogTable3(NJS_FOG_TABLE fog, Float n, Float f);
Uint32	njGenerateFogDensity(Float f);

/************************/
/*	 Fade				*/
/************************/
void	njFadeEnable(void);
void	njFadeDisable(void);
void	njSetFadeColor(Uint32 c);
void	njExecuteFade(Float f);

/************************/
/*	 Camera				*/
/************************/
void	njForwardCameraPosition(NJS_CAMERA *c, Float x);
void	njInitCamera(NJS_CAMERA *c);
void	njPitchCameraInterest(NJS_CAMERA *c, Angle ang);
void	njPointCameraInterest( NJS_CAMERA*, float, float, float );
void	njRollCameraInterest( NJS_CAMERA*, Angle );
void	njRotateCameraPositionX(NJS_CAMERA *c, Angle ang);
void	njRotateCameraPositionXYZ(NJS_CAMERA *c, Angle ax, Angle ay, Angle az);
void	njRotateCameraPositionY(NJS_CAMERA *c, Angle ang);
void	njRotateCameraPositionZ(NJS_CAMERA *c, Angle ang);
void	njSetCameraDepth(NJS_CAMERA *c, Float n, Float f);
void	njSetCameraAngle( NJS_CAMERA*, Angle );
void	njSetCamera( NJS_CAMERA* );
void	njTranslateCameraPosition(NJS_CAMERA *c, Float x, Float y, Float z);
void	njYawCameraInterest(NJS_CAMERA *c, Angle ang);

/************************/
/*	 Binary				*/
/************************/
Sint8	*njOpenBinary(const char *fname);
void	njCloseBinary(Sint8 *wbuff);
void	*njReadBinary(Sint8 *wbuff, Uint32 *fpos, Uint32 *ptype);

#endif /* _NINJA_API_H_ */
