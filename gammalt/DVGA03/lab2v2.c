#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int el;
    struct node* next;
}node;

node *startList(int n);
void meny();
int fval();
void skrivList(node *head);
int listStor(node *head);
int addSist(node *head);
int addFri(node *head);
int hittaEl(node *head);
int bortEl(node *head, int j);
int bortPlats(node *head);




int main()
{
  int n=4; //Nummber of Nodes in list, i start with 4 nodes to make program easier to use
  int val, j;
  node * head;
  head = startList(n);
  meny();
  do
  {
    val = fval();
    switch (val)
    {
      case 1: skrivList(head); break;
      case 2: n = listStor(head); printf("Listan har %d noder.\n", n); break;
      case 3: addSist(head); break;
      case 4: addFri(head); break;
      case 5: j = hittaEl(head);
                if(j == 0)
                {
                  printf("El finns inte i listan\n");
                  break;
                }
                else
                {
                  bortEl(head, j);
                  break;
                }
      case 6: bortPlats(head); break;
      case 7: break;
      case 8: break;
      case 9: break;
      case 10: break;
      case 11: break;
      case 12: break;
      case 0: printf("Exit.\n"); break;
      default: printf("Invalid input val är %d \n", val);
    }
  }while(val != 0);

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

void meny()
{
  printf("---- Meny ----\n");
  printf("1.  Skriv ut listan.\n");
  printf("2.  Skriv ut listans stolek.\n");
  printf("3.  Lägg till ett heltal sist i listan.\n");
  printf("4.  Lägg till ett heltal på valfri plats.\n");
  printf("5.  Ta bort ett givet heltal.\n");
  printf("6.  Ta bort ett heltal på valfri plats.\n");
  printf("7.  Töm listan.\n");
  printf("8.  Vänd på listan.\n");
  printf("9.  Skifta lista ett steg åt vänster och lägg första heltalet sist.\n");
  printf("10. Skifta listan ett steg åt höger och lägg sista heltalet först.\n");
  printf("11. Sortera lista, lägsta heltalet först.\n");
  printf("12. Skriv ut startadress för listan.\n");
  printf("0. Avsluta.\n");
}

int fval()
{
  int val;
  scanf("%d", &val);
  if(val > 12 || val < 0)
    val = -1;
  return val;
}

void skrivList(node *head)
{
  node * temp = head;

  while(temp != NULL)
  {
    printf("%d \t", temp->el);
    temp = temp->next;
  }
  printf("\n");
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

int addSist(node *head)
{
  node * temp = NULL;
  temp = (node*)malloc(sizeof(node));
  printf("Skriv in element: ");
  scanf("%d", &temp->el);
  printf("\n");

  temp->next = NULL;
  node * temp2 = head;
  while(temp2->next != NULL)
  {
    temp2 = temp2->next;
  }
  temp2->next = temp;
  return 0;
}

int addFri(node *head)
{
  int k, i=0;
  node * temp = NULL;
  temp = (node*)malloc(sizeof(node));
  printf("Skriv in element: ");
  scanf("%d", &temp->el);
  printf("\n");
  printf("Skriv in en plats: ");
  scanf("%d", &k);
  printf("\n");

  temp->next = NULL;
  node * tempH1 = head;
  node * tempH2 = head;
  if(k==1)
  {
    temp->next = tempH1;
    head = temp;
    return 0;
  }
  for (i = 0; i < (k-2); i++)
  {
		if (tempH1->next != NULL)
      tempH1=tempH1->next;
		else
    {
			printf("Postitionen finns inte.\n");
      free(temp);
			return 0;
		}
	}
  for (i = 0; i < (k-1); i++)
  {
		if (tempH2->next != NULL)
      tempH2 = tempH2->next;
		else
      tempH2 = NULL;
	}
  temp->next = tempH2;
  tempH1->next = temp;
  return 0;

}

int hittaEl(node *head)
{
  node * temp = head;
  int k, i=0, j=0;
  printf("Skriv in elementet du vill ta bort: ");
  scanf("%d", &k);
  printf("\n");
  while(temp != NULL)
  {
    i++;
    if(k == temp->el)
    {
      j = i;
      return j;
    }
    temp = temp->next;
  }

  return 0;
}

int bortEl(node *head, int j)
{
  int i = 0;
  node * temp = head;
  node * tempH1 = head;
  node * tempH2 = head;
  node * tempH3 = head;
  printf("position %d \n", j);

  if(j == 1)
  {
    head = temp->next;
    free(temp);
    return 0;
  }
  for(i=0; i < j-2; i++)
  {
      tempH1=tempH1->next;
  }
  for(i=0; i < j-1; i++)
  {
      tempH2=tempH2->next;
  }
  for(i=0; i < j; i++)
  {
    if (tempH3->next != NULL)
      tempH3=tempH3->next;
    else
    {
      tempH1->next = NULL;
      free(tempH3);
      head = temp;
      return 0;
    }
  }
  tempH1->next = tempH3;
  free(tempH2);

  head = temp;
  return 0;
}
int bortPlats(node *head)
{
  int k;
  node * temp = head;
  printf("Skriv in en plats: ");
  scanf("%d", &k);
  printf("\n");
  if(k > 0 && k <= listStor(temp))
    bortEl(temp, k);
  else
  {
    printf("Platsen finns inte i listan.\n");
  }
  return 0;
}
