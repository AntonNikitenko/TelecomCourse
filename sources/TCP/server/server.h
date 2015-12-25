#ifndef SERVER
#define SERVER
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


void closeServ(){
FILE *id,*names,*prices,*amount;
id = fopen("id.txt","w");
names = fopen("names.txt","w");
prices = fopen("prices.txt","w");
amount = fopen("amount.txt","w");
int i=0;
for (i=0;i<seNum;i++) {
    if(goods[i].id!=0){
        fprintf(names,"%s",goods[i].name);
        fprintf(id,"%i\n",goods[i].id);
        fprintf(prices,"%i\n",goods[i].price);
        fprintf(amount,"%i\n",goods[i].amount);
    }
    }
fclose(id);
fclose(names);
fclose(prices);
fclose(amount);
}


void servInit(){
FILE *id,*names,*prices,*amount;
id = fopen("id.txt","r");
names = fopen("names.txt","r");
prices = fopen("prices.txt","r");
amount = fopen("amount.txt","r");
int i=0;
while ( !feof(names) ) {
    fgets(goods[i].name,35,names);
    fscanf(id,"%i",&goods[i].id);
    fscanf(prices,"%i",&goods[i].price);
    fscanf(amount,"%i",&goods[i].amount);
    i++;
    seNum++;
    }
fclose(id);
fclose(names);
fclose(prices);
fclose(amount);
}

#endif // SERVER

