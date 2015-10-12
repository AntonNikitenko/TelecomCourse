#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


struct product{
	int id;
	char name[35];
	int price;
	int amount;
};

void buy(){
printf("buy product\n");
}

void showList(struct product list[]){
printf("This is the list of products:\n");
printf("id	price	name\n");
int i;
for (i=0;i<7;i++){
	printf("%i	%i	%s",list[i].id,list[i].price,list[i].name);
}
}


void dialog(struct product goods[]){    //принимаем команды клиента и решаем что дальше делать
char str[15];
int com;
printf("Enter your command:\n");
scanf("%s", str);
if (!strcmp(str, "buy"))
        com=1;
if (!strcmp(str, "list"))
        com=2;
switch (com ) {
case 1:
  buy();
  break;
case 2:
  showList(goods);
  break;
default:
  printf("Incorrect entry. ");
  dialog(goods);
  break;
}
}


void servInit(){   //загружаем состояние магазина-информацию о товарах
FILE *id,*names,*prices,*amount;
id = fopen("id.txt","r");
names = fopen("names.txt","r");
prices = fopen("prices.txt","r");
amount = fopen("amount.txt","r");
char st[35];
struct product goods[10];
int i=0;
while ( !feof(names) ) {
	fgets(goods[i].name,35,names);
	fscanf(id,"%i",&goods[i].id);
	fscanf(prices,"%i",&goods[i].price);
	fscanf(amount,"%i",&goods[i].amount);
	i++;
	}
dialog(goods);
}



int main(int argc, char**argv[])
{
//	int lsock,csock,n;
//	struct sockaddr_in serv_addr,cli_addr;
//	socklen_t addr_len;
//	char mesg[50];
	
	servInit();
/*	return 0;

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

	for (;;)
	{
		n = recvfrom(csock,mesg,50,0,(struct sockaddr *)&cli_addr,&addr_len);
 //   		sendto(csock,mesg,n,0,(struct sockaddr *)&cli_addr,sizeof(cli_addr));
	
		printf("Welcome to our e-shop!\n");
		mesg[n] = 0;
		server(mesg);
        
  //      	printf("Received the following:\n");
    //    	printf("%s",mesg);
      //  	printf("-------------------------------------------------------\n");
	}
	close(csock);*/
}



