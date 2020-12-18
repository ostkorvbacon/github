#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char x[] = "yela", *p1, *p2;
  p1 = x;
  p2 = (char *)malloc(5 * sizeof(char));
  *p2 = (--(*p1))-1;
  printf("%s\n", p1);

  *(p2+3) = p1[1] + 1;
  printf("%s\n", p2);

  p2[2] = x[2];
  printf("%s\n", p2);

  p1++;
  p2[1] = *p1 + 10;
  printf("%s\n", p2);


  return 0;
}
