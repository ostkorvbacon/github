#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  struct nod *VT;
  int varde;
  struct nod *HT;
}nod;
nod add(nod *rit, int aValue)
{
  if(rot==NULL)
  {
    rot=(nod*)malloc(sizeof(nod));
    rot->varde = aValue
    rot->VT = NULL;
    rot->HT = NULL;
  }
}
int main(int argc, char *argv[])
{
  int i;
  nod *mittTrad = NULL;
  mittTrad = add(mittTrad, 10);
  printf("VT:%p, varde= %d, HT:%p", mittTrad->VT, mittTrad->varde, mittTrad->HT);
  for(i=1; i<argc;i++)
  {}

  return 0;
}
