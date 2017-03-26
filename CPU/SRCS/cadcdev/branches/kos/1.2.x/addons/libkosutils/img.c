/* KallistiOS ##version##

   img.c
   (c)2002 Dan Potter

   Platform independent image handling
*/

#include <malloc.h>
#include <assert.h>
#include <kos/img.h>

CVSID("$Id: img.c,v 1.2 2003/04/24 03:17:44 bardtx Exp $");

/* Free a kos_img_t which was created by an image loader; set struct_also to non-zero   
   if you want it to free the struct itself as well. */
void kos_img_free(kos_img_t *img, int struct_also) {
	assert( img != NULL );
	
	/* Free the image data (if any) */
	if (img->data && !(KOS_IMG_FMT_I(img->fmt) & KOS_IMG_NOT_OWNER))
		free(img->data);

	/* Free the struct itself */
	if (struct_also)
		free(img);
}


