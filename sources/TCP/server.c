#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


struct product{
	int id;
	char name[35];
	int price;
	int amount;
};

struct product goods[10];
int seNum=0;


void showList(){
printf("This is the list of products:\n");
printf("id	price	name\n");
int i;
for (i=0;i<seNum-1;i++){
	printf("%i	%i	%s",goods[i].amount,goods[i].price,goods[i].name);
}
}



void add(int csock){
char *prname=(char*)malloc(35*sizeof(char));
char *pram=(char*)malloc(7*sizeof(char));
int n,am,i;
printf("Enter name of product:\n");
n=recv(csock,prname,1024,0);
prname[n]=0;
printf("You selected: %s",prname);
printf("How many selected products you want to add?\n");
n=recv(csock,pram,1024,0);
pram[n]=0;
am=atoi(pram);
for (i=0;i<seNum-1;i++){
	if (!strncmp(goods[i].name,prname,strlen(prname)-2))
		goods[i].amount=goods[i].amount+am;	
}
free(prname);
free(pram);
printf("New product list:\n");
	showList();
}


void buy(int csock){
char *prname=(char*)malloc(35*sizeof(char));
char *pram=(char*)malloc(7*sizeof(char));
char *ch=(char*)malloc(5*sizeof(char));
char *ch1=(char*)malloc(5*sizeof(char));
int n,am,i;
printf("Enter name of selected product:\n");
n=recv(csock,prname,1024,0);
prname[n]=0;
printf("You selected: %s",prname);
printf("How many selected products you want to buy?\n");
n=recv(csock,pram,1024,0);
pram[n]=0;
am=atoi(pram);
printf("Do you really want to buy %s",prname);
printf("Amount - %d (yes/no)\n",am);
n=recv(csock,ch,1024,0);
if (!strcmp(ch,"yes\r\n")){
	for (i=0;i<seNum-1;i++){
		if (!strncmp(goods[i].name,prname,strlen(prname)-2))
			goods[i].amount=goods[i].amount-am;	
	}
}
free(ch);
free(prname);
free(pram);
printf("Do you to view our product list?(yes/no)\n");
n=recv(csock,ch1,1024,0);
if (!strcmp(ch1,"yes\r\n"));{
	free(ch1);
	showList();
}
}









void dialog(int csock){
int com,n;
char *str=(char*)malloc(35*sizeof(char));
printf("\nEnter command:\n");
n=recv(csock,str,1024,0);
str[n]=0;
printf("%s\n",str);
if (!strcmp(str, "buy\r\n"))
        com=1;
if (!strcmp(str, "list\r\n"))
        com=2;
if (!strcmp(str, "add\r\n"))
        com=3;
if (!strcmp(str, "create\r\n"))
        com=4;
if (!strcmp(str, "remove\r\n"))
        com=5;
if (!strcmp(str, "exit\r\n"))
        com=6;
switch (com ) {
case 1:
  free(str);
  buy(csock);
  break;
case 2:
  free(str);
  showList();
  break;
case 3:
  free(str);
  add(csock);
  break;
default:
  printf("Incorrect entry. ");
  free(str);
  dialog(csock);
  break;
}
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




int main(int argc, char**argv[])
{
	int lsock,csock,n;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t addr_len;
	servInit();
	

	lsock=socket(AF_INET,SOCK_STREAM,0);

	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 	serv_addr.sin_port=htons(32000);
	bind(lsock,(struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(lsock,1024);
	addr_len=sizeof(cli_addr);

	csock=accept(lsock,(struct sockaddr *)&cli_addr,&addr_len);
	close(lsock);

	printf("Welcome to our e-shop!\n");
	for (;;)
	{
		dialog(csock);

	}
	close(csock);
}



