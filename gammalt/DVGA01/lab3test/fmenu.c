#include "lab3.h"

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
  printf("6: Avsluta programet\n");

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
        if (v != 1 && v != 2)
        {
          printf("Du måste generera och sortera en lista med tal först.\n\n");
        }
        else
        {
          fkalkylera(arr);
        }
        break;

      case '4':
        if (v != 1 && v != 2)
        {
          printf("Du måste generera och sortera en lista med tal först.\n\n");
        }
        else
        {
          fbinsok(arr);
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
        printf("6: Avsluta programet\n");
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
