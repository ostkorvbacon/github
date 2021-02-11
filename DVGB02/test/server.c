#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SERVER_PORT 12345
#define BUF_SIZE 4096
#define QUEUE_SIZE 10

int web(int sa, char *buf);

int main(int argc, char *arhv[])
{
    int s, b, l, fd, sa, bytes, on = 1;
    char buf[BUF_SIZE];
    struct sockaddr_in serveraddr;
    int addrlngt = sizeof(serveraddr);
    // Adress structure
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);
    //Passive open
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s == -1) printf("Error socket");

    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

    b = bind(s, (struct sockaddr*) &serveraddr, sizeof(serveraddr));
    if(b == -1) printf("Error bind");
    l = listen(s, QUEUE_SIZE);
    if(l == -1) printf("Error listen");

    //socket set up and bound, wait for conectiopn.
    while(1)
    {
      sa = accept(s, (struct sockaddr *)&serveraddr, (socklen_t*)&addrlngt);
      if(sa == -1) printf("Error accept");
      web(sa, buf);

      close(sa);
    }
}

int web(int sa, char *buf)
{
  read(sa, buf, BUF_SIZE);
  printf("Message from user %s\n", buf);
  write(sa, buf, BUF_SIZE);
  printf("Message sent back to user\n");

  return 0;
}
