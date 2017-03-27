/*
 * Dreamroq by Mike Melanson
 *
 * This is a simple, sample program that helps test the Dreamroq library.
 */

#include <stdio.h>
#include "dreamroqlib.h"

int quit_cb()
{
    /* big, fat no-op for command line tool */
    return 0;
}

int render_cb(unsigned short *buf, int width, int height, int stride,
    int texture_height)
{
    static int count = 0;
    FILE *out;
    char filename[20];
    int x, y, pixel;

    sprintf(filename, "%04d.pnm", count);
    printf("writing frame %d to file %s\n", count, filename);
    count++;
    out = fopen(filename, "wb");
    if (!out)
        return ROQ_CLIENT_PROBLEM;
    fprintf(out, "P6\n%d %d\n255\n", width, height);
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pixel = *buf++;
            fputc(((pixel >> 11) << 3) & 0xFF, out);  /* red */
            fputc(((pixel >>  5) << 2) & 0xFF, out);  /* green */
            fputc(((pixel >>  0) << 3) & 0xFF, out);  /* blue */
        }
        buf += (stride - width);
    }
    fclose(out);

    return ROQ_SUCCESS;
}

int main(int argc, char *argv[])
{
    int status;

    if (argc < 2)
    {
        printf("USAGE: newroq-cli <file.roq>\n");
        return 1;
    }

    status = dreamroq_play(argv[1], 0, render_cb, 0, quit_cb);
    printf("final status = %d\n", status);

    return status;
}

