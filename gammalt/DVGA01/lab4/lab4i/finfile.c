#include "lab4.h"

void finfile(bil b[RSIZE], int *ant)
{
  FILE *infile;
  int i = 0;
  infile = fopen("register.txt", "r");
  if(infile != NULL)
  {
  while(fscanf(infile, "%s", b[i].agare.agare1.namn) != EOF)
  {
    fscanf(infile, "%s", b[i].agare.agare1.pnum);
    fscanf(infile, "%s", b[i].agare.agare2.namn);
    fscanf(infile, "%s", b[i].agare.agare2.pnum);
    fscanf(infile, "%s", b[i].marke);
    fscanf(infile, "%s", b[i].arsmodell);
    fscanf(infile, "%s", b[i].reg);
    fscanf(infile, "%s", b[i].count);
    i++;
  }
  *ant = i;
  fclose(infile);
  }
  else printf("Registret kunde inte öppnas\n");
}
