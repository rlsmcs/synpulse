#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netdb.h>
#include <unistd.h>


#define PORT "3490"

#define BACKLOG 10


int main(void){
    int sockfd;
    int rv;
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; 
    rv = getaddrinfo(NULL,PORT,&hints,&servinfo);

    if(rv!=0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;  // we dont use perror() because of getaddrinfo()'s behaviour. it doesnt use errno and returns its own error codes so we use another linux helper
        // called gai_strerror()
    }

    for(p=servinfo; p!=NULL; p=p->ai_next){
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
            perror("socket");
            continue;
        }
        if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            close(sockfd);
            perror("server:bind");
            continue;
        }
        break;

    } 
    freeaddrinfo(servinfo);
    if(p==NULL){
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
    }
    if(listen(sockfd, BACKLOG) == -1){
    perror("listen");
    exit(1);
    }
    printf("synpulse server is listenin on port %s. \n", PORT);

    struct sockaddr_storage their_addr;   // cuz we don know if its ipv4 or ipv6 jus let the kernel fill it 
    socklen_t addr_size; // we use a pointer to this cuz we may change the value
    int new_fd;
    while(1)
    {
    addr_size = sizeof(their_addr);
    new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &addr_size); // typecast to ipv4 for now
    if(new_fd == -1){
    perror("accept");
    continue;
    }
    printf("Client connected!\n");
    close(new_fd);
    }
    
    
}
