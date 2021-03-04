/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

#include "Stud.h"


/* called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message)
{
  int k, i = 0;
  struct pkt packet;
  int checksum = 0;
  for(k = 0; k < 20; k++)
  {
    checksum = checksum + (int)(message.data[i]);
  }
  packet.checksum = checksum;
  packet.seqnum = i;
  i++;
  strcpy(packet.payload, message.data);
  B_input(packet);

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
  int k = 0, i = 0;
  int checksum = 0;

  for(k; k < 20; k++)
  {
    checksum = checksum + (int)(packet.payload[i]);
  }
  if(packet.seqnum == i && packet.checksum == checksum)
  {
    i++;
    printf("\n--ACK--\n\n");
  }
}

/* called when B's timer goes off */
void B_timerinterrupt()
{}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{}
