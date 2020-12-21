#include "lab3.h"

void fbinsok(int arr[ARRSIZE])
{
  int start, mid, end, tal, i, plats, rad, kolumn;
  for (i = 0; i < ARRSIZE; i++)
  {
    printf("Mata in talet i arrayen du söker.\n");
    scanf("%d", &tal);

    start = 0;
    end = ARRSIZE - 1;
    mid = (start+end)/2;

    while (start <= end)
    {
      if (arr[mid] < tal)
         start = mid + 1;
      else if (arr[mid] == tal)
      {
        plats = mid + 1;
        rad = plats /KOLUMNER;
        kolumn = plats - rad * KOLUMNER;
        printf("Talet finns på.\n");
        printf("Rad: %d\nKolumn: %d\n", rad+1, kolumn);
        i = ARRSIZE;
        break;
      }
      else
        end = mid - 1;
        mid = (start + end)/2;
    }
    if (start > end)
    {
      printf("Talet %d finns inte i arrayen.\n", tal);
      i = ARRSIZE;
    }
  }
}
