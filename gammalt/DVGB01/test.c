#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define SEMNAME "semname"

int main()
{
  int value;
  pid_t rc;
  rc = fork();
  if(rc == 0)
  {
    sem_unlink(SEMNAME);
    sem_t *sem_txt = sem_open(SEMNAME, O_CREAT, 0600, 0);
    sem_wait(sem_txt);
    printf("World\n");

    return EXIT_SUCCESS;
  }
  else if(rc > 0)
  {
    sem_unlink(SEMNAME);
    sem_t *sem_txt = sem_open(SEMNAME, O_CREAT, 0600, 0);
    printf("Hello ");
    sem_post(sem_txt);

    return EXIT_SUCCESS;
  }
  else
  {
    printf("fel\n");
    return EXIT_FAILURE;
  }
}
