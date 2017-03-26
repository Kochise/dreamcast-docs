/********************************************************************/
/*                                                                  */
/*  Renderman v2.x  -  2D Rendering engine based on AGG 2.x         */
/*                                                                  */
/*    (c) Ales a.s. Lipt. Mikulas - 26.2.2006                       */
/*                                                                  */
/********************************************************************/

#include <stdio.h>
#include <assert.h>

#include "agg_basics.h"
#include "agg_rendering_buffer.h"

#include "vgEngine.h"
#include "vgConfig.h"
#include "vgImage.h"
#include "vgBitmapFile.h"

#ifdef __BORLANDC__
#pragma option push -b
#pragma option push -a4
#endif

#ifndef __GNUC__
#pragma	pack(1)
#endif

class vgBitmapFile
{
		class vgImage* image;

		struct RGB3
		{
			char bBlue;				 /* Blue component of the color definition */
			char bGreen;			 /* Green component of the color definition*/
			char bRed;				 /* Red component of the color definition  */
		};
		struct RGB4
		{
	    	char bBlue;				 /* Blue component of the color definition */
		    char bGreen;			 /* Green component of the color definition*/
    		char bRed;				 /* Red component of the color definition  */
	    	char fcOptions;			 /* Reserved, must be zero                 */
    	};
		struct bitmap_file_header
    	{
			unsigned short	usType;
		    unsigned short	cbSizeLow, cbSizeHigh;
			short			reserve1, reserve2;
		};
    	struct bitmap_info
		{
			unsigned short	imageOffset;
	    	short			reserve;
    	};
    	struct bitmap_info_header1
		{
    	  unsigned int	 size;
		  unsigned short cx;			   /* Bit-map width in pels                  */
		  unsigned short cy;			   /* Bit-map height in pels                 */
		  unsigned short cPlanes;		   /* Number of bit planes                   */
		  unsigned short cBitCount;		   /* Number of bits per pel within a plane  */
		  unsigned int	 ulCompression;	   /* Compression scheme used to store the bitmap */
    	  unsigned int	 cbImage;		   /* Length of bit-map storage data in chars*/
    	  unsigned int	 cxResolution;	   /* x resolution of target device          */
		  unsigned int	 cyResolution;	   /* y resolution of target device          */
		  unsigned int	 cclrUsed;		   /* Number of color indices used           */
		  unsigned int	 cclrImportant;	   /* Number of important color indices      */
    	};
		struct bitmap_info_header2
    	{
		  unsigned int	 size;
		  unsigned int	 cx;			   /* Bit-map width in pels                  */
    	  unsigned int	 cy;			   /* Bit-map height in pels                 */
    	  unsigned short cPlanes;		   /* Number of bit planes                   */
		  unsigned short cBitCount;		   /* Number of bits per pel within a plane  */
		  unsigned int	 ulCompression;	   /* Compression scheme used to store the bitmap */
		  unsigned int	 cbImage;		   /* Length of bit-map storage data in chars*/
    	  unsigned int	 cxResolution;	   /* x resolution of target device          */
    	  unsigned int	 cyResolution;	   /* y resolution of target device          */
    	  unsigned int	 cclrUsed;		   /* Number of color indices used           */
		  unsigned int	 cclrImportant;	   /* Number of important color indices      */
    	};

		void init(void);
		bitmap_file_header	bmfh;
		bitmap_info			bmi;
		union {
			bitmap_info_header1	bmih1;
			bitmap_info_header2	bmih2;
		} bmih;
		union {
			RGB3 rgb3[256];
			RGB4 rgb4[256];
		} rgb;

	public:
		vgBitmapFile(int width, int height);
		~vgBitmapFile();

		bool Save(const char* filename = "rendered_img.bmp");
		vgImage* GetImage() const { return image; }
		void* GetRawData();
};

#ifndef __GNUC__
#pragma	pack()
#endif

#ifdef __BORLANDC__
#pragma option pop
#pragma option pop
#endif

