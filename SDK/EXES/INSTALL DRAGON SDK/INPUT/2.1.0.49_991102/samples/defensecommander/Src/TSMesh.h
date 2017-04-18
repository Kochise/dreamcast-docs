// Header for mesh system.

// Mesh version number.
#define TSM_VERSION 1.01f
// Number of materials a mesh can have.
#define TSM_NUM_MATERIALS 4
// Maximum length of texture names (no extension).
#define TSM_TEXTURE_NAME_SIZE 32
// Maximum vertex count for a strip.
#define TSM_MAX_STRIP_VERTICES 64

#define TSM_FLAG_HAVE_OPAQUE			0x01
#define TSM_FLAG_HAVE_TRANS				0x02
#define TSM_FLAG_FIRST_PERSON			0x04
#define TSM_FLAG_USER_RENDER			0x08

#define TSM_MFLAG_USED					0x01
#define TSM_MFLAG_SMOOTH				0x02
#define TSM_MFLAG_TRANSLUCENT			0x04
#define TSM_MFLAG_TEXCLAMP				0x08
#define TSM_MFLAG_CORONA				0x10	
#define TSM_MFLAG_CORONA_DIRECTIONAL	0x20
#define TSM_MFLAG_CORONA_PROJECT		0x40

struct TSMVertex
{
	float X,Y,Z;
	float U,V;
};

struct TSMVector
{
	float X,Y,Z;
};

struct TSMPlane
{
	float X,Y,Z,W;
};

struct TSMCorona
{
	float CX,CY,CZ; // Center.
	float Radius;
	float NX,NY,NZ;	// Normal.
};

struct TSMMaterial
{
	DWORD			Flags;
	HANDLE			TextureHandle;
	signed short	*Indices;
	WORD			TextureName[TSM_TEXTURE_NAME_SIZE];
};

struct TSMHeader
{
	float		Version;
	DWORD		Flags;

	// Bounding.
	float		BoundingRadiusCollision;
	float		BoundingRadiusView;
	TSMVector	*BoundingVerts;
	int			BoundingVertsCount;
	TSMPlane	*BoundingPlanes;
	int			BoundingPlanesCount;

	// Mesh data.
	TSMVertex	*Verts;
	TSMVector	*Normals;
	int			VertsCount,NormalsCount;

	// Mesh materials.
	TSMMaterial	Materials[TSM_NUM_MATERIALS];
};
