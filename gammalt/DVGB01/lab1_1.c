#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PA 4
#define WINP 10
#define STARTTOKEN 4


int main()
{
  pid_t p[PA];
  int playerid[PA];
  int j;
  int points = 0;
  for (j=0;j<PA;j++)
  {
    p[j] = 0;
    playerid[j] = 0;
  }
  int pipes[PA][2];
  int i;
  for(i=0; i<PA; i++)
    if(pipe(pipes[i])<0)
      printf("error");
  p[0] = fork();

  if(p[0] != 0)
  {
    for(i=0; i<(PA-1); i++)
    {
        if(p[i] != 0)
        {
          p[i+1] = fork();
            if(p[i+1] == 0)
              playerid[i+1] = 1;
        }
    }
  }
  else
    playerid[0]=1;
printf("a\n");
for (j=0;j<PA;j++)
  wait(NULL);
  if(p[PA] =! 0)
    {
printf("b\n");
      int token = 4;
      //parrent
      close(pipes[0][0]);
      write(pipes[0][1], &token, sizeof(int));
      exit(EXIT_SUCCESS);
    }
printf("c\n");

  for(i=0; i<PA; i++)
    if(playerid[0] == 1)
      {
        int token;
        // player i
        close(pipes[0][1]);
        read(pipes[0][0], &token, sizeof(int));
        printf("%d", token);
        exit(EXIT_SUCCESS);

        /*if (token==0)
          points++;
        if (points==WINP)
          {
            //Great succes!
          }
        exit(EXIT_SUCCESS);*/
      }
  printf("%d\n", getppid());
  for(i=0; i<PA; i++)
    printf("%d\n", playerid[i]);
  return 0;
}
