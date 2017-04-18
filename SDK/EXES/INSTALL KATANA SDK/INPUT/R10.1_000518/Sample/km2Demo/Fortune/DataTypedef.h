/* Typedef for textures */

typedef struct { char *sTextureFileName;
				 int nWidth;
				 int nHeight;
				 unsigned char *pBitmapData;
				}  Struct_Texture;

/* Typedef for meshes */
typedef struct { unsigned int      nNumVertex;
                 unsigned int      nNumFaces;
                 unsigned int      nNumStrips;
                 unsigned int      nFlags;
                 unsigned int      nMaterial;
                 float             fCenter[3];
                 float             *pVertex;
                 float             *pUV;
                 float             *pNormals;
                 float             *pPackedVertex;
                 unsigned int      *pVertexColor;
                 unsigned int      *pVertexMaterial;
                 unsigned short    *pFaces;
                 unsigned short    *pStrips;
                 unsigned short    *pStripLength;
               }   Struct_Mesh;


/* Typedef for materials */
typedef struct { char     *sMatName;
                 char     *sAmbientFile;
                 char     *sDifusseFile;
                 char     *sSpecularFile;
                 char     *sShininessFile;
                 char     *sShinStrenghtFile;
                 char     *sSelfIlluminationFile;
                 char     *sOpacityFile;
                 char     *sFilterColorFile;
                 char     *sBumpFile;
                 char     *sReflectionFile;
                 char     *sRefractionFile;
                 unsigned nMatAmbientColor;
                 unsigned nMatDiffuseColor;
                 unsigned nMatSpecularColor;
                 float    fMatShininess;
                 float    fMatShineStrength;
                 float    fMatOpacity;
                 unsigned nMatShadingType;
               }   Struct_Material;

/* Typedef for lights */
typedef struct { int      nLightType;
                 float    fPosition[3];
                 float    fTarget[3];
                 unsigned nColor;
                 float    fIntensity;
                 float    fHotspot;
                 float    fFalloff;
               }   Struct_Light;


/* Typedef for cameras */
typedef struct { float    fPosition[3];
                 float    fTarget[3];
                 float    fFOV;
                 float    fNearClip;
                 float    fFarClip;
               }   Struct_Camera;

/* Typedef for paths */
typedef struct { unsigned int  nNumVertex;
                 float         *pVertex;
               }   Struct_Path;

/* Typedef for animation */
typedef struct { unsigned int  nNumFrames;
                 float         Pivot[3];
                 float         *pData;
               }   Struct_Animation;

/* Typedef for camera animation */
typedef struct { unsigned int  nNumFrames;
                 float         *Position;
                 float         *Target;
               }   Struct_CameraAnimation;