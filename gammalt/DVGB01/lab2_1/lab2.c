#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
int pid;
int arrT;
int burstT;
}pif;
pif temp;

int schedf(char *fName, char *algName, int tQuant)
{

  pif pif[20];
  int time=0;
  int i = 0;
   float avgWait, avgTurn, sumWait, sumTurn;

  FILE *infile;
  int k=0;
  infile = fopen(fName, "r");
  int n = 0;
  if(infile != NULL)
  {
    while(fscanf(infile, "%d", &pif[i].pid) != EOF)
    {
      fscanf(infile, "%d", &pif[i].arrT);
      fscanf(infile, "%d", &pif[i].burstT);

      i++;
      n++;
    }

  }
  else
  {
    printf("fel\n");
  }
  fclose(infile);ls
  int waitTime[n];
  int turnTime[n];

  for(i=0; i<n; i++)
  {
    waitTime[i] = 0;
    turnTime[i] = 0;
  }

  //printf("data points %d\n", n);
  if (strcmp(algName, "FCFS") == 0) //First come first serve
  {
      printf("FCFS\n");
      while (k==0){
        k=1;
        for (i=0;i<(n-1);i++){

          if (pif[i].arrT>pif[i+1].arrT){
            k=0;
            temp=pif[i];
            pif[i]=pif[i+1];
            pif[i+1]=temp;
          }
        }
      }

	//int idle=1;

	time=0;
	for (i=0;i<n;i++){
		int done=0;
		while (done==0) {

			if (done==0 && time>=pif[i].arrT ) {
			time=time+pif[i].burstT;
			  turnTime[i]=time-pif[i].arrT;
			waitTime[i]=turnTime[i]-pif[i].burstT;
			done=1;

			}

			else time++;
		}


		}

  }

  else if (strcmp(algName, "SJF") == 0) // Shortest-job first
  {
    printf("SJF\n");
    while (k==0){
      k=1;
      for (i=0;i<(n-1);i++){

        if (pif[i].burstT>pif[i+1].burstT){
          k=0;
          temp=pif[i];
          pif[i]=pif[i+1];
          pif[i+1]=temp;
        }
      }
    }

       time=0;
	for (i=0;i<n;i++){
		int done=0;
		while (done==0) {

			if (done==0 && time>=pif[i].arrT ) {
			time=time+pif[i].burstT;
			  turnTime[i]=time-pif[i].arrT;
			waitTime[i]=turnTime[i]-pif[i].burstT;
			done=1;

			}

			else time++;
		}


		}

  }

  else if (strcmp(algName, "RR") == 0) // Round robin
  {
    printf("RR\n");
    while (k==0){
      k=1;
      for (i=0;i<(n-1);i++){

        if (pif[i].arrT>pif[i+1].arrT){
          k=0;
          temp=pif[i];
          pif[i]=pif[i+1];
          pif[i+1]=temp;
        }
      }
    }


    int tempburst[n];
    for(i=0 ;i<n; i++)
    {
      tempburst[i] = pif[i].burstT;
    }
    //for(i=0; i<n; i++) printf("%d\n", tempburst[i]);
    int k2 = 1;
    while(k2 == 1)
    {
      k2 = 0;
      for(i=0 ;i<n; i++)
      {
        if(tempburst[i] > 0)
        {
          k2=1;
          if( tempburst[i]> tQuant)
          {
            time = time + tQuant;
            tempburst[i] = tempburst[i] - tQuant;
          }
          else
          {
            time = time + tempburst[i];
            tempburst[i] = 0;
            waitTime[i] = time - pif[i].burstT;
            turnTime[i] = time;
          }
        }


      }
    }




  }

  else {
    printf("Ogiltig algoritm\n");
    return 0;

	}

    for(i=0; i<n; i++)
    {
      sumWait= sumWait + waitTime[i];
      sumTurn= sumTurn + turnTime[i];
    }
    avgWait = sumWait / n;
    avgTurn = sumTurn / n;

    printf("\n PID	Arrival Time	Burst Time	Waiting Time	Turnaround Time\n");
      for(i=0; i<n; i++)
    {
      printf("%d	%d		%d		%d		%d\n", pif[i].pid,pif[i].arrT,pif[i].burstT,waitTime[i],turnTime[i]);

    }
    printf("Average wait time %f\n", avgWait);
    printf("Average turnaround time %f\n", avgTurn);


  return 0;
}

int main(int argc, char**argv)
{
	char *fName=NULL;
	char *algName=NULL;
	int tQuant=0;
fName =argv[1];
algName =argv[2];
tQuant =atoi(argv[3]);


  //char fName[] = "PIF.txt";
  //char algName[] = "RR";
 // int tQuant = 4;

  schedf(fName, algName, tQuant);

  return 0;
}
