#include "agg_path_storage.h"


struct ContextBase
{
	static const int MAX_DASH_LEN = 32;
	
	// Mode settings
	VGFillRule						fillRule;
	VGBlendMode						blendMode;
	
	// Stroke parameters
	VGdouble						strokeLineWidth;
	VGCapStyle						strokeCapStyle;
	VGJoinStyle						strokeJoinStyle;
	VGdouble						strokeMiterLimit;
	VGdouble						strokeDashPattern[MAX_DASH_LEN];
	VGint							strokeDashSize;
	VGdouble						strokeDashPhase;

	// Color for vgClear
	vgColor							clearColor;
	vgColor							fillColor;
	vgColor							lineColor;
	vgColor							textColor;

	VGPixelLayout					pixelLayout;
	
	VGint							clipMinX;	
	VGint							clipMinY;	
	VGint							clipWidth;
	VGint							clipHeight;
				
	ContextBase()
	:	fillRule(VG_EVEN_ODD),
		blendMode(VG_BLEND_SRC_OVER),
		
		// Stroke parameters
		strokeLineWidth(1.0f),
		strokeCapStyle(VG_CAP_BUTT),
		strokeJoinStyle(VG_JOIN_MITER),
		strokeMiterLimit(4.0f),
		strokeDashSize(0),
		strokeDashPhase(0.0f),
							
		// Color for vgClear
		clearColor(0,0,0,0),
		fillColor(255,255,255,255),
		lineColor(0,0,255,255),
		textColor(0,255,255,255),
		
		pixelLayout(VG_PIXEL_LAYOUT_UNKNOWN),
		clipMinX(0),
		clipMinY(0),
  		clipWidth(1),
		clipHeight(1)
	{	
	}
};

/**
 * 
 */
class vgContext : public ContextBase
{
  public:

	VGMatrix						pathUserToSurface;
	Array<VGMatrix>					matrixStack;

	VGErrorCode						error;
		
	class vgSurfaceInterface*		surface;
	
	
	class StateSaver*				saver;
	
	vgContext( unsigned w, unsigned h, VGPixelFormat format, void* memory );
	~vgContext();
	
	void 			SetError(VGErrorCode e);
	
	void 			DrawPath(VGPath path, VGbitfield paintModes);
	bool			TestPathHit(VGPath path, VGdouble sx, VGdouble sy, bool transform);
	void 			SetRenderingQuality( VGRenderingQuality q );
  private:
	vgContext(const vgContext&);			//!< Not allowed.
	void operator=(const vgContext&);		//!< Not allowed.	  
	
	VGRenderingQuality				renderingQuality;
	void FillPipeline(agg::path_storage& originalPath);
	void StrokePipeline(agg::path_storage& originalPath);
};

class StateSaver
{
		static const int MAX = 32;
		unsigned char stack[MAX][sizeof(ContextBase)];
		int current;
	public:
		StateSaver()
		{
			current = 0;
		}
		
		void Save(void* ctx)
		{
			void* memory = &((vgContext *)ctx)->fillRule;
			if (current<MAX)
				memmove( &stack[current++][0], memory, sizeof(ContextBase) );
		}
		void Restore(void* ctx)
		{
			if (current>0)
				memmove( ctx, &stack[--current][0], sizeof(ContextBase) );
		}
};
