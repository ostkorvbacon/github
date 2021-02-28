#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 1895
#define SIZE 20

int main(int argc, char const *argv[])
{
    int i, server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    struct stat filestat;
    FILE *fp;
    int fd;
    char header_buff [999999];
    char file_buff [99999];
    char filesize[99999];

    char *hello = "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 42 \r\n\r\n";

    char *hello2 =
    "HTTP/1.1 404 Not Found\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 66 \r\n\r\n";



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
          write(new_socket ,hello, strlen(hello2));
          write(new_socket ,"<html><body><p>A webpage</p></body></html>", 39);

        }
        else if (strcmp(temp2,"a.jpg")==0){

          if ( ((fd = open ("a.jpg", O_RDONLY)) < -1) || (fstat(fd, &filestat) < 0) ) {
              printf ("Error in measuring the size of the file");
      }


          sprintf (filesize, "%zd", filestat.st_size);
          fp = fopen ("a.jpg", "rb");

          strcpy (header_buff, "HTTP/1.1 200 OK\r\nContent-Length: ");
          strcat (header_buff, filesize);
          strcat (header_buff, "\r\n");
          strcat (header_buff, "Content-Type: image/jpg");
          strcat (header_buff, "Connection: keep-alive\r\n\r\n");
          write (new_socket, header_buff, strlen(header_buff));

          fread (file_buff, sizeof(char), filestat.st_size + 1, fp);
          fclose(fp);
          write (new_socket, file_buff, filestat.st_size);

          close (new_socket);


        }

        else if (strcmp(temp2,"test.png")==0){

          if ( ((fd = open ("test.png", O_RDONLY)) < -1) || (fstat(fd, &filestat) < 0) ) {
              printf ("Error in measuring the size of the file");
      }


          sprintf (filesize, "%zd", filestat.st_size);
          fp = fopen ("test.png", "rb");

          strcpy (header_buff, "HTTP/1.1 200 OK\r\nContent-Length: ");
          strcat (header_buff, filesize);
          strcat (header_buff, "\r\n");
          strcat (header_buff, "Content-Type: image/png");
          strcat (header_buff, "Connection: keep-alive\r\n\r\n");

          write (new_socket, header_buff, strlen(header_buff));

          fread (file_buff, sizeof(char), filestat.st_size + 1, fp);
          fclose(fp);
          write (new_socket, file_buff, filestat.st_size);

          close (new_socket);


        }
        else{

          write(new_socket ,hello2, strlen(hello2));
          write(new_socket ,"<html><body><p>404 error requested URL not found</p></body></html>", 66);

        }

        close(new_socket);
    }

    return 0;
}
