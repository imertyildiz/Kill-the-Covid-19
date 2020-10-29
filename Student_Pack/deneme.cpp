#include <stdio.h>      /* printf */
#include <math.h>       /* atan2 */

#define PI 3.14159265

int main ()
{
  float ax,ay,bx,by,cx,cy,dx,dy, result;
  ax=0;
  ay=0;
  bx=3;
  by=0;
  cx=0;
  cy=0;
  cx=0;
  cy=3;
  float angle1 = (float) atan2(by-ay,ax-bx);
  float angle2 = (float) atan2(dy-cy,cx-dx);

  float x= (angle1-angle2)* 180 / 3.14159265;
  if(x>=180){
    x-=180;
  }
  result =x;
  printf ("The arc tangent for  is %f degrees\n",result );
  return 0;
}