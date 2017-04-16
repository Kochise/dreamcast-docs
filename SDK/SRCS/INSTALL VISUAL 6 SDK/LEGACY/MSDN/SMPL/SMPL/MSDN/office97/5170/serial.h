/*****************************************************************************

   Module  : MOD_Serial
   Prefix  : none
   Owner   : TonyLin
             PP4's PP5 Translator: v-hemta
   Platform: Core 

******************************************************************************

   WARNINGS: If you add a new type (PST_) or new instance (INS_) to the 
   enumeration, make sure it doesn't change the values of the existing enums!

   DO NOT INCLUDE THIS FILE IN YOUR HEADER FILES IF AT ALL POSSIBLE.
   Use forward declarations.

   The goal of this module is to separate the meaning contained in a PowerPoint
   file from the PowerPoint-specific object hierarchy.  This module can be
   compiled into clients of the PowerPoint file, such as translators and
   viewers. 

   The data structures in this module should be independent of MFC and
   PowerPoint types.
                                   
   For examples of how to do conversion, look at serial.cpp, recnst.cpp. 
   For more documentation, see papers\win\pp5files.ppt  
*****************************************************************************/

#undef MOD_Serial
#define MOD_Serial IsDefined

#include MOD_SerialTypes
#include MOD_SerialConstants

#pragma pack(4)


//================ FILE FORMAT CHANGES & FILE VERSIONS =======================
//============================================================================
// If the new build will not be able to read old files, bump DOCFILE_VERSION.
// 
// If old builds will not be able to read new files, bump PS_MAJOR_VERSION,
// and set PS_MINOR_VERSION to 0.
// 
// For other changes (old build can read new file, new build can read old
// files) bump PS_MINOR_VERSION
//
/*                      
   10/07/94    TonyLin        serial.h checked into project                         1007.0.0
   10/12/94    AndreB         handout master
   10/12/94    AliceW         embedded fonts saved with file
   10/13/94    TonyLin        added Directory stream                       
                              RecordHeader change                                   1008.0.0
   10/18/94    TonyLin        fix PictCollection deserialization
   10/19/94    GregNi         Added boolean to DocumentAtom
   10/20/94    AliceW         Added ExEmbed,ExLink stuff
   10/20/94    TonyLin        Add PST_ListPlaceholder
   10/24/94    TonyLin        PST_ColorTable / INS_MruColors
   10/25/94    TonyLin        PowerPointStateInfoAtom
   10/26/94    TonyLin        Texture
   11/04/94    PaulWa         Slide Show info, Sound Collection
   11/07/94    TonyLin        Text Style stuff
   11/09/94    AliceW         Added PST_ExPlain, PST_ExSlide
   11/09/94    ImranQ         add DocRoutingSlip to the Document
   11/16/94    TonyLin        Add PST_SubContainerCompleted
   11/23/94    4hrisAm        Center of Text Rotation
   11/??/94                   <ColorIndex usage was changed>   
   11/30/94    TonyLin        Modifications to allow automatic generation
                              of byte-swapping code
   12/02/94    EricWi         SlideBaseAtom add background
   12/04/94    TonyLin        GuideList
   12/04/94    TonyLin        Text Embedee Collection
   12/05/94    JimBar         Add member to PSR_ExOleObjAtom
   12/06/94    TonyLin        Conversion code for PSR_ExOleObjAtom
   12/12/94    GregNi         Added header and footers info for slide.
   12/16/94    v-Sanjar       ReColorInfo changes
   12/19/94    TonyLin        Major changes to text serialization                   1008.1.0
   01/04/95    TonyLin        Scheme/ColorTable/CDWordArray serialization cleanup   1008.1.1
   01/04/95    AndersKi       MainMaster
   01/05/95    TonyLin        Serialize colortable array from MainMaster            1008.1.2
   01/17/95    TonyLin        Textures serialize CoEntityAtoms                      1008.1.3
   01/26/95    TonyLin        Texture atom, MasterText container                    1008.1.4
   01/26/95    ImranQ         Removed saving of refcounts ( recount on open )       1008.2.0
   02/10/95    TonyLin        OEDefault saves OEShape info, change position of the
                              OEDefault container within the Environment container 1008.2.1
   02/11/95    ChrisAm        Removed saving of run array atoms                     1008.3.0
   02/14/95    TonyLin        Save MainMaster name                                  1008.3.1
   02/16/95    TonyLin        RulerEntity changes                                   1008.4.0
   02/16/95    GregNi         Change the SSlideLayoutAtom                           1008.4.1
   03/09/95    TonyLin        Change DocumentAtom (save slide size type A4,
                              custom, etc.)                                         1008.4.2
   03/26/95    RobPa          Added TagInfo serialization for doc, slide,
                              elem.                                                 1008.4.3
   03/29/95    TonyLin        Change DocumentAtom (nSlides)                         1008.4.4
   04/??/95    BrendB         PST_RecolorInfoAtom
   04/19/95    TonyLin        SSExInfo container, CString member                    1008.5.0 
   05/04/95    ChrisAm        DBC/SBC font references                               1008.6.0
   05/27/95    BrianJac       QuickTime and Subscription
   05/04/95    PaulWa         Interactive Sounds                                    1008.7.0
   11/29/95    MayQ           Escher                                                1009.0.0
   12/01/95    LanceA         Right to Left document                                1009.0.1
   01/17/96    MikeKern       Added VER_CStringAtom 1
   02/12/96    BrendB         Added PST_VBASlideInfoAtom                            1009.0.2
   02/21/96    GregNi         
   02/23/96    TonyLin        Added PSR_ExMediaAtom                                 1009.0.3
*/


