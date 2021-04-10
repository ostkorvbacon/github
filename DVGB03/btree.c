#include <stdio.h>
#include <stdlib.h>

#define DGREMAX 3
#define DGREMIN 2

struct Node {
  int data[DGREMAX + 1], num, leaf;
  struct Node *next[DGREMAX + 1];
};
struct Node insertfirst(struct Node Head)
{
  printf("Data: \n");
  scanf("%d", &Head.data[0]);
  Head.num = 1;
  Head.leaf = 1;
}

struct Node insertval(struct Node Head, int val)
{
  int i, temp;
  if (Head.leaf == 1)
  {
    while(1)
    {
      if(Head.num < DGREMAX) //checks if there is room in headnode
      {
        for(i = Head.num; i > 0; i--)
          if(val > Head.data[i])
            Head.data[i+1] = val;
      }
      if(Head.num == DGREMAX)
      {
        for(i = Head.num; i > 0; i--)
          if(val > Head.data[i])
            Head.data[i+1] = val;
        struct Node *child1;
        child1 = (struct Node*)malloc(sizeof(struct Node));
        struct Node *child2;
        child2 = (struct Node*)malloc(sizeof(struct Node));
        for(i = 0; i < DGREMAX/2; i++)
        {
          temp = Head.data[i];
          child1.data[i] = temp;
          temp = child1.num;
          child1.num = temp +1;
        }
        int k;
        k= 0;
        for(i = DGREMAX; i < DGREMAX; i++)
        {

          child2.data[k] = Head.data[i];
          child1.num ++;
          k++;
        }
        insertval(*Head, Head.data[DGREMAX/2]);
      }
    }
  }
  else // if not in leaf go to the right leaf.
  {
    for(i = 0; i< Head.num; i++)
    {
      if(val < Head.data[i])
        {
          insertval(*Head.next[i], val);
        }

    }
  }
}

int main()
{
  struct Node *Head;
  Head = (struct Node*)malloc(sizeof(struct Node));
  insertfirst(*Head);
  printf("Data: \n");
  int val, i;
  scanf("%d", &val);
  insertval(*Head, val);

  return 0;
}
