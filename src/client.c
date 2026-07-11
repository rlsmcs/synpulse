#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

void *sender(void *arg){
    int sockfd = *(int *)arg;
    char msg[256];
    while(1){
        printf("Client:");
        fgets(msg,sizeof(msg),stdin);
        send(sockfd,msg,strlen(msg)+1,0);
    }
    return NULL;
}

void *receiver(void *arg){
    int sockfd = *(int *)arg;
    char buffer[256];
    while(1){
        int bytes = recv(sockfd,buffer,sizeof(buffer),0);
        if(bytes==0){
            printf("Server disconnected.\n");
            break;
        }
        if(bytes==-1){
            perror("recv");
            break;
        }
        printf("Server: %s", buffer);
    }
    return NULL;
}

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

    pthread_t sender_thread;
    pthread_t receiver_thread;
    pthread_create(&sender_thread,NULL,sender,&sockfd);
    pthread_create(&receiver_thread,NULL,receiver,&sockfd);
    pthread_join(sender_thread, NULL);
    pthread_join(receiver_thread, NULL);

    close(sockfd);
    return 0;
}