#define DOCFILE_VERSION    1011
#define PS_MAJOR_VERSION   1
#define PS_MINOR_VERSION   0

//============================================================================
//=========================== APPLICATION VERSIONS ===========================
//============================================================================
#define REL_VER_MAJ 8         // Major version of app
#define REL_VER_MIN 0         // Minor version of app



//============================================================================
//============ PowerPoint-specific file format information ===================
//============================================================================

// PowerPoint files are OLE2 compound storage files.
// The stream where PSR's can be found is INITIAL_STREAM_NAME

#if !MACINTOSH
   #define INITIAL_STREAM_NAME     L"PowerPoint Document"
#else
   #define INITIAL_STREAM_NAME     "PowerPoint Document"
#endif



//====================== Types enumeration ===================================
//============================================================================

enum psrTypeCode                       // enumerates record types that are saved
{
   PST_UNKNOWN                   = 0,  // should never occur in file
   PST_SubContainerCompleted     = 1,  // should never occur in file
   PST_IRRAtom                   = 2,  // Indexed Record Reference
   PST_PSS                       = 3,  // start of stream
   PST_SubContainerException     = 4,  // should never occur in file
   PST_ClientSignal1 = 6,              // should never occur in file
   PST_ClientSignal2 = 7,              // should never occur in file

   // WARNING: If you add a new type (PST_) to the enumeration, 
   // make sure it doesn't change the values of the existing enums!
   
   /* Application Saved State Information */
   PST_PowerPointStateInfoAtom = 10,

   /* Document & Slide */
   PST_Document            = 1000,
   PST_DocumentAtom        = 1001,
   PST_EndDocument         = 1002,
   // unused 1003
   PST_SlideBase           = 1004,  
   PST_SlideBaseAtom       = 1005, 
   PST_Slide               = 1006,
   PST_SlideAtom           = 1007,
   PST_Notes               = 1008,
   PST_NotesAtom           = 1009,
   PST_Environment         = 1010,
//   PST_DLook               = 1011,
   PST_Scheme              = 1012,
   PST_SchemeAtom          = 1013,
   PST_DocViewInfo         = 1014,
   PST_SSlideLayoutAtom    = 1015,
   PST_MainMaster          = 1016,
   PST_SSSlideInfoAtom     = 1017,
   PST_SlideViewInfo       = 1018,
   PST_GuideAtom           = 1019,
   PST_ViewInfo            = 1020,
   PST_ViewInfoAtom        = 1021,
   PST_SlideViewInfoAtom   = 1022,
   PST_VBAInfo             = 1023,
   PST_VBAInfoAtom         = 1024,
   PST_SSDocInfoAtom       = 1025,
   PST_Summary             = 1026,
//   PST_Texture             = 1027,
   PST_VBASlideInfo        = 1028,
   PST_VBASlideInfoAtom    = 1029,
   PST_DocRoutingSlip      = 1030,
   PST_OutlineViewInfo     = 1031,
   PST_SorterViewInfo      = 1032,
   PST_ExObjList           = 1033,     /* new for PP96 */
   PST_ExObjListAtom       = 1034,     /* new for PP96 */
   PST_PPDrawingGroup      = 1035,     /* new for PP96 */
   PST_PPDrawing           = 1036,     /* new for PP96 */

   PST_NamedShows          = 1040,
   PST_NamedShow           = 1041,
   PST_NamedShowSlides     = 1042,

   /* Collections & lists */
   PST_List                = 2000,
//   PST_ListAtom            = 2001,
//   PST_ListItem            = 2002,
//   PST_ListItemAtom        = 2003,
//   PST_Collection          = 2004,
   PST_FontCollection      = 2005,
//   PST_PictCollection      = 2006,
//   PST_CObArray            = 2007,
//   PST_CObArrayAtom        = 2008,
//   PST_ObjListAtom         = 2009,
//   PST_ObjList             = 2010,
//   PST_CQWordArray         = 2011,
//   PST_HandleEntityAtom    = 2012,
//   PST_CoEntity            = 2013,
//   PST_CoEntityAtom        = 2014,
//   PST_CollectionReference = 2015,   
//   PST_CollectionReferenceAtom   = 2016,
   PST_ListPlaceholder     = 2017,
//   PST_NonSerializedCoEntity = 2018,
   PST_BookmarkCollection  = 2019,
   PST_SoundCollection     = 2020,
   PST_SoundCollAtom       = 2021,
   PST_Sound               = 2022,
   PST_SoundData           = 2023,
//   PST_BookmarkEntityEnd   = 2024,
   PST_BookmarkSeedAtom    = 2025,
   PST_GuideList           = 2026,
   // ...
   PST_RunArray            = 2028,
   PST_RunArrayAtom        = 2029,     // for compatibility with pre-d255 files
   PST_ArrayElementAtom    = 2030,     // variable length atom.  no PSR_ defined
   PST_Int4ArrayAtom       = 2031,     // variable length atom.  no PSR_ defined
   PST_ColorSchemeAtom     = 2032,     // contains 8 colors

