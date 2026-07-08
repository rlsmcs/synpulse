#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#define PORT "3490"
int main(void){
    int sockfd;
    int rv;
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    rv = getaddrinfo("127.0.0.1", PORT, &hints, &servinfo);
    if(rv!=0){
        fprintf(stderr, "getaddrinfo:%s \n",gai_strerror(rv));
        return 1;
    }

    for(p=servinfo; p!=NULL; p=p->ai_next){
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
            perror("client:socket");
            continue;
        }

        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            perror("client:connect");
            close(sockfd);
            continue;
        }
        
        break;
    }
    if(p==NULL){
        fprintf(stderr, "client:failed to connect\n");
        return 2;
    }
    freeaddrinfo(servinfo);
    printf("Connected to the server!\n");

    char buffer[256];
    char msg[256];
    while(1){
    
        printf("Client:");
        fgets(msg, sizeof(msg),stdin);
        send(sockfd,msg,strlen(msg)+1,0);
        recv(sockfd, buffer,sizeof(buffer),0);
        printf("Server: %s", buffer);
    }
}
