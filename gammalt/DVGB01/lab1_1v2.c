#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  pid_t p1;
  int pipes[2];
  int i;

  if (pipe(pipes) == 0)
  {
    p1 = fork();
    if(p1 == -1)
    {
      exit(EXIT_FAILURE);
    }
    else if(p1 == 0)
    {
      //Child
      close(pipes[0]);
      int x;
      printf("enter a number\n");
      scanf("%d", &x);
      write(pipes[1], &x, sizeof(int));
      close(pipes[1]);
    }
    else
    {
      // Parent
      int y;
      close(pipes[1]);
      read(pipes[0], &y, sizeof(int));
      close(pipes[0]);
      printf("%d\n", y);
    }
  }
  else
  printf("failiure\n");

  exit(EXIT_SUCCESS);
}