   /* Slide Elements */
//   PST_OElementList        = 3000,
//   PST_OEGroup             = 3001,
//   PST_OEGroupAtom         = 3002,
//   PST_OElement            = 3003,
//   PST_OESingle            = 3004,
//   PST_OESingleAtom        = 3005,
//   PST_OELineBase          = 3006,
//   PST_OELineBaseAtom      = 3007,
   PST_OEShape             = 3008,
   PST_ExObjRefAtom        = 3009,
//   PST_OEPlaceholder       = 3010,
   PST_OEPlaceholderAtom   = 3011,
//   PST_OEDefault           = 3012,
//   PST_OEDefaultAtom       = 3013,
//   PST_OELine              = 3014,
//   PST_OELineAtom          = 3015,
//   PST_OEPoly              = 3016,
//   PST_OEPolyAtom          = 3017,
//   PST_OEArc               = 3018,
//   PST_OEArcAtom           = 3019,
   PST_GrColor             = 3020,
//   PST_PPShape             = 3021,
//   PST_PPShapeAtom         = 3022,
//   PST_PPPoly              = 3023,   
//   PST_GLine               = 3024,
   PST_GRectAtom           = 3025,
//   PST_GPolygon            = 3026,
//   PST_GArc                = 3027,
//   PST_GWedge              = 3028,
//   PST_GWedgeAtom          = 3029,
//   PST_GAngle              = 3030,
   PST_GRatioAtom          = 3031,
   PST_GScaling            = 3032,
//   PST_GLPoint             = 3033,
   PST_GPointAtom          = 3034,
//   PST_GPointArray         = 3035,
//   PST_SSOEInfoAtom        = 3036,
//   PST_ColorTable          = 3037,        // for compatibility with pre-d231 files
//   PST_TextureAtom         = 3038,

   /* Text, Rulers, External */
   PST_TextCharsAtom       = 4000,
   PST_StyleTextPropAtom   = 4001,            
   PST_BaseTextPropAtom    = 4002,
   PST_TxMasterStyleAtom   = 4003,
   PST_TxCFStyleAtom       = 4004,
   PST_TxPFStyleAtom       = 4005,
   // ... 
//   PST_OEExInfo            = 4014,
//   PST_OEExInfoAtom        = 4015,
   // ...
   PST_FontEntityAtom      = 4023,
   PST_FontEmbedData       = 4024,      
   PST_TypeFace            = 4025,             
   PST_CString             = 4026,
   PST_ExternalObject      = 4027,
//   PST_PictEntity          = 4028,
//   PST_PictEntityAtom      = 4029,
//   PST_Image               = 4030,
//   PST_PictImage           = 4031,        
//   PST_SlideImageAtom      = 4032,       
   PST_MetaFile            = 4033,
   PST_ExOleObj            = 4034,
   PST_ExOleObjAtom        = 4035,
   PST_ExPlainLinkAtom     = 4036,
   PST_CorePict            = 4037,
   PST_CorePictAtom        = 4038,
   PST_ExPlainAtom         = 4039,
   PST_SrKinsoku           = 4040,
   PST_Handout             = 4041,
//   PST_FontEntityEnd       = 4042,
//   PST_CoEntityEnd         = 4043,
   PST_ExEmbed             = 4044,
   PST_ExEmbedAtom         = 4045,
   PST_ExLink              = 4046,
   PST_ExLinkAtom          = 4047,
   PST_BookmarkEntityAtom  = 4048,
//   PST_DocNotes            = 4049,
   PST_SrKinsokuAtom       = 4050,
   PST_ExHyperlinkAtom     = 4051,
   PST_ExPlain             = 4053,
   PST_ExPlainLink         = 4054,
   PST_ExHyperlink         = 4055,
   PST_SlideNumberMCAtom   = 4056,
   PST_HeadersFooters      = 4057,
   PST_HeadersFootersAtom  = 4058,
//   PST_LogbrushAtom        = 4059,
//   PST_FrombrushAtom       = 4060,
//   PST_BrushAtom           = 4061,
   PST_RecolorEntryAtom    = 4062,
//   PST_RecolorInfoAtom     = 4063,   // old recolor info, conversion not supported
   PST_PowerText           = 4064,
   PST_EmFormatAtom        = 4065,
   PST_CharFormatAtom      = 4066,
   PST_ParaFormatAtom      = 4067,
   PST_MasterText          = 4068,
   PST_RulerEntity         = 4069,
   PST_RulerTabArrayAtom   = 4070,        // variable length atom.  no PSR_ defined
   PST_RecolorInfoAtom     = 4071,     // recolor info after d303
//   PST_SSExInfo            = 4072,
   PST_ExQuickTime         = 4073,
   PST_ExQuickTimeMovie    = 4074,
   PST_ExQuickTimeMovieData= 4075,
   PST_ExSubscription      = 4076,
   PST_ExSubscriptionSection= 4077,
   PST_ExControl           = 4078,     // new for PP96
   PST_ExControlAtom       = 4079,     // new for PP96
//    PST_AnimationInfo       = 4080,
   PST_AnimationInfoAtom   = 4081,
   PST_InteractiveInfo     = 4082,
   PST_InteractiveInfoAtom = 4083,
   PST_SlideList           = 4084,
   PST_UserEditAtom        = 4085,
   PST_CurrentUserAtom     = 4086,
   PST_DateTimeMCAtom      = 4087,     // header and footer meta characters.
   PST_GenericDateMCAtom   = 4088,
   PST_HeaderMCAtom        = 4089,
   PST_FooterMCAtom        = 4090,
   PST_ExMediaAtom         = 4100,    // External Media
   PST_ExVideo             = 4101,
   PST_ExAviMovie          = 4102,


