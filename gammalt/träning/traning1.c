#include <stdio.h>
#include <stdlib.h>

int main()
{
  /*int x, y;
  int *p1,*p2;
  x=2;
  y=3;
  p1 = &x;
  p2 = &y;
  printf("x=%d, y=%d\n",x ,y);
  printf("&x = %p \n&y = %p\n", &x,&y);
  printf("p1 = %p \np2 = %p\n",p1,p2);
  printf("*p1 = %d *p2 = %d\n", *p1, *p2);
  printf("&p1 = %p \n&p2 = %p\n",&p1,&p2);*/
  float farray[100];
  float *fp;
  fp = farray;
  //fp = fp+1;
  printf("%p  \n%p", farray, fp);
}
