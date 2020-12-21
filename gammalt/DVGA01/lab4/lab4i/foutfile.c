#include "lab4.h"

void foutfile(bil b[RSIZE], int ant)
{
  FILE *outfile;
  int i = 0;
  outfile = fopen("register.txt", "w");
  if(outfile != NULL)
  {
  for(i=0; i< ant  ; i++)
    {
      fprintf(outfile, "\n%s ", b[i].agare.agare1.namn);
      fprintf(outfile, "%s ", b[i].agare.agare1.pnum);
      fprintf(outfile, "%s ", b[i].agare.agare2.namn);
      fprintf(outfile, "%s ", b[i].agare.agare2.pnum);
      fprintf(outfile, "%s ", b[i].marke);
      fprintf(outfile, "%s ", b[i].arsmodell);
      fprintf(outfile, "%s ", b[i].reg);
      fprintf(outfile, "%s\n", b[i].count);
    }
    fclose(outfile);
  }
  else printf("Registret kunde inte öppnas\n");
}