   //  The 5000 block is used for client data in our 
   PST_ProgTags            = 5000,        // Programmable tags
   PST_ProgTagsAtom        = 5001,
   PST_ProgTag             = 5002,


   PST_PrintOptions        = 6000,        // Per-document print options
   PST_PersistPtrFullBlock = 6001,			// Complete list of persist's for this ver.
   PST_PersistPtrIncrementalBlock = 6002, // Incremental diffs on persists
//   PST_SlideRefList        = 6003,        // List of slides

//   PST_RulerIndentAtom     = 10000,       // Does not occur in file (nested within another record)
   PST_GScalingAtom        = 10001,       // Does not occur in file (nested within another record)
   PST_GrColorAtom         = 10002,       // Does not occur in file (nested within another record)
//   PST_GLPointAtom         = 10003,     // Does not occur in file (nested within another record)
//   PST_GLineAtom           = 10004,       // Does not occur in file (nested within another record)
  

   PST_LAST
};



//====================== Instance enumeration ================================
//============================================================================

//
enum PSSInstanceCode
{
   // exoleobj
  INS_StgName           = 0,
  INS_MenuName          = 1,
  INS_ProgID            = 2,
  INS_ClipboardName     = 3,
  
   // SrKinsoku
  INS_Leading           = 0,
  INS_Following         = 1,  
  INS_DocKinsoku        = 2,
  INS_SrKinsokuLevel    = 3,

   // VBAInfo
  INS_StorageName       = 1,
  INS_MacroName         = 2, // AR: also used in InteractiveInfo ?????

   // look
  INS_LookName          = 1,

   // object array
  INS_ObArrayElement    = 0,

   // doc
  INS_DocSlideList      = 0,
  INS_DocMasterList     = 1,

  INS_DocInfoList       = 0,
  INS_DocSlideShowInfo  = 0,
  INS_Handout           = 0,
  INS_Summary           = 0,

  // slide
  INS_SlideSlideShowInfo = 0,
  INS_SlideScheme       = 1,      // SlideMaster's scheme
  INS_TemplateName      = 2,

   //list // AR: are these needed?
  INS_GroupElementList  = 0,
  INS_ListElement       = 1,
  INS_OEInfoListElement = 2,
  INS_SlideElementListElement = 3,
  INS_OElements         = 4,
  INS_InfoListElement   = 5,
  INS_SchemeListElement = 6,
  INS_GuideListElement  = 7,
  INS_SlideBackground   = 8,

   // environment
  INS_DocEnvironment    = 0,
  INS_DefaultAttribs    = 1,
  INS_Pictures          = 2,
  INS_PicFonts          = 3,
  INS_MruColors         = 4,

   // text/external
  INS_SSPlayInfo        = 1,

  // slideshow
  INS_AnimationInfo     = 0,
  INS_InteractiveInfo   = 1,
  INS_SlideNotes        = 3,
  INS_DocNotes          = 4,
  INS_Sounds            = 5,
  INS_SSOEInfo          = 6,

  // Named shows
  INS_NamedShows        = 0,
  INS_NamedShowName     = 1,
  INS_NamedShowSlides   = 2,

   // HeadersFooters
  INS_UserDate          = 0,
  INS_Header            = 1,
  INS_Footer            = 2, 
  INS_SlideHeadersFooters = 3,
  INS_NotesHeadersFooters = 4,

   // Summary Info
  INS_BookmarkCollection = 0,
  INS_BookmarkValue     = 1,
  INS_BookmarkSeedAtom  = 2,

  // Textures
  INS_TextureName       = 0,

  // TagName
  INS_TagName           = 0,
  INS_TagValue          = 1,

   // DocInfoList
  INS_SlideViewInfo     = 0,
  INS_NotesViewInfo     = 1,
  INS_HandoutViewInfo   = 2, 
  INS_SlideShowWindowViewInfo = 3, 

  // ExControl
  INS_StreamName        = 0,

  // Placeholder
  INS_PlaceholderInfo   = 0,

  // InteractiveInfo trigger
  INS_MouseClick        = 0,
  INS_MouseOver         = 1,
};



//====================== Versions ============================================
//============================================================================

#define VER_PowerPointStateInfoAtom 0

