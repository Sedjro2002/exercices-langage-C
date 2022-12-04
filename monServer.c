#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

int init();

int main(int argc, char const *argv[]) {
    if(argc >= 1){
        printf("\n Server execution\n\n");
        int ret = 1, sc, csc, fd, buf_t;
        const char* filename = argv[1];
        struct sockaddr client_addr;
        int clen;
        sc = init();
        if((csc = accept(sc, &client_addr, &clen)) < 0){
            fprintf(stderr, "there is an erros with the accept %d\n", errno);
            return -1;
        }
        fprintf(stdout, "trying to connect\n");
        fd = open(filename,O_RDONLY ,0644);
        while(ret == 1){
            char car[1];
            ret = read(fd,car,1);
            write(csc,car,1);
        }
        fprintf(stdout, "\n File send\n");
        close(fd);

        for(;;){}
    }
    else{
        fprintf(stderr, "\n Wrong arguments, try again \n\n");
        exit(-1);
    }
    return 0;
}

int init(){
    int sc = socket(AF_INET, SOCK_STREAM, 0), ret;
    struct sockaddr_in serv_addr;
    if(sc < 0){
        fprintf(stderr, "Socket error\n");
        return sc;
    }
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_addr.sin_port = htons(8080); 

    ret=bind(sc, (struct sockaddr*)&serv_addr,sizeof(serv_addr)); 
    if(ret<0){
        printf("bind error\n");
        close(sc);
        return ret;
    }
    if(listen(sc, 10) == -1) 
    {
        printf("listen failure\n");
        return -1;
    }

    return sc;
}
