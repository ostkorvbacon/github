#include <stdio.h>
#include <stdlib.h>

int dubblera(char *str, int a, int b);

int main()
{
  int a, b;
  char * str;
  str = (char *) malloc(20*sizeof(char));
  *str = 'H';
  *(str+1) = 'e';
  *(str+2) = 'j';
  *(str+3) = 's';
  *(str+4) = 'a';
  *(str+5) = 'n';
  *(str+6) = '\0';
  a = 1;
  b = 1;
  dubblera(str, a, b);
  a = 5;
  b = 5;
  dubblera(str, a, b);
  printf("%s\n", str);
  return 0;
}

int dubblera(char *str, int a, int b)
{
  char *temp;
  int len = 0, add = 0, nlen = 0;
  int i, j;
  add = b - a + 1;
  temp = str;
  while(*(str + len) != '\0')
  {
    len++;
  }
  nlen = len + add;
  printf("a: %d  b: %d  len: %d  add: %d  nlen: %d\n", a, b, len, add, nlen);
  temp = str;
  if(a < 0) a = 0;
  if(b > len - 1) b = len -1;

  for(i=0; i < len; i++)
  {
    if(i<=b && i>=a)
    {
      for(j=0; j < len - i + 1; j++)
      {
        *(str + (len - j + 1)) = *(temp + (len - j));
      }
      len ++;
      i++;
      a++;
      b++;
    }
  }

  return 0;
}
