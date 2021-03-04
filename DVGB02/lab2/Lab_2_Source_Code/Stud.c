/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

#include "Stud.h"
enum hostnum {
  A,
  B
};

/* called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message)
{
  int k, altbit = 0;
  struct pkt packet;
  int checksum = 0;
  for(k = 0; k < 20; k++)
  {
    checksum = checksum + (int)(message.data[k]);
  }
  packet.checksum = checksum;
  packet.seqnum = altbit;
  altbit++;
  for(k = 0; k < 20; k++)
  {
    packet.payload[k] = message.data[k];
  }
  /*
  printf("\nA seqnum: %d\n\n", packet.seqnum);
  printf("\nA checksum: %d\n\n", packet.checksum);
  */
  tolayer3(A,packet);
}

void B_output(struct msg message)  /* need be completed only for extra credit */
{}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{}


/* called when A's timer goes off */
void A_timerinterrupt()
{}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{}


/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
  int k, altbit = 0;
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
  /*
  printf("\nB seqnum: %d\n\n", packet.seqnum);
  printf("\nB checksum: %d\n\n", packet.checksum);
  printf("\nT checksum: %d\n\n", checksum);
  */
  if(packet.seqnum == altbit && packet.checksum == checksum)
  {
    printf("\n--ACK--\n\n");
    altbit++;
    tolayer5(B, message.data);
  }
}

/* called when B's timer goes off */
void B_timerinterrupt()
{}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{}
