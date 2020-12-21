#include "lab3.h"

void fgenerera(int arr[ARRSIZE])
{
  srand ( time(NULL));
  int i;

  for(i=0; i<ARRSIZE; i++)
  {
   arr[i] = rand()%NUMMAX + 1;
  }
  printf("Dina slumpade tal:");
  for(i=0; i<ARRSIZE; i++)
  { if(i%KOLUMNER == 0) printf("\n");
     printf("%3d ", arr[i]);
  }
  printf("\n\n");
}
