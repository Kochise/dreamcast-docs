#define XPOS_INIT 1
#define YPOS_INIT 1
#define SCREENWIDTH 640

int disp_xpos=XPOS_INIT;
int disp_ypos=YPOS_INIT;

void printpos_d(int xpos, int ypos, char *str)
{
	int offset;
	char current;
	while(*str)
	{
		offset = (xpos*12) + ((ypos* (24+4)) * SCREENWIDTH);
		current=*str++;
		if(current != '\n')
		{
			bfont_draw(vram_s + offset,SCREENWIDTH, 0, current);
			xpos++;
		}
		else
		{
			xpos = XPOS_INIT;
			ypos ++;
		}
	}
}
void print_d(char *str)
{
	int offset;
	char current;
	while(*str)
	{
		offset = (disp_xpos*12) + ((disp_ypos* (24+4)) * SCREENWIDTH);
		current=*str++;
		if(current != '\n')
		{
			bfont_draw(vram_s + offset,SCREENWIDTH, 0, current);
			disp_xpos++;
		}
		else
		{
			disp_xpos = XPOS_INIT;
			disp_ypos ++;
		}
	}
}

