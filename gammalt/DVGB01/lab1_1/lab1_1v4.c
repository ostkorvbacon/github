#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define pa1 1000 //Simplifies allocation of space for players in player-array since size must be defined at declearation
//- before input from user is possible. It is asumed that a maximum number of players in the array will not exceed 1000
#define WINP 4   //Points to win
#define STOK 4  // Starting value of token

int pa;
int pid; // Variable used to easely identify all the processes
pid_t p[pa1]; // Array of process ids
int i;

void pri() // Kills all child processes
{
	for (i=0;i<pa;i++) kill(p[i],SIGTERM);
	sleep(1);
	exit(0);
}

void pri2() // is triggered by pri to signal child termination
{
	printf("\nPlayer %d eliminerad\n",pid);
	exit(0);
}

int main()
{
	printf("Antal: ");
	scanf("%d",&pa);
	printf("\n");

	if (pa==1)
	{
		printf("Endast 1 spelare => Player 0 vinner\n"); // error code for 1 player
		exit(0);
	}
	int token;
	int k=1;
	int j;
	int points = 0;

  pid = -1; // -1 is parrent, is overwritten in child processes
  int pipes[pa][2]; // declaring an array of pipes the size of the player amount (pa)

  for(i=0; i<pa; i++)
	{
    if(pipe(pipes[i])<0)
		{
      printf("Pipe failiure");
			exit(EXIT_FAILURE);
		}
	}
  p[0] = fork(); // first fork is created in order for our for loop to create the remaining children
	if (p[0] == -1)
	{
		fprintf(stderr, "Fork failure");
		exit(EXIT_FAILURE);
	}
  if(p[0] != 0)
  {
    for(i=0; i<(pa-1); i++)
    {
      if(p[i] != 0)
      {
        p[i+1] = fork(); // if is used to ensure we are in parrent process then fork is used pa -1 amount of times

				if (p[i+1] == -1)
				{
					fprintf(stderr, "Fork failure");
					exit(EXIT_FAILURE);
				}
				if (p[i+1]==0)
				{
			  	pid=i+1; // we create an easylely useable ID for the players.
			  	printf("Player %d startat",pid);
		  	}
      }
    }
  }
  else
	{
		pid=0; // player id for first player is set
		printf("player 0 startat");
	}
	if (pid==-1)
	{
		(void) signal(SIGTERM,pri); // Signalhandler is created to enable parrent to kill children
		int t=STOK; // value of token is set to a decided value
		write(pipes[0][1],&t,sizeof(int)); // sends value of token to first player
	}
	while (k==1)
	{
		if (pid==-1)
		{}
    else if (pid==0)
		{
			(void) signal(SIGTERM,pri2);
			read(pipes[0][0],&token,sizeof(int));

			if (token==0)
			{
				points++; // a player is given a point in the case that the token value hits 0
				printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token,STOK,points);
				token=STOK; // token value is reset

				if (points==WINP)
				{
					printf("\nPlayer %d vinner\n",pid);
					kill(getppid(),SIGTERM); // signal is sent to parrent when win conditions are met
					sleep(1); // sleeps in order to give parrent time to terminate child processes
				}
			}
			else
			{
				token--;
				printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token+1,token,points);
			}
			write(pipes[1][1],&token,sizeof(int)); // first player sends token to next child
		}
		else if (pid<pa-1)
		{
			(void) signal(SIGTERM,pri2);
			read(pipes[pid][0],&token,sizeof(int)); // a player that is not first or last recevies token to next player

			if (token==0)
			{
				points++;
				printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token,STOK,points);
				token=STOK;

				if (points==WINP)
				{
					printf("\nPlayer %d vinner\n",pid);
					kill(getppid(),SIGTERM);
					sleep(1);
				}
			}
			else
			{
				token--;
				printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token+1,token,points);
			}
			write(pipes[pid+1][1],&token,sizeof(int)); // a player that is not first or last writes token to next player
		}
		else
		{
			(void) signal(SIGTERM,pri2);
			read(pipes[pid][0],&token,sizeof(int)); // last player recieves token

			if (token==0)
			{
				points++;
				printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token,STOK,points);
				token=STOK;

				if (points==WINP)
				{
					printf("\nPlayer %d vinner\n",pid);
					kill(getppid(),SIGTERM);
					sleep(1);
				}
			}
			else
			{
				token--;
				printf("\n Player %d, Received: %d, Sent: %d ,Points: %d  \n",pid,token+1,token,points);
			}
			write(pipes[0][1],&token,sizeof(int)); // last child sends token to first child
		}
	}
	for (j=0;j<pa;j++)  wait(NULL); // keeps rrent alive

  return 0;
}
