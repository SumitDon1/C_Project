// socket is a IP connection
// we are doing TCP connection on port 80(http)
#include <stdio.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define IP "74.6.231.20"        // yahoo.com
#define PORT 80                 // http

int main(){
    int s;
    struct sockaddr_in sock;

    char buff[512];
    char *data;

    data = "HEAD / HTTP/1.0\r\n\r\n";

    s = socket(AF_INET,SOCK_STREAM,0);
    if(s<0){
        printf("socket() error\n");
        return -1;
    }

    // IP address of the target
    sock.sin_addr.s_addr = inet_addr(IP);
    sock.sin_port = htons(PORT);
    sock.sin_family = AF_INET;

    if(connect(s,(struct sockaddr *)&sock,sizeof(struct sockaddr_in))!=0){
        printf("connect() error\n");

        close(s);
        return -1;
    }
    write(s,data,strlen(data));
    memset(buff,0,512);
    read(s,buff,511);
    close(s);
    printf("\n%s\n", buff);


}
