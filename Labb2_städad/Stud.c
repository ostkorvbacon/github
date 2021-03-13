#include "Stud.h"


/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional or bidirectional
   data transfer protocols (from A to B. Bidirectional transfer of data
   is for extra credit and is not required).  Network properties:
   - one way network delay averages five time units (longer if there
       are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
       or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
       (although some can be lost).
**********************************************************************/


/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/



int checksum(struct pkt packet) {
    int checksum = 0;
    for (int i = 0; i < 20; ++i)
        checksum += packet.payload[i];
    return checksum;
}

/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
    if (A_state != 1) return;


    packet.seqnum = A_seqnum;
    memmove(packet.payload, message.data, 20);
    packet.checksum = checksum(packet);
    A_state = 0;
    tolayer3(0, packet);
    starttimer(0, TIMEOUT);
}

/* need be completed only for extra credit */
void B_output(struct msg message) {

}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {

    if (packet.checksum != checksum(packet)||packet.acknum != A_seqnum) return;


    stoptimer(0);
    A_seqnum= 1 - A_seqnum;
    A_state = 1;
}

/* called when A's timer goes off */
void A_timerinterrupt(void) {
    if (A_state == 0) {
      tolayer3(0, packet);
      starttimer(0, TIMEOUT);
    }
}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(void) {
    A_state = 1;
    A_seqnum= 0;

}

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet) {

    if (packet.checksum != checksum(packet) || packet.seqnum != B_seqnum) {


        ack.acknum = 1-B_seqnum;
        ack.checksum = checksum(ack);
        tolayer3(1, ack);
        return;
    }

    ack.acknum = B_seqnum;
    ack.checksum = checksum(ack);
    tolayer3(1, ack);

    tolayer5(1, packet.payload);
    B_seqnum= 1 - B_seqnum;
}

/* called when B's timer goes off */
void B_timerinterrupt(void) {//Not required for solution

}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init(void) {
    B_seqnum= 0;
}
