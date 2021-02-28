#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#define SERVER_PORT 1895
#define TDELTA 2208988800

int main(int argc, char *arhv[])
{
    int s, b, l, c, fd, sa, bytes, on = 1;
     time_t buf;
     time_t tdelta=TDELTA;
    struct sockaddr_in channel;
    // Adress structure
    memset(&channel, 0, sizeof(channel));

    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "10.0.2.15,", &channel.sin_addr);

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    c = connect(s, (struct sockaddr*)&channel, sizeof(channel));
    if(c == -1) printf("error connection");

    read(s,&buf,8);  
    buf=buf-tdelta;

    printf("%s\n",ctime(&buf));

    close(c);

    return 0;
}
