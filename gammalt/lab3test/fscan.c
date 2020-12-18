#include "lab3.h"

char fscan()
{
  char val1[100];
  scanf("%s", val1);
  if(strlen(val1)>1)
  val1[0]= -1;
  return val1[0];
}
