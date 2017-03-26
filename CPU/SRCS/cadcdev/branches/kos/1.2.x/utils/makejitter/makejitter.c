#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <imageload/jitterdefs.h>

int ijitter[JITTER_TABLE_SIZE];
float ujitter[JITTER_TABLE_SIZE];
float vjitter[JITTER_TABLE_SIZE];

#define jitterx(x,y,s) (ujitter[((x+(y<<2))+ijitter[(x+s)&JITTER_MASK])&JITTER_MASK])
#define jittery(x,y,s) (vjitter[((y+(x<<2))+ijitter[(y+s)&JITTER_MASK])&JITTER_MASK])

void jitter_init(void)
{
  unsigned int i;
  
  for(i = 0; i < JITTER_TABLE_SIZE; i++)
    ujitter[i] = (float)(rand()%LARGE_NUMBER)/(float)LARGE_NUMBER;
  for(i = 0; i < JITTER_TABLE_SIZE; i++)
    vjitter[i] = (float)(rand()%LARGE_NUMBER)/(float)LARGE_NUMBER;
  for(i = 0; i < JITTER_TABLE_SIZE; i++)
    ijitter[i] = JITTER_TABLE_SIZE*
      (float)(rand()%LARGE_NUMBER)/(float)LARGE_NUMBER;
}


int main(int argc, char *argv[])
{
  FILE *f = fopen("jitter_table.h","wb+");
  int i;

  srand(time(NULL));
  jitter_init();

  fprintf(f,"int ijitter[JITTER_TABLE_SIZE] = {\n");
  
  for(i = 0; i < JITTER_TABLE_SIZE-1; i++)
  {
    fprintf(f,"%d,",ijitter[i]);
  }
  fprintf(f,"%d};\n", ijitter[i]);
  
  fprintf(f,"float ujitter[JITTER_TABLE_SIZE] = {\n");
  
  for(i = 0; i < JITTER_TABLE_SIZE-1; i++)
  {
    fprintf(f,"%.10f,",ujitter[i]);
  }
  fprintf(f,"%.10f};\n", ujitter[i]);
  
  fprintf(f,"float vjitter[JITTER_TABLE_SIZE] = {\n");
  
  for(i = 0; i < JITTER_TABLE_SIZE-1; i++)
  {
    fprintf(f,"%.10f,",vjitter[i]);
  }
  fprintf(f,"%.10f};\n", vjitter[i]);
  
  fclose(f);

  return 0;
}
