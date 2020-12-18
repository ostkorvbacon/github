#include <stdio.h>

 int main()
 {
   char data;
   int read;
   FILE *infile, *outfile;
   infile = fopen("fil.txt", "r");
   outfile = fopen("kopia.txt", "w");
   if(infile)
   {
     printf("Det gick bra\n");
     fscanf(infile,"%c", &data);
     read = fread(&data, sizeof(char), 1, infile);
     while(read != 0)
     {
       printf("%c", data);
       fprintf(outfile, "%c", data);
       read = fread(&data, sizeof(char), 1, infile);
     }
     fclose(infile);
   }
   else
    printf("Det gick inte bra\n");

   return 0;
 }
