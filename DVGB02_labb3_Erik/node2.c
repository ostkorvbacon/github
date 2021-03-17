#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt2;


/* students to write the following two routines, and maybe some others */

void printdt2(struct distance_table *dtptr)


{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}

void rtinit2()
{
  struct rtpkt packet;
  for (int i=0;i<4;i++){
    for (int j=0;j<4;j++){
      dt2.costs[i][j]=999;
    }
  }
  dt2.costs[0][0]=3;
  dt2.costs[1][1]=1;
  dt2.costs[3][3]=2;

  packet.sourceid=2;
  packet.mincost[0]=3;
  packet.mincost[1]=1;
  packet.mincost[2]=999;
  packet.mincost[3]=2;

  packet.destid=0;
  tolayer2(packet);
  packet.destid=1;
  tolayer2(packet);
  packet.destid=3;
  tolayer2(packet);


}


void rtupdate2(struct rtpkt *rcvdpkt)


{
  struct rtpkt packet;
    for (int y=0;y<4;y++){
      for (int i=0;i<4;i++){
        //for (int j=0;j<4;j++){
          if (y!=2 || i!=2){

            if(dt2.costs[y][i]>dt2.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y]){

              dt2.costs[y][i]=dt2.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y];

              for (int k=0;k<4;k++) packet.mincost[k]=999;
              packet.mincost[y]=dt2.costs[y][i];

              packet.sourceid=2;
              packet.destid=0;
              tolayer2(packet);
              packet.destid=1;
              tolayer2(packet);
              packet.destid=3;
              tolayer2(packet);

            }

        }
      //}
      }
    }
printdt2(&dt2);
}
