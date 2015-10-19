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



void add(int csock){
char *name,*sprice,*samount;
int n,id;
printf("Enter product name:\n");
n=recv(csock,name,1024,0);
name[n]=0;
strcpy (goods[seNum].name, name);
printf("%s",name);

printf("Enter product price:\n");
n=recv(csock,sprice,1024,0);
sprice[n]=0;
//int price=atoi(sprice);
printf("%s",sprice);
//goods[seNum].price=price;

printf("Enter product amount:\n");
n=recv(csock,samount,1024,0);
samount[n]=0;
//int amount=atoi(samount);
printf("%s",samount);
//goods[seNum].amount=amount;

goods[seNum].id=seNum;
seNum++;
}

void buy(int csock){
char *str;
int n;
printf("Enter product name:\n");
n=recv(csock,str,1024,0);
str[n]=0;
printf(" %s ",str);

}




void showList(){
printf("This is the list of products:\n");
printf("id	price	name\n");
int i;
for (i=0;i<seNum-1;i++){
	printf("%i	%i	%s",goods[i].id,goods[i].price,goods[i].name);
}
}




void dialog(int csock){
int com,n;
char *str;
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
switch (com ) {
case 1:
  buy(csock);
  break;
case 2:
  showList();
  break;
case 3:
  add(csock);
  break;
default:
  printf("Incorrect entry. ");
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
char st[35];
int i=0;
while ( !feof(names) ) {
	fgets(goods[i].name,35,names);
	fscanf(id,"%i",&goods[i].id);
	fscanf(prices,"%i",&goods[i].price);
	fscanf(amount,"%i",&goods[i].amount);
	i++;
	seNum++;
	}
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



