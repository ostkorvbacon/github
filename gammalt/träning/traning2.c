#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RSIZE 10
#define NSIZE 20
typedef struct{
  char namn[NSIZE];
  int pnum;
  char adress[NSIZE];
}person;
typedef struct{
  char marke[NSIZE];
  int arsmodell;
  char reg[NSIZE];
  person person;
}bil;

void meny()
{
  printf("Meny\n");
  printf("1. Lägg till fordon\n");
  printf("2. Skriv ut registret\n");
  printf("0. Avsluta\n");
}
char fval()
{
  char val[NSIZE];
  scanf("%s", val);
  if(strlen(val)>1)
  val[0]= -1;
  return val[0];
}
void fmeny2()
{
  printf("1. Välj ett specifikt fordon\n");
  printf("0. Skriv ut alla\n");
}
char fval2()
{
  char val[NSIZE];
  int valr;
  scanf("%s", val);
  valr = atoi(val);
  printf("%d", valr);
  return valr;
}
void finmatning(int *ant, bil b[RSIZE])
{
  if(*ant<RSIZE)
  {
    printf("Mata in ägarens namn.\n");
    scanf("%s", b[*ant].person.namn);
    printf("Mata in ägarens personnummer.\n");
    scanf("%d", &(b[*ant].person.pnum));
    printf("Mata in ägarens adress:\n ");
    scanf("%s", b[*ant].person.adress);

    printf("Mata in bilens märke\n");
    scanf("%s", b[*ant].marke);
    printf("Mata in bilesn årsmodell.\n");
    scanf("%d", &(b[*ant].arsmodell));
    printf("Mata in bilens registreringsnummer:\n ");
    scanf("%s", b[*ant].reg);
  }
  else printf("registret är fullt\n");
  *ant = *ant + 1;
}
void fregister(bil b[RSIZE], int ant)
{
  int val2;
  int i;

    for(i=0;i<ant;i++)
    {
      printf("Ägare %d\n", i+1);
      printf("Namn: %s\n", b[i].person.namn);
      printf("Personnummer: %d\n", b[i].person.pnum);
      printf("Adress: %s\n", b[i].person.adress);

      printf("Fordon %d\n", i+1);
      printf("Märke: %s\n", b[i].marke);
      printf("Årsmodell: %d\n", b[i].arsmodell);
      printf("Registreringsnummer: %s\n\n", b[i].reg);
    }
}

int main()
{
  int val;
  int ant=0;
  bil b[RSIZE];
  person p[RSIZE];
  do
  {
    meny();
    val = fval();
    switch (val)
    {
      case '1': finmatning(&ant, b); break;
      case '2': fregister(b, ant); break;
      case '0': printf("Exit.\n"); break;
      default: printf("Invalid input\n");
    }

  }while(val!='0');
}
