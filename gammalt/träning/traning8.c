#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
char namn[] = "Olle";
char *p1;
p1 = (char*) malloc(4 * sizeof(char));
p1 = namn;
namn[2] = (*p1)+1;
namn[3] = *namn +10;
printf("%s\n", namn);




  return 0;
}