vgBitmapFile::vgBitmapFile(int width, int height)
{
	image = new vgImage(width, height, VG_Pixel_Bgra32);
}

vgBitmapFile::~vgBitmapFile()
{
	delete image;
	image = 0;
}

bool vgBitmapFile::Save(const char* filename)
{
	FILE *fp=0;
	int j, rest;
	char *bmp2;

	int w = image->GetWidth();
	int h = image->GetHeight();

	bmfh.usType = 'M' * 256 + 'B';
	bmfh.reserve1 = 0;
	bmfh.reserve2 = 0;
	bmi.reserve = 0;
	bmih.bmih2.size = 0x28;
	bmih.bmih2.cx = w;
	bmih.bmih2.cy = h;
	bmih.bmih2.cPlanes = 1;
	bmih.bmih2.ulCompression = 0;
	bmih.bmih2.cbImage = w * h;
	bmih.bmih2.cxResolution = 0;
	bmih.bmih2.cyResolution = 0;
	bmi.imageOffset = 0x36;
	bmfh.cbSizeLow = w * h + 0x36;
	bmfh.cbSizeHigh = (w * h + 0x36) >> 16;
	bmih.bmih2.cclrUsed = 0;
	bmih.bmih2.cclrImportant = 0;
	bmih.bmih2.cBitCount = 24;

	char* ext;
	if ((ext = (char *)strstr(filename,".bmp")) == 0)
	{
		char new_filename[128];
		strncpy(new_filename, filename, sizeof(new_filename)-5);
		strcat(new_filename, ".bmp");
		fp = fopen(new_filename, "wb");
	}
	else
		fp = fopen(filename, "wb");

	if (fp == 0)
	{
		printf("Bitmap '%s' not saved because of disk write error!", filename);
		return false;
	}
	assert(sizeof(bmfh) == 10);
	fwrite(&bmfh, sizeof(bmfh), 1, fp);
	fwrite(&bmi, sizeof(bmi), 1, fp);
	fwrite(&bmih, sizeof(bmih.bmih2), 1, fp);

	unsigned* img = (unsigned *)image->GetImage();

	for (int i = h - 1; i >= 0; i--)
	{
		bmp2 = (char *) (img + w * i);
		for (j = 0; j < w; j++)
		{
			fwrite(bmp2, 3, 1, fp);
			bmp2 += 4;
		}
		rest = (w * 3) % 4;

		while (rest & 3)
		{
			rest++;
			fputc(0, fp);
		}
	}
	fclose(fp);

	return false;
}

void* vgBitmapFile::GetRawData()
{
	return image->GetImage();
}

VGBitmapFile vgCreateBitmapFile(VGint width, VGint height)
{
	return (VGBitmapFile) new vgBitmapFile(width, height);
}

VGErrorCode vgSaveBitmapFile(VGBitmapFile bmpFile, const char* fileName)
{
	vgBitmapFile* ptr = (vgBitmapFile*) bmpFile;
	ptr->Save(fileName);	
}

VGint vgGetBitmapFileWidth(VGBitmapFile bmpFile)
{
	vgBitmapFile* ptr = (vgBitmapFile*) bmpFile;
	return ptr->GetImage()->GetWidth();
}

VGint vgGetBitmapFileHeight(VGBitmapFile bmpFile)
{
	vgBitmapFile* ptr = (vgBitmapFile*) bmpFile;
	return ptr->GetImage()->GetHeight();
}

void* vgGetBitmapFileRawData(VGBitmapFile bmpFile)
{
	vgBitmapFile* ptr = (vgBitmapFile*) bmpFile;
	return ptr->GetRawData();
}

void vgDestroyBitmapFile(VGBitmapFile bmpFile)
{
	vgBitmapFile* ptr = (vgBitmapFile*) bmpFile;
	delete ptr;
}

VGPixelFormat vgGetBitmapFileFormat(VGBitmapFile bmpFile)
{
	return VG_Pixel_Bgra32;
}

