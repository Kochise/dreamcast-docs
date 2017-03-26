/* Very simple test for bfont (and its various encodings) */

#include <kos.h>

int main(int argc, char **argv) {
	int x, y, o;

	for (y=0; y<480; y++)
		for (x=0; x<640; x++) {
			int c = (x ^ y) & 255;
			vram_s[y*640+x] = ((c >> 3) << 12)
				| ((c >> 2) << 5)
				| ((c >> 3) << 0);
		}

	o = 20*640 + 20;

	/* Test with ISO8859-1 encoding */
	bfont_set_encoding(BFONT_CODE_ISO8859_1);
	bfont_draw_str(vram_s + o, 640, 1, "Test of basic ASCII"); o += 640*24;
	bfont_draw_str(vram_s + o, 640, 1, "Parlez-vous fran軋is?"); o += 640*24;
	bfont_draw_str(vram_s + o, 640, 0, "Test of basic ASCII"); o += 640*24;
	bfont_draw_str(vram_s + o, 640, 0, "Parlez-vous fran軋is?"); o += 640*24;

	/* Test with EUC encoding */
	bfont_set_encoding(BFONT_CODE_EUC);
	bfont_draw_str(vram_s + o, 640, 1, "､ｳ､ﾋ､ﾁ､ﾏ EUC!"); o += 640*24;
	bfont_draw_str(vram_s + o, 640, 0, "､ｳ､ﾋ､ﾁ､ﾏ EUC!"); o += 640*24;

	/* Test with Shift-JIS encoding */
	bfont_set_encoding(BFONT_CODE_SJIS);
	bfont_draw_str(vram_s + o, 640, 1, "アドレス変換 SJIS"); o += 640*24;
	bfont_draw_str(vram_s + o, 640, 0, "アドレス変換 SJIS"); o += 640*24;

	/* Pause to see the results */
	usleep(5*1000*1000);

	return 0;
}
