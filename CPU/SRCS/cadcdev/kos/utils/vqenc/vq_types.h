
#ifndef __VQ_TYPES_H
#define __VQ_TYPES_H

#ifndef uint8
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
#endif

/* from 2x2 to 1024x1024 */
#define MAX_MIPMAP 10

typedef struct fcolor_t {
	float r;
	float g;
	float b;
	float a;
} fcolor_t;

typedef struct fquad_t {
	fcolor_t p[4];
} fquad_t;

typedef struct mipmap_t {
	/* each map represents quads of a different resolution */
	fquad_t *map[MAX_MIPMAP];
} mipmap_t;

typedef struct code_t {
	/* sum of quads using this code */
	fquad_t pos_sum;
	int pos_count;
	
	float max_dist;
	fquad_t max_dist_vec;
	
	/* position in codebook index */
	uint8 index;
	
	/* value of this codebook entry */
	fquad_t value;
} code_t;

typedef struct context_t {
	int in_use;
	code_t codes[256];
} context_t;

#endif
