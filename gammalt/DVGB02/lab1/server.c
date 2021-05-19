#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT 12345
#define BUF_SIZE 4096
#define QUEUE_SIZE 10

int main(int argc, char *arhv[])
{
    int s, b, l, fd, sa, bytes, on = 1;
    char buf[BUF_SIZE];
    struct sockaddr_in channel;
    // Adress structure
    memset(&channel, 0, sizeof(channel));
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);
    //Passive open
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s < 0) fatal("socket failed");
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

    b = bind(s, (struct sockaddr*) &channel, sizeof(channel));
    if(b < 0) fatal("bind failed");

    l = listen(s, QUEUE_SIZE);
    if(l < 0) fatal("listen failed");

    //socket set up and bound, wait for conectiopn.
    while(1)
    {
      sa = accept(s, 0, 0);
      if(sa < 0) fatal("accept failed");

      read(sa, buf, BUF_SIZE);

      //get returnfile
      fd = open(buf, O_RDONALY);
      if(fd < 0) fatal("open failed");

      while(1)
      {
        bytes = read(fd, buf, BUF_SIZE);
        if(bytes <= 0) break;
        write(sa, buf, bytes);
      }
      close(fd);
      close(sa);
    }


}
