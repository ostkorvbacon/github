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

int main(int argc, char *arhv[])
{
    int s, b, l, fd, sa, bytes, on = 1;
    int sizechannel;
    char buf[BUF_SIZE];
    struct sockaddr_in channel;
    printf("hajd");
    // Adress structure
    memset(&channel, 0, sizeof(channel));
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);
    //Passive open
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s == -1) printf("error socket");

    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

    b = bind(s, (struct sockaddr*) &channel, sizeof(channel));
    if(b == -1) printf("error bind");
    l = listen(s, QUEUE_SIZE);
    if(l == -1) printf("error listen");

    printf("geh");
    //socket set up and bound, wait for conectiopn.
      sizechannel = sizeof(channel);
      sa = accept(s, (struct sockaddr *)&channel, (socklen_t*)&sizechannel);
      if(sa == -1) printf("error accept");

      read(sa, buf, BUF_SIZE);
      printf("message %s", buf);
      close(sa);
}
