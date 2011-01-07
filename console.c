#include "console.h"
#define S_COLS 80
#define S_ROWS 25

int row = 0, col = 0;
char* video = (char*) 0xb8000;
void kcls()
{
  int i = 0;
  for (i; i < 2*S_ROWS*S_COLS; i++)
  {
    video[i] = 0;
  }
  col = 0;
  row = 0;
}

void kputs( char* string )
{
  int i;
  for (i = 0; string[i] != '\0'; i++) 
  {
    if ( ( string[i] == '\n' ) || ( col == S_COLS ) )
    {
      row++;
      if ( row == S_ROWS )
      {
        kscroll();
        row--;
      }
      col = 0;
    }
    if ( string[i] != '\n' )
    {
      video[(row * S_COLS + col)*2] = string[i];
      video[(row * S_COLS + col)*2+1] = 0x07;
      col++;
    }
  }
}

void kscroll()
{
  int scroll_line;
  int i;
  for( scroll_line = 0; scroll_line<S_ROWS; scroll_line++ )
  {
    if (scroll_line != S_ROWS-1)
    {
      for(i=0; i < S_COLS; i++)
      {
        video[(scroll_line * S_COLS  + i)*2] = video[((scroll_line +1 ) * S_COLS + i ) * 2];
	video[(scroll_line * S_COLS  + i)*2+1] = video[((scroll_line +1 ) * S_COLS + i ) * 2+1];
      }
    }
    else
    {
      for(i=0; i < 2 * S_COLS; i++)
      {
        video[scroll_line * S_COLS + i] = 0;
      }
    }
  }
}
