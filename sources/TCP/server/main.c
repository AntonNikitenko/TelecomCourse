#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <pthread.h>
#include "product.h"
#include "dialogs.h"

#define size 1024
extern struct product goods[100];
extern int seNum=0;
extern int cl=0;
extern int sr=0;

void *handler(int *arg){
    int usr=0,n;
    int csock = * (int *) arg;
    char str[size];

    strcpy(str,"\n\nWelcome to our e-shop!\n");
    send(csock,str,strlen("\n\nWelcome to our e-shop!\n"),0);
    memset(str,0,sizeof(str));

    n = recv(csock, str, size, 0);
    str[n] = 0;
    memset(str, 0, sizeof(str));

    strcpy(str,"Enter your name:\n");
    send(csock,str,strlen("Enter your name:\n"),0);
    memset(str,0,sizeof(str));

    n=recv(csock,str,size,0);
    str[n]=0;

    if (!strcmp(str,"admin\r\n")){
        usr=1;
    }
    else
        usr=2;
    while(1){
        switch (usr ) {
        case 1:
          admDial(csock);
          break;
        case 2:
          usrDial(csock);
          break;
        }
        if (cl!=0){
            cl=0;
            break;
        }
    }
    memset(str,0,sizeof(str));
    strcpy(str,"\nConnection closed.\n");
    write(csock,str,strlen("\nConnection closed.\n"));
    memset(str,0,sizeof(str));
    close(csock);
}



int main()
{
    int lsock,csock,*new_sock;
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t addr_len;
    servInit();


    lsock=socket(AF_INET,SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(1234);
    bind(lsock,(struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(lsock,1024);
    addr_len=sizeof(cli_addr);


     while( csock=accept(lsock,(struct sockaddr *)&cli_addr,&addr_len) )
    {

        pthread_t thr;
        new_sock=malloc(1);
        *new_sock = csock;
        if( pthread_create( &thr,NULL,handler,(void*)new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
    }
}

