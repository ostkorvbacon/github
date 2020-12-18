#include "list.h"
#include "node.h"
int n; // variable to save size of linked list.
int in, in2; // Variable to save inputs from user.

// Calls for funktion in list.c to print list.
void case1(node *head)
{
  skrivList(head);
}

// Calls for funktion in list.c to return number of nodes
// and then prints out number of nodes.
void case2(node *head)
{
  n = listStor(head);
  printf("Listan har %d noder.\n", n);
}

// Calls for funktion in list.c to add element to a new node that is placed
// at the end of the linked list.
node *case3(node *head)
{
  printf("Skriv in element: ");
  scanf("%d", &in);
  printf("\n");
  head = addSist(head, in);
  return head;
}

// calls for funktion in list.c to add element to a node and places that node
// in a place designated by the user.
node *case4(node *head)
{
  printf("Skriv in element: ");
  scanf("%d", &in);
  printf("\n");
  printf("Skriv in en position: ");
  scanf("%d", &in2);
  printf("\n");
  head = addFri(head, in, in2);
  return head;
}

// calls for funktions in list.c to remove the first node that contains
// a element that has a specific value designated by the user.
node *case5(node *head)
{
  int j;
  printf("Skriv in elementet du vill ta bort: ");
  scanf("%d", &in);
  printf("\n");
  j = hittaEl(head, in);
  if(j == 0)
  {
    printf("Värdet finns inte i listan\n");
    return head;
  }
  return bortEl(head, j);
}

// calls for a funktion in list.c to remove a node in a place designated
// by the user.
node *case6(node *head)
{
  printf("Skriv in en position: ");
  scanf("%d", &in);
  printf("\n");

  if(in > 0 && in <= listStor(head))
    return bortEl(head, in);
  else
  {
    printf("Positionen finns inte.\n");
    return head;
  }
}

// calls for a funktion in list.c to remove and free every node in the list.
node *case7(node *head)
{
head = tomLista(head);
return head;
}

node *case8(node* head)
{
head = vandList(head);
return head;
}

// calls for a funktion in list.c that removes the first node from the list
// and reatatches the first node to the end of the list.
node *case9(node *head)
{
head = skiftV(head);
return head;
}

// calls for a funktion in list.c that removes the last node from the list
// and reatatches the last node to the start of the list.
node *case10(node *head)
{
head = skiftH(head);
return head;
}

// calls for a funktion in list.c that sorts the nodes in the list based on
// the values of their elements in acending order.
node *case11(node *head)
{
head = sortList(head);
return head;
}

// calls for a funktion in list.c that finds and prints the adress
// of the first node
void case12(node *head)
{
skrivAdrs(head);
}

// calls for a funktion in list.c to remove and free every node in the list.
// the funktion then prints exit.
void case0(node *head)
{
tomLista(head); printf("Exit.\n");
}