/* Document & Slide */
#define VER_DocumentAtom         0
#define VER_SlideBaseAtom        0
#define VER_SlideAtom            0
#define VER_NotesAtom            0
#define VER_SchemeAtom           0
#define VER_SSlideLayoutAtom     0  
#define VER_SSSlideInfoAtom      0
#define VER_GuideAtom            0
#define VER_ViewInfoAtom         0
#define VER_SlideViewInfoAtom    0
#define VER_VBAInfoAtom          0 
#define VER_VBASlideInfoAtom     0
#define VER_SSDocInfoAtom        0
#define VER_Summary              0
#define VER_TxStylesAtom         0
#define VER_ExObjListAtom        0     /* new for PP96 */
#define VER_SoundCollAtom        0     /* new for PP96 */

/* Collections & lists */
#define VER_RunArrayAtom         0
#define VER_ArrayElementAtom     0
#define VER_Int4ArrayAtom        0
#define VER_ColorSchemeAtom      0     /* new for PP96 */

/* Slide Elements */
#define VER_ExObjRefAtom         0
#define VER_OEPlaceholderAtom    0
#define VER_GRectAtom            0

/* Text, Rulers, External */
#define VER_TextCharsAtom        0
#define VER_StyleTextPropAtom    0
#define VER_BaseTextPropAtom     0
#define VER_TxMasterStyleAtom    0
#define VER_TxCFStyleAtom        0
#define VER_TxPFStyleAtom        0
#define VER_FontEntityAtom       0
#define VER_ExOleObjAtom         0
#define VER_ExEmbedAtom          0
#define VER_ExLinkAtom           0
#define VER_ExControlAtom        0
#define VER_ExPlainAtom          0
#define VER_ExPlainLinkAtom      0
#define VER_ExHyperlinkAtom      0
#define VER_CorePictAtom         0
#define VER_BookmarkEntityAtom   0
#define VER_SrKinsokuAtom        0
#define VER_TxStyleEntryAtom     0
#define VER_BookmarkSeedAtom     0
#define VER_HeadersFooters       0
#define VER_HeadersFootersAtom   0
#define VER_SlideNumberMCAtom    0
#define VER_DateTimeMCAtom       0
#define VER_GenericDateMCAtom    0
#define VER_HeaderMCAtom         0
#define VER_FooterMCAtom         0

#define VER_RecolorEntryAtom     0
#define VER_RecolorInfoAtom      0
#define VER_EmFormatAtom         0
#define VER_ParaFormatAtom       0
#define VER_CharFormatAtom       0
#define VER_RulerTabArrayAtom    0
#define VER_AnimationInfoAtom    0
#define VER_InteractiveInfoAtom  0
#define VER_CStringAtom          0
#define VER_SlideListAtom        0
#define VER_UserEditAtom         0
#define VER_CurrentUserAtom      0


/* External Media */
#define VER_ExMediaAtom          0

/* Programmable Tags */
#define VER_ProgTagsAtom         0

/* Print Options */
#define VER_PrintOptions         0


//====================== Persistent Storage Records ==========================
//============================================================================


typedef sint4  PSR_GCoord;   
typedef sint4  PSR_GLCoord; 

struct PSR_GPointAtom
{
   sint4   x;
   sint4   y;
};

struct PSR_GRatioAtom
{
   sint4 numer;
   sint4 denom;
};

struct PSR_GScalingAtom
{
 PSR_GRatioAtom x;
 PSR_GRatioAtom y;
};

enum
{
   F_SCALE   = 16,                   // this should be the same as SCALE in geometry.h
   F_DEG90   = 90 * F_SCALE,
   F_DEG360  = 360 * F_SCALE,
};


struct PSR_GRectAtom
{
   sint4  left;
   sint4  top;
   sint4  right; 
   sint4  bottom;
};

struct PSR_GrColorAtom
{
   ubyte1 red;
   ubyte1 green;
   ubyte1 blue;
   ubyte1 pad;
};


struct PSR_EmFormatAtom
{
   sint4 ref;
};

// Font
#define PSR_LF_FACESIZE    32

struct PSR_FontEntityAtom
{
 // members of logfont
 uint2   lfFaceName[PSR_LF_FACESIZE];
 ubyte1  lfCharSet;
 ubyte1  lfClipPrecision;
 ubyte1  lfQuality;
 ubyte1  lfPitchAndFamily;
};

#define PSR_BOOKMARKNAMESIZE  32

struct PSR_BookmarkEntityAtom
{
 uint4   bookmarkID;
 uint2   bookmarkName[PSR_BOOKMARKNAMESIZE];
};

struct PSR_BookmarkSeedAtom
{
 uint4   bookmarkID;
};

typedef PSR_GPointAtom PSR_TxCtrOfRotAtom;

/******************************************************************************
   classes related to OElement
******************************************************************************/

typedef sint4 FEAlignment;

enum                        // can OR one horizontal and one vertical
{  // horizontal alignments
   FE_ALIGN_LEFT        = 0x0001,      // left edges
   FE_ALIGN_CENTER      = 0x0002,      // horizontal center
   FE_ALIGN_RIGHT       = 0x0003,      // right edges
   FE_ALIGN_HORIZONTAL  = 0x000F,      // mask for horizontal component

   // vertical alignments
   FE_ALIGN_TOP         = 0x0010,      // top edges
   FE_ALIGN_MIDDLE      = 0x0020,      // vertical center
   FE_ALIGN_BOTTOM      = 0x0030,      // bottom edges
   FE_ALIGN_VERTICAL    = 0x00F0,      // mask for vertical component
};

