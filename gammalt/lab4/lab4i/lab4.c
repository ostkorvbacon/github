#include "lab4.h"

void meny()
{
  printf("Meny\n");
  printf("1. Lägg till fordon\n");
  printf("2. Skriv ut registret\n");
  printf("3. Sortera registret efter bilmärken i stigande bokstavsordning\n");
  printf("4. Sök efter ett specifikt fordon mha registernummret\n");
  printf("5. Sök efter ett specifikt fordon mha ägare\n");
  printf("6. Sök efter ett specifikt fordon mha registreringsnummret\n");
  printf("7. Sök efter ett specifikt fordon mha valfria fordonsegenskaper\n");
  printf("8. Ta bort ett fordon ur registret\n");
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
char fval2()
{
  char val[NSIZE];
  int valr;
  scanf("%s", val);
  valr = atoi(val);
  return valr;
}
void finmatning(bil b[RSIZE], int *ant)
{
  int val = 1;
  if(*ant<RSIZE)
  {
    printf("Hur många ägare har fordonet?\n1. En ägare\n2. Två ägare\n");
    val = fval2();
    if(val == 1)
    {
      printf("Mata in ägarens namn.\n");
      scanf("%s", b[*ant].agare.agare1.namn);
      printf("Mata in ägarens personnummer.\n");
      scanf("%s", b[*ant].agare.agare1.pnum);
      strcpy(b[*ant].agare.agare2.namn,"inget");
      strcpy(b[*ant].agare.agare2.pnum,"inget");

      printf("Mata in bilens märke\n");
      scanf("%s", b[*ant].marke);
      printf("Mata in bilesn årsmodell.\n");
      scanf("%s", b[*ant].arsmodell);
      printf("Mata in bilens registreringsnummer:\n");
      scanf("%s", b[*ant].reg);
      strcpy(b[*ant].count, "en");
      *ant = *ant + 1;
    }
    else if(val == 2)
    {
      printf("Mata in den första ägaren namn.\n");
      scanf("%s", b[*ant].agare.agare1.namn);
      printf("Mata in den första ägarens personnummer.\n");
      scanf("%s", b[*ant].agare.agare1.pnum);
      printf("Mata in den andra ägarens namn.\n");
      scanf("%s", b[*ant].agare.agare2.namn);
      printf("Mata in den andra ägarens personnummer.\n");
      scanf("%s", b[*ant].agare.agare2.pnum);

      printf("Mata in bilens märke\n");
      scanf("%s", b[*ant].marke);
      printf("Mata in bilesn årsmodell.\n");
      scanf("%s", b[*ant].arsmodell);
      printf("Mata in bilens registreringsnummer:\n");
      scanf("%s", b[*ant].reg);
      strcpy(b[*ant].count, "två");
      *ant = *ant + 1;
    }
  }
  else
  {
  printf("registret är fullt\n");
  }
  meny();
}
void fskriv(bil b[RSIZE], int r)
{
  if(strcmp(b[r].count, "en") == 0)
  {
    printf("Registernummer. %d\n", r+1);
    printf("Ägarens namn: %s\n", b[r].agare.agare1.namn);
    printf("Ägarens personnummer: %s\n", b[r].agare.agare1.pnum);
    printf("Bilmärke: %s\n", b[r].marke);
    printf("Årsmodell: %s\n", b[r].arsmodell);
    printf("Registreringsnummer: %s\n\n", b[r].reg);
  }
  else
  {
    printf("Registernummer. %d\n", r+1);
    printf("Första ägarens namn: %s\n", b[r].agare.agare1.namn);
    printf("Första ägarens personnummer: %s\n", b[r].agare.agare1.pnum);
    printf("Andra ägarens namn: %s\n", b[r].agare.agare2.namn);
    printf("Andra ägarens personnummer: %s\n", b[r].agare.agare2.pnum);
    printf("Bilmärke: %s\n", b[r].marke);
    printf("Årsmodell: %s\n", b[r].arsmodell);
    printf("Registreringsnummer: %s\n\n", b[r].reg);
  }
}
void fregister(bil b[RSIZE], int ant)
{
  int i;
  for(i=0;i<ant;i++)
    fskriv(b, i);
  meny();
}
void fsortera(bil b[RSIZE], int ant)
{
  if(ant == 1) printf("Det finns endast ett fordon i registret.\n");
  else if(ant<1) printf("Registret är tomt.");
  else
  {
    int i;
    int loop = 1;
    bil byt;
    char comp[NSIZE];
    char comp2[NSIZE];
    do
    {
      loop = 0;
      for(i=0;i<ant-1;i++)
      {
      strcpy(comp, b[i].marke);
      strcpy(comp2, b[i+1].marke);
      comp[0] = toupper(comp[0]);
      comp2[0] = toupper(comp2[0]);
      if(strcmp(comp, comp2)>0)
      {
        byt = b[i];
        b[i] = b[i+1];
        b[i+1] = byt;
        loop = 1;
      }
      }
    }
    while(loop == 1);
    printf("Registret har sorterats.\n");
  }
}
void fprint(bil b[RSIZE], int ant)
{
  int val;
  printf("Mata in registernummret du vill läsa.\n");
  val = fval2();
  if(val<=0 || val > ant)
    printf("Invalid input\n");
  else
    if(val<=ant)
      fskriv(b, (val-1));
  meny();
}
void fbort(bil b[RSIZE], int *ant)
{
  int val, i;
  printf("Mata in registernummret du vill rensa.\n");
  val = fval2();
  if(val<=0 || val > *ant)
    printf("Invalid input\n");
  else
  {
    if (val >= *ant+1)
      printf("Registernummret är oanvänt.\n");
    else
    {
      for (i = val - 1; i < *ant; i++)
      {
        b[i] = b[i+1];
      }
      *ant = *ant -1;
    }
  }
   meny();
}
void fsokperson(bil b[RSIZE],int ant)
{
  char namn[NSIZE];
  printf("Mata in personen vars register du söker.\n");
  scanf("%s", namn);
  int i;
  for(i=0; i<ant; i++)
  {
    if(strcmp(namn, b[i].agare.agare1.namn) == 0)
      fskriv(b, i);
    if(strcmp(namn, b[i].agare.agare2.namn) == 0)
      fskriv(b, i);
  }
  meny();
}
void fsokreg(bil b[RSIZE],int ant)
{
  char bil[NSIZE];
  printf("Mata in en bils registreringsnummer vars register du söker.\n");
  scanf("%s", bil);
  int i;
  for(i=0; i<ant; i++)
  {
    if(strcmp(bil, b[i].reg) == 0)
      fskriv(b, i);
  }
  meny();
}
void fsokmarke(bil b[RSIZE], int ant)
{
  char marke[NSIZE];
  printf("Mata in de bilmärke vars register du söker.\n");
  scanf("%s", marke);
  int i;
  for(i=0; i<ant; i++)
  {
    if(strcmp(marke, b[i].marke) == 0)
      fskriv(b, i);
  }
  meny();
}
void fsokarsmodell(bil b[RSIZE], int ant)
{
  char arsmodell[NSIZE];
  printf("Mata in det årsmodell vars register du söker.\n");
  scanf("%s", arsmodell);
  int i;
  for(i=0; i<ant; i++)
  {
    if(strcmp(arsmodell, b[i].arsmodell) == 0)
      fskriv(b, i);
  }
  meny();
}
void fsokkombi(bil b[RSIZE], int ant)
{
  char marke[NSIZE];
  printf("Mata in de bilmärke vars register du söker.\n");
  scanf("%s", marke);
  char arsmodell[NSIZE];
  printf("Mata in det årsmodell vars register du söker.\n");
  scanf("%s", arsmodell);
  int i;
  for(i=0; i<ant; i++)
  {
    if(strcmp(arsmodell, b[i].marke) == 0 && strcmp(arsmodell, b[i].arsmodell) == 0)
      fskriv(b, i);
  }
  meny();
}
void fmeny2(bil b[RSIZE], int ant)
{
  int val;
  printf("1. Sök efter alla fordon med ett visst märke\n");
  printf("2. Sök efter alla fordon med en specifik årsmodell\n");
  printf("3. Sök efter alla fordon med ett visst märke och årsmodell\n");
  val = fval2();
  if(val<1 || val>3)
  {
    printf("Invalid input\n");
    meny();
  }
  else
    switch(val)
    {
      case 1: fsokmarke(b, ant); break;
      case 2: fsokarsmodell(b, ant); break;
      case 3: fsokkombi(b, ant); break;
      default: printf("Invalid input\n"); meny();
    }
}
int main()
{
  int val, ant=0;
  bil b[RSIZE];
  finfile(b, &ant);
  meny();
  do
  {
    val = fval();
    switch (val)
    {
      case '1': finmatning(b, &ant); break;
      case '2': fregister(b, ant); break;
      case '3': fsortera(b, ant); break;
      case '4': fprint(b, ant); break;
      case '5': fsokperson(b, ant); break;
      case '6': fsokreg(b, ant); break;
      case '7': fmeny2(b, ant); break;
      case '8': fbort(b, &ant); break;
      case '0': printf("Exit.\n"); break;
      default: printf("Invalid input\n");
    }
  }while(val!='0');
  foutfile(b, ant);

  return 0;
}
