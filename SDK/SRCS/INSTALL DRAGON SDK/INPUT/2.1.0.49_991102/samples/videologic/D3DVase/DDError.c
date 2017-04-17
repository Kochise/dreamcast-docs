/* Source file used for debugging purposes */

#include <stdio.h>
#include "ddraw.h"
#include "d3d.h"


/* Prototypes */
TCHAR *ErrorToString(HRESULT hres);
void DisplayHRESULTInDebug(HRESULT hErr);

/* DisplayHRESULTInDebug Function */
void DisplayHRESULTInDebug(HRESULT hErr)
{       
    switch (hErr)
    {
	case DDERR_ALREADYINITIALIZED:
		OutputDebugString(L"DDERR_ALREADYINITIALIZED"); break;
	case DDERR_CANNOTATTACHSURFACE:
		OutputDebugString(L"DDERR_CANNOTATTACHSURFACE"); break;
	case DDERR_CANNOTDETACHSURFACE:
		OutputDebugString(L"DDERR_CANNOTDETACHSURFACE"); break;
	case DDERR_CURRENTLYNOTAVAIL:
		OutputDebugString(L"DDERR_CURRENTLYNOTAVAIL"); break;
	case DDERR_EXCEPTION:
		OutputDebugString(L"DDERR_EXCEPTION"); break;
	case DDERR_GENERIC:
		OutputDebugString(L"DDERR_GENERIC"); break;
	case DDERR_HEIGHTALIGN:
		OutputDebugString(L"DDERR_HEIGHTALIGN"); break;
	case DDERR_INCOMPATIBLEPRIMARY:
		OutputDebugString(L"DDERR_INCOMPATIBLEPRIMARY"); break;
	case DDERR_INVALIDCAPS:
		OutputDebugString(L"DDERR_INVALIDCAPS"); break;
	case DDERR_INVALIDCLIPLIST:
		OutputDebugString(L"DDERR_INVALIDCLIPLIST"); break;
	case DDERR_INVALIDMODE:
		OutputDebugString(L"DDERR_INVALIDMODE"); break;
	case DDERR_INVALIDOBJECT:
		OutputDebugString(L"DDERR_INVALIDOBJECT"); break;
	case DDERR_INVALIDPARAMS:
		OutputDebugString(L"DDERR_INVALIDPARAMS"); break;
	case DDERR_INVALIDPIXELFORMAT:
		OutputDebugString(L"DDERR_INVALIDPIXELFORMAT"); break;
	case DDERR_INVALIDRECT:
		OutputDebugString(L"DDERR_INVALIDRECT"); break;
	case DDERR_LOCKEDSURFACES:
		OutputDebugString(L"DDERR_LOCKEDSURFACES"); break;
	case DDERR_NO3D:
		OutputDebugString(L"DDERR_NO3D"); break;
	case DDERR_NOALPHAHW:
		OutputDebugString(L"DDERR_NOALPHAHW"); break;
	case DDERR_NOCLIPLIST:
		OutputDebugString(L"DDERR_NOCLIPLIST"); break;
	case DDERR_NOCOLORCONVHW:
		OutputDebugString(L"DDERR_NOCOLORCONVHW"); break;
	case DDERR_NOCOOPERATIVELEVELSET:
		OutputDebugString(L"DDERR_NOCOOPERATIVELEVELSET"); break;
	case DDERR_NOCOLORKEY:
		OutputDebugString(L"DDERR_NOCOLORKEY"); break;
	case DDERR_NOCOLORKEYHW:
		OutputDebugString(L"DDERR_NOCOLORKEYHW"); break;
	case DDERR_NODIRECTDRAWSUPPORT:
		OutputDebugString(L"DDERR_NODIRECTDRAWSUPPORT"); break;
	case DDERR_NOEXCLUSIVEMODE:
		OutputDebugString(L"DDERR_NOEXCLUSIVEMODE"); break;
	case DDERR_NOFLIPHW:
		OutputDebugString(L"DDERR_NOFLIPHW"); break;
	case DDERR_NOGDI:
		OutputDebugString(L"DDERR_NOGDI"); break;
	case DDERR_NOMIRRORHW:
		OutputDebugString(L"DDERR_NOMIRRORHW"); break;
	case DDERR_NOTFOUND:
		OutputDebugString(L"DDERR_NOTFOUND"); break;
	case DDERR_NOOVERLAYHW:
		OutputDebugString(L"DDERR_NOOVERLAYHW"); break;
	case DDERR_NORASTEROPHW:
		OutputDebugString(L"DDERR_NORASTEROPHW"); break;
	case DDERR_NOROTATIONHW:
		OutputDebugString(L"DDERR_NOROTATIONHW"); break;
	case DDERR_NOSTRETCHHW:
		OutputDebugString(L"DDERR_NOSTRETCHHW"); break;
	case DDERR_NOT4BITCOLOR:
		OutputDebugString(L"DDERR_NOT4BITCOLOR"); break;
	case DDERR_NOT4BITCOLORINDEX:
		OutputDebugString(L"DDERR_NOT4BITCOLORINDEX"); break;
	case DDERR_NOT8BITCOLOR:
		OutputDebugString(L"DDERR_NOT8BITCOLOR"); break;
	case DDERR_NOTEXTUREHW:
		OutputDebugString(L"DDERR_NOTEXTUREHW"); break;
	case DDERR_NOVSYNCHW:
		OutputDebugString(L"DDERR_NOVSYNCHW"); break;
	case DDERR_NOZBUFFERHW:
		OutputDebugString(L"DDERR_NOZBUFFERHW"); break;
	case DDERR_NOZOVERLAYHW:
		OutputDebugString(L"DDERR_NOZOVERLAYHW"); break;
	case DDERR_OUTOFCAPS:
		OutputDebugString(L"DDERR_OUTOFCAPS"); break;
	case DDERR_OUTOFMEMORY:
		OutputDebugString(L"DDERR_OUTOFMEMORY"); break;
	case DDERR_OUTOFVIDEOMEMORY:
		OutputDebugString(L"DDERR_OUTOFVIDEOMEMORY"); break;
	case DDERR_OVERLAYCANTCLIP:
		OutputDebugString(L"DDERR_OVERLAYCANTCLIP"); break;
	case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
		OutputDebugString(L"DDERR_OVERLAYCOLORKEYONLYONEACTIVE"); break;
	case DDERR_PALETTEBUSY:
		OutputDebugString(L"DDERR_PALETTEBUSY"); break;
	case DDERR_COLORKEYNOTSET:
		OutputDebugString(L"DDERR_COLORKEYNOTSET"); break;
	case DDERR_SURFACEALREADYATTACHED:
		OutputDebugString(L"DDERR_SURFACEALREADYATTACHED"); break;
	case DDERR_SURFACEALREADYDEPENDENT:
		OutputDebugString(L"DDERR_SURFACEALREADYDEPENDENT"); break;
	case DDERR_SURFACEBUSY:
		OutputDebugString(L"DDERR_SURFACEBUSY"); break;
	case DDERR_CANTLOCKSURFACE:
		OutputDebugString(L"DDERR_CANTLOCKSURFACE"); break;
	case DDERR_SURFACEISOBSCURED:
		OutputDebugString(L"DDERR_SURFACEISOBSCURED"); break;
	case DDERR_SURFACELOST:
		OutputDebugString(L"DDERR_SURFACELOST"); break;
	case DDERR_SURFACENOTATTACHED:
		OutputDebugString(L"DDERR_SURFACENOTATTACHED"); break;
	case DDERR_TOOBIGHEIGHT:
		OutputDebugString(L"DDERR_TOOBIGHEIGHT"); break;
	case DDERR_TOOBIGSIZE:
		OutputDebugString(L"DDERR_TOOBIGSIZE"); break;
	case DDERR_TOOBIGWIDTH:
		OutputDebugString(L"DDERR_TOOBIGWIDTH"); break;
	case DDERR_UNSUPPORTED:
		OutputDebugString(L"DDERR_UNSUPPORTED"); break;
	case DDERR_UNSUPPORTEDFORMAT:
		OutputDebugString(L"DDERR_UNSUPPORTEDFORMAT"); break;
	case DDERR_UNSUPPORTEDMASK:
		OutputDebugString(L"DDERR_UNSUPPORTEDMASK"); break;
	case DDERR_VERTICALBLANKINPROGRESS:
		OutputDebugString(L"DDERR_VERTICALBLANKINPROGRESS"); break;
	case DDERR_WASSTILLDRAWING:
		OutputDebugString(L"DDERR_WASSTILLDRAWING"); break;
	case DDERR_XALIGN:
		OutputDebugString(L"DDERR_XALIGN"); break;
	case DDERR_INVALIDDIRECTDRAWGUID:
		OutputDebugString(L"DDERR_INVALIDDIRECTDRAWGUID"); break;
	case DDERR_DIRECTDRAWALREADYCREATED:
		OutputDebugString(L"DDERR_DIRECTDRAWALREADYCREATED"); break;
	case DDERR_NODIRECTDRAWHW:
		OutputDebugString(L"DDERR_NODIRECTDRAWHW"); break;
	case DDERR_PRIMARYSURFACEALREADYEXISTS:
		OutputDebugString(L"DDERR_PRIMARYSURFACEALREADYEXISTS"); break;
	case DDERR_NOEMULATION:
		OutputDebugString(L"DDERR_NOEMULATION"); break;
	case DDERR_REGIONTOOSMALL:
		OutputDebugString(L"DDERR_REGIONTOOSMALL"); break;
	case DDERR_CLIPPERISUSINGHWND:
		OutputDebugString(L"DDERR_CLIPPERISUSINGHWND"); break;
	case DDERR_NOCLIPPERATTACHED:
		OutputDebugString(L"DDERR_NOCLIPPERATTACHED"); break;
	case DDERR_NOHWND:
		OutputDebugString(L"DDERR_NOHWND"); break;
	case DDERR_HWNDSUBCLASSED:
		OutputDebugString(L"DDERR_HWNDSUBCLASSED"); break;
	case DDERR_HWNDALREADYSET:
		OutputDebugString(L"DDERR_HWNDALREADYSET"); break;
	case DDERR_NOPALETTEATTACHED:
		OutputDebugString(L"DDERR_NOPALETTEATTACHED"); break;
	case DDERR_NOPALETTEHW:
		OutputDebugString(L"DDERR_NOPALETTEHW"); break;
	case DDERR_BLTFASTCANTCLIP:
		OutputDebugString(L"DDERR_BLTFASTCANTCLIP"); break;
	case DDERR_NOBLTHW:
		OutputDebugString(L"DDERR_NOBLTHW"); break;
	case DDERR_NODDROPSHW:
		OutputDebugString(L"DDERR_NODDROPSHW"); break;
	case DDERR_OVERLAYNOTVISIBLE:
		OutputDebugString(L"DDERR_OVERLAYNOTVISIBLE"); break;
	case DDERR_NOOVERLAYDEST:
		OutputDebugString(L"DDERR_NOOVERLAYDEST"); break;
	case DDERR_INVALIDPOSITION:
		OutputDebugString(L"DDERR_INVALIDPOSITION"); break;
	case DDERR_NOTAOVERLAYSURFACE:
		OutputDebugString(L"DDERR_NOTAOVERLAYSURFACE"); break;
	case DDERR_EXCLUSIVEMODEALREADYSET:
		OutputDebugString(L"DDERR_EXCLUSIVEMODEALREADYSET"); break;
	case DDERR_NOTFLIPPABLE:
		OutputDebugString(L"DDERR_NOTFLIPPABLE"); break;
	case DDERR_CANTDUPLICATE:
		OutputDebugString(L"DDERR_CANTDUPLICATE"); break;
	case DDERR_NOTLOCKED:
		OutputDebugString(L"DDERR_NOTLOCKED"); break;
	case DDERR_CANTCREATEDC:
		OutputDebugString(L"DDERR_CANTCREATEDC"); break;
	case DDERR_NODC:
		OutputDebugString(L"DDERR_NODC"); break;
	case DDERR_WRONGMODE:
		OutputDebugString(L"DDERR_WRONGMODE"); break;
	case DDERR_IMPLICITLYCREATED:
		OutputDebugString(L"DDERR_IMPLICITLYCREATED"); break;
	case DDERR_NOTPALETTIZED:
		OutputDebugString(L"DDERR_NOTPALETTIZED"); break;
	case DDERR_UNSUPPORTEDMODE:
		OutputDebugString(L"DDERR_UNSUPPORTEDMODE"); break;
	case DDERR_NOMIPMAPHW:
		OutputDebugString(L"DDERR_NOMIPMAPHW"); break;
	case DDERR_INVALIDSURFACETYPE:
		OutputDebugString(L"DDERR_INVALIDSURFACETYPE"); break;
	case DDERR_DCALREADYCREATED:
		OutputDebugString(L"DDERR_DCALREADYCREATED"); break;
	case DDERR_CANTPAGELOCK:
		OutputDebugString(L"DDERR_CANTPAGELOCK"); break;
	case DDERR_CANTPAGEUNLOCK:
		OutputDebugString(L"DDERR_CANTPAGEUNLOCK"); break;
	case DDERR_NOTPAGELOCKED:
		OutputDebugString(L"DDERR_NOTPAGELOCKED"); break;
	case DDERR_NOTINITIALIZED:
		OutputDebugString(L"DDERR_NOTINITIALIZED"); break;
	case DD_OK:
		OutputDebugString(L"NO ERROR"); break;
	default:
		OutputDebugString(L"Unknown Error"); break;
	}
	OutputDebugString(L"\n->");
	OutputDebugString(ErrorToString(hErr));
	OutputDebugString(L"\n");
}


