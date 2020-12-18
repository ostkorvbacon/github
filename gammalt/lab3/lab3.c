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
        plats = mid;
        rad = plats /KOLUMNER;
        kolumn = plats - rad * KOLUMNER;
        printf("Talet finns på.\n");
        printf("Rad: %d\nKolumn: %d\n", rad+1, kolumn+1);
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
char fscan()
{
  char val1[100];
  scanf("%s", val1);
  if(strlen(val1)>1)
  val1[0]= -1;
  return val1[0];
}
void fmenu(int arr[ARRSIZE])
{
  int v;
  char val;

  printf("\n      Main Menu\n\n");
  printf("Välj från alternativen nedanför.\n");
  printf("1: Generera en slumpad lista med tal\n");
  printf("2: Sortera talen från lägst till högst\n");
  printf("3: Ge mig Min/Max/Medel-värden och Medianen för talen\n");
  printf("4: Hitta ett specifikt tal\n");
  printf("5: Rensa kommandotolken\n");
  printf("0: Avsluta programet\n");

  do
  {
    val= fscan();
    switch (val)
    {
      case '1':
        v = 1;
        fgenerera(arr);
        break;
      case '2':
        if (v != 1 && v != 2)
        {
          printf("Du måste generera en lista med tal först.\n\n");
        }
        else if (v == 2)
        {
          printf("Du har redan sorterat talen.\n\n");
        }
        else
        {
        v = 2;
        fsortera(arr);
        }
        break;
      case '3':
        if (v == 2 )
        {
          fkalkylera(arr);
        }
        else if (v == 1)
        {
          printf("Du måste sortera din lista först.\n\n");
        }
        else
        {
          printf("Du måste generera och sortera en lista med tal först.\n\n");
        }
        break;

      case '4':
        if (v == 2)
        {
          fbinsok(arr);
        }
        else if (v == 1)
        {
          printf("Du måste sortera din lista först.\n\n");
        }
        else
        {
          printf("Du måste generera och sortera en lista med tal först.\n\n");
        }
        break;

      case '5':
        printf("\033[2J");
        printf("\n      Main Menu\n\n");
        printf("Välj från alternativen nedanför.\n");
        printf("1: Generera en slumpad lista med taL\n");
        printf("2: sortera talen från lägst till högst\n");
        printf("3: Ge mig Min/Max/Medel-värden och Medianen för talen\n");
        printf("4: Hitta ett specifikt tal\n");
        printf("5: Rensa kommandotolken\n");
        printf("0: Avsluta programet\n");
        break;
      case '0':
        printf("Exit");
        break;
      default:
        printf("Invalid input\n");
    }
  }
  while (val != '0');
}

int main()
{
  int arr[ARRSIZE];
  fmenu(arr);

  return 0;
}
