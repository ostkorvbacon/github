#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt3;

/* students to write the following two routines, and maybe some others */

void printdt3(struct distance_table *dtptr)


{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}
void rtinit3()
{
  struct rtpkt packet;
  for (int i=0;i<4;i++){
    for (int j=0;j<4;j++){
      dt3.costs[i][j]=999;
    }
  }
  dt3.costs[0][0]=7;

  dt3.costs[2][2]=2;

  packet.sourceid=3;
  packet.mincost[0]=7;
  packet.mincost[1]=999;
  packet.mincost[2]=2;
  packet.mincost[3]=999;

  packet.destid=0;
  tolayer2(packet);
  packet.destid=2;

  tolayer2(packet);

}


void rtupdate3(struct rtpkt *rcvdpkt)


{
  struct rtpkt packet;
    for (int y=0;y<3;y++){
      for (int i=0;i<3;i++){
      //  for (int j=0;j<3;j++){

          if(dt3.costs[y][i]>dt3.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y]){

            dt3.costs[y][i]=dt3.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y];

            for (int k=0;k<4;k++) packet.mincost[k]=999;
            packet.mincost[y]=dt3.costs[y][i];

            packet.sourceid=3;
            packet.destid=0;

            tolayer2(packet);

            packet.destid=2;
            tolayer2(packet);

          }

        //}
      }
    }
printdt3(&dt3);
}
