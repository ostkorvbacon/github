#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define PA 3
#define WINP 4
#define STOK 4

int pid;


void pri()
{
	printf("\nPlayer %d eliminerad\n",pid);
	exit(0);
}

int main()
{

	sem_t semph[PA],sem2;
	sem_init(&sem2,1,20);

  (void) signal(SIGTERM,pri);
  pid_t p[PA];
  int token;
  int k=1;

  int j;
  int points = 0;
  for (j=0;j<PA;j++)
  {
    p[j] = 0;
  }
  pid = -1; // -1 är parent
  int pipes[PA][2];
  int i;
  for(i=0; i<PA; i++)
  {
    if(pipe(pipes[i])<0)
    {
      printf("error");
    }
	  sem_init(&semph[i],1,20);
  }
  p[0] = fork();

  if(p[0] != 0)
  {
    for(i=0; i<(PA-1); i++)
    {
      if(p[i] != 0)
      {
        p[i+1] = fork();

        if (p[i+1]==0)
        {
    		  pid=i+1;
    		  printf("Player %d startat",pid);
	      }
      }
    }
  }
  else
	{
		pid=0;
		printf("player 0 startat");
	}
	if (pid==-1)
  {
		int t=STOK;
		write(pipes[0][1],&t,sizeof(int));
		sem_post(&semph[0]);
	}
	while (k==1)
  {
		if (pid==-1)
    {
			sem_wait(&sem2);
			k=0;
			//for (i=0;i<PA;i++) kill(p[i],SIGTERM);
		}
    else if (pid==0)
    {
  		sem_wait(&semph[0]);
  		read(pipes[0][0],&token,sizeof(int));

      if (token==0)
      {
  			points++;
  			printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token,STOK,points);
  			token=STOK;

  			if (points==WINP)
        {
  				printf("\nPlayer %d vinner\n",pid);
  				sem_post(&sem2);
  				k=0;
  				exit(0);
  			}
      }
    	else
      {
        token--;
        printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token+1,token,points);
  	  }
      write(pipes[1][1],&token,sizeof(int));
  		sem_post(&semph[1]);
    }
    else if (pid<PA-1)
    {
      sem_wait(&semph[pid]);
		  read(pipes[pid][0],&token,sizeof(int));
			if (token==0)
      {
  			points++;
  			printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token,STOK,points);
  			token=STOK;

  			if (points==WINP)
        {
  				printf("\nPlayer %d vinner\n",pid);
  				sem_post(&sem2);
  				k=0;
  				exit(0);
  			}
      }
  		else
  		{
  		  token--;
  		  printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token+1,token,points);
  	  }
  	  write(pipes[pid+1][1],&token,sizeof(int));
  		sem_post(&semph[pid+1]);
    }
  	else
    {
  		sem_wait(&semph[pid]);
  		read(pipes[pid][0],&token,sizeof(int));

  		if (token==0)
      {
  			points++;
  			printf("\n Player %d, Received: %d, Sent: %d ,Points: %d \n",pid,token,STOK,points);

  			token=STOK;

  			if (points==WINP)
        {
  				printf("\nPlayer %d vinner\n",pid);
  				sem_post(&sem2);
  				k=0;
  				exit(0);
  			}
  		}
  		else
      {
  		    token--;
  		    printf("\n Player %d, Received: %d, Sent: %d ,Points: %d  \n",pid,token+1,token,points);
  	  }
  		write(pipes[0][1],&token,sizeof(int));

  		sem_post(&semph[0]);
    }
  }
  for (j=0;j<PA;j++)  wait(NULL);
  //printf("\n id: %d  ppid: %d  pid: %d\n",pid,getppid(),getpid());

  return 0;
}
