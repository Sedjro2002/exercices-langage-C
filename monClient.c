#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

int init(const char* fname);

int main(int argc, char const *argv[]) {
    if(argc >= 1){
        printf("\n Cient execution\n\n");
        int ret, sc, csc, fd, buf_t=1;
        const char* filename = argv[1];
        sc = init(filename);    
    }
    else{
        fprintf(stderr,"\n Wrong arguments, try again \n\n");
        exit(-1);
    }
    return 0;
}

int init(const char* fname){
    struct sockaddr_in serv_addr;
    int sc,fd,ret = 1;
    /* Creation du socket*/
    if((sc = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printf("\n Socket error \n");
        return sc;
    }

    /* Initialisation du strucutre du socket */
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_port = htons(4445); // port
    serv_addr.sin_port = htons(8080);
    //serv_addr.sin_addr.s_addr = inet_addr("196.192.16.70");
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    if(connect(sc, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("\n Error: Connection Failed (%d) \n", errno);
        return -1;
    }
    fprintf(stdout, "Connected\n");
    //char buffer[buf_t];
    fd = open(fname,O_CREAT | O_WRONLY ,0644);

    while(ret == 1){
        char car[1];
        ret = read(sc,car,1);
        write(fd,car,1);
    }

    close(fd);
    for(;;){}
    return sc;
}
