/* text.h */

#ifndef __TEXT_H
#define __TEXT_H
int text_init();

void font_draw_string(float x1, float y1, float z, float a, float r, float g, float b, char *str);

void font_draw_string_bouncy(float x1, float y1, float z, float a, float r, float g, float b, char *str);

void font_throb();

#endif /* __TEXT_H */

/* vi:tabstop=4
*/
