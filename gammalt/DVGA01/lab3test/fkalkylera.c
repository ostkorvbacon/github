#include "lab3.h"

void fkalkylera(int arr[ARRSIZE])
{
  int arrmin, arrmax,  i, k;
  float arr1, arr2,  arrsum = 0, arrmedel = 0, arrmedian = 0;
  arrmin = arr[ARRSIZE - ARRSIZE];
  arrmax = arr[ARRSIZE - 1];
    for(i=0; i<ARRSIZE; i++)
    {
      arrsum = arrsum + arr[i];
    }
    arrmedel = arrsum / ARRSIZE;
    if (ARRSIZE % 2 == 0)
    {
      arr1 = arr[(ARRSIZE - 1)/2];
      arr2 = arr[ARRSIZE/2];
      arrmedian = (arr1+arr2)/2;
    }
    else
    {
      arrmedian = arr[(ARRSIZE - 1)/2];
    }

    printf("Min-värde för talen är: %d\nMax-värde för talen är: %d", arrmin, arrmax);
    printf("\nMedelvärde för talen är: %f", arrmedel);
    printf("\nMedianen för talen är: %f\n\n", arrmedian);
}