typedef ubyte1 FELineStyle;

typedef ubyte1 FEArrowStyle;    // arrowhead style is on or off
enum
{
   FE_ARROW_NONE = 0,
   FE_ARROW_NORMAL,
   FE_ARROW_ROUND,
   FE_ARROW_DIAMOND
}; 
                
typedef ubyte1 FELineStyle;

#define   F_LT_SOLIDLINE   0                 // solid colored line
//   F_LT_PATTERNEDLINE             // Mac only: patterned line
#define   F_LT_DASH1       1                     // Dash Pattern 1
#define   F_LT_DASH2       2                     // Dash Pattern 2
#define   F_LT_DASH3       3              // Dash Pattern 3
#define   F_LT_DASH4       4                     // Dash Pattern 4 
//   F_LT_MIXEDLINETYPES,            // only used to indicate mixed multi-sel
//   F_LT_NOTAPPLICABLE              // this attribute is not applicable

typedef ubyte1 FEShadowType;
#define F_ST_COLOREDSHADOW         (1)   // solid, colored shadow
#define F_ST_TRANSPARENTSHADOW     (2)   // transparent, colored shadow
#define F_ST_EMBOSSEDSHADOW        (3)   // double-shadow with embossed effect

typedef ubyte1 FEFillType;

#define F_FT_SOLIDFILL             (1)   // solid colored fill
#define F_FT_BACKGROUNDFILL        (2)   // automatic fill with slide background
#define F_FT_TRANSPARENTFILL       (3)   // transparent fill
#define F_FT_PATTERNEDFILL         (4)   // patterned fill
#define F_FT_SHADEDFILL            (5)   // shaded fill (fade)
#define F_FT_TEXTUREDFILL          (6)   // textured bitmap fill
#define F_FT_PICTUREFILL           (7)   // fill with a picture

enum
{  FDimX        = 0,     
   FAnimateX    = 2,
   FLastFlag    = 2
};


typedef ubyte1 FEPlaceholderId;
enum
{  FE_PLACE_NONE = 0,
   FE_PLACE_MASTER_TITLE,   
   FE_PLACE_MASTER_BODY,
   FE_PLACE_MASTER_CENTERTITLE,
   FE_PLACE_MASTER_SUBTITLE,
   FE_PLACE_MASTER_NOTES_SLIDEIMAGE,
   FE_PLACE_MASTER_NOTES_BODY,
   FE_PLACE_MASTER_DATE,
   FE_PLACE_MASTER_SLIDENUMBER,
   FE_PLACE_MASTER_FOOTER,
   FE_PLACE_MASTER_HEADER,
   FE_PLACE_NOTES_SLIDEIMAGE,
   FE_PLACE_NOTES_BODY,
   FE_PLACE_TITLE,
   FE_PLACE_BODY,
   FE_PLACE_CENTERTITLE,
   FE_PLACE_SUBTITLE,
   FE_PLACE_V_TITLE,          
   FE_PLACE_V_BODY,
   FE_PLACE_OBJECT,           
   FE_PLACE_GRAPH,
   FE_PLACE_TABLE,
   FE_PLACE_CLIPART,
   FE_PLACE_ORGCHART,
   FE_PLACE_MEDIA,
   FE_PLACE_FIRST = FE_PLACE_MASTER_TITLE,
   FE_PLACE_LAST = FE_PLACE_MEDIA
};

typedef ubyte1 FEPlaceholderSize;
enum
{  FE_SIZE_FULL,
   FE_SIZE_HALF,
   FE_SIZE_QUART
};


typedef sint4 FLayout ;
enum
{
   F_GEOM_TITLE_SLIDE,    // title moved down, center aligned body below it
   F_GEOM_TITLE_BODY,     // standard title/body layout copied from master
   F_GEOM_TITLE_ONLY,     // title only, no body placeholder
   F_GEOM_2_COLUMNS,      // body split into 2 columns
   F_GEOM_2_ROWS,         // body split into 2 rows
   F_GEOM_COLUMN_2_ROWS,  // body split into 2 columns, right column has 2 rows
   F_GEOM_2_ROWS_COLUMN,  // body split into 2 columns, left column has 2 rows
   F_GEOM_ROW_2_COLUMNS,  // body split into 2 rows, bottom row has 2 columns
   F_GEOM_2_COLUMNS_ROW,  // body split into 2 rows, top row has 2 columns
   F_GEOM_4_OBJECTS,      // body split into 4 objects
   F_GEOM_BIG_OBJECT,     // title and body combined into one big object
   F_GEOM_BLANK           // neither title nor body
};

enum
{  F_ManualAdvanceX = 0,  
   F_HiddenX        = 2,     
   F_SoundX         = 4,
   /* 
   F_BuildX         = 4,     
   F_DimPointsX     = 6,     
   F_AnimatePointsX = 8,
   */
   F_LastFlag       = 4
};

enum
{ F_Layout= 0,
 F_Look,   
 F_Notes   
};

#define MAX_OBJECTS_IN_LAYOUT 8     // no layout has more than 5 objects
struct PSR_SSlideLayoutAtom
{   
   sint4 geom;
   ubyte1 placeholderId[ MAX_OBJECTS_IN_LAYOUT ];
};

