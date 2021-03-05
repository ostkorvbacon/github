/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

#include "Stud.h"

enum hostnum {
  A,
  B
};
#define CHECK 1895
int altbitA = 0;
int altbitB = 0;
struct pkt packet;
struct pkt ack;
int count=10;
int countA=10;

/* called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message)
{
  int k;
  int checksum = 0;
  for(k = 0; k < 20; k++)
  {
    checksum = checksum + (int)(message.data[k]);
  }
  packet.checksum = checksum;
  packet.seqnum = altbitA;

  for(k = 0; k < 20; k++)
  {
    packet.payload[k] = message.data[k];
  }

  tolayer3(A,packet);
  printf("Sent packet from A seqnum: %d\n",packet.seqnum);
  starttimer(A,200);
}



void B_output(struct msg message) //NOT REQUIRED /* need be completed only for extra credit */
{}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  if(packet.acknum ==altbitA  && packet.checksum == CHECK)
  {
    stoptimer(A);
    printf("A recived ack from B acknum: %d\n\n",packet.acknum);
    if (altbitA==0) altbitA=1;
    else altbitA=0;

    countA--;

  }
}


/* called when A's timer goes off */
void A_timerinterrupt()
{
  if (countA>0)
  {
    tolayer3(A,packet);
    printf("countA %d\n",countA);
    starttimer(A,200);
  }
}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(int a)
{
  countA=a;


}


/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{


  int k;
  int checksum = 0;
  struct msg message;
  for(k = 0; k < 20; k++)
  {
    message.data[k] = packet.payload[k];
  }
  for(k = 0; k < 20; k++)
  {
    checksum = checksum + (int)(packet.payload[k]);
  }


  if(packet.seqnum == altbitB && packet.checksum == checksum)
  {


    printf("B received packet seqnum=%d\n",packet.seqnum);
    ack.acknum=altbitB;
    ack.checksum=CHECK;
    printf("sent ack from B acknum: %d\n",ack.acknum);

    tolayer3(B,ack);
    tolayer5(B, message.data);


    if (count<1)
    {
      stoptimer(B);
      for (int i=0;i<4;i++)
      {
        sleep(1);
        tolayer3(B,ack);
      }

    }
    if (altbitB==0) altbitB=1;
    else altbitB=0;

    count--;
  }
}

/* called when B's timer goes off */
void B_timerinterrupt()
{ if (count>0)
  {
    tolayer3(B,ack);
    starttimer(B,200);
  }
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init(int a)
{ count=a;
  starttimer(B,200);}
