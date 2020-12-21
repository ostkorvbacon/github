#include "lab3.h"

void fsortera(int arr[ARRSIZE])
{
  int i, k, x, n = ARRSIZE;
    for (i = 0 ; i < n; i++ )
      {

      for (k=i+1; k<n; ++k)
        if (arr[k] < arr[i])
        {
          x = arr[i];
          arr[i] = arr[k];
          arr[k] = x;
        }
      }
    printf("Talen sorterade lägst till högst:");
    for(i=0; i<ARRSIZE; i++)
    { if(i%KOLUMNER == 0) printf("\n");
      printf("%3d ", arr[i]);
    }
  printf("\n\n");
}
