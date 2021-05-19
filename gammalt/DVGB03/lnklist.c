typedef struct{
  int data;
  int prio;
  que *next;
}que;


que insert(que head, int data,int prio)
{
  que temp;
  temp = head;
  new = create_new(data,prio);

  while(temp.next != NUll)
  {
    temp = temp.next;
    if  (prio < temp.prio);
    {
      // inserta new noden här
      return head;
    }


  }

  return head;
}

int extract_max(que head)
{
  que temp;
  temp = head;
  while(temp.next != NUll)
  {
    temp = temp.next;
    return head.prio;
  }
}
que increase_key(que head, int newkey, int data)
{
  que temp;
  temp = head;
  while(temp.next != NUll)
  {
    temp = temp.next;
    if(temp.data == data)
    {
      temp.prio = newkey;
      return head;
    }
  }

}
