#ifndef USRCOMMANDS
#define USRCOMMANDS
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define size 1024

struct product goods[100];
int seNum,cl;


void buy(int csock){
char temp[size];
char str[size];
int n,am,i,flag=0;
strcpy(str,"\n\nEnter name of selected product:\n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));

n=recv(csock,temp,size,0);
temp[n]=0;

strcpy(str,"How many selected products you want to buy?\n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));

n=recv(csock,str,size,0);
str[n]=0;
am=atoi(str);
memset(str,0,sizeof(str));


sprintf(str,"\n\n%s %s\n","Processing your request...",temp);
write(csock,str,strlen(str));
memset(str,0,sizeof(str));
/*sprintf(str,"%s %i\n","Amount: ",am);
write(csock,str,strlen(str));
memset(str,0,sizeof(str));*/

n=recv(csock,str,size,0);
str[n]=0;
memset(str,0,sizeof(str));

for (i=0;i<seNum-1;i++){
    if (!strncmp(goods[i].name,temp,strlen(temp)-2)){
        if (am>goods[i].amount)
        {
            flag=0;
        }else
        {
            goods[i].amount=goods[i].amount-am;
            flag++;
        }
    }
}
if(flag==1){
    strcpy(str,"Purchase is made. Thank you for your order.\n");
    write(csock,str,strlen(str));
    memset(str,0,sizeof(str));
    }
else {
    strcpy(str,"Purchase error. Please try again.\n");
    write(csock,str,strlen(str));
    memset(str,0,sizeof(str));
    }
memset(temp,0,sizeof(temp));

n=recv(csock,str,size,0);
str[n]=0;
memset(str,0,sizeof(str));



n=recv(csock,str,size,0);
str[n]=0;
memset(str,0,sizeof(str));

}

#endif // USRCOMMANDS

