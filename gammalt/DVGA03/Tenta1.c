#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    int el;
    struct node* next;
}node;

node *startList(int n);
node *swap(node *head, int a, int b);
int listStor(node *head);
void skrivList(node *head);

int main()
{
  int n = 4;
  int a, b;
  node *head;
  head = startList(n);
  skrivList(head);
  printf("skriv in a\n");
  scanf("%d", &a);
  printf("skriv in b\n");
  scanf("%d", &b);
  printf("\n");
  if( a < 2 || b < 2)
  {
    printf("fel\n");
    return 0;
  }
  if( a > n || b > n)
  {
    printf("fel\n");
    return 0;
  }
  head = swap(head, a, b);
  skrivList(head);

  return 0;
}

node *startList(int n)
{
  int i = 0;
  node * head2 = NULL;
  node * temp = NULL;
  node * norm = NULL;

  for(i; i<n; i++)
  {
    temp = (node*)malloc(sizeof(node)*1);
    temp->el = (i+1);
    temp->next = NULL;
    if(head2 == NULL)
      head2 = temp;
    else
    {
      norm = head2;
      while(norm->next != NULL)
      {
        norm = norm->next;
      }
      norm->next = temp;
    }
  }
  return head2;
}
// koden ska funka genom att hitta noderna före och efter de specificerade platsernas
// och helt enkelt sätta nodeAföre->next till nodeB
// nodeB->next till nodeAefter
// och nodeBföre->next till nodeA och nodeA->next till nodeBefter
// koden funkar inte och jag har inte tid att fixxa den men jag hoppas att jag visat principen väl
node *swap(node *head, int a, int b)
{
  int i, n; // skapar tillfälliga noder och variabler
  node *temp = NULL;
  node *tempA = head;
  node *tempB = head;
  node *nodeAfore = head;
  node *nodeBfore = head;

  n = listStor(head);

  for(i=0; i < a-2; i++)
  {
    nodeAfore = nodeAfore->next;
  }
  for(i=0; i < a-1; i++)
  {
    tempA = tempA->next;
  }

  for(i=0; i < b-2; i++)
  {
    nodeBfore = nodeBfore->next;
  }
  for(i=0; i < b-1; i++)
  {
    tempB = tempB->next;
  }

    nodeAfore->next = tempB;
    nodeBfore->next = tempA;
    temp = tempB->next;
    tempB->next = tempA->next;
    tempA->next = temp;

  return head;
}

int listStor(node *head)
{
  int n = 0;
  node * temp = head;
  while(temp != NULL)
  {
    n++;
    temp = temp->next;
  }
  return n;
}

void skrivList(node *head)
{
  node *temp = head;
  while(temp != NULL)
  {
    printf("%d \t", temp->el);
    temp = temp->next;
  }
  printf("\n");
}
