#ifdef __cplusplus
extern "C" {
#endif
	
/// @defgroup bitmap BMP file backend
/// @{
typedef void* VGBitmapFile;

VGBitmapFile  vgCreateBitmapFile(VGint width, VGint height);
void          vgDestroyBitmapFile(VGBitmapFile bmpFile);
VGErrorCode   vgSaveBitmapFile(VGBitmapFile bmpFile, const char* fileName);
VGint         vgGetBitmapFileWidth(VGBitmapFile bmpFile);
VGint         vgGetBitmapFileHeight(VGBitmapFile bmpFile);
VGPixelFormat vgGetBitmapFileFormat(VGBitmapFile bmpFile);
void*         vgGetBitmapFileRawData(VGBitmapFile bmpFile);
/// @}

#ifdef __cplusplus 
} /* extern "C" */
#endif