struct PSR_DocumentAtom
{
   PSR_GPointAtom      slideSize;      // slide size in master coords 
   PSR_GPointAtom      notesSize;      // notes page size in master coords
   PSR_GRatioAtom      serverZoom;
   uint2               firstSlideNum;
   sint2               slideSizeType;  // size type: A4, screen, custom, etc.
   bool1               saveWithFonts; 
   bool1               omitTitlePlace; // omit placeholders on title slide
   bool1               rightToLeft;    // right-to-left document (Middle East)
   bool1               showComments;   // are comments visible
};

// This is written out with every save.  It contains user settings which
// are always saved.
// It should be noted that you can always easily traverse back through
// versions, however even though this is the first record in the file,
// moving forward through versions is not possible.  The reason is that
// we have a principal that we don't overwrite old data, we simply add
// new data within the actual stream.  We break this principal exactly
// once with the current user field which is overwritten after a successful
// save.
struct PSR_UserEditAtom
{
   sint4  lastSlideID;    // slideID
   uint4  version;        // This is major/minor/build which did the edit
   uint4  offsetLastEdit; // File offset of last edit
   uint4  offsetPersistDirectory; // Offset to PersistPtrs for 
 	                          // this file version.
   uint4  documentRef;
   uint4  maxPersistWritten;      // Addr of last persist ref written to the file (max seen so far).
   sint2  lastViewType;   // enum view type
};

// This is written to the current user stream.  It is a variable length
// record, whose true size includes a sequence of bytes after this structure
// which is the current User's name.
// NOTE: We don't support incremental records of different machine types,
//       thus saving a file on the other plaform will involve a full save.
struct PSR_CurrentUserAtom
{
   uint4  size;
   uint4  magic;  // Magic number to ensure this is a PowerPoint file.
   uint4  offsetToCurrentEdit;  // Offset in main stream to current edit field.
   uint2	 lenUserName;
   uint2  docFileVersion;
   ubyte1 majorVersion;
   ubyte1 minorVersion;
};

struct PSR_ExObjListAtom
{
   sint4  objectIdSeed;   // next unique identifier for ole objects
};

struct PSR_SoundCollAtom
{
   sint4  objectIdSeed;   // next unique identifier for ole objects
};

const int MST_FLAG_OBJECTS = 0x01;
const int MST_FLAG_SCHEME = 0x02;
const int MST_FLAG_BACKGROUND = 0x04;

struct PSR_SlideBaseAtom
{
   PSR_GRectAtom    rect;       // size in master coordinates

   uint2  flags; // Replaces below
   // MasterFlags
//   bool1  objects;                   // background objects follow master
//   bool1  scheme;                    // scheme follows master
//   bool1  title;                     // title follows master
//   bool1  body;                      // body follows master
//   bool1  background;                // background follows master
};


struct PSR_SlideAtom
{
   PSR_SlideBaseAtom base;       // base attributes
   PSR_SSlideLayoutAtom layout;
   sint4       slideId;
   sint4       masterId;         // Id of master slide
};

struct PSR_NotesAtom
{
   sint4 slideID;
};

struct PSR_ExObjRefAtom
{
   uint4 exObjId;
};

struct PSR_OEPlaceholderAtom
{
   uint4    placementId;               // the placeholders position.
   ubyte1   placeholderId;             // Place holder number
   ubyte1   size;                      // the placeholders size. 
}; 


//====================== Text ========================================
//============================================================================
// Containers:
//    PSR_SrKinsokuAtom

const int S_HEADERFOOTER_DATE =        0x01;
const int S_HEADERFOOTER_TODAYDATE =   0x02;
const int S_HEADERFOOTER_USERDATE =    0x04;
const int S_HEADERFOOTER_SLIDENUMBER = 0x08;
const int S_HEADERFOOTER_HEADER =      0x10;
const int S_HEADERFOOTER_FOOTER =      0x20;

struct PSR_HeadersFootersAtom
{
   sint2 formatId;
   uint2 flags;    // date, todayDate, userDate, slideNumber, header, footer
};

struct PSR_SlideNumberMCAtom
{  sint4 position; // position in text
};       

struct PSR_DateTimeMCAtom
{  sint4  position; // position in text
   ubyte1 index;    // the date/time index
};

struct PSR_GenericDateMCAtom
{  sint4 position; // position in text
};

struct PSR_HeaderMCAtom
{  sint4 position; // position in text
};

struct PSR_FooterMCAtom
{  sint4 position; // position in text
};

struct PSR_SrKinsokuAtom
{
   sint4 level;
};

struct PSR_ExPlainAtom
{
    sint4  objID; // persistent unique identifier for external object
};

struct PSR_ExPlainLinkAtom
{
    sint4  objID; // persistent unique identifier for external object
};

struct PSR_ExHyperlinkAtom
{
    sint4  objID; // persistent unique identifier for external object
};

// ExOleObject
struct PSR_ExOleObjAtom
{
   uint4  drawAspect;
   sint4  type;  // whether embedded or linked ?
   sint4  objID; // persistent unique identifier for external object
   sint4  subType;
   bool1  isBlank; // true if object has no presentation data
};

