
/**************************************************************************
 **************************************************************************/
class D3DTexture {
    private:
        IDirectDrawSurface *MemorySurface;  // system memory surface
        IDirectDrawSurface *DeviceSurface;  // video memory texture
	IDirectDrawPalette *Palette;
	D3DTEXTUREHANDLE    Handle;

    public:
        D3DTexture()
        {
	    MemorySurface = 0;
	    DeviceSurface = 0;
            Palette = 0;
	    Handle = 0;
        }

        D3DTEXTUREHANDLE    GetHandle()    {return Handle;}
        IDirectDrawSurface* GetSurface()   {return MemorySurface;}
        IDirectDrawPalette* GetPalette()   {return Palette;}

        BOOL Load(IDirect3DDevice2 *Device, char *BitmapName);
        BOOL Copy(HBITMAP Bitmap);
        void Release(void);
        BOOL Restore(void);
};
