#ifndef DIALOGS
#define DIALOGS
#include "product.h"
#include "admcommands.h"
#include "usrcommands.h"
#include "gencommands.h"
#include "server.h"
#define size 1024

struct product goods[100];
int seNum,cl;


void usrDial(int csock){
int n,com=0;
char temp[size];
strcpy(temp,"\nAvailable commands : buy,showlist,exit");
send(csock,temp,strlen(temp),0);
memset(temp,0,sizeof(temp));

n = recv(csock, temp, size, 0);
temp[n] = 0;
memset(temp, 0, sizeof(temp));

strcpy(temp,"\nEnter command:\n");
send(csock,temp,strlen(temp),0);
memset(temp,0,sizeof(temp));

n=recv(csock,temp,size,0);
temp[n]=0;
if (!strcmp(temp, "buy\r\n"))
        com=1;
if (!strcmp(temp, "showlist\r\n"))
        com=2;
if (!strcmp(temp, "exit\r\n"))
        com=3;
memset(temp,0,sizeof(temp));
switch (com ) {
case 1:
  buy(csock);
  break;
case 2:
  showList(csock);
  break;
case 3:
   disc();
   break;
default:

    strcpy(temp,"Incorrect entry.\n");
    send(csock,temp,strlen(temp),0);
    memset(temp,0,sizeof(temp));

    n = recv(csock, temp, size, 0);
    temp[n] = 0;
    memset(temp, 0, sizeof(temp));
  break;
}
}






void admDial(int csock){
int n,com=0;
char temp[size];
printf("\n AdmDial \n");

strcpy(temp,"\nAvailable commands : increase, decrease,create,remove,showlist,exit");
send(csock,temp,strlen(temp),0);
memset(temp,0,sizeof(temp));

n = recv(csock, temp, size, 0);
temp[n] = 0;
memset(temp, 0, sizeof(temp));

strcpy(temp,"\nEnter command:\n");
send(csock,temp,strlen(temp),0);
memset(temp,0,sizeof(temp));

n=recv(csock,temp,size,0);
temp[n]=0;
if (!strcmp(temp, "increase\r\n"))
        com=1;
if (!strcmp(temp, "decrease\r\n"))
        com=2;
if (!strcmp(temp, "create\r\n"))
        com=3;
if (!strcmp(temp, "remove\r\n"))
        com=4;
if (!strcmp(temp, "showlist\r\n"))
        com=5;
if (!strcmp(temp, "exit\r\n"))
        com=6;
printf("priniato: %s",temp);
memset(temp,0,sizeof(temp));
switch (com) {
case 1:
  add(csock);
  break;
case 2:
  decr(csock);
  break;
case 3:
  create(csock);
  break;
case 4:
  rem(csock);
  break;
case 5:
  showList(csock);
  break;
case 6:
   disc();
   break;
default:

    strcpy(temp,"Incorrect entry.\n");
    send(csock,temp,strlen(temp),0);
    memset(temp,0,sizeof(temp));


    n = recv(csock, temp, size, 0);
    temp[n] = 0;
    memset(temp, 0, sizeof(temp));
  break;
}
}

#endif // DIALOGS