// ExEmbed
struct PSR_ExEmbedAtom
{
   sint4        followColorScheme;
   bool1        cantLockServerB;
   bool1        noSizeToServerB;
   bool1        isTable;
};

// ExLink
struct PSR_ExLinkAtom
{
   uint4        updateMode;
   bool1        unavailable;
};

// ExControl
struct PSR_ExControlAtom
{  bool1        useIStream;
};

//struct PSR_LogbrushAtom
//{
// uint4 lbStyle;
// uint4 lbColor;
// sint4 lbHatch;
//};

//struct PSR_BrushAtom
//{
// PSR_LogbrushAtom log;
// PSR_GrColorAtom  foreground;
// PSR_GrColorAtom  background;
// sint4            bitmapType;
// ubyte1           bits[8];
//};

//struct PSR_FrombrushAtom
//{
// PSR_GrColorAtom color;
// PSR_BrushAtom   brush;
//};


struct PSR_RecolorEntryAtom
{
   PSR_GrColorAtom toColor;
   PSR_GrColorAtom fromColor;
   bool1           doRecolor;
};

struct PSR_RecolorInfoAtom			// AR: THL for backwards compatibility only
{
 PSR_GrColorAtom monoColor;
 sint4  nColors; 
 sint4  nFills;
 uint2  flags;
// uint2  recolorState    :1;
// uint2  fMissingColors  :1;
// uint2  fMissingFills   :1;
// uint2  fIgnoredColors  :1;
// uint2  monoRecolor     :1;
// uint2  noModify        :1;
// uint2  blackFg         :1;
// uint2  unused          :9;
};

 
struct PSR_CorePictAtom
{
 PSR_GRectAtom  frame;      // frame of the picture.
 bool1          isVirtual;  // Is memory handle virtual?
};


#define PSR_NAMEDSHOW_SIZE    32

struct PSR_SSDocInfoAtom
{
    PSR_GrColorAtom  penColor;      // color to use for John Madden
    sint4            restartTime;
    sint2            startSlide;
    sint2            endSlide;
    uint2            namedShow[PSR_NAMEDSHOW_SIZE];
    ubyte1           flags; 
};

struct PSR_SSSlideInfoAtom
{
   sint4        slideTime;     // how long to show the slide in ticks
   uint4        soundRef;     
   uint2        effect;        // type of transition (2 character signature)
   uint2        flags;         // set of flags that determine type of build
   ubyte1       speed;         // speed of transition
};  // slide show info

struct PSR_AnimationInfoAtom
{
  PSR_GrColorAtom  dimColor;
  uint4            flags;
  uint4            soundRef;     
  uint2            orderID;    
  uint2            delayTime;
  uint2            slideCount;
  ubyte1           buildType;
  ubyte1           flyMethod;
  ubyte1           flyDirection;     
  ubyte1           afterEffect;     
  ubyte1           subEffect;    
  ubyte1           oleVerb;
};

struct PSR_InteractiveInfoAtom
{
 uint4      soundRef;     
 uint4      exHyperlinkID;
 ubyte1     action;
 ubyte1     oleVerb;
 ubyte1     jump;
 ubyte1     flags;
};


// External Media related Atoms
struct PSR_ExMediaAtom
{
   uint4    exObjId;    // All objects derived from ExternalObject must save/load their id
   uint2    flags;
};



// View Info

struct PSR_ViewInfoAtom
{
 PSR_GScalingAtom  curScale;
 PSR_GScalingAtom  prevScale;
 PSR_GPointAtom    viewSize;
 PSR_GPointAtom    origin;
 bool1             varScale;
 bool1             draftMode;
};

struct PSR_GuideAtom
{
 sint4   type;  // guide type
 sint4   pos;   // position in master coordinates
                // x if vertical; y if horizontal
};

// DocViewInfo

struct PSR_SlideViewInfoAtom
{
   bool1 showGuides;
   bool1 snapToGrid;
   bool1 snapToShape; // AR: is this really stored with the document?
};

// VBA
struct PSR_VBAInfoAtom
{
 uint4   state;  // Project State
 uint4   autoLoad; // Bring project into running state immediately
 uint4   version; // version number, 0 and 1: old VBA, 2: new VBA^3
};

struct PSR_VBASlideInfoAtom
{
 uint4   state;  // Project State
};

// VBAProject
 
struct PSR_SchemeAtom
{
   uint4 tableSize;
};

struct PSR_ColorSchemeAtom
{
   uint4 color[8]; // 8 COLORREFs in color scheme
};


// Indexed Record Reference Atom

struct PSR_IRRAtom
{
   uint4 indexID;          // Which index to use   indexToUse = indexMap.Lookup(indexID)
   uint4 indexKey;         // location = index.Lookup(indexKey)
};


struct PSR_PowerPointStateInfoAtom
{
   uint4 curViewType;         
   uint4 curSlideId;
};


struct PSR_ProgTagsAtom
{
   uint4 nTags;
};


// Per-document options:

struct PSR_PrintOptions
{
   ubyte1   printWhat;
   bool1    printHidden;
   bool1    printBlackWhite;
   bool1    printPureBlackWhite;
   bool1    scaleToFitPaper;
   bool1    frameSlides;
};

//

#pragma pack()













