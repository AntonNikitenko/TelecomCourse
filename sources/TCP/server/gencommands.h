#ifndef GENCOMMANDS
#define GENCOMMANDS
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "server.h"
#define size 1024

struct product goods[100];
int seNum,cl;


void showList(int csock){
char temp[size];
int i,n;
printf("\n show list \n");
sleep(1);

strcpy(temp,"\n\nThis is the list of products:\n");
send(csock,temp,strlen("\n\nThis is the list of products:\n"),0);
memset(temp,0,sizeof(temp));
sleep(1);

n = recv(csock, temp, size, 0);
temp[n] = 0;
memset(temp, 0, sizeof(temp));

strcpy(temp,"id	amount	price	name\n");
send(csock,temp,strlen("id     amount     price     name\n"),0);
memset(temp,0,sizeof(temp));
sleep(1);


n = recv(csock, temp, size, 0);
temp[n] = 0;
memset(temp, 0, sizeof(temp));

sprintf(temp,"%i",seNum);
send(csock,temp,strlen(temp),0);
memset(temp,0,sizeof(temp));
sleep(1);

n = recv(csock, temp, size, 0);
temp[n] = 0;
memset(temp, 0, sizeof(temp));

for (i=0;i<seNum-1;i++){
    if(goods[i].id!=0){
        sprintf(temp,"%i       %i       %i       %s",goods[i].id,goods[i].amount,goods[i].price,goods[i].name);
        send(csock,temp,strlen(temp),0);
        memset(temp,0,sizeof(temp));

        n = recv(csock, temp, size, 0);
        temp[n] = 0;
        memset(temp, 0, sizeof(temp));

    }
}
n = recv(csock, temp, size, 0);
temp[n] = 0;
memset(temp, 0, sizeof(temp));
}


void disc(){
closeServ();
cl=1;
//close(csock);
}
#endif // GENCOMMANDS

