#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define PORT 1895
#define SIZE 20
#define TDELTA 2208988800


int main(int argc, char const *argv[])
{
    int i, server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    int fd;





    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
      printf("Socket failed\n" );
      exit(1);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
      printf("Bind failed\n");
      exit(1);
    }
    if (listen(server_fd, 10) < 0)
    {
        printf("Lisen failed\n");
        exit(1);
    }
    while(1)
    {
        i = 0;
        printf("\n Awaiting connection\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            printf("Accept failed\n");
            exit(1);
        }

      time_t sec=time(NULL);
      printf("%s\n",ctime(&sec));
      sec=sec+TDELTA;
      
      printf("%s\n",ctime(&sec));
      write(new_socket,&sec,sizeof(sec));
      close(new_socket);

    printf("%ld",sizeof(sec));


    }

    return 0;
}
