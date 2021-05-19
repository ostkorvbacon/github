#include <stdio.h>
#include <stdlib.h>

#define LISTSIZE 20
// this is for list of nodes i.e list of lists
typedef struct{
    int list[LISTSIZE];
    int sum
}listoflist;

int main()
{
  int i, k;
  listoflists *arr;
  createLists(arr); //påhittat funktion som helt enkelt fyller listorna med värden. har inte tid att skriva.
  int temp;
  for i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++);
  {
    for (k = 0; k < LISTSIZE; k++)
    {
      temp = temp + arr[i].list[k];
    }
    arr[i].sum = temp;
  }
  sort(arr); // simpel funktion som sorterar arrayen baserat på sum; har inte tid att skriva.
  return 0;

}
