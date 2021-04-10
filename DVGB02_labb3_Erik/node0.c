#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt0;

void printdt0(struct distance_table *dtptr)


{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

/* students to write the following two routines, and maybe some others */

void rtinit0()
{
struct rtpkt packet;
for (int i=0;i<4;i++){
  for (int j=0;j<4;j++){
    dt0.costs[i][j]=999;
  }
}


dt0.costs[1][1]=1;
dt0.costs[2][2]=3;
dt0.costs[3][3]=7;

packet.sourceid=0;
packet.mincost[0]=999;
packet.mincost[1]=1;
packet.mincost[2]=3;
packet.mincost[3]=7;

packet.destid=1;
tolayer2(packet);
packet.destid=2;
tolayer2(packet);
packet.destid=3;
tolayer2(packet);


//printdt0(&dt0);

}


void rtupdate0(struct rtpkt *rcvdpkt)

{struct rtpkt packet;
  for (int y=1;y<4;y++){
    for (int i=1;i<4;i++){
      //for (int j=1;j<4;j++){

        if(dt0.costs[y][i]>dt0.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y]){

          dt0.costs[y][i]=dt0.costs[rcvdpkt->sourceid][i]+rcvdpkt->mincost[y];

          for (int k=0;k<4;k++) packet.mincost[k]=999;
          packet.mincost[y]=dt0.costs[y][i];

          packet.sourceid=0;

          packet.destid=1;
          tolayer2(packet);
          packet.destid=2;
          tolayer2(packet);
          packet.destid=3;
          tolayer2(packet);


        }

      //}
    }
  }


printdt0(&dt0);
}




void linkhandler0(int linkid, int newcost)


/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}
