#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>


#define SERVER_PORT 12345
#define BUF_SIZE 4096
#define QUEUE_SIZE 10

int main(int argc, char *arhv[])
{
    printf("he");
    int s, b, l, c, fd, sa, bytes, on = 1;
    char buf[BUF_SIZE];
    char *msg = "hello";
    printf("hejhej");

    struct sockaddr_in channel;
    // Adress structure
    memset(&channel, 0, sizeof(channel));

    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "192.168.85.130", &channel.sin_addr);

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    printf("hejhej");

    c = connect(s, (struct sockaddr*)&channel, sizeof(channel));
    if(c == 0) printf("connection succesfull");
    else printf("error");
    write(s, msg, sizeof(msg));
    return 0;
}