/* ErrorToString Function */
TCHAR *ErrorToString(HRESULT hres)
{
    switch(hres) 
	{
        case DD_OK:
            return L"No error.\0";
        case DDERR_ALREADYINITIALIZED:
            return L"This object is already initialized.\0";
        case DDERR_BLTFASTCANTCLIP:
            return L"Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
        case DDERR_CANNOTATTACHSURFACE:
            return L"This surface can not be attached to the requested surface.\0";
        case DDERR_CANNOTDETACHSURFACE:
            return L"This surface can not be detached from the requested surface.\0";
        case DDERR_CANTCREATEDC:
            return L"Windows can not create any more DCs.\0";
        case DDERR_CANTDUPLICATE:
            return L"Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
        case DDERR_CLIPPERISUSINGHWND:
            return L"An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
        case DDERR_COLORKEYNOTSET:
            return L"No src color key specified for this operation.\0";
        case DDERR_CURRENTLYNOTAVAIL:
            return L"Support is currently not available.\0";
        case DDERR_DIRECTDRAWALREADYCREATED:
            return L"A DirectDraw object representing this driver has already been created for this process.\0";
        case DDERR_EXCEPTION:
            return L"An exception was encountered while performing the requested operation.\0";
        case DDERR_EXCLUSIVEMODEALREADYSET:
            return L"An attempt was made to set the cooperative level when it was already set to exclusive.\0";
        case DDERR_GENERIC:
            return L"Generic failure.\0";
        case DDERR_HEIGHTALIGN:
            return L"Height of rectangle provided is not a multiple of reqd alignment.\0";
        case DDERR_HWNDALREADYSET:
            return L"The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.\0";
        case DDERR_HWNDSUBCLASSED:
            return L"HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.\0";
        case DDERR_IMPLICITLYCREATED:
            return L"This surface can not be restored because it is an implicitly created surface.\0";
        case DDERR_INCOMPATIBLEPRIMARY:
            return L"Unable to match primary surface creation request with existing primary surface.\0";
        case DDERR_INVALIDCAPS:
            return L"One or more of the caps bits passed to the callback are incorrect.\0";
        case DDERR_INVALIDCLIPLIST:
            return L"DirectDraw does not support the provided cliplist.\0";
        case DDERR_INVALIDDIRECTDRAWGUID:
            return L"The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
        case DDERR_INVALIDMODE:
            return L"DirectDraw does not support the requested mode.\0";
        case DDERR_INVALIDOBJECT:
            return L"DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
        case DDERR_INVALIDPARAMS:
            return L"One or more of the parameters passed to the function are incorrect.\0";
        case DDERR_INVALIDPIXELFORMAT:
            return L"The pixel format was invalid as specified.\0";
        case DDERR_INVALIDPOSITION:
            return L"Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
        case DDERR_INVALIDRECT:
            return L"Rectangle provided was invalid.\0";
        case DDERR_LOCKEDSURFACES:
            return L"Operation could not be carried out because one or more surfaces are locked.\0";
        case DDERR_NO3D:
            return L"There is no 3D present.\0";
        case DDERR_NOALPHAHW:
            return L"Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
        case DDERR_NOBLTHW:
            return L"No blitter hardware present.\0";
        case DDERR_NOCLIPLIST:
            return L"No cliplist available.\0";
        case DDERR_NOCLIPPERATTACHED:
            return L"No clipper object attached to surface object.\0";
        case DDERR_NOCOLORCONVHW:
            return L"Operation could not be carried out because there is no color conversion hardware present or available.\0";
        case DDERR_NOCOLORKEY:
            return L"Surface doesn't currently have a color key\0";
        case DDERR_NOCOLORKEYHW:
            return L"Operation could not be carried out because there is no hardware support of the destination color key.\0";
        case DDERR_NOCOOPERATIVELEVELSET:
            return L"Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
        case DDERR_NODC:
            return L"No DC was ever created for this surface.\0";
        case DDERR_NODDROPSHW:
            return L"No DirectDraw ROP hardware.\0";
        case DDERR_NODIRECTDRAWHW:
            return L"A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
        case DDERR_NOEMULATION:
            return L"Software emulation not available.\0";
        case DDERR_NOEXCLUSIVEMODE:
            return L"Operation requires the application to have exclusive mode but the application does not have exclusive mode.\0";
        case DDERR_NOFLIPHW:
            return L"Flipping visible surfaces is not supported.\0";
        case DDERR_NOGDI:
            return L"There is no GDI present.\0";
        case DDERR_NOHWND:
            return L"Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
        case DDERR_NOMIRRORHW:
            return L"Operation could not be carried out because there is no hardware present or available.\0";
        case DDERR_NOOVERLAYDEST:
            return L"Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to establish a destination.\0";
        case DDERR_NOOVERLAYHW:
            return L"Operation could not be carried out because there is no overlay hardware present or available.\0";
        case DDERR_NOPALETTEATTACHED:
            return L"No palette object attached to this surface.\0";
        case DDERR_NOPALETTEHW:
            return L"No hardware support for 16 or 256 color palettes.\0";
        case DDERR_NORASTEROPHW:
            return L"Operation could not be carried out because there is no appropriate raster op hardware present or available.\0";
        case DDERR_NOROTATIONHW:
            return L"Operation could not be carried out because there is no rotation hardware present or available.\0";
        case DDERR_NOSTRETCHHW:
            return L"Operation could not be carried out because there is no hardware support for stretching.\0";
        case DDERR_NOT4BITCOLOR:
            return L"DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.\0";
        case DDERR_NOT4BITCOLORINDEX:
            return L"DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.\0";
        case DDERR_NOT8BITCOLOR:
            return L"DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
        case DDERR_NOTAOVERLAYSURFACE:
            return L"Returned when an overlay member is called for a non-overlay surface.\0";
        case DDERR_NOTEXTUREHW:
            return L"Operation could not be carried out because there is no texture mapping hardware present or available.\0";
        case DDERR_NOTFLIPPABLE:
            return L"An attempt has been made to flip a surface that is not flippable.\0";
        case DDERR_NOTFOUND:
            return L"Requested item was not found.\0";
        case DDERR_NOTLOCKED:
            return L"Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.\0";
        case DDERR_NOTPALETTIZED:
            return L"The surface being used is not a palette-based surface.\0";
        case DDERR_NOVSYNCHW:
            return L"Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.\0";
        case DDERR_NOZBUFFERHW:
            return L"Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
        case DDERR_NOZOVERLAYHW:
            return L"Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.\0";
        case DDERR_OUTOFCAPS:
            return L"The hardware needed for the requested operation has already been allocated.\0";
        case DDERR_OUTOFMEMORY:
            return L"DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OUTOFVIDEOMEMORY:
            return L"DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OVERLAYCANTCLIP:
            return L"The hardware does not support clipped overlays.\0";
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
            return L"Can only have ony color key active at one time for overlays.\0";
        case DDERR_OVERLAYNOTVISIBLE:
            return L"Returned when GetOverlayPosition is called on a hidden overlay.\0";
        case DDERR_PALETTEBUSY:
            return L"Access to this palette is being refused because the palette is already locked by another thread.\0";
        case DDERR_PRIMARYSURFACEALREADYEXISTS:
            return L"This process already has created a primary surface.\0";
        case DDERR_REGIONTOOSMALL:
            return L"Region passed to Clipper::GetClipList is too small.\0";
        case DDERR_SURFACEALREADYATTACHED:
            return L"This surface is already attached to the surface it is being attached to.\0";
        case DDERR_SURFACEALREADYDEPENDENT:
            return L"This surface is already a dependency of the surface it is being made a dependency of.\0";
        case DDERR_SURFACEBUSY:
            return L"Access to this surface is being refused because the surface is already locked by another thread.\0";
        case DDERR_SURFACEISOBSCURED:
            return L"Access to surface refused because the surface is obscured.\0";
        case DDERR_SURFACELOST:
            return L"Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have Restore called on it.\0";
        case DDERR_SURFACENOTATTACHED:
            return L"The requested surface is not attached.\0";
        case DDERR_TOOBIGHEIGHT:
            return L"Height requested by DirectDraw is too large.\0";
        case DDERR_TOOBIGSIZE:
            return L"Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
        case DDERR_TOOBIGWIDTH:
            return L"Width requested by DirectDraw is too large.\0";
        case DDERR_UNSUPPORTED:
            return L"Action not supported.\0";
        case DDERR_UNSUPPORTEDFORMAT:
            return L"FOURCC format requested is unsupported by DirectDraw.\0";
        case DDERR_UNSUPPORTEDMASK:
            return L"Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
        case DDERR_VERTICALBLANKINPROGRESS:
            return L"Vertical blank is in progress.\0";
        case DDERR_WASSTILLDRAWING:
            return L"Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is incomplete.\0";
        case DDERR_WRONGMODE:
            return L"This surface can not be restored because it was created in a different mode.\0";
        case DDERR_XALIGN:
            return L"Rectangle provided was not horizontally aligned on required boundary.\0";
        case D3DERR_BADMAJORVERSION:
            return L"D3DERR_BADMAJORVERSION\0";
        case D3DERR_BADMINORVERSION:
            return L"D3DERR_BADMINORVERSION\0";
        case D3DERR_EXECUTE_LOCKED:
            return L"D3DERR_EXECUTE_LOCKED\0";
        case D3DERR_EXECUTE_NOT_LOCKED:
            return L"D3DERR_EXECUTE_NOT_LOCKED\0";
        case D3DERR_EXECUTE_CREATE_FAILED:
            return L"D3DERR_EXECUTE_CREATE_FAILED\0";
        case D3DERR_EXECUTE_DESTROY_FAILED:
            return L"D3DERR_EXECUTE_DESTROY_FAILED\0";
        case D3DERR_EXECUTE_LOCK_FAILED:
            return L"D3DERR_EXECUTE_LOCK_FAILED\0";
        case D3DERR_EXECUTE_UNLOCK_FAILED:
            return L"D3DERR_EXECUTE_UNLOCK_FAILED\0";
        case D3DERR_EXECUTE_FAILED:
            return L"D3DERR_EXECUTE_FAILED\0";
        case D3DERR_EXECUTE_CLIPPED_FAILED:
            return L"D3DERR_EXECUTE_CLIPPED_FAILED\0";
        case D3DERR_TEXTURE_NO_SUPPORT:
            return L"D3DERR_TEXTURE_NO_SUPPORT\0";
        case D3DERR_TEXTURE_NOT_LOCKED:
            return L"D3DERR_TEXTURE_NOT_LOCKED\0";
        case D3DERR_TEXTURE_LOCKED:
            return L"D3DERR_TEXTURELOCKED\0";
        case D3DERR_TEXTURE_CREATE_FAILED:
            return L"D3DERR_TEXTURE_CREATE_FAILED\0";
        case D3DERR_TEXTURE_DESTROY_FAILED:
            return L"D3DERR_TEXTURE_DESTROY_FAILED\0";
        case D3DERR_TEXTURE_LOCK_FAILED:
            return L"D3DERR_TEXTURE_LOCK_FAILED\0";
        case D3DERR_TEXTURE_UNLOCK_FAILED:
            return L"D3DERR_TEXTURE_UNLOCK_FAILED\0";
        case D3DERR_TEXTURE_LOAD_FAILED:
            return L"D3DERR_TEXTURE_LOAD_FAILED\0";
        case D3DERR_MATRIX_CREATE_FAILED:
            return L"D3DERR_MATRIX_CREATE_FAILED\0";
        case D3DERR_MATRIX_DESTROY_FAILED:
            return L"D3DERR_MATRIX_DESTROY_FAILED\0";
        case D3DERR_MATRIX_SETDATA_FAILED:
            return L"D3DERR_MATRIX_SETDATA_FAILED\0";
        case D3DERR_SETVIEWPORTDATA_FAILED:
            return L"D3DERR_SETVIEWPORTDATA_FAILED\0";
        case D3DERR_MATERIAL_CREATE_FAILED:
            return L"D3DERR_MATERIAL_CREATE_FAILED\0";
        case D3DERR_MATERIAL_DESTROY_FAILED:
            return L"D3DERR_MATERIAL_DESTROY_FAILED\0";
        case D3DERR_MATERIAL_SETDATA_FAILED:
            return L"D3DERR_MATERIAL_SETDATA_FAILED\0";
        case D3DERR_LIGHT_SET_FAILED:
            return L"D3DERR_LIGHT_SET_FAILED\0";
        default:
            return L"Unrecognized error value.\0";
    }
}

