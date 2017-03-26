#ifndef TRUE
#  define TRUE 1
#  define FALSE 0
#endif

#ifndef MAX
#  define MAX(a,b)  ((a) > (b)? (a) : (b))
#  define MIN(a,b)  ((a) < (b)? (a) : (b))
#endif

#ifdef DEBUG
#  define Trace(x)  {fprintf x ; fflush(stderr); fflush(stdout);}
#else
#  define Trace(x)  ;
#endif

void readpng_version_info(void);

void * readpng_init(FILE *infile);

/* pNumChannels will be 3 for RGB images, and 4 for RGBA images
 * pRowBytes is the number of bytes necesary to hold one row
 * the data gets returned as a flat stream of bytes, each row
 * starts at a multiple of pRowBytes
 * The caller is responsible for freeing the memory
 */
uint8 *readpng_get_image(void * strs, uint32 *pNumChannels,
                       uint32 *pRowBytes, uint32 *pWidth, uint32 *pHeight);

void readpng_cleanup(void * strs);
