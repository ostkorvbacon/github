#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

char* strang(int storlek)
{
  char* tmp;
  tmp = (char*)calloc(storlek, sizeof(char));
  return tmp;
}
int *gemigint(int storlek)
{
  int *tmp;
  tmp = (int*) calloc(storlek, sizeof(int));
  return tmp;
}
int main(int argc, char *argv[])
{

  int i;
  int *heltal;
  if(argc!=2){ printf("du är dum"); exit(-1);}
  heltal = (int*)calloc(atoi(argv[1], sizeof(int));
  for(i=0; i<atoi(argv[1]);i++)
    printf("%d\n", heltal[i]);


  /*for(i=0; i<argc;i++)
    printf("argv[%d] = %s\n", i, argv[i]);


  /*int *p1, *p2;
  char *str;
  int i;
  printf("%p\n", str);
  str = strang(SIZE);
  strcpy(str, "Lisa");
  printf("%p\n", str);
  p1 = gemigint(SIZE);



  p1 = (int*)malloc(SIZE*sizeof(int));
  p2 = (int*)calloc(SIZE, sizeof(int));
  for(i=0;i<SIZE;i++)
    printf("%d|", p1[i]);
  printf("\n--------------\n");
  for(i=0;i<SIZE;i++)
    printf("%d|", p2[i]);
    free(p1);
    free(p2);*/

  return 0;
}
