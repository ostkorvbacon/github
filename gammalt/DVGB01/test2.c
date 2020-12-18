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
    sem_t *sem_txt = sem_open(SEMNAME, O_CREAT, 0700, 0);
    printf("\n\n");
    printf("rc = %d\n", rc);
    sem_getvalue(sem_txt, &value);
    printf("sem_txt = %d\n",value);
    sem_wait(sem_txt);
    sem_getvalue(sem_txt, &value);
    printf("sem_txt = %d\n",value);
    printf("World\n");

    return EXIT_SUCCESS;
  }
  else if(rc > 0)
  {
    sem_unlink(SEMNAME);
    sem_t *sem_txt = sem_open(SEMNAME, O_CREAT, 0700, 0);
    printf("rc = %d\n", rc);
    printf("Hello ");
    sem_getvalue(sem_txt, &value);
    printf("\nsem_txt = %d\n",value);
    sem_post(sem_txt);
    sem_getvalue(sem_txt, &value);
    printf("sem_txt = %d\n",value);

    return EXIT_SUCCESS;
  }
  else
  {
    printf("fel\n");
    return EXIT_FAILURE;
  }
}
