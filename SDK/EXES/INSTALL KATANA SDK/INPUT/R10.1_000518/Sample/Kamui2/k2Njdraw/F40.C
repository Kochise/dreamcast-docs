
/* NJA 0.78alpha1 NinjaAsciiDataMix (SI) */

/* ROOT OBJECT : object_F40_GTE_sh_null1_1_null1_1 n(50) d(4) */
/* TEXLIST     : texlist_F40_GTE_sh_null1_1 n(33) */

#include <kamui2.h>
#include "model.h"
#include "nd.h"

TEXTURE_START

TEXTURENAME textures_F40_GTE_sh_null1_1[]
START
	TEXN( "tier_patarnb" ),    /* 20990 1024x128 565 RE */
	TEXN( "tier_sidea" ),      /* 20991 128x128 565 TW MIP */
	TEXN( "f4e_wheela" ),      /* 20992 128x128 4444 TW MIP */
	TEXN( "f4e_wheel" ),       /* 20993 128x128 565 TW MIP */
	TEXN( "tier_patarn" ),     /* 20994 128x128 565 TW MIP */
	TEXN( "recaro" ),          /* 20995 64x128 565 RE */
	TEXN( "recaro_b" ),        /* 20996 64x128 565 RE */
	TEXN( "tex_f1_ramp2" ),    /* 20997 64x64 565 TW MIP */
	TEXN( "car_mesh3" ),       /* 20998 32x32 565 TW MIP */
	TEXN( "f40_engine" ),      /* 999 64x64 4444 RE */
	TEXN( "GRAD_METAL" ),      /* 21000 32x32 565 TW MIP */
	TEXN( "f40_i_cooler" ),    /* 21001 64x64 565 TW MIP */
	TEXN( "GRAD_METAL00" ),    /* 21002 32x32 565 TW MIP */
	TEXN( "mcl_h_light1_on" ), /* 21003 128x64 565 RE */
	TEXN( "igolb" ),           /* 21004 128x32 1555 RE */
	TEXN( "igolw" ),           /* 21005 128x32 1555 RE */
	TEXN( "leaseplan_logo" ),  /* 21006 256x32 565 RE */
	TEXN( "fer_emblem_sy" ),   /* 21007 64x64 4444 TW MIP */
	TEXN( "fer_emblem_fa" ),   /* 21008 64x64 1555 TW MIP */
	TEXN( "fer_emblem_sb" ),   /* 21009 64x64 4444 TW MIP */
	TEXN( "f40_number" ),      /* 21010 64x64 565 TW MIP */
	TEXN( "bpr_logo" ),        /* 21011 128x32 565 RE */
	TEXN( "f40_rearend" ),     /* 21012 256x128 565 RE */
	TEXN( "f40_locka" ),       /* 21013 32x64 565 RE */
	TEXN( "fer_logoa" ),       /* 21014 128x32 1555 RE */
	TEXN( "tex_f1_ramp1" ),    /* 21015 64x64 1555 TW MIP */
	TEXN( "pirelli" ),         /* 21016 128x32 1555 RE */
	TEXN( "ref_deepblue" ),    /* 21017 128x128 565 TW MIP */
	TEXN( "ref_sky_ts4" ),     /* 21018 128x128 565 TW MIP */
	TEXN( "ref_lemon_line" ),  /* 21019 128x128 565 TW MIP */
	TEXN( "mirror_r" ),        /* 21020 128x128 565 TW MIP */
	TEXN( "mirror_l" ),        /* 21021 128x128 565 TW MIP */
	TEXN( "tex_f1_ramp" ),     /* 21022 64x64 565 TW MIP */
	TEXN( "cafe128" ),     	   /* 21022 128x128 565 TW MIP */
END

TEXTURELIST texlist_F40_GTE_sh_null1_1
START
TextureList textures_F40_GTE_sh_null1_1,
TextureNum  34,
END

TEXTURE_END


OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 32 ),
AttrFlags ( 0x9621a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START
	Strip(0x8000, 14),  3, 5, 6, 8, 4, 10, 2, 12, 0, 14, 
			18, 16, 15, 13, 
	Strip(0x0, 10),  15, 18, 17, 0, 19, 2, 1, 4, 3, 6, 
	Strip(0x0, 10),  16, 13, 14, 11, 12, 9, 10, 7, 8, 5, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START
	UV( 23, 51 ),
	UV( 86, 3 ),
	UV( 86, 3 ),
	UV( 164, 3 ),
	UV( 23, 51 ),
	UV( 227, 51 ),
	UV( 0, 129 ),
	UV( 251, 129 ),
	UV( 23, 207 ),
	UV( 227, 207 ),
	UV( 86, 255 ),
	UV( 164, 255 ),
	UV( 164, 255 ),
	UV( 227, 207 ),
	UV( 164, 255 ),
	UV( 86, 255 ),
	UV( 86, 255 ),
	UV( 23, 207 ),
	UV( 23, 207 ),
	UV( 0, 129 ),
	UV( 0, 129 ),
	UV( 23, 51 ),
	UV( 23, 51 ),
	UV( 86, 3 ),
	UV( 164, 255 ),
	UV( 227, 207 ),
	UV( 227, 207 ),
	UV( 251, 129 ),
	UV( 251, 129 ),
	UV( 227, 51 ),
	UV( 227, 51 ),
	UV( 164, 3 ),
	UV( 164, 3 ),
	UV( 86, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START
	VERT( -0.623846F,  0.603534F,  2.188158F ),
	VERT( -0.638814F,  0.649602F,  2.095658F ),
	VERT( -0.638814F,  0.649602F,  2.188158F ),
	VERT( -0.623846F,  0.695670F,  2.095658F ),
	VERT( -0.623846F,  0.695670F,  2.188158F ),
	VERT( -0.584659F,  0.724141F,  2.095658F ),
	VERT( -0.584659F,  0.724141F,  2.188158F ),
	VERT( -0.536220F,  0.724141F,  2.095658F ),
	VERT( -0.536220F,  0.724141F,  2.188158F ),
	VERT( -0.497033F,  0.695670F,  2.095658F ),
	VERT( -0.497033F,  0.695670F,  2.188158F ),
	VERT( -0.482064F,  0.649602F,  2.095658F ),
	VERT( -0.482064F,  0.649602F,  2.188158F ),
	VERT( -0.497033F,  0.603534F,  2.095658F ),
	VERT( -0.497033F,  0.603534F,  2.188158F ),
	VERT( -0.536220F,  0.575063F,  2.095658F ),
	VERT( -0.536220F,  0.575063F,  2.188158F ),
	VERT( -0.584659F,  0.575063F,  2.095658F ),
	VERT( -0.584659F,  0.575063F,  2.188158F ),
	VERT( -0.623846F,  0.603534F,  2.095658F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START
	NORM( -0.619112F, -0.449811F,  0.643717F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -0.765264F,  0.000000F,  0.643717F ),
	NORM( -0.809017F,  0.587785F,  0.000000F ),
	NORM( -0.619111F,  0.449811F,  0.643717F ),
	NORM( -0.309017F,  0.951056F,  0.000000F ),
	NORM( -0.236480F,  0.727809F,  0.643717F ),
	NORM(  0.309017F,  0.951056F,  0.000000F ),
	NORM(  0.236480F,  0.727809F,  0.643717F ),
	NORM(  0.809017F,  0.587785F,  0.000000F ),
	NORM(  0.619111F,  0.449811F,  0.643717F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  0.765264F,  0.000000F,  0.643717F ),
	NORM(  0.809017F, -0.587785F,  0.000000F ),
	NORM(  0.619111F, -0.449811F,  0.643717F ),
	NORM(  0.309017F, -0.951056F,  0.000000F ),
	NORM(  0.236480F, -0.727809F,  0.643717F ),
	NORM( -0.309017F, -0.951056F,  0.000000F ),
	NORM( -0.236480F, -0.727809F,  0.643717F ),
	NORM( -0.809017F, -0.587785F, -0.000001F ),
END

MODEL       model_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START
Points      point_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
Normal      normal_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
PointNum    20,
Meshset     meshset_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
Materials   matlist_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
MeshsetNum  1,
MatNum      1,
Center      -0.560439F,  0.649602F,  2.141908F,
Radius       0.091004F,
END

OBJECT      object_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     NULL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 32 ),
AttrFlags ( 0x9621a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START
	Strip(0x0, 10),  7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 
	Strip(0x8000, 14),  9, 7, 8, 6, 10, 4, 12, 2, 14, 0, 
			16, 18, 17, 19, 
	Strip(0x0, 10),  17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START
	UV( 86, 3 ),
	UV( 164, 3 ),
	UV( 164, 3 ),
	UV( 227, 51 ),
	UV( 227, 51 ),
	UV( 251, 129 ),
	UV( 251, 129 ),
	UV( 227, 207 ),
	UV( 227, 207 ),
	UV( 164, 255 ),
	UV( 23, 51 ),
	UV( 86, 3 ),
	UV( 86, 3 ),
	UV( 164, 3 ),
	UV( 23, 51 ),
	UV( 227, 51 ),
	UV( 0, 129 ),
	UV( 251, 129 ),
	UV( 23, 207 ),
	UV( 227, 207 ),
	UV( 86, 255 ),
	UV( 164, 255 ),
	UV( 164, 254 ),
	UV( 227, 207 ),
	UV( 164, 254 ),
	UV( 86, 255 ),
	UV( 86, 254 ),
	UV( 23, 207 ),
	UV( 23, 207 ),
	UV( 0, 129 ),
	UV( 0, 129 ),
	UV( 23, 51 ),
	UV( 23, 51 ),
	UV( 86, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START
	VERT(  0.620932F,  0.603534F,  2.188161F ),
	VERT(  0.635900F,  0.649602F,  2.095660F ),
	VERT(  0.635900F,  0.649602F,  2.188161F ),
	VERT(  0.620932F,  0.695670F,  2.095660F ),
	VERT(  0.620932F,  0.695670F,  2.188161F ),
	VERT(  0.581744F,  0.724141F,  2.095660F ),
	VERT(  0.581744F,  0.724141F,  2.188161F ),
	VERT(  0.533306F,  0.724141F,  2.095660F ),
	VERT(  0.533306F,  0.724141F,  2.188161F ),
	VERT(  0.494119F,  0.695670F,  2.095660F ),
	VERT(  0.494119F,  0.695670F,  2.188161F ),
	VERT(  0.479150F,  0.649602F,  2.095660F ),
	VERT(  0.479150F,  0.649602F,  2.188161F ),
	VERT(  0.494119F,  0.603534F,  2.095660F ),
	VERT(  0.494119F,  0.603534F,  2.188161F ),
	VERT(  0.533306F,  0.575063F,  2.095660F ),
	VERT(  0.533306F,  0.575063F,  2.188161F ),
	VERT(  0.581744F,  0.575063F,  2.095660F ),
	VERT(  0.581744F,  0.575063F,  2.188161F ),
	VERT(  0.620932F,  0.603534F,  2.095660F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START
	NORM(  0.619112F, -0.449811F,  0.643717F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  0.765264F,  0.000000F,  0.643717F ),
	NORM(  0.809017F,  0.587785F,  0.000000F ),
	NORM(  0.619111F,  0.449811F,  0.643717F ),
	NORM(  0.309017F,  0.951057F,  0.000001F ),
	NORM(  0.236479F,  0.727809F,  0.643717F ),
	NORM( -0.309017F,  0.951056F,  0.000000F ),
	NORM( -0.236480F,  0.727809F,  0.643717F ),
	NORM( -0.809017F,  0.587785F,  0.000000F ),
	NORM( -0.619111F,  0.449811F,  0.643717F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -0.765264F,  0.000000F,  0.643717F ),
	NORM( -0.809017F, -0.587785F,  0.000000F ),
	NORM( -0.619111F, -0.449811F,  0.643717F ),
	NORM( -0.309017F, -0.951056F, -0.000001F ),
	NORM( -0.236480F, -0.727809F,  0.643716F ),
	NORM(  0.309017F, -0.951057F, -0.000001F ),
	NORM(  0.236479F, -0.727809F,  0.643717F ),
	NORM(  0.809017F, -0.587785F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START
Points      point_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
Normal      normal_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
PointNum    20,
Meshset     meshset_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
Materials   matlist_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
MeshsetNum  1,
MatNum      1,
Center       0.557525F,  0.649602F,  2.141911F,
Radius       0.091004F,
END

OBJECT      object_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2[]
START
EvalFlags ( 0x00000007 ),
Model       model_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       object_F40_GTE_sh_null1_1_BLK_LAMP_R_1_1,
Sibling     NULL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cube41[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 28 ),
AttrFlags ( 0x9469a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_cube41[]
START
	Strip(0x8000, 12),  12, 0, 14, 4, 9, 5, 8, 1, 13, 3, 
			12, 0, 
	Strip(0x8000, 12),  12, 10, 13, 2, 8, 11, 9, 7, 14, 6, 
			12, 10, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_cube41[]
START
	UV( 126, 91 ),
	UV( 0, 113 ),
	UV( 126, 233 ),
	UV( 0, 255 ),
	UV( 126, 233 ),
	UV( 0, 255 ),
	UV( 126, 91 ),
	UV( 0, 113 ),
	UV( 126, 1 ),
	UV( 0, 23 ),
	UV( 126, 91 ),
	UV( 0, 113 ),
	UV( 126, 91 ),
	UV( 253, 113 ),
	UV( 126, 1 ),
	UV( 253, 23 ),
	UV( 126, 91 ),
	UV( 253, 113 ),
	UV( 126, 233 ),
	UV( 253, 255 ),
	UV( 126, 233 ),
	UV( 253, 255 ),
	UV( 126, 91 ),
	UV( 253, 113 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_cube41[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     2,
Meshes      pgS_0_F40_GTE_sh_null1_1_cube41,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_cube41,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cube41[]
START
	VERT( -0.937440F,  1.054207F,  2.015445F ),
	VERT( -0.930000F,  1.034207F,  2.015445F ),
	VERT(  0.930000F,  1.086235F,  2.165213F ),
	VERT( -0.930000F,  1.086235F,  2.165213F ),
	VERT( -0.937440F,  1.037444F,  1.780304F ),
	VERT( -0.930000F,  1.017444F,  1.780304F ),
	VERT(  0.937440F,  1.037444F,  1.780304F ),
	VERT(  0.930000F,  1.017444F,  1.780304F ),
	VERT(  0.000000F,  1.020055F,  2.052035F ),
	VERT(  0.000000F,  1.003292F,  1.816894F ),
	VERT(  0.937440F,  1.054207F,  2.015445F ),
	VERT(  0.930000F,  1.034207F,  2.015445F ),
	VERT(  0.000000F,  1.040055F,  2.052035F ),
	VERT(  0.000000F,  1.072083F,  2.201803F ),
	VERT(  0.000000F,  1.023292F,  1.816894F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cube41[]
START
	NORM(  0.020335F,  0.990227F, -0.137978F ),
	NORM( -0.022717F, -0.979856F,  0.198411F ),
	NORM(  0.026397F,  0.501359F,  0.864837F ),
	NORM( -0.027863F,  0.501356F,  0.864792F ),
	NORM(  0.036949F,  0.761200F, -0.647464F ),
	NORM(  0.020619F, -0.637113F, -0.770495F ),
	NORM( -0.036949F,  0.761200F, -0.647464F ),
	NORM( -0.020619F, -0.637113F, -0.770495F ),
	NORM(  0.000000F, -0.978916F,  0.204263F ),
	NORM(  0.000000F, -0.741886F, -0.670526F ),
	NORM( -0.020423F,  0.990224F, -0.137980F ),
	NORM(  0.022717F, -0.979856F,  0.198411F ),
	NORM( -0.000047F,  0.989818F, -0.142341F ),
	NORM( -0.000746F,  0.254370F,  0.967107F ),
	NORM(  0.000000F,  0.689177F, -0.724593F ),
END

MODEL       model_F40_GTE_sh_null1_1_cube41[]
START
Points      point_F40_GTE_sh_null1_1_cube41,
Normal      normal_F40_GTE_sh_null1_1_cube41,
PointNum    15,
Meshset     meshset_F40_GTE_sh_null1_1_cube41,
Materials   matlist_F40_GTE_sh_null1_1_cube41,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  1.044763F,  1.991053F,
Radius       0.960837F,
END

OBJECT      object_F40_GTE_sh_null1_1_cube41[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_cube41,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     NULL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cube45[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 28 ),
AttrFlags ( 0x9469a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_cube45[]
START
	Strip(0x0, 6),  1, 6, 4, 2, 11, 8, 
	Strip(0x0, 3),  4, 5, 1, 
	Strip(0x0, 8),  10, 7, 9, 2, 0, 6, 3, 1, 
	Strip(0x0, 8),  8, 10, 11, 9, 4, 0, 5, 3, 
	Strip(0x0, 3),  7, 8, 2, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_cube45[]
START
	UV( 219, 255 ),
	UV( 219, 241 ),
	UV( 253, 219 ),
	UV( 6, 51 ),
	UV( 199, 25 ),
	UV( 199, 1 ),
	UV( 253, 219 ),
	UV( 253, 255 ),
	UV( 219, 255 ),
	UV( 199, 1 ),
	UV( 0, 12 ),
	UV( 199, 25 ),
	UV( 6, 51 ),
	UV( 253, 219 ),
	UV( 219, 241 ),
	UV( 253, 255 ),
	UV( 219, 255 ),
	UV( 199, 1 ),
	UV( 199, 1 ),
	UV( 199, 25 ),
	UV( 199, 25 ),
	UV( 253, 219 ),
	UV( 253, 219 ),
	UV( 253, 255 ),
	UV( 253, 255 ),
	UV( 0, 12 ),
	UV( 199, 1 ),
	UV( 6, 51 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_cube45[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     5,
Meshes      pgS_0_F40_GTE_sh_null1_1_cube45,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_cube45,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cube45[]
START
	VERT( -0.005000F,  0.848875F,  2.192296F ),
	VERT(  0.000000F,  0.816910F,  2.145451F ),
	VERT(  0.000000F,  1.002555F,  1.842776F ),
	VERT( -0.005000F,  0.816910F,  2.192296F ),
	VERT(  0.005000F,  0.848875F,  2.192296F ),
	VERT(  0.005000F,  0.816910F,  2.192296F ),
	VERT(  0.000000F,  0.829461F,  2.145451F ),
	VERT(  0.000000F,  1.023286F,  1.833762F ),
	VERT(  0.005000F,  1.043995F,  2.115765F ),
	VERT( -0.005000F,  1.026129F,  2.115765F ),
	VERT( -0.005000F,  1.043995F,  2.115765F ),
	VERT(  0.005000F,  1.026129F,  2.115765F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cube45[]
START
	NORM( -0.684884F,  0.139078F,  0.715256F ),
	NORM(  0.000000F,  0.000000F, -1.000000F ),
	NORM( -0.018575F, -0.504664F, -0.863116F ),
	NORM( -0.743684F,  0.000000F,  0.668532F ),
	NORM(  0.694493F,  0.127461F,  0.708119F ),
	NORM(  0.743684F,  0.000000F,  0.668532F ),
	NORM( -0.014605F, -0.396811F, -0.917784F ),
	NORM(  0.000000F,  0.000000F, -1.000000F ),
	NORM(  0.696200F,  0.000000F,  0.717848F ),
	NORM( -0.765137F,  0.116288F,  0.633280F ),
	NORM( -0.696200F,  0.000000F,  0.717848F ),
	NORM(  0.775147F,  0.103554F,  0.623237F ),
END

MODEL       model_F40_GTE_sh_null1_1_cube45[]
START
Points      point_F40_GTE_sh_null1_1_cube45,
Normal      normal_F40_GTE_sh_null1_1_cube45,
PointNum    12,
Meshset     meshset_F40_GTE_sh_null1_1_cube45,
Materials   matlist_F40_GTE_sh_null1_1_cube45,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.930452F,  2.013029F,
Radius       0.212199F,
END

OBJECT      object_F40_GTE_sh_null1_1_cube45[]
START
EvalFlags ( 0x00000007 ),
Model       model_F40_GTE_sh_null1_1_cube45,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       object_F40_GTE_sh_null1_1_cube41,
Sibling     NULL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cube43[]
START

MATSTART
Diffuse   ( 255, 84, 84, 84 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_cube43[]
START
	Strip(0x0, 3),  4, 1, 3, 
	Strip(0x0, 3),  2, 5, 0, 
	Strip(0x0, 4),  5, 4, 0, 3, 
END

MESHSET     meshset_F40_GTE_sh_null1_1_cube43[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_cube43,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cube43[]
START
	VERT( -0.570000F,  0.125776F,  1.292304F ),
	VERT(  0.620000F,  0.102477F,  2.198240F ),
	VERT( -0.620000F,  0.102477F,  2.198240F ),
	VERT(  0.570000F,  0.125776F,  1.292304F ),
	VERT(  0.620000F,  0.243635F,  2.198240F ),
	VERT( -0.620000F,  0.243635F,  2.198240F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cube43[]
START
	NORM( -0.094628F,  0.986512F, -0.133565F ),
	NORM(  0.998480F,  0.000000F, -0.055108F ),
	NORM( -0.998480F,  0.000000F, -0.055108F ),
	NORM(  0.094628F,  0.986512F, -0.133565F ),
	NORM(  0.685601F,  0.716094F, -0.131001F ),
	NORM( -0.685601F,  0.716094F, -0.131001F ),
END

MODEL       model_F40_GTE_sh_null1_1_cube43[]
START
Points      point_F40_GTE_sh_null1_1_cube43,
Normal      normal_F40_GTE_sh_null1_1_cube43,
PointNum    6,
Meshset     meshset_F40_GTE_sh_null1_1_cube43,
Materials   matlist_F40_GTE_sh_null1_1_cube43,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.173056F,  1.745272F,
Radius       0.767841F,
END

OBJECT      object_F40_GTE_sh_null1_1_cube43[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_cube43,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_cube45,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_F4E_R_BUMPER[]
START

MATSTART
Diffuse   ( 255, 38, 38, 38 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_F4E_R_BUMPER[]
START
	Strip(0x0, 6),  2, 3, 1, 0, 11, 7, 
	Strip(0x0, 5),  11, 8, 1, 9, 2, 
	Strip(0x0, 3),  10, 5, 4, 
	Strip(0x8000, 12),  6, 7, 10, 11, 4, 8, 5, 9, 10, 2, 
			6, 3, 
END

MESHSET     meshset_F40_GTE_sh_null1_1_F4E_R_BUMPER[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     4,
Meshes      pgS_0_F40_GTE_sh_null1_1_F4E_R_BUMPER,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_F4E_R_BUMPER[]
START
	VERT( -0.983213F,  0.429962F,  1.941812F ),
	VERT( -0.954262F,  0.429962F,  2.182195F ),
	VERT( -0.954262F,  0.489962F,  2.182195F ),
	VERT( -0.983213F,  0.489962F,  1.941812F ),
	VERT(  0.251011F,  0.429962F,  2.237102F ),
	VERT(  0.251011F,  0.489962F,  2.237102F ),
	VERT(  0.983213F,  0.489962F,  1.941812F ),
	VERT(  0.983213F,  0.429962F,  1.941812F ),
	VERT( -0.251011F,  0.429962F,  2.237102F ),
	VERT( -0.251011F,  0.489962F,  2.237102F ),
	VERT(  0.954262F,  0.489962F,  2.182195F ),
	VERT(  0.954262F,  0.429962F,  2.182195F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_F4E_R_BUMPER[]
START
	NORM( -0.729307F, -0.678525F,  0.087835F ),
	NORM( -0.559595F, -0.588470F,  0.583572F ),
	NORM( -0.559595F,  0.588470F,  0.583572F ),
	NORM( -0.729307F,  0.678525F,  0.087835F ),
	NORM(  0.027874F, -0.698444F,  0.715121F ),
	NORM(  0.027874F,  0.698444F,  0.715121F ),
	NORM(  0.729307F,  0.678525F,  0.087835F ),
	NORM(  0.729307F, -0.678525F,  0.087835F ),
	NORM( -0.027874F, -0.698444F,  0.715121F ),
	NORM( -0.027874F,  0.698444F,  0.715121F ),
	NORM(  0.559595F,  0.588470F,  0.583572F ),
	NORM(  0.559595F, -0.588470F,  0.583572F ),
END

MODEL       model_F40_GTE_sh_null1_1_F4E_R_BUMPER[]
START
Points      point_F40_GTE_sh_null1_1_F4E_R_BUMPER,
Normal      normal_F40_GTE_sh_null1_1_F4E_R_BUMPER,
PointNum    12,
Meshset     meshset_F40_GTE_sh_null1_1_F4E_R_BUMPER,
Materials   matlist_F40_GTE_sh_null1_1_F4E_R_BUMPER,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.459962F,  2.089457F,
Radius       0.994236F,
END

OBJECT      object_F40_GTE_sh_null1_1_F4E_R_BUMPER[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_F4E_R_BUMPER,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_cube43,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_grid19[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 27 ),
AttrFlags ( 0x9469a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_grid19[]
START
	Strip(0x0, 6),  2, 3, 1, 0, 5, 4, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_grid19[]
START
	UV( 185, 39 ),
	UV( 185, 207 ),
	UV( 126, 49 ),
	UV( 126, 217 ),
	UV( 67, 39 ),
	UV( 67, 207 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_grid19[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_grid19,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_grid19,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_grid19[]
START
	VERT(  0.000000F,  0.610190F, -1.591177F ),
	VERT(  0.000000F,  0.708497F, -1.170533F ),
	VERT(  0.050000F,  0.612918F, -1.144492F ),
	VERT(  0.050000F,  0.514611F, -1.565136F ),
	VERT( -0.050000F,  0.514611F, -1.565136F ),
	VERT( -0.050000F,  0.612918F, -1.144492F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_grid19[]
START
	NORM(  0.000000F,  0.973761F, -0.227573F ),
	NORM(  0.000000F,  0.973761F, -0.227573F ),
	NORM(  0.892610F,  0.439000F, -0.102597F ),
	NORM(  0.892610F,  0.439000F, -0.102597F ),
	NORM( -0.892610F,  0.439000F, -0.102597F ),
	NORM( -0.892610F,  0.439000F, -0.102597F ),
END

MODEL       model_F40_GTE_sh_null1_1_grid19[]
START
Points      point_F40_GTE_sh_null1_1_grid19,
Normal      normal_F40_GTE_sh_null1_1_grid19,
PointNum    6,
Meshset     meshset_F40_GTE_sh_null1_1_grid19,
Materials   matlist_F40_GTE_sh_null1_1_grid19,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.611554F, -1.367835F,
Radius       0.243474F,
END

OBJECT      object_F40_GTE_sh_null1_1_grid19[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_grid19,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_F4E_R_BUMPER,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_D_MIRROR_R[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 29 ),
AttrFlags ( 0x9461a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 31 ),
AttrFlags ( 0x9469a400 ),
MATEND

MATSTART
Diffuse   ( 255, 17, 17, 17 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
	Strip(0x0, 5),  29, 2, 25, 20, 0, 
	Strip(0x8000, 5),  3, 4, 28, 26, 27, 
	Strip(0x0, 8),  9, 18, 15, 19, 13, 11, 12, 16, 
	Strip(0x0, 27),  23, 17, 22, 21, 3, 31, 28, 30, 27, 2, 
			26, 29, 5, 7, 6, 1, 22, 24, 23, 8, 
			14, 0, 9, 20, 18, 2, 30, 
	Strip(0x0, 6),  22, 3, 6, 4, 5, 26, 
	Strip(0x0, 5),  16, 11, 10, 31, 21, 
	Strip(0x8000, 5),  11, 31, 19, 30, 18, 
	Strip(0x0, 4),  21, 17, 10, 16, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
	Strip(0x8000, 8),  15, 9, 13, 14, 12, 23, 16, 17, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
	Strip(0x8000, 7),  8, 0, 24, 25, 1, 29, 7, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
	UV( 74, 184 ),
	UV( 111, 152 ),
	UV( 77, 191 ),
	UV( 109, 155 ),
	UV( 76, 188 ),
	UV( 109, 77 ),
	UV( 111, 109 ),
	UV( 164, 109 ),
	UV( 107, 145 ),
	UV( 169, 139 ),
	UV( 103, 155 ),
	UV( 180, 155 ),
	UV( 176, 155 ),
	UV( 189, 140 ),
	UV( 186, 140 ),
	UV( 189, 80 ),
	UV( 186, 80 ),
	UV( 176, 65 ),
	UV( 94, 87 ),
	UV( 103, 65 ),
	UV( 97, 87 ),
	UV( 107, 65 ),
	UV( 109, 77 ),
	UV( 181, 83 ),
	UV( 164, 109 ),
	UV( 181, 146 ),
	UV( 169, 139 ),
	UV( 111, 152 ),
	UV( 107, 145 ),
	UV( 74, 184 ),
	UV( 103, 127 ),
	UV( 68, 167 ),
	UV( 101, 96 ),
	UV( 65, 158 ),
	UV( 97, 87 ),
	UV( 63, 153 ),
	UV( 94, 87 ),
	UV( 63, 150 ),
	UV( 94, 140 ),
	UV( 76, 188 ),
	UV( 103, 155 ),
	UV( 109, 155 ),
	UV( 180, 155 ),
	UV( 111, 152 ),
	UV( 181, 146 ),
	UV( 97, 87 ),
	UV( 109, 77 ),
	UV( 101, 96 ),
	UV( 111, 109 ),
	UV( 103, 127 ),
	UV( 107, 145 ),
	UV( 176, 65 ),
	UV( 189, 80 ),
	UV( 180, 65 ),
	UV( 181, 83 ),
	UV( 107, 65 ),
	UV( 189, 80 ),
	UV( 181, 83 ),
	UV( 189, 140 ),
	UV( 181, 146 ),
	UV( 180, 155 ),
	UV( 107, 65 ),
	UV( 103, 65 ),
	UV( 180, 65 ),
	UV( 176, 65 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
	UV( 160, 146 ),
	UV( 111, 146 ),
	UV( 166, 136 ),
	UV( 104, 136 ),
	UV( 166, 96 ),
	UV( 104, 101 ),
	UV( 160, 86 ),
	UV( 111, 86 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_D_MIRROR_R[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     8,
Meshes      pgS_0_F40_GTE_sh_null1_1_D_MIRROR_R,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_D_MIRROR_R,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     1,
Meshes      pgS_1_F40_GTE_sh_null1_1_D_MIRROR_R,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_D_MIRROR_R,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     1,
Meshes      pgS_2_F40_GTE_sh_null1_1_D_MIRROR_R,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
	VERT(  0.698207F,  0.779173F, -0.229766F ),
	VERT(  0.676336F,  0.816706F, -0.272836F ),
	VERT(  0.765681F,  0.823531F, -0.286272F ),
	VERT(  0.761869F,  0.916148F, -0.287108F ),
	VERT(  0.766222F,  0.876126F, -0.309730F ),
	VERT(  0.750595F,  0.853982F, -0.313241F ),
	VERT(  0.745867F,  0.892095F, -0.290620F ),
	VERT(  0.682216F,  0.805166F, -0.283212F ),
	VERT(  0.672373F,  0.826540F, -0.235985F ),
	VERT(  0.751207F,  0.819632F, -0.226111F ),
	VERT(  0.899244F,  0.931220F, -0.222627F ),
	VERT(  0.918091F,  0.912118F, -0.218491F ),
	VERT(  0.912020F,  0.912118F, -0.190824F ),
	VERT(  0.912020F,  0.838735F, -0.190824F ),
	VERT(  0.732524F,  0.838736F, -0.230210F ),
	VERT(  0.893173F,  0.819632F, -0.194960F ),
	VERT(  0.893173F,  0.931220F, -0.194960F ),
	VERT(  0.751371F,  0.931220F, -0.226075F ),
	VERT(  0.899244F,  0.819632F, -0.222627F ),
	VERT(  0.918091F,  0.838735F, -0.218491F ),
	VERT(  0.762084F,  0.819632F, -0.252723F ),
	VERT(  0.757442F,  0.931220F, -0.253741F ),
	VERT(  0.738594F,  0.903392F, -0.257877F ),
	VERT(  0.732524F,  0.903392F, -0.230210F ),
	VERT(  0.673760F,  0.822374F, -0.257480F ),
	VERT(  0.699880F,  0.775217F, -0.246259F ),
	VERT(  0.759195F,  0.831895F, -0.308206F ),
	VERT(  0.878361F,  0.839467F, -0.285207F ),
	VERT(  0.869761F,  0.876126F, -0.287094F ),
	VERT(  0.693726F,  0.784130F, -0.284364F ),
	VERT(  0.902878F,  0.831458F, -0.256168F ),
	VERT(  0.902878F,  0.908221F, -0.256168F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
	NORM( -0.245053F, -0.714056F,  0.655799F ),
	NORM( -0.928715F,  0.060234F, -0.365869F ),
	NORM(  0.305455F, -0.910195F, -0.279718F ),
	NORM( -0.256648F,  0.708287F, -0.657618F ),
	NORM( -0.033624F,  0.300392F, -0.953223F ),
	NORM( -0.170454F,  0.084985F, -0.981694F ),
	NORM( -0.612064F,  0.495599F, -0.616246F ),
	NORM( -0.766276F, -0.238324F, -0.596677F ),
	NORM( -0.851686F,  0.133437F,  0.506780F ),
	NORM(  0.075281F, -0.545103F,  0.834982F ),
	NORM(  0.411121F,  0.895700F, -0.169416F ),
	NORM(  0.929572F,  0.360250F, -0.078199F ),
	NORM(  0.565194F,  0.299046F,  0.768848F ),
	NORM(  0.565194F, -0.299046F,  0.768848F ),
	NORM( -0.149750F,  0.024532F,  0.988419F ),
	NORM(  0.153141F, -0.717718F,  0.679286F ),
	NORM(  0.153141F,  0.717718F,  0.679285F ),
	NORM( -0.488858F,  0.697832F,  0.523496F ),
	NORM(  0.404759F, -0.912751F, -0.055273F ),
	NORM(  0.938745F, -0.341490F, -0.046282F ),
	NORM(  0.313326F, -0.949350F, -0.023673F ),
	NORM( -0.369239F,  0.883871F, -0.287116F ),
	NORM( -0.767386F,  0.581192F, -0.270805F ),
	NORM( -0.698360F,  0.424943F,  0.575949F ),
	NORM( -0.982969F,  0.098487F, -0.155152F ),
	NORM( -0.164137F, -0.986258F,  0.018804F ),
	NORM(  0.169437F, -0.523405F, -0.835068F ),
	NORM(  0.453874F, -0.478185F, -0.751889F ),
	NORM(  0.412176F,  0.221369F, -0.883802F ),
	NORM( -0.271230F, -0.789798F, -0.550140F ),
	NORM(  0.675048F, -0.577654F, -0.458940F ),
	NORM(  0.644715F,  0.475615F, -0.598443F ),
END

MODEL       model_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
Points      point_F40_GTE_sh_null1_1_D_MIRROR_R,
Normal      normal_F40_GTE_sh_null1_1_D_MIRROR_R,
PointNum    32,
Meshset     meshset_F40_GTE_sh_null1_1_D_MIRROR_R,
Materials   matlist_F40_GTE_sh_null1_1_D_MIRROR_R,
MeshsetNum  3,
MatNum      3,
Center       0.795232F,  0.853218F, -0.252033F,
Radius       0.137262F,
END

OBJECT      object_F40_GTE_sh_null1_1_D_MIRROR_R[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_D_MIRROR_R,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_grid19,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_D_MIRROR_L[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 29 ),
AttrFlags ( 0x9461a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 30 ),
AttrFlags ( 0x9469a400 ),
MATEND

MATSTART
Diffuse   ( 255, 17, 17, 17 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
	Strip(0x0, 3),  26, 4, 5, 
	Strip(0x8000, 5),  31, 4, 3, 5, 6, 
	Strip(0x8000, 5),  30, 18, 20, 15, 9, 
	Strip(0x0, 3),  13, 12, 19, 
	Strip(0x8000, 6),  19, 11, 12, 10, 16, 21, 
	Strip(0x8000, 12),  9, 25, 20, 2, 30, 26, 27, 4, 28, 31, 
			27, 30, 
	Strip(0x0, 6),  23, 14, 7, 9, 1, 25, 
	Strip(0x0, 14),  7, 24, 22, 6, 21, 3, 10, 31, 11, 30, 
			19, 18, 13, 15, 
	Strip(0x0, 6),  7, 22, 23, 21, 17, 16, 
	Strip(0x8000, 6),  24, 6, 0, 5, 8, 26, 
	Strip(0x8000, 5),  2, 25, 26, 29, 8, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
	Strip(0x8000, 8),  16, 17, 12, 23, 13, 14, 15, 9, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
	Strip(0x8000, 7),  1, 7, 25, 24, 29, 0, 8, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
	UV( 107, 145 ),
	UV( 111, 109 ),
	UV( 103, 127 ),
	UV( 181, 83 ),
	UV( 111, 109 ),
	UV( 109, 77 ),
	UV( 103, 127 ),
	UV( 101, 96 ),
	UV( 181, 146 ),
	UV( 180, 155 ),
	UV( 109, 155 ),
	UV( 176, 155 ),
	UV( 103, 155 ),
	UV( 186, 140 ),
	UV( 186, 80 ),
	UV( 189, 140 ),
	UV( 189, 140 ),
	UV( 189, 80 ),
	UV( 186, 80 ),
	UV( 180, 65 ),
	UV( 176, 65 ),
	UV( 107, 65 ),
	UV( 103, 155 ),
	UV( 77, 191 ),
	UV( 109, 155 ),
	UV( 111, 152 ),
	UV( 181, 146 ),
	UV( 107, 145 ),
	UV( 169, 139 ),
	UV( 111, 109 ),
	UV( 164, 109 ),
	UV( 181, 83 ),
	UV( 169, 139 ),
	UV( 181, 146 ),
	UV( 94, 87 ),
	UV( 94, 140 ),
	UV( 63, 150 ),
	UV( 103, 155 ),
	UV( 76, 188 ),
	UV( 77, 191 ),
	UV( 63, 150 ),
	UV( 63, 153 ),
	UV( 97, 87 ),
	UV( 101, 96 ),
	UV( 107, 65 ),
	UV( 109, 77 ),
	UV( 180, 65 ),
	UV( 181, 83 ),
	UV( 189, 80 ),
	UV( 181, 146 ),
	UV( 189, 140 ),
	UV( 180, 155 ),
	UV( 186, 140 ),
	UV( 176, 155 ),
	UV( 63, 150 ),
	UV( 97, 87 ),
	UV( 94, 87 ),
	UV( 107, 65 ),
	UV( 103, 65 ),
	UV( 176, 65 ),
	UV( 63, 153 ),
	UV( 101, 96 ),
	UV( 65, 158 ),
	UV( 103, 127 ),
	UV( 68, 167 ),
	UV( 107, 145 ),
	UV( 111, 152 ),
	UV( 77, 191 ),
	UV( 107, 145 ),
	UV( 74, 184 ),
	UV( 68, 167 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
	UV( 92, 86 ),
	UV( 141, 86 ),
	UV( 86, 96 ),
	UV( 148, 101 ),
	UV( 86, 136 ),
	UV( 148, 136 ),
	UV( 92, 146 ),
	UV( 141, 146 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_D_MIRROR_L[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     11,
Meshes      pgS_0_F40_GTE_sh_null1_1_D_MIRROR_L,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_D_MIRROR_L,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     1,
Meshes      pgS_1_F40_GTE_sh_null1_1_D_MIRROR_L,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_D_MIRROR_L,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     1,
Meshes      pgS_2_F40_GTE_sh_null1_1_D_MIRROR_L,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
	VERT( -0.676336F,  0.816706F, -0.272836F ),
	VERT( -0.698207F,  0.779173F, -0.229766F ),
	VERT( -0.765681F,  0.823531F, -0.286272F ),
	VERT( -0.761869F,  0.916148F, -0.287109F ),
	VERT( -0.766222F,  0.876126F, -0.309730F ),
	VERT( -0.750595F,  0.853982F, -0.313242F ),
	VERT( -0.745867F,  0.892095F, -0.290620F ),
	VERT( -0.672373F,  0.826540F, -0.235985F ),
	VERT( -0.682216F,  0.805166F, -0.283212F ),
	VERT( -0.751207F,  0.819632F, -0.226111F ),
	VERT( -0.899244F,  0.931220F, -0.222627F ),
	VERT( -0.918091F,  0.912118F, -0.218491F ),
	VERT( -0.912020F,  0.912118F, -0.190825F ),
	VERT( -0.912020F,  0.838735F, -0.190825F ),
	VERT( -0.732523F,  0.838736F, -0.230210F ),
	VERT( -0.893173F,  0.819632F, -0.194960F ),
	VERT( -0.893173F,  0.931220F, -0.194960F ),
	VERT( -0.751371F,  0.931220F, -0.226075F ),
	VERT( -0.899244F,  0.819632F, -0.222627F ),
	VERT( -0.918091F,  0.838735F, -0.218491F ),
	VERT( -0.762084F,  0.819632F, -0.252723F ),
	VERT( -0.757442F,  0.931220F, -0.253742F ),
	VERT( -0.738594F,  0.903392F, -0.257877F ),
	VERT( -0.732523F,  0.903392F, -0.230210F ),
	VERT( -0.673760F,  0.822374F, -0.257480F ),
	VERT( -0.699880F,  0.775217F, -0.246259F ),
	VERT( -0.759195F,  0.831895F, -0.308206F ),
	VERT( -0.878361F,  0.839467F, -0.285207F ),
	VERT( -0.869761F,  0.876126F, -0.287094F ),
	VERT( -0.693726F,  0.784130F, -0.284364F ),
	VERT( -0.902878F,  0.831458F, -0.256168F ),
	VERT( -0.902878F,  0.908221F, -0.256168F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
	NORM(  0.928715F,  0.060234F, -0.365869F ),
	NORM(  0.245053F, -0.714056F,  0.655799F ),
	NORM( -0.305455F, -0.910195F, -0.279718F ),
	NORM(  0.256647F,  0.708287F, -0.657618F ),
	NORM(  0.033891F,  0.317491F, -0.947655F ),
	NORM(  0.170454F,  0.084985F, -0.981694F ),
	NORM(  0.612064F,  0.495600F, -0.616245F ),
	NORM(  0.851686F,  0.133437F,  0.506780F ),
	NORM(  0.766276F, -0.238325F, -0.596676F ),
	NORM( -0.075281F, -0.545103F,  0.834982F ),
	NORM( -0.411121F,  0.895699F, -0.169417F ),
	NORM( -0.929572F,  0.360250F, -0.078199F ),
	NORM( -0.565195F,  0.299046F,  0.768848F ),
	NORM( -0.565194F, -0.299046F,  0.768848F ),
	NORM(  0.149750F,  0.024532F,  0.988419F ),
	NORM( -0.153142F, -0.717718F,  0.679285F ),
	NORM( -0.153143F,  0.717718F,  0.679285F ),
	NORM(  0.488858F,  0.697832F,  0.523496F ),
	NORM( -0.404759F, -0.912751F, -0.055273F ),
	NORM( -0.938745F, -0.341489F, -0.046282F ),
	NORM( -0.313326F, -0.949350F, -0.023673F ),
	NORM(  0.369239F,  0.883871F, -0.287116F ),
	NORM(  0.767385F,  0.581192F, -0.270804F ),
	NORM(  0.698360F,  0.424943F,  0.575949F ),
	NORM(  0.982969F,  0.098487F, -0.155152F ),
	NORM(  0.164137F, -0.986258F,  0.018804F ),
	NORM( -0.170348F, -0.511501F, -0.842228F ),
	NORM( -0.457274F, -0.463328F, -0.759097F ),
	NORM( -0.409547F,  0.240265F, -0.880082F ),
	NORM(  0.271230F, -0.789798F, -0.550140F ),
	NORM( -0.675048F, -0.577654F, -0.458940F ),
	NORM( -0.644714F,  0.475615F, -0.598443F ),
END

MODEL       model_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
Points      point_F40_GTE_sh_null1_1_D_MIRROR_L,
Normal      normal_F40_GTE_sh_null1_1_D_MIRROR_L,
PointNum    32,
Meshset     meshset_F40_GTE_sh_null1_1_D_MIRROR_L,
Materials   matlist_F40_GTE_sh_null1_1_D_MIRROR_L,
MeshsetNum  3,
MatNum      3,
Center      -0.795232F,  0.853218F, -0.252033F,
Radius       0.137262F,
END

OBJECT      object_F40_GTE_sh_null1_1_D_MIRROR_L[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_D_MIRROR_L,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_D_MIRROR_R,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cyl55[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 10 ),
AttrFlags ( 0x94a9a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_cyl55[]
START
	Strip(0x8000, 9),  3, 2, 8, 5, 7, 1, 6, 0, 4, 
	Strip(0x0, 5),  8, 3, 9, 4, 6, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_cyl55[]
START
	UV( 46, 254 ),
	UV( 200, 255 ),
	UV( 214, 219 ),
	UV( 247, 131 ),
	UV( 214, 44 ),
	UV( 200, 7 ),
	UV( 31, 44 ),
	UV( 46, 7 ),
	UV( 0, 131 ),
	UV( 214, 219 ),
	UV( 46, 254 ),
	UV( 31, 219 ),
	UV( 0, 131 ),
	UV( 31, 44 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_cyl55[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     2,
Meshes      pgS_0_F40_GTE_sh_null1_1_cyl55,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_cyl55,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cyl55[]
START
	VERT(  0.056217F,  0.349955F,  2.208989F ),
	VERT(  0.112585F,  0.349955F,  2.208989F ),
	VERT(  0.112585F,  0.292213F,  2.208989F ),
	VERT(  0.056217F,  0.292213F,  2.208989F ),
	VERT(  0.039304F,  0.321084F,  2.208989F ),
	VERT(  0.129497F,  0.321084F,  2.208989F ),
	VERT(  0.050944F,  0.341311F,  2.058989F ),
	VERT(  0.117539F,  0.341311F,  2.058989F ),
	VERT(  0.117539F,  0.300599F,  2.058989F ),
	VERT(  0.050944F,  0.300599F,  2.058989F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cyl55[]
START
	NORM( -0.480940F,  0.876110F, -0.033583F ),
	NORM(  0.481432F,  0.875802F, -0.034569F ),
	NORM(  0.481677F, -0.875725F, -0.033053F ),
	NORM( -0.481184F, -0.876033F, -0.032065F ),
	NORM( -0.999982F,  0.000270F, -0.005968F ),
	NORM(  0.999967F,  0.000270F, -0.008093F ),
	NORM( -0.699937F,  0.709023F, -0.085878F ),
	NORM(  0.699343F,  0.709429F, -0.087347F ),
	NORM(  0.699018F, -0.709899F, -0.086125F ),
	NORM( -0.699610F, -0.709492F, -0.084657F ),
END

MODEL       model_F40_GTE_sh_null1_1_cyl55[]
START
Points      point_F40_GTE_sh_null1_1_cyl55,
Normal      normal_F40_GTE_sh_null1_1_cyl55,
PointNum    10,
Meshset     meshset_F40_GTE_sh_null1_1_cyl55,
Materials   matlist_F40_GTE_sh_null1_1_cyl55,
MeshsetNum  1,
MatNum      1,
Center       0.084401F,  0.321084F,  2.133989F,
Radius       0.087514F,
END

OBJECT      object_F40_GTE_sh_null1_1_cyl55[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_cyl55,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     NULL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cyl56[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 10 ),
AttrFlags ( 0x94a9a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_cyl56[]
START
	Strip(0x0, 5),  9, 2, 8, 5, 7, 
	Strip(0x8000, 9),  2, 3, 9, 4, 6, 0, 7, 1, 5, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_cyl56[]
START
	UV( 214, 219 ),
	UV( 46, 255 ),
	UV( 31, 219 ),
	UV( 0, 131 ),
	UV( 31, 44 ),
	UV( 46, 255 ),
	UV( 200, 254 ),
	UV( 214, 219 ),
	UV( 247, 131 ),
	UV( 214, 44 ),
	UV( 200, 7 ),
	UV( 31, 44 ),
	UV( 46, 7 ),
	UV( 0, 131 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_cyl56[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     2,
Meshes      pgS_0_F40_GTE_sh_null1_1_cyl56,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_cyl56,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cyl56[]
START
	VERT( -0.056217F,  0.349955F,  2.208989F ),
	VERT( -0.112585F,  0.349955F,  2.208989F ),
	VERT( -0.112585F,  0.292213F,  2.208989F ),
	VERT( -0.056217F,  0.292213F,  2.208989F ),
	VERT( -0.039304F,  0.321084F,  2.208989F ),
	VERT( -0.129497F,  0.321084F,  2.208989F ),
	VERT( -0.051263F,  0.341311F,  2.058989F ),
	VERT( -0.117857F,  0.341311F,  2.058989F ),
	VERT( -0.117857F,  0.300599F,  2.058989F ),
	VERT( -0.051263F,  0.300599F,  2.058989F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cyl56[]
START
	NORM(  0.481432F,  0.875802F, -0.034570F ),
	NORM( -0.480940F,  0.876110F, -0.033583F ),
	NORM( -0.481184F, -0.876033F, -0.032065F ),
	NORM(  0.481678F, -0.875725F, -0.033053F ),
	NORM(  0.999967F,  0.000270F, -0.008093F ),
	NORM( -0.999982F,  0.000270F, -0.005968F ),
	NORM(  0.699343F,  0.709429F, -0.087347F ),
	NORM( -0.699937F,  0.709023F, -0.085878F ),
	NORM( -0.699610F, -0.709492F, -0.084657F ),
	NORM(  0.699018F, -0.709899F, -0.086125F ),
END

MODEL       model_F40_GTE_sh_null1_1_cyl56[]
START
Points      point_F40_GTE_sh_null1_1_cyl56,
Normal      normal_F40_GTE_sh_null1_1_cyl56,
PointNum    10,
Meshset     meshset_F40_GTE_sh_null1_1_cyl56,
Materials   matlist_F40_GTE_sh_null1_1_cyl56,
MeshsetNum  1,
MatNum      1,
Center      -0.084401F,  0.321084F,  2.133989F,
Radius       0.087514F,
END

OBJECT      object_F40_GTE_sh_null1_1_cyl56[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_cyl56,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_cyl55,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_EX_PIPE[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 10 ),
AttrFlags ( 0x94a9a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_EX_PIPE[]
START
	Strip(0x0, 5),  10, 6, 11, 7, 0, 
	Strip(0x8000, 5),  2, 1, 8, 0, 11, 
	Strip(0x0, 3),  2, 9, 8, 
	Strip(0x0, 7),  2, 3, 9, 4, 10, 5, 6, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_EX_PIPE[]
START
	UV( 210, 218 ),
	UV( 72, 254 ),
	UV( 36, 218 ),
	UV( 0, 182 ),
	UV( 0, 80 ),
	UV( 174, 7 ),
	UV( 72, 7 ),
	UV( 36, 44 ),
	UV( 0, 80 ),
	UV( 36, 218 ),
	UV( 174, 7 ),
	UV( 210, 44 ),
	UV( 36, 44 ),
	UV( 174, 7 ),
	UV( 247, 80 ),
	UV( 210, 44 ),
	UV( 247, 182 ),
	UV( 210, 218 ),
	UV( 174, 255 ),
	UV( 72, 254 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_EX_PIPE[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     4,
Meshes      pgS_0_F40_GTE_sh_null1_1_EX_PIPE,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_EX_PIPE,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_EX_PIPE[]
START
	VERT( -0.028871F,  0.333063F,  2.208989F ),
	VERT( -0.011959F,  0.349975F,  2.208989F ),
	VERT(  0.011959F,  0.349975F,  2.208989F ),
	VERT(  0.028871F,  0.333063F,  2.208989F ),
	VERT(  0.028871F,  0.309145F,  2.208989F ),
	VERT(  0.011959F,  0.292233F,  2.208989F ),
	VERT( -0.011959F,  0.292233F,  2.208989F ),
	VERT( -0.028871F,  0.309145F,  2.208989F ),
	VERT( -0.020415F,  0.341519F,  2.058989F ),
	VERT(  0.020415F,  0.341519F,  2.058989F ),
	VERT(  0.020415F,  0.300689F,  2.058989F ),
	VERT( -0.020415F,  0.300689F,  2.058989F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_EX_PIPE[]
START
	NORM( -0.930040F,  0.366080F, -0.031793F ),
	NORM( -0.366080F,  0.930040F, -0.031793F ),
	NORM(  0.366080F,  0.930040F, -0.031793F ),
	NORM(  0.930040F,  0.366080F, -0.031793F ),
	NORM(  0.930040F, -0.366080F, -0.031793F ),
	NORM(  0.366080F, -0.930040F, -0.031793F ),
	NORM( -0.366080F, -0.930040F, -0.031793F ),
	NORM( -0.930040F, -0.366080F, -0.031793F ),
	NORM( -0.705168F,  0.705168F, -0.074001F ),
	NORM(  0.705168F,  0.705168F, -0.074001F ),
	NORM(  0.705168F, -0.705168F, -0.074001F ),
	NORM( -0.705168F, -0.705168F, -0.074001F ),
END

MODEL       model_F40_GTE_sh_null1_1_EX_PIPE[]
START
Points      point_F40_GTE_sh_null1_1_EX_PIPE,
Normal      normal_F40_GTE_sh_null1_1_EX_PIPE,
PointNum    12,
Meshset     meshset_F40_GTE_sh_null1_1_EX_PIPE,
Materials   matlist_F40_GTE_sh_null1_1_EX_PIPE,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.321104F,  2.133989F,
Radius       0.080365F,
END

OBJECT      object_F40_GTE_sh_null1_1_EX_PIPE[]
START
EvalFlags ( 0x00000007 ),
Model       model_F40_GTE_sh_null1_1_EX_PIPE,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       object_F40_GTE_sh_null1_1_cyl56,
Sibling     object_F40_GTE_sh_null1_1_D_MIRROR_L,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 63, 165, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 27 ),
AttrFlags ( 0x9461a400 ),
MATEND

MATSTART
Diffuse   ( 255, 15, 15, 15 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 127, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 28 ),
AttrFlags ( 0x94f9a400 ),
MATEND

MATSTART
Diffuse   ( 101, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 28 ),
AttrFlags ( 0x9479a400 ),
MATEND

MATSTART
Diffuse   ( 255, 15, 15, 15 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94882400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 29 ),
AttrFlags ( 0x9461a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 63, 165, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 27 ),
AttrFlags ( 0x94e1a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 29 ),
AttrFlags ( 0x9469a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x0, 3),  500, 64, 61, 
	Strip(0x8000, 12),  63, 473, 64, 388, 500, 502, 506, 501, 216, 135, 
			138, 137, 
	Strip(0x0, 5),  500, 499, 506, 495, 216, 
	Strip(0x0, 11),  6, 5, 7, 349, 196, 51, 48, 556, 557, 562, 
			609, 
	Strip(0x0, 3),  122, 457, 465, 
	Strip(0x0, 8),  522, 14, 13, 28, 136, 41, 135, 501, 
	Strip(0x0, 3),  160, 236, 65, 
	Strip(0x0, 3),  111, 110, 396, 
	Strip(0x8000, 5),  347, 67, 382, 109, 381, 
	Strip(0x8000, 6),  475, 356, 480, 355, 456, 121, 
	Strip(0x0, 3),  487, 120, 455, 
	Strip(0x8000, 6),  486, 176, 189, 178, 188, 339, 
	Strip(0x0, 8),  485, 98, 3, 2, 511, 510, 661, 607, 
	Strip(0x8000, 5),  378, 97, 126, 377, 123, 
	Strip(0x8000, 9),  603, 123, 249, 377, 608, 484, 47, 96, 605, 
	Strip(0x8000, 12),  453, 348, 387, 105, 363, 362, 66, 357, 113, 103, 
			102, 101, 
	Strip(0x8000, 5),  453, 387, 386, 216, 138, 
	Strip(0x0, 3),  475, 474, 480, 
	Strip(0x0, 5),  523, 532, 15, 24, 191, 
	Strip(0x0, 3),  6, 7, 458, 
	Strip(0x0, 5),  463, 340, 464, 306, 187, 
	Strip(0x8000, 5),  122, 121, 461, 355, 460, 
	Strip(0x8000, 7),  461, 462, 122, 463, 465, 340, 457, 
	Strip(0x8000, 5),  319, 323, 94, 322, 428, 
	Strip(0x8000, 11),  323, 434, 322, 433, 428, 431, 427, 432, 417, 414, 
			291, 
	Strip(0x0, 3),  434, 433, 414, 
	Strip(0x0, 14),  52, 560, 559, 166, 706, 513, 515, 514, 596, 675, 
			283, 78, 726, 125, 
	Strip(0x8000, 16),  53, 54, 49, 50, 558, 521, 346, 646, 690, 647, 
			287, 644, 726, 634, 446, 274, 
	Strip(0x0, 4),  246, 266, 308, 262, 
	Strip(0x8000, 11),  87, 90, 56, 599, 564, 452, 676, 459, 601, 600, 
			91, 
	Strip(0x0, 7),  56, 87, 167, 248, 92, 91, 601, 
	Strip(0x0, 3),  104, 105, 362, 
	Strip(0x0, 12),  676, 564, 677, 56, 168, 167, 353, 312, 236, 68, 
			65, 312, 
	Strip(0x0, 10),  398, 108, 106, 101, 107, 102, 408, 113, 402, 112, 
	Strip(0x8000, 5),  107, 106, 111, 398, 396, 
	Strip(0x8000, 5),  71, 69, 383, 335, 334, 
	Strip(0x0, 3),  60, 59, 568, 
	Strip(0x0, 8),  59, 567, 568, 792, 304, 467, 172, 630, 
	Strip(0x0, 14),  356, 59, 475, 60, 474, 568, 493, 304, 169, 172, 
			152, 630, 535, 716, 
	Strip(0x8000, 11),  126, 174, 378, 8, 31, 516, 661, 294, 607, 606, 
			97, 
	Strip(0x0, 6),  64, 63, 61, 62, 500, 454, 
	Strip(0x0, 3),  89, 85, 88, 
	Strip(0x8000, 9),  88, 86, 85, 83, 84, 74, 200, 73, 199, 
	Strip(0x0, 7),  167, 92, 312, 376, 65, 384, 354, 
	Strip(0x0, 3),  306, 340, 341, 
	Strip(0x0, 6),  341, 356, 306, 355, 187, 460, 
	Strip(0x8000, 15),  341, 188, 340, 339, 457, 343, 122, 120, 121, 455, 
			456, 483, 480, 481, 474, 
	Strip(0x0, 14),  334, 333, 335, 336, 381, 101, 109, 108, 67, 110, 
			66, 111, 112, 107, 
	Strip(0x8000, 6),  313, 314, 134, 131, 133, 132, 
	Strip(0x0, 7),  216, 507, 66, 75, 67, 793, 347, 
	Strip(0x0, 4),  66, 363, 216, 387, 
	Strip(0x8000, 8),  147, 146, 291, 325, 417, 94, 427, 428, 
	Strip(0x0, 7),  147, 164, 291, 163, 414, 430, 434, 
	Strip(0x0, 12),  245, 281, 190, 265, 12, 1, 520, 509, 700, 775, 
			755, 790, 
	Strip(0x8000, 5),  180, 266, 267, 262, 268, 
	Strip(0x8000, 10),  148, 132, 149, 131, 39, 324, 38, 316, 318, 315, 
	Strip(0x8000, 7),  245, 191, 190, 15, 12, 523, 520, 
	Strip(0x0, 6),  47, 555, 605, 518, 660, 586, 
	Strip(0x0, 6),  607, 98, 97, 485, 378, 31, 
	Strip(0x0, 3),  50, 100, 54, 
	Strip(0x8000, 10),  147, 148, 146, 149, 325, 39, 94, 38, 319, 318, 
	Strip(0x0, 5),  135, 137, 136, 351, 13, 
	Strip(0x0, 8),  101, 105, 103, 104, 494, 362, 404, 357, 
	Strip(0x0, 3),  112, 113, 66, 
	Strip(0x0, 3),  73, 771, 74, 
	Strip(0x0, 4),  332, 151, 572, 332, 
	Strip(0x0, 3),  274, 440, 634, 
	Strip(0x8000, 6),  634, 151, 440, 569, 674, 570, 
	Strip(0x8000, 7),  644, 443, 634, 438, 151, 572, 569, 
	Strip(0x8000, 6),  726, 283, 287, 596, 282, 317, 
	Strip(0x0, 6),  574, 773, 622, 611, 289, 389, 
	Strip(0x0, 14),  358, 688, 618, 575, 619, 574, 620, 621, 615, 616, 
			610, 611, 612, 773, 
	Strip(0x0, 4),  615, 590, 620, 619, 
	Strip(0x8000, 12),  590, 588, 615, 617, 610, 618, 780, 360, 301, 578, 
			580, 581, 
	Strip(0x0, 6),  445, 77, 613, 78, 614, 675, 
	Strip(0x0, 9),  716, 630, 629, 631, 436, 791, 263, 681, 307, 
	Strip(0x0, 3),  436, 757, 629, 
	Strip(0x8000, 6),  685, 286, 687, 699, 786, 698, 
	Strip(0x8000, 5),  661, 511, 31, 3, 485, 
	Strip(0x8000, 8),  169, 328, 152, 284, 535, 482, 455, 483, 
	Strip(0x0, 9),  690, 346, 609, 558, 557, 49, 48, 53, 196, 
	Strip(0x8000, 7),  381, 335, 793, 69, 70, 71, 72, 
	Strip(0x0, 3),  317, 515, 596, 
	Strip(0x0, 3),  282, 287, 690, 
	Strip(0x0, 4),  259, 697, 307, 263, 
	Strip(0x8000, 12),  192, 702, 630, 259, 467, 697, 794, 263, 698, 436, 
			786, 757, 
	Strip(0x8000, 6),  630, 631, 192, 791, 678, 681, 
	Strip(0x0, 4),  276, 426, 93, 435, 
	Strip(0x0, 12),  403, 393, 476, 673, 655, 656, 658, 657, 640, 641, 
			643, 642, 
	Strip(0x8000, 7),  435, 320, 426, 425, 276, 424, 277, 
	Strip(0x0, 9),  689, 25, 532, 180, 24, 266, 191, 246, 245, 
	Strip(0x8000, 29),  562, 561, 556, 559, 51, 52, 349, 344, 5, 348, 
			6, 453, 458, 386, 471, 138, 472, 137, 100, 351, 
			50, 13, 521, 522, 645, 536, 644, 549, 443, 
	Strip(0x0, 6),  93, 270, 546, 547, 279, 269, 
	Strip(0x0, 8),  584, 125, 574, 78, 773, 77, 577, 445, 
	Strip(0x0, 3),  611, 616, 389, 
	Strip(0x0, 3),  617, 618, 619, 
	Strip(0x8000, 7),  468, 668, 235, 21, 745, 676, 601, 
	Strip(0x0, 3),  618, 360, 358, 
	Strip(0x0, 5),  569, 570, 572, 571, 422, 
	Strip(0x8000, 5),  574, 584, 575, 469, 688, 
	Strip(0x0, 3),  586, 632, 635, 
	Strip(0x0, 7),  555, 693, 518, 759, 586, 602, 632, 
	Strip(0x0, 5),  581, 579, 578, 469, 360, 
	Strip(0x0, 9),  582, 709, 583, 710, 592, 593, 595, 594, 598, 
	Strip(0x0, 3),  597, 595, 598, 
	Strip(0x0, 8),  676, 677, 21, 478, 159, 746, 668, 669, 
	Strip(0x0, 3),  467, 792, 794, 
	Strip(0x0, 6),  675, 514, 758, 513, 560, 166, 
	Strip(0x8000, 6),  354, 65, 158, 160, 161, 310, 
	Strip(0x8000, 6),  512, 780, 261, 301, 361, 580, 
	Strip(0x0, 12),  640, 269, 658, 547, 655, 270, 476, 93, 403, 435, 
			393, 320, 
	Strip(0x0, 8),  279, 539, 546, 247, 93, 285, 276, 277, 
	Strip(0x0, 4),  643, 533, 640, 350, 
	Strip(0x0, 3),  21, 159, 668, 
	Strip(0x8000, 8),  778, 772, 776, 751, 701, 756, 700, 755, 
	Strip(0x0, 3),  778, 777, 776, 
	Strip(0x8000, 8),  689, 777, 532, 776, 523, 701, 520, 700, 
	Strip(0x0, 3),  559, 706, 561, 
	Strip(0x8000, 7),  684, 516, 517, 8, 9, 174, 175, 
	Strip(0x8000, 7),  684, 683, 516, 635, 294, 586, 606, 
	Strip(0x8000, 5),  644, 647, 645, 646, 521, 
	Strip(0x0, 5),  614, 610, 613, 612, 445, 
	Strip(0x0, 4),  574, 622, 621, 289, 
	Strip(0x0, 3),  583, 466, 582, 
	Strip(0x0, 3),  602, 759, 693, 
	Strip(0x8000, 10),  603, 249, 183, 608, 46, 47, 671, 555, 554, 693, 
	Strip(0x0, 3),  422, 438, 572, 
	Strip(0x8000, 5),  388, 473, 502, 505, 501, 
	Strip(0x8000, 6),  468, 667, 668, 670, 669, 162, 
	Strip(0x8000, 7),  673, 672, 393, 321, 424, 416, 277, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x8000, 8),  489, 492, 491, 490, 204, 206, 768, 784, 
	Strip(0x0, 4),  491, 489, 487, 488, 
	Strip(0x0, 8),  377, 484, 97, 96, 606, 605, 586, 660, 
	Strip(0x0, 4),  431, 432, 433, 414, 
	Strip(0x0, 4),  34, 33, 30, 373, 
	Strip(0x0, 4),  439, 437, 375, 374, 
	Strip(0x8000, 11),  89, 203, 202, 411, 280, 130, 256, 129, 257, 298, 
			243, 
	Strip(0x0, 4),  224, 420, 76, 297, 
	Strip(0x0, 4),  182, 244, 242, 243, 
	Strip(0x8000, 12),  244, 183, 182, 46, 181, 671, 32, 554, 691, 693, 
			692, 752, 
	Strip(0x0, 4),  370, 367, 372, 368, 
	Strip(0x0, 4),  365, 352, 366, 57, 
	Strip(0x8000, 5),  314, 315, 131, 316, 324, 
	Strip(0x0, 4),  607, 510, 98, 2, 
	Strip(0x8000, 10),  176, 177, 178, 338, 339, 342, 343, 488, 120, 487, 
	Strip(0x8000, 6),  784, 206, 519, 490, 11, 492, 
	Strip(0x0, 6),  768, 204, 535, 491, 455, 487, 
	Strip(0x0, 4),  629, 768, 716, 535, 
	Strip(0x0, 4),  424, 393, 425, 320, 
	Strip(0x0, 4),  541, 542, 576, 538, 
	Strip(0x0, 4),  253, 423, 429, 573, 
	Strip(0x8000, 11),  713, 598, 392, 712, 639, 789, 638, 766, 385, 767, 
			753, 
	Strip(0x0, 4),  399, 734, 470, 585, 
	Strip(0x0, 4),  693, 752, 754, 753, 
	Strip(0x0, 4),  604, 55, 415, 563, 
	Strip(0x0, 4),  81, 565, 79, 345, 
	Strip(0x8000, 5),  539, 350, 279, 640, 269, 
	Strip(0x8000, 10),  685, 687, 686, 786, 787, 757, 795, 629, 40, 768, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x8000, 6),  139, 308, 140, 246, 290, 245, 
	Strip(0x8000, 14),  268, 242, 267, 182, 180, 181, 25, 32, 689, 691, 
			777, 692, 778, 752, 
	Strip(0x8000, 5),  154, 281, 171, 309, 170, 
	Strip(0x0, 3),  262, 243, 260, 
	Strip(0x0, 3),  19, 16, 217, 
	Strip(0x8000, 6),  18, 17, 239, 234, 264, 233, 
	Strip(0x8000, 9),  1, 0, 265, 240, 239, 238, 18, 237, 0, 
	Strip(0x0, 4),  222, 218, 228, 217, 
	Strip(0x8000, 5),  195, 229, 705, 739, 740, 
	Strip(0x0, 7),  239, 265, 264, 193, 184, 186, 185, 
	Strip(0x0, 3),  566, 695, 724, 
	Strip(0x0, 3),  234, 233, 232, 
	Strip(0x0, 3),  16, 17, 231, 
	Strip(0x0, 8),  229, 230, 195, 214, 185, 215, 184, 208, 
	Strip(0x0, 6),  19, 222, 20, 228, 22, 209, 
	Strip(0x0, 6),  215, 214, 213, 221, 219, 220, 
	Strip(0x0, 14),  22, 212, 23, 207, 208, 209, 184, 228, 264, 217, 
			233, 16, 232, 231, 
	Strip(0x8000, 6),  751, 648, 756, 649, 755, 4, 
	Strip(0x8000, 5),  790, 663, 241, 680, 679, 
	Strip(0x0, 3),  772, 770, 753, 
	Strip(0x0, 9),  527, 727, 743, 774, 744, 775, 749, 750, 748, 
	Strip(0x0, 3),  743, 524, 527, 
	Strip(0x0, 6),  525, 744, 526, 749, 747, 748, 
	Strip(0x0, 5),  530, 719, 528, 738, 728, 
	Strip(0x8000, 5),  723, 724, 729, 731, 730, 
	Strip(0x0, 4),  775, 509, 750, 508, 
	Strip(0x0, 4),  728, 732, 528, 527, 
	Strip(0x8000, 5),  775, 703, 774, 696, 694, 
	Strip(0x0, 3),  747, 508, 526, 
	Strip(0x0, 6),  525, 524, 741, 743, 742, 744, 
	Strip(0x0, 6),  530, 531, 722, 718, 717, 719, 
	Strip(0x8000, 6),  696, 695, 694, 724, 725, 723, 
	Strip(0x8000, 20),  725, 730, 531, 23, 530, 22, 528, 20, 527, 19, 
			524, 16, 525, 17, 526, 18, 508, 0, 509, 1, 
			
	Strip(0x0, 9),  531, 725, 718, 694, 719, 774, 738, 727, 728, 
	Strip(0x0, 3),  215, 220, 208, 
	Strip(0x8000, 13),  208, 23, 220, 730, 221, 731, 740, 724, 705, 566, 
			195, 58, 185, 
	Strip(0x0, 4),  740, 221, 230, 214, 
END

POLYGON     pgS_3_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x0, 6),  418, 303, 406, 302, 380, 379, 
	Strip(0x0, 5),  380, 405, 406, 407, 418, 
	Strip(0x0, 6),  587, 479, 326, 179, 329, 390, 
	Strip(0x8000, 5),  391, 329, 359, 326, 587, 
END

POLYGON     pgS_4_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x8000, 5),  281, 194, 309, 227, 170, 
	Strip(0x0, 4),  260, 139, 262, 308, 
	Strip(0x0, 4),  281, 245, 154, 290, 
	Strip(0x8000, 5),  790, 241, 704, 679, 737, 
	Strip(0x0, 4),  772, 751, 770, 648, 
	Strip(0x0, 4),  663, 4, 790, 755, 
END

POLYGON     pgS_5_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x8000, 13),  372, 497, 374, 454, 272, 500, 43, 44, 42, 45, 
			210, 413, 771, 
	Strip(0x0, 3),  497, 454, 769, 
	Strip(0x8000, 8),  44, 500, 157, 499, 75, 495, 507, 216, 
	Strip(0x8000, 11),  337, 292, 498, 254, 293, 128, 255, 127, 410, 130, 
			411, 
	Strip(0x8000, 8),  70, 72, 157, 223, 44, 173, 45, 413, 
	Strip(0x0, 3),  380, 379, 116, 
	Strip(0x0, 8),  272, 99, 271, 156, 226, 145, 224, 225, 
	Strip(0x8000, 6),  447, 444, 275, 451, 437, 439, 
	Strip(0x8000, 5),  99, 450, 449, 150, 153, 
	Strip(0x8000, 13),  437, 374, 275, 272, 447, 99, 444, 449, 451, 153, 
			439, 150, 375, 
	Strip(0x8000, 5),  419, 330, 421, 331, 82, 
	Strip(0x0, 3),  80, 412, 529, 
	Strip(0x0, 4),  410, 205, 411, 203, 
	Strip(0x0, 9),  243, 244, 298, 252, 299, 251, 296, 295, 292, 
	Strip(0x0, 9),  154, 290, 144, 140, 141, 139, 142, 260, 243, 
	Strip(0x8000, 11),  156, 155, 99, 227, 450, 186, 150, 185, 375, 368, 
			372, 
	Strip(0x0, 4),  118, 119, 175, 174, 
	Strip(0x0, 3),  58, 185, 368, 
	Strip(0x0, 4),  70, 793, 157, 75, 
	Strip(0x0, 7),  129, 298, 128, 299, 254, 296, 292, 
	Strip(0x0, 3),  372, 375, 374, 
	Strip(0x0, 3),  26, 33, 34, 
	Strip(0x0, 21),  117, 337, 116, 292, 380, 295, 405, 300, 407, 124, 
			418, 123, 303, 126, 302, 174, 379, 119, 115, 118, 
			114, 
	Strip(0x8000, 5),  183, 250, 603, 124, 123, 
	Strip(0x0, 3),  251, 300, 295, 
	Strip(0x0, 5),  43, 272, 42, 271, 226, 
	Strip(0x8000, 7),  244, 252, 183, 251, 250, 300, 124, 
	Strip(0x0, 3),  257, 142, 243, 
	Strip(0x0, 7),  257, 256, 142, 197, 141, 143, 144, 
	Strip(0x0, 3),  198, 225, 145, 
	Strip(0x0, 6),  210, 42, 211, 226, 76, 224, 
	Strip(0x0, 17),  89, 88, 201, 80, 273, 529, 197, 198, 143, 145, 
			144, 156, 154, 155, 171, 227, 170, 
	Strip(0x0, 7),  89, 201, 202, 273, 280, 197, 256, 
	Strip(0x0, 3),  86, 80, 88, 
	Strip(0x0, 13),  86, 83, 80, 82, 412, 421, 529, 419, 198, 330, 
			225, 420, 224, 
	Strip(0x0, 4),  128, 127, 129, 130, 
	Strip(0x8000, 5),  117, 114, 116, 115, 379, 
	Strip(0x8000, 6),  83, 76, 74, 211, 771, 210, 
	Strip(0x8000, 7),  83, 82, 76, 331, 297, 330, 420, 
	Strip(0x0, 4),  604, 442, 674, 258, 
	Strip(0x8000, 9),  674, 551, 440, 552, 274, 666, 446, 584, 125, 
	Strip(0x0, 22),  448, 779, 477, 626, 625, 624, 587, 628, 479, 683, 
			179, 635, 390, 633, 27, 761, 288, 762, 165, 754, 
			385, 753, 
	Strip(0x0, 3),  477, 764, 448, 
	Strip(0x0, 3),  733, 552, 666, 
	Strip(0x8000, 14),  573, 429, 662, 253, 659, 696, 504, 10, 503, 714, 
			662, 545, 573, 423, 
	Strip(0x0, 12),  587, 359, 625, 391, 477, 540, 764, 288, 637, 165, 
			638, 385, 
	Strip(0x0, 3),  27, 329, 390, 
	Strip(0x0, 3),  10, 737, 696, 
	Strip(0x0, 4),  503, 504, 662, 659, 
	Strip(0x0, 6),  10, 714, 305, 545, 785, 423, 
	Strip(0x0, 6),  550, 551, 553, 552, 682, 733, 
	Strip(0x0, 3),  765, 636, 395, 
	Strip(0x8000, 6),  636, 637, 765, 764, 95, 448, 
	Strip(0x8000, 10),  734, 278, 399, 788, 470, 591, 585, 583, 721, 720, 
	Strip(0x0, 9),  654, 653, 736, 665, 550, 781, 551, 782, 674, 
	Strip(0x0, 4),  679, 664, 680, 663, 
	Strip(0x0, 14),  679, 737, 664, 10, 781, 305, 782, 785, 674, 423, 
			604, 253, 695, 696, 
	Strip(0x0, 14),  682, 327, 553, 720, 550, 721, 736, 734, 735, 278, 
			397, 788, 364, 591, 
	Strip(0x8000, 8),  715, 713, 395, 392, 636, 639, 637, 638, 
	Strip(0x8000, 15),  663, 4, 653, 650, 654, 652, 735, 708, 397, 311, 
			364, 401, 591, 592, 583, 
	Strip(0x8000, 12),  648, 770, 651, 767, 707, 766, 783, 789, 711, 712, 
			597, 598, 
	Strip(0x0, 5),  781, 665, 664, 653, 663, 
	Strip(0x8000, 9),  595, 592, 589, 401, 783, 311, 707, 708, 652, 
	Strip(0x0, 4),  604, 695, 55, 566, 
	Strip(0x0, 7),  63, 473, 62, 400, 454, 548, 769, 
	Strip(0x8000, 6),  693, 602, 760, 632, 633, 635, 
	Strip(0x0, 4),  583, 720, 466, 327, 
	Strip(0x8000, 5),  288, 27, 540, 329, 391, 
	Strip(0x8000, 6),  633, 761, 760, 762, 693, 754, 
	Strip(0x8000, 6),  707, 652, 651, 650, 649, 4, 
	Strip(0x0, 3),  753, 770, 767, 
	Strip(0x0, 3),  735, 654, 736, 
	Strip(0x8000, 5),  597, 595, 711, 589, 783, 
	Strip(0x0, 3),  648, 649, 651, 
	Strip(0x8000, 7),  626, 624, 623, 628, 627, 683, 684, 
	Strip(0x0, 3),  125, 446, 726, 
	Strip(0x0, 6),  584, 469, 666, 579, 733, 581, 
	Strip(0x0, 3),  422, 571, 409, 
	Strip(0x0, 6),  571, 570, 409, 674, 37, 258, 
	Strip(0x0, 3),  585, 734, 721, 
END

POLYGON     pgS_6_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x0, 4),  262, 268, 243, 242, 
	Strip(0x8000, 6),  186, 227, 193, 194, 265, 281, 
	Strip(0x0, 4),  753, 752, 772, 778, 
	Strip(0x8000, 5),  790, 704, 703, 737, 696, 
	Strip(0x0, 3),  790, 775, 703, 
END

POLYGON     pgS_7_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	Strip(0x0, 4),  366, 496, 41, 501, 
	Strip(0x8000, 7),  14, 28, 29, 41, 35, 366, 365, 
	Strip(0x8000, 8),  30, 34, 29, 26, 14, 534, 522, 536, 
	Strip(0x0, 5),  33, 36, 373, 35, 29, 
	Strip(0x0, 3),  565, 566, 58, 
	Strip(0x8000, 10),  534, 26, 541, 33, 544, 36, 565, 57, 58, 368, 
	Strip(0x8000, 5),  35, 365, 36, 352, 57, 
	Strip(0x8000, 6),  367, 369, 370, 371, 372, 497, 
	Strip(0x8000, 10),  57, 366, 371, 496, 497, 501, 769, 505, 548, 400, 
	Strip(0x0, 5),  371, 57, 369, 368, 367, 
	Strip(0x0, 3),  373, 29, 30, 
	Strip(0x0, 4),  442, 441, 443, 549, 
	Strip(0x0, 8),  534, 536, 537, 549, 576, 543, 541, 544, 
	Strip(0x0, 5),  763, 415, 394, 563, 55, 
	Strip(0x8000, 6),  566, 55, 565, 394, 81, 763, 
	Strip(0x8000, 6),  576, 537, 538, 534, 542, 541, 
	Strip(0x8000, 8),  415, 604, 763, 442, 81, 441, 543, 549, 
	Strip(0x0, 6),  565, 544, 345, 543, 79, 81, 
	Strip(0x0, 3),  473, 505, 400, 
	Strip(0x0, 3),  409, 37, 422, 
	Strip(0x8000, 6),  422, 438, 37, 443, 258, 442, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	UV( 70, 60 ),
	UV( 70, 40 ),
	UV( 70, 56 ),
	UV( 71, 40 ),
	UV( 71, 40 ),
	UV( 70, 40 ),
	UV( 70, 40 ),
	UV( 70, 60 ),
	UV( 70, 40 ),
	UV( 71, 40 ),
	UV( 72, 40 ),
	UV( 73, 40 ),
	UV( 74, 40 ),
	UV( 77, 40 ),
	UV( 88, 39 ),
	UV( 70, 60 ),
	UV( 71, 53 ),
	UV( 71, 40 ),
	UV( 72, 46 ),
	UV( 73, 40 ),
	UV( 75, 40 ),
	UV( 88, 39 ),
	UV( 75, 43 ),
	UV( 111, 38 ),
	UV( 126, 41 ),
	UV( 126, 38 ),
	UV( 126, 38 ),
	UV( 127, 38 ),
	UV( 127, 38 ),
	UV( 127, 41 ),
	UV( 127, 41 ),
	UV( 83, 211 ),
	UV( 79, 210 ),
	UV( 80, 210 ),
	UV( 142, 39 ),
	UV( 111, 39 ),
	UV( 111, 38 ),
	UV( 88, 39 ),
	UV( 88, 39 ),
	UV( 74, 40 ),
	UV( 74, 40 ),
	UV( 72, 40 ),
	UV( 69, 52 ),
	UV( 89, 52 ),
	UV( 71, 40 ),
	UV( 70, 47 ),
	UV( 70, 48 ),
	UV( 70, 48 ),
	UV( 70, 51 ),
	UV( 69, 49 ),
	UV( 69, 51 ),
	UV( 68, 49 ),
	UV( 68, 51 ),
	UV( 98, 213 ),
	UV( 95, 213 ),
	UV( 97, 213 ),
	UV( 95, 213 ),
	UV( 98, 214 ),
	UV( 95, 214 ),
	UV( 101, 214 ),
	UV( 95, 214 ),
	UV( 101, 214 ),
	UV( 69, 186 ),
	UV( 69, 186 ),
	UV( 74, 202 ),
	UV( 74, 202 ),
	UV( 77, 208 ),
	UV( 77, 208 ),
	UV( 125, 202 ),
	UV( 123, 200 ),
	UV( 125, 202 ),
	UV( 123, 200 ),
	UV( 128, 202 ),
	UV( 130, 200 ),
	UV( 128, 202 ),
	UV( 130, 200 ),
	UV( 111, 202 ),
	UV( 111, 189 ),
	UV( 96, 202 ),
	UV( 102, 189 ),
	UV( 96, 189 ),
	UV( 96, 176 ),
	UV( 96, 189 ),
	UV( 98, 176 ),
	UV( 102, 189 ),
	UV( 98, 176 ),
	UV( 102, 189 ),
	UV( 111, 177 ),
	UV( 111, 189 ),
	UV( 142, 189 ),
	UV( 74, 40 ),
	UV( 70, 40 ),
	UV( 72, 40 ),
	UV( 70, 40 ),
	UV( 72, 40 ),
	UV( 71, 43 ),
	UV( 70, 46 ),
	UV( 70, 44 ),
	UV( 70, 45 ),
	UV( 69, 44 ),
	UV( 69, 45 ),
	UV( 69, 46 ),
	UV( 74, 40 ),
	UV( 72, 40 ),
	UV( 75, 40 ),
	UV( 73, 40 ),
	UV( 77, 40 ),
	UV( 98, 213 ),
	UV( 98, 210 ),
	UV( 97, 213 ),
	UV( 140, 123 ),
	UV( 140, 129 ),
	UV( 113, 123 ),
	UV( 113, 129 ),
	UV( 99, 123 ),
	UV( 75, 40 ),
	UV( 75, 43 ),
	UV( 74, 43 ),
	UV( 80, 207 ),
	UV( 79, 209 ),
	UV( 79, 206 ),
	UV( 80, 210 ),
	UV( 80, 207 ),
	UV( 83, 211 ),
	UV( 95, 214 ),
	UV( 92, 211 ),
	UV( 95, 213 ),
	UV( 92, 210 ),
	UV( 92, 211 ),
	UV( 83, 208 ),
	UV( 83, 211 ),
	UV( 80, 207 ),
	UV( 80, 210 ),
	UV( 79, 209 ),
	UV( 79, 210 ),
	UV( 67, 105 ),
	UV( 67, 95 ),
	UV( 67, 105 ),
	UV( 66, 95 ),
	UV( 67, 95 ),
	UV( 67, 95 ),
	UV( 66, 85 ),
	UV( 66, 95 ),
	UV( 66, 91 ),
	UV( 67, 95 ),
	UV( 67, 91 ),
	UV( 68, 95 ),
	UV( 69, 91 ),
	UV( 67, 95 ),
	UV( 67, 91 ),
	UV( 67, 95 ),
	UV( 66, 85 ),
	UV( 66, 91 ),
	UV( 67, 91 ),
	UV( 111, 38 ),
	UV( 142, 38 ),
	UV( 127, 38 ),
	UV( 142, 38 ),
	UV( 127, 41 ),
	UV( 165, 39 ),
	UV( 178, 43 ),
	UV( 178, 40 ),
	UV( 179, 40 ),
	UV( 183, 40 ),
	UV( 181, 40 ),
	UV( 181, 40 ),
	UV( 180, 40 ),
	UV( 182, 46 ),
	UV( 126, 41 ),
	UV( 126, 41 ),
	UV( 126, 38 ),
	UV( 126, 38 ),
	UV( 127, 38 ),
	UV( 142, 38 ),
	UV( 142, 38 ),
	UV( 165, 39 ),
	UV( 176, 43 ),
	UV( 176, 40 ),
	UV( 178, 40 ),
	UV( 178, 40 ),
	UV( 180, 40 ),
	UV( 182, 40 ),
	UV( 181, 46 ),
	UV( 182, 53 ),
	UV( 93, 123 ),
	UV( 99, 129 ),
	UV( 93, 128 ),
	UV( 92, 130 ),
	UV( 118, 38 ),
	UV( 120, 38 ),
	UV( 117, 38 ),
	UV( 133, 38 ),
	UV( 135, 38 ),
	UV( 135, 38 ),
	UV( 138, 38 ),
	UV( 135, 38 ),
	UV( 142, 38 ),
	UV( 133, 38 ),
	UV( 120, 38 ),
	UV( 117, 38 ),
	UV( 118, 38 ),
	UV( 115, 38 ),
	UV( 118, 38 ),
	UV( 111, 38 ),
	UV( 120, 38 ),
	UV( 142, 38 ),
	UV( 69, 43 ),
	UV( 70, 40 ),
	UV( 71, 43 ),
	UV( 138, 38 ),
	UV( 135, 38 ),
	UV( 143, 53 ),
	UV( 117, 38 ),
	UV( 110, 53 ),
	UV( 115, 38 ),
	UV( 90, 53 ),
	UV( 88, 39 ),
	UV( 89, 52 ),
	UV( 87, 39 ),
	UV( 71, 40 ),
	UV( 88, 39 ),
	UV( 69, 48 ),
	UV( 68, 48 ),
	UV( 69, 47 ),
	UV( 69, 46 ),
	UV( 69, 46 ),
	UV( 69, 45 ),
	UV( 69, 46 ),
	UV( 70, 45 ),
	UV( 71, 46 ),
	UV( 70, 46 ),
	UV( 69, 46 ),
	UV( 69, 47 ),
	UV( 70, 47 ),
	UV( 69, 48 ),
	UV( 70, 48 ),
	UV( 67, 63 ),
	UV( 68, 53 ),
	UV( 67, 60 ),
	UV( 68, 53 ),
	UV( 67, 58 ),
	UV( 111, 214 ),
	UV( 111, 214 ),
	UV( 142, 214 ),
	UV( 111, 214 ),
	UV( 142, 214 ),
	UV( 142, 214 ),
	UV( 158, 213 ),
	UV( 155, 213 ),
	UV( 158, 213 ),
	UV( 156, 213 ),
	UV( 158, 214 ),
	UV( 95, 213 ),
	UV( 111, 214 ),
	UV( 98, 213 ),
	UV( 111, 214 ),
	UV( 98, 210 ),
	UV( 142, 214 ),
	UV( 155, 210 ),
	UV( 155, 213 ),
	UV( 156, 210 ),
	UV( 156, 213 ),
	UV( 155, 214 ),
	UV( 158, 214 ),
	UV( 152, 214 ),
	UV( 152, 214 ),
	UV( 96, 202 ),
	UV( 95, 213 ),
	UV( 111, 202 ),
	UV( 111, 214 ),
	UV( 126, 207 ),
	UV( 142, 214 ),
	UV( 128, 202 ),
	UV( 142, 202 ),
	UV( 130, 200 ),
	UV( 142, 189 ),
	UV( 111, 189 ),
	UV( 70, 40 ),
	UV( 71, 40 ),
	UV( 70, 56 ),
	UV( 71, 56 ),
	UV( 70, 60 ),
	UV( 71, 60 ),
	UV( 71, 155 ),
	UV( 71, 123 ),
	UV( 71, 142 ),
	UV( 71, 142 ),
	UV( 71, 123 ),
	UV( 71, 123 ),
	UV( 68, 105 ),
	UV( 68, 105 ),
	UV( 67, 95 ),
	UV( 68, 95 ),
	UV( 66, 83 ),
	UV( 66, 84 ),
	UV( 115, 38 ),
	UV( 111, 38 ),
	UV( 88, 39 ),
	UV( 88, 39 ),
	UV( 71, 40 ),
	UV( 70, 40 ),
	UV( 69, 40 ),
	UV( 80, 210 ),
	UV( 79, 209 ),
	UV( 79, 209 ),
	UV( 79, 209 ),
	UV( 95, 213 ),
	UV( 80, 210 ),
	UV( 95, 213 ),
	UV( 80, 207 ),
	UV( 92, 210 ),
	UV( 79, 209 ),
	UV( 77, 208 ),
	UV( 79, 209 ),
	UV( 77, 208 ),
	UV( 79, 210 ),
	UV( 79, 210 ),
	UV( 83, 211 ),
	UV( 95, 214 ),
	UV( 95, 214 ),
	UV( 101, 214 ),
	UV( 98, 214 ),
	UV( 98, 211 ),
	UV( 97, 213 ),
	UV( 97, 210 ),
	UV( 98, 210 ),
	UV( 67, 58 ),
	UV( 67, 57 ),
	UV( 68, 53 ),
	UV( 68, 53 ),
	UV( 68, 51 ),
	UV( 69, 46 ),
	UV( 68, 49 ),
	UV( 68, 48 ),
	UV( 69, 49 ),
	UV( 70, 48 ),
	UV( 70, 46 ),
	UV( 70, 47 ),
	UV( 70, 46 ),
	UV( 69, 46 ),
	UV( 68, 161 ),
	UV( 68, 155 ),
	UV( 69, 159 ),
	UV( 69, 154 ),
	UV( 70, 158 ),
	UV( 70, 154 ),
	UV( 73, 40 ),
	UV( 71, 46 ),
	UV( 70, 46 ),
	UV( 70, 48 ),
	UV( 69, 49 ),
	UV( 69, 51 ),
	UV( 70, 51 ),
	UV( 70, 46 ),
	UV( 72, 40 ),
	UV( 73, 40 ),
	UV( 72, 40 ),
	UV( 68, 105 ),
	UV( 67, 105 ),
	UV( 67, 95 ),
	UV( 68, 105 ),
	UV( 67, 95 ),
	UV( 67, 105 ),
	UV( 68, 95 ),
	UV( 67, 95 ),
	UV( 68, 105 ),
	UV( 68, 95 ),
	UV( 67, 95 ),
	UV( 68, 86 ),
	UV( 67, 91 ),
	UV( 66, 85 ),
	UV( 66, 85 ),
	UV( 93, 106 ),
	UV( 93, 104 ),
	UV( 99, 109 ),
	UV( 99, 96 ),
	UV( 113, 109 ),
	UV( 113, 96 ),
	UV( 140, 109 ),
	UV( 140, 96 ),
	UV( 154, 109 ),
	UV( 154, 96 ),
	UV( 160, 106 ),
	UV( 160, 104 ),
	UV( 113, 134 ),
	UV( 99, 129 ),
	UV( 99, 134 ),
	UV( 92, 130 ),
	UV( 95, 133 ),
	UV( 69, 123 ),
	UV( 70, 154 ),
	UV( 68, 123 ),
	UV( 69, 154 ),
	UV( 71, 123 ),
	UV( 72, 154 ),
	UV( 70, 123 ),
	UV( 71, 154 ),
	UV( 70, 123 ),
	UV( 71, 155 ),
	UV( 93, 106 ),
	UV( 99, 123 ),
	UV( 99, 109 ),
	UV( 113, 123 ),
	UV( 113, 109 ),
	UV( 140, 123 ),
	UV( 140, 109 ),
	UV( 111, 177 ),
	UV( 142, 177 ),
	UV( 142, 189 ),
	UV( 155, 176 ),
	UV( 151, 189 ),
	UV( 151, 189 ),
	UV( 130, 200 ),
	UV( 123, 200 ),
	UV( 111, 189 ),
	UV( 125, 202 ),
	UV( 111, 202 ),
	UV( 126, 207 ),
	UV( 126, 38 ),
	UV( 126, 41 ),
	UV( 126, 41 ),
	UV( 68, 105 ),
	UV( 69, 123 ),
	UV( 67, 105 ),
	UV( 68, 123 ),
	UV( 68, 105 ),
	UV( 71, 123 ),
	UV( 67, 105 ),
	UV( 70, 123 ),
	UV( 67, 105 ),
	UV( 70, 123 ),
	UV( 74, 40 ),
	UV( 88, 39 ),
	UV( 88, 39 ),
	UV( 111, 38 ),
	UV( 111, 38 ),
	UV( 69, 46 ),
	UV( 70, 40 ),
	UV( 69, 44 ),
	UV( 69, 43 ),
	UV( 70, 44 ),
	UV( 71, 43 ),
	UV( 71, 44 ),
	UV( 70, 44 ),
	UV( 70, 46 ),
	UV( 70, 45 ),
	UV( 70, 46 ),
	UV( 66, 83 ),
	UV( 66, 81 ),
	UV( 67, 95 ),
	UV( 183, 40 ),
	UV( 183, 40 ),
	UV( 183, 40 ),
	UV( 183, 40 ),
	UV( 182, 53 ),
	UV( 183, 60 ),
	UV( 182, 40 ),
	UV( 182, 40 ),
	UV( 183, 40 ),
	UV( 183, 60 ),
	UV( 183, 56 ),
	UV( 182, 60 ),
	UV( 182, 56 ),
	UV( 178, 40 ),
	UV( 181, 40 ),
	UV( 182, 40 ),
	UV( 182, 40 ),
	UV( 183, 40 ),
	UV( 183, 40 ),
	UV( 183, 56 ),
	UV( 180, 40 ),
	UV( 181, 40 ),
	UV( 178, 40 ),
	UV( 179, 40 ),
	UV( 178, 43 ),
	UV( 179, 43 ),
	UV( 183, 46 ),
	UV( 183, 44 ),
	UV( 183, 45 ),
	UV( 184, 45 ),
	UV( 182, 46 ),
	UV( 184, 46 ),
	UV( 184, 51 ),
	UV( 183, 51 ),
	UV( 185, 49 ),
	UV( 184, 49 ),
	UV( 183, 48 ),
	UV( 183, 46 ),
	UV( 183, 47 ),
	UV( 183, 46 ),
	UV( 184, 47 ),
	UV( 184, 46 ),
	UV( 184, 46 ),
	UV( 184, 45 ),
	UV( 184, 44 ),
	UV( 183, 44 ),
	UV( 184, 47 ),
	UV( 183, 48 ),
	UV( 183, 47 ),
	UV( 183, 48 ),
	UV( 183, 48 ),
	UV( 184, 48 ),
	UV( 184, 47 ),
	UV( 185, 48 ),
	UV( 184, 46 ),
	UV( 185, 49 ),
	UV( 185, 53 ),
	UV( 185, 51 ),
	UV( 185, 53 ),
	UV( 185, 53 ),
	UV( 186, 63 ),
	UV( 186, 65 ),
	UV( 183, 44 ),
	UV( 182, 43 ),
	UV( 183, 43 ),
	UV( 181, 40 ),
	UV( 183, 40 ),
	UV( 183, 40 ),
	UV( 152, 214 ),
	UV( 158, 214 ),
	UV( 158, 214 ),
	UV( 170, 211 ),
	UV( 174, 210 ),
	UV( 173, 210 ),
	UV( 174, 209 ),
	UV( 174, 206 ),
	UV( 173, 207 ),
	UV( 174, 210 ),
	UV( 174, 210 ),
	UV( 158, 214 ),
	UV( 184, 186 ),
	UV( 184, 186 ),
	UV( 179, 202 ),
	UV( 179, 202 ),
	UV( 176, 208 ),
	UV( 176, 208 ),
	UV( 128, 202 ),
	UV( 128, 202 ),
	UV( 126, 207 ),
	UV( 125, 202 ),
	UV( 125, 202 ),
	UV( 156, 210 ),
	UV( 155, 211 ),
	UV( 155, 214 ),
	UV( 152, 211 ),
	UV( 152, 214 ),
	UV( 101, 211 ),
	UV( 101, 214 ),
	UV( 98, 211 ),
	UV( 176, 43 ),
	UV( 142, 38 ),
	UV( 127, 41 ),
	UV( 127, 38 ),
	UV( 127, 38 ),
	UV( 126, 38 ),
	UV( 126, 38 ),
	UV( 126, 41 ),
	UV( 126, 41 ),
	UV( 68, 51 ),
	UV( 68, 53 ),
	UV( 69, 51 ),
	UV( 68, 53 ),
	UV( 69, 53 ),
	UV( 67, 63 ),
	UV( 67, 65 ),
	UV( 179, 43 ),
	UV( 178, 43 ),
	UV( 179, 40 ),
	UV( 178, 43 ),
	UV( 178, 40 ),
	UV( 176, 43 ),
	UV( 161, 210 ),
	UV( 173, 210 ),
	UV( 173, 207 ),
	UV( 174, 209 ),
	UV( 170, 208 ),
	UV( 161, 211 ),
	UV( 158, 214 ),
	UV( 161, 210 ),
	UV( 158, 213 ),
	UV( 173, 210 ),
	UV( 174, 209 ),
	UV( 174, 209 ),
	UV( 176, 208 ),
	UV( 174, 210 ),
	UV( 176, 208 ),
	UV( 174, 210 ),
	UV( 158, 214 ),
	UV( 170, 211 ),
	UV( 170, 208 ),
	UV( 173, 210 ),
	UV( 173, 207 ),
	UV( 174, 206 ),
	UV( 187, 95 ),
	UV( 186, 95 ),
	UV( 186, 105 ),
	UV( 185, 95 ),
	UV( 186, 95 ),
	UV( 186, 91 ),
	UV( 186, 95 ),
	UV( 185, 95 ),
	UV( 186, 105 ),
	UV( 185, 105 ),
	UV( 185, 123 ),
	UV( 184, 123 ),
	UV( 184, 154 ),
	UV( 183, 154 ),
	UV( 184, 159 ),
	UV( 183, 158 ),
	UV( 185, 95 ),
	UV( 184, 91 ),
	UV( 186, 95 ),
	UV( 186, 91 ),
	UV( 187, 95 ),
	UV( 187, 91 ),
	UV( 186, 95 ),
	UV( 140, 134 ),
	UV( 126, 134 ),
	UV( 140, 129 ),
	UV( 113, 134 ),
	UV( 113, 129 ),
	UV( 99, 129 ),
	UV( 99, 123 ),
	UV( 93, 123 ),
	UV( 93, 106 ),
	UV( 127, 41 ),
	UV( 127, 41 ),
	UV( 127, 38 ),
	UV( 127, 38 ),
	UV( 126, 38 ),
	UV( 111, 38 ),
	UV( 111, 38 ),
	UV( 88, 39 ),
	UV( 88, 39 ),
	UV( 70, 40 ),
	UV( 75, 40 ),
	UV( 74, 40 ),
	UV( 74, 43 ),
	UV( 75, 40 ),
	UV( 75, 43 ),
	UV( 77, 40 ),
	UV( 77, 43 ),
	UV( 88, 39 ),
	UV( 126, 41 ),
	UV( 111, 38 ),
	UV( 126, 38 ),
	UV( 111, 38 ),
	UV( 142, 38 ),
	UV( 142, 39 ),
	UV( 165, 39 ),
	UV( 165, 39 ),
	UV( 178, 40 ),
	UV( 179, 40 ),
	UV( 181, 40 ),
	UV( 186, 105 ),
	UV( 185, 105 ),
	UV( 183, 123 ),
	UV( 182, 123 ),
	UV( 182, 154 ),
	UV( 181, 154 ),
	UV( 183, 48 ),
	UV( 182, 46 ),
	UV( 183, 46 ),
	UV( 181, 40 ),
	UV( 183, 44 ),
	UV( 182, 43 ),
	UV( 182, 44 ),
	UV( 183, 44 ),
	UV( 184, 45 ),
	UV( 184, 46 ),
	UV( 184, 46 ),
	UV( 185, 48 ),
	UV( 185, 49 ),
	UV( 183, 48 ),
	UV( 183, 40 ),
	UV( 182, 40 ),
	UV( 183, 40 ),
	UV( 165, 39 ),
	UV( 165, 39 ),
	UV( 138, 38 ),
	UV( 142, 38 ),
	UV( 185, 49 ),
	UV( 185, 51 ),
	UV( 184, 51 ),
	UV( 183, 56 ),
	UV( 182, 56 ),
	UV( 183, 40 ),
	UV( 182, 40 ),
	UV( 182, 40 ),
	UV( 183, 46 ),
	UV( 183, 48 ),
	UV( 184, 49 ),
	UV( 184, 51 ),
	UV( 183, 51 ),
	UV( 151, 189 ),
	UV( 157, 189 ),
	UV( 157, 202 ),
	UV( 142, 177 ),
	UV( 158, 164 ),
	UV( 155, 176 ),
	UV( 155, 176 ),
	UV( 151, 189 ),
	UV( 157, 176 ),
	UV( 157, 189 ),
	UV( 186, 65 ),
	UV( 184, 53 ),
	UV( 185, 53 ),
	UV( 184, 51 ),
	UV( 185, 51 ),
	UV( 187, 83 ),
	UV( 187, 84 ),
	UV( 186, 95 ),
	UV( 186, 95 ),
	UV( 185, 105 ),
	UV( 185, 105 ),
	UV( 182, 123 ),
	UV( 182, 123 ),
	UV( 182, 155 ),
	UV( 181, 142 ),
	UV( 182, 123 ),
	UV( 182, 155 ),
	UV( 138, 38 ),
	UV( 143, 53 ),
	UV( 165, 39 ),
	UV( 163, 53 ),
	UV( 166, 39 ),
	UV( 164, 52 ),
	UV( 182, 40 ),
	UV( 184, 52 ),
	UV( 158, 213 ),
	UV( 158, 213 ),
	UV( 174, 209 ),
	UV( 183, 40 ),
	UV( 178, 40 ),
	UV( 165, 39 ),
	UV( 165, 39 ),
	UV( 142, 38 ),
	UV( 142, 38 ),
	UV( 69, 40 ),
	UV( 71, 40 ),
	UV( 68, 46 ),
	UV( 69, 52 ),
	UV( 68, 53 ),
	UV( 67, 56 ),
	UV( 186, 57 ),
	UV( 185, 53 ),
	UV( 186, 58 ),
	UV( 185, 53 ),
	UV( 186, 60 ),
	UV( 186, 63 ),
	UV( 184, 154 ),
	UV( 181, 154 ),
	UV( 185, 123 ),
	UV( 182, 123 ),
	UV( 186, 105 ),
	UV( 185, 105 ),
	UV( 186, 95 ),
	UV( 186, 105 ),
	UV( 186, 95 ),
	UV( 185, 95 ),
	UV( 186, 91 ),
	UV( 184, 91 ),
	UV( 182, 154 ),
	UV( 182, 155 ),
	UV( 183, 123 ),
	UV( 183, 123 ),
	UV( 186, 105 ),
	UV( 186, 105 ),
	UV( 187, 95 ),
	UV( 186, 95 ),
	UV( 184, 159 ),
	UV( 185, 161 ),
	UV( 184, 154 ),
	UV( 185, 155 ),
	UV( 165, 39 ),
	UV( 166, 39 ),
	UV( 182, 40 ),
	UV( 158, 133 ),
	UV( 161, 130 ),
	UV( 154, 129 ),
	UV( 160, 128 ),
	UV( 154, 123 ),
	UV( 160, 123 ),
	UV( 154, 109 ),
	UV( 160, 106 ),
	UV( 158, 133 ),
	UV( 154, 134 ),
	UV( 154, 129 ),
	UV( 140, 134 ),
	UV( 154, 134 ),
	UV( 140, 129 ),
	UV( 154, 129 ),
	UV( 140, 123 ),
	UV( 154, 123 ),
	UV( 140, 109 ),
	UV( 154, 109 ),
	UV( 127, 38 ),
	UV( 127, 41 ),
	UV( 127, 41 ),
	UV( 158, 213 ),
	UV( 142, 214 ),
	UV( 142, 214 ),
	UV( 111, 214 ),
	UV( 111, 214 ),
	UV( 95, 213 ),
	UV( 95, 213 ),
	UV( 158, 213 ),
	UV( 158, 213 ),
	UV( 142, 214 ),
	UV( 157, 202 ),
	UV( 142, 202 ),
	UV( 151, 189 ),
	UV( 142, 189 ),
	UV( 178, 40 ),
	UV( 176, 40 ),
	UV( 165, 39 ),
	UV( 165, 39 ),
	UV( 142, 38 ),
	UV( 183, 40 ),
	UV( 184, 46 ),
	UV( 183, 43 ),
	UV( 184, 44 ),
	UV( 183, 44 ),
	UV( 183, 46 ),
	UV( 183, 45 ),
	UV( 183, 46 ),
	UV( 182, 46 ),
	UV( 186, 95 ),
	UV( 187, 81 ),
	UV( 187, 83 ),
	UV( 157, 176 ),
	UV( 155, 176 ),
	UV( 158, 164 ),
	UV( 96, 176 ),
	UV( 98, 176 ),
	UV( 95, 164 ),
	UV( 98, 176 ),
	UV( 111, 167 ),
	UV( 111, 177 ),
	UV( 126, 168 ),
	UV( 142, 177 ),
	UV( 142, 167 ),
	UV( 158, 164 ),
	UV( 182, 40 ),
	UV( 182, 40 ),
	UV( 183, 40 ),
	UV( 70, 40 ),
	UV( 71, 40 ),
	UV( 70, 40 ),
	UV( 71, 40 ),
	UV( 72, 40 ),
	UV( 183, 40 ),
	UV( 184, 46 ),
	UV( 182, 40 ),
	UV( 185, 53 ),
	UV( 184, 52 ),
	UV( 186, 56 ),
	UV( 185, 95 ),
	UV( 185, 86 ),
	UV( 186, 91 ),
	UV( 187, 85 ),
	UV( 187, 91 ),
	UV( 187, 85 ),
	UV( 186, 95 ),
END

VERTUV      vuvS_2_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	UV( 3, 191 ),
	UV( 33, 167 ),
	UV( 3, 155 ),
	UV( 35, 156 ),
	UV( 3, 123 ),
	UV( 33, 120 ),
	UV( 39, 175 ),
	UV( 11, 225 ),
	UV( 49, 177 ),
	UV( 39, 240 ),
	UV( 89, 178 ),
	UV( 84, 246 ),
	UV( 126, 178 ),
	UV( 126, 247 ),
	UV( 163, 178 ),
	UV( 168, 246 ),
	UV( 203, 177 ),
	UV( 213, 240 ),
	UV( 213, 175 ),
	UV( 241, 225 ),
	UV( 3, 119 ),
	UV( 32, 116 ),
	UV( 8, 99 ),
	UV( 27, 102 ),
	UV( 19, 79 ),
	UV( 32, 170 ),
	UV( 4, 216 ),
	UV( 3, 194 ),
	UV( 117, 66 ),
	UV( 117, 70 ),
	UV( 59, 66 ),
	UV( 117, 84 ),
	UV( 117, 80 ),
	UV( 59, 84 ),
	UV( 59, 80 ),
	UV( 45, 63 ),
	UV( 59, 70 ),
	UV( 89, 101 ),
	UV( 117, 94 ),
	UV( 49, 101 ),
	UV( 59, 94 ),
	UV( 59, 84 ),
	UV( 59, 94 ),
	UV( 117, 84 ),
	UV( 117, 94 ),
	UV( 117, 94 ),
	UV( 117, 66 ),
	UV( 59, 66 ),
	UV( 59, 56 ),
	UV( 59, 66 ),
	UV( 97, 16 ),
	UV( 97, 25 ),
	UV( 155, 16 ),
	UV( 155, 25 ),
	UV( 155, 25 ),
	UV( 59, 84 ),
	UV( 49, 101 ),
	UV( 45, 63 ),
	UV( 29, 63 ),
	UV( 42, 39 ),
	UV( 18, 41 ),
	UV( 39, 18 ),
	UV( 168, 9 ),
	UV( 213, 18 ),
	UV( 193, 28 ),
	UV( 59, 80 ),
	UV( 59, 70 ),
	UV( 59, 80 ),
	UV( 117, 70 ),
	UV( 117, 80 ),
	UV( 117, 80 ),
	UV( 97, 25 ),
	UV( 97, 25 ),
	UV( 97, 16 ),
	UV( 59, 28 ),
	UV( 39, 18 ),
	UV( 59, 38 ),
	UV( 42, 39 ),
	UV( 59, 42 ),
	UV( 117, 66 ),
	UV( 117, 66 ),
	UV( 117, 56 ),
	UV( 59, 56 ),
	UV( 117, 52 ),
	UV( 59, 52 ),
	UV( 59, 38 ),
	UV( 59, 28 ),
	UV( 59, 38 ),
	UV( 117, 28 ),
	UV( 117, 38 ),
	UV( 117, 38 ),
	UV( 117, 52 ),
	UV( 117, 52 ),
	UV( 117, 42 ),
	UV( 59, 52 ),
	UV( 59, 42 ),
	UV( 59, 52 ),
	UV( 42, 39 ),
	UV( 59, 56 ),
	UV( 45, 63 ),
	UV( 59, 66 ),
	UV( 59, 70 ),
	UV( 117, 70 ),
	UV( 59, 80 ),
	UV( 117, 80 ),
	UV( 219, 167 ),
	UV( 249, 191 ),
	UV( 218, 156 ),
	UV( 249, 155 ),
	UV( 219, 120 ),
	UV( 249, 123 ),
	UV( 220, 116 ),
	UV( 249, 119 ),
	UV( 225, 102 ),
	UV( 244, 99 ),
	UV( 233, 79 ),
	UV( 220, 170 ),
	UV( 249, 194 ),
	UV( 248, 216 ),
	UV( 135, 66 ),
	UV( 193, 66 ),
	UV( 193, 70 ),
	UV( 207, 63 ),
	UV( 193, 80 ),
	UV( 203, 101 ),
	UV( 193, 84 ),
	UV( 193, 94 ),
	UV( 193, 94 ),
	UV( 193, 70 ),
	UV( 135, 70 ),
	UV( 135, 66 ),
	UV( 135, 80 ),
	UV( 193, 80 ),
	UV( 135, 84 ),
	UV( 193, 84 ),
	UV( 135, 94 ),
	UV( 193, 94 ),
	UV( 135, 52 ),
	UV( 193, 52 ),
	UV( 135, 56 ),
	UV( 193, 56 ),
	UV( 193, 66 ),
	UV( 193, 38 ),
	UV( 193, 28 ),
	UV( 135, 38 ),
	UV( 135, 28 ),
	UV( 135, 38 ),
	UV( 203, 101 ),
	UV( 163, 101 ),
	UV( 193, 94 ),
	UV( 135, 94 ),
	UV( 193, 66 ),
	UV( 135, 66 ),
	UV( 135, 56 ),
	UV( 135, 66 ),
	UV( 203, 101 ),
	UV( 223, 63 ),
	UV( 207, 63 ),
	UV( 234, 41 ),
	UV( 210, 39 ),
	UV( 135, 94 ),
	UV( 135, 94 ),
	UV( 135, 84 ),
	UV( 135, 80 ),
	UV( 135, 70 ),
	UV( 135, 80 ),
	UV( 193, 70 ),
	UV( 193, 80 ),
	UV( 193, 80 ),
	UV( 135, 52 ),
	UV( 135, 42 ),
	UV( 135, 52 ),
	UV( 193, 42 ),
	UV( 193, 52 ),
	UV( 193, 52 ),
	UV( 234, 41 ),
	UV( 213, 18 ),
	UV( 210, 39 ),
	UV( 193, 28 ),
	UV( 193, 38 ),
	UV( 193, 38 ),
	UV( 193, 38 ),
	UV( 135, 38 ),
	UV( 135, 42 ),
	UV( 117, 42 ),
	UV( 135, 52 ),
	UV( 117, 52 ),
	UV( 135, 56 ),
	UV( 117, 56 ),
	UV( 135, 66 ),
	UV( 117, 66 ),
	UV( 135, 70 ),
	UV( 117, 70 ),
	UV( 135, 80 ),
	UV( 117, 80 ),
	UV( 135, 84 ),
	UV( 117, 84 ),
	UV( 135, 94 ),
	UV( 117, 94 ),
	UV( 163, 101 ),
	UV( 89, 101 ),
	UV( 135, 42 ),
	UV( 193, 38 ),
	UV( 193, 42 ),
	UV( 210, 39 ),
	UV( 193, 52 ),
	UV( 207, 63 ),
	UV( 193, 56 ),
	UV( 193, 66 ),
	UV( 193, 66 ),
	UV( 59, 38 ),
	UV( 117, 38 ),
	UV( 59, 42 ),
	UV( 59, 42 ),
	UV( 117, 42 ),
	UV( 117, 38 ),
	UV( 135, 38 ),
	UV( 117, 28 ),
	UV( 135, 28 ),
	UV( 155, 25 ),
	UV( 193, 28 ),
	UV( 155, 16 ),
	UV( 168, 9 ),
	UV( 97, 16 ),
	UV( 84, 9 ),
	UV( 39, 18 ),
	UV( 155, 25 ),
	UV( 117, 28 ),
	UV( 97, 25 ),
	UV( 59, 28 ),
END

VERTUV      vuvS_3_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	UV( 99, 216 ),
	UV( 99, 220 ),
	UV( 92, 220 ),
	UV( 99, 232 ),
	UV( 83, 220 ),
	UV( 86, 228 ),
	UV( 83, 220 ),
	UV( 82, 213 ),
	UV( 92, 220 ),
	UV( 92, 215 ),
	UV( 99, 216 ),
	UV( 166, 228 ),
	UV( 153, 232 ),
	UV( 160, 220 ),
	UV( 153, 220 ),
	UV( 160, 215 ),
	UV( 153, 216 ),
	UV( 170, 213 ),
	UV( 160, 215 ),
	UV( 169, 220 ),
	UV( 160, 220 ),
	UV( 166, 228 ),
END

VERTUV      vuvS_5_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	UV( 80, 52 ),
	UV( 72, 53 ),
	UV( 73, 62 ),
	UV( 71, 60 ),
	UV( 70, 67 ),
	UV( 70, 60 ),
	UV( 69, 67 ),
	UV( 68, 67 ),
	UV( 70, 84 ),
	UV( 68, 73 ),
	UV( 68, 80 ),
	UV( 66, 78 ),
	UV( 66, 81 ),
	UV( 72, 53 ),
	UV( 71, 60 ),
	UV( 71, 53 ),
	UV( 68, 67 ),
	UV( 70, 60 ),
	UV( 69, 53 ),
	UV( 71, 53 ),
	UV( 70, 48 ),
	UV( 72, 46 ),
	UV( 71, 46 ),
	UV( 73, 40 ),
	UV( 69, 185 ),
	UV( 69, 189 ),
	UV( 69, 182 ),
	UV( 68, 176 ),
	UV( 68, 176 ),
	UV( 69, 164 ),
	UV( 68, 170 ),
	UV( 69, 164 ),
	UV( 68, 164 ),
	UV( 69, 154 ),
	UV( 69, 155 ),
	UV( 69, 53 ),
	UV( 67, 65 ),
	UV( 69, 53 ),
	UV( 67, 67 ),
	UV( 68, 67 ),
	UV( 67, 71 ),
	UV( 68, 73 ),
	UV( 66, 78 ),
	UV( 76, 202 ),
	UV( 79, 208 ),
	UV( 74, 202 ),
	UV( 70, 67 ),
	UV( 79, 83 ),
	UV( 70, 84 ),
	UV( 73, 95 ),
	UV( 72, 95 ),
	UV( 73, 105 ),
	UV( 72, 98 ),
	UV( 73, 105 ),
	UV( 77, 75 ),
	UV( 77, 75 ),
	UV( 74, 67 ),
	UV( 74, 67 ),
	UV( 73, 62 ),
	UV( 84, 62 ),
	UV( 79, 83 ),
	UV( 80, 75 ),
	UV( 80, 75 ),
	UV( 83, 67 ),
	UV( 83, 67 ),
	UV( 73, 62 ),
	UV( 73, 62 ),
	UV( 74, 67 ),
	UV( 70, 67 ),
	UV( 77, 75 ),
	UV( 79, 83 ),
	UV( 77, 75 ),
	UV( 80, 75 ),
	UV( 74, 67 ),
	UV( 83, 67 ),
	UV( 84, 62 ),
	UV( 83, 67 ),
	UV( 84, 62 ),
	UV( 75, 123 ),
	UV( 76, 105 ),
	UV( 74, 123 ),
	UV( 73, 105 ),
	UV( 69, 105 ),
	UV( 72, 123 ),
	UV( 73, 123 ),
	UV( 74, 135 ),
	UV( 68, 164 ),
	UV( 68, 161 ),
	UV( 69, 155 ),
	UV( 68, 155 ),
	UV( 82, 153 ),
	UV( 85, 157 ),
	UV( 72, 154 ),
	UV( 84, 164 ),
	UV( 71, 164 ),
	UV( 84, 176 ),
	UV( 70, 176 ),
	UV( 71, 189 ),
	UV( 69, 189 ),
	UV( 82, 105 ),
	UV( 82, 107 ),
	UV( 74, 105 ),
	UV( 82, 123 ),
	UV( 75, 123 ),
	UV( 82, 140 ),
	UV( 75, 142 ),
	UV( 82, 142 ),
	UV( 82, 153 ),
	UV( 73, 95 ),
	UV( 82, 95 ),
	UV( 79, 83 ),
	UV( 84, 84 ),
	UV( 80, 75 ),
	UV( 88, 67 ),
	UV( 83, 67 ),
	UV( 95, 55 ),
	UV( 84, 62 ),
	UV( 97, 52 ),
	UV( 80, 52 ),
	UV( 79, 209 ),
	UV( 79, 209 ),
	UV( 95, 213 ),
	UV( 95, 213 ),
	UV( 111, 51 ),
	UV( 95, 55 ),
	UV( 97, 52 ),
	UV( 69, 53 ),
	UV( 69, 51 ),
	UV( 69, 53 ),
	UV( 70, 48 ),
	UV( 70, 154 ),
	UV( 72, 154 ),
	UV( 69, 164 ),
	UV( 71, 164 ),
	UV( 68, 176 ),
	UV( 70, 176 ),
	UV( 69, 189 ),
	UV( 80, 52 ),
	UV( 84, 62 ),
	UV( 73, 62 ),
	UV( 122, 40 ),
	UV( 122, 42 ),
	UV( 122, 42 ),
	UV( 74, 202 ),
	UV( 69, 185 ),
	UV( 74, 202 ),
	UV( 69, 189 ),
	UV( 76, 202 ),
	UV( 71, 189 ),
	UV( 74, 197 ),
	UV( 85, 189 ),
	UV( 86, 198 ),
	UV( 95, 189 ),
	UV( 94, 198 ),
	UV( 96, 189 ),
	UV( 94, 202 ),
	UV( 96, 202 ),
	UV( 94, 212 ),
	UV( 95, 213 ),
	UV( 79, 208 ),
	UV( 79, 209 ),
	UV( 77, 208 ),
	UV( 79, 209 ),
	UV( 77, 208 ),
	UV( 95, 164 ),
	UV( 95, 176 ),
	UV( 96, 176 ),
	UV( 95, 189 ),
	UV( 96, 189 ),
	UV( 84, 176 ),
	UV( 85, 189 ),
	UV( 71, 189 ),
	UV( 69, 67 ),
	UV( 70, 67 ),
	UV( 70, 84 ),
	UV( 70, 84 ),
	UV( 72, 95 ),
	UV( 85, 157 ),
	UV( 84, 164 ),
	UV( 95, 164 ),
	UV( 84, 176 ),
	UV( 95, 176 ),
	UV( 85, 189 ),
	UV( 95, 189 ),
	UV( 75, 154 ),
	UV( 75, 142 ),
	UV( 82, 153 ),
	UV( 75, 154 ),
	UV( 75, 154 ),
	UV( 75, 142 ),
	UV( 75, 142 ),
	UV( 75, 123 ),
	UV( 75, 123 ),
	UV( 74, 105 ),
	UV( 74, 123 ),
	UV( 73, 105 ),
	UV( 73, 105 ),
	UV( 68, 80 ),
	UV( 70, 84 ),
	UV( 70, 95 ),
	UV( 72, 95 ),
	UV( 68, 98 ),
	UV( 72, 98 ),
	UV( 71, 155 ),
	UV( 71, 142 ),
	UV( 72, 142 ),
	UV( 72, 123 ),
	UV( 73, 142 ),
	UV( 74, 135 ),
	UV( 75, 142 ),
	UV( 74, 123 ),
	UV( 75, 123 ),
	UV( 73, 105 ),
	UV( 74, 105 ),
	UV( 73, 95 ),
	UV( 82, 105 ),
	UV( 82, 95 ),
	UV( 84, 95 ),
	UV( 84, 84 ),
	UV( 88, 85 ),
	UV( 71, 155 ),
	UV( 72, 142 ),
	UV( 72, 155 ),
	UV( 73, 142 ),
	UV( 73, 154 ),
	UV( 75, 142 ),
	UV( 75, 154 ),
	UV( 71, 123 ),
	UV( 72, 123 ),
	UV( 71, 142 ),
	UV( 71, 123 ),
	UV( 68, 105 ),
	UV( 72, 123 ),
	UV( 69, 105 ),
	UV( 73, 123 ),
	UV( 74, 123 ),
	UV( 74, 135 ),
	UV( 75, 123 ),
	UV( 74, 123 ),
	UV( 76, 105 ),
	UV( 73, 105 ),
	UV( 77, 98 ),
	UV( 72, 98 ),
	UV( 69, 164 ),
	UV( 69, 164 ),
	UV( 70, 154 ),
	UV( 69, 154 ),
	UV( 74, 202 ),
	UV( 77, 208 ),
	UV( 74, 202 ),
	UV( 77, 208 ),
	UV( 79, 208 ),
	UV( 68, 105 ),
	UV( 68, 98 ),
	UV( 67, 95 ),
	UV( 70, 95 ),
	UV( 66, 81 ),
	UV( 68, 80 ),
	UV( 68, 105 ),
	UV( 69, 105 ),
	UV( 68, 98 ),
	UV( 73, 105 ),
	UV( 73, 98 ),
	UV( 76, 105 ),
	UV( 77, 98 ),
	UV( 173, 52 ),
	UV( 181, 53 ),
	UV( 182, 60 ),
	UV( 182, 53 ),
	UV( 182, 60 ),
	UV( 184, 67 ),
	UV( 183, 60 ),
	UV( 185, 67 ),
	UV( 182, 53 ),
	UV( 184, 53 ),
	UV( 181, 46 ),
	UV( 183, 48 ),
	UV( 182, 46 ),
	UV( 184, 182 ),
	UV( 184, 185 ),
	UV( 184, 189 ),
	UV( 179, 202 ),
	UV( 179, 202 ),
	UV( 176, 208 ),
	UV( 174, 208 ),
	UV( 174, 209 ),
	UV( 159, 212 ),
	UV( 158, 213 ),
	UV( 159, 202 ),
	UV( 157, 202 ),
	UV( 159, 198 ),
	UV( 158, 189 ),
	UV( 168, 189 ),
	UV( 169, 176 ),
	UV( 183, 176 ),
	UV( 169, 164 ),
	UV( 182, 164 ),
	UV( 168, 157 ),
	UV( 181, 154 ),
	UV( 171, 153 ),
	UV( 184, 189 ),
	UV( 185, 176 ),
	UV( 184, 182 ),
	UV( 186, 67 ),
	UV( 185, 67 ),
	UV( 184, 53 ),
	UV( 180, 62 ),
	UV( 169, 62 ),
	UV( 169, 67 ),
	UV( 169, 62 ),
	UV( 169, 67 ),
	UV( 165, 67 ),
	UV( 173, 75 ),
	UV( 174, 83 ),
	UV( 173, 75 ),
	UV( 176, 75 ),
	UV( 169, 67 ),
	UV( 179, 67 ),
	UV( 180, 62 ),
	UV( 180, 62 ),
	UV( 174, 208 ),
	UV( 177, 202 ),
	UV( 179, 202 ),
	UV( 179, 197 ),
	UV( 184, 189 ),
	UV( 182, 189 ),
	UV( 185, 176 ),
	UV( 183, 176 ),
	UV( 184, 164 ),
	UV( 182, 164 ),
	UV( 182, 154 ),
	UV( 181, 154 ),
	UV( 168, 189 ),
	UV( 167, 198 ),
	UV( 159, 198 ),
	UV( 174, 83 ),
	UV( 169, 84 ),
	UV( 165, 67 ),
	UV( 173, 75 ),
	UV( 173, 75 ),
	UV( 169, 67 ),
	UV( 169, 67 ),
	UV( 174, 83 ),
	UV( 176, 75 ),
	UV( 176, 75 ),
	UV( 179, 67 ),
	UV( 179, 67 ),
	UV( 180, 62 ),
	UV( 183, 84 ),
	UV( 184, 67 ),
	UV( 185, 73 ),
	UV( 185, 67 ),
	UV( 186, 71 ),
	UV( 186, 67 ),
	UV( 185, 170 ),
	UV( 184, 164 ),
	UV( 185, 164 ),
	UV( 184, 164 ),
	UV( 184, 164 ),
	UV( 185, 170 ),
	UV( 185, 176 ),
	UV( 185, 176 ),
	UV( 184, 182 ),
	UV( 181, 98 ),
	UV( 177, 105 ),
	UV( 176, 98 ),
	UV( 180, 105 ),
	UV( 180, 98 ),
	UV( 184, 105 ),
	UV( 185, 98 ),
	UV( 186, 95 ),
	UV( 183, 95 ),
	UV( 185, 80 ),
	UV( 180, 105 ),
	UV( 179, 105 ),
	UV( 181, 95 ),
	UV( 180, 95 ),
	UV( 183, 84 ),
	UV( 183, 84 ),
	UV( 184, 67 ),
	UV( 183, 67 ),
	UV( 182, 60 ),
	UV( 165, 85 ),
	UV( 171, 95 ),
	UV( 169, 95 ),
	UV( 171, 105 ),
	UV( 165, 85 ),
	UV( 169, 84 ),
	UV( 171, 95 ),
	UV( 174, 83 ),
	UV( 183, 84 ),
	UV( 176, 75 ),
	UV( 183, 67 ),
	UV( 179, 67 ),
	UV( 182, 60 ),
	UV( 180, 62 ),
	UV( 173, 52 ),
	UV( 169, 62 ),
	UV( 158, 55 ),
	UV( 165, 67 ),
	UV( 186, 71 ),
	UV( 187, 78 ),
	UV( 185, 73 ),
	UV( 185, 80 ),
	UV( 183, 84 ),
	UV( 183, 95 ),
	UV( 181, 95 ),
	UV( 181, 98 ),
	UV( 180, 105 ),
	UV( 177, 105 ),
	UV( 178, 123 ),
	UV( 180, 105 ),
	UV( 179, 123 ),
	UV( 184, 105 ),
	UV( 185, 161 ),
	UV( 185, 155 ),
	UV( 185, 164 ),
	UV( 184, 155 ),
	UV( 184, 164 ),
	UV( 184, 154 ),
	UV( 184, 164 ),
	UV( 182, 154 ),
	UV( 171, 105 ),
	UV( 171, 107 ),
	UV( 179, 105 ),
	UV( 178, 123 ),
	UV( 180, 105 ),
	UV( 178, 123 ),
	UV( 180, 105 ),
	UV( 179, 123 ),
	UV( 178, 123 ),
	UV( 179, 135 ),
	UV( 179, 123 ),
	UV( 180, 123 ),
	UV( 184, 105 ),
	UV( 185, 105 ),
	UV( 186, 95 ),
	UV( 171, 140 ),
	UV( 171, 142 ),
	UV( 178, 142 ),
	UV( 178, 154 ),
	UV( 178, 142 ),
	UV( 178, 154 ),
	UV( 180, 142 ),
	UV( 180, 154 ),
	UV( 181, 142 ),
	UV( 181, 155 ),
	UV( 181, 142 ),
	UV( 182, 155 ),
	UV( 183, 84 ),
	UV( 180, 95 ),
	UV( 171, 95 ),
	UV( 179, 105 ),
	UV( 171, 105 ),
	UV( 182, 123 ),
	UV( 185, 105 ),
	UV( 181, 123 ),
	UV( 180, 123 ),
	UV( 180, 142 ),
	UV( 179, 135 ),
	UV( 178, 142 ),
	UV( 179, 123 ),
	UV( 178, 123 ),
	UV( 173, 52 ),
	UV( 158, 55 ),
	UV( 156, 52 ),
	UV( 142, 51 ),
	UV( 71, 40 ),
	UV( 71, 40 ),
	UV( 71, 56 ),
	UV( 71, 56 ),
	UV( 71, 60 ),
	UV( 71, 54 ),
	UV( 71, 53 ),
	UV( 158, 164 ),
	UV( 157, 176 ),
	UV( 158, 176 ),
	UV( 157, 189 ),
	UV( 158, 189 ),
	UV( 157, 202 ),
	UV( 186, 95 ),
	UV( 185, 80 ),
	UV( 187, 81 ),
	UV( 187, 78 ),
	UV( 183, 176 ),
	UV( 168, 189 ),
	UV( 182, 189 ),
	UV( 167, 198 ),
	UV( 179, 197 ),
	UV( 158, 189 ),
	UV( 169, 176 ),
	UV( 158, 176 ),
	UV( 169, 164 ),
	UV( 158, 164 ),
	UV( 168, 157 ),
	UV( 178, 142 ),
	UV( 178, 123 ),
	UV( 178, 142 ),
	UV( 178, 123 ),
	UV( 171, 123 ),
	UV( 171, 107 ),
	UV( 171, 153 ),
	UV( 171, 142 ),
	UV( 178, 154 ),
	UV( 180, 105 ),
	UV( 180, 105 ),
	UV( 181, 95 ),
	UV( 181, 142 ),
	UV( 182, 123 ),
	UV( 181, 142 ),
	UV( 181, 123 ),
	UV( 180, 142 ),
	UV( 171, 140 ),
	UV( 171, 123 ),
	UV( 178, 142 ),
	UV( 179, 202 ),
	UV( 176, 208 ),
	UV( 176, 208 ),
	UV( 174, 209 ),
	UV( 174, 209 ),
	UV( 158, 213 ),
	UV( 158, 213 ),
	UV( 182, 46 ),
	UV( 181, 46 ),
	UV( 180, 40 ),
	UV( 183, 48 ),
	UV( 184, 51 ),
	UV( 184, 53 ),
	UV( 184, 53 ),
	UV( 186, 67 ),
	UV( 186, 65 ),
	UV( 182, 40 ),
	UV( 182, 40 ),
	UV( 182, 56 ),
	UV( 182, 40 ),
	UV( 182, 56 ),
	UV( 182, 56 ),
	UV( 182, 60 ),
	UV( 182, 54 ),
	UV( 182, 53 ),
	UV( 185, 98 ),
	UV( 181, 98 ),
	UV( 183, 95 ),
END

VERTUV      vuvS_6_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	UV( 92, 130 ),
	UV( 95, 133 ),
	UV( 82, 153 ),
	UV( 85, 157 ),
	UV( 88, 67 ),
	UV( 84, 84 ),
	UV( 92, 77 ),
	UV( 89, 95 ),
	UV( 99, 96 ),
	UV( 93, 104 ),
	UV( 171, 153 ),
	UV( 168, 157 ),
	UV( 161, 130 ),
	UV( 158, 133 ),
	UV( 160, 104 ),
	UV( 164, 95 ),
	UV( 161, 77 ),
	UV( 169, 84 ),
	UV( 165, 67 ),
	UV( 160, 104 ),
	UV( 154, 96 ),
	UV( 161, 77 ),
END

VERTUV      vuvS_7_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	UV( 80, 48 ),
	UV( 73, 46 ),
	UV( 74, 40 ),
	UV( 72, 40 ),
	UV( 111, 39 ),
	UV( 88, 39 ),
	UV( 81, 42 ),
	UV( 74, 40 ),
	UV( 80, 46 ),
	UV( 80, 48 ),
	UV( 80, 48 ),
	UV( 81, 44 ),
	UV( 122, 42 ),
	UV( 81, 42 ),
	UV( 122, 40 ),
	UV( 111, 39 ),
	UV( 131, 40 ),
	UV( 142, 39 ),
	UV( 165, 39 ),
	UV( 122, 42 ),
	UV( 109, 45 ),
	UV( 81, 44 ),
	UV( 80, 46 ),
	UV( 81, 42 ),
	UV( 144, 47 ),
	UV( 142, 51 ),
	UV( 111, 51 ),
	UV( 131, 40 ),
	UV( 122, 40 ),
	UV( 131, 42 ),
	UV( 122, 42 ),
	UV( 144, 45 ),
	UV( 109, 45 ),
	UV( 144, 47 ),
	UV( 109, 47 ),
	UV( 111, 51 ),
	UV( 97, 52 ),
	UV( 80, 46 ),
	UV( 80, 48 ),
	UV( 109, 45 ),
	UV( 109, 47 ),
	UV( 109, 47 ),
	UV( 97, 52 ),
	UV( 97, 50 ),
	UV( 80, 52 ),
	UV( 80, 50 ),
	UV( 80, 52 ),
	UV( 72, 53 ),
	UV( 109, 47 ),
	UV( 80, 48 ),
	UV( 80, 50 ),
	UV( 73, 46 ),
	UV( 72, 53 ),
	UV( 72, 40 ),
	UV( 71, 53 ),
	UV( 71, 40 ),
	UV( 71, 54 ),
	UV( 71, 56 ),
	UV( 80, 50 ),
	UV( 109, 47 ),
	UV( 97, 50 ),
	UV( 97, 52 ),
	UV( 97, 52 ),
	UV( 81, 44 ),
	UV( 81, 42 ),
	UV( 81, 44 ),
	UV( 181, 53 ),
	UV( 180, 46 ),
	UV( 181, 40 ),
	UV( 179, 40 ),
	UV( 131, 40 ),
	UV( 165, 39 ),
	UV( 172, 42 ),
	UV( 179, 40 ),
	UV( 171, 44 ),
	UV( 173, 46 ),
	UV( 131, 42 ),
	UV( 144, 45 ),
	UV( 173, 50 ),
	UV( 173, 52 ),
	UV( 156, 50 ),
	UV( 156, 52 ),
	UV( 156, 52 ),
	UV( 142, 51 ),
	UV( 156, 52 ),
	UV( 144, 47 ),
	UV( 156, 50 ),
	UV( 173, 48 ),
	UV( 173, 50 ),
	UV( 171, 44 ),
	UV( 172, 42 ),
	UV( 171, 44 ),
	UV( 131, 40 ),
	UV( 131, 42 ),
	UV( 131, 42 ),
	UV( 173, 52 ),
	UV( 173, 52 ),
	UV( 173, 50 ),
	UV( 181, 53 ),
	UV( 173, 48 ),
	UV( 180, 46 ),
	UV( 173, 46 ),
	UV( 179, 40 ),
	UV( 144, 47 ),
	UV( 144, 45 ),
	UV( 144, 47 ),
	UV( 173, 46 ),
	UV( 173, 48 ),
	UV( 173, 48 ),
	UV( 71, 40 ),
	UV( 71, 40 ),
	UV( 71, 56 ),
	UV( 182, 56 ),
	UV( 182, 54 ),
	UV( 182, 40 ),
	UV( 182, 40 ),
	UV( 182, 40 ),
	UV( 182, 54 ),
	UV( 181, 40 ),
	UV( 182, 53 ),
	UV( 181, 53 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     130,
Meshes      pgS_0_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_C_F4E_BODY_3,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     28,
Meshes      pgS_1_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     37,
Meshes      pgS_2_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_2_F40_GTE_sh_null1_1_C_F4E_BODY_3,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 3 ),
MeshNum     4,
Meshes      pgS_3_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_3_F40_GTE_sh_null1_1_C_F4E_BODY_3,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 4 ),
MeshNum     6,
Meshes      pgS_4_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 5 ),
MeshNum     80,
Meshes      pgS_5_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_5_F40_GTE_sh_null1_1_C_F4E_BODY_3,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 6 ),
MeshNum     5,
Meshes      pgS_6_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_6_F40_GTE_sh_null1_1_C_F4E_BODY_3,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 7 ),
MeshNum     21,
Meshes      pgS_7_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_7_F40_GTE_sh_null1_1_C_F4E_BODY_3,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	VERT( -0.054931F,  1.050032F,  0.844449F ),
	VERT( -0.221500F,  1.064094F,  0.766261F ),
	VERT( -0.050864F,  0.489905F, -1.833380F ),
	VERT( -0.029889F,  0.478090F, -1.883696F ),
	VERT(  0.740481F,  0.759120F,  0.492959F ),
	VERT( -0.642200F,  0.527615F,  2.195358F ),
	VERT( -0.847689F,  0.527620F,  2.179560F ),
	VERT( -0.847689F,  0.527615F,  2.104714F ),
	VERT( -0.250000F,  0.354325F, -2.183557F ),
	VERT( -0.250000F,  0.335431F, -2.183557F ),
	VERT(  0.796568F,  0.794779F,  1.090233F ),
	VERT( -0.408985F,  0.075770F, -2.150438F ),
	VERT( -0.221500F,  1.094793F,  0.452163F ),
	VERT( -0.250000F,  0.811271F,  2.215000F ),
	VERT( -0.250000F,  0.817280F,  2.206654F ),
	VERT( -0.221500F,  1.100239F,  0.081028F ),
	VERT( -0.054931F,  0.996078F,  1.144449F ),
	VERT( -0.054931F,  1.018559F,  1.019449F ),
	VERT( -0.054931F,  1.027551F,  0.969449F ),
	VERT( -0.054931F,  0.987086F,  1.194449F ),
	VERT( -0.054931F,  0.962026F,  1.319449F ),
	VERT(  0.642354F,  0.305519F,  2.195358F ),
	VERT( -0.054931F,  0.951585F,  1.369449F ),
	VERT( -0.054931F,  0.925483F,  1.494449F ),
	VERT( -0.221500F,  1.086778F, -0.057161F ),
	VERT(  0.000000F,  1.055995F, -0.195351F ),
	VERT( -0.066913F,  0.817280F,  2.169764F ),
	VERT(  0.692384F,  0.622499F, -1.562257F ),
	VERT( -0.638458F,  0.817283F,  2.187320F ),
	VERT( -0.754221F,  0.817282F,  2.128830F ),
	VERT( -0.747149F,  0.802436F,  2.078890F ),
	VERT(  0.000000F,  0.431769F, -2.027380F ),
	VERT(  0.000000F,  0.704833F, -1.043698F ),
	VERT( -0.067298F,  0.817280F,  2.119824F ),
	VERT( -0.067298F,  0.802431F,  2.119824F ),
	VERT( -0.768982F,  0.817214F,  2.025089F ),
	VERT( -0.285804F,  0.817281F,  2.053776F ),
	VERT(  0.927122F,  0.861906F,  1.830991F ),
	VERT( -0.931201F,  0.303359F,  0.097366F ),
	VERT( -0.918164F,  0.202977F,  0.097366F ),
	VERT(  0.520036F,  0.077661F, -2.244867F ),
	VERT( -0.872872F,  0.817280F,  2.161488F ),
	VERT( -0.942951F,  0.777978F,  1.075996F ),
	VERT( -0.948676F,  0.802858F,  1.505506F ),
	VERT( -0.978516F,  0.739042F,  1.500628F ),
	VERT( -0.978686F,  0.730510F,  1.335937F ),
	VERT( -0.250000F,  0.753456F, -1.024537F ),
	VERT( -0.250000F,  0.685873F, -1.270945F ),
	VERT( -0.005463F,  0.537615F,  2.215000F ),
	VERT( -0.005463F,  0.753733F,  2.215000F ),
	VERT( -0.015463F,  0.763733F,  2.215000F ),
	VERT( -0.015463F,  0.527615F,  2.215000F ),
	VERT( -0.250000F,  0.476146F,  2.215000F ),
	VERT( -0.005463F,  0.537615F,  2.140000F ),
	VERT( -0.005463F,  0.753733F,  2.140000F ),
	VERT(  0.494269F,  0.816317F,  1.878518F ),
	VERT( -0.149500F,  0.253277F,  2.215000F ),
	VERT( -0.286188F,  0.817281F,  2.003836F ),
	VERT( -0.250000F,  0.817280F,  1.903015F ),
	VERT( -0.250000F,  0.315431F, -2.184510F ),
	VERT( -0.250000F,  0.301136F, -2.185874F ),
	VERT( -0.939600F,  1.086462F,  1.774372F ),
	VERT( -0.927100F,  1.086462F,  1.774372F ),
	VERT( -0.927100F,  1.103348F,  2.161440F ),
	VERT( -0.939600F,  1.103348F,  2.161440F ),
	VERT( -0.923631F,  0.187470F,  2.161488F ),
	VERT( -0.932457F,  0.751406F,  2.024636F ),
	VERT( -0.947255F,  0.732383F,  1.936923F ),
	VERT( -0.660103F,  0.187470F,  2.187482F ),
	VERT( -0.964543F,  0.688893F,  1.855562F ),
	VERT( -0.959178F,  0.723157F,  1.855664F ),
	VERT( -0.987854F,  0.646976F,  1.583178F ),
	VERT( -0.989800F,  0.660320F,  1.549720F ),
	VERT( -1.000000F,  0.514292F,  1.087994F ),
	VERT( -0.984826F,  0.526225F,  0.783257F ),
	VERT( -0.938092F,  0.751350F,  1.978431F ),
	VERT( -0.978282F,  0.535361F,  0.722167F ),
	VERT(  0.923271F,  0.732383F,  2.101923F ),
	VERT(  0.907424F,  0.751406F,  2.161488F ),
	VERT(  0.769377F,  0.802249F,  1.975149F ),
	VERT( -0.910714F,  0.551637F,  0.097366F ),
	VERT(  0.769377F,  0.817098F,  1.975149F ),
	VERT( -0.961470F,  0.547045F,  0.547468F ),
	VERT( -0.967595F,  0.501847F,  0.546898F ),
	VERT( -0.977290F,  0.430302F,  0.545997F ),
	VERT( -0.928430F,  0.423741F,  0.097366F ),
	VERT( -0.922531F,  0.466331F,  0.097366F ),
	VERT( -0.147607F,  0.299948F,  2.215000F ),
	VERT( -0.912787F,  0.436445F, -0.385201F ),
	VERT( -0.914374F,  0.423742F, -0.708017F ),
	VERT( -0.112182F,  0.271084F,  2.215000F ),
	VERT( -0.112182F,  0.371084F,  2.215000F ),
	VERT( -0.250000F,  0.456146F,  2.215000F ),
	VERT(  0.980000F,  0.306638F,  0.545745F ),
	VERT( -0.980000F,  0.306638F,  0.545745F ),
	VERT(  0.963828F,  0.616228F, -1.251085F ),
	VERT( -0.250000F,  0.521601F, -1.562257F ),
	VERT( -0.250000F,  0.623782F, -1.562257F ),
	VERT( -0.050864F,  0.522100F, -1.833380F ),
	VERT( -0.796569F,  0.794779F,  1.090233F ),
	VERT( -0.015463F,  0.763733F,  2.140000F ),
	VERT( -0.961363F,  0.471292F,  2.024636F ),
	VERT( -0.955694F,  0.532814F,  2.046922F ),
	VERT( -0.952037F,  0.532814F,  2.066922F ),
	VERT( -0.946440F,  0.532814F,  2.101922F ),
	VERT( -0.944460F,  0.476146F,  2.161488F ),
	VERT( -0.961870F,  0.532814F,  1.991922F ),
	VERT( -0.960009F,  0.532814F,  2.011922F ),
	VERT( -0.965128F,  0.532814F,  1.956922F ),
	VERT( -0.967219F,  0.532814F,  1.936923F ),
	VERT( -0.944803F,  0.732383F,  1.956922F ),
	VERT( -0.940504F,  0.732383F,  1.991922F ),
	VERT( -0.938043F,  0.732383F,  2.011922F ),
	VERT( -0.933408F,  0.732383F,  2.046922F ),
	VERT( -0.821171F,  0.335431F, -2.035119F ),
	VERT( -0.821171F,  0.357911F, -2.035119F ),
	VERT( -0.876178F,  0.438883F, -1.883696F ),
	VERT( -0.876178F,  0.350306F, -1.883696F ),
	VERT( -0.784986F,  0.335431F, -2.072745F ),
	VERT( -0.784986F,  0.354325F, -2.072745F ),
	VERT( -0.520035F,  0.133732F, -2.187675F ),
	VERT( -0.520035F,  0.173665F, -2.185157F ),
	VERT( -0.715676F,  0.173665F, -2.113870F ),
	VERT( -0.499234F,  0.619940F, -1.562257F ),
	VERT( -0.520035F,  0.633855F, -1.562257F ),
	VERT(  0.928258F,  0.761960F,  2.024636F ),
	VERT( -0.499234F,  0.496078F, -1.883696F ),
	VERT( -0.960205F,  0.617055F, -0.943726F ),
	VERT( -0.950603F,  0.682442F, -0.950294F ),
	VERT( -0.929750F,  0.681694F, -0.692336F ),
	VERT( -0.949419F,  0.618559F, -0.700249F ),
	VERT( -0.954382F,  0.202977F, -0.690391F ),
	VERT( -0.942929F,  0.089178F, -0.690391F ),
	VERT( -0.942929F,  0.089178F, -0.799480F ),
	VERT( -0.954382F,  0.203177F, -0.809587F ),
	VERT( -0.863127F,  0.811255F,  2.171437F ),
	VERT( -0.638576F,  0.811274F,  2.195658F ),
	VERT( -0.642200F,  0.763733F,  2.195358F ),
	VERT( -0.823163F,  0.763738F,  2.176902F ),
	VERT( -0.739352F,  0.702105F, -0.345799F ),
	VERT( -0.740481F,  0.722747F,  0.097366F ),
	VERT( -0.850798F,  0.697592F,  0.097366F ),
	VERT( -0.851759F,  0.675542F, -0.385201F ),
	VERT( -0.861089F,  0.690126F,  0.097366F ),
	VERT( -0.873895F,  0.737162F,  0.545745F ),
	VERT( -0.884466F,  0.729695F,  0.545745F ),
	VERT( -0.987972F,  0.202976F,  0.545732F ),
	VERT( -0.976117F,  0.089178F,  0.545732F ),
	VERT( -0.959931F,  0.089178F,  0.097371F ),
	VERT( -0.971590F,  0.202976F,  0.097371F ),
	VERT( -0.713703F,  0.810324F,  1.505506F ),
	VERT(  0.939600F,  0.949074F,  2.171440F ),
	VERT(  0.472151F,  0.203344F, -2.184153F ),
	VERT( -0.713700F,  0.751506F,  1.505509F ),
	VERT( -0.740481F,  0.763909F,  0.545745F ),
	VERT( -0.740481F,  0.779339F,  0.782614F ),
	VERT( -0.892295F,  0.759522F,  0.782614F ),
	VERT( -0.953161F,  0.751406F,  1.855749F ),
	VERT( -0.962603F,  0.451292F,  2.024636F ),
	VERT(  0.660103F,  0.187470F,  2.187482F ),
	VERT( -0.948362F,  0.139552F,  1.856461F ),
	VERT( -0.977299F,  0.446437F,  1.855562F ),
	VERT(  0.982145F,  0.441379F,  1.758921F ),
	VERT( -0.976117F,  0.089178F,  1.027503F ),
	VERT( -0.976117F,  0.089178F,  0.782614F ),
	VERT(  0.929352F,  0.701185F, -0.950293F ),
	VERT(  0.250000F,  0.527615F,  2.215000F ),
	VERT( -0.196622F,  0.305519F,  2.215000F ),
	VERT( -0.280400F,  0.201609F,  1.836407F ),
	VERT(  0.494700F,  0.286522F, -2.101675F ),
	VERT( -0.645617F,  0.795355F,  1.029665F ),
	VERT( -0.708338F,  0.779339F,  0.782614F ),
	VERT(  0.494700F,  0.286522F, -2.176675F ),
	VERT( -0.995642F,  0.695542F,  1.401928F ),
	VERT( -0.520035F,  0.354325F, -2.170783F ),
	VERT( -0.519161F,  0.335431F, -2.170825F ),
	VERT( -0.950545F,  0.071032F, -1.500854F ),
	VERT( -0.904047F,  0.072296F, -1.883696F ),
	VERT( -0.876178F,  0.116346F, -1.883696F ),
	VERT(  0.537397F,  0.509007F, -1.883696F ),
	VERT( -0.221500F,  1.055995F, -0.195351F ),
	VERT( -0.250000F,  0.704833F, -1.024537F ),
	VERT( -0.520035F,  0.704833F, -0.950293F ),
	VERT( -0.520035F,  0.742794F, -0.950294F ),
	VERT( -0.505474F,  0.886945F,  1.532735F ),
	VERT( -0.520035F,  0.816012F,  1.792720F ),
	VERT( -0.646464F,  0.810324F,  1.505506F ),
	VERT( -0.767763F,  0.301136F, -2.010800F ),
	VERT( -0.821171F,  0.315431F, -2.035119F ),
	VERT( -0.876178F,  0.330306F, -1.883696F ),
	VERT( -0.460752F,  1.073090F,  0.452163F ),
	VERT( -0.460752F,  1.078536F,  0.081028F ),
	VERT(  0.715676F,  0.173665F, -2.038870F ),
	VERT( -0.579806F,  0.904811F,  1.230424F ),
	VERT( -0.622501F,  0.945726F,  0.787732F ),
	VERT( -0.175000F,  0.850279F,  1.810252F ),
	VERT( -0.015463F,  0.527615F,  2.140000F ),
	VERT( -0.862062F,  0.668076F, -0.385201F ),
	VERT( -0.868026F,  0.676501F,  0.097366F ),
	VERT( -1.000000F,  0.443805F,  1.059877F ),
	VERT( -0.977466F,  0.433577F,  0.782614F ),
	VERT( -0.897155F,  0.548805F, -0.385201F ),
	VERT( -0.896940F,  0.550862F, -0.700887F ),
	VERT( -0.966000F,  0.423739F, -0.713800F ),
	VERT(  0.418600F,  0.147874F, -2.243182F ),
	VERT( -0.966000F,  0.423539F, -0.863600F ),
	VERT(  0.409107F,  0.129436F, -2.246474F ),
	VERT( -0.404931F,  0.906596F,  1.369449F ),
	VERT( -0.404931F,  0.906672F,  1.494449F ),
	VERT( -0.404931F,  0.932877F,  1.369449F ),
	VERT( -0.978854F,  0.713081F,  1.173815F ),
	VERT( -0.944378F,  0.673502F,  0.782614F ),
	VERT( -0.054931F,  0.925305F,  1.369449F ),
	VERT( -0.404931F,  0.868387F,  1.544449F ),
	VERT( -0.404931F,  0.867644F,  1.669449F ),
	VERT( -0.404931F,  0.895989F,  1.544449F ),
	VERT( -0.889971F,  0.791412F,  2.171437F ),
	VERT( -0.404931F,  0.968520F,  1.194449F ),
	VERT( -0.404931F,  0.943126F,  1.194449F ),
	VERT( -0.054931F,  0.887331F,  1.544449F ),
	VERT( -0.054931F,  0.914933F,  1.544449F ),
	VERT( -0.054931F,  0.887667F,  1.669449F ),
	VERT( -0.054931F,  0.961692F,  1.194449F ),
	VERT( -0.992866F,  0.681837F,  1.495750F ),
	VERT( -0.906628F,  0.725009F,  0.722167F ),
	VERT( -0.894496F,  0.712970F,  0.547468F ),
	VERT( -0.903088F,  0.752055F,  0.782614F ),
	VERT( -0.706969F,  0.799781F,  1.075996F ),
	VERT( -0.404931F,  0.943325F,  1.319449F ),
	VERT( -0.175000F,  0.851082F,  1.706689F ),
	VERT( -0.175000F,  0.878859F,  1.706689F ),
	VERT( -0.054931F,  0.995553F,  1.019449F ),
	VERT( -0.404931F,  0.978294F,  1.019449F ),
	VERT( -0.404931F,  0.977886F,  1.144449F ),
	VERT( -0.404931F,  1.001300F,  1.019449F ),
	VERT(  0.936711F,  0.456146F,  2.171438F ),
	VERT( -0.615552F,  0.139552F,  1.856461F ),
	VERT( -0.054931F,  1.027079F,  0.844449F ),
	VERT( -0.404931F,  1.010707F,  0.844449F ),
	VERT( -0.404931F,  1.010666F,  0.969449F ),
	VERT( -0.404931F,  1.033660F,  0.844449F ),
	VERT(  0.595480F,  0.945726F,  0.755073F ),
	VERT( -0.692054F,  0.705954F, -0.764855F ),
	VERT( -0.735734F,  0.707075F, -0.660589F ),
	VERT( -0.692054F,  0.724934F, -0.764855F ),
	VERT( -0.560823F,  1.027906F,  0.521524F ),
	VERT( -0.549685F,  1.039690F,  0.081028F ),
	VERT(  0.931201F,  0.403741F,  0.097366F ),
	VERT( -0.147607F,  0.344384F,  2.215000F ),
	VERT( -0.466285F,  0.705792F, -1.240308F ),
	VERT( -0.520035F,  0.719706F, -1.240308F ),
	VERT( -0.699662F,  0.708351F, -1.240308F ),
	VERT( -0.699662F,  0.731439F, -0.950294F ),
	VERT(  0.705860F,  0.812398F,  1.610206F ),
	VERT( -0.966000F,  0.656108F, -1.240308F ),
	VERT( -0.966000F,  0.616228F, -1.082853F ),
	VERT( -0.861856F,  0.670339F, -0.686819F ),
	VERT( -0.851555F,  0.677805F, -0.684617F ),
	VERT(  0.917922F,  0.827296F,  1.848830F ),
	VERT(  0.577239F,  0.301136F, -2.098099F ),
	VERT( -0.738224F,  0.700697F, -0.385201F ),
	VERT(  0.983995F,  0.514292F,  1.715862F ),
	VERT( -0.564844F,  1.017175F, -0.088460F ),
	VERT(  0.784987F,  0.278689F, -2.077201F ),
	VERT( -0.489200F,  0.952216F,  1.230424F ),
	VERT( -0.460752F,  1.042391F,  0.766261F ),
	VERT( -0.460752F,  1.064682F, -0.057258F ),
	VERT( -0.460752F,  1.037354F, -0.174371F ),
	VERT( -0.519743F,  1.018843F, -0.154385F ),
	VERT(  0.904277F,  0.202977F, -0.684873F ),
	VERT(  0.966280F,  0.202977F,  0.545745F ),
	VERT( -0.931681F,  0.785445F,  1.075996F ),
	VERT( -0.937338F,  0.810324F,  1.505506F ),
	VERT( -0.883159F,  0.605802F, -0.385201F ),
	VERT(  0.926481F,  0.799842F,  1.855893F ),
	VERT( -0.879434F,  0.810324F,  1.505506F ),
	VERT(  1.000000F,  0.360277F,  0.782615F ),
	VERT(  0.985992F,  0.413577F,  0.782615F ),
	VERT(  0.834637F,  0.712970F,  0.547468F ),
	VERT(  0.917117F,  0.303359F, -0.697006F ),
	VERT( -0.882947F,  0.614334F, -0.693853F ),
	VERT( -0.562849F,  1.020657F,  0.572180F ),
	VERT(  0.851482F,  0.748108F,  2.098934F ),
	VERT(  0.898364F,  0.751406F,  2.171438F ),
	VERT(  0.418600F,  0.156780F, -2.114838F ),
	VERT(  0.980000F,  0.410298F,  0.545745F ),
	VERT(  0.953158F,  0.376336F, -1.478091F ),
	VERT(  0.851482F,  0.748108F,  2.173801F ),
	VERT(  0.944406F,  0.674851F, -1.240308F ),
	VERT(  0.924910F,  0.732383F,  2.011923F ),
	VERT( -0.740481F,  0.759120F,  0.492959F ),
	VERT( -0.987972F,  0.202976F,  0.782614F ),
	VERT( -0.950545F,  0.570256F, -1.562257F ),
	VERT( -0.963827F,  0.616228F, -1.251085F ),
	VERT(  0.250000F,  0.502625F, -1.883696F ),
	VERT( -0.929295F,  0.589000F, -1.562257F ),
	VERT( -0.944405F,  0.674851F, -1.240308F ),
	VERT( -0.887035F,  0.535361F,  0.722167F ),
	VERT( -0.908966F,  0.700437F, -0.688565F ),
	VERT( -0.929352F,  0.701185F, -0.950293F ),
	VERT( -0.692384F,  0.622499F, -1.562257F ),
	VERT(  0.973307F,  0.601888F,  1.855562F ),
	VERT( -0.537397F,  0.368680F, -2.141139F ),
	VERT( -0.537397F,  0.509007F, -1.883696F ),
	VERT(  0.475861F,  0.301136F, -2.175760F ),
	VERT(  0.819082F,  0.802193F,  1.287251F ),
	VERT( -0.767763F,  0.301136F, -2.085800F ),
	VERT(  0.767763F,  0.301136F, -2.010800F ),
	VERT( -0.560608F,  1.025685F, -0.047613F ),
	VERT( -0.595480F,  0.945726F,  0.755073F ),
	VERT( -0.982145F,  0.441379F,  1.758920F ),
	VERT(  0.870819F,  0.650879F, -0.213765F ),
	VERT( -0.642354F,  0.305519F,  2.195358F ),
	VERT( -0.966000F,  0.403537F, -0.853043F ),
	VERT( -0.966000F,  0.403741F, -0.714656F ),
	VERT( -0.917117F,  0.403741F, -0.709139F ),
	VERT( -0.917117F,  0.303359F, -0.697006F ),
	VERT(  0.875951F,  0.543240F,  2.102478F ),
	VERT( -0.931201F,  0.403741F,  0.097366F ),
	VERT( -0.980000F,  0.410298F,  0.545745F ),
	VERT(  0.962161F,  0.227226F,  0.892489F ),
	VERT(  1.000000F,  0.333042F,  1.039428F ),
	VERT( -1.000000F,  0.360277F,  0.782614F ),
	VERT( -0.980112F,  0.413577F,  0.782614F ),
	VERT( -0.904277F,  0.202977F, -0.684873F ),
	VERT( -0.966280F,  0.202977F,  0.545745F ),
	VERT(  0.664932F,  0.502805F, -1.883696F ),
	VERT(  0.999239F,  0.646976F,  1.220678F ),
	VERT(  0.472151F,  0.203344F, -2.109153F ),
	VERT(  0.678155F,  0.541076F, -1.780918F ),
	VERT( -0.834637F,  0.712970F,  0.547468F ),
	VERT( -0.883385F,  0.547045F,  0.547468F ),
	VERT(  0.939600F,  1.075494F,  2.171440F ),
	VERT( -0.982631F,  0.460780F,  1.747464F ),
	VERT( -0.983996F,  0.514292F,  1.715862F ),
	VERT( -0.973308F,  0.601888F,  1.855562F ),
	VERT( -0.977299F,  0.466437F,  1.855562F ),
	VERT( -0.953003F,  0.396874F, -1.476563F ),
	VERT( -0.846023F,  0.073874F, -2.102810F ),
	VERT( -0.821171F,  0.133732F, -2.052011F ),
	VERT( -0.784987F,  0.278689F, -2.077201F ),
	VERT( -0.784986F,  0.315431F, -2.073698F ),
	VERT( -0.797546F,  0.075768F, -2.146828F ),
	VERT( -0.784986F,  0.133732F, -2.089637F ),
	VERT( -0.642200F,  0.476148F,  2.195358F ),
	VERT(  0.286188F,  0.802431F,  2.003836F ),
	VERT(  0.250000F,  0.763733F,  2.215000F ),
	VERT( -0.938224F,  0.732383F,  1.901922F ),
	VERT( -0.935030F,  0.476146F,  2.171437F ),
	VERT( -0.250000F,  0.527615F,  2.215000F ),
	VERT(  0.966001F,  0.403741F, -0.714656F ),
	VERT( -0.250000F,  0.763733F,  2.215000F ),
	VERT( -0.286188F,  0.802431F,  2.003836F ),
	VERT( -0.599149F,  0.201609F,  1.836406F ),
	VERT( -0.946158F,  0.456146F,  2.161488F ),
	VERT( -0.520035F,  0.301136F, -2.173100F ),
	VERT( -0.520035F,  0.315431F, -2.171736F ),
	VERT( -0.930339F,  0.732383F,  2.066922F ),
	VERT(  0.957529F,  0.532814F,  1.901923F ),
	VERT(  0.845076F,  0.461009F, -1.883696F ),
	VERT(  0.971125F,  0.532814F,  1.901923F ),
	VERT(  0.986031F,  0.589368F,  1.658254F ),
	VERT( -0.923272F,  0.732383F,  2.101922F ),
	VERT( -0.907424F,  0.751406F,  2.161488F ),
	VERT(  0.865191F,  0.605298F,  0.097366F ),
	VERT( -0.769377F,  0.802249F,  1.975149F ),
	VERT( -0.769377F,  0.817098F,  1.975149F ),
	VERT( -0.494269F,  0.801467F,  1.878518F ),
	VERT( -0.494269F,  0.816317F,  1.878518F ),
	VERT( -0.493885F,  0.816440F,  1.928457F ),
	VERT( -0.767207F,  0.802002F,  1.861574F ),
	VERT( -0.767200F,  0.817000F,  1.911519F ),
	VERT( -0.767207F,  0.816852F,  1.861574F ),
	VERT( -0.747149F,  0.817285F,  2.078890F ),
	VERT( -0.887276F,  0.812600F,  1.610206F ),
	VERT( -0.705861F,  0.812398F,  1.610206F ),
	VERT( -0.642200F,  0.456148F,  2.195358F ),
	VERT( -0.405947F,  0.621861F, -1.562257F ),
	VERT( -0.250000F,  0.502625F, -1.883696F ),
	VERT( -0.792885F,  0.369747F, -2.046484F ),
	VERT( -0.845076F,  0.461009F, -1.883696F ),
	VERT( -0.971125F,  0.532814F,  1.901923F ),
	VERT( -0.957529F,  0.532814F,  1.901923F ),
	VERT( -0.986032F,  0.589368F,  1.658254F ),
	VERT( -0.936712F,  0.456146F,  2.171437F ),
	VERT(  0.908966F,  0.700437F, -0.688565F ),
	VERT( -0.851482F,  0.748108F,  2.173801F ),
	VERT( -0.898365F,  0.751406F,  2.171437F ),
	VERT( -0.939600F,  1.075494F,  2.171440F ),
	VERT(  0.946569F,  0.532814F,  2.011923F ),
	VERT(  0.537397F,  0.541429F, -1.799557F ),
	VERT(  0.874747F,  0.514993F, -1.754884F ),
	VERT(  0.959799F,  0.540978F, -0.708162F ),
	VERT(  0.989996F,  0.227226F,  0.892489F ),
	VERT(  0.493884F,  0.816440F,  1.928458F ),
	VERT(  0.966001F,  0.532112F, -0.937159F ),
	VERT( -0.931576F,  0.732383F,  1.956922F ),
	VERT(  0.848083F,  0.676501F,  0.097366F ),
	VERT( -0.951616F,  0.532814F,  1.956922F ),
	VERT(  0.827801F,  0.725009F,  0.722167F ),
	VERT( -0.927107F,  1.017446F,  1.780303F ),
	VERT(  0.893130F,  0.605298F,  0.097366F ),
	VERT( -0.924911F,  0.732383F,  2.011922F ),
	VERT(  0.992000F,  0.252954F,  0.782615F ),
	VERT( -0.917314F,  0.732383F,  2.066922F ),
	VERT( -0.874747F,  0.514993F, -1.754884F ),
	VERT( -0.664932F,  0.502805F, -1.883696F ),
	VERT( -0.678155F,  0.541076F, -1.780918F ),
	VERT( -0.946569F,  0.532814F,  2.011922F ),
	VERT(  0.927107F,  1.017446F,  1.780303F ),
	VERT( -0.966000F,  0.532112F, -0.937159F ),
	VERT( -0.959799F,  0.540978F, -0.708163F ),
	VERT( -0.893130F,  0.605298F,  0.097366F ),
	VERT( -0.999239F,  0.646976F,  1.220678F ),
	VERT( -0.989996F,  0.227226F,  0.892489F ),
	VERT(  0.767207F,  0.802002F,  1.861574F ),
	VERT(  1.000000F,  0.423506F,  1.051780F ),
	VERT( -0.992000F,  0.252954F,  0.782614F ),
	VERT( -0.537397F,  0.541429F, -1.799558F ),
	VERT( -0.848083F,  0.676501F,  0.097366F ),
	VERT( -0.827801F,  0.725009F,  0.722167F ),
	VERT( -0.865191F,  0.605298F,  0.097366F ),
	VERT(  0.927100F,  1.075494F,  2.171440F ),
	VERT(  0.887276F,  0.812600F,  1.610206F ),
	VERT(  1.000000F,  0.388059F,  0.897728F ),
	VERT(  0.984861F,  0.388059F,  0.897728F ),
	VERT(  0.980608F,  0.360277F,  0.782614F ),
	VERT( -0.964179F,  0.252954F,  0.782614F ),
	VERT( -0.980608F,  0.360277F,  0.782614F ),
	VERT(  0.705860F,  0.744654F,  1.610206F ),
	VERT( -1.000000F,  0.333042F,  1.039428F ),
	VERT( -0.984861F,  0.388059F,  0.897728F ),
	VERT( -0.962161F,  0.227226F,  0.892489F ),
	VERT( -1.000000F,  0.388059F,  0.897728F ),
	VERT( -1.000000F,  0.423506F,  1.051780F ),
	VERT(  0.964179F,  0.252954F,  0.782614F ),
	VERT(  0.784987F,  0.173665F, -2.087119F ),
	VERT( -0.887276F,  0.744664F,  1.610205F ),
	VERT(  0.927100F,  0.949074F,  2.171440F ),
	VERT( -0.705861F,  0.744654F,  1.610206F ),
	VERT(  0.939587F,  0.805197F,  1.663639F ),
	VERT(  0.891006F,  0.817280F,  2.024636F ),
	VERT(  0.908597F,  0.816638F,  1.854324F ),
	VERT(  0.904803F,  0.854228F,  2.171440F ),
	VERT( -0.819082F,  0.770472F,  1.287251F ),
	VERT(  0.938708F,  0.532814F,  2.066923F ),
	VERT(  0.910786F,  0.797437F,  2.024636F ),
	VERT( -0.819082F,  0.802193F,  1.287251F ),
	VERT(  0.956833F,  0.532111F, -1.396778F ),
	VERT( -0.774055F,  0.770472F,  1.287251F ),
	VERT( -0.774055F,  0.803500F,  1.287251F ),
	VERT( -0.879400F,  0.751506F,  1.505509F ),
	VERT(  0.147607F,  0.299948F,  2.215000F ),
	VERT( -0.875952F,  0.543240F,  2.177345F ),
	VERT( -0.927136F,  0.813802F,  1.663639F ),
	VERT( -0.418600F,  0.156780F, -2.190913F ),
	VERT( -0.472151F,  0.203344F, -2.184153F ),
	VERT( -0.784986F,  0.173665F, -2.087119F ),
	VERT( -0.875952F,  0.543240F,  2.102478F ),
	VERT(  0.147607F,  0.344384F,  2.215000F ),
	VERT( -0.577238F,  0.301136F, -2.098099F ),
	VERT( -0.577238F,  0.173665F, -2.110157F ),
	VERT( -0.715676F,  0.173665F, -2.038870F ),
	VERT( -0.773014F,  0.210954F, -2.012651F ),
	VERT( -0.784987F,  0.278689F, -2.002202F ),
	VERT( -0.773014F,  0.210954F, -2.087651F ),
	VERT(  1.000000F,  0.577499F,  1.136495F ),
	VERT(  0.520036F,  0.301136F, -2.173100F ),
	VERT(  0.946158F,  0.456146F,  2.161488F ),
	VERT(  0.951545F,  0.732383F,  1.901923F ),
	VERT(  0.887034F,  0.535361F,  0.722167F ),
	VERT( -0.851482F,  0.748108F,  2.098934F ),
	VERT( -0.823163F,  0.763738F,  2.101592F ),
	VERT( -0.927100F,  1.075494F,  2.171440F ),
	VERT( -0.475861F,  0.301136F, -2.100760F ),
	VERT( -0.475861F,  0.301136F, -2.175760F ),
	VERT(  0.987972F,  0.202976F,  0.782615F ),
	VERT(  0.950545F,  0.570256F, -1.562257F ),
	VERT(  0.599149F,  0.201609F,  1.836407F ),
	VERT(  0.537397F,  0.368680F, -2.141139F ),
	VERT( -0.494700F,  0.286522F, -2.176675F ),
	VERT( -0.494700F,  0.286522F, -2.101675F ),
	VERT( -0.418600F,  0.156780F, -2.114838F ),
	VERT( -0.472151F,  0.203344F, -2.109153F ),
	VERT( -0.405947F,  0.519680F, -1.562257F ),
	VERT( -0.029889F,  0.502625F, -1.883696F ),
	VERT( -0.952842F,  0.376336F, -1.478091F ),
	VERT( -0.418600F,  0.133733F, -2.193330F ),
	VERT( -0.520035F,  0.077661F, -2.244867F ),
	VERT( -0.418600F,  0.077662F, -2.250520F ),
	VERT( -0.409107F,  0.129436F, -2.246474F ),
	VERT( -0.418600F,  0.147874F, -2.243182F ),
	VERT( -0.409107F,  0.077662F, -2.251250F ),
	VERT(  0.475861F,  0.301136F, -2.100760F ),
	VERT( -0.938709F,  0.532814F,  2.066922F ),
	VERT( -0.910786F,  0.797437F,  2.024636F ),
	VERT( -0.891006F,  0.817280F,  2.024636F ),
	VERT( -0.908597F,  0.816638F,  1.854324F ),
	VERT( -0.956833F,  0.532111F, -1.396778F ),
	VERT( -0.926481F,  0.799842F,  1.855893F ),
	VERT( -0.939587F,  0.805197F,  1.663639F ),
	VERT( -0.904804F,  0.854228F,  2.171440F ),
	VERT( -0.939600F,  0.949074F,  2.171440F ),
	VERT(  0.774054F,  0.770472F,  1.287251F ),
	VERT(  0.774054F,  0.803500F,  1.287251F ),
	VERT( -0.927100F,  0.949074F,  2.171440F ),
	VERT( -0.918504F,  0.845259F,  2.171440F ),
	VERT( -0.928258F,  0.761960F,  2.024636F ),
	VERT(  0.054931F,  1.050032F,  0.844449F ),
	VERT(  0.221500F,  1.064094F,  0.766261F ),
	VERT(  0.050864F,  0.489905F, -1.833380F ),
	VERT(  0.029889F,  0.478090F, -1.883696F ),
	VERT(  0.982630F,  0.460780F,  1.747464F ),
	VERT(  0.642200F,  0.527615F,  2.195358F ),
	VERT(  0.847689F,  0.527620F,  2.179560F ),
	VERT(  0.847689F,  0.527615F,  2.104714F ),
	VERT(  0.250000F,  0.354325F, -2.183557F ),
	VERT(  0.250000F,  0.335431F, -2.183557F ),
	VERT(  0.466285F,  0.682032F, -1.240308F ),
	VERT(  0.408985F,  0.075770F, -2.150438F ),
	VERT(  0.221500F,  1.094793F,  0.452163F ),
	VERT(  0.250000F,  0.811271F,  2.215000F ),
	VERT(  0.250000F,  0.817280F,  2.206654F ),
	VERT(  0.221500F,  1.100239F,  0.081028F ),
	VERT(  0.054931F,  0.996078F,  1.144449F ),
	VERT(  0.054931F,  1.018559F,  1.019449F ),
	VERT(  0.054931F,  1.027551F,  0.969449F ),
	VERT(  0.054931F,  0.987086F,  1.194449F ),
	VERT(  0.054931F,  0.962026F,  1.319449F ),
	VERT( -0.870819F,  0.650879F, -0.213765F ),
	VERT(  0.054931F,  0.951585F,  1.369449F ),
	VERT(  0.054931F,  0.925483F,  1.494449F ),
	VERT(  0.221500F,  1.086778F, -0.057161F ),
	VERT(  0.966001F,  0.403537F, -0.853043F ),
	VERT(  0.066913F,  0.817280F,  2.169764F ),
	VERT(  0.418600F,  0.156780F, -2.190913F ),
	VERT(  0.638458F,  0.817283F,  2.187320F ),
	VERT(  0.754221F,  0.817282F,  2.128830F ),
	VERT(  0.747149F,  0.802436F,  2.078890F ),
	VERT(  0.917117F,  0.403741F, -0.709139F ),
	VERT(  0.929295F,  0.589000F, -1.562257F ),
	VERT(  0.067298F,  0.817280F,  2.119824F ),
	VERT(  0.067298F,  0.802431F,  2.119824F ),
	VERT(  0.768981F,  0.817214F,  2.025089F ),
	VERT(  0.285803F,  0.817281F,  2.053776F ),
	VERT(  0.879400F,  0.751506F,  1.505509F ),
	VERT(  0.931201F,  0.303359F,  0.097366F ),
	VERT(  0.918164F,  0.202977F,  0.097366F ),
	VERT( -0.927122F,  0.861906F,  1.830991F ),
	VERT(  0.872872F,  0.817280F,  2.161488F ),
	VERT(  0.942951F,  0.777978F,  1.075996F ),
	VERT(  0.948676F,  0.802858F,  1.505506F ),
	VERT(  0.978516F,  0.739042F,  1.500628F ),
	VERT(  0.978686F,  0.730510F,  1.335937F ),
	VERT(  0.250000F,  0.753456F, -1.024537F ),
	VERT(  0.250000F,  0.685873F, -1.270945F ),
	VERT(  0.005463F,  0.537615F,  2.215000F ),
	VERT(  0.005463F,  0.753733F,  2.215000F ),
	VERT(  0.015463F,  0.763733F,  2.215000F ),
	VERT(  0.015463F,  0.527615F,  2.215000F ),
	VERT(  0.250000F,  0.476146F,  2.215000F ),
	VERT(  0.005463F,  0.537615F,  2.140000F ),
	VERT(  0.005463F,  0.753733F,  2.140000F ),
	VERT(  0.494269F,  0.801467F,  1.878518F ),
	VERT(  0.149500F,  0.253277F,  2.215000F ),
	VERT(  0.286188F,  0.817281F,  2.003836F ),
	VERT(  0.250000F,  0.817280F,  1.903015F ),
	VERT(  0.250000F,  0.315431F, -2.184510F ),
	VERT(  0.250000F,  0.301136F, -2.185874F ),
	VERT(  0.939600F,  1.086462F,  1.774373F ),
	VERT(  0.927100F,  1.086462F,  1.774373F ),
	VERT(  0.927100F,  1.103348F,  2.161440F ),
	VERT(  0.939600F,  1.103348F,  2.161440F ),
	VERT(  0.887276F,  0.744664F,  1.610206F ),
	VERT(  0.932457F,  0.751406F,  2.024636F ),
	VERT(  0.947254F,  0.732383F,  1.936923F ),
	VERT(  0.747149F,  0.817285F,  2.078890F ),
	VERT(  0.917314F,  0.732383F,  2.066923F ),
	VERT(  0.964543F,  0.688893F,  1.855562F ),
	VERT(  0.959178F,  0.723157F,  1.855665F ),
	VERT(  0.987853F,  0.646976F,  1.583178F ),
	VERT(  0.989800F,  0.660320F,  1.549720F ),
	VERT(  1.000000F,  0.514292F,  1.087994F ),
	VERT(  0.984826F,  0.526225F,  0.783257F ),
	VERT(  0.938091F,  0.751350F,  1.978431F ),
	VERT(  0.978282F,  0.535361F,  0.722167F ),
	VERT(  0.405947F,  0.621861F, -1.562257F ),
	VERT(  0.792885F,  0.369747F, -2.046484F ),
	VERT(  0.951616F,  0.532814F,  1.956922F ),
	VERT(  0.910714F,  0.551637F,  0.097366F ),
	VERT(  0.931575F,  0.732383F,  1.956922F ),
	VERT(  0.961470F,  0.547045F,  0.547468F ),
	VERT(  0.967595F,  0.501847F,  0.546898F ),
	VERT(  0.977290F,  0.430302F,  0.545997F ),
	VERT(  0.928430F,  0.423741F,  0.097366F ),
	VERT(  0.922531F,  0.466331F,  0.097366F ),
	VERT(  0.875951F,  0.543240F,  2.177345F ),
	VERT(  0.912787F,  0.436445F, -0.385201F ),
	VERT(  0.914374F,  0.423742F, -0.708017F ),
	VERT(  0.112181F,  0.271084F,  2.215000F ),
	VERT(  0.112181F,  0.371084F,  2.215000F ),
	VERT(  0.250000F,  0.456146F,  2.215000F ),
	VERT(  0.499234F,  0.705792F, -1.240308F ),
	VERT( -0.499234F,  0.705792F, -1.240308F ),
	VERT(  0.767207F,  0.816852F,  1.861574F ),
	VERT(  0.250000F,  0.521601F, -1.562257F ),
	VERT(  0.250000F,  0.623782F, -1.562257F ),
	VERT(  0.050864F,  0.522100F, -1.833380F ),
	VERT( -0.466285F,  0.682032F, -1.240308F ),
	VERT(  0.015463F,  0.763733F,  2.140000F ),
	VERT(  0.961363F,  0.471292F,  2.024636F ),
	VERT(  0.955693F,  0.532814F,  2.046922F ),
	VERT(  0.952037F,  0.532814F,  2.066923F ),
	VERT(  0.946440F,  0.532814F,  2.101923F ),
	VERT(  0.944459F,  0.476146F,  2.161488F ),
	VERT(  0.961870F,  0.532814F,  1.991923F ),
	VERT(  0.960009F,  0.532814F,  2.011923F ),
	VERT(  0.965127F,  0.532814F,  1.956922F ),
	VERT(  0.967219F,  0.532814F,  1.936923F ),
	VERT(  0.944803F,  0.732383F,  1.956922F ),
	VERT(  0.940503F,  0.732383F,  1.991923F ),
	VERT(  0.938043F,  0.732383F,  2.011923F ),
	VERT(  0.933407F,  0.732383F,  2.046922F ),
	VERT(  0.821171F,  0.335431F, -2.035119F ),
	VERT(  0.821171F,  0.357911F, -2.035119F ),
	VERT(  0.876178F,  0.438883F, -1.883696F ),
	VERT(  0.876178F,  0.350306F, -1.883696F ),
	VERT(  0.784987F,  0.335431F, -2.072745F ),
	VERT(  0.784987F,  0.354325F, -2.072745F ),
	VERT(  0.520036F,  0.133732F, -2.187675F ),
	VERT(  0.520036F,  0.173665F, -2.185157F ),
	VERT(  0.715676F,  0.173665F, -2.113870F ),
	VERT(  0.499234F,  0.619940F, -1.562257F ),
	VERT(  0.520035F,  0.633855F, -1.562257F ),
	VERT(  0.918503F,  0.845259F,  2.171440F ),
	VERT(  0.499234F,  0.496078F, -1.883696F ),
	VERT(  0.960205F,  0.617055F, -0.943726F ),
	VERT(  0.950603F,  0.682442F, -0.950293F ),
	VERT(  0.929751F,  0.681694F, -0.692336F ),
	VERT(  0.949419F,  0.618559F, -0.700249F ),
	VERT(  0.954382F,  0.202977F, -0.690391F ),
	VERT(  0.942929F,  0.089178F, -0.690391F ),
	VERT(  0.942929F,  0.089178F, -0.799480F ),
	VERT(  0.954382F,  0.203177F, -0.809587F ),
	VERT(  0.863127F,  0.811255F,  2.171438F ),
	VERT(  0.638576F,  0.811274F,  2.195658F ),
	VERT(  0.642200F,  0.763733F,  2.195358F ),
	VERT(  0.823162F,  0.763738F,  2.176902F ),
	VERT(  0.739352F,  0.702105F, -0.345799F ),
	VERT(  0.740481F,  0.722747F,  0.097366F ),
	VERT(  0.850798F,  0.697592F,  0.097366F ),
	VERT(  0.851759F,  0.675542F, -0.385201F ),
	VERT(  0.861089F,  0.690126F,  0.097366F ),
	VERT(  0.873895F,  0.737162F,  0.545745F ),
	VERT(  0.884466F,  0.729695F,  0.545745F ),
	VERT(  0.987972F,  0.202976F,  0.545732F ),
	VERT(  0.976117F,  0.089178F,  0.545732F ),
	VERT(  0.959931F,  0.089178F,  0.097372F ),
	VERT(  0.971590F,  0.202976F,  0.097372F ),
	VERT(  0.713703F,  0.810324F,  1.505506F ),
	VERT(  0.405947F,  0.519680F, -1.562257F ),
	VERT(  0.029889F,  0.502625F, -1.883696F ),
	VERT(  0.713700F,  0.751506F,  1.505509F ),
	VERT(  0.740481F,  0.763909F,  0.545745F ),
	VERT(  0.740481F,  0.779339F,  0.782615F ),
	VERT(  0.892294F,  0.759522F,  0.782615F ),
	VERT(  0.953161F,  0.751406F,  1.855750F ),
	VERT(  0.962602F,  0.451292F,  2.024636F ),
	VERT(  0.923630F,  0.187470F,  2.161488F ),
	VERT(  0.948362F,  0.139552F,  1.856461F ),
	VERT(  0.977298F,  0.446437F,  1.855562F ),
	VERT(  0.000000F,  0.753456F, -1.043698F ),
	VERT(  0.976116F,  0.089178F,  1.027503F ),
	VERT(  0.976117F,  0.089178F,  0.782615F ),
	VERT(  0.927135F,  0.813802F,  1.663639F ),
	VERT(  0.935030F,  0.476146F,  2.171438F ),
	VERT(  0.196621F,  0.305519F,  2.215000F ),
	VERT(  0.280400F,  0.201609F,  1.836407F ),
	VERT(  0.773014F,  0.210954F, -2.012651F ),
	VERT(  0.645617F,  0.795355F,  1.029666F ),
	VERT(  0.708338F,  0.779339F,  0.782615F ),
	VERT(  0.784987F,  0.278689F, -2.002202F ),
	VERT(  0.995642F,  0.695542F,  1.401928F ),
	VERT(  0.520035F,  0.354325F, -2.170783F ),
	VERT(  0.519161F,  0.335431F, -2.170825F ),
	VERT(  0.950545F,  0.071032F, -1.500853F ),
	VERT(  0.904047F,  0.072296F, -1.883696F ),
	VERT(  0.876178F,  0.116346F, -1.883696F ),
	VERT(  0.938224F,  0.732383F,  1.901923F ),
	VERT(  0.221500F,  1.055995F, -0.195351F ),
	VERT(  0.823162F,  0.763738F,  2.101592F ),
	VERT(  0.250000F,  0.704833F, -1.024537F ),
	VERT(  0.520035F,  0.704833F, -0.950293F ),
	VERT(  0.520035F,  0.742794F, -0.950293F ),
	VERT(  0.505474F,  0.886945F,  1.532735F ),
	VERT(  0.520035F,  0.816012F,  1.792720F ),
	VERT(  0.646464F,  0.810324F,  1.505506F ),
	VERT(  0.767763F,  0.301136F, -2.085800F ),
	VERT(  0.821171F,  0.315431F, -2.035119F ),
	VERT(  0.876178F,  0.330306F, -1.883696F ),
	VERT(  0.460752F,  1.073090F,  0.452164F ),
	VERT(  0.460752F,  1.078536F,  0.081028F ),
	VERT(  0.577239F,  0.173665F, -2.110157F ),
	VERT(  0.579806F,  0.904811F,  1.230424F ),
	VERT(  0.622501F,  0.945726F,  0.787733F ),
	VERT(  0.175000F,  0.850279F,  1.810252F ),
	VERT(  0.015463F,  0.527615F,  2.140000F ),
	VERT(  0.862062F,  0.668076F, -0.385201F ),
	VERT(  0.868026F,  0.676501F,  0.097366F ),
	VERT(  1.000000F,  0.443805F,  1.059877F ),
	VERT(  0.983331F,  0.433577F,  0.782615F ),
	VERT(  0.897155F,  0.548805F, -0.385201F ),
	VERT(  0.896941F,  0.550862F, -0.700886F ),
	VERT(  0.966000F,  0.423739F, -0.713800F ),
	VERT(  0.819082F,  0.770472F,  1.287251F ),
	VERT(  0.966000F,  0.423539F, -0.863600F ),
	VERT(  0.418600F,  0.133733F, -2.193330F ),
	VERT(  0.404931F,  0.906596F,  1.369449F ),
	VERT(  0.404931F,  0.906672F,  1.494449F ),
	VERT(  0.404931F,  0.932877F,  1.369449F ),
	VERT(  0.978854F,  0.713081F,  1.173815F ),
	VERT(  0.944378F,  0.673502F,  0.782615F ),
	VERT(  0.054931F,  0.925305F,  1.369449F ),
	VERT(  0.404931F,  0.868387F,  1.544449F ),
	VERT(  0.404931F,  0.867644F,  1.669449F ),
	VERT(  0.404931F,  0.895989F,  1.544449F ),
	VERT(  0.889970F,  0.791412F,  2.171438F ),
	VERT(  0.404931F,  0.968520F,  1.194449F ),
	VERT(  0.404931F,  0.943126F,  1.194449F ),
	VERT(  0.054931F,  0.887331F,  1.544449F ),
	VERT(  0.054931F,  0.914933F,  1.544449F ),
	VERT(  0.054931F,  0.887667F,  1.669449F ),
	VERT(  0.054931F,  0.961692F,  1.194449F ),
	VERT(  0.992866F,  0.681837F,  1.495750F ),
	VERT(  0.906628F,  0.725009F,  0.722167F ),
	VERT(  0.894496F,  0.712970F,  0.547468F ),
	VERT(  0.903088F,  0.752055F,  0.782615F ),
	VERT(  0.706969F,  0.799781F,  1.075996F ),
	VERT(  0.404931F,  0.943325F,  1.319449F ),
	VERT(  0.175000F,  0.851082F,  1.706689F ),
	VERT(  0.175000F,  0.878859F,  1.706689F ),
	VERT(  0.054931F,  0.995553F,  1.019449F ),
	VERT(  0.404931F,  0.978294F,  1.019449F ),
	VERT(  0.404931F,  0.977886F,  1.144449F ),
	VERT(  0.404931F,  1.001300F,  1.019449F ),
	VERT(  0.642200F,  0.456148F,  2.195358F ),
	VERT(  0.615552F,  0.139552F,  1.856461F ),
	VERT(  0.054931F,  1.027079F,  0.844449F ),
	VERT(  0.404931F,  1.010707F,  0.844449F ),
	VERT(  0.404931F,  1.010666F,  0.969449F ),
	VERT(  0.404931F,  1.033660F,  0.844449F ),
	VERT(  0.560608F,  1.025685F, -0.047613F ),
	VERT(  0.692054F,  0.705954F, -0.764855F ),
	VERT(  0.735734F,  0.707075F, -0.660589F ),
	VERT(  0.692054F,  0.724934F, -0.764855F ),
	VERT(  0.560823F,  1.027906F,  0.521524F ),
	VERT(  0.549685F,  1.039690F,  0.081028F ),
	VERT(  0.784987F,  0.133732F, -2.089637F ),
	VERT(  0.642200F,  0.476148F,  2.195358F ),
	VERT(  0.466285F,  0.705792F, -1.240308F ),
	VERT(  0.520035F,  0.719706F, -1.240308F ),
	VERT(  0.699662F,  0.708351F, -1.240308F ),
	VERT(  0.699662F,  0.731439F, -0.950293F ),
	VERT(  0.767200F,  0.817000F,  1.911519F ),
	VERT(  0.966001F,  0.656108F, -1.240308F ),
	VERT(  0.966001F,  0.616228F, -1.082853F ),
	VERT(  0.861856F,  0.670339F, -0.686819F ),
	VERT(  0.851555F,  0.677805F, -0.684617F ),
	VERT(  0.418600F,  0.077662F, -2.250520F ),
	VERT( -0.917922F,  0.827296F,  1.848830F ),
	VERT(  0.738224F,  0.700697F, -0.385201F ),
	VERT( -1.000000F,  0.577499F,  1.136494F ),
	VERT(  0.564844F,  1.017175F, -0.088460F ),
	VERT(  0.930339F,  0.732383F,  2.066923F ),
	VERT(  0.489200F,  0.952216F,  1.230424F ),
	VERT(  0.460752F,  1.042391F,  0.766261F ),
	VERT(  0.460752F,  1.064682F, -0.057258F ),
	VERT(  0.460752F,  1.037354F, -0.174371F ),
	VERT(  0.519743F,  1.018843F, -0.154384F ),
	VERT(  0.953003F,  0.396874F, -1.476563F ),
	VERT(  0.977298F,  0.466437F,  1.855562F ),
	VERT(  0.931680F,  0.785445F,  1.075996F ),
	VERT(  0.937337F,  0.810324F,  1.505506F ),
	VERT(  0.883159F,  0.605802F, -0.385201F ),
	VERT(  0.409107F,  0.077662F, -2.251250F ),
	VERT(  0.879434F,  0.810324F,  1.505506F ),
	VERT(  0.821171F,  0.133732F, -2.052011F ),
	VERT(  0.846024F,  0.073874F, -2.102810F ),
	VERT(  0.883385F,  0.547045F,  0.547468F ),
	VERT(  0.882947F,  0.614334F, -0.693852F ),
	VERT(  0.562849F,  1.020657F,  0.572181F ),
	VERT(  0.773014F,  0.210954F, -2.087651F ),
	VERT(  0.520036F,  0.315431F, -2.171736F ),
	VERT( -0.951545F,  0.732383F,  1.901922F ),
	VERT(  0.784987F,  0.315431F, -2.073698F ),
	VERT(  0.797546F,  0.075768F, -2.146828F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
	NORM( -0.288332F,  0.940229F,  0.181199F ),
	NORM( -0.049150F,  0.980313F,  0.191237F ),
	NORM(  0.710135F,  0.497561F, -0.498138F ),
	NORM(  0.693103F,  0.720796F,  0.007903F ),
	NORM(  0.570562F,  0.819192F, -0.058161F ),
	NORM( -0.046779F,  0.702417F,  0.710226F ),
	NORM(  0.091028F,  0.624496F,  0.775705F ),
	NORM(  0.258596F,  0.965986F, -0.000054F ),
	NORM( -0.020403F,  0.523966F, -0.851495F ),
	NORM( -0.023633F,  0.000002F, -0.999721F ),
	NORM(  0.061406F,  0.996996F, -0.047213F ),
	NORM(  0.298008F, -0.833125F, -0.465933F ),
	NORM( -0.045093F,  0.997418F,  0.055898F ),
	NORM( -0.022107F,  0.452927F,  0.891273F ),
	NORM( -0.007840F,  0.950269F,  0.311331F ),
	NORM( -0.045104F,  0.998123F, -0.041437F ),
	NORM( -0.054530F,  0.989645F,  0.132776F ),
	NORM( -0.297135F,  0.939759F,  0.169010F ),
	NORM( -0.052900F,  0.989837F,  0.132001F ),
	NORM( -0.294355F,  0.939251F,  0.176531F ),
	NORM( -0.058498F,  0.986786F,  0.151098F ),
	NORM( -0.158127F, -0.326849F,  0.931754F ),
	NORM( -0.293144F,  0.935881F,  0.195428F ),
	NORM( -0.059738F,  0.986221F,  0.154273F ),
	NORM( -0.046271F,  0.986276F, -0.158488F ),
	NORM(  0.000072F,  0.953025F, -0.302893F ),
	NORM( -0.042160F,  0.996785F, -0.068137F ),
	NORM(  0.100459F,  0.946899F, -0.305435F ),
	NORM( -0.025080F,  0.949774F,  0.311931F ),
	NORM(  0.049319F,  0.996891F, -0.061447F ),
	NORM(  0.509975F,  0.668337F,  0.541527F ),
	NORM(  0.000000F,  0.903965F, -0.427606F ),
	NORM(  0.000126F,  0.814042F,  0.580806F ),
	NORM( -0.321406F,  0.896491F,  0.304960F ),
	NORM( -0.573993F,  0.667692F,  0.474045F ),
	NORM(  0.051066F,  0.995836F, -0.075517F ),
	NORM( -0.042241F,  0.996739F, -0.068754F ),
	NORM( -0.993114F,  0.112974F, -0.030996F ),
	NORM( -0.995905F, -0.065270F, -0.062562F ),
	NORM( -0.758941F,  0.649448F, -0.047180F ),
	NORM(  0.131720F,  0.711251F, -0.690486F ),
	NORM(  0.473109F,  0.879421F, -0.052787F ),
	NORM( -0.774984F,  0.622846F, -0.107061F ),
	NORM( -0.757671F,  0.652617F, -0.005160F ),
	NORM( -0.937651F,  0.346411F,  0.028452F ),
	NORM( -0.924480F,  0.379877F, -0.032104F ),
	NORM(  0.087922F,  0.823837F,  0.559966F ),
	NORM( -0.034370F,  0.921273F, -0.387396F ),
	NORM( -0.549133F,  0.227458F,  0.804186F ),
	NORM( -0.549133F, -0.227458F,  0.804186F ),
	NORM( -0.227458F, -0.549133F,  0.804186F ),
	NORM( -0.227458F,  0.549133F,  0.804186F ),
	NORM( -0.025018F,  0.000000F,  0.999687F ),
	NORM( -0.923879F,  0.382684F,  0.000000F ),
	NORM( -0.923879F, -0.382684F,  0.000000F ),
	NORM(  0.325983F,  0.895407F,  0.303284F ),
	NORM( -0.238758F, -0.658065F,  0.714105F ),
	NORM( -0.322191F,  0.896645F,  0.303679F ),
	NORM( -0.035424F,  0.990848F,  0.130251F ),
	NORM( -0.022988F,  0.094896F, -0.995222F ),
	NORM( -0.017146F, -0.667524F, -0.744391F ),
	NORM( -0.639797F,  0.629217F, -0.441300F ),
	NORM(  0.564008F,  0.676064F, -0.474165F ),
	NORM(  0.594874F,  0.667348F,  0.448075F ),
	NORM( -0.580811F,  0.662197F,  0.473448F ),
	NORM( -0.553801F, -0.569953F,  0.607007F ),
	NORM( -0.948060F,  0.286968F,  0.137227F ),
	NORM( -0.995245F,  0.095190F,  0.020664F ),
	NORM(  0.448557F, -0.600904F,  0.661597F ),
	NORM( -0.987215F,  0.105841F,  0.119183F ),
	NORM( -0.983546F,  0.152027F,  0.097601F ),
	NORM( -0.991969F,  0.108560F,  0.064901F ),
	NORM( -0.988720F,  0.132275F,  0.070255F ),
	NORM( -0.998139F,  0.012569F, -0.059669F ),
	NORM( -0.990517F,  0.122795F, -0.061616F ),
	NORM( -0.934036F,  0.340400F,  0.108184F ),
	NORM( -0.851378F,  0.435424F, -0.292509F ),
	NORM(  0.988815F,  0.118689F,  0.090316F ),
	NORM(  0.885495F,  0.209312F,  0.414834F ),
	NORM( -0.551637F,  0.657213F,  0.513583F ),
	NORM( -0.976148F,  0.205675F, -0.069523F ),
	NORM( -0.283662F,  0.913560F,  0.291451F ),
	NORM( -0.649009F,  0.760747F, -0.007143F ),
	NORM( -0.989054F,  0.125889F, -0.076971F ),
	NORM( -0.995552F,  0.075815F, -0.055937F ),
	NORM( -0.988486F,  0.136423F, -0.065458F ),
	NORM( -0.988318F,  0.136728F, -0.067328F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM( -0.990393F,  0.137153F, -0.017609F ),
	NORM( -0.704331F,  0.057069F,  0.707574F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM( -0.030438F, -0.005378F,  0.999522F ),
	NORM(  0.996627F, -0.043174F, -0.069795F ),
	NORM( -0.995741F, -0.035453F, -0.085108F ),
	NORM(  0.999962F, -0.008160F, -0.003181F ),
	NORM( -0.026708F,  0.861996F,  0.506210F ),
	NORM( -0.008590F,  0.823300F,  0.567541F ),
	NORM(  0.199492F,  0.837349F, -0.508970F ),
	NORM( -0.061406F,  0.996996F, -0.047213F ),
	NORM( -0.376974F, -0.926224F, -0.000006F ),
	NORM( -0.991693F,  0.055134F,  0.116216F ),
	NORM( -0.989531F,  0.131728F,  0.058963F ),
	NORM( -0.922039F,  0.360625F,  0.140690F ),
	NORM( -0.982595F,  0.174072F,  0.064858F ),
	NORM( -0.901046F,  0.111743F,  0.419082F ),
	NORM( -0.991093F,  0.133099F,  0.004281F ),
	NORM( -0.931947F,  0.348657F,  0.099566F ),
	NORM( -0.929377F,  0.355801F,  0.098304F ),
	NORM( -0.992017F,  0.125568F,  0.011579F ),
	NORM( -0.983380F, -0.138330F,  0.117596F ),
	NORM( -0.995140F,  0.097196F,  0.015758F ),
	NORM( -0.983636F, -0.136167F,  0.117974F ),
	NORM( -0.993191F,  0.104996F,  0.050479F ),
	NORM( -0.845361F,  0.000000F, -0.534195F ),
	NORM( -0.766968F,  0.311009F, -0.561278F ),
	NORM( -0.828959F,  0.382513F, -0.408058F ),
	NORM( -0.960713F,  0.000000F, -0.277543F ),
	NORM( -0.547737F, -0.003590F, -0.836643F ),
	NORM( -0.469941F,  0.414502F, -0.779323F ),
	NORM( -0.185128F,  0.426173F, -0.885496F ),
	NORM( -0.324527F,  0.167196F, -0.930982F ),
	NORM( -0.133762F,  0.671868F, -0.728492F ),
	NORM(  0.228345F,  0.922946F, -0.309885F ),
	NORM(  0.217607F,  0.927897F, -0.302745F ),
	NORM(  0.906786F,  0.401583F,  0.128337F ),
	NORM(  0.124833F,  0.901726F, -0.413892F ),
	NORM( -0.989623F,  0.135871F,  0.046747F ),
	NORM( -0.868405F,  0.494536F,  0.036142F ),
	NORM( -0.672582F,  0.327790F,  0.663466F ),
	NORM( -0.737396F,  0.055722F,  0.673158F ),
	NORM( -0.919908F,  0.243762F,  0.307163F ),
	NORM( -0.994876F, -0.100529F, -0.010727F ),
	NORM( -0.994983F, -0.100045F,  0.000000F ),
	NORM( -0.997033F, -0.076982F,  0.000047F ),
	NORM(  0.024628F,  0.438138F,  0.898570F ),
	NORM( -0.068469F,  0.452311F,  0.889228F ),
	NORM( -0.056074F, -0.701054F,  0.710900F ),
	NORM(  0.077248F, -0.622916F,  0.778465F ),
	NORM( -0.587424F,  0.808412F, -0.037444F ),
	NORM( -0.583548F,  0.810561F, -0.049630F ),
	NORM( -0.408782F,  0.909901F, -0.070548F ),
	NORM( -0.412770F,  0.910703F, -0.015496F ),
	NORM( -0.751815F,  0.656298F, -0.063615F ),
	NORM( -0.380425F,  0.919174F, -0.101957F ),
	NORM( -0.736103F,  0.668340F, -0.107120F ),
	NORM( -0.746400F,  0.665361F, -0.013453F ),
	NORM( -0.994501F, -0.103177F, -0.017967F ),
	NORM( -0.994386F, -0.101854F, -0.028663F ),
	NORM( -0.740377F,  0.671853F, -0.021362F ),
	NORM( -0.674166F,  0.732170F,  0.097090F ),
	NORM(  0.656524F, -0.066959F,  0.751327F ),
	NORM( -0.476709F,  0.414678F, -0.775107F ),
	NORM( -0.711092F,  0.681888F,  0.171396F ),
	NORM( -0.521618F,  0.852648F, -0.030099F ),
	NORM( -0.052206F,  0.995518F, -0.078862F ),
	NORM( -0.343005F,  0.932117F, -0.116214F ),
	NORM( -0.938500F,  0.334358F,  0.086159F ),
	NORM( -0.990363F, -0.090666F,  0.104698F ),
	NORM( -0.450104F, -0.598591F,  0.662642F ),
	NORM( -0.717274F, -0.680135F,  0.151438F ),
	NORM( -0.992685F, -0.094279F,  0.075420F ),
	NORM(  0.994106F, -0.093574F,  0.054750F ),
	NORM( -0.994928F, -0.100566F,  0.001973F ),
	NORM( -0.994617F, -0.103618F,  0.000704F ),
	NORM(  0.408394F,  0.912757F, -0.009442F ),
	NORM(  0.017829F,  0.701519F,  0.712428F ),
	NORM( -0.209588F, -0.411001F,  0.887215F ),
	NORM( -0.045864F, -0.973042F,  0.226023F ),
	NORM( -0.939347F, -0.342967F,  0.000000F ),
	NORM( -0.765168F,  0.348996F, -0.541036F ),
	NORM( -0.441435F,  0.896861F,  0.027833F ),
	NORM( -0.458416F, -0.075011F, -0.885566F ),
	NORM( -0.933345F,  0.358858F, -0.009348F ),
	NORM( -0.141744F,  0.488595F, -0.860920F ),
	NORM( -0.195121F, -0.003437F, -0.980773F ),
	NORM( -0.982130F,  0.043004F, -0.183225F ),
	NORM( -0.834681F,  0.528817F, -0.153819F ),
	NORM( -0.934292F,  0.282884F, -0.216968F ),
	NORM( -0.122508F,  0.899704F, -0.418956F ),
	NORM( -0.053781F,  0.951031F, -0.304382F ),
	NORM(  0.109276F,  0.809757F,  0.576500F ),
	NORM(  0.344272F,  0.778344F,  0.525030F ),
	NORM(  0.313643F,  0.815923F,  0.485693F ),
	NORM( -0.306460F,  0.929122F,  0.206918F ),
	NORM( -0.081628F,  0.992125F,  0.095000F ),
	NORM( -0.254296F,  0.964677F,  0.068787F ),
	NORM(  0.545051F, -0.838403F,  0.000000F ),
	NORM( -0.864239F,  0.047150F, -0.500867F ),
	NORM( -0.967408F,  0.014173F, -0.252828F ),
	NORM( -0.243448F,  0.968722F,  0.048061F ),
	NORM( -0.246993F,  0.968292F, -0.037480F ),
	NORM( -0.362022F,  0.932169F,  0.000000F ),
	NORM( -0.562382F,  0.814095F,  0.144831F ),
	NORM( -0.942870F,  0.143383F, -0.300729F ),
	NORM(  0.000049F,  0.973261F,  0.229703F ),
	NORM( -0.377585F,  0.925975F,  0.000000F ),
	NORM( -0.804976F,  0.593226F, -0.009816F ),
	NORM( -0.851307F, -0.523917F,  0.028061F ),
	NORM( -0.996330F, -0.030874F, -0.079835F ),
	NORM( -0.999188F, -0.007818F, -0.039534F ),
	NORM( -0.982663F,  0.184864F, -0.014094F ),
	NORM( -0.723257F,  0.070863F,  0.686933F ),
	NORM( -0.755822F, -0.002410F,  0.654773F ),
	NORM(  0.593212F,  0.564484F, -0.573984F ),
	NORM( -0.999051F,  0.035160F,  0.025693F ),
	NORM( -0.171040F, -0.134872F, -0.975989F ),
	NORM(  0.687785F,  0.725914F, -0.001034F ),
	NORM( -0.050197F,  0.986645F,  0.154955F ),
	NORM(  0.194606F,  0.960073F,  0.200968F ),
	NORM( -0.938669F,  0.336336F, -0.076019F ),
	NORM( -0.910010F,  0.353034F, -0.217368F ),
	NORM( -0.725472F,  0.688251F, -0.000981F ),
	NORM(  0.688546F,  0.725190F, -0.001948F ),
	NORM( -0.063420F,  0.980006F,  0.188591F ),
	NORM(  0.190899F,  0.957316F,  0.217034F ),
	NORM( -0.549642F, -0.012158F,  0.835312F ),
	NORM(  0.199129F,  0.962833F,  0.182483F ),
	NORM(  0.687616F,  0.726073F, -0.001549F ),
	NORM( -0.725906F,  0.687792F, -0.001847F ),
	NORM( -0.291621F,  0.935477F,  0.199599F ),
	NORM( -0.051517F,  0.985810F,  0.159766F ),
	NORM( -0.725140F,  0.688600F, -0.001469F ),
	NORM( -0.973258F,  0.220673F,  0.063814F ),
	NORM( -0.817735F,  0.123488F, -0.562193F ),
	NORM( -0.864241F, -0.502499F, -0.024122F ),
	NORM( -0.739061F,  0.647697F, -0.185141F ),
	NORM( -0.380650F,  0.923602F, -0.045442F ),
	NORM( -0.050201F,  0.987013F,  0.152597F ),
	NORM(  0.708844F,  0.705344F,  0.005464F ),
	NORM(  0.208618F,  0.968040F,  0.139199F ),
	NORM( -0.723846F,  0.689955F, -0.002903F ),
	NORM(  0.689744F,  0.724047F, -0.003047F ),
	NORM( -0.052194F,  0.989282F,  0.136367F ),
	NORM(  0.201337F,  0.963208F,  0.178025F ),
	NORM(  0.436577F, -0.046790F,  0.898449F ),
	NORM(  0.676076F, -0.709363F,  0.199313F ),
	NORM( -0.722861F,  0.690989F, -0.002610F ),
	NORM(  0.690200F,  0.723613F, -0.002733F ),
	NORM( -0.050166F,  0.989515F,  0.135436F ),
	NORM(  0.210068F,  0.949609F,  0.232625F ),
	NORM(  0.954880F, -0.167712F, -0.245106F ),
	NORM(  0.489166F,  0.832400F,  0.260437F ),
	NORM( -0.353480F,  0.935324F, -0.014868F ),
	NORM(  0.490531F,  0.768379F,  0.411064F ),
	NORM( -0.634845F,  0.772058F,  0.029973F ),
	NORM( -0.647320F,  0.761652F, -0.029376F ),
	NORM(  0.998007F, -0.000526F, -0.063102F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.691408F,  0.722278F, -0.016382F ),
	NORM(  0.252844F,  0.953990F, -0.161162F ),
	NORM( -0.097590F,  0.980724F, -0.169284F ),
	NORM( -0.090441F,  0.995586F, -0.025060F ),
	NORM(  0.295006F,  0.910179F, -0.290767F ),
	NORM( -0.897060F,  0.436526F, -0.068765F ),
	NORM( -0.996288F,  0.072980F,  0.045662F ),
	NORM( -0.578824F,  0.278485F,  0.766426F ),
	NORM( -0.405433F,  0.480523F,  0.777638F ),
	NORM( -0.894193F,  0.441434F, -0.074532F ),
	NORM(  0.399909F, -0.864314F, -0.305014F ),
	NORM( -0.596378F,  0.802635F, -0.010484F ),
	NORM(  0.997811F,  0.022662F,  0.062131F ),
	NORM( -0.652842F,  0.745540F, -0.134042F ),
	NORM( -0.141542F, -0.183323F, -0.972810F ),
	NORM( -0.294202F,  0.939541F,  0.175235F ),
	NORM( -0.269112F,  0.949427F,  0.161761F ),
	NORM( -0.237916F,  0.959204F, -0.152717F ),
	NORM( -0.230466F,  0.926400F, -0.297774F ),
	NORM( -0.423640F,  0.864348F, -0.270983F ),
	NORM(  0.654367F,  0.571019F,  0.495722F ),
	NORM(  0.743654F,  0.664458F, -0.073990F ),
	NORM( -0.327027F,  0.940418F, -0.093096F ),
	NORM( -0.294892F,  0.955183F, -0.025793F ),
	NORM( -0.959614F,  0.281179F, -0.008931F ),
	NORM(  0.989310F,  0.125995F,  0.073429F ),
	NORM(  0.673911F,  0.732821F,  0.093900F ),
	NORM(  0.768103F, -0.624004F,  0.143655F ),
	NORM(  0.983831F,  0.173775F, -0.043352F ),
	NORM(  0.795617F, -0.602398F,  0.064108F ),
	NORM(  0.740117F,  0.038549F,  0.671372F ),
	NORM( -0.708720F,  0.122956F,  0.694692F ),
	NORM( -0.627227F,  0.775691F,  0.069926F ),
	NORM( -0.835498F, -0.549493F, -0.000001F ),
	NORM(  0.431211F,  0.077074F,  0.898953F ),
	NORM( -0.358948F,  0.933357F,  0.000000F ),
	NORM(  0.996738F,  0.044912F, -0.067061F ),
	NORM(  0.982071F,  0.000000F, -0.188513F ),
	NORM( -0.436693F, -0.317578F,  0.841691F ),
	NORM(  0.411478F,  0.898391F, -0.153559F ),
	NORM(  0.770151F, -0.605435F, -0.200786F ),
	NORM( -0.570562F,  0.819192F, -0.058161F ),
	NORM( -0.996032F, -0.086977F, -0.018867F ),
	NORM( -0.882987F,  0.393523F, -0.255877F ),
	NORM( -0.999951F,  0.003600F, -0.009195F ),
	NORM(  0.010444F,  0.917106F, -0.398507F ),
	NORM( -0.406005F,  0.854570F, -0.323836F ),
	NORM( -0.411478F,  0.898391F, -0.153559F ),
	NORM( -0.474816F,  0.663167F, -0.578583F ),
	NORM( -0.352633F,  0.653238F,  0.670022F ),
	NORM( -0.408394F,  0.912757F, -0.009442F ),
	NORM( -0.100459F,  0.946899F, -0.305435F ),
	NORM(  0.990920F,  0.068080F,  0.115946F ),
	NORM( -0.029728F,  0.860211F, -0.509072F ),
	NORM(  0.122508F,  0.899704F, -0.418956F ),
	NORM( -0.174402F, -0.544127F, -0.820676F ),
	NORM( -0.704504F,  0.701812F,  0.105517F ),
	NORM( -0.139941F, -0.543366F, -0.827750F ),
	NORM( -0.545051F, -0.838403F,  0.000000F ),
	NORM( -0.649752F,  0.756649F, -0.072825F ),
	NORM( -0.955232F, -0.168368F, -0.243276F ),
	NORM( -0.994106F, -0.093575F,  0.054750F ),
	NORM(  0.949659F,  0.313011F, -0.013126F ),
	NORM(  0.153279F, -0.327287F,  0.932410F ),
	NORM( -0.998327F, -0.057821F,  0.000086F ),
	NORM( -0.780870F,  0.031537F,  0.623897F ),
	NORM( -0.724202F,  0.080430F,  0.684882F ),
	NORM( -0.740117F,  0.038549F,  0.671372F ),
	NORM( -0.898401F,  0.439177F, -0.000034F ),
	NORM( -0.998007F, -0.000526F, -0.063103F ),
	NORM( -0.991913F,  0.063148F, -0.110094F ),
	NORM(  0.616280F,  0.617192F, -0.489155F ),
	NORM(  0.998385F, -0.056326F,  0.007422F ),
	NORM( -0.790340F, -0.604071F,  0.102279F ),
	NORM( -0.964566F,  0.244293F, -0.099668F ),
	NORM( -0.654367F,  0.571019F,  0.495722F ),
	NORM( -0.744167F,  0.664463F, -0.068587F ),
	NORM(  0.129865F,  0.887687F, -0.441754F ),
	NORM(  0.955658F,  0.276892F, -0.100244F ),
	NORM( -0.855736F,  0.517412F,  0.000000F ),
	NORM(  0.118117F,  0.923213F, -0.365686F ),
	NORM( -0.795378F, -0.602223F,  0.068566F ),
	NORM( -0.594100F,  0.801584F,  0.067141F ),
	NORM(  0.560628F, -0.000038F,  0.828068F ),
	NORM( -0.997833F,  0.024106F,  0.061227F ),
	NORM( -0.997811F,  0.022662F,  0.062130F ),
	NORM( -0.990920F,  0.068080F,  0.115946F ),
	NORM( -0.996693F,  0.025497F,  0.077149F ),
	NORM( -0.991465F, -0.002327F, -0.130356F ),
	NORM( -0.649041F,  0.626444F, -0.431641F ),
	NORM( -0.822616F,  0.338781F, -0.456652F ),
	NORM(  0.141544F, -0.183322F, -0.972810F ),
	NORM( -0.602557F,  0.075750F, -0.794473F ),
	NORM( -0.364090F,  0.691767F, -0.623616F ),
	NORM( -0.501149F,  0.412673F, -0.760625F ),
	NORM( -0.065725F, -0.004784F,  0.997826F ),
	NORM(  0.574176F,  0.667675F,  0.473848F ),
	NORM(  0.017777F, -0.701522F,  0.712426F ),
	NORM( -0.766819F, -0.605740F, -0.212292F ),
	NORM( -0.467265F,  0.059404F,  0.882119F ),
	NORM( -0.017829F,  0.701519F,  0.712428F ),
	NORM(  0.780870F,  0.031537F,  0.623897F ),
	NORM( -0.017776F, -0.701533F,  0.712415F ),
	NORM( -0.574176F,  0.667675F,  0.473848F ),
	NORM(  0.574186F, -0.768098F,  0.283436F ),
	NORM( -0.903105F, -0.075721F,  0.422692F ),
	NORM( -0.344256F, -0.004296F, -0.938866F ),
	NORM( -0.199210F,  0.100372F, -0.974803F ),
	NORM( -0.979475F, -0.102148F,  0.173763F ),
	NORM(  0.711657F,  0.674335F, -0.197020F ),
	NORM(  0.368530F,  0.798265F, -0.476402F ),
	NORM(  0.939845F,  0.326581F,  0.100178F ),
	NORM(  0.996249F,  0.062053F,  0.060310F ),
	NORM( -0.989465F,  0.117658F,  0.084354F ),
	NORM( -0.885495F,  0.209311F,  0.414833F ),
	NORM(  0.616505F,  0.781076F,  0.099203F ),
	NORM(  0.551637F,  0.657213F,  0.513583F ),
	NORM(  0.283662F,  0.913560F,  0.291451F ),
	NORM( -0.573998F,  0.669285F,  0.471787F ),
	NORM( -0.326036F,  0.895363F,  0.303356F ),
	NORM( -0.041975F,  0.996209F, -0.076197F ),
	NORM(  0.550034F,  0.657271F,  0.515226F ),
	NORM(  0.051592F,  0.995429F, -0.080370F ),
	NORM(  0.280690F,  0.914043F,  0.292812F ),
	NORM(  0.282059F,  0.895105F,  0.345296F ),
	NORM(  0.293847F,  0.909579F, -0.293802F ),
	NORM( -0.295006F,  0.910179F, -0.290768F ),
	NORM( -0.065472F, -0.017484F,  0.997701F ),
	NORM(  0.368851F,  0.924466F,  0.096495F ),
	NORM( -0.010444F,  0.917106F, -0.398507F ),
	NORM( -0.350441F,  0.762684F, -0.543603F ),
	NORM( -0.379756F,  0.792140F, -0.477806F ),
	NORM( -0.939845F,  0.326581F,  0.100178F ),
	NORM( -0.711657F,  0.674335F, -0.197020F ),
	NORM( -0.996249F,  0.062053F,  0.060309F ),
	NORM( -0.436579F, -0.046790F,  0.898449F ),
	NORM(  0.352633F,  0.653238F,  0.670022F ),
	NORM(  0.426074F, -0.315616F,  0.847849F ),
	NORM( -0.441840F,  0.080874F,  0.893441F ),
	NORM( -0.560628F, -0.000037F,  0.828067F ),
	NORM(  0.706974F,  0.682800F, -0.184315F ),
	NORM( -0.165068F,  0.917636F, -0.361521F ),
	NORM(  0.367321F,  0.836947F, -0.405703F ),
	NORM(  0.748137F,  0.007700F,  0.663500F ),
	NORM(  0.943703F,  0.225328F, -0.242183F ),
	NORM(  0.041908F,  0.996207F, -0.076256F ),
	NORM(  0.996889F,  0.073407F,  0.028715F ),
	NORM( -0.764377F, -0.604629F, -0.223946F ),
	NORM(  0.793271F, -0.603017F,  0.084204F ),
	NORM( -0.710580F,  0.672112F, -0.208185F ),
	NORM(  0.667963F, -0.516122F, -0.536138F ),
	NORM(  1.000000F, -0.000088F, -0.000040F ),
	NORM(  0.594010F,  0.803063F,  0.047351F ),
	NORM( -0.770151F, -0.605435F, -0.200786F ),
	NORM(  0.750400F,  0.648576F,  0.127468F ),
	NORM( -0.762754F, -0.624353F, -0.168492F ),
	NORM( -0.388901F,  0.825905F, -0.408213F ),
	NORM( -0.129865F,  0.887687F, -0.441754F ),
	NORM( -0.118117F,  0.923213F, -0.365686F ),
	NORM( -0.706974F,  0.682800F, -0.184315F ),
	NORM( -1.000000F, -0.000088F, -0.000041F ),
	NORM( -0.996889F,  0.073407F,  0.028715F ),
	NORM( -0.748137F,  0.007700F,  0.663500F ),
	NORM( -0.594010F,  0.803063F,  0.047351F ),
	NORM( -0.961984F,  0.258746F, -0.087392F ),
	NORM( -0.943702F,  0.225329F, -0.242184F ),
	NORM( -0.549976F,  0.657264F,  0.515296F ),
	NORM(  1.000000F,  0.000949F, -0.000328F ),
	NORM( -0.750044F,  0.647759F,  0.133572F ),
	NORM(  0.165068F,  0.917635F, -0.361521F ),
	NORM( -0.792928F, -0.602763F,  0.089121F ),
	NORM( -0.667962F, -0.516122F, -0.536138F ),
	NORM( -0.616256F,  0.780766F,  0.103117F ),
	NORM( -0.801586F,  0.028673F,  0.597192F ),
	NORM( -0.293845F,  0.909550F, -0.293894F ),
	NORM(  0.954816F, -0.147851F, -0.257812F ),
	NORM(  0.511985F, -0.674560F, -0.531828F ),
	NORM(  0.658583F, -0.735848F,  0.157470F ),
	NORM( -0.760827F,  0.625259F,  0.173764F ),
	NORM( -0.659157F, -0.736416F,  0.152327F ),
	NORM(  0.596516F,  0.593200F, -0.540632F ),
	NORM( -0.998385F, -0.056326F,  0.007421F ),
	NORM( -0.510051F, -0.671921F, -0.537002F ),
	NORM( -0.613575F,  0.614710F, -0.495638F ),
	NORM( -0.955770F, -0.086621F, -0.281072F ),
	NORM( -0.999843F,  0.017105F, -0.004522F ),
	NORM(  0.760080F,  0.624492F,  0.179687F ),
	NORM(  0.551459F,  0.070643F, -0.831206F ),
	NORM(  0.596615F,  0.593263F, -0.540453F ),
	NORM( -0.756200F,  0.062027F,  0.651394F ),
	NORM( -0.596535F,  0.593215F, -0.540594F ),
	NORM(  0.839501F,  0.529783F, -0.120702F ),
	NORM( -0.433989F,  0.899629F, -0.048180F ),
	NORM( -0.428113F,  0.902212F, -0.052267F ),
	NORM( -0.597112F,  0.304380F,  0.742166F ),
	NORM(  0.664363F,  0.718315F,  0.206505F ),
	NORM(  0.704944F,  0.695737F, -0.137855F ),
	NORM(  0.993517F,  0.022765F,  0.111379F ),
	NORM(  0.704504F,  0.701812F,  0.105517F ),
	NORM(  0.998914F, -0.031876F, -0.033979F ),
	NORM( -0.664442F,  0.718228F,  0.206558F ),
	NORM( -0.728853F,  0.674101F,  0.119837F ),
	NORM(  0.710882F,  0.682089F,  0.171468F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.396578F,  0.265331F,  0.878820F ),
	NORM(  0.011918F,  0.934556F, -0.355615F ),
	NORM( -0.086227F,  0.862142F, -0.499276F ),
	NORM(  0.476709F,  0.414678F, -0.775107F ),
	NORM( -0.551457F,  0.070643F, -0.831207F ),
	NORM(  0.898401F,  0.439177F, -0.000033F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM( -0.399909F, -0.864314F, -0.305014F ),
	NORM( -0.403252F,  0.861854F, -0.307564F ),
	NORM(  0.362022F,  0.932169F,  0.000000F ),
	NORM(  0.873702F,  0.486462F,  0.000000F ),
	NORM(  0.976717F, -0.214533F,  0.000000F ),
	NORM(  0.253887F,  0.499584F, -0.828225F ),
	NORM(  0.984871F,  0.148056F, -0.090048F ),
	NORM(  0.344256F, -0.004296F, -0.938866F ),
	NORM(  0.903104F, -0.075721F,  0.422693F ),
	NORM(  0.982705F, -0.127576F,  0.134220F ),
	NORM(  0.474816F,  0.663167F, -0.578583F ),
	NORM(  0.835499F, -0.549493F,  0.000000F ),
	NORM(  0.259643F, -0.965705F, -0.000007F ),
	NORM(  0.801585F,  0.028673F,  0.597193F ),
	NORM(  0.319910F, -0.947448F,  0.000000F ),
	NORM(  0.174402F, -0.544127F, -0.820676F ),
	NORM(  0.995957F, -0.086962F, -0.022514F ),
	NORM(  0.877828F,  0.404295F, -0.256835F ),
	NORM( -0.579538F, -0.764700F,  0.281727F ),
	NORM(  0.029728F,  0.860211F, -0.509071F ),
	NORM(  0.458416F, -0.075011F, -0.885566F ),
	NORM(  0.939347F, -0.342967F,  0.000000F ),
	NORM(  0.358948F,  0.933357F,  0.000000F ),
	NORM(  0.855736F,  0.517412F,  0.000000F ),
	NORM(  0.493138F,  0.743649F,  0.451444F ),
	NORM(  0.726823F,  0.684178F, -0.060246F ),
	NORM( -0.982143F,  0.000000F, -0.188134F ),
	NORM( -0.658702F,  0.316888F, -0.682417F ),
	NORM( -0.131720F,  0.711252F, -0.690486F ),
	NORM( -0.286131F,  0.409830F, -0.866123F ),
	NORM(  0.171040F, -0.134872F, -0.975989F ),
	NORM( -0.593212F,  0.564484F, -0.573984F ),
	NORM(  0.661863F,  0.074071F, -0.745956F ),
	NORM( -0.319910F, -0.947448F,  0.000000F ),
	NORM( -0.703275F,  0.693736F, -0.155353F ),
	NORM( -0.993517F,  0.022764F,  0.111380F ),
	NORM(  0.433990F,  0.899628F, -0.048179F ),
	NORM(  0.428113F,  0.902213F, -0.052267F ),
	NORM( -0.998998F, -0.019938F, -0.040079F ),
	NORM( -0.989309F,  0.125996F,  0.073429F ),
	NORM( -0.839501F,  0.529782F, -0.120702F ),
	NORM(  0.597112F,  0.304379F,  0.742166F ),
	NORM( -0.656524F, -0.066959F,  0.751327F ),
	NORM(  0.664442F,  0.718228F,  0.206556F ),
	NORM(  0.728853F,  0.674101F,  0.119835F ),
	NORM(  0.756199F,  0.062028F,  0.651395F ),
	NORM( -0.671764F, -0.228811F,  0.704542F ),
	NORM( -0.906786F,  0.401582F,  0.128337F ),
	NORM(  0.288332F,  0.940229F,  0.181199F ),
	NORM(  0.049150F,  0.980313F,  0.191237F ),
	NORM( -0.710135F,  0.497561F, -0.498138F ),
	NORM( -0.693103F,  0.720796F,  0.007903F ),
	NORM(  0.997833F,  0.024106F,  0.061227F ),
	NORM(  0.046779F,  0.702417F,  0.710226F ),
	NORM( -0.091028F,  0.624496F,  0.775706F ),
	NORM( -0.258596F,  0.965986F, -0.000055F ),
	NORM(  0.020403F,  0.523966F, -0.851495F ),
	NORM(  0.023633F,  0.000002F, -0.999721F ),
	NORM( -0.722818F,  0.681006F, -0.117328F ),
	NORM( -0.298008F, -0.833125F, -0.465933F ),
	NORM(  0.045093F,  0.997418F,  0.055898F ),
	NORM(  0.022107F,  0.452927F,  0.891273F ),
	NORM(  0.007840F,  0.950269F,  0.311331F ),
	NORM(  0.045104F,  0.998123F, -0.041437F ),
	NORM(  0.054530F,  0.989645F,  0.132776F ),
	NORM(  0.297135F,  0.939759F,  0.169010F ),
	NORM(  0.052900F,  0.989837F,  0.132001F ),
	NORM(  0.294355F,  0.939251F,  0.176531F ),
	NORM(  0.058498F,  0.986786F,  0.151098F ),
	NORM( -0.949659F,  0.313010F, -0.013127F ),
	NORM(  0.293144F,  0.935881F,  0.195428F ),
	NORM(  0.059733F,  0.986123F,  0.154897F ),
	NORM(  0.046271F,  0.986276F, -0.158488F ),
	NORM(  0.998327F, -0.057821F,  0.000086F ),
	NORM(  0.042205F,  0.996783F, -0.068140F ),
	NORM(  0.086227F,  0.862142F, -0.499276F ),
	NORM(  0.025080F,  0.949774F,  0.311931F ),
	NORM( -0.049274F,  0.996893F, -0.061450F ),
	NORM( -0.509880F,  0.668385F,  0.541557F ),
	NORM(  0.724202F,  0.080430F,  0.684882F ),
	NORM(  0.394922F,  0.860136F, -0.322803F ),
	NORM(  0.321412F,  0.896485F,  0.304973F ),
	NORM(  0.574084F,  0.667644F,  0.474003F ),
	NORM( -0.051036F,  0.995842F, -0.075458F ),
	NORM(  0.042319F,  0.996746F, -0.068599F ),
	NORM( -0.710907F,  0.682105F,  0.171305F ),
	NORM(  0.995905F, -0.065270F, -0.062562F ),
	NORM(  0.758941F,  0.649448F, -0.047180F ),
	NORM(  0.993114F,  0.112975F, -0.030996F ),
	NORM( -0.473109F,  0.879421F, -0.052785F ),
	NORM(  0.774984F,  0.622847F, -0.107061F ),
	NORM(  0.757671F,  0.652617F, -0.005160F ),
	NORM(  0.937651F,  0.346411F,  0.028452F ),
	NORM(  0.918634F,  0.392918F, -0.041568F ),
	NORM( -0.087872F,  0.826818F,  0.555563F ),
	NORM(  0.039887F,  0.920004F, -0.389873F ),
	NORM(  0.549133F,  0.227458F,  0.804186F ),
	NORM(  0.549133F, -0.227458F,  0.804186F ),
	NORM(  0.227458F, -0.549133F,  0.804186F ),
	NORM(  0.227458F,  0.549133F,  0.804186F ),
	NORM(  0.025018F,  0.000000F,  0.999687F ),
	NORM(  0.923879F,  0.382684F,  0.000000F ),
	NORM(  0.923879F, -0.382684F,  0.000000F ),
	NORM(  0.573977F,  0.669260F,  0.471848F ),
	NORM(  0.238758F, -0.658065F,  0.714105F ),
	NORM(  0.322134F,  0.896692F,  0.303602F ),
	NORM(  0.035372F,  0.990858F,  0.130187F ),
	NORM(  0.022988F,  0.094896F, -0.995222F ),
	NORM(  0.017146F, -0.667524F, -0.744391F ),
	NORM(  0.639797F,  0.629217F, -0.441300F ),
	NORM( -0.564007F,  0.676064F, -0.474165F ),
	NORM( -0.594873F,  0.667349F,  0.448075F ),
	NORM(  0.580812F,  0.662197F,  0.473447F ),
	NORM( -0.596539F,  0.593176F, -0.540633F ),
	NORM(  0.948060F,  0.286969F,  0.137226F ),
	NORM(  0.995245F,  0.095190F,  0.020664F ),
	NORM( -0.281987F,  0.895081F,  0.345417F ),
	NORM(  0.768276F, -0.622238F, -0.150240F ),
	NORM(  0.987215F,  0.105840F,  0.119183F ),
	NORM(  0.983545F,  0.152028F,  0.097601F ),
	NORM(  0.991969F,  0.108557F,  0.064902F ),
	NORM(  0.988720F,  0.132278F,  0.070255F ),
	NORM(  0.998327F,  0.024208F, -0.052515F ),
	NORM(  0.991114F,  0.118608F, -0.060201F ),
	NORM(  0.934036F,  0.340402F,  0.108183F ),
	NORM(  0.856043F,  0.437460F, -0.275353F ),
	NORM( -0.368850F,  0.924466F,  0.096495F ),
	NORM(  0.350440F,  0.762685F, -0.543602F ),
	NORM(  0.710580F,  0.672113F, -0.208184F ),
	NORM(  0.976148F,  0.205675F, -0.069523F ),
	NORM(  0.764377F, -0.604629F, -0.223945F ),
	NORM(  0.649009F,  0.760747F, -0.007143F ),
	NORM(  0.987270F,  0.135305F, -0.083612F ),
	NORM(  0.993283F,  0.093403F, -0.068294F ),
	NORM(  0.988486F,  0.136423F, -0.065458F ),
	NORM(  0.988318F,  0.136728F, -0.067327F ),
	NORM( -0.416265F,  0.255291F,  0.872668F ),
	NORM(  0.990393F,  0.137153F, -0.017609F ),
	NORM(  0.704330F,  0.057069F,  0.707575F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.026788F, -0.004733F,  0.999630F ),
	NORM( -0.280857F,  0.943338F, -0.176728F ),
	NORM(  0.280857F,  0.943338F, -0.176728F ),
	NORM( -0.280690F,  0.914042F,  0.292813F ),
	NORM(  0.026708F,  0.861996F,  0.506210F ),
	NORM(  0.008590F,  0.823300F,  0.567541F ),
	NORM( -0.199492F,  0.837349F, -0.508970F ),
	NORM(  0.722818F,  0.681005F, -0.117327F ),
	NORM(  0.376975F, -0.926224F, -0.000001F ),
	NORM(  0.991693F,  0.055134F,  0.116216F ),
	NORM(  0.989531F,  0.131728F,  0.058963F ),
	NORM(  0.922039F,  0.360625F,  0.140690F ),
	NORM(  0.982034F,  0.174978F,  0.070649F ),
	NORM(  0.901046F,  0.111743F,  0.419082F ),
	NORM(  0.991093F,  0.133099F,  0.004281F ),
	NORM(  0.931947F,  0.348657F,  0.099566F ),
	NORM(  0.929377F,  0.355801F,  0.098304F ),
	NORM(  0.992017F,  0.125568F,  0.011579F ),
	NORM(  0.983380F, -0.138332F,  0.117596F ),
	NORM(  0.995141F,  0.097195F,  0.015758F ),
	NORM(  0.983636F, -0.136169F,  0.117974F ),
	NORM(  0.993191F,  0.104994F,  0.050479F ),
	NORM(  0.845362F,  0.000000F, -0.534194F ),
	NORM(  0.766969F,  0.311010F, -0.561277F ),
	NORM(  0.822871F,  0.393233F, -0.410185F ),
	NORM(  0.960713F,  0.000000F, -0.277543F ),
	NORM(  0.547739F, -0.003590F, -0.836642F ),
	NORM(  0.469941F,  0.414503F, -0.779322F ),
	NORM(  0.185128F,  0.426173F, -0.885497F ),
	NORM(  0.324527F,  0.167196F, -0.930982F ),
	NORM(  0.133762F,  0.671868F, -0.728492F ),
	NORM( -0.228345F,  0.922946F, -0.309885F ),
	NORM( -0.217607F,  0.927897F, -0.302745F ),
	NORM(  0.671764F, -0.228811F,  0.704542F ),
	NORM( -0.124833F,  0.901726F, -0.413892F ),
	NORM(  0.989623F,  0.135871F,  0.046747F ),
	NORM(  0.868405F,  0.494536F,  0.036142F ),
	NORM(  0.672582F,  0.327790F,  0.663466F ),
	NORM(  0.737396F,  0.055722F,  0.673158F ),
	NORM(  0.919908F,  0.243762F,  0.307163F ),
	NORM(  0.994876F, -0.100529F, -0.010727F ),
	NORM(  0.994983F, -0.100045F,  0.000000F ),
	NORM(  0.997033F, -0.076982F,  0.000047F ),
	NORM( -0.024628F,  0.438138F,  0.898570F ),
	NORM(  0.068469F,  0.452311F,  0.889228F ),
	NORM(  0.056074F, -0.701043F,  0.710911F ),
	NORM( -0.077248F, -0.622916F,  0.778465F ),
	NORM(  0.587424F,  0.808412F, -0.037444F ),
	NORM(  0.583548F,  0.810561F, -0.049630F ),
	NORM(  0.408782F,  0.909901F, -0.070548F ),
	NORM(  0.412770F,  0.910703F, -0.015496F ),
	NORM(  0.751815F,  0.656298F, -0.063615F ),
	NORM(  0.380425F,  0.919174F, -0.101956F ),
	NORM(  0.736103F,  0.668339F, -0.107120F ),
	NORM(  0.746400F,  0.665361F, -0.013452F ),
	NORM(  0.994501F, -0.103177F, -0.017966F ),
	NORM(  0.994386F, -0.101854F, -0.028663F ),
	NORM(  0.740377F,  0.671853F, -0.021362F ),
	NORM(  0.674167F,  0.732170F,  0.097088F ),
	NORM( -0.493138F,  0.743649F,  0.451444F ),
	NORM( -0.726823F,  0.684178F, -0.060246F ),
	NORM(  0.711096F,  0.681893F,  0.171360F ),
	NORM(  0.523138F,  0.851707F, -0.030350F ),
	NORM(  0.052206F,  0.995518F, -0.078862F ),
	NORM(  0.343005F,  0.932117F, -0.116214F ),
	NORM(  0.938499F,  0.334359F,  0.086159F ),
	NORM(  0.990363F, -0.090666F,  0.104698F ),
	NORM(  0.550612F, -0.569463F,  0.610360F ),
	NORM(  0.715241F, -0.681272F,  0.155882F ),
	NORM(  0.992685F, -0.094279F,  0.075420F ),
	NORM(  0.009539F,  0.818797F,  0.574004F ),
	NORM(  0.994928F, -0.100566F,  0.001973F ),
	NORM(  0.994617F, -0.103618F,  0.000704F ),
	NORM( -0.011918F,  0.934556F, -0.355615F ),
	NORM(  0.459699F,  0.056566F,  0.886272F ),
	NORM(  0.205548F, -0.411242F,  0.888048F ),
	NORM(  0.039075F, -0.973404F,  0.225740F ),
	NORM( -0.873702F,  0.486462F,  0.000000F ),
	NORM(  0.758414F,  0.360265F, -0.543155F ),
	NORM(  0.443285F,  0.895956F,  0.027591F ),
	NORM( -0.976717F, -0.214533F,  0.000000F ),
	NORM(  0.930405F,  0.366242F, -0.014626F ),
	NORM(  0.141744F,  0.488595F, -0.860920F ),
	NORM(  0.195121F, -0.003437F, -0.980773F ),
	NORM(  0.982064F,  0.042999F, -0.183578F ),
	NORM(  0.834681F,  0.528817F, -0.153819F ),
	NORM(  0.934268F,  0.282883F, -0.217072F ),
	NORM(  0.766819F, -0.605740F, -0.212292F ),
	NORM(  0.053871F,  0.950414F, -0.306285F ),
	NORM( -0.259643F, -0.965705F, -0.000002F ),
	NORM( -0.109473F,  0.810877F,  0.574886F ),
	NORM( -0.344286F,  0.778370F,  0.524982F ),
	NORM( -0.313643F,  0.815923F,  0.485693F ),
	NORM(  0.306460F,  0.929122F,  0.206918F ),
	NORM(  0.081628F,  0.992125F,  0.095001F ),
	NORM(  0.252018F,  0.965453F,  0.066243F ),
	NORM(  0.139941F, -0.543366F, -0.827750F ),
	NORM(  0.864240F,  0.047150F, -0.500866F ),
	NORM(  0.967355F,  0.014173F, -0.253027F ),
	NORM(  0.243448F,  0.968722F,  0.048061F ),
	NORM(  0.246993F,  0.968292F, -0.037480F ),
	NORM(  0.403252F,  0.861854F, -0.307563F ),
	NORM(  0.551350F,  0.823808F,  0.131734F ),
	NORM(  0.936063F,  0.160305F, -0.313191F ),
	NORM( -0.000049F,  0.973261F,  0.229703F ),
	NORM(  0.377585F,  0.925975F,  0.000000F ),
	NORM(  0.804976F,  0.593226F, -0.009816F ),
	NORM(  0.851307F, -0.523917F,  0.028061F ),
	NORM(  0.998194F,  0.001442F, -0.060063F ),
	NORM(  0.998738F,  0.026300F, -0.042786F ),
	NORM(  0.982663F,  0.184864F, -0.014093F ),
	NORM(  0.723257F,  0.070863F,  0.686934F ),
	NORM(  0.755822F, -0.002410F,  0.654773F ),
	NORM( -0.664364F,  0.718315F,  0.206505F ),
	NORM(  0.999051F,  0.035160F,  0.025693F ),
	NORM(  0.658702F,  0.316888F, -0.682417F ),
	NORM( -0.687785F,  0.725914F, -0.001034F ),
	NORM(  0.050191F,  0.986546F,  0.155589F ),
	NORM( -0.194606F,  0.960073F,  0.200968F ),
	NORM(  0.942180F,  0.325792F, -0.078464F ),
	NORM(  0.933955F,  0.338121F, -0.115771F ),
	NORM(  0.725472F,  0.688251F, -0.000981F ),
	NORM( -0.688546F,  0.725190F, -0.001948F ),
	NORM(  0.063420F,  0.980006F,  0.188591F ),
	NORM( -0.190906F,  0.957131F,  0.217844F ),
	NORM(  0.549642F, -0.012158F,  0.835312F ),
	NORM( -0.199129F,  0.962833F,  0.182483F ),
	NORM( -0.687616F,  0.726073F, -0.001549F ),
	NORM(  0.725906F,  0.687792F, -0.001847F ),
	NORM(  0.291612F,  0.935309F,  0.200395F ),
	NORM(  0.051517F,  0.985810F,  0.159766F ),
	NORM(  0.725140F,  0.688599F, -0.001469F ),
	NORM(  0.973258F,  0.220674F,  0.063814F ),
	NORM(  0.863302F,  0.135969F, -0.486026F ),
	NORM(  0.864241F, -0.502499F, -0.024122F ),
	NORM(  0.746786F,  0.650017F, -0.140671F ),
	NORM(  0.368862F,  0.927578F, -0.059500F ),
	NORM(  0.050201F,  0.987013F,  0.152597F ),
	NORM( -0.708844F,  0.705344F,  0.005464F ),
	NORM( -0.208618F,  0.968040F,  0.139199F ),
	NORM(  0.723846F,  0.689955F, -0.002903F ),
	NORM( -0.689744F,  0.724047F, -0.003047F ),
	NORM(  0.052194F,  0.989282F,  0.136367F ),
	NORM( -0.201337F,  0.963208F,  0.178025F ),
	NORM(  0.062476F, -0.016955F,  0.997902F ),
	NORM( -0.677752F, -0.706855F,  0.202506F ),
	NORM(  0.722861F,  0.690989F, -0.002609F ),
	NORM( -0.690200F,  0.723613F, -0.002733F ),
	NORM(  0.050166F,  0.989515F,  0.135436F ),
	NORM( -0.210068F,  0.949609F,  0.232625F ),
	NORM(  0.649752F,  0.756649F, -0.072825F ),
	NORM( -0.489166F,  0.832400F,  0.260437F ),
	NORM(  0.353480F,  0.935324F, -0.014868F ),
	NORM( -0.490531F,  0.768379F,  0.411064F ),
	NORM(  0.634845F,  0.772058F,  0.029973F ),
	NORM(  0.647320F,  0.761652F, -0.029376F ),
	NORM(  0.501150F,  0.412673F, -0.760624F ),
	NORM(  0.065724F, -0.004784F,  0.997826F ),
	NORM( -0.691408F,  0.722278F, -0.016383F ),
	NORM( -0.252844F,  0.953990F, -0.161162F ),
	NORM(  0.097590F,  0.980724F, -0.169284F ),
	NORM(  0.090441F,  0.995586F, -0.025060F ),
	NORM( -0.051582F,  0.995433F, -0.080332F ),
	NORM(  0.898485F,  0.433840F, -0.067134F ),
	NORM(  0.996288F,  0.072981F,  0.045662F ),
	NORM(  0.578824F,  0.278485F,  0.766426F ),
	NORM(  0.405433F,  0.480523F,  0.777638F ),
	NORM(  0.286131F,  0.409830F, -0.866123F ),
	NORM(  0.894193F,  0.441434F, -0.074532F ),
	NORM(  0.596378F,  0.802635F, -0.010484F ),
	NORM( -0.975280F,  0.199190F, -0.095664F ),
	NORM(  0.652842F,  0.745540F, -0.134042F ),
	NORM(  0.979475F, -0.102147F,  0.173764F ),
	NORM(  0.294202F,  0.939541F,  0.175235F ),
	NORM(  0.269112F,  0.949427F,  0.161762F ),
	NORM(  0.237916F,  0.959204F, -0.152717F ),
	NORM(  0.230474F,  0.926384F, -0.297817F ),
	NORM(  0.423640F,  0.864348F, -0.270983F ),
	NORM(  0.991465F, -0.002327F, -0.130356F ),
	NORM(  0.996693F,  0.025497F,  0.077150F ),
	NORM(  0.327027F,  0.940418F, -0.093095F ),
	NORM(  0.294892F,  0.955183F, -0.025793F ),
	NORM(  0.959614F,  0.281179F, -0.008931F ),
	NORM( -0.661863F,  0.074071F, -0.745956F ),
	NORM( -0.673924F,  0.732825F,  0.093779F ),
	NORM(  0.822616F,  0.338781F, -0.456651F ),
	NORM(  0.649041F,  0.626443F, -0.431641F ),
	NORM(  0.594231F,  0.801755F,  0.063861F ),
	NORM(  0.708720F,  0.122956F,  0.694692F ),
	NORM(  0.628528F,  0.774652F,  0.069758F ),
	NORM( -0.253887F,  0.499584F, -0.828225F ),
	NORM(  0.199210F,  0.100372F, -0.974803F ),
	NORM( -0.982705F, -0.127576F,  0.134220F ),
	NORM(  0.602558F,  0.075750F, -0.794472F ),
	NORM(  0.364091F,  0.691766F, -0.623616F ),
END

MODEL       model_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
Points      point_F40_GTE_sh_null1_1_C_F4E_BODY_3,
Normal      normal_F40_GTE_sh_null1_1_C_F4E_BODY_3,
PointNum    796,
Meshset     meshset_F40_GTE_sh_null1_1_C_F4E_BODY_3,
Materials   matlist_F40_GTE_sh_null1_1_C_F4E_BODY_3,
MeshsetNum  8,
MatNum      8,
Center       0.000000F,  0.587190F, -0.018125F,
Radius       2.446803F,
END

OBJECT      object_F40_GTE_sh_null1_1_C_F4E_BODY_3[]
START
EvalFlags ( 0x00000007 ),
Model       model_F40_GTE_sh_null1_1_C_F4E_BODY_3,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       object_F40_GTE_sh_null1_1_EX_PIPE,
Sibling     object_F40_GTE_sh_null1_1_C_F4E_LAMP_1_2,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool1[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 17 ),
AttrFlags ( 0x9431a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool1[]
START
	Strip(0x0, 6),  3, 0, 5, 4, 2, 1, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool1[]
START
	UV( 0, 255 ),
	UV( 251, 255 ),
	UV( 0, 124 ),
	UV( 251, 126 ),
	UV( 0, 3 ),
	UV( 251, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool1[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool1,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool1[]
START
	VERT(  0.966660F,  0.548248F, -0.872849F ),
	VERT(  0.950130F,  0.683248F, -0.872849F ),
	VERT(  0.939162F,  0.683248F, -0.737849F ),
	VERT(  0.961589F,  0.548248F, -0.737849F ),
	VERT(  0.961300F,  0.617493F, -0.872849F ),
	VERT(  0.953864F,  0.618327F, -0.737849F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool1[]
START
	NORM(  0.995967F,  0.077096F,  0.045901F ),
	NORM(  0.983691F,  0.167109F,  0.066537F ),
	NORM(  0.983691F,  0.167109F,  0.066537F ),
	NORM(  0.995966F,  0.077096F,  0.045901F ),
	NORM(  0.990954F,  0.121866F,  0.056196F ),
	NORM(  0.990845F,  0.122669F,  0.056380F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool1[]
START
Points      point_F40_GTE_sh_null1_1_bool1,
Normal      normal_F40_GTE_sh_null1_1_bool1,
PointNum    6,
Meshset     meshset_F40_GTE_sh_null1_1_bool1,
Materials   matlist_F40_GTE_sh_null1_1_bool1,
MeshsetNum  1,
MatNum      1,
Center       0.952911F,  0.615748F, -0.805349F,
Radius       0.095459F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool1[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool1,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     NULL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 23 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START
	Strip(0x0, 4),  3, 0, 1, 2, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START
	UV( 0, 3 ),
	UV( 175, 3 ),
	UV( 0, 255 ),
	UV( 175, 255 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_COWLLOCK_RL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_RL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START
	VERT( -0.918215F,  0.571209F,  2.176694F ),
	VERT( -0.889911F,  0.465506F,  2.179662F ),
	VERT( -0.918215F,  0.465506F,  2.177192F ),
	VERT( -0.889911F,  0.571209F,  2.179519F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START
	NORM( -0.093120F,  0.001338F,  0.995654F ),
	NORM( -0.093120F,  0.001338F,  0.995654F ),
	NORM( -0.093120F,  0.001338F,  0.995654F ),
	NORM( -0.093120F,  0.001338F,  0.995654F ),
END

MODEL       model_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START
Points      point_F40_GTE_sh_null1_1_COWLLOCK_RL,
Normal      normal_F40_GTE_sh_null1_1_COWLLOCK_RL,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_COWLLOCK_RL,
Materials   matlist_F40_GTE_sh_null1_1_COWLLOCK_RL,
MeshsetNum  1,
MatNum      1,
Center      -0.904063F,  0.518358F,  2.178178F,
Radius       0.052872F,
END

OBJECT      object_F40_GTE_sh_null1_1_COWLLOCK_RL[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_COWLLOCK_RL,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool1,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 23 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START
	Strip(0x0, 4),  3, 1, 2, 0, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START
	UV( 175, 254 ),
	UV( 175, 3 ),
	UV( 0, 255 ),
	UV( 0, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_COWLLOCK_FL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_FL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START
	VERT( -0.965033F,  0.527281F, -0.811096F ),
	VERT( -0.963991F,  0.527281F, -0.782792F ),
	VERT( -0.969000F,  0.423608F, -0.811096F ),
	VERT( -0.969000F,  0.423646F, -0.782792F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START
	NORM( -0.999064F,  0.043259F, -0.000054F ),
	NORM( -0.999064F,  0.043259F, -0.000054F ),
	NORM( -0.999064F,  0.043259F, -0.000054F ),
	NORM( -0.999064F,  0.043259F, -0.000054F ),
END

MODEL       model_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START
Points      point_F40_GTE_sh_null1_1_COWLLOCK_FL,
Normal      normal_F40_GTE_sh_null1_1_COWLLOCK_FL,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_COWLLOCK_FL,
Materials   matlist_F40_GTE_sh_null1_1_COWLLOCK_FL,
MeshsetNum  1,
MatNum      1,
Center      -0.966496F,  0.475444F, -0.796944F,
Radius       0.053734F,
END

OBJECT      object_F40_GTE_sh_null1_1_COWLLOCK_FL[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_COWLLOCK_FL,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_COWLLOCK_RL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool10_1[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 26 ),
AttrFlags ( 0x9639a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool10_1[]
START
	Strip(0x0, 4),  0, 1, 2, 3, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool10_1[]
START
	UV( 253, 255 ),
	UV( 253, 7 ),
	UV( 0, 255 ),
	UV( 0, 7 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool10_1[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool10_1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool10_1,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool10_1[]
START
	VERT(  0.823629F,  0.429962F,  2.196306F ),
	VERT(  0.823629F,  0.489962F,  2.196306F ),
	VERT(  0.512529F,  0.429962F,  2.222429F ),
	VERT(  0.512529F,  0.489962F,  2.222429F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool10_1[]
START
	NORM(  0.083675F,  0.000000F,  0.996493F ),
	NORM(  0.083675F,  0.000000F,  0.996493F ),
	NORM(  0.083675F,  0.000000F,  0.996493F ),
	NORM(  0.083675F,  0.000000F,  0.996493F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool10_1[]
START
Points      point_F40_GTE_sh_null1_1_bool10_1,
Normal      normal_F40_GTE_sh_null1_1_bool10_1,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_bool10_1,
Materials   matlist_F40_GTE_sh_null1_1_bool10_1,
MeshsetNum  1,
MatNum      1,
Center       0.668079F,  0.459962F,  2.209367F,
Radius       0.156097F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool10_1[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool10_1,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_COWLLOCK_FL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool11_1[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 26 ),
AttrFlags ( 0x9639a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool11_1[]
START
	Strip(0x0, 4),  3, 2, 0, 1, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool11_1[]
START
	UV( 253, 255 ),
	UV( 253, 7 ),
	UV( 0, 255 ),
	UV( 0, 7 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool11_1[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool11_1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool11_1,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool11_1[]
START
	VERT( -0.823629F,  0.429962F,  2.196306F ),
	VERT( -0.823629F,  0.489962F,  2.196306F ),
	VERT( -0.512529F,  0.489962F,  2.222429F ),
	VERT( -0.512529F,  0.429962F,  2.222429F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool11_1[]
START
	NORM( -0.083675F,  0.000000F,  0.996493F ),
	NORM( -0.083675F,  0.000000F,  0.996493F ),
	NORM( -0.083675F,  0.000000F,  0.996493F ),
	NORM( -0.083675F,  0.000000F,  0.996493F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool11_1[]
START
Points      point_F40_GTE_sh_null1_1_bool11_1,
Normal      normal_F40_GTE_sh_null1_1_bool11_1,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_bool11_1,
Materials   matlist_F40_GTE_sh_null1_1_bool11_1,
MeshsetNum  1,
MatNum      1,
Center      -0.668079F,  0.459962F,  2.209367F,
Radius       0.156097F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool11_1[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool11_1,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool10_1,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool12[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 25 ),
AttrFlags ( 0x9639a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool12[]
START
	Strip(0x0, 4),  2, 3, 1, 0, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool12[]
START
	UV( 0, 3 ),
	UV( 0, 255 ),
	UV( 251, 3 ),
	UV( 251, 255 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool12[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool12,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool12,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool12[]
START
	VERT( -0.319835F,  0.583792F,  2.150728F ),
	VERT( -0.319835F,  0.716741F,  2.150728F ),
	VERT( -0.416666F,  0.716741F,  2.148055F ),
	VERT( -0.416666F,  0.583792F,  2.148055F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool12[]
START
	NORM( -0.027603F,  0.000000F,  0.999619F ),
	NORM( -0.027603F,  0.000000F,  0.999619F ),
	NORM( -0.027603F,  0.000000F,  0.999619F ),
	NORM( -0.027603F,  0.000000F,  0.999619F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool12[]
START
Points      point_F40_GTE_sh_null1_1_bool12,
Normal      normal_F40_GTE_sh_null1_1_bool12,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_bool12,
Materials   matlist_F40_GTE_sh_null1_1_bool12,
MeshsetNum  1,
MatNum      1,
Center      -0.368250F,  0.650266F,  2.149392F,
Radius       0.066488F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool12[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool12,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool11_1,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_FER_LOGO[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 24 ),
AttrFlags ( 0x9439a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_FER_LOGO[]
START
	Strip(0x0, 4),  1, 0, 3, 2, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_FER_LOGO[]
START
	UV( 0, 7 ),
	UV( 0, 255 ),
	UV( 253, 7 ),
	UV( 253, 255 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_FER_LOGO[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_FER_LOGO,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_FER_LOGO,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_FER_LOGO[]
START
	VERT( -0.125000F,  0.763867F,  2.219000F ),
	VERT( -0.125000F,  0.811405F,  2.219000F ),
	VERT(  0.125000F,  0.763867F,  2.219000F ),
	VERT(  0.125000F,  0.811405F,  2.219000F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_FER_LOGO[]
START
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_FER_LOGO[]
START
Points      point_F40_GTE_sh_null1_1_FER_LOGO,
Normal      normal_F40_GTE_sh_null1_1_FER_LOGO,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_FER_LOGO,
Materials   matlist_F40_GTE_sh_null1_1_FER_LOGO,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.787636F,  2.219000F,
Radius       0.125000F,
END

OBJECT      object_F40_GTE_sh_null1_1_FER_LOGO[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_FER_LOGO,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool12,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 23 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START
	Strip(0x0, 4),  3, 0, 2, 1, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START
	UV( 175, 255 ),
	UV( 175, 3 ),
	UV( 0, 254 ),
	UV( 0, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_COWLLOCK_FR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_FR,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START
	VERT(  0.965033F,  0.527281F, -0.811096F ),
	VERT(  0.963991F,  0.527281F, -0.782792F ),
	VERT(  0.969000F,  0.423646F, -0.782792F ),
	VERT(  0.969000F,  0.423608F, -0.811096F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START
	NORM(  0.999064F,  0.043259F, -0.000054F ),
	NORM(  0.999064F,  0.043259F, -0.000054F ),
	NORM(  0.999064F,  0.043259F, -0.000054F ),
	NORM(  0.999064F,  0.043259F, -0.000054F ),
END

MODEL       model_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START
Points      point_F40_GTE_sh_null1_1_COWLLOCK_FR,
Normal      normal_F40_GTE_sh_null1_1_COWLLOCK_FR,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_COWLLOCK_FR,
Materials   matlist_F40_GTE_sh_null1_1_COWLLOCK_FR,
MeshsetNum  1,
MatNum      1,
Center       0.966496F,  0.475444F, -0.796944F,
Radius       0.053734F,
END

OBJECT      object_F40_GTE_sh_null1_1_COWLLOCK_FR[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_COWLLOCK_FR,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_FER_LOGO,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 23 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START
	Strip(0x0, 4),  1, 2, 3, 0, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START
	UV( 0, 255 ),
	UV( 175, 255 ),
	UV( 0, 3 ),
	UV( 175, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_COWLLOCK_RR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_COWLLOCK_RR,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START
	VERT(  0.918215F,  0.571209F,  2.176694F ),
	VERT(  0.889911F,  0.465506F,  2.179662F ),
	VERT(  0.918215F,  0.465506F,  2.177192F ),
	VERT(  0.889911F,  0.571209F,  2.179519F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START
	NORM(  0.093120F,  0.001338F,  0.995654F ),
	NORM(  0.093120F,  0.001338F,  0.995654F ),
	NORM(  0.093120F,  0.001338F,  0.995654F ),
	NORM(  0.093120F,  0.001338F,  0.995654F ),
END

MODEL       model_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START
Points      point_F40_GTE_sh_null1_1_COWLLOCK_RR,
Normal      normal_F40_GTE_sh_null1_1_COWLLOCK_RR,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_COWLLOCK_RR,
Materials   matlist_F40_GTE_sh_null1_1_COWLLOCK_RR,
MeshsetNum  1,
MatNum      1,
Center       0.904063F,  0.518358F,  2.178178F,
Radius       0.052872F,
END

OBJECT      object_F40_GTE_sh_null1_1_COWLLOCK_RR[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_COWLLOCK_RR,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_COWLLOCK_FR,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START

MATSTART
Diffuse   ( 255, 0, 0, 0 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 22 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START
	Strip(0x0, 4),  2, 3, 7, 6, 
	Strip(0x0, 4),  5, 4, 0, 1, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START
	Strip(0x0, 4),  7, 6, 5, 4, 
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START
	UV( 11, 58 ),
	UV( 11, 198 ),
	UV( 242, 58 ),
	UV( 242, 198 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     2,
Meshes      pgS_0_F40_GTE_sh_null1_1_F40_REAR_GRIL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     1,
Meshes      pgS_1_F40_GTE_sh_null1_1_F40_REAR_GRIL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_F40_REAR_GRIL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START
	VERT(  0.853847F,  0.779139F,  2.109180F ),
	VERT(  0.888949F,  0.516375F,  2.112731F ),
	VERT( -0.853847F,  0.779139F,  2.109180F ),
	VERT( -0.888949F,  0.516375F,  2.112731F ),
	VERT(  0.446100F,  0.516400F,  2.144585F ),
	VERT(  0.446100F,  0.779164F,  2.144585F ),
	VERT( -0.446100F,  0.516400F,  2.144585F ),
	VERT( -0.446100F,  0.779164F,  2.144585F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START
	NORM(  0.086500F,  0.012509F,  0.996173F ),
	NORM(  0.086500F,  0.012509F,  0.996173F ),
	NORM( -0.086500F,  0.012509F,  0.996173F ),
	NORM( -0.086500F,  0.012509F,  0.996173F ),
	NORM(  0.043292F,  0.006261F,  0.999043F ),
	NORM(  0.043291F,  0.006261F,  0.999043F ),
	NORM( -0.043292F,  0.006261F,  0.999043F ),
	NORM( -0.043291F,  0.006261F,  0.999043F ),
END

MODEL       model_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START
Points      point_F40_GTE_sh_null1_1_F40_REAR_GRIL,
Normal      normal_F40_GTE_sh_null1_1_F40_REAR_GRIL,
PointNum    8,
Meshset     meshset_F40_GTE_sh_null1_1_F40_REAR_GRIL,
Materials   matlist_F40_GTE_sh_null1_1_F40_REAR_GRIL,
MeshsetNum  2,
MatNum      2,
Center       0.000000F,  0.647769F,  2.126883F,
Radius       0.889126F,
END

OBJECT      object_F40_GTE_sh_null1_1_F40_REAR_GRIL[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_F40_REAR_GRIL,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_COWLLOCK_RR,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool20[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 20 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool20[]
START
	Strip(0x8000, 7),  0, 3, 1, 2, 5, 8, 7, 
	Strip(0x0, 3),  1, 4, 5, 
	Strip(0x0, 4),  2, 8, 3, 6, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool20[]
START
	UV( 251, 35 ),
	UV( 251, 74 ),
	UV( 112, 35 ),
	UV( 112, 74 ),
	UV( 0, 74 ),
	UV( 107, 223 ),
	UV( 0, 223 ),
	UV( 112, 35 ),
	UV( 0, 35 ),
	UV( 0, 74 ),
	UV( 112, 74 ),
	UV( 107, 223 ),
	UV( 251, 74 ),
	UV( 251, 223 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool20[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool20,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool20,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool20[]
START
	VERT( -0.904147F,  0.688516F, -1.164535F ),
	VERT( -0.699662F,  0.716383F, -1.164535F ),
	VERT( -0.699662F,  0.710351F, -1.240308F ),
	VERT( -0.904147F,  0.682362F, -1.240308F ),
	VERT( -0.534147F,  0.726846F, -1.164535F ),
	VERT( -0.534147F,  0.720814F, -1.240308F ),
	VERT( -0.904147F,  0.602132F, -1.534536F ),
	VERT( -0.534147F,  0.642355F, -1.534536F ),
	VERT( -0.693011F,  0.631892F, -1.534536F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool20[]
START
	NORM( -0.134902F,  0.987734F, -0.078633F ),
	NORM( -0.098781F,  0.991971F, -0.078970F ),
	NORM( -0.098265F,  0.980692F, -0.169079F ),
	NORM( -0.133468F,  0.976167F, -0.171125F ),
	NORM( -0.062891F,  0.994873F, -0.079201F ),
	NORM( -0.062811F,  0.983739F, -0.168263F ),
	NORM( -0.130966F,  0.956820F, -0.259507F ),
	NORM( -0.062213F,  0.964364F, -0.257160F ),
	NORM( -0.096750F,  0.961156F, -0.258492F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool20[]
START
Points      point_F40_GTE_sh_null1_1_bool20,
Normal      normal_F40_GTE_sh_null1_1_bool20,
PointNum    9,
Meshset     meshset_F40_GTE_sh_null1_1_bool20,
Materials   matlist_F40_GTE_sh_null1_1_bool20,
MeshsetNum  1,
MatNum      1,
Center      -0.719147F,  0.664489F, -1.349535F,
Radius       0.261630F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool20[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool20,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_F40_REAR_GRIL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool18[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 20 ),
AttrFlags ( 0x9429a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 21 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool18[]
START
	Strip(0x8000, 10),  15, 5, 2, 7, 10, 9, 13, 0, 14, 6, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_bool18[]
START
	Strip(0x0, 4),  12, 8, 1, 3, 
	Strip(0x0, 4),  14, 11, 6, 4, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool18[]
START
	UV( 251, 218 ),
	UV( 0, 218 ),
	UV( 251, 128 ),
	UV( 0, 129 ),
	UV( 251, 84 ),
	UV( 0, 86 ),
	UV( 251, 42 ),
	UV( 0, 40 ),
	UV( 251, 37 ),
	UV( 0, 33 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_bool18[]
START
	UV( 253, 255 ),
	UV( 253, 8 ),
	UV( 0, 255 ),
	UV( 0, 8 ),
	UV( 253, 284 ),
	UV( 253, 7 ),
	UV( 0, 283 ),
	UV( 0, 7 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool18[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool18,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool18,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_bool18,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_bool18,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool18[]
START
	VERT(  0.864949F,  0.675489F, -0.213753F ),
	VERT(  0.928828F,  0.303359F, -0.213753F ),
	VERT(  0.898986F,  0.550425F, -0.633753F ),
	VERT(  0.928828F,  0.403741F, -0.213753F ),
	VERT(  0.758096F,  0.706514F, -0.213753F ),
	VERT(  0.926050F,  0.423741F, -0.213753F ),
	VERT(  0.853417F,  0.685376F, -0.213753F ),
	VERT(  0.903973F,  0.549811F, -0.213753F ),
	VERT(  0.919168F,  0.403741F, -0.633753F ),
	VERT(  0.887409F,  0.609567F, -0.213753F ),
	VERT(  0.884988F,  0.612672F, -0.633753F ),
	VERT(  0.758096F,  0.703699F, -0.633753F ),
	VERT(  0.919161F,  0.303359F, -0.633753F ),
	VERT(  0.863892F,  0.671941F, -0.633753F ),
	VERT(  0.853589F,  0.679421F, -0.633753F ),
	VERT(  0.916415F,  0.423742F, -0.633753F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool18[]
START
	NORM(  0.815121F,  0.579261F, -0.005835F ),
	NORM(  0.999735F, -0.000033F, -0.023010F ),
	NORM(  0.979910F,  0.199001F, -0.013219F ),
	NORM(  0.999735F, -0.000033F, -0.023010F ),
	NORM(  0.231527F,  0.972732F, -0.013697F ),
	NORM(  0.987750F,  0.154391F, -0.022659F ),
	NORM(  0.436633F,  0.899570F, -0.011218F ),
	NORM(  0.979953F,  0.198787F, -0.013264F ),
	NORM(  0.999735F, -0.000033F, -0.023010F ),
	NORM(  0.958271F,  0.285840F, -0.003409F ),
	NORM(  0.958129F,  0.286316F, -0.003404F ),
	NORM(  0.231527F,  0.972732F, -0.013697F ),
	NORM(  0.999735F, -0.000033F, -0.023010F ),
	NORM(  0.816232F,  0.577695F, -0.005817F ),
	NORM(  0.438263F,  0.898777F, -0.011195F ),
	NORM(  0.987750F,  0.154391F, -0.022659F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool18[]
START
Points      point_F40_GTE_sh_null1_1_bool18,
Normal      normal_F40_GTE_sh_null1_1_bool18,
PointNum    16,
Meshset     meshset_F40_GTE_sh_null1_1_bool18,
Materials   matlist_F40_GTE_sh_null1_1_bool18,
MeshsetNum  2,
MatNum      2,
Center       0.843462F,  0.504937F, -0.423753F,
Radius       0.291091F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool18[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool18,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool20,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool19[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 20 ),
AttrFlags ( 0x9429a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 21 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool19[]
START
	Strip(0x8000, 10),  14, 6, 13, 0, 10, 9, 2, 7, 15, 5, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_bool19[]
START
	Strip(0x0, 4),  1, 3, 8, 12, 
	Strip(0x0, 4),  6, 4, 14, 11, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool19[]
START
	UV( 0, 37 ),
	UV( 251, 33 ),
	UV( 0, 42 ),
	UV( 251, 40 ),
	UV( 0, 84 ),
	UV( 251, 86 ),
	UV( 0, 128 ),
	UV( 251, 129 ),
	UV( 0, 218 ),
	UV( 251, 218 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_bool19[]
START
	UV( 253, 255 ),
	UV( 253, 8 ),
	UV( 0, 255 ),
	UV( 0, 8 ),
	UV( 253, 259 ),
	UV( 253, 7 ),
	UV( 0, 259 ),
	UV( 0, 7 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool19[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool19,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool19,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_bool19,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_bool19,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool19[]
START
	VERT( -0.864949F,  0.675489F, -0.213753F ),
	VERT( -0.928828F,  0.303359F, -0.213753F ),
	VERT( -0.898986F,  0.550425F, -0.633753F ),
	VERT( -0.928828F,  0.403741F, -0.213753F ),
	VERT( -0.758096F,  0.706514F, -0.213753F ),
	VERT( -0.926050F,  0.423741F, -0.213753F ),
	VERT( -0.853417F,  0.685376F, -0.213753F ),
	VERT( -0.903972F,  0.549811F, -0.213753F ),
	VERT( -0.919161F,  0.303359F, -0.633753F ),
	VERT( -0.887409F,  0.609567F, -0.213753F ),
	VERT( -0.884988F,  0.612672F, -0.633753F ),
	VERT( -0.758096F,  0.703699F, -0.633753F ),
	VERT( -0.919168F,  0.403741F, -0.633753F ),
	VERT( -0.863892F,  0.671941F, -0.633753F ),
	VERT( -0.853589F,  0.679421F, -0.633753F ),
	VERT( -0.916415F,  0.423742F, -0.633753F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool19[]
START
	NORM( -0.815122F,  0.579260F, -0.005835F ),
	NORM( -0.999735F, -0.000033F, -0.023010F ),
	NORM( -0.979856F,  0.198989F, -0.016914F ),
	NORM( -0.999735F, -0.000033F, -0.023010F ),
	NORM( -0.231527F,  0.972732F, -0.013697F ),
	NORM( -0.987750F,  0.154391F, -0.022659F ),
	NORM( -0.436634F,  0.899569F, -0.011218F ),
	NORM( -0.979899F,  0.198775F, -0.016942F ),
	NORM( -0.999735F, -0.000033F, -0.023010F ),
	NORM( -0.958252F,  0.285835F, -0.007117F ),
	NORM( -0.958111F,  0.286311F, -0.007072F ),
	NORM( -0.231527F,  0.972732F, -0.013697F ),
	NORM( -0.999735F, -0.000033F, -0.023010F ),
	NORM( -0.816233F,  0.577693F, -0.005817F ),
	NORM( -0.438265F,  0.898776F, -0.011195F ),
	NORM( -0.987750F,  0.154391F, -0.022659F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool19[]
START
Points      point_F40_GTE_sh_null1_1_bool19,
Normal      normal_F40_GTE_sh_null1_1_bool19,
PointNum    16,
Meshset     meshset_F40_GTE_sh_null1_1_bool19,
Materials   matlist_F40_GTE_sh_null1_1_bool19,
MeshsetNum  2,
MatNum      2,
Center      -0.843462F,  0.504937F, -0.423753F,
Radius       0.291091F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool19[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool19,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool18,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool13[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 19 ),
AttrFlags ( 0x9439a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool13[]
START
	Strip(0x0, 4),  2, 3, 1, 0, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool13[]
START
	UV( 251, 3 ),
	UV( 0, 3 ),
	UV( 251, 255 ),
	UV( 0, 255 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool13[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool13,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool13,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool13[]
START
	VERT(  0.315101F,  0.583766F,  2.150859F ),
	VERT(  0.448101F,  0.583766F,  2.147187F ),
	VERT(  0.448101F,  0.716766F,  2.147187F ),
	VERT(  0.315101F,  0.716766F,  2.150859F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool13[]
START
	NORM(  0.027601F,  0.000000F,  0.999619F ),
	NORM(  0.027601F,  0.000000F,  0.999619F ),
	NORM(  0.027601F,  0.000000F,  0.999619F ),
	NORM(  0.027601F,  0.000000F,  0.999619F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool13[]
START
Points      point_F40_GTE_sh_null1_1_bool13,
Normal      normal_F40_GTE_sh_null1_1_bool13,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_bool13,
Materials   matlist_F40_GTE_sh_null1_1_bool13,
MeshsetNum  1,
MatNum      1,
Center       0.381601F,  0.650266F,  2.149023F,
Radius       0.066525F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool13[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool13,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool19,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool3[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 18 ),
AttrFlags ( 0x9439a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool3[]
START
	Strip(0x0, 4),  2, 3, 1, 0, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool3[]
START
	UV( 0, 3 ),
	UV( 0, 255 ),
	UV( 251, 3 ),
	UV( 251, 255 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool3[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool3,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool3,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool3[]
START
	VERT( -0.045000F,  0.374758F, -2.147987F ),
	VERT( -0.045000F,  0.414504F, -2.066284F ),
	VERT(  0.045000F,  0.414504F, -2.066284F ),
	VERT(  0.045000F,  0.374758F, -2.147987F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool3[]
START
	NORM(  0.000000F,  0.899241F, -0.437454F ),
	NORM(  0.000000F,  0.899241F, -0.437454F ),
	NORM(  0.000000F,  0.899241F, -0.437454F ),
	NORM(  0.000000F,  0.899241F, -0.437454F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool3[]
START
Points      point_F40_GTE_sh_null1_1_bool3,
Normal      normal_F40_GTE_sh_null1_1_bool3,
PointNum    4,
Meshset     meshset_F40_GTE_sh_null1_1_bool3,
Materials   matlist_F40_GTE_sh_null1_1_bool3,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.394631F, -2.107136F,
Radius       0.060777F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool3[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool3,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool13,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool2[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 17 ),
AttrFlags ( 0x9439a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool2[]
START
	Strip(0x0, 6),  0, 3, 4, 5, 1, 2, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool2[]
START
	UV( 0, 255 ),
	UV( 251, 255 ),
	UV( 0, 126 ),
	UV( 251, 124 ),
	UV( 0, 3 ),
	UV( 251, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool2[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool2,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool2,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool2[]
START
	VERT( -0.966660F,  0.548248F, -0.872849F ),
	VERT( -0.950130F,  0.683248F, -0.872849F ),
	VERT( -0.939162F,  0.683248F, -0.737849F ),
	VERT( -0.961589F,  0.548248F, -0.737849F ),
	VERT( -0.961300F,  0.617493F, -0.872849F ),
	VERT( -0.953864F,  0.618327F, -0.737849F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool2[]
START
	NORM( -0.995966F,  0.077097F,  0.045901F ),
	NORM( -0.983691F,  0.167108F,  0.066537F ),
	NORM( -0.983691F,  0.167108F,  0.066537F ),
	NORM( -0.995966F,  0.077097F,  0.045901F ),
	NORM( -0.990954F,  0.121866F,  0.056196F ),
	NORM( -0.990845F,  0.122669F,  0.056380F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool2[]
START
Points      point_F40_GTE_sh_null1_1_bool2,
Normal      normal_F40_GTE_sh_null1_1_bool2,
PointNum    6,
Meshset     meshset_F40_GTE_sh_null1_1_bool2,
Materials   matlist_F40_GTE_sh_null1_1_bool2,
MeshsetNum  1,
MatNum      1,
Center      -0.952911F,  0.615748F, -0.805349F,
Radius       0.095459F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool2[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool2,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool3,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool14[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 16 ),
AttrFlags ( 0x9429a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 231, 0 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool14[]
START
	Strip(0x0, 10),  11, 8, 0, 9, 2, 1, 3, 5, 4, 7, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_bool14[]
START
	Strip(0x0, 4),  6, 12, 7, 4, 
	Strip(0x0, 4),  11, 13, 8, 10, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool14[]
START
	UV( 254, 249 ),
	UV( 250, 7 ),
	UV( 187, 254 ),
	UV( 186, 12 ),
	UV( 127, 254 ),
	UV( 127, 12 ),
	UV( 66, 254 ),
	UV( 67, 12 ),
	UV( 0, 249 ),
	UV( 3, 7 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool14[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool14,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool14,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_bool14,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool14[]
START
	VERT( -0.226991F,  0.995373F, -0.359179F ),
	VERT(  0.000000F,  1.057995F, -0.197351F ),
	VERT(  0.000000F,  0.997324F, -0.361290F ),
	VERT(  0.226991F,  0.995373F, -0.359179F ),
	VERT(  0.473820F,  0.972727F, -0.334675F ),
	VERT(  0.221500F,  1.057995F, -0.197351F ),
	VERT(  0.519743F,  1.020843F, -0.156384F ),
	VERT(  0.460752F,  1.039354F, -0.176371F ),
	VERT( -0.460752F,  1.039354F, -0.176371F ),
	VERT( -0.221500F,  1.057995F, -0.197351F ),
	VERT( -0.519743F,  1.020843F, -0.156385F ),
	VERT( -0.473820F,  0.972727F, -0.334675F ),
	VERT(  0.562287F,  0.946138F, -0.305903F ),
	VERT( -0.562287F,  0.946138F, -0.305903F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool14[]
START
	NORM( -0.057811F,  0.930828F, -0.360855F ),
	NORM(  0.000000F,  0.935322F, -0.353798F ),
	NORM(  0.000000F,  0.935322F, -0.353798F ),
	NORM(  0.066222F,  0.930509F, -0.360234F ),
	NORM(  0.250499F,  0.902506F, -0.350334F ),
	NORM(  0.066082F,  0.930524F, -0.360219F ),
	NORM(  0.382158F,  0.864051F, -0.327675F ),
	NORM(  0.257058F,  0.901029F, -0.349382F ),
	NORM( -0.245147F,  0.902855F, -0.353209F ),
	NORM( -0.057691F,  0.930842F, -0.360838F ),
	NORM( -0.374792F,  0.865167F, -0.333192F ),
	NORM( -0.238348F,  0.904340F, -0.354062F ),
	NORM(  0.382159F,  0.864051F, -0.327675F ),
	NORM( -0.374792F,  0.865167F, -0.333192F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool14[]
START
Points      point_F40_GTE_sh_null1_1_bool14,
Normal      normal_F40_GTE_sh_null1_1_bool14,
PointNum    14,
Meshset     meshset_F40_GTE_sh_null1_1_bool14,
Materials   matlist_F40_GTE_sh_null1_1_bool14,
MeshsetNum  2,
MatNum      2,
Center       0.000000F,  1.002066F, -0.258837F,
Radius       0.571544F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool14[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool14,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool2,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool15[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 15 ),
AttrFlags ( 0x9439a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool15[]
START
	Strip(0x0, 8),  7, 5, 6, 2, 4, 3, 1, 0, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool15[]
START
	UV( 253, 255 ),
	UV( 253, 7 ),
	UV( 201, 255 ),
	UV( 201, 7 ),
	UV( 51, 255 ),
	UV( 51, 7 ),
	UV( 0, 255 ),
	UV( 0, 7 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool15[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool15,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool15,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool15[]
START
	VERT(  0.420000F,  0.619211F, -1.573574F ),
	VERT(  0.420000F,  0.522820F, -1.823574F ),
	VERT( -0.250000F,  0.621516F, -1.573574F ),
	VERT(  0.250000F,  0.621516F, -1.573574F ),
	VERT(  0.250000F,  0.527286F, -1.823574F ),
	VERT( -0.420000F,  0.619211F, -1.573574F ),
	VERT( -0.250000F,  0.527286F, -1.823574F ),
	VERT( -0.420000F,  0.523227F, -1.823574F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool15[]
START
	NORM(  0.024541F,  0.934117F, -0.356123F ),
	NORM(  0.024541F,  0.934117F, -0.356123F ),
	NORM( -0.006327F,  0.935178F, -0.354122F ),
	NORM(  0.012253F,  0.935001F, -0.354434F ),
	NORM(  0.012308F,  0.934997F, -0.354442F ),
	NORM( -0.012674F,  0.934576F, -0.355537F ),
	NORM( -0.006354F,  0.935175F, -0.354128F ),
	NORM( -0.012674F,  0.934576F, -0.355537F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool15[]
START
Points      point_F40_GTE_sh_null1_1_bool15,
Normal      normal_F40_GTE_sh_null1_1_bool15,
PointNum    8,
Meshset     meshset_F40_GTE_sh_null1_1_bool15,
Materials   matlist_F40_GTE_sh_null1_1_bool15,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.572168F, -1.698574F,
Radius       0.438207F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool15[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool15,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool14,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool16[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 14 ),
AttrFlags ( 0x9431a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool16[]
START
	Strip(0x8000, 7),  4, 3, 1, 2, 9, 11, 7, 
	Strip(0x0, 7),  4, 0, 1, 5, 9, 10, 8, 
	Strip(0x0, 4),  8, 6, 9, 7, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool16[]
START
	UV( 0, 145 ),
	UV( 0, 39 ),
	UV( 31, 147 ),
	UV( 27, 39 ),
	UV( 216, 168 ),
	UV( 253, 39 ),
	UV( 253, 171 ),
	UV( 0, 145 ),
	UV( 0, 223 ),
	UV( 31, 147 ),
	UV( 86, 223 ),
	UV( 216, 168 ),
	UV( 159, 223 ),
	UV( 205, 223 ),
	UV( 205, 223 ),
	UV( 253, 223 ),
	UV( 216, 168 ),
	UV( 253, 171 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool16[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool16,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool16,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool16[]
START
	VERT(  0.986235F,  0.701013F,  1.557670F ),
	VERT(  0.980100F,  0.740619F,  1.500588F ),
	VERT(  0.954836F,  0.794651F,  1.504718F ),
	VERT(  0.951860F,  0.795727F,  1.553639F ),
	VERT(  0.976146F,  0.742547F,  1.555965F ),
	VERT(  0.996858F,  0.698055F,  1.404009F ),
	VERT(  0.982458F,  0.680897F,  1.110227F ),
	VERT(  0.974738F,  0.708115F,  1.109096F ),
	VERT(  0.989088F,  0.686611F,  1.193659F ),
	VERT(  0.980438F,  0.714659F,  1.173775F ),
	VERT(  0.994628F,  0.691917F,  1.275949F ),
	VERT(  0.947813F,  0.775521F,  1.106196F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool16[]
START
	NORM(  0.968701F,  0.240674F,  0.060784F ),
	NORM(  0.938208F,  0.345061F,  0.026438F ),
	NORM(  0.906103F,  0.422949F,  0.009560F ),
	NORM(  0.906221F,  0.420058F,  0.048107F ),
	NORM(  0.941416F,  0.332793F,  0.054629F ),
	NORM(  0.914957F,  0.403009F, -0.020910F ),
	NORM(  0.968534F,  0.228125F, -0.099506F ),
	NORM(  0.949059F,  0.295644F, -0.108998F ),
	NORM(  0.967656F,  0.236875F, -0.086781F ),
	NORM(  0.940561F,  0.331622F, -0.073298F ),
	NORM(  0.911614F,  0.409348F, -0.037352F ),
	NORM(  0.914799F,  0.397027F, -0.074241F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool16[]
START
Points      point_F40_GTE_sh_null1_1_bool16,
Normal      normal_F40_GTE_sh_null1_1_bool16,
PointNum    12,
Meshset     meshset_F40_GTE_sh_null1_1_bool16,
Materials   matlist_F40_GTE_sh_null1_1_bool16,
MeshsetNum  1,
MatNum      1,
Center       0.972335F,  0.738312F,  1.331933F,
Radius       0.232924F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool16[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool16,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool15,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool17[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 14 ),
AttrFlags ( 0x9439a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool17[]
START
	Strip(0x8000, 7),  8, 9, 10, 1, 5, 4, 0, 
	Strip(0x0, 9),  6, 8, 7, 9, 11, 1, 2, 4, 3, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool17[]
START
	UV( 47, 223 ),
	UV( 36, 168 ),
	UV( 93, 223 ),
	UV( 221, 147 ),
	UV( 166, 223 ),
	UV( 253, 145 ),
	UV( 253, 223 ),
	UV( 0, 223 ),
	UV( 47, 223 ),
	UV( 0, 171 ),
	UV( 36, 168 ),
	UV( 0, 39 ),
	UV( 221, 147 ),
	UV( 225, 39 ),
	UV( 253, 145 ),
	UV( 253, 39 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool17[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     2,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool17,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool17,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool17[]
START
	VERT( -0.986235F,  0.701013F,  1.557670F ),
	VERT( -0.980100F,  0.740619F,  1.500588F ),
	VERT( -0.954836F,  0.794651F,  1.504718F ),
	VERT( -0.951860F,  0.795727F,  1.553639F ),
	VERT( -0.976146F,  0.742547F,  1.555966F ),
	VERT( -0.996858F,  0.698055F,  1.404009F ),
	VERT( -0.982458F,  0.680897F,  1.110227F ),
	VERT( -0.974738F,  0.708115F,  1.109096F ),
	VERT( -0.989087F,  0.686611F,  1.193659F ),
	VERT( -0.980438F,  0.714659F,  1.173775F ),
	VERT( -0.994628F,  0.691917F,  1.275949F ),
	VERT( -0.947813F,  0.775521F,  1.106196F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool17[]
START
	NORM( -0.968701F,  0.240675F,  0.060783F ),
	NORM( -0.938208F,  0.345062F,  0.026437F ),
	NORM( -0.906103F,  0.422949F,  0.009559F ),
	NORM( -0.906221F,  0.420058F,  0.048105F ),
	NORM( -0.941416F,  0.332794F,  0.054627F ),
	NORM( -0.914956F,  0.403011F, -0.020910F ),
	NORM( -0.968534F,  0.228126F, -0.099506F ),
	NORM( -0.949059F,  0.295645F, -0.108998F ),
	NORM( -0.967656F,  0.236875F, -0.086782F ),
	NORM( -0.940561F,  0.331622F, -0.073298F ),
	NORM( -0.911613F,  0.409349F, -0.037352F ),
	NORM( -0.914799F,  0.397027F, -0.074241F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool17[]
START
Points      point_F40_GTE_sh_null1_1_bool17,
Normal      normal_F40_GTE_sh_null1_1_bool17,
PointNum    12,
Meshset     meshset_F40_GTE_sh_null1_1_bool17,
Materials   matlist_F40_GTE_sh_null1_1_bool17,
MeshsetNum  1,
MatNum      1,
Center      -0.972335F,  0.738312F,  1.331933F,
Radius       0.232924F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool17[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool17,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool16,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool8[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 12 ),
AttrFlags ( 0x9669a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 13 ),
AttrFlags ( 0x9621a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool8[]
START
	Strip(0x0, 4),  2, 1, 3, 4, 
	Strip(0x0, 3),  2, 3, 5, 
	Strip(0x0, 3),  1, 0, 4, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_bool8[]
START
	Strip(0x0, 4),  0, 1, 5, 2, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool8[]
START
	UV( 244, 255 ),
	UV( 134, 254 ),
	UV( 204, 67 ),
	UV( 134, 29 ),
	UV( 98, 254 ),
	UV( 134, 254 ),
	UV( 244, 255 ),
	UV( 134, 29 ),
	UV( 79, 7 ),
	UV( 79, 7 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_bool8[]
START
	UV( 253, 42 ),
	UV( 253, 253 ),
	UV( 0, 3 ),
	UV( 0, 255 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool8[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool8,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool8,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     1,
Meshes      pgS_1_F40_GTE_sh_null1_1_bool8,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_bool8,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool8[]
START
	VERT(  0.874747F,  0.514993F, -1.754885F ),
	VERT(  0.874753F,  0.369743F, -1.754877F ),
	VERT(  0.537403F,  0.368643F, -1.799557F ),
	VERT(  0.537397F,  0.368680F, -2.141140F ),
	VERT(  0.792885F,  0.369747F, -2.046486F ),
	VERT(  0.537397F,  0.541429F, -1.799559F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool8[]
START
	NORM( -0.545314F, -0.000045F, -0.838232F ),
	NORM( -0.627074F,  0.557861F, -0.543662F ),
	NORM(  0.609089F,  0.585793F, -0.534656F ),
	NORM(  0.356416F,  0.934328F,  0.000097F ),
	NORM( -0.195306F,  0.979259F,  0.053928F ),
	NORM(  0.659460F, -0.000001F, -0.751740F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool8[]
START
Points      point_F40_GTE_sh_null1_1_bool8,
Normal      normal_F40_GTE_sh_null1_1_bool8,
PointNum    6,
Meshset     meshset_F40_GTE_sh_null1_1_bool8,
Materials   matlist_F40_GTE_sh_null1_1_bool8,
MeshsetNum  2,
MatNum      2,
Center       0.706075F,  0.455036F, -1.948009F,
Radius       0.256422F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool8[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool8,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool17,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bool9[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 12 ),
AttrFlags ( 0x9669a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 13 ),
AttrFlags ( 0x9621a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bool9[]
START
	Strip(0x0, 4),  1, 2, 4, 3, 
	Strip(0x0, 3),  5, 3, 2, 
	Strip(0x0, 3),  4, 0, 1, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_bool9[]
START
	Strip(0x0, 4),  1, 0, 2, 5, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_bool9[]
START
	UV( 204, 195 ),
	UV( 134, 233 ),
	UV( 244, 7 ),
	UV( 134, 7 ),
	UV( 98, 7 ),
	UV( 134, 7 ),
	UV( 244, 7 ),
	UV( 204, 195 ),
	UV( 134, 233 ),
	UV( 79, 254 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_bool9[]
START
	UV( 0, 253 ),
	UV( 0, 42 ),
	UV( 253, 255 ),
	UV( 253, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_bool9[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_bool9,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_bool9,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     1,
Meshes      pgS_1_F40_GTE_sh_null1_1_bool9,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_bool9,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bool9[]
START
	VERT( -0.874747F,  0.514993F, -1.754884F ),
	VERT( -0.874753F,  0.369743F, -1.754876F ),
	VERT( -0.537403F,  0.368643F, -1.799556F ),
	VERT( -0.537397F,  0.368680F, -2.141139F ),
	VERT( -0.792885F,  0.369747F, -2.046484F ),
	VERT( -0.537397F,  0.541429F, -1.799558F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bool9[]
START
	NORM(  0.545300F, -0.000045F, -0.838241F ),
	NORM(  0.627337F,  0.557991F, -0.543226F ),
	NORM( -0.609202F,  0.586023F, -0.534276F ),
	NORM( -0.356223F,  0.934400F,  0.001037F ),
	NORM(  0.195518F,  0.979162F,  0.054907F ),
	NORM( -0.659470F, -0.000001F, -0.751731F ),
END

MODEL       model_F40_GTE_sh_null1_1_bool9[]
START
Points      point_F40_GTE_sh_null1_1_bool9,
Normal      normal_F40_GTE_sh_null1_1_bool9,
PointNum    6,
Meshset     meshset_F40_GTE_sh_null1_1_bool9,
Materials   matlist_F40_GTE_sh_null1_1_bool9,
MeshsetNum  2,
MatNum      2,
Center      -0.706075F,  0.455036F, -1.948007F,
Radius       0.256422F,
END

OBJECT      object_F40_GTE_sh_null1_1_bool9[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bool9,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool8,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cube13[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 10 ),
AttrFlags ( 0x9429a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 11 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_1_F40_GTE_sh_null1_1_cube13[]
START
	Strip(0x0, 4),  5, 2, 3, 0, 
	Strip(0x0, 8),  3, 7, 5, 4, 2, 1, 0, 6, 
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_cube13[]
START
	UV( 251, 253 ),
	UV( 0, 253 ),
	UV( 251, 253 ),
	UV( 0, 253 ),
	UV( 251, 253 ),
	UV( 251, 5 ),
	UV( 251, 253 ),
	UV( 251, 5 ),
	UV( 0, 253 ),
	UV( 0, 5 ),
	UV( 0, 253 ),
	UV( 0, 5 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_cube13[]
START

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_cube13,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_cube13,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cube13[]
START
	VERT(  0.129023F,  0.603432F,  1.394192F ),
	VERT(  0.129023F,  0.789233F,  1.075192F ),
	VERT(  0.129023F,  0.740638F,  1.394192F ),
	VERT(  0.444477F,  0.603432F,  1.394192F ),
	VERT(  0.444477F,  0.789233F,  1.075192F ),
	VERT(  0.444477F,  0.740638F,  1.394192F ),
	VERT(  0.129023F,  0.603432F,  1.075192F ),
	VERT(  0.444477F,  0.603432F,  1.075192F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cube13[]
START
	NORM( -0.707107F,  0.000000F,  0.707107F ),
	NORM( -0.670504F,  0.733444F,  0.111731F ),
	NORM( -0.585719F,  0.528204F,  0.614763F ),
	NORM(  0.707107F,  0.000000F,  0.707107F ),
	NORM(  0.670504F,  0.733444F,  0.111731F ),
	NORM(  0.585719F,  0.528204F,  0.614763F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_cube13[]
START
Points      point_F40_GTE_sh_null1_1_cube13,
Normal      normal_F40_GTE_sh_null1_1_cube13,
PointNum    8,
Meshset     meshset_F40_GTE_sh_null1_1_cube13,
Materials   matlist_F40_GTE_sh_null1_1_cube13,
MeshsetNum  1,
MatNum      2,
Center       0.286750F,  0.696333F,  1.234692F,
Radius       0.224317F,
END

OBJECT      object_F40_GTE_sh_null1_1_cube13[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_cube13,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bool9,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cube8[]
START

MATSTART
Diffuse   ( 255, 109, 109, 109 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 11 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_1_F40_GTE_sh_null1_1_cube8[]
START
	Strip(0x0, 4),  5, 2, 3, 0, 
	Strip(0x0, 8),  3, 7, 5, 4, 2, 1, 0, 6, 
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_cube8[]
START
	UV( 251, 253 ),
	UV( 0, 253 ),
	UV( 251, 253 ),
	UV( 0, 253 ),
	UV( 251, 253 ),
	UV( 251, 5 ),
	UV( 251, 253 ),
	UV( 251, 5 ),
	UV( 0, 253 ),
	UV( 0, 5 ),
	UV( 0, 253 ),
	UV( 0, 5 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_cube8[]
START

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_cube8,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_cube8,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cube8[]
START
	VERT( -0.444416F,  0.603432F,  1.394192F ),
	VERT( -0.444416F,  0.789233F,  1.075192F ),
	VERT( -0.444416F,  0.740638F,  1.394192F ),
	VERT( -0.128961F,  0.603432F,  1.394192F ),
	VERT( -0.128961F,  0.789233F,  1.075192F ),
	VERT( -0.128961F,  0.740638F,  1.394192F ),
	VERT( -0.444416F,  0.603432F,  1.075192F ),
	VERT( -0.128961F,  0.603432F,  1.075192F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cube8[]
START
	NORM( -0.707107F,  0.000000F,  0.707107F ),
	NORM( -0.670504F,  0.733444F,  0.111731F ),
	NORM( -0.585719F,  0.528204F,  0.614763F ),
	NORM(  0.707107F,  0.000000F,  0.707107F ),
	NORM(  0.670504F,  0.733444F,  0.111731F ),
	NORM(  0.585719F,  0.528204F,  0.614763F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_cube8[]
START
Points      point_F40_GTE_sh_null1_1_cube8,
Normal      normal_F40_GTE_sh_null1_1_cube8,
PointNum    8,
Meshset     meshset_F40_GTE_sh_null1_1_cube8,
Materials   matlist_F40_GTE_sh_null1_1_cube8,
MeshsetNum  1,
MatNum      2,
Center      -0.286688F,  0.696333F,  1.234692F,
Radius       0.224317F,
END

OBJECT      object_F40_GTE_sh_null1_1_cube8[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_cube8,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_cube13,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_cube10[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 9 ),
AttrFlags ( 0x9429a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 10 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_cube10[]
START
	Strip(0x8000, 5),  3, 2, 6, 0, 4, 
	Strip(0x0, 3),  3, 7, 6, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_cube10[]
START
	Strip(0x0, 4),  7, 3, 5, 1, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_cube10[]
START
	UV( 0, 255 ),
	UV( 30, 3 ),
	UV( 220, 3 ),
	UV( 30, 3 ),
	UV( 220, 3 ),
	UV( 0, 255 ),
	UV( 251, 255 ),
	UV( 220, 3 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_cube10[]
START
	UV( 191, 255 ),
	UV( 191, 7 ),
	UV( 41, 255 ),
	UV( 41, 7 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_cube10[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     2,
Meshes      pgS_0_F40_GTE_sh_null1_1_cube10,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_cube10,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     1,
Meshes      pgS_1_F40_GTE_sh_null1_1_cube10,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_cube10,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_cube10[]
START
	VERT( -0.245787F,  0.601081F,  0.783245F ),
	VERT( -0.324930F,  0.601081F,  1.026406F ),
	VERT( -0.245787F,  0.763321F,  0.783245F ),
	VERT( -0.324930F,  0.699999F,  1.026406F ),
	VERT(  0.245787F,  0.601081F,  0.783245F ),
	VERT(  0.324930F,  0.601081F,  1.026406F ),
	VERT(  0.245787F,  0.763321F,  0.783245F ),
	VERT(  0.324930F,  0.699999F,  1.026406F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_cube10[]
START
	NORM(  0.000000F,  0.000000F, -1.000000F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.000000F,  0.855654F, -0.517549F ),
	NORM(  0.000000F,  0.543888F,  0.839158F ),
	NORM(  0.000000F,  0.000000F, -1.000000F ),
	NORM(  0.000000F,  0.000000F,  1.000000F ),
	NORM(  0.000000F,  0.855654F, -0.517549F ),
	NORM(  0.000000F,  0.543888F,  0.839158F ),
END

MODEL       model_F40_GTE_sh_null1_1_cube10[]
START
Points      point_F40_GTE_sh_null1_1_cube10,
Normal      normal_F40_GTE_sh_null1_1_cube10,
PointNum    8,
Meshset     meshset_F40_GTE_sh_null1_1_cube10,
Materials   matlist_F40_GTE_sh_null1_1_cube10,
MeshsetNum  2,
MatNum      2,
Center       0.000000F,  0.682201F,  0.904825F,
Radius       0.346932F,
END

OBJECT      object_F40_GTE_sh_null1_1_cube10[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_cube10,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_cube8,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_C_F_GRIL[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 8 ),
AttrFlags ( 0x9428a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_C_F_GRIL[]
START
	Strip(0x0, 4),  9, 4, 0, 2, 
	Strip(0x0, 4),  5, 10, 3, 11, 
	Strip(0x0, 4),  6, 8, 7, 1, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_C_F_GRIL[]
START
	UV( 0, 226 ),
	UV( 0, 7 ),
	UV( 514, 226 ),
	UV( 514, 7 ),
	UV( 3127, 7 ),
	UV( 3127, 255 ),
	UV( 697, 7 ),
	UV( 697, 255 ),
	UV( 3825, 7 ),
	UV( 3825, 226 ),
	UV( 3310, 7 ),
	UV( 3310, 226 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_C_F_GRIL[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_C_F_GRIL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_C_F_GRIL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_C_F_GRIL[]
START
	VERT( -0.577238F,  0.173664F, -2.110157F ),
	VERT(  0.577238F,  0.173664F, -2.110157F ),
	VERT( -0.577238F,  0.301136F, -2.098099F ),
	VERT( -0.501495F,  0.301139F, -2.100369F ),
	VERT( -0.789508F,  0.301139F, -2.000720F ),
	VERT(  0.501495F,  0.301139F, -2.100369F ),
	VERT(  0.789508F,  0.301139F, -2.000720F ),
	VERT(  0.577239F,  0.301136F, -2.098099F ),
	VERT(  0.789508F,  0.173633F, -2.012650F ),
	VERT( -0.789508F,  0.173633F, -2.012650F ),
	VERT(  0.501495F,  0.156766F, -2.112082F ),
	VERT( -0.501495F,  0.156766F, -2.112082F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_C_F_GRIL[]
START
	NORM( -0.415916F,  0.085179F, -0.905405F ),
	NORM(  0.415453F,  0.085199F, -0.905616F ),
	NORM( -0.415916F,  0.085179F, -0.905405F ),
	NORM(  0.000000F,  0.080865F, -0.996725F ),
	NORM( -0.415916F,  0.085179F, -0.905405F ),
	NORM(  0.000000F,  0.080865F, -0.996725F ),
	NORM(  0.415453F,  0.085199F, -0.905616F ),
	NORM(  0.415453F,  0.085199F, -0.905616F ),
	NORM(  0.415453F,  0.085199F, -0.905616F ),
	NORM( -0.415916F,  0.085179F, -0.905405F ),
	NORM(  0.000000F,  0.080865F, -0.996725F ),
	NORM(  0.000000F,  0.080865F, -0.996725F ),
END

MODEL       model_F40_GTE_sh_null1_1_C_F_GRIL[]
START
Points      point_F40_GTE_sh_null1_1_C_F_GRIL,
Normal      normal_F40_GTE_sh_null1_1_C_F_GRIL,
PointNum    12,
Meshset     meshset_F40_GTE_sh_null1_1_C_F_GRIL,
Materials   matlist_F40_GTE_sh_null1_1_C_F_GRIL,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.228953F, -2.056401F,
Radius       0.791469F,
END

OBJECT      object_F40_GTE_sh_null1_1_C_F_GRIL[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_C_F_GRIL,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_cube10,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 7 ),
AttrFlags ( 0x9629a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START
	Strip(0x8000, 14),  3, 5, 6, 8, 4, 10, 2, 12, 0, 14, 
			18, 16, 15, 13, 
	Strip(0x0, 10),  5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 
	Strip(0x0, 10),  15, 18, 17, 0, 19, 2, 1, 4, 3, 6, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START
	UV( 23, 51 ),
	UV( 86, 3 ),
	UV( 86, 3 ),
	UV( 164, 3 ),
	UV( 23, 51 ),
	UV( 227, 51 ),
	UV( 0, 129 ),
	UV( 251, 129 ),
	UV( 23, 207 ),
	UV( 227, 207 ),
	UV( 86, 255 ),
	UV( 164, 255 ),
	UV( 164, 255 ),
	UV( 227, 207 ),
	UV( 86, 3 ),
	UV( 164, 3 ),
	UV( 164, 3 ),
	UV( 227, 51 ),
	UV( 227, 51 ),
	UV( 251, 129 ),
	UV( 251, 129 ),
	UV( 227, 207 ),
	UV( 227, 207 ),
	UV( 164, 255 ),
	UV( 164, 255 ),
	UV( 86, 255 ),
	UV( 86, 255 ),
	UV( 23, 207 ),
	UV( 23, 207 ),
	UV( 0, 129 ),
	UV( 0, 129 ),
	UV( 23, 51 ),
	UV( 23, 51 ),
	UV( 86, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START
	VERT( -0.808407F,  0.603534F,  2.173978F ),
	VERT( -0.823376F,  0.649602F,  2.081477F ),
	VERT( -0.823376F,  0.649602F,  2.173978F ),
	VERT( -0.808407F,  0.695670F,  2.081477F ),
	VERT( -0.808407F,  0.695670F,  2.173978F ),
	VERT( -0.769220F,  0.724141F,  2.081477F ),
	VERT( -0.769220F,  0.724141F,  2.173978F ),
	VERT( -0.720781F,  0.724141F,  2.081477F ),
	VERT( -0.720781F,  0.724141F,  2.173978F ),
	VERT( -0.681594F,  0.695670F,  2.081477F ),
	VERT( -0.681594F,  0.695670F,  2.173978F ),
	VERT( -0.666625F,  0.649602F,  2.081477F ),
	VERT( -0.666625F,  0.649602F,  2.173978F ),
	VERT( -0.681594F,  0.603534F,  2.081477F ),
	VERT( -0.681594F,  0.603534F,  2.173978F ),
	VERT( -0.720781F,  0.575063F,  2.081477F ),
	VERT( -0.720781F,  0.575063F,  2.173978F ),
	VERT( -0.769220F,  0.575063F,  2.081477F ),
	VERT( -0.769220F,  0.575063F,  2.173978F ),
	VERT( -0.808407F,  0.603534F,  2.081477F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START
	NORM( -0.619112F, -0.449811F,  0.643716F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -0.765264F,  0.000000F,  0.643717F ),
	NORM( -0.809017F,  0.587785F,  0.000000F ),
	NORM( -0.619112F,  0.449811F,  0.643717F ),
	NORM( -0.309017F,  0.951057F,  0.000000F ),
	NORM( -0.236480F,  0.727809F,  0.643717F ),
	NORM(  0.309017F,  0.951057F,  0.000000F ),
	NORM(  0.236479F,  0.727809F,  0.643717F ),
	NORM(  0.809017F,  0.587785F,  0.000000F ),
	NORM(  0.619111F,  0.449811F,  0.643717F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  0.765264F,  0.000000F,  0.643717F ),
	NORM(  0.809017F, -0.587785F,  0.000000F ),
	NORM(  0.619112F, -0.449811F,  0.643717F ),
	NORM(  0.309017F, -0.951056F,  0.000000F ),
	NORM(  0.236479F, -0.727809F,  0.643717F ),
	NORM( -0.309017F, -0.951057F,  0.000000F ),
	NORM( -0.236479F, -0.727809F,  0.643717F ),
	NORM( -0.809017F, -0.587785F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START
Points      point_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
Normal      normal_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
PointNum    20,
Meshset     meshset_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
Materials   matlist_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
MeshsetNum  1,
MatNum      1,
Center      -0.745000F,  0.649602F,  2.127728F,
Radius       0.091004F,
END

OBJECT      object_F40_GTE_sh_null1_1_TALE_LAMP_R_1[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_C_F_GRIL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 7 ),
AttrFlags ( 0x9629a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START
	Strip(0x0, 10),  18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 
	Strip(0x8000, 14),  9, 7, 8, 6, 10, 4, 12, 2, 14, 0, 
			16, 18, 17, 19, 
	Strip(0x0, 10),  17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START
	UV( 164, 255 ),
	UV( 227, 207 ),
	UV( 227, 207 ),
	UV( 251, 129 ),
	UV( 251, 129 ),
	UV( 227, 51 ),
	UV( 227, 51 ),
	UV( 164, 3 ),
	UV( 164, 3 ),
	UV( 86, 3 ),
	UV( 23, 51 ),
	UV( 86, 3 ),
	UV( 86, 3 ),
	UV( 164, 3 ),
	UV( 23, 51 ),
	UV( 227, 51 ),
	UV( 0, 129 ),
	UV( 251, 129 ),
	UV( 23, 207 ),
	UV( 227, 207 ),
	UV( 86, 255 ),
	UV( 164, 255 ),
	UV( 164, 255 ),
	UV( 227, 207 ),
	UV( 164, 255 ),
	UV( 86, 255 ),
	UV( 86, 255 ),
	UV( 23, 207 ),
	UV( 23, 207 ),
	UV( 0, 129 ),
	UV( 0, 129 ),
	UV( 23, 51 ),
	UV( 23, 51 ),
	UV( 86, 3 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START
	VERT(  0.808407F,  0.603534F,  2.173978F ),
	VERT(  0.823376F,  0.649602F,  2.081478F ),
	VERT(  0.823376F,  0.649602F,  2.173978F ),
	VERT(  0.808407F,  0.695670F,  2.081478F ),
	VERT(  0.808407F,  0.695670F,  2.173978F ),
	VERT(  0.769220F,  0.724141F,  2.081478F ),
	VERT(  0.769220F,  0.724141F,  2.173978F ),
	VERT(  0.720781F,  0.724141F,  2.081478F ),
	VERT(  0.720781F,  0.724141F,  2.173978F ),
	VERT(  0.681594F,  0.695670F,  2.081478F ),
	VERT(  0.681594F,  0.695670F,  2.173978F ),
	VERT(  0.666625F,  0.649602F,  2.081478F ),
	VERT(  0.666625F,  0.649602F,  2.173978F ),
	VERT(  0.681594F,  0.603534F,  2.081478F ),
	VERT(  0.681594F,  0.603534F,  2.173978F ),
	VERT(  0.720781F,  0.575063F,  2.081478F ),
	VERT(  0.720781F,  0.575063F,  2.173978F ),
	VERT(  0.769220F,  0.575063F,  2.081478F ),
	VERT(  0.769220F,  0.575063F,  2.173978F ),
	VERT(  0.808407F,  0.603534F,  2.081478F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START
	NORM(  0.619112F, -0.449811F,  0.643717F ),
	NORM(  1.000000F,  0.000001F,  0.000000F ),
	NORM(  0.765264F,  0.000000F,  0.643717F ),
	NORM(  0.809017F,  0.587786F,  0.000000F ),
	NORM(  0.619111F,  0.449811F,  0.643717F ),
	NORM(  0.309017F,  0.951056F,  0.000000F ),
	NORM(  0.236480F,  0.727809F,  0.643717F ),
	NORM( -0.309017F,  0.951057F,  0.000000F ),
	NORM( -0.236479F,  0.727809F,  0.643717F ),
	NORM( -0.809017F,  0.587785F,  0.000000F ),
	NORM( -0.619111F,  0.449811F,  0.643717F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -0.765264F,  0.000000F,  0.643717F ),
	NORM( -0.809017F, -0.587785F,  0.000000F ),
	NORM( -0.619112F, -0.449811F,  0.643717F ),
	NORM( -0.309017F, -0.951056F,  0.000000F ),
	NORM( -0.236480F, -0.727809F,  0.643717F ),
	NORM(  0.309017F, -0.951057F,  0.000000F ),
	NORM(  0.236479F, -0.727809F,  0.643717F ),
	NORM(  0.809017F, -0.587785F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START
Points      point_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
Normal      normal_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
PointNum    20,
Meshset     meshset_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
Materials   matlist_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
MeshsetNum  1,
MatNum      1,
Center       0.745000F,  0.649602F,  2.127728F,
Radius       0.091004F,
END

OBJECT      object_F40_GTE_sh_null1_1_TALE_LAMP_L_1[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_TALE_LAMP_R_1,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_SEAT_L[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 5 ),
AttrFlags ( 0x9429a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 6 ),
AttrFlags ( 0x9429a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_SEAT_L[]
START
	Strip(0x8000, 7),  8, 9, 3, 0, 16, 19, 11, 
	Strip(0x8000, 13),  14, 2, 19, 13, 11, 12, 10, 17, 18, 5, 
			16, 6, 15, 
	Strip(0x0, 4),  2, 13, 1, 12, 
	Strip(0x0, 4),  11, 16, 10, 18, 
	Strip(0x8000, 5),  9, 7, 0, 14, 19, 
	Strip(0x0, 5),  8, 4, 3, 15, 16, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_SEAT_L[]
START
	Strip(0x0, 3),  2, 7, 14, 
	Strip(0x0, 3),  4, 6, 15, 
	Strip(0x0, 7),  9, 7, 4, 2, 6, 1, 5, 
	Strip(0x0, 3),  4, 8, 9, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_SEAT_L[]
START
	UV( 170, 1 ),
	UV( 80, 1 ),
	UV( 196, 45 ),
	UV( 54, 45 ),
	UV( 213, 126 ),
	UV( 37, 126 ),
	UV( 53, 246 ),
	UV( 0, 81 ),
	UV( 37, 126 ),
	UV( 37, 126 ),
	UV( 37, 197 ),
	UV( 53, 246 ),
	UV( 37, 244 ),
	UV( 197, 246 ),
	UV( 213, 244 ),
	UV( 213, 197 ),
	UV( 213, 265 ),
	UV( 213, 126 ),
	UV( 213, 126 ),
	UV( 251, 81 ),
	UV( 37, 126 ),
	UV( 37, 197 ),
	UV( 37, 265 ),
	UV( 37, 244 ),
	UV( 53, 246 ),
	UV( 213, 126 ),
	UV( 197, 246 ),
	UV( 213, 197 ),
	UV( 80, 1 ),
	UV( 54, 45 ),
	UV( 54, 45 ),
	UV( 0, 81 ),
	UV( 37, 126 ),
	UV( 170, 1 ),
	UV( 196, 45 ),
	UV( 196, 45 ),
	UV( 251, 81 ),
	UV( 213, 126 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_SEAT_L[]
START
	UV( 37, 121 ),
	UV( 54, 44 ),
	UV( 0, 78 ),
	UV( 196, 44 ),
	UV( 213, 121 ),
	UV( 251, 78 ),
	UV( 80, 1 ),
	UV( 54, 44 ),
	UV( 196, 44 ),
	UV( 37, 121 ),
	UV( 213, 121 ),
	UV( 37, 255 ),
	UV( 213, 255 ),
	UV( 196, 44 ),
	UV( 170, 1 ),
	UV( 80, 1 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_SEAT_L[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     6,
Meshes      pgS_0_F40_GTE_sh_null1_1_SEAT_L,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_SEAT_L,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     4,
Meshes      pgS_1_F40_GTE_sh_null1_1_SEAT_L,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_SEAT_L,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_SEAT_L[]
START
	VERT( -0.510405F,  0.819058F,  0.255712F ),
	VERT( -0.550000F,  0.209595F,  0.005652F ),
	VERT( -0.550000F,  0.595942F,  0.207610F ),
	VERT( -0.189595F,  0.819058F,  0.255712F ),
	VERT( -0.189595F,  0.819058F,  0.305027F ),
	VERT( -0.150000F,  0.209595F,  0.005652F ),
	VERT( -0.150000F,  0.595942F,  0.207610F ),
	VERT( -0.510405F,  0.819058F,  0.305027F ),
	VERT( -0.247333F,  0.941138F,  0.328523F ),
	VERT( -0.452667F,  0.941138F,  0.328523F ),
	VERT( -0.187333F,  0.261669F, -0.046472F ),
	VERT( -0.512667F,  0.261669F, -0.046472F ),
	VERT( -0.550000F,  0.268758F, -0.557643F ),
	VERT( -0.550000F,  0.399379F, -0.050145F ),
	VERT( -0.634992F,  0.720731F,  0.112964F ),
	VERT( -0.065008F,  0.720731F,  0.112964F ),
	VERT( -0.150000F,  0.595942F,  0.158295F ),
	VERT( -0.150000F,  0.268758F, -0.557643F ),
	VERT( -0.150000F,  0.399379F, -0.050145F ),
	VERT( -0.550000F,  0.595942F,  0.158295F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_SEAT_L[]
START
	NORM( -0.373307F,  0.711558F, -0.595254F ),
	NORM( -0.778418F, -0.290810F,  0.556322F ),
	NORM( -0.594361F, -0.407869F,  0.693093F ),
	NORM(  0.373307F,  0.711558F, -0.595254F ),
	NORM(  0.636922F,  0.073273F,  0.767438F ),
	NORM(  0.778418F, -0.290810F,  0.556322F ),
	NORM(  0.594361F, -0.407869F,  0.693093F ),
	NORM( -0.636922F,  0.073273F,  0.767438F ),
	NORM(  0.336922F,  0.880197F,  0.334271F ),
	NORM( -0.336922F,  0.880197F,  0.334271F ),
	NORM( -0.502376F,  0.762002F, -0.408622F ),
	NORM(  0.502376F,  0.762002F, -0.408622F ),
	NORM( -0.058057F,  0.998312F,  0.001516F ),
	NORM( -0.185341F,  0.812611F, -0.552550F ),
	NORM( -0.670705F,  0.235576F, -0.703320F ),
	NORM(  0.670705F,  0.235576F, -0.703320F ),
	NORM(  0.658185F,  0.123254F, -0.742698F ),
	NORM(  0.058057F,  0.998312F,  0.001516F ),
	NORM(  0.185341F,  0.812611F, -0.552550F ),
	NORM( -0.658185F,  0.123254F, -0.742698F ),
END

MODEL       model_F40_GTE_sh_null1_1_SEAT_L[]
START
Points      point_F40_GTE_sh_null1_1_SEAT_L,
Normal      normal_F40_GTE_sh_null1_1_SEAT_L,
PointNum    20,
Meshset     meshset_F40_GTE_sh_null1_1_SEAT_L,
Materials   matlist_F40_GTE_sh_null1_1_SEAT_L,
MeshsetNum  2,
MatNum      2,
Center      -0.350000F,  0.575366F, -0.114560F,
Radius       0.574553F,
END

OBJECT      object_F40_GTE_sh_null1_1_SEAT_L[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_SEAT_L,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_TALE_LAMP_L_1,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_C_F4E_INNER_2[]
START

MATSTART
Diffuse   ( 255, 26, 26, 26 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_C_F4E_INNER_2[]
START
	Strip(0x0, 14),  16, 15, 10, 14, 3, 4, 23, 8, 0, 5, 
			17, 20, 6, 11, 
	Strip(0x8000, 6),  20, 11, 18, 7, 16, 10, 
	Strip(0x8000, 9),  9, 2, 1, 19, 12, 13, 21, 0, 23, 
	Strip(0x0, 3),  13, 22, 19, 
	Strip(0x0, 4),  12, 1, 21, 9, 
END

MESHSET     meshset_F40_GTE_sh_null1_1_C_F4E_INNER_2[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     5,
Meshes      pgS_0_F40_GTE_sh_null1_1_C_F4E_INNER_2,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_C_F4E_INNER_2[]
START
	VERT(  0.694044F,  0.779340F,  0.782614F ),
	VERT( -0.740400F,  0.200239F,  0.311995F ),
	VERT( -0.735800F,  0.200239F, -0.660513F ),
	VERT( -0.645617F,  0.795355F,  1.029665F ),
	VERT( -0.694044F,  0.629009F,  0.782614F ),
	VERT(  0.645617F,  0.629004F,  1.029666F ),
	VERT(  0.646464F,  0.810324F,  1.505506F ),
	VERT( -0.250000F,  0.817280F,  1.903015F ),
	VERT(  0.694044F,  0.629009F,  0.782614F ),
	VERT( -0.735734F,  0.707075F, -0.660589F ),
	VERT( -0.646464F,  0.810324F,  1.505506F ),
	VERT(  0.250000F,  0.817280F,  1.903015F ),
	VERT(  0.740400F,  0.200239F,  0.311995F ),
	VERT(  0.740481F,  0.763909F,  0.545745F ),
	VERT( -0.645617F,  0.629004F,  1.029665F ),
	VERT( -0.646400F,  0.629004F,  1.505491F ),
	VERT( -0.250000F,  0.629004F,  1.902995F ),
	VERT(  0.645617F,  0.795355F,  1.029666F ),
	VERT(  0.250000F,  0.629004F,  1.902995F ),
	VERT(  0.735800F,  0.200239F, -0.660602F ),
	VERT(  0.646400F,  0.629004F,  1.505491F ),
	VERT( -0.740481F,  0.763909F,  0.545745F ),
	VERT(  0.735734F,  0.707075F, -0.660589F ),
	VERT( -0.694044F,  0.779340F,  0.782614F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_C_F4E_INNER_2[]
START
	NORM( -0.607298F,  0.666540F,  0.432336F ),
	NORM(  0.602289F,  0.664321F, -0.442634F ),
	NORM(  0.706359F,  0.707848F,  0.002808F ),
	NORM(  0.995684F,  0.000183F, -0.092803F ),
	NORM(  0.772131F,  0.000000F,  0.635464F ),
	NORM( -0.995403F,  0.000000F, -0.095778F ),
	NORM( -0.922244F,  0.000103F, -0.386609F ),
	NORM(  0.381798F,  0.000158F, -0.924246F ),
	NORM( -0.772131F,  0.000000F,  0.635463F ),
	NORM(  0.999992F, -0.000854F,  0.003975F ),
	NORM(  0.922243F,  0.000292F, -0.386611F ),
	NORM( -0.381798F,  0.000158F, -0.924246F ),
	NORM( -0.602289F,  0.664321F, -0.442634F ),
	NORM( -0.411756F,  0.719419F, -0.559368F ),
	NORM(  0.995402F,  0.000178F, -0.095781F ),
	NORM(  0.924466F,  0.000294F, -0.381266F ),
	NORM(  0.383335F,  0.000158F, -0.923610F ),
	NORM( -0.995685F,  0.000000F, -0.092800F ),
	NORM( -0.383335F,  0.000158F, -0.923609F ),
	NORM( -0.706347F,  0.707860F,  0.002808F ),
	NORM( -0.924467F,  0.000102F, -0.381263F ),
	NORM(  0.411757F,  0.719419F, -0.559368F ),
	NORM( -0.999992F, -0.000854F,  0.003975F ),
	NORM(  0.607297F,  0.666540F,  0.432336F ),
END

MODEL       model_F40_GTE_sh_null1_1_C_F4E_INNER_2[]
START
Points      point_F40_GTE_sh_null1_1_C_F4E_INNER_2,
Normal      normal_F40_GTE_sh_null1_1_C_F4E_INNER_2,
PointNum    24,
Meshset     meshset_F40_GTE_sh_null1_1_C_F4E_INNER_2,
Materials   matlist_F40_GTE_sh_null1_1_C_F4E_INNER_2,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.508759F,  0.621206F,
Radius       1.480319F,
END

OBJECT      object_F40_GTE_sh_null1_1_C_F4E_INNER_2[]
START
EvalFlags ( 0x00000007 ),
Model       model_F40_GTE_sh_null1_1_C_F4E_INNER_2,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       object_F40_GTE_sh_null1_1_SEAT_L,
Sibling     object_F40_GTE_sh_null1_1_C_F4E_BODY_3,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_bmerge1[]
START

MATSTART
Diffuse   ( 255, 68, 68, 68 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  (  9.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 0, 0, 0 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 17, 17, 17 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 26, 26, 26 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 43, 43, 43 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 5, 5, 5 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 15, 15, 15 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 25, 25, 25 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 15, 15, 17 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94082400 ),
MATEND

MATSTART
Diffuse   ( 255, 25, 25, 25 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94882400 ),
MATEND

MATSTART
Diffuse   ( 255, 43, 43, 43 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94882400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 9),  16, 18, 15, 13, 12, 14, 3, 5, 4, 
	Strip(0x8000, 5),  4, 3, 10, 6, 7, 
	Strip(0x8000, 6),  3, 12, 6, 15, 7, 16, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 4),  22, 21, 20, 19, 
	Strip(0x0, 4),  24, 23, 26, 25, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 16),  38, 90, 58, 43, 27, 59, 28, 42, 65, 63, 
			60, 64, 40, 85, 94, 93, 
	Strip(0x0, 4),  61, 50, 55, 89, 
	Strip(0x0, 12),  92, 57, 81, 47, 80, 48, 78, 52, 77, 45, 
			76, 67, 
	Strip(0x0, 12),  68, 69, 34, 71, 33, 72, 53, 74, 32, 75, 
			31, 91, 
	Strip(0x0, 4),  56, 86, 62, 88, 
END

POLYGON     pgS_3_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x8000, 5),  17, 211, 11, 1, 0, 
	Strip(0x0, 3),  17, 212, 11, 
	Strip(0x8000, 5),  100, 101, 102, 97, 103, 
	Strip(0x0, 3),  100, 98, 102, 
END

POLYGON     pgS_4_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x8000, 8),  105, 106, 99, 96, 95, 104, 97, 103, 
END

POLYGON     pgS_5_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 4),  110, 109, 108, 107, 
	Strip(0x0, 4),  118, 117, 116, 115, 
	Strip(0x0, 10),  113, 118, 114, 116, 112, 115, 111, 117, 113, 118, 
END

POLYGON     pgS_6_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x8000, 7),  134, 148, 145, 158, 166, 165, 151, 
	Strip(0x8000, 7),  155, 154, 147, 149, 182, 157, 146, 
	Strip(0x0, 7),  156, 136, 138, 162, 150, 161, 164, 
	Strip(0x8000, 10),  172, 171, 127, 170, 173, 168, 141, 155, 160, 147, 
	Strip(0x0, 3),  172, 153, 127, 
	Strip(0x0, 6),  150, 164, 163, 151, 142, 166, 
	Strip(0x8000, 9),  122, 177, 121, 176, 133, 186, 137, 144, 139, 
	Strip(0x8000, 8),  124, 123, 178, 130, 184, 143, 132, 140, 
	Strip(0x0, 3),  124, 179, 178, 
	Strip(0x8000, 11),  181, 126, 152, 169, 180, 125, 185, 131, 139, 135, 
			137, 
	Strip(0x8000, 11),  120, 175, 159, 167, 119, 174, 129, 183, 140, 128, 
			132, 
END

POLYGON     pgS_7_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 4),  177, 181, 179, 175, 
	Strip(0x0, 4),  204, 205, 203, 206, 
END

POLYGON     pgS_8_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 4),  190, 189, 188, 187, 
	Strip(0x0, 4),  193, 194, 191, 192, 
	Strip(0x0, 4),  198, 197, 196, 195, 
	Strip(0x0, 4),  201, 202, 199, 200, 
END

POLYGON     pgS_9_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 4),  66, 54, 73, 70, 
	Strip(0x0, 3),  82, 30, 36, 
	Strip(0x8000, 6),  79, 49, 29, 36, 35, 82, 
	Strip(0x0, 3),  79, 51, 29, 
	Strip(0x0, 4),  44, 41, 2, 37, 
	Strip(0x0, 3),  207, 209, 215, 
	Strip(0x0, 6),  215, 8, 207, 208, 213, 214, 
	Strip(0x0, 3),  8, 9, 208, 
END

POLYGON     pgS_10_F40_GTE_sh_null1_1_bmerge1[]
START
	Strip(0x0, 6),  84, 87, 46, 39, 83, 210, 
END

MESHSET     meshset_F40_GTE_sh_null1_1_bmerge1[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     3,
Meshes      pgS_0_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     5,
Meshes      pgS_2_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 3 ),
MeshNum     4,
Meshes      pgS_3_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 4 ),
MeshNum     1,
Meshes      pgS_4_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 5 ),
MeshNum     3,
Meshes      pgS_5_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 6 ),
MeshNum     11,
Meshes      pgS_6_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 7 ),
MeshNum     2,
Meshes      pgS_7_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 8 ),
MeshNum     4,
Meshes      pgS_8_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 9 ),
MeshNum     8,
Meshes      pgS_9_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 10 ),
MeshNum     1,
Meshes      pgS_10_F40_GTE_sh_null1_1_bmerge1,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_bmerge1[]
START
	VERT(  0.106820F,  0.200204F,  0.587134F ),
	VERT(  0.106820F,  0.200204F, -1.060812F ),
	VERT(  0.942929F,  0.089178F, -0.799480F ),
	VERT( -0.460752F,  1.073090F,  0.452163F ),
	VERT( -0.562849F,  1.020657F,  0.572180F ),
	VERT( -0.460752F,  1.042391F,  0.766261F ),
	VERT( -0.460752F,  1.064682F, -0.057258F ),
	VERT( -0.519743F,  1.018843F, -0.154385F ),
	VERT(  0.408985F,  0.075770F, -2.150438F ),
	VERT(  0.409107F,  0.077662F, -2.251250F ),
	VERT( -0.549685F,  1.039690F,  0.081028F ),
	VERT(  0.000000F,  0.343204F,  0.587134F ),
	VERT(  0.460752F,  1.073090F,  0.452164F ),
	VERT(  0.562849F,  1.020657F,  0.572181F ),
	VERT(  0.460752F,  1.042391F,  0.766261F ),
	VERT(  0.460752F,  1.064682F, -0.057258F ),
	VERT(  0.519743F,  1.018843F, -0.154384F ),
	VERT( -0.106820F,  0.200204F, -1.060812F ),
	VERT(  0.549685F,  1.039690F,  0.081028F ),
	VERT(  0.921778F,  0.751405F,  1.778185F ),
	VERT(  0.889588F,  0.751405F,  2.161488F ),
	VERT(  0.947611F,  0.466437F,  1.777998F ),
	VERT(  0.915033F,  0.476147F,  2.161488F ),
	VERT( -0.921778F,  0.751405F,  1.778185F ),
	VERT( -0.889588F,  0.751405F,  2.161488F ),
	VERT( -0.947611F,  0.466437F,  1.777997F ),
	VERT( -0.915033F,  0.476147F,  2.161488F ),
	VERT( -0.784986F,  0.315431F, -2.073699F ),
	VERT( -0.520035F,  0.315431F, -2.171737F ),
	VERT( -0.586668F,  0.765018F,  1.552202F ),
	VERT(  0.532230F,  0.765018F,  0.755397F ),
	VERT( -0.966000F,  0.403537F, -0.853043F ),
	VERT( -0.966000F,  0.403741F, -0.714656F ),
	VERT( -0.931201F,  0.403741F,  0.097366F ),
	VERT( -0.980000F,  0.410298F,  0.545745F ),
	VERT(  0.586668F,  0.765018F,  1.552202F ),
	VERT(  0.532230F,  0.765018F,  1.476911F ),
	VERT( -0.942929F,  0.089178F, -0.799480F ),
	VERT( -0.952842F,  0.376336F, -1.478091F ),
	VERT( -0.208956F,  0.807460F, -0.660774F ),
	VERT(  0.821171F,  0.315431F, -2.035119F ),
	VERT( -0.976117F,  0.089178F,  1.027503F ),
	VERT( -0.519161F,  0.335431F, -2.170825F ),
	VERT( -0.821171F,  0.335431F, -2.035120F ),
	VERT(  0.976116F,  0.089178F,  1.027503F ),
	VERT(  0.966000F,  0.403741F, -0.714656F ),
	VERT( -0.488941F,  0.705496F, -0.943239F ),
	VERT(  0.980000F,  0.410298F,  0.545745F ),
	VERT(  0.931201F,  0.403741F,  0.097366F ),
	VERT( -0.532230F,  0.765018F,  1.476911F ),
	VERT( -0.961363F,  0.471292F,  2.024636F ),
	VERT( -0.586668F,  0.765018F,  0.755397F ),
	VERT(  0.917117F,  0.403741F, -0.709139F ),
	VERT( -0.917117F,  0.403741F, -0.709139F ),
	VERT(  0.487944F,  0.995741F,  0.617256F ),
	VERT( -0.982145F,  0.441379F,  1.758920F ),
	VERT(  0.982145F,  0.441379F,  1.758921F ),
	VERT(  1.000000F,  0.423506F,  1.051780F ),
	VERT( -0.821171F,  0.315431F, -2.035120F ),
	VERT( -0.784986F,  0.335431F, -2.072745F ),
	VERT(  0.784987F,  0.315431F, -2.073699F ),
	VERT( -0.962603F,  0.451292F,  2.024636F ),
	VERT(  0.962602F,  0.451292F,  2.024636F ),
	VERT(  0.519161F,  0.335431F, -2.170825F ),
	VERT(  0.784987F,  0.335431F, -2.072745F ),
	VERT(  0.520036F,  0.315431F, -2.171737F ),
	VERT(  0.508747F,  0.995741F,  0.640465F ),
	VERT(  0.966000F,  0.403537F, -0.853043F ),
	VERT( -1.000000F,  0.423506F,  1.051780F ),
	VERT( -1.000000F,  0.443805F,  1.059877F ),
	VERT( -0.511979F,  0.792794F,  1.513538F ),
	VERT( -0.977290F,  0.430302F,  0.545997F ),
	VERT( -0.928430F,  0.423741F,  0.097366F ),
	VERT( -0.491176F,  0.792794F,  1.536746F ),
	VERT( -0.914374F,  0.423742F, -0.708017F ),
	VERT( -0.966000F,  0.423739F, -0.713800F ),
	VERT(  0.966000F,  0.423537F, -0.863642F ),
	VERT(  0.966000F,  0.423739F, -0.713840F ),
	VERT(  0.914374F,  0.423742F, -0.708017F ),
	VERT( -0.532230F,  0.765018F,  0.755397F ),
	VERT(  0.928430F,  0.423741F,  0.097366F ),
	VERT(  0.977290F,  0.430302F,  0.545997F ),
	VERT(  0.586668F,  0.765018F,  0.755397F ),
	VERT( -0.209723F,  0.705496F, -0.943239F ),
	VERT( -0.541102F,  0.705496F, -0.660774F ),
	VERT(  0.821171F,  0.335431F, -2.035119F ),
	VERT(  0.982630F,  0.460780F,  1.747464F ),
	VERT( -0.489708F,  0.807460F, -0.660774F ),
	VERT(  0.961363F,  0.471292F,  2.024636F ),
	VERT( -0.982631F,  0.460780F,  1.747464F ),
	VERT( -0.953003F,  0.396874F, -1.476563F ),
	VERT( -0.966000F,  0.423539F, -0.863600F ),
	VERT(  1.000000F,  0.443805F,  1.059877F ),
	VERT(  0.953003F,  0.396874F, -1.476563F ),
	VERT(  0.953158F,  0.376336F, -1.478091F ),
	VERT( -0.735734F,  0.707075F, -0.660589F ),
	VERT(  0.520035F,  0.704833F, -0.950293F ),
	VERT( -0.735767F,  0.545235F, -0.660551F ),
	VERT(  0.735800F,  0.200239F, -0.660602F ),
	VERT( -0.520035F,  0.704833F, -0.950293F ),
	VERT( -0.735800F,  0.200239F, -0.660513F ),
	VERT( -0.494365F,  0.200239F, -0.764618F ),
	VERT(  0.494365F,  0.200239F, -0.764839F ),
	VERT(  0.735767F,  0.545235F, -0.660596F ),
	VERT(  0.735734F,  0.707075F, -0.660589F ),
	VERT( -0.250000F,  0.704830F, -1.043700F ),
	VERT(  0.250000F,  0.704830F, -1.043700F ),
	VERT( -0.645600F,  0.629004F,  0.777018F ),
	VERT( -0.646400F,  0.629004F,  1.939774F ),
	VERT(  0.645600F,  0.629004F,  0.777018F ),
	VERT(  0.646400F,  0.629004F,  1.939774F ),
	VERT( -0.147607F,  0.371084F,  2.215000F ),
	VERT( -0.147607F,  0.271084F,  2.215000F ),
	VERT(  0.147607F,  0.371084F,  2.215000F ),
	VERT(  0.147607F,  0.271084F,  2.215000F ),
	VERT( -0.147607F,  0.371084F,  2.068847F ),
	VERT( -0.147607F,  0.271084F,  2.068847F ),
	VERT(  0.147607F,  0.371084F,  2.068847F ),
	VERT(  0.147607F,  0.271084F,  2.068847F ),
	VERT( -0.966000F,  0.403537F, -0.853043F ),
	VERT( -0.942929F,  0.089178F, -0.799480F ),
	VERT(  0.953003F,  0.396874F, -1.476563F ),
	VERT(  0.950545F,  0.071032F, -1.500853F ),
	VERT( -0.953003F,  0.396874F, -1.476563F ),
	VERT( -0.950545F,  0.071032F, -1.500854F ),
	VERT(  0.966000F,  0.403537F, -0.853043F ),
	VERT(  0.942929F,  0.089178F, -0.799480F ),
	VERT(  0.586000F,  0.514289F,  1.715872F ),
	VERT( -0.500000F,  0.616229F, -1.082840F ),
	VERT( -0.966000F,  0.532112F, -0.937159F ),
	VERT( -0.956833F,  0.532112F, -1.396778F ),
	VERT(  0.966000F,  0.532112F, -0.937159F ),
	VERT( -0.500000F,  0.616229F, -1.251091F ),
	VERT(  0.956833F,  0.532112F, -1.396778F ),
	VERT( -0.586000F,  0.089178F,  1.027494F ),
	VERT(  0.966000F,  0.616228F, -1.082852F ),
	VERT( -0.948362F,  0.139552F,  1.856461F ),
	VERT(  0.963827F,  0.616228F, -1.251084F ),
	VERT( -0.586000F,  0.514289F,  1.715872F ),
	VERT(  0.500000F,  0.616229F, -1.082840F ),
	VERT( -0.966000F,  0.616228F, -1.082853F ),
	VERT(  0.586000F,  0.695539F,  1.401918F ),
	VERT( -0.586000F,  0.646979F,  1.220686F ),
	VERT( -0.963828F,  0.616228F, -1.251085F ),
	VERT(  0.500000F,  0.616229F, -1.251091F ),
	VERT( -0.586000F,  0.333039F,  1.039455F ),
	VERT(  0.586000F,  0.089178F,  1.027494F ),
	VERT(  0.586000F,  0.514289F,  1.088008F ),
	VERT( -0.976117F,  0.089178F,  1.027503F ),
	VERT(  1.000000F,  0.333042F,  1.039428F ),
	VERT( -0.586000F,  0.646979F,  1.583193F ),
	VERT( -0.999239F,  0.646976F,  1.220678F ),
	VERT(  0.500000F,  0.203178F, -0.809602F ),
	VERT(  0.615552F,  0.139552F,  1.856461F ),
	VERT(  1.000000F,  0.514292F,  1.087994F ),
	VERT(  0.999239F,  0.646976F,  1.220679F ),
	VERT( -0.615552F,  0.139552F,  1.856461F ),
	VERT(  0.976117F,  0.089178F,  1.027503F ),
	VERT( -1.000000F,  0.333043F,  1.039428F ),
	VERT( -0.954382F,  0.203177F, -0.809587F ),
	VERT(  0.586000F,  0.646979F,  1.220686F ),
	VERT( -0.987854F,  0.646976F,  1.583178F ),
	VERT( -0.983996F,  0.514292F,  1.715862F ),
	VERT( -0.586000F,  0.695539F,  1.401918F ),
	VERT( -0.995642F,  0.695542F,  1.401928F ),
	VERT( -1.000000F,  0.514292F,  1.087994F ),
	VERT( -0.586000F,  0.514289F,  1.088008F ),
	VERT( -0.500000F,  0.203178F, -0.809602F ),
	VERT(  0.995642F,  0.695542F,  1.401928F ),
	VERT(  0.954382F,  0.203177F, -0.809587F ),
	VERT(  0.987853F,  0.646976F,  1.583178F ),
	VERT(  0.983995F,  0.514292F,  1.715862F ),
	VERT(  0.948362F,  0.139552F,  1.856461F ),
	VERT(  0.586000F,  0.646979F,  1.583193F ),
	VERT( -0.500000F,  0.403539F, -0.853056F ),
	VERT( -0.500000F,  0.089178F, -0.799497F ),
	VERT(  0.500000F,  0.396857F, -1.476550F ),
	VERT(  0.500000F,  0.071032F, -1.500854F ),
	VERT( -0.500000F,  0.396857F, -1.476550F ),
	VERT( -0.500000F,  0.071032F, -1.500854F ),
	VERT(  0.500000F,  0.403539F, -0.853056F ),
	VERT(  0.500000F,  0.089178F, -0.799497F ),
	VERT(  0.586000F,  0.333039F,  1.039455F ),
	VERT( -0.500000F,  0.532109F, -0.937181F ),
	VERT( -0.500000F,  0.532109F, -1.396794F ),
	VERT(  0.500000F,  0.532109F, -0.937137F ),
	VERT(  0.500000F,  0.532109F, -1.396794F ),
	VERT( -0.500000F,  0.100239F, -1.500884F ),
	VERT( -0.500000F,  0.089178F, -0.799615F ),
	VERT( -0.500000F,  0.627339F, -1.500884F ),
	VERT( -0.500000F,  0.627339F, -0.799615F ),
	VERT(  0.500000F,  0.100239F, -1.500884F ),
	VERT(  0.500000F,  0.089178F, -0.799615F ),
	VERT(  0.500000F,  0.627339F, -1.500884F ),
	VERT(  0.500000F,  0.627339F, -0.799615F ),
	VERT( -0.586000F,  0.089178F,  1.027494F ),
	VERT( -0.599149F,  0.201609F,  1.836406F ),
	VERT( -0.586000F,  0.695539F,  1.026431F ),
	VERT( -0.586000F,  0.695539F,  1.782543F ),
	VERT(  0.586000F,  0.089178F,  1.027494F ),
	VERT(  0.599149F,  0.201609F,  1.836407F ),
	VERT(  0.586000F,  0.695539F,  1.026431F ),
	VERT(  0.586000F,  0.695539F,  1.782543F ),
	VERT( -0.586000F,  0.089178F,  1.027494F ),
	VERT(  0.586000F,  0.089178F,  1.027494F ),
	VERT(  0.599149F,  0.201609F,  1.836407F ),
	VERT( -0.599149F,  0.201609F,  1.836406F ),
	VERT( -0.797546F,  0.075768F, -2.146829F ),
	VERT(  0.797546F,  0.075768F, -2.146828F ),
	VERT( -0.409107F,  0.077662F, -2.251250F ),
	VERT( -0.157562F,  0.705496F, -0.660774F ),
	VERT(  0.000000F,  0.343204F, -1.060812F ),
	VERT( -0.106820F,  0.200204F,  0.587134F ),
	VERT( -0.950545F,  0.071032F, -1.500854F ),
	VERT(  0.950545F,  0.071032F, -1.500853F ),
	VERT( -0.408985F,  0.075770F, -2.150438F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_bmerge1[]
START
	NORM(  0.801155F,  0.598457F,  0.000000F ),
	NORM(  0.801155F,  0.598457F,  0.000000F ),
	NORM(  0.000000F, -1.000000F,  0.000000F ),
	NORM(  0.221109F, -0.974689F, -0.033038F ),
	NORM(  0.392796F, -0.917213F, -0.066566F ),
	NORM(  0.093200F, -0.990926F, -0.096851F ),
	NORM(  0.195187F, -0.960473F,  0.198480F ),
	NORM(  0.190549F, -0.927385F,  0.321945F ),
	NORM(  0.000060F, -0.999938F, -0.011158F ),
	NORM(  0.000168F, -0.999824F, -0.018762F ),
	NORM(  0.454976F, -0.890295F,  0.019270F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM( -0.221109F, -0.974689F, -0.033038F ),
	NORM( -0.392796F, -0.917213F, -0.066566F ),
	NORM( -0.093200F, -0.990926F, -0.096851F ),
	NORM( -0.195187F, -0.960473F,  0.198480F ),
	NORM( -0.190549F, -0.927385F,  0.321945F ),
	NORM( -0.801155F,  0.598457F,  0.000000F ),
	NORM( -0.454976F, -0.890295F,  0.019270F ),
	NORM(  0.992347F,  0.091731F,  0.082658F ),
	NORM(  0.992347F,  0.091731F,  0.082658F ),
	NORM(  0.992347F,  0.091731F,  0.082658F ),
	NORM(  0.992347F,  0.091731F,  0.082658F ),
	NORM( -0.992347F,  0.091731F,  0.082658F ),
	NORM( -0.992347F,  0.091731F,  0.082658F ),
	NORM( -0.992347F,  0.091731F,  0.082658F ),
	NORM( -0.992347F,  0.091731F,  0.082658F ),
	NORM( -0.543965F,  0.035071F, -0.838375F ),
	NORM( -0.179442F,  0.049239F, -0.982536F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000024F,  0.000000F ),
	NORM( -0.754792F, -0.027326F,  0.655394F ),
	NORM( -0.988621F,  0.136446F, -0.063335F ),
	NORM( -0.991456F,  0.106137F, -0.075824F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F, -1.000000F,  0.000000F ),
	NORM( -0.973129F,  0.004820F, -0.230210F ),
	NORM(  0.457244F,  0.836111F, -0.303063F ),
	NORM(  0.872922F,  0.015090F, -0.487626F ),
	NORM(  0.000000F, -1.000000F,  0.000000F ),
	NORM( -0.171753F,  0.049112F, -0.983915F ),
	NORM( -0.882234F,  0.010864F, -0.470687F ),
	NORM(  0.000000F, -1.000000F,  0.000000F ),
	NORM(  0.754389F, -0.026698F,  0.655885F ),
	NORM( -0.191287F,  0.923058F, -0.333727F ),
	NORM(  0.991457F,  0.106128F, -0.075824F ),
	NORM(  0.988621F,  0.136442F, -0.063335F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM( -0.996618F,  0.039946F,  0.071807F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.710332F,  0.058120F,  0.701464F ),
	NORM( -0.710374F,  0.057412F,  0.701479F ),
	NORM( -0.111278F,  0.988771F,  0.099744F ),
	NORM( -0.996618F,  0.039946F,  0.071807F ),
	NORM(  0.996618F,  0.039947F,  0.071807F ),
	NORM(  0.996283F,  0.075563F, -0.041348F ),
	NORM( -0.873363F,  0.011275F, -0.486940F ),
	NORM( -0.550218F,  0.034492F, -0.834308F ),
	NORM(  0.543969F,  0.035071F, -0.838372F ),
	NORM( -0.996618F,  0.039946F,  0.071807F ),
	NORM(  0.996618F,  0.039947F,  0.071807F ),
	NORM(  0.171753F,  0.049112F, -0.983915F ),
	NORM(  0.550223F,  0.034492F, -0.834305F ),
	NORM(  0.179442F,  0.049239F, -0.982536F ),
	NORM( -0.111278F,  0.988771F,  0.099744F ),
	NORM(  1.000000F,  0.000012F,  0.000000F ),
	NORM( -0.996283F,  0.075572F, -0.041348F ),
	NORM( -0.996283F,  0.075572F, -0.041348F ),
	NORM( -0.111278F,  0.988771F,  0.099744F ),
	NORM( -0.991622F,  0.105274F, -0.074850F ),
	NORM( -0.988626F,  0.136447F, -0.063252F ),
	NORM( -0.111278F,  0.988771F,  0.099744F ),
	NORM( -0.783959F,  0.072374F,  0.616579F ),
	NORM( -0.736200F, -0.028194F,  0.676177F ),
	NORM(  1.000000F,  0.000012F,  0.000000F ),
	NORM(  0.736630F, -0.027506F,  0.675736F ),
	NORM(  0.783918F,  0.073000F,  0.616558F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.988627F,  0.136443F, -0.063252F ),
	NORM(  0.991623F,  0.105266F, -0.074850F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.191287F,  0.923058F, -0.333727F ),
	NORM( -0.881080F,  0.444100F, -0.162705F ),
	NORM(  0.881774F,  0.014948F, -0.471435F ),
	NORM(  0.996618F,  0.039947F,  0.071807F ),
	NORM( -0.457244F,  0.836111F, -0.303063F ),
	NORM(  0.996618F,  0.039947F,  0.071807F ),
	NORM( -0.996618F,  0.039946F,  0.071807F ),
	NORM( -0.973129F,  0.004820F, -0.230210F ),
	NORM( -1.000000F,  0.000024F,  0.000000F ),
	NORM(  0.996283F,  0.075563F, -0.041348F ),
	NORM(  0.972675F,  0.012455F, -0.231835F ),
	NORM(  0.972675F,  0.012455F, -0.231835F ),
	NORM(  0.000000F,  0.511526F,  0.859268F ),
	NORM(  0.000000F,  0.999977F, -0.006730F ),
	NORM(  0.000040F, -0.112048F,  0.993703F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  0.999977F, -0.006730F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000076F,  0.714122F,  0.700022F ),
	NORM(  0.000076F,  0.714011F,  0.700134F ),
	NORM(  0.000040F, -0.112054F,  0.993702F ),
	NORM(  0.000000F,  0.511526F,  0.859268F ),
	NORM(  0.000000F,  1.000000F, -0.000029F ),
	NORM(  0.000000F,  1.000000F, -0.000029F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.707107F, -0.707107F,  0.000000F ),
	NORM(  0.707107F,  0.707107F,  0.000000F ),
	NORM( -0.707107F, -0.707107F,  0.000000F ),
	NORM( -0.707107F,  0.707107F,  0.000000F ),
	NORM(  0.577350F, -0.577350F,  0.577350F ),
	NORM(  0.577350F,  0.577350F,  0.577350F ),
	NORM( -0.577350F, -0.577350F,  0.577350F ),
	NORM( -0.577350F,  0.577350F,  0.577350F ),
	NORM( -0.000035F, -0.389295F, -0.921113F ),
	NORM( -0.000038F, -0.088303F, -0.996094F ),
	NORM(  0.000002F, -0.301275F,  0.953537F ),
	NORM(  0.000032F, -0.074364F,  0.997231F ),
	NORM( -0.000003F, -0.301225F,  0.953553F ),
	NORM(  0.000002F, -0.074364F,  0.997231F ),
	NORM(  0.000023F, -0.389239F, -0.921137F ),
	NORM(  0.000038F, -0.088303F, -0.996094F ),
	NORM( -0.000011F, -0.545796F, -0.837918F ),
	NORM(  0.000010F, -0.965917F, -0.258853F ),
	NORM( -0.000014F, -0.726523F, -0.687142F ),
	NORM(  0.000001F, -0.714212F,  0.699929F ),
	NORM(  0.000001F, -0.726511F, -0.687155F ),
	NORM(  0.000007F, -0.965926F,  0.258817F ),
	NORM( -0.000019F, -0.714246F,  0.699895F ),
	NORM(  0.000021F, -0.048915F,  0.998803F ),
	NORM( -0.000011F, -0.965640F, -0.259882F ),
	NORM(  0.000011F, -0.351261F, -0.936277F ),
	NORM( -0.000006F, -0.967130F,  0.254284F ),
	NORM(  0.000017F, -0.545793F, -0.837920F ),
	NORM( -0.000011F, -0.965925F, -0.258822F ),
	NORM(  0.000010F, -0.965632F, -0.259913F ),
	NORM(  0.000000F, -1.000000F,  0.000035F ),
	NORM( -0.000010F, -0.866017F,  0.500015F ),
	NORM(  0.000007F, -0.967130F,  0.254282F ),
	NORM( -0.000006F, -0.965926F,  0.258819F ),
	NORM( -0.000023F, -0.154726F,  0.987957F ),
	NORM(  0.000024F, -0.048989F,  0.998799F ),
	NORM(  0.000030F, -0.499963F,  0.866047F ),
	NORM(  0.000021F, -0.048915F,  0.998803F ),
	NORM(  0.000038F, -0.158124F,  0.987419F ),
	NORM(  0.000004F, -0.866020F, -0.500009F ),
	NORM( -0.000010F, -0.865016F,  0.501744F ),
	NORM(  0.000032F, -0.150425F, -0.988621F ),
	NORM( -0.000001F, -0.351270F, -0.936274F ),
	NORM(  0.000030F, -0.499660F,  0.866221F ),
	NORM(  0.000005F, -0.865023F,  0.501733F ),
	NORM(  0.000011F, -0.351261F, -0.936277F ),
	NORM(  0.000024F, -0.048989F,  0.998799F ),
	NORM( -0.000024F, -0.158106F,  0.987422F ),
	NORM( -0.000031F, -0.153550F, -0.988141F ),
	NORM(  0.000005F, -0.866023F,  0.500005F ),
	NORM(  0.000004F, -0.868642F, -0.495441F ),
	NORM(  0.000017F, -0.547892F, -0.836549F ),
	NORM( -0.000007F, -1.000000F,  0.000020F ),
	NORM( -0.000007F, -0.999986F,  0.005221F ),
	NORM( -0.000045F, -0.499665F,  0.866218F ),
	NORM( -0.000044F, -0.499968F,  0.866044F ),
	NORM( -0.000032F, -0.150425F, -0.988621F ),
	NORM(  0.000000F, -0.999986F,  0.005235F ),
	NORM(  0.000032F, -0.153550F, -0.988141F ),
	NORM( -0.000011F, -0.868650F, -0.495426F ),
	NORM( -0.000012F, -0.547896F, -0.836547F ),
	NORM( -0.000001F, -0.351270F, -0.936274F ),
	NORM( -0.000011F, -0.866028F, -0.499995F ),
	NORM( -0.000035F, -0.386170F, -0.922428F ),
	NORM( -0.000026F, -0.746336F, -0.665569F ),
	NORM(  0.000002F, -0.299019F,  0.954247F ),
	NORM(  0.000022F, -0.724067F,  0.689730F ),
	NORM( -0.000003F, -0.298970F,  0.954263F ),
	NORM(  0.000001F, -0.724067F,  0.689730F ),
	NORM(  0.000023F, -0.386114F, -0.922451F ),
	NORM(  0.000026F, -0.746336F, -0.665569F ),
	NORM(  0.000037F, -0.154746F,  0.987954F ),
	NORM( -0.000014F, -0.726529F, -0.687136F ),
	NORM(  0.000001F, -0.710352F,  0.703847F ),
	NORM(  0.000001F, -0.726503F, -0.687163F ),
	NORM( -0.000019F, -0.710387F,  0.703812F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM( -0.999623F,  0.025495F, -0.010230F ),
	NORM( -0.999623F,  0.025495F, -0.010230F ),
	NORM( -0.999623F,  0.025495F, -0.010230F ),
	NORM( -0.999623F,  0.025495F, -0.010230F ),
	NORM(  0.999965F, -0.000015F, -0.008400F ),
	NORM(  0.999965F, -0.000015F, -0.008400F ),
	NORM(  0.999965F, -0.000015F, -0.008400F ),
	NORM(  0.999965F, -0.000015F, -0.008400F ),
	NORM(  0.000000F, -0.990479F,  0.137667F ),
	NORM(  0.000000F, -0.990479F,  0.137667F ),
	NORM(  0.000000F, -0.990479F,  0.137667F ),
	NORM(  0.000000F, -0.990479F,  0.137667F ),
	NORM( -0.000016F, -0.999962F, -0.008728F ),
	NORM(  0.000026F, -0.999962F, -0.008728F ),
	NORM( -0.000168F, -0.999824F, -0.018762F ),
	NORM(  0.881080F,  0.444100F, -0.162705F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM( -0.801155F,  0.598457F,  0.000000F ),
	NORM(  0.000006F, -0.999973F, -0.007326F ),
	NORM(  0.000006F, -0.999973F, -0.007326F ),
	NORM( -0.000053F, -0.999938F, -0.011158F ),
END

MODEL       model_F40_GTE_sh_null1_1_bmerge1[]
START
Points      point_F40_GTE_sh_null1_1_bmerge1,
Normal      normal_F40_GTE_sh_null1_1_bmerge1,
PointNum    216,
Meshset     meshset_F40_GTE_sh_null1_1_bmerge1,
Materials   matlist_F40_GTE_sh_null1_1_bmerge1,
MeshsetNum  11,
MatNum      11,
Center       0.000000F,  0.572061F, -0.018125F,
Radius       2.446804F,
END

OBJECT      object_F40_GTE_sh_null1_1_bmerge1[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_bmerge1,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_C_F4E_INNER_2,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_TIRE_RL[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94a9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 1 ),
AttrFlags ( 0x94a9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 2 ),
AttrFlags ( 0x94f9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 3 ),
AttrFlags ( 0x94a9a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_TIRE_RL[]
START
	Strip(0x8000, 26),  20, 21, 25, 26, 30, 31, 35, 36, 40, 41, 
			45, 46, 50, 51, 55, 56, 0, 1, 5, 6, 
			10, 11, 15, 16, 20, 21, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_TIRE_RL[]
START
	Strip(0x0, 26),  51, 47, 46, 42, 41, 37, 36, 32, 31, 27, 
			26, 22, 21, 17, 16, 12, 11, 7, 6, 2, 
			1, 57, 56, 52, 51, 47, 
	Strip(0x0, 26),  18, 22, 23, 27, 28, 32, 33, 37, 38, 42, 
			43, 47, 48, 52, 53, 57, 58, 2, 3, 7, 
			8, 12, 13, 17, 18, 22, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_TIRE_RL[]
START
	Strip(0x0, 26),  54, 58, 59, 3, 4, 8, 9, 13, 14, 18, 
			19, 23, 24, 28, 29, 33, 34, 38, 39, 43, 
			44, 48, 49, 53, 54, 58, 
END

POLYGON     pgS_3_F40_GTE_sh_null1_1_TIRE_RL[]
START
	Strip(0x0, 4),  62, 63, 61, 60, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_RL[]
START
	UV( 132, 24 ),
	UV( 132, 237 ),
	UV( 122, 24 ),
	UV( 122, 237 ),
	UV( 111, 24 ),
	UV( 111, 237 ),
	UV( 100, 24 ),
	UV( 100, 237 ),
	UV( 90, 24 ),
	UV( 90, 237 ),
	UV( 79, 24 ),
	UV( 79, 237 ),
	UV( 68, 24 ),
	UV( 68, 237 ),
	UV( 58, 24 ),
	UV( 58, 237 ),
	UV( 47, 24 ),
	UV( 47, 237 ),
	UV( 37, 24 ),
	UV( 37, 237 ),
	UV( 26, 24 ),
	UV( 26, 237 ),
	UV( 15, 24 ),
	UV( 15, 237 ),
	UV( 5, 24 ),
	UV( 5, 237 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_RL[]
START
	UV( 241, 96 ),
	UV( 207, 45 ),
	UV( 210, 42 ),
	UV( 156, 15 ),
	UV( 157, 11 ),
	UV( 96, 15 ),
	UV( 95, 11 ),
	UV( 44, 45 ),
	UV( 42, 42 ),
	UV( 15, 97 ),
	UV( 11, 96 ),
	UV( 15, 156 ),
	UV( 11, 157 ),
	UV( 44, 208 ),
	UV( 42, 211 ),
	UV( 96, 237 ),
	UV( 95, 241 ),
	UV( 156, 237 ),
	UV( 157, 241 ),
	UV( 207, 208 ),
	UV( 210, 211 ),
	UV( 237, 156 ),
	UV( 241, 157 ),
	UV( 237, 97 ),
	UV( 241, 96 ),
	UV( 207, 45 ),
	UV( 59, 193 ),
	UV( 15, 156 ),
	UV( 34, 151 ),
	UV( 15, 97 ),
	UV( 34, 102 ),
	UV( 44, 45 ),
	UV( 59, 59 ),
	UV( 96, 15 ),
	UV( 101, 35 ),
	UV( 156, 15 ),
	UV( 150, 35 ),
	UV( 207, 45 ),
	UV( 193, 59 ),
	UV( 237, 97 ),
	UV( 217, 102 ),
	UV( 237, 156 ),
	UV( 217, 151 ),
	UV( 207, 208 ),
	UV( 193, 193 ),
	UV( 156, 237 ),
	UV( 150, 218 ),
	UV( 96, 237 ),
	UV( 101, 218 ),
	UV( 44, 208 ),
	UV( 59, 193 ),
	UV( 15, 156 ),
END

VERTUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_RL[]
START
	UV( 146, 52 ),
	UV( 101, 36 ),
	UV( 106, 52 ),
	UV( 59, 61 ),
	UV( 70, 72 ),
	UV( 34, 103 ),
	UV( 50, 108 ),
	UV( 34, 153 ),
	UV( 50, 148 ),
	UV( 59, 195 ),
	UV( 70, 184 ),
	UV( 101, 220 ),
	UV( 106, 204 ),
	UV( 151, 220 ),
	UV( 146, 204 ),
	UV( 193, 195 ),
	UV( 182, 184 ),
	UV( 218, 153 ),
	UV( 202, 148 ),
	UV( 218, 103 ),
	UV( 202, 108 ),
	UV( 193, 61 ),
	UV( 182, 72 ),
	UV( 151, 36 ),
	UV( 146, 52 ),
	UV( 101, 36 ),
END

VERTUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_RL[]
START
	UV( 31, 223 ),
	UV( 31, 33 ),
	UV( 221, 223 ),
	UV( 221, 33 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_TIRE_RL[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_TIRE_RL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_RL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_TIRE_RL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_RL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     1,
Meshes      pgS_2_F40_GTE_sh_null1_1_TIRE_RL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_RL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 3 ),
MeshNum     1,
Meshes      pgS_3_F40_GTE_sh_null1_1_TIRE_RL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_RL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_TIRE_RL[]
START
	VERT(  0.154016F,  0.246115F, -0.246046F ),
	VERT( -0.192010F,  0.246115F, -0.246046F ),
	VERT( -0.238995F,  0.237630F, -0.237561F ),
	VERT( -0.238997F,  0.196150F, -0.196083F ),
	VERT( -0.170672F,  0.162677F, -0.162608F ),
	VERT(  0.154016F,  0.090111F, -0.336115F ),
	VERT( -0.192010F,  0.090111F, -0.336115F ),
	VERT( -0.238995F,  0.087005F, -0.324524F ),
	VERT( -0.238997F,  0.071822F, -0.267863F ),
	VERT( -0.170672F,  0.059571F, -0.222136F ),
	VERT(  0.154016F, -0.090027F, -0.336115F ),
	VERT( -0.192010F, -0.090027F, -0.336115F ),
	VERT( -0.238995F, -0.086921F, -0.324524F ),
	VERT( -0.238997F, -0.071740F, -0.267863F ),
	VERT( -0.170672F, -0.059486F, -0.222136F ),
	VERT(  0.154016F, -0.246031F, -0.246046F ),
	VERT( -0.192010F, -0.246031F, -0.246046F ),
	VERT( -0.238995F, -0.237546F, -0.237561F ),
	VERT( -0.238997F, -0.196068F, -0.196083F ),
	VERT( -0.170672F, -0.162592F, -0.162608F ),
	VERT(  0.154016F, -0.336100F, -0.090042F ),
	VERT( -0.192010F, -0.336100F, -0.090042F ),
	VERT( -0.238995F, -0.324509F, -0.086936F ),
	VERT( -0.238997F, -0.267848F, -0.071754F ),
	VERT( -0.170672F, -0.222121F, -0.059501F ),
	VERT(  0.154016F, -0.336100F,  0.090096F ),
	VERT( -0.192010F, -0.336100F,  0.090096F ),
	VERT( -0.238995F, -0.324509F,  0.086990F ),
	VERT( -0.238997F, -0.267849F,  0.071807F ),
	VERT( -0.170672F, -0.222121F,  0.059555F ),
	VERT(  0.154016F, -0.246031F,  0.246100F ),
	VERT( -0.192010F, -0.246031F,  0.246100F ),
	VERT( -0.238995F, -0.237546F,  0.237615F ),
	VERT( -0.238997F, -0.196068F,  0.196135F ),
	VERT( -0.170672F, -0.162592F,  0.162662F ),
	VERT(  0.154016F, -0.090027F,  0.336169F ),
	VERT( -0.192010F, -0.090027F,  0.336169F ),
	VERT( -0.238995F, -0.086921F,  0.324578F ),
	VERT( -0.238997F, -0.071740F,  0.267916F ),
	VERT( -0.170672F, -0.059486F,  0.222190F ),
	VERT(  0.154016F,  0.090111F,  0.336169F ),
	VERT( -0.192010F,  0.090111F,  0.336169F ),
	VERT( -0.238995F,  0.087005F,  0.324578F ),
	VERT( -0.238997F,  0.071822F,  0.267916F ),
	VERT( -0.170672F,  0.059571F,  0.222190F ),
	VERT(  0.154016F,  0.246115F,  0.246100F ),
	VERT( -0.192010F,  0.246115F,  0.246100F ),
	VERT( -0.238995F,  0.237630F,  0.237615F ),
	VERT( -0.238997F,  0.196150F,  0.196135F ),
	VERT( -0.170672F,  0.162677F,  0.162661F ),
	VERT(  0.154016F,  0.336184F,  0.090096F ),
	VERT( -0.192010F,  0.336184F,  0.090096F ),
	VERT( -0.238995F,  0.324593F,  0.086990F ),
	VERT( -0.238997F,  0.267931F,  0.071807F ),
	VERT( -0.170672F,  0.222205F,  0.059555F ),
	VERT(  0.154016F,  0.336184F, -0.090042F ),
	VERT( -0.192010F,  0.336184F, -0.090042F ),
	VERT( -0.238995F,  0.324593F, -0.086936F ),
	VERT( -0.238997F,  0.267931F, -0.071754F ),
	VERT( -0.170672F,  0.222205F, -0.059501F ),
	VERT( -0.170635F,  0.222327F,  0.222311F ),
	VERT( -0.170635F,  0.222327F, -0.222257F ),
	VERT( -0.170635F, -0.222242F, -0.222257F ),
	VERT( -0.170635F, -0.222242F,  0.222311F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_TIRE_RL[]
START
	NORM(  0.000000F,  0.707107F, -0.707107F ),
	NORM( -0.122232F,  0.701805F, -0.701805F ),
	NORM( -0.742699F,  0.473497F, -0.473496F ),
	NORM( -0.916909F, -0.282204F,  0.282205F ),
	NORM( -0.569518F, -0.581228F,  0.581226F ),
	NORM(  0.000000F,  0.258819F, -0.965926F ),
	NORM( -0.122232F,  0.256878F, -0.958683F ),
	NORM( -0.742699F,  0.173312F, -0.646809F ),
	NORM( -0.916910F, -0.103293F,  0.385496F ),
	NORM( -0.569522F, -0.212745F,  0.793967F ),
	NORM(  0.000000F, -0.258819F, -0.965926F ),
	NORM( -0.122231F, -0.256879F, -0.958683F ),
	NORM( -0.742699F, -0.173312F, -0.646809F ),
	NORM( -0.916910F,  0.103293F,  0.385495F ),
	NORM( -0.569525F,  0.212741F,  0.793966F ),
	NORM(  0.000000F, -0.707107F, -0.707107F ),
	NORM( -0.122232F, -0.701805F, -0.701804F ),
	NORM( -0.742699F, -0.473497F, -0.473497F ),
	NORM( -0.916911F,  0.282201F,  0.282201F ),
	NORM( -0.569527F,  0.581222F,  0.581223F ),
	NORM(  0.000000F, -0.965926F, -0.258819F ),
	NORM( -0.122232F, -0.958683F, -0.256878F ),
	NORM( -0.742699F, -0.646808F, -0.173312F ),
	NORM( -0.916911F,  0.385494F,  0.103293F ),
	NORM( -0.569527F,  0.793965F,  0.212742F ),
	NORM(  0.000000F, -0.965926F,  0.258819F ),
	NORM( -0.122232F, -0.958683F,  0.256879F ),
	NORM( -0.742699F, -0.646808F,  0.173312F ),
	NORM( -0.916910F,  0.385495F, -0.103293F ),
	NORM( -0.569525F,  0.793966F, -0.212744F ),
	NORM(  0.000000F, -0.707107F,  0.707107F ),
	NORM( -0.122232F, -0.701804F,  0.701805F ),
	NORM( -0.742699F, -0.473497F,  0.473497F ),
	NORM( -0.916909F,  0.282204F, -0.282203F ),
	NORM( -0.569521F,  0.581224F, -0.581227F ),
	NORM(  0.000000F, -0.258819F,  0.965926F ),
	NORM( -0.122231F, -0.256878F,  0.958683F ),
	NORM( -0.742698F, -0.173312F,  0.646809F ),
	NORM( -0.916909F,  0.103295F, -0.385498F ),
	NORM( -0.569516F,  0.212742F, -0.793972F ),
	NORM(  0.000000F,  0.258819F,  0.965926F ),
	NORM( -0.122231F,  0.256878F,  0.958683F ),
	NORM( -0.742699F,  0.173312F,  0.646809F ),
	NORM( -0.916908F, -0.103294F, -0.385501F ),
	NORM( -0.569513F, -0.212746F, -0.793974F ),
	NORM(  0.000000F,  0.707107F,  0.707107F ),
	NORM( -0.122232F,  0.701804F,  0.701805F ),
	NORM( -0.742699F,  0.473496F,  0.473497F ),
	NORM( -0.916907F, -0.282206F, -0.282206F ),
	NORM( -0.569512F, -0.581230F, -0.581230F ),
	NORM(  0.000000F,  0.965926F,  0.258819F ),
	NORM( -0.122232F,  0.958683F,  0.256878F ),
	NORM( -0.742699F,  0.646808F,  0.173312F ),
	NORM( -0.916907F, -0.385501F, -0.103294F ),
	NORM( -0.569512F, -0.793974F, -0.212746F ),
	NORM(  0.000000F,  0.965926F, -0.258819F ),
	NORM( -0.122232F,  0.958683F, -0.256879F ),
	NORM( -0.742699F,  0.646808F, -0.173312F ),
	NORM( -0.916908F, -0.385500F,  0.103295F ),
	NORM( -0.569514F, -0.793973F,  0.212743F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_TIRE_RL[]
START
Points      point_F40_GTE_sh_null1_1_TIRE_RL,
Normal      normal_F40_GTE_sh_null1_1_TIRE_RL,
PointNum    64,
Meshset     meshset_F40_GTE_sh_null1_1_TIRE_RL,
Materials   matlist_F40_GTE_sh_null1_1_TIRE_RL,
MeshsetNum  4,
MatNum      4,
Center      -0.042491F,  0.000042F,  0.000027F,
Radius       0.475377F,
END

OBJECT      object_F40_GTE_sh_null1_1_TIRE_RL[]
START
EvalFlags ( 0x00000016 ),
Model       model_F40_GTE_sh_null1_1_TIRE_RL,
OPosition  ( -0.785000F,  0.348000F,  1.401900F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_bmerge1,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_TIRE_RR[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 4 ),
AttrFlags ( 0x94a8a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 1 ),
AttrFlags ( 0x94a9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 2 ),
AttrFlags ( 0x94f9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 3 ),
AttrFlags ( 0x94a9a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_TIRE_RR[]
START
	Strip(0x8000, 26),  20, 21, 25, 26, 30, 31, 35, 36, 40, 41, 
			45, 46, 50, 51, 55, 56, 0, 1, 5, 6, 
			10, 11, 15, 16, 20, 21, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_TIRE_RR[]
START
	Strip(0x0, 26),  18, 22, 23, 27, 28, 32, 33, 37, 38, 42, 
			43, 47, 48, 52, 53, 57, 58, 2, 3, 7, 
			8, 12, 13, 17, 18, 22, 
	Strip(0x0, 26),  31, 27, 26, 22, 21, 17, 16, 12, 11, 7, 
			6, 2, 1, 57, 56, 52, 51, 47, 46, 42, 
			41, 37, 36, 32, 31, 27, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_TIRE_RR[]
START
	Strip(0x0, 26),  54, 58, 59, 3, 4, 8, 9, 13, 14, 18, 
			19, 23, 24, 28, 29, 33, 34, 38, 39, 43, 
			44, 48, 49, 53, 54, 58, 
END

POLYGON     pgS_3_F40_GTE_sh_null1_1_TIRE_RR[]
START
	Strip(0x0, 4),  62, 63, 61, 60, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_RR[]
START
	UV( 1062, 0 ),
	UV( 1062, 224 ),
	UV( 981, 0 ),
	UV( 981, 224 ),
	UV( 896, 0 ),
	UV( 896, 224 ),
	UV( 810, 0 ),
	UV( 810, 224 ),
	UV( 725, 0 ),
	UV( 725, 224 ),
	UV( 640, 0 ),
	UV( 640, 224 ),
	UV( 554, 0 ),
	UV( 554, 224 ),
	UV( 469, 0 ),
	UV( 469, 224 ),
	UV( 384, 0 ),
	UV( 384, 224 ),
	UV( 298, 0 ),
	UV( 298, 224 ),
	UV( 213, 0 ),
	UV( 213, 224 ),
	UV( 128, 0 ),
	UV( 128, 224 ),
	UV( 42, 0 ),
	UV( 42, 224 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_RR[]
START
	UV( 193, 193 ),
	UV( 237, 156 ),
	UV( 217, 151 ),
	UV( 237, 97 ),
	UV( 217, 102 ),
	UV( 207, 45 ),
	UV( 193, 59 ),
	UV( 156, 15 ),
	UV( 150, 35 ),
	UV( 96, 15 ),
	UV( 101, 35 ),
	UV( 44, 45 ),
	UV( 59, 59 ),
	UV( 15, 97 ),
	UV( 34, 102 ),
	UV( 15, 156 ),
	UV( 34, 151 ),
	UV( 44, 208 ),
	UV( 59, 193 ),
	UV( 96, 237 ),
	UV( 101, 218 ),
	UV( 156, 237 ),
	UV( 150, 218 ),
	UV( 207, 208 ),
	UV( 193, 193 ),
	UV( 237, 156 ),
	UV( 210, 42 ),
	UV( 237, 97 ),
	UV( 241, 96 ),
	UV( 237, 156 ),
	UV( 241, 157 ),
	UV( 207, 208 ),
	UV( 210, 211 ),
	UV( 156, 237 ),
	UV( 157, 241 ),
	UV( 96, 237 ),
	UV( 95, 241 ),
	UV( 44, 208 ),
	UV( 42, 211 ),
	UV( 15, 156 ),
	UV( 11, 157 ),
	UV( 15, 97 ),
	UV( 11, 96 ),
	UV( 44, 45 ),
	UV( 42, 42 ),
	UV( 96, 15 ),
	UV( 95, 11 ),
	UV( 156, 15 ),
	UV( 157, 11 ),
	UV( 207, 45 ),
	UV( 210, 42 ),
	UV( 237, 97 ),
END

VERTUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_RR[]
START
	UV( 146, 204 ),
	UV( 101, 220 ),
	UV( 106, 204 ),
	UV( 59, 195 ),
	UV( 70, 184 ),
	UV( 34, 153 ),
	UV( 50, 148 ),
	UV( 34, 103 ),
	UV( 50, 108 ),
	UV( 59, 61 ),
	UV( 70, 72 ),
	UV( 101, 36 ),
	UV( 106, 52 ),
	UV( 151, 36 ),
	UV( 146, 52 ),
	UV( 193, 61 ),
	UV( 182, 72 ),
	UV( 218, 103 ),
	UV( 202, 108 ),
	UV( 218, 153 ),
	UV( 202, 148 ),
	UV( 193, 195 ),
	UV( 182, 184 ),
	UV( 151, 220 ),
	UV( 146, 204 ),
	UV( 101, 220 ),
END

VERTUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_RR[]
START
	UV( 221, 223 ),
	UV( 221, 33 ),
	UV( 31, 223 ),
	UV( 31, 33 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_TIRE_RR[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_TIRE_RR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_RR,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_TIRE_RR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_RR,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     1,
Meshes      pgS_2_F40_GTE_sh_null1_1_TIRE_RR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_RR,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 3 ),
MeshNum     1,
Meshes      pgS_3_F40_GTE_sh_null1_1_TIRE_RR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_RR,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_TIRE_RR[]
START
	VERT( -0.154016F, -0.246115F, -0.246046F ),
	VERT(  0.192010F, -0.246115F, -0.246046F ),
	VERT(  0.238995F, -0.237630F, -0.237561F ),
	VERT(  0.238997F, -0.196150F, -0.196083F ),
	VERT(  0.170672F, -0.162677F, -0.162608F ),
	VERT( -0.154016F, -0.090111F, -0.336115F ),
	VERT(  0.192010F, -0.090111F, -0.336115F ),
	VERT(  0.238995F, -0.087005F, -0.324524F ),
	VERT(  0.238997F, -0.071822F, -0.267863F ),
	VERT(  0.170672F, -0.059571F, -0.222136F ),
	VERT( -0.154016F,  0.090027F, -0.336115F ),
	VERT(  0.192010F,  0.090027F, -0.336115F ),
	VERT(  0.238995F,  0.086921F, -0.324524F ),
	VERT(  0.238997F,  0.071740F, -0.267863F ),
	VERT(  0.170672F,  0.059486F, -0.222136F ),
	VERT( -0.154016F,  0.246031F, -0.246046F ),
	VERT(  0.192010F,  0.246031F, -0.246046F ),
	VERT(  0.238995F,  0.237546F, -0.237561F ),
	VERT(  0.238997F,  0.196068F, -0.196083F ),
	VERT(  0.170672F,  0.162592F, -0.162608F ),
	VERT( -0.154016F,  0.336100F, -0.090042F ),
	VERT(  0.192010F,  0.336100F, -0.090042F ),
	VERT(  0.238995F,  0.324509F, -0.086936F ),
	VERT(  0.238997F,  0.267849F, -0.071754F ),
	VERT(  0.170672F,  0.222121F, -0.059501F ),
	VERT( -0.154016F,  0.336100F,  0.090096F ),
	VERT(  0.192010F,  0.336100F,  0.090096F ),
	VERT(  0.238995F,  0.324509F,  0.086990F ),
	VERT(  0.238997F,  0.267849F,  0.071807F ),
	VERT(  0.170672F,  0.222121F,  0.059555F ),
	VERT( -0.154016F,  0.246031F,  0.246100F ),
	VERT(  0.192010F,  0.246031F,  0.246100F ),
	VERT(  0.238995F,  0.237546F,  0.237615F ),
	VERT(  0.238997F,  0.196068F,  0.196135F ),
	VERT(  0.170672F,  0.162592F,  0.162662F ),
	VERT( -0.154016F,  0.090027F,  0.336169F ),
	VERT(  0.192010F,  0.090027F,  0.336169F ),
	VERT(  0.238995F,  0.086921F,  0.324578F ),
	VERT(  0.238997F,  0.071740F,  0.267916F ),
	VERT(  0.170672F,  0.059486F,  0.222190F ),
	VERT( -0.154016F, -0.090111F,  0.336169F ),
	VERT(  0.192010F, -0.090111F,  0.336169F ),
	VERT(  0.238995F, -0.087005F,  0.324578F ),
	VERT(  0.238997F, -0.071822F,  0.267916F ),
	VERT(  0.170672F, -0.059571F,  0.222190F ),
	VERT( -0.154016F, -0.246115F,  0.246100F ),
	VERT(  0.192010F, -0.246115F,  0.246100F ),
	VERT(  0.238995F, -0.237630F,  0.237615F ),
	VERT(  0.238997F, -0.196150F,  0.196135F ),
	VERT(  0.170672F, -0.162677F,  0.162661F ),
	VERT( -0.154016F, -0.336184F,  0.090096F ),
	VERT(  0.192010F, -0.336184F,  0.090096F ),
	VERT(  0.238995F, -0.324593F,  0.086990F ),
	VERT(  0.238997F, -0.267931F,  0.071807F ),
	VERT(  0.170672F, -0.222205F,  0.059555F ),
	VERT( -0.154016F, -0.336184F, -0.090042F ),
	VERT(  0.192010F, -0.336184F, -0.090042F ),
	VERT(  0.238995F, -0.324593F, -0.086936F ),
	VERT(  0.238997F, -0.267931F, -0.071754F ),
	VERT(  0.170672F, -0.222205F, -0.059501F ),
	VERT(  0.170635F, -0.222327F,  0.222311F ),
	VERT(  0.170635F, -0.222327F, -0.222257F ),
	VERT(  0.170635F,  0.222242F, -0.222257F ),
	VERT(  0.170635F,  0.222242F,  0.222311F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_TIRE_RR[]
START
	NORM(  0.000000F, -0.707107F, -0.707107F ),
	NORM(  0.122232F, -0.701805F, -0.701805F ),
	NORM(  0.742699F, -0.473497F, -0.473496F ),
	NORM(  0.916909F,  0.282204F,  0.282205F ),
	NORM(  0.569518F,  0.581228F,  0.581226F ),
	NORM(  0.000000F, -0.258819F, -0.965926F ),
	NORM(  0.122232F, -0.256878F, -0.958683F ),
	NORM(  0.742699F, -0.173312F, -0.646809F ),
	NORM(  0.916910F,  0.103293F,  0.385496F ),
	NORM(  0.569522F,  0.212745F,  0.793967F ),
	NORM(  0.000000F,  0.258819F, -0.965926F ),
	NORM(  0.122231F,  0.256879F, -0.958683F ),
	NORM(  0.742699F,  0.173312F, -0.646809F ),
	NORM(  0.916910F, -0.103293F,  0.385494F ),
	NORM(  0.569525F, -0.212741F,  0.793966F ),
	NORM(  0.000000F,  0.707107F, -0.707107F ),
	NORM(  0.122232F,  0.701805F, -0.701804F ),
	NORM(  0.742699F,  0.473497F, -0.473497F ),
	NORM(  0.916911F, -0.282201F,  0.282201F ),
	NORM(  0.569527F, -0.581222F,  0.581223F ),
	NORM(  0.000000F,  0.965926F, -0.258819F ),
	NORM(  0.122232F,  0.958683F, -0.256878F ),
	NORM(  0.742699F,  0.646808F, -0.173312F ),
	NORM(  0.916911F, -0.385494F,  0.103293F ),
	NORM(  0.569527F, -0.793965F,  0.212742F ),
	NORM(  0.000000F,  0.965926F,  0.258819F ),
	NORM(  0.122232F,  0.958683F,  0.256879F ),
	NORM(  0.742699F,  0.646808F,  0.173312F ),
	NORM(  0.916910F, -0.385495F, -0.103293F ),
	NORM(  0.569525F, -0.793966F, -0.212744F ),
	NORM(  0.000000F,  0.707106F,  0.707107F ),
	NORM(  0.122231F,  0.701804F,  0.701805F ),
	NORM(  0.742699F,  0.473497F,  0.473497F ),
	NORM(  0.916909F, -0.282204F, -0.282203F ),
	NORM(  0.569521F, -0.581224F, -0.581227F ),
	NORM(  0.000000F,  0.258819F,  0.965926F ),
	NORM(  0.122231F,  0.256878F,  0.958683F ),
	NORM(  0.742698F,  0.173312F,  0.646809F ),
	NORM(  0.916909F, -0.103294F, -0.385498F ),
	NORM(  0.569517F, -0.212742F, -0.793972F ),
	NORM(  0.000000F, -0.258819F,  0.965926F ),
	NORM(  0.122231F, -0.256878F,  0.958683F ),
	NORM(  0.742699F, -0.173312F,  0.646809F ),
	NORM(  0.916908F,  0.103294F, -0.385501F ),
	NORM(  0.569513F,  0.212746F, -0.793974F ),
	NORM(  0.000000F, -0.707107F,  0.707107F ),
	NORM(  0.122232F, -0.701804F,  0.701805F ),
	NORM(  0.742699F, -0.473496F,  0.473497F ),
	NORM(  0.916907F,  0.282206F, -0.282206F ),
	NORM(  0.569512F,  0.581230F, -0.581230F ),
	NORM(  0.000000F, -0.965926F,  0.258819F ),
	NORM(  0.122232F, -0.958683F,  0.256878F ),
	NORM(  0.742699F, -0.646808F,  0.173311F ),
	NORM(  0.916907F,  0.385501F, -0.103294F ),
	NORM(  0.569512F,  0.793974F, -0.212746F ),
	NORM(  0.000000F, -0.965926F, -0.258819F ),
	NORM(  0.122232F, -0.958683F, -0.256879F ),
	NORM(  0.742699F, -0.646808F, -0.173312F ),
	NORM(  0.916908F,  0.385500F,  0.103295F ),
	NORM(  0.569514F,  0.793974F,  0.212743F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_TIRE_RR[]
START
Points      point_F40_GTE_sh_null1_1_TIRE_RR,
Normal      normal_F40_GTE_sh_null1_1_TIRE_RR,
PointNum    64,
Meshset     meshset_F40_GTE_sh_null1_1_TIRE_RR,
Materials   matlist_F40_GTE_sh_null1_1_TIRE_RR,
MeshsetNum  4,
MatNum      4,
Center       0.042491F, -0.000042F,  0.000027F,
Radius       0.475377F,
END

OBJECT      object_F40_GTE_sh_null1_1_TIRE_RR[]
START
EvalFlags ( 0x00000016 ),
Model       model_F40_GTE_sh_null1_1_TIRE_RR,
OPosition  (  0.785000F,  0.348000F,  1.401900F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_TIRE_RL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_TIRE_FL[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94a9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 1 ),
AttrFlags ( 0x94a9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 2 ),
AttrFlags ( 0x94f9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 3 ),
AttrFlags ( 0x94a9a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_TIRE_FL[]
START
	Strip(0x8000, 26),  20, 21, 25, 26, 30, 31, 35, 36, 40, 41, 
			45, 46, 50, 51, 55, 56, 0, 1, 5, 6, 
			10, 11, 15, 16, 20, 21, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_TIRE_FL[]
START
	Strip(0x0, 26),  16, 12, 11, 7, 6, 2, 1, 57, 56, 52, 
			51, 47, 46, 42, 41, 37, 36, 32, 31, 27, 
			26, 22, 21, 17, 16, 12, 
	Strip(0x0, 26),  13, 17, 18, 22, 23, 27, 28, 32, 33, 37, 
			38, 42, 43, 47, 48, 52, 53, 57, 58, 2, 
			3, 7, 8, 12, 13, 17, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_TIRE_FL[]
START
	Strip(0x0, 26),  59, 3, 4, 8, 9, 13, 14, 18, 19, 23, 
			24, 28, 29, 33, 34, 38, 39, 43, 44, 48, 
			49, 53, 54, 58, 59, 3, 
END

POLYGON     pgS_3_F40_GTE_sh_null1_1_TIRE_FL[]
START
	Strip(0x0, 4),  62, 63, 61, 60, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_FL[]
START
	UV( 132, 24 ),
	UV( 132, 237 ),
	UV( 122, 24 ),
	UV( 122, 237 ),
	UV( 111, 24 ),
	UV( 111, 237 ),
	UV( 100, 24 ),
	UV( 100, 237 ),
	UV( 90, 24 ),
	UV( 90, 237 ),
	UV( 79, 24 ),
	UV( 79, 237 ),
	UV( 68, 24 ),
	UV( 68, 237 ),
	UV( 58, 24 ),
	UV( 58, 237 ),
	UV( 47, 24 ),
	UV( 47, 237 ),
	UV( 37, 24 ),
	UV( 37, 237 ),
	UV( 26, 24 ),
	UV( 26, 237 ),
	UV( 15, 24 ),
	UV( 15, 237 ),
	UV( 5, 24 ),
	UV( 5, 237 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_FL[]
START
	UV( 42, 211 ),
	UV( 96, 238 ),
	UV( 95, 241 ),
	UV( 156, 238 ),
	UV( 157, 241 ),
	UV( 207, 208 ),
	UV( 210, 211 ),
	UV( 237, 156 ),
	UV( 241, 157 ),
	UV( 237, 97 ),
	UV( 241, 96 ),
	UV( 207, 45 ),
	UV( 210, 42 ),
	UV( 156, 15 ),
	UV( 157, 11 ),
	UV( 96, 15 ),
	UV( 95, 11 ),
	UV( 44, 45 ),
	UV( 42, 42 ),
	UV( 15, 97 ),
	UV( 11, 96 ),
	UV( 15, 156 ),
	UV( 11, 157 ),
	UV( 44, 208 ),
	UV( 42, 211 ),
	UV( 96, 238 ),
	UV( 101, 218 ),
	UV( 44, 208 ),
	UV( 59, 194 ),
	UV( 15, 156 ),
	UV( 34, 151 ),
	UV( 15, 97 ),
	UV( 34, 102 ),
	UV( 44, 45 ),
	UV( 59, 59 ),
	UV( 96, 15 ),
	UV( 101, 35 ),
	UV( 156, 15 ),
	UV( 150, 35 ),
	UV( 207, 45 ),
	UV( 193, 59 ),
	UV( 237, 97 ),
	UV( 218, 102 ),
	UV( 237, 156 ),
	UV( 218, 151 ),
	UV( 207, 208 ),
	UV( 193, 194 ),
	UV( 156, 238 ),
	UV( 150, 218 ),
	UV( 96, 238 ),
	UV( 101, 218 ),
	UV( 44, 208 ),
END

VERTUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_FL[]
START
	UV( 106, 52 ),
	UV( 59, 61 ),
	UV( 70, 72 ),
	UV( 34, 103 ),
	UV( 50, 108 ),
	UV( 34, 153 ),
	UV( 50, 148 ),
	UV( 59, 195 ),
	UV( 70, 184 ),
	UV( 101, 220 ),
	UV( 106, 204 ),
	UV( 151, 220 ),
	UV( 146, 204 ),
	UV( 193, 195 ),
	UV( 182, 184 ),
	UV( 218, 153 ),
	UV( 202, 148 ),
	UV( 218, 103 ),
	UV( 202, 108 ),
	UV( 193, 61 ),
	UV( 182, 72 ),
	UV( 151, 36 ),
	UV( 146, 52 ),
	UV( 101, 36 ),
	UV( 106, 52 ),
	UV( 59, 61 ),
END

VERTUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_FL[]
START
	UV( 42, 44 ),
	UV( 210, 44 ),
	UV( 42, 212 ),
	UV( 210, 212 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_TIRE_FL[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_TIRE_FL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_FL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_TIRE_FL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_FL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     1,
Meshes      pgS_2_F40_GTE_sh_null1_1_TIRE_FL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_FL,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 3 ),
MeshNum     1,
Meshes      pgS_3_F40_GTE_sh_null1_1_TIRE_FL,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_FL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_TIRE_FL[]
START
	VERT(  0.050680F,  0.224365F, -0.224365F ),
	VERT( -0.183989F,  0.224365F, -0.224365F ),
	VERT( -0.229008F,  0.216940F, -0.216940F ),
	VERT( -0.229005F,  0.179062F, -0.179062F ),
	VERT( -0.162638F,  0.148492F, -0.148492F ),
	VERT(  0.050680F,  0.082123F, -0.306488F ),
	VERT( -0.183988F,  0.082123F, -0.306488F ),
	VERT( -0.229008F,  0.079406F, -0.296346F ),
	VERT( -0.229005F,  0.065541F, -0.244603F ),
	VERT( -0.162638F,  0.054352F, -0.202844F ),
	VERT(  0.050680F, -0.082123F, -0.306488F ),
	VERT( -0.183988F, -0.082123F, -0.306488F ),
	VERT( -0.229008F, -0.079406F, -0.296346F ),
	VERT( -0.229005F, -0.065541F, -0.244603F ),
	VERT( -0.162638F, -0.054352F, -0.202844F ),
	VERT(  0.050680F, -0.224365F, -0.224365F ),
	VERT( -0.183988F, -0.224365F, -0.224365F ),
	VERT( -0.229008F, -0.216940F, -0.216940F ),
	VERT( -0.229004F, -0.179062F, -0.179062F ),
	VERT( -0.162638F, -0.148492F, -0.148492F ),
	VERT(  0.050680F, -0.306488F, -0.082123F ),
	VERT( -0.183988F, -0.306488F, -0.082123F ),
	VERT( -0.229008F, -0.296346F, -0.079406F ),
	VERT( -0.229004F, -0.244603F, -0.065541F ),
	VERT( -0.162638F, -0.202844F, -0.054352F ),
	VERT(  0.050680F, -0.306488F,  0.082123F ),
	VERT( -0.183988F, -0.306488F,  0.082123F ),
	VERT( -0.229008F, -0.296346F,  0.079406F ),
	VERT( -0.229004F, -0.244603F,  0.065541F ),
	VERT( -0.162638F, -0.202844F,  0.054352F ),
	VERT(  0.050680F, -0.224365F,  0.224365F ),
	VERT( -0.183988F, -0.224365F,  0.224365F ),
	VERT( -0.229008F, -0.216940F,  0.216940F ),
	VERT( -0.229004F, -0.179062F,  0.179062F ),
	VERT( -0.162638F, -0.148492F,  0.148492F ),
	VERT(  0.050680F, -0.082123F,  0.306488F ),
	VERT( -0.183988F, -0.082123F,  0.306488F ),
	VERT( -0.229008F, -0.079406F,  0.296346F ),
	VERT( -0.229005F, -0.065541F,  0.244603F ),
	VERT( -0.162638F, -0.054352F,  0.202844F ),
	VERT(  0.050680F,  0.082123F,  0.306488F ),
	VERT( -0.183988F,  0.082123F,  0.306488F ),
	VERT( -0.229008F,  0.079406F,  0.296346F ),
	VERT( -0.229005F,  0.065541F,  0.244603F ),
	VERT( -0.162638F,  0.054352F,  0.202844F ),
	VERT(  0.050680F,  0.224365F,  0.224365F ),
	VERT( -0.183989F,  0.224365F,  0.224365F ),
	VERT( -0.229008F,  0.216940F,  0.216940F ),
	VERT( -0.229005F,  0.179062F,  0.179062F ),
	VERT( -0.162638F,  0.148492F,  0.148492F ),
	VERT(  0.050680F,  0.306488F,  0.082123F ),
	VERT( -0.183989F,  0.306488F,  0.082123F ),
	VERT( -0.229008F,  0.296346F,  0.079406F ),
	VERT( -0.229005F,  0.244603F,  0.065541F ),
	VERT( -0.162638F,  0.202844F,  0.054352F ),
	VERT(  0.050680F,  0.306488F, -0.082123F ),
	VERT( -0.183989F,  0.306488F, -0.082123F ),
	VERT( -0.229008F,  0.296346F, -0.079406F ),
	VERT( -0.229005F,  0.244603F, -0.065541F ),
	VERT( -0.162638F,  0.202844F, -0.054352F ),
	VERT( -0.162612F,  0.203544F,  0.203544F ),
	VERT( -0.162612F,  0.203544F, -0.203544F ),
	VERT( -0.162612F, -0.203544F, -0.203544F ),
	VERT( -0.162612F, -0.203544F,  0.203544F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_TIRE_FL[]
START
	NORM(  0.000000F,  0.707107F, -0.707107F ),
	NORM( -0.112235F,  0.702639F, -0.702639F ),
	NORM( -0.735547F,  0.479046F, -0.479046F ),
	NORM( -0.911752F, -0.290438F,  0.290438F ),
	NORM( -0.545819F, -0.592487F,  0.592487F ),
	NORM(  0.000000F,  0.258819F, -0.965926F ),
	NORM( -0.112235F,  0.257184F, -0.959823F ),
	NORM( -0.735547F,  0.175343F, -0.654390F ),
	NORM( -0.911752F, -0.106308F,  0.396746F ),
	NORM( -0.545819F, -0.216865F,  0.809352F ),
	NORM(  0.000000F, -0.258819F, -0.965926F ),
	NORM( -0.112235F, -0.257184F, -0.959823F ),
	NORM( -0.735547F, -0.175343F, -0.654389F ),
	NORM( -0.911752F,  0.106307F,  0.396746F ),
	NORM( -0.545819F,  0.216865F,  0.809352F ),
	NORM(  0.000000F, -0.707107F, -0.707107F ),
	NORM( -0.112235F, -0.702639F, -0.702639F ),
	NORM( -0.735547F, -0.479047F, -0.479046F ),
	NORM( -0.911752F,  0.290438F,  0.290438F ),
	NORM( -0.545819F,  0.592487F,  0.592487F ),
	NORM(  0.000000F, -0.965926F, -0.258819F ),
	NORM( -0.112235F, -0.959823F, -0.257183F ),
	NORM( -0.735547F, -0.654390F, -0.175343F ),
	NORM( -0.911752F,  0.396745F,  0.106308F ),
	NORM( -0.545820F,  0.809352F,  0.216865F ),
	NORM(  0.000000F, -0.965926F,  0.258819F ),
	NORM( -0.112235F, -0.959823F,  0.257184F ),
	NORM( -0.735547F, -0.654390F,  0.175343F ),
	NORM( -0.911752F,  0.396745F, -0.106308F ),
	NORM( -0.545820F,  0.809352F, -0.216865F ),
	NORM(  0.000000F, -0.707107F,  0.707107F ),
	NORM( -0.112235F, -0.702639F,  0.702639F ),
	NORM( -0.735547F, -0.479046F,  0.479046F ),
	NORM( -0.911752F,  0.290438F, -0.290438F ),
	NORM( -0.545820F,  0.592487F, -0.592487F ),
	NORM(  0.000000F, -0.258819F,  0.965926F ),
	NORM( -0.112236F, -0.257184F,  0.959823F ),
	NORM( -0.735547F, -0.175343F,  0.654389F ),
	NORM( -0.911752F,  0.106307F, -0.396746F ),
	NORM( -0.545819F,  0.216865F, -0.809352F ),
	NORM(  0.000000F,  0.258819F,  0.965926F ),
	NORM( -0.112236F,  0.257184F,  0.959823F ),
	NORM( -0.735547F,  0.175343F,  0.654389F ),
	NORM( -0.911752F, -0.106308F, -0.396746F ),
	NORM( -0.545819F, -0.216865F, -0.809352F ),
	NORM(  0.000000F,  0.707107F,  0.707107F ),
	NORM( -0.112236F,  0.702639F,  0.702639F ),
	NORM( -0.735547F,  0.479046F,  0.479046F ),
	NORM( -0.911752F, -0.290438F, -0.290438F ),
	NORM( -0.545819F, -0.592487F, -0.592487F ),
	NORM(  0.000000F,  0.965926F,  0.258819F ),
	NORM( -0.112236F,  0.959823F,  0.257184F ),
	NORM( -0.735547F,  0.654389F,  0.175343F ),
	NORM( -0.911752F, -0.396746F, -0.106308F ),
	NORM( -0.545818F, -0.809353F, -0.216865F ),
	NORM(  0.000000F,  0.965926F, -0.258819F ),
	NORM( -0.112236F,  0.959823F, -0.257184F ),
	NORM( -0.735547F,  0.654389F, -0.175343F ),
	NORM( -0.911752F, -0.396746F,  0.106308F ),
	NORM( -0.545818F, -0.809353F,  0.216865F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
	NORM( -1.000000F,  0.000000F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_TIRE_FL[]
START
Points      point_F40_GTE_sh_null1_1_TIRE_FL,
Normal      normal_F40_GTE_sh_null1_1_TIRE_FL,
PointNum    64,
Meshset     meshset_F40_GTE_sh_null1_1_TIRE_FL,
Materials   matlist_F40_GTE_sh_null1_1_TIRE_FL,
MeshsetNum  4,
MatNum      4,
Center      -0.089164F,  0.000000F,  0.000000F,
Radius       0.433440F,
END

OBJECT      object_F40_GTE_sh_null1_1_TIRE_FL[]
START
EvalFlags ( 0x00000016 ),
Model       model_F40_GTE_sh_null1_1_TIRE_FL,
OPosition  ( -0.735000F,  0.317300F, -1.164300F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_TIRE_RR,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_TIRE_FR[]
START

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x94a9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 1 ),
AttrFlags ( 0x94a9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 2 ),
AttrFlags ( 0x94f9a400 ),
MATEND

MATSTART
Diffuse   ( 255, 255, 255, 255 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 3 ),
AttrFlags ( 0x94a9a400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_TIRE_FR[]
START
	Strip(0x8000, 26),  20, 21, 25, 26, 30, 31, 35, 36, 40, 41, 
			45, 46, 50, 51, 55, 56, 0, 1, 5, 6, 
			10, 11, 15, 16, 20, 21, 
END

POLYGON     pgS_1_F40_GTE_sh_null1_1_TIRE_FR[]
START
	Strip(0x0, 26),  13, 17, 18, 22, 23, 27, 28, 32, 33, 37, 
			38, 42, 43, 47, 48, 52, 53, 57, 58, 2, 
			3, 7, 8, 12, 13, 17, 
	Strip(0x0, 26),  56, 52, 51, 47, 46, 42, 41, 37, 36, 32, 
			31, 27, 26, 22, 21, 17, 16, 12, 11, 7, 
			6, 2, 1, 57, 56, 52, 
END

POLYGON     pgS_2_F40_GTE_sh_null1_1_TIRE_FR[]
START
	Strip(0x0, 26),  59, 3, 4, 8, 9, 13, 14, 18, 19, 23, 
			24, 28, 29, 33, 34, 38, 39, 43, 44, 48, 
			49, 53, 54, 58, 59, 3, 
END

POLYGON     pgS_3_F40_GTE_sh_null1_1_TIRE_FR[]
START
	Strip(0x0, 4),  62, 63, 61, 60, 
END

VERTUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_FR[]
START
	UV( 132, 24 ),
	UV( 132, 237 ),
	UV( 122, 24 ),
	UV( 122, 237 ),
	UV( 111, 24 ),
	UV( 111, 237 ),
	UV( 100, 24 ),
	UV( 100, 237 ),
	UV( 90, 24 ),
	UV( 90, 237 ),
	UV( 79, 24 ),
	UV( 79, 237 ),
	UV( 68, 24 ),
	UV( 68, 237 ),
	UV( 58, 24 ),
	UV( 58, 237 ),
	UV( 47, 24 ),
	UV( 47, 237 ),
	UV( 37, 24 ),
	UV( 37, 237 ),
	UV( 26, 24 ),
	UV( 26, 237 ),
	UV( 15, 24 ),
	UV( 15, 237 ),
	UV( 5, 24 ),
	UV( 5, 237 ),
END

VERTUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_FR[]
START
	UV( 150, 218 ),
	UV( 207, 208 ),
	UV( 193, 194 ),
	UV( 237, 156 ),
	UV( 218, 151 ),
	UV( 237, 97 ),
	UV( 218, 102 ),
	UV( 207, 45 ),
	UV( 193, 59 ),
	UV( 156, 15 ),
	UV( 150, 35 ),
	UV( 96, 15 ),
	UV( 101, 35 ),
	UV( 44, 45 ),
	UV( 59, 59 ),
	UV( 15, 97 ),
	UV( 34, 102 ),
	UV( 15, 156 ),
	UV( 34, 151 ),
	UV( 44, 208 ),
	UV( 59, 194 ),
	UV( 96, 238 ),
	UV( 101, 218 ),
	UV( 156, 238 ),
	UV( 150, 218 ),
	UV( 207, 208 ),
	UV( 11, 157 ),
	UV( 15, 97 ),
	UV( 11, 96 ),
	UV( 44, 45 ),
	UV( 42, 42 ),
	UV( 96, 15 ),
	UV( 95, 11 ),
	UV( 156, 15 ),
	UV( 157, 11 ),
	UV( 207, 45 ),
	UV( 210, 42 ),
	UV( 237, 97 ),
	UV( 241, 96 ),
	UV( 237, 156 ),
	UV( 241, 157 ),
	UV( 207, 208 ),
	UV( 210, 211 ),
	UV( 156, 238 ),
	UV( 157, 241 ),
	UV( 96, 238 ),
	UV( 95, 241 ),
	UV( 44, 208 ),
	UV( 42, 211 ),
	UV( 15, 156 ),
	UV( 11, 157 ),
	UV( 15, 97 ),
END

VERTUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_FR[]
START
	UV( 106, 204 ),
	UV( 59, 195 ),
	UV( 70, 184 ),
	UV( 34, 153 ),
	UV( 50, 148 ),
	UV( 34, 103 ),
	UV( 50, 108 ),
	UV( 59, 61 ),
	UV( 70, 72 ),
	UV( 101, 36 ),
	UV( 106, 52 ),
	UV( 151, 36 ),
	UV( 146, 52 ),
	UV( 193, 61 ),
	UV( 182, 72 ),
	UV( 218, 103 ),
	UV( 202, 108 ),
	UV( 218, 153 ),
	UV( 202, 148 ),
	UV( 193, 195 ),
	UV( 182, 184 ),
	UV( 151, 220 ),
	UV( 146, 204 ),
	UV( 101, 220 ),
	UV( 106, 204 ),
	UV( 59, 195 ),
END

VERTUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_FR[]
START
	UV( 221, 223 ),
	UV( 221, 33 ),
	UV( 31, 223 ),
	UV( 31, 33 ),
END

MESHSET     meshset_F40_GTE_sh_null1_1_TIRE_FR[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_TIRE_FR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_0_F40_GTE_sh_null1_1_TIRE_FR,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 1 ),
MeshNum     2,
Meshes      pgS_1_F40_GTE_sh_null1_1_TIRE_FR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_1_F40_GTE_sh_null1_1_TIRE_FR,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 2 ),
MeshNum     1,
Meshes      pgS_2_F40_GTE_sh_null1_1_TIRE_FR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_2_F40_GTE_sh_null1_1_TIRE_FR,
MESHEND

MESHSTART
TypeMatId ( 0xc000, 3 ),
MeshNum     1,
Meshes      pgS_3_F40_GTE_sh_null1_1_TIRE_FR,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      vuvS_3_F40_GTE_sh_null1_1_TIRE_FR,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_TIRE_FR[]
START
	VERT( -0.050680F, -0.224365F, -0.224365F ),
	VERT(  0.183988F, -0.224365F, -0.224365F ),
	VERT(  0.229008F, -0.216940F, -0.216940F ),
	VERT(  0.229005F, -0.179062F, -0.179062F ),
	VERT(  0.162638F, -0.148492F, -0.148492F ),
	VERT( -0.050680F, -0.082123F, -0.306488F ),
	VERT(  0.183988F, -0.082123F, -0.306488F ),
	VERT(  0.229008F, -0.079406F, -0.296346F ),
	VERT(  0.229005F, -0.065541F, -0.244603F ),
	VERT(  0.162638F, -0.054352F, -0.202844F ),
	VERT( -0.050680F,  0.082123F, -0.306488F ),
	VERT(  0.183988F,  0.082123F, -0.306488F ),
	VERT(  0.229008F,  0.079406F, -0.296346F ),
	VERT(  0.229005F,  0.065541F, -0.244603F ),
	VERT(  0.162638F,  0.054352F, -0.202844F ),
	VERT( -0.050680F,  0.224365F, -0.224365F ),
	VERT(  0.183988F,  0.224365F, -0.224365F ),
	VERT(  0.229008F,  0.216940F, -0.216940F ),
	VERT(  0.229004F,  0.179062F, -0.179062F ),
	VERT(  0.162638F,  0.148492F, -0.148492F ),
	VERT( -0.050680F,  0.306488F, -0.082123F ),
	VERT(  0.183988F,  0.306488F, -0.082123F ),
	VERT(  0.229008F,  0.296346F, -0.079406F ),
	VERT(  0.229004F,  0.244603F, -0.065541F ),
	VERT(  0.162638F,  0.202844F, -0.054352F ),
	VERT( -0.050680F,  0.306488F,  0.082123F ),
	VERT(  0.183988F,  0.306488F,  0.082123F ),
	VERT(  0.229008F,  0.296346F,  0.079406F ),
	VERT(  0.229004F,  0.244603F,  0.065541F ),
	VERT(  0.162638F,  0.202844F,  0.054352F ),
	VERT( -0.050680F,  0.224365F,  0.224365F ),
	VERT(  0.183988F,  0.224365F,  0.224365F ),
	VERT(  0.229008F,  0.216940F,  0.216940F ),
	VERT(  0.229004F,  0.179062F,  0.179062F ),
	VERT(  0.162638F,  0.148492F,  0.148492F ),
	VERT( -0.050680F,  0.082123F,  0.306488F ),
	VERT(  0.183988F,  0.082123F,  0.306488F ),
	VERT(  0.229008F,  0.079406F,  0.296346F ),
	VERT(  0.229005F,  0.065541F,  0.244603F ),
	VERT(  0.162638F,  0.054352F,  0.202844F ),
	VERT( -0.050680F, -0.082123F,  0.306488F ),
	VERT(  0.183988F, -0.082123F,  0.306488F ),
	VERT(  0.229008F, -0.079406F,  0.296346F ),
	VERT(  0.229005F, -0.065541F,  0.244603F ),
	VERT(  0.162638F, -0.054352F,  0.202844F ),
	VERT( -0.050680F, -0.224365F,  0.224365F ),
	VERT(  0.183988F, -0.224365F,  0.224365F ),
	VERT(  0.229008F, -0.216940F,  0.216940F ),
	VERT(  0.229005F, -0.179062F,  0.179062F ),
	VERT(  0.162638F, -0.148492F,  0.148492F ),
	VERT( -0.050680F, -0.306488F,  0.082123F ),
	VERT(  0.183988F, -0.306488F,  0.082123F ),
	VERT(  0.229008F, -0.296346F,  0.079406F ),
	VERT(  0.229005F, -0.244603F,  0.065541F ),
	VERT(  0.162638F, -0.202844F,  0.054352F ),
	VERT( -0.050680F, -0.306488F, -0.082123F ),
	VERT(  0.183988F, -0.306488F, -0.082123F ),
	VERT(  0.229008F, -0.296346F, -0.079406F ),
	VERT(  0.229005F, -0.244603F, -0.065541F ),
	VERT(  0.162638F, -0.202844F, -0.054352F ),
	VERT(  0.162612F, -0.203544F,  0.203544F ),
	VERT(  0.162612F, -0.203544F, -0.203544F ),
	VERT(  0.162612F,  0.203544F, -0.203544F ),
	VERT(  0.162612F,  0.203544F,  0.203544F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_TIRE_FR[]
START
	NORM(  0.000000F, -0.707107F, -0.707107F ),
	NORM(  0.112235F, -0.702639F, -0.702639F ),
	NORM(  0.735547F, -0.479046F, -0.479046F ),
	NORM(  0.911752F,  0.290438F,  0.290438F ),
	NORM(  0.545819F,  0.592487F,  0.592487F ),
	NORM(  0.000000F, -0.258819F, -0.965926F ),
	NORM(  0.112235F, -0.257184F, -0.959823F ),
	NORM(  0.735547F, -0.175343F, -0.654390F ),
	NORM(  0.911752F,  0.106308F,  0.396746F ),
	NORM(  0.545819F,  0.216865F,  0.809352F ),
	NORM(  0.000000F,  0.258819F, -0.965926F ),
	NORM(  0.112235F,  0.257184F, -0.959823F ),
	NORM(  0.735547F,  0.175343F, -0.654389F ),
	NORM(  0.911752F, -0.106307F,  0.396746F ),
	NORM(  0.545819F, -0.216865F,  0.809352F ),
	NORM(  0.000000F,  0.707107F, -0.707107F ),
	NORM(  0.112235F,  0.702639F, -0.702639F ),
	NORM(  0.735547F,  0.479047F, -0.479046F ),
	NORM(  0.911752F, -0.290438F,  0.290438F ),
	NORM(  0.545820F, -0.592487F,  0.592487F ),
	NORM(  0.000000F,  0.965926F, -0.258819F ),
	NORM(  0.112235F,  0.959823F, -0.257183F ),
	NORM(  0.735547F,  0.654390F, -0.175343F ),
	NORM(  0.911752F, -0.396745F,  0.106308F ),
	NORM(  0.545820F, -0.809352F,  0.216865F ),
	NORM(  0.000000F,  0.965926F,  0.258819F ),
	NORM(  0.112235F,  0.959823F,  0.257184F ),
	NORM(  0.735547F,  0.654390F,  0.175343F ),
	NORM(  0.911752F, -0.396745F, -0.106308F ),
	NORM(  0.545820F, -0.809352F, -0.216865F ),
	NORM(  0.000000F,  0.707107F,  0.707107F ),
	NORM(  0.112235F,  0.702639F,  0.702639F ),
	NORM(  0.735547F,  0.479046F,  0.479046F ),
	NORM(  0.911752F, -0.290438F, -0.290438F ),
	NORM(  0.545820F, -0.592487F, -0.592487F ),
	NORM(  0.000000F,  0.258819F,  0.965926F ),
	NORM(  0.112236F,  0.257184F,  0.959823F ),
	NORM(  0.735547F,  0.175343F,  0.654389F ),
	NORM(  0.911752F, -0.106308F, -0.396746F ),
	NORM(  0.545819F, -0.216865F, -0.809352F ),
	NORM(  0.000000F, -0.258819F,  0.965926F ),
	NORM(  0.112236F, -0.257184F,  0.959823F ),
	NORM(  0.735547F, -0.175343F,  0.654389F ),
	NORM(  0.911752F,  0.106308F, -0.396746F ),
	NORM(  0.545819F,  0.216865F, -0.809352F ),
	NORM(  0.000000F, -0.707107F,  0.707107F ),
	NORM(  0.112236F, -0.702639F,  0.702639F ),
	NORM(  0.735547F, -0.479046F,  0.479046F ),
	NORM(  0.911752F,  0.290438F, -0.290438F ),
	NORM(  0.545818F,  0.592487F, -0.592487F ),
	NORM(  0.000000F, -0.965926F,  0.258819F ),
	NORM(  0.112236F, -0.959823F,  0.257184F ),
	NORM(  0.735547F, -0.654389F,  0.175343F ),
	NORM(  0.911752F,  0.396746F, -0.106308F ),
	NORM(  0.545818F,  0.809353F, -0.216865F ),
	NORM(  0.000000F, -0.965926F, -0.258819F ),
	NORM(  0.112236F, -0.959823F, -0.257184F ),
	NORM(  0.735547F, -0.654389F, -0.175343F ),
	NORM(  0.911752F,  0.396746F,  0.106308F ),
	NORM(  0.545818F,  0.809353F,  0.216865F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
	NORM(  1.000000F,  0.000000F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_TIRE_FR[]
START
Points      point_F40_GTE_sh_null1_1_TIRE_FR,
Normal      normal_F40_GTE_sh_null1_1_TIRE_FR,
PointNum    64,
Meshset     meshset_F40_GTE_sh_null1_1_TIRE_FR,
Materials   matlist_F40_GTE_sh_null1_1_TIRE_FR,
MeshsetNum  4,
MatNum      4,
Center       0.089164F,  0.000000F,  0.000000F,
Radius       0.433440F,
END

OBJECT      object_F40_GTE_sh_null1_1_TIRE_FR[]
START
EvalFlags ( 0x00000016 ),
Model       model_F40_GTE_sh_null1_1_TIRE_FR,
OPosition  (  0.735000F,  0.317302F, -1.164293F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_TIRE_FL,
END

OBJECT_END



OBJECT_START

MATERIAL    matlist_F40_GTE_sh_null1_1_shadow[]
START

MATSTART
Diffuse   ( 127, 0, 0, 0 ),
Specular  ( 255, 255, 255, 255 ),
Exponent  ( 11.0F ),
AttrTexId ( 0x0, 0 ),
AttrFlags ( 0x96182400 ),
MATEND

END

POLYGON     pgS_0_F40_GTE_sh_null1_1_shadow[]
START
	Strip(0x8000, 14),  0, 1, 5, 12, 3, 13, 4, 8, 2, 7, 
			10, 9, 11, 6, 
END

MESHSET     meshset_F40_GTE_sh_null1_1_shadow[]
START

MESHSTART
TypeMatId ( 0xc000, 0 ),
MeshNum     1,
Meshes      pgS_0_F40_GTE_sh_null1_1_shadow,
PolyAttrs   NULL,
PolyNormal  NULL,
VertColor   NULL,
VertUV      NULL,
MESHEND

END

POINT       point_F40_GTE_sh_null1_1_shadow[]
START
	VERT(  0.949460F,  0.000000F,  2.165439F ),
	VERT( -0.949460F,  0.000000F,  2.165439F ),
	VERT(  1.035184F,  0.000000F, -1.300597F ),
	VERT(  1.080280F,  0.000000F,  1.409176F ),
	VERT(  1.029010F,  0.000000F,  0.242768F ),
	VERT(  1.045278F,  0.000000F,  1.856201F ),
	VERT( -0.555152F,  0.000000F, -2.256297F ),
	VERT( -1.035184F,  0.000000F, -1.300597F ),
	VERT( -1.029010F,  0.000000F,  0.242768F ),
	VERT( -0.904403F,  0.000000F, -2.064590F ),
	VERT(  0.904403F,  0.000000F, -2.064590F ),
	VERT(  0.555152F,  0.000000F, -2.256297F ),
	VERT( -1.045278F,  0.000000F,  1.856201F ),
	VERT( -1.080280F,  0.000000F,  1.409176F ),
END

NORMAL      normal_F40_GTE_sh_null1_1_shadow[]
START
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
	NORM(  0.000000F,  1.000000F,  0.000000F ),
END

MODEL       model_F40_GTE_sh_null1_1_shadow[]
START
Points      point_F40_GTE_sh_null1_1_shadow,
Normal      normal_F40_GTE_sh_null1_1_shadow,
PointNum    14,
Meshset     meshset_F40_GTE_sh_null1_1_shadow,
Materials   matlist_F40_GTE_sh_null1_1_shadow,
MeshsetNum  1,
MatNum      1,
Center       0.000000F,  0.000000F, -0.045429F,
Radius       2.460679F,
END

OBJECT      object_F40_GTE_sh_null1_1_shadow[]
START
EvalFlags ( 0x00000017 ),
Model       model_F40_GTE_sh_null1_1_shadow,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       NULL,
Sibling     object_F40_GTE_sh_null1_1_TIRE_FR,
END

OBJECT_END



OBJECT_START

OBJECT      object_F40_GTE_sh_null1_1_null1_1[]
START
EvalFlags ( 0x0000000f ),
Model       NULL,
OPosition  (  0.000000F,  0.000000F,  0.000000F ),
OAngle     (  0.000000F,  0.000000F,  0.000000F ),
OScale     (  1.000000F,  1.000000F,  1.000000F ),
Child       object_F40_GTE_sh_null1_1_shadow,
Sibling     NULL,
END

OBJECT_END


DEFAULT_START

#ifndef DEFAULT_OBJECT_NAME
#define DEFAULT_OBJECT_NAME object_F40_GTE_sh_null1_1_null1_1
#endif
#ifndef DEFAULT_TEXLIST_NAME
#define DEFAULT_TEXLIST_NAME texlist_F40_GTE_sh_null1_1
#endif

DEFAULT_END
