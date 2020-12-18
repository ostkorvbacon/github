#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define NT 100
#define BUFF 4


int i,n,bsize,tint,buffer[BUFF];
int inde=1;
sem_t prodcount; // varor producerade
sem_t remaining; // kvarvarand utrymme i buffer

void *p(void *a )
{
	printf("Hej jag är konsument id: %d \n",(int)pthread_self());

	while (1)
	{
		sem_wait(&prodcount);
		for (i=0;i<bsize;i++) printf(" %d \n",buffer[i]);
		printf("Data: %d konsument id: %d\n",buffer[inde],(int)pthread_self());
 		inde--;
		sem_post(&remaining);

	}
}


void *p2(void *a)
{
	printf("\nHej jag är producent id: %d \n",(int)pthread_self());

	while (1)
	{
			sem_wait(&remaining);
			buffer[inde]=inde;
			inde++;
			sem_post(&prodcount);
			sleep(tint);

	}
}

int main()
{
	pthread_t tid[NT];
	printf("N: ");
	scanf("%d",&n);

	printf("\nBufffer: ");
	scanf("%d",&bsize);

	printf("\nInterval: ");
	scanf("%d",&tint);

	sem_init(&prodcount, 0, 0);
	sem_init(&remaining, 0, BUFF);

	for (i=0;i<bsize+2;i++) printf(" %d \n",buffer[i]);

	pthread_create(&tid[0],NULL,*p2,0);

	for (i=1;i<n+1;i++) pthread_create(&tid[i],NULL,*p,0);

	for (i=0;i<n+1;i++) pthread_join(tid[i],NULL);

	return 0;
}
