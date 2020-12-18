#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int busta_rhymes(char str1[5], char str2[5])
{
  int l1,l2;
  l1 = strlen(str1);
  l2 = strlen(str2);
  if(str1[l1-1] == str2[l2-1] && str1[l1-2] == str2[l2-2])
  return 1;
  if(strstr(str1, str2) != NULL)
  return 1;

  return 0;
}
int main()
{
  char str1[]="rimma";
  char str2[]="simma";
  int rimma;
  rimma = busta_rhymes(str1, str2);
  printf("%d\n", rimma);
  return 0;
}
