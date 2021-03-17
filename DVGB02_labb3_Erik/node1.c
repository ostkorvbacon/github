#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;



struct distance_table
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */

void printdt1(struct distance_table *dtptr)


{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}

void rtinit1()
{
  struct rtpkt packet;
  for (int i=0;i<4;i++){
    for (int j=0;j<4;j++){
      dt1.costs[i][j]=999;
    }
  }
  dt1.costs[0][0]=1;
  dt1.costs[2][2]=1;

  packet.sourceid=1;
  packet.mincost[0]=1;
  packet.mincost[1]=999;
  packet.mincost[2]=1;
  packet.mincost[3]=999;

  packet.destid=0;
  tolayer2(packet);

  packet.destid=2;
  tolayer2(packet);




}


void rtupdate1(struct rtpkt *rcvdpkt)


{

  struct rtpkt packet;
    for (int y=0;y<4;y++){
      for (int i=0;i<4;i++){
      //  for (int j=0;j<4;j++){
          if (y!=1 || i!=1 ){
            if(dt1.costs[y][i]>dt1.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y]){

              dt1.costs[y][i]=dt1.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y];

              for (int k=0;k<4;k++) packet.mincost[k]=999;
              packet.mincost[y]=dt1.costs[y][i];

              packet.sourceid=1;

              packet.destid=0;
              tolayer2(packet);
              packet.destid=2;
              tolayer2(packet);

            }

          }

        //}
      }
    }
printdt1(&dt1);
}






void linkhandler1(int linkid, int newcost)

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}
