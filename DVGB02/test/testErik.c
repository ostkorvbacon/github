#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 1895
#define SIZE 20

int main(int argc, char const *argv[])
{
    int i, server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *hello = "200 OK";
    char *hello2 = "404 NOT FOUND";
    char *httpresp =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: image/jpg\r\n"
    "Content-Length: 12229\r\n\r\n";
    char *picbuff;
    picbuff = (char *) malloc(12229);
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

        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        char temp1[SIZE],temp2[SIZE];

        memset(temp2,'\0',SIZE);
        sscanf(buffer,"%s /%s ",temp1,temp2);
        printf("temp2= %s\n",temp2);
        if (strcmp(temp2,"index.html")==0){
          write(new_socket , hello , strlen(hello));
          printf("Message sent\n");

        }
        else if (strcmp(temp2,"a.jpg")==0){

          FILE *ft=fopen("a.jpg","rb");
          //FILE *s=fdopen(new_socket,"wb");
          int ch;


          fread (picbuff, sizeof(char), 12229+1, ft);
          write(new_socket ,httpresp, strlen(httpresp));
          write(new_socket, picbuff, strlen(picbuff));
        }
        else{
          write(new_socket ,hello2, strlen(hello2));

          printf("404 Not Found\n");


        }

        close(new_socket);
    }
    free(picbuff);
    free(httpresp);
    return 0;
}
