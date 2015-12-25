#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#define size 1024
#define BUFLEN 1024
#define NPACK 10
#define PORT 8888
//#define SRV_IP "192.168.0.33"
//#define OWN_IP "192.168.0.96"

typedef struct {
    int sockfd;
    struct sockaddr_in client;
    int clilen;
} btClient;


int cl=0;
void showList(btClient *client){
    char str[size];
    int counter,i;
    int n;
    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;

    sendto(sock, "1", strlen("1"), 0,(struct sockaddr *)&si_other,slen);
    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    counter = atoi(str);
    memset(str, 0, sizeof(str));

    sendto(sock, "1", strlen("1"), 0,(struct sockaddr *)&si_other,slen);

    for (i = 0; i < counter -1; i++){
        n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
        str[n] = 0;
        printf(str);
        memset(str, 0, sizeof(str));
    }
}


void increase(btClient *client){
    char str[size];
    int n;

    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));
}


void decrease(btClient *client){
    char str[size];
    int n;

    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;
    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));


    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));
}


void create(btClient *client){
    char str[size];
    int n;

    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;
    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));


    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));



    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));
}


void rem(btClient *client){
    char str[size];
    int n;

    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");
    sendto(sock, str, strlen(str), 0,(struct sockaddr *)&si_other,slen);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));
}


void admDial(btClient *client){
    char str[size];
    int com = 0;
    int n;

    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;
    sendto(sock, "1", strlen("1"), 0,(struct sockaddr *)&si_other,slen);


    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");

    if (!strcmp(str, "increase\r\n")){
        com = 1;
        sendto(sock, "increase\r\n", strlen("increase\r\n"), 0,(struct sockaddr *)&si_other,slen);
        increase(client);
    }
    if (!strcmp(str, "decrease\r\n")){
        com = 2;
        sendto(sock, "decrease\r\n", strlen("decrease\r\n"), 0,(struct sockaddr *)&si_other,slen);
        decrease(client);
    }
    if (!strcmp(str, "create\r\n")){
        com = 3;
        sendto(sock, "create\r\n", strlen("create\r\n"), 0,(struct sockaddr *)&si_other,slen);
        create(client);
    }

    if (!strcmp(str, "remove\r\n")){
        com = 4;
        sendto(sock, "remove\r\n", strlen("remove\r\n"), 0,(struct sockaddr *)&si_other,slen);
        rem(client);
    }
    if (!strcmp(str, "showlist\r\n")){
        com = 5;
        sendto(sock, "showlist\r\n", strlen("showlist\r\n"), 0,(struct sockaddr *)&si_other,slen);
        showList(client);
    }
    if (!strcmp(str, "exit\r\n")){
        com = 6;
        sendto(sock, "exit\r\n", strlen("exit\r\n"), 0,(struct sockaddr *)&si_other,slen);
        cl = 1;
    }
    if (com == 0){

        sendto(sock, "incorrect\r\n", strlen("incorrect\r\n"), 0,(struct sockaddr *)&si_other,slen);

        n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
        str[n] = 0;
        printf(str);
        memset(str, 0, sizeof(str));
    }
    memset(str, 0, sizeof(str));
}



void usrDial(btClient *client){
    char str[size];
    int com = 0;
    int n;
    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;

    sendto(sock, "1", strlen("1"), 0,(struct sockaddr *)&si_other,slen);


    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    printf(str);
    memset(str, 0, sizeof(str));

    scanf("%s", str);
    strcat(str, "\r\n");

    if (!strcmp(str, "showlist\r\n")){
        com = 1;
        sendto(sock, "showlist\r\n", strlen("showlist\r\n"), 0,(struct sockaddr *)&si_other,slen);
        showList(client);
    }
    if (!strcmp(str, "buy\r\n")){
        com = 2;
        sendto(sock, "buy\r\n", strlen("buy\r\n"), 0,(struct sockaddr *)&si_other,slen);
        decrease(client);
    }
    if (!strcmp(str, "exit\r\n")){
        com = 3;
        sendto(sock, "exit\r\n", strlen("exit\r\n"), 0,(struct sockaddr *)&si_other,slen);
        cl = 1;
    }
    if (com == 0){

        sendto(sock, "incorrect\r\n", strlen("incorrect\r\n"), 0,(struct sockaddr *)&si_other,slen);

        n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other,&slen);
        str[n] = 0;
        printf(str);
        memset(str, 0, sizeof(str));
    }
    memset(str, 0, sizeof(str));
}

void handler(void* param){
    char str[BUFLEN];
    char inp[BUFLEN];
    int usr=0,n,i;

    btClient* client = (btClient*)param;
    int sock=client->sockfd;
    struct sockaddr_in si_other=client->client;
    int slen=client->clilen;

    sendto(sock, "1", strlen("1"), 0,(struct sockaddr *) &si_other, slen);
    for (i=0; i<2; i++) {
        n = recvfrom(sock, str, size, 0,(struct sockaddr *) &si_other, &slen);
        str[n] = 0;
        printf(str);
        memset(str, 0, sizeof(str));
    }
    scanf("%s",inp);
    sendto(sock, inp, strlen(inp), 0,(struct sockaddr *) &si_other, slen);
    if (!strcmp(inp, "admin")){
        usr = 1;
    }
    else
        usr = 0;
    while (cl==0){
        switch (usr) {
        case 1:
            memset(inp, 0, sizeof(inp));
            admDial(client);
            break;
        case 0:
            memset(inp, 0, sizeof(inp));
            usrDial(client);
            break;
        }
    }
n = recvfrom(sock, str, size, 0,(struct sockaddr *)&si_other, &slen);
str[n] = 0;
printf(str);
memset(str, 0, sizeof(str));
close(sock);
}


int main(void)
{   struct sockaddr_in si_other;
    int slen=sizeof(si_other);
    int s,n,newport;
    char str[size];
    char SRV_IP[size];
    printf("Enter servers's ip:\n");
    scanf("%s",SRV_IP);
    //struct sockaddr_in si_other;
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    if (inet_aton(SRV_IP, &si_other.sin_addr)==0) {
       fprintf(stderr, "inet_aton() failed\n");
       exit(1);
    }
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
          perror("socket");
    memset(str,0,sizeof(str));

    sendto(s, "1", strlen("1"), 0,(struct sockaddr *) &si_other, slen);

    n = recvfrom(s,str,size,0,(struct sockaddr *)&si_other,&slen);
        str[n] = 0;
        newport = atoi(str);
        printf("port=%i",newport);
        memset(str, 0, sizeof(str));
        struct sockaddr_in new_si_other;
            int ns, new_slen = sizeof(new_si_other);

    ns=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset((char *)&new_si_other, 0, new_slen);
        new_si_other.sin_family = AF_INET;
        new_si_other.sin_port = htons(newport);
        inet_aton(SRV_IP, &new_si_other.sin_addr);

        btClient client;
            client.sockfd = ns;
            client.client = new_si_other;
            client.clilen = sizeof(new_si_other);

        close(s);
            sendto(client.sockfd, "newclient created", strlen("newclient created"), 0,(struct sockaddr *) &client.client, client.clilen);
            handler((void*)&client);
    /*n = recvfrom(s,str,size,0,(struct sockaddr *)&si_other,&slen);
    str[n] = 0;
    newport = atoi(str);
    printf("port=%i",newport);
    memset(str, 0, sizeof(str));


    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(newport);
    inet_aton(SRV_IP, &si_other.sin_addr);
    ns=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sendto(ns, "newclient created", strlen("newclient created"), 0,(struct sockaddr *) &si_other, slen);
    handler(ns);*/
}
