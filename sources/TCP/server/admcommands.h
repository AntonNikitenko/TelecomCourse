#ifndef ADMCOMMANDS
#define ADMCOMMANDS
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define size 1024

struct product goods[100];
int seNum,cl,sr;


void create(int csock){
char temp[size];
char temp1[size];
char str[size];
int n,am,pr,i=0,j=0;
printf("\n create \n");

strcpy(str,"\nEnter name of product:\n");
write(csock,str,strlen("\nEnter name of product:\n"));
memset(str,0,sizeof(str));


n=recv(csock,temp,size,0);
temp[n]=0;


  strncpy(temp1,temp,strlen(temp)-2);
  memset(temp,0,sizeof(temp));
  strcat(temp1,"\n");
  strcpy(goods[seNum-1].name,temp1);
  memset(temp1,0,sizeof(temp1));

strcpy(str,"Enter the product price: \n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));


n=recv(csock,str,1024,0);
str[n]=0;
pr=atoi(str);
memset(str,0,sizeof(str));
goods[seNum-1].price=pr;

strcpy(str,"How many of created products you want to add? \n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));


n=recv(csock,str,1024,0);
str[n]=0;
am=atoi(str);
memset(str,0,sizeof(str));
goods[seNum-1].amount=am;
goods[seNum-1].id=1;

for (j=0;j<seNum-1;j++)
for (i=0;i<seNum-1;i++)
{
   if (goods[seNum-1].id == goods[i].id){
        goods[seNum-1].id++;
   }
}
seNum++;

n=recv(csock,str,size,0);
str[n]=0;
memset(str,0,sizeof(str));
}




void rem(int csock){
char temp[size];
char str[size];
int n,i,flag=0,r_num=0;
printf("\n remove \n");
strcpy(str,"\n\n\nEnter name of product you want to remove:\n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));

n=recv(csock,temp,size,0);
temp[n]=0;


for (i=0;i<seNum-1;i++){
    if (!strncmp(goods[i].name,temp,strlen(temp)-2)){
        r_num=i;
        flag++;
    }
}

if(flag>0){
    for (i=r_num;i<seNum-1;i++){
        goods[i].amount=goods[i+1].amount;
        goods[i].id=goods[i+1].id;
        goods[i].price=goods[i+1].price;
        strcpy(goods[i].name,goods[i+1].name);

    }
    bzero(&goods[seNum-1],sizeof(struct product));
    seNum--;

    strcpy(str,"Succesfully removed.\n");
    write(csock,str,strlen(str));
    memset(str,0,sizeof(str));
}
else {
    strcpy(str,"No such product. Try again.\n");
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





void add(int csock){
char temp[size];
char str[size];
int n,am,i,flag=0;

strcpy(str,"\n\nEnter name of product:\n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));\


n=recv(csock,temp,size,0);
temp[n]=0;


strcpy(str,"How many selected products you want to add?\n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));\


n=recv(csock,str,size,0);
str[n]=0;
am=atoi(str);
memset(str,0,sizeof(str));
printf("am=%i",am);


for (i=0;i<seNum-1;i++){
    if (!strncmp(goods[i].name,temp,strlen(temp)-2)){
        goods[i].amount=goods[i].amount+am;
        flag++;
    }
}
if(flag==1){
    strcpy(str,"Changes doned\n");
    write(csock,str,strlen(str));
    memset(str,0,sizeof(str));
    }
else {
    strcpy(str,"No such product. Try again.\n");
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



void decr(int csock){
char temp[size];
char str[size];
int n,am,i,flag=0;

printf("\n decrease \n");

strcpy(str,"\n\nEnter name of selected product:\n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));

n=recv(csock,temp,1024,0);
temp[n]=0;/*
strcpy(str,"You selected: ");
strcat(str,temp);
write(csock,str,strlen(str));*/

strcpy(str,"How many selected products you want to subtract?\n");
write(csock,str,strlen(str));
memset(str,0,sizeof(str));

n=recv(csock,str,size,0);
str[n]=0;
am=atoi(str);
memset(str,0,sizeof(str));
printf("am=%i\n",am);


strcpy(str,"Processing your request... ");
//strcat(str,temp);
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
    strcpy(str,"Products amount changes. Check this using 'show list' command\n");
    write(csock,str,strlen(str));
    memset(str,0,sizeof(str));
    }
else {
    strcpy(str,"Error(no such product or too few products). Please try again.\n");
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

#endif // ADMCOMMANDS

