#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int rakna_versaler(char* string)
{
int i;
int antal=0;
for(i=0; string[i] != '\0' ;i++)
if(isupper(string[i]))
antal++;
return antal;
}

int rakna(char *string, int antrek, int i)
{
  if(string[i] == '\0')
    return antrek;
  if(isupper(string[i]))
  {
    antrek++;
    i++;
    rakna(string, antrek, i);
  }
  else
  {
    i++;
    rakna(string, antrek, i);
  }
}


int main()
{
  int i= 0;
  char string[]= "JagHeterOLLE";
  int antal;
  int antrek= 0;
  antal = rakna(string, antrek, i);
  printf("%d\n", antal);

  return 0;
}
