#include <stdio.h>
#include <stdlib.h>

char *dubblera(char *str, int a, int b);

int main()
{
  int a, b;
  char * str;
  str = (char*) malloc(20*sizeof(char));
  str = "Hejsan\0";
  a = 1;
  b = 1;
  /*str = dubblera(str, a, b);
  a = 5;
  b = 5;*/
  str = dubblera(str, a, b);
  printf("%s\n", str);
  return 0;
}

char *dubblera(char *str, int a, int b)
{
  char *temp;
  int len = 0, add = 0, nlen = 0;
  int i, j;
  add = b - a + 1;
  temp = str;
  while(*(temp+len) != '\0')
  {
    len++;
  }
  nlen = len + add;
  printf("len: %d  add: %d  nlen: %d\n", len, add, nlen);
  printf("%c\n", *(str +1));
  temp = str;
  for(i=0; i < len; i++)
  {
    if(i<=b && i>=a)
    {
      for(j=0; j < len; j++)
      {
          printf("test\n");
          *(str + (nlen-j)) = *(temp + (len -j));
          printf("test2\n");

      }
    }
  }
  *(str + 8) = *(temp +(len+1));
  printf("%s\n", str);

  return str;
}
