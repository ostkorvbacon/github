#include <stdio.h>
#include <stdlib.h>
#define RSIZE 10
typedef struct{
  char namn;
  int pnum;
  char adress;
}person;
typedef struct{
  char marke[20];
  int arsmodel;
  char reg;
  person p;
}bil;

void meny()
{
  printf("Meny\n");
  printf("1. Lägg till fordon\n");
  printf("0. Avsluta\n");
}
void finmatning(int *ant, person p[RSIZE])
{
  printf("Mata in ägarens namn.\n");
  scanf("%c", p[*ant].namn);
  printf("Mata in ägarens personnummer.\n");
  scanf("%d", &(p[*ant].pnum));
  printf("Mata in ägarens adress:");
  scanf("%c", p[*ant].adress);
  *ant = *ant +1;
}
int main()
{
  int val, ant=0;
  bil b[RSIZE];
  person p[RSIZE];
  do
  {
    meny();
    scanf("%d", &val);
    switch (val)
    {
      case 1: finmatning(&ant, p); break;
      case 0: printf("Exit.\n"); break;
    }

  }while(val!=0);
}
