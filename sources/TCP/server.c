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

struct product goods[100];
int seNum=0;

void dialog(int csock);


void showList(){
printf("\n\nThis is the list of products:\n");
printf("id	amount	price	name\n");
int i;
for (i=0;i<100;i++){
	if(goods[i].id!=0){
		printf("%i	%i	%i	%s",goods[i].id,goods[i].amount,goods[i].price,goods[i].name);
	}
}
printf("seNum=%i\n",seNum);
}


void create(int csock){
char *name1=(char*)malloc(35*sizeof(char));
char *temp1=(char*)malloc(35*sizeof(char));
char *am1=(char*)malloc(7*sizeof(char));
char *price1=(char*)malloc(7*sizeof(char));
int n,am,pr,i;

printf("\nEnter name of product:\n");
n=recv(csock,name1,1024,0);
name1[n]=0;
printf("You created: %s",name1);
strncpy(temp1,name1,strlen(name1)-2);
strcat(temp1,"\n");
strcpy(goods[seNum-1].name,temp1);
free(temp1);
free(name1);

printf("Enter the product price: \n");
n=recv(csock,price1,1024,0);
price1[n]=0;
pr=atoi(price1);
free(price1);
printf("%i\n",pr);
goods[seNum-1].price=pr;

printf("How many of created products you want to add? \n");
n=recv(csock,am1,1024,0);
am1[n]=0;
am=atoi(am1);
free(am1);
printf("%i\n",am);
goods[seNum-1].amount=am;
goods[seNum-1].id=seNum;
for (i=0;i<seNum-1;i++){
	if(goods[i].id==seNum)
		goods[seNum-1].id++;		

}
seNum++;
}




void rem(int csock){
char *name4=(char*)malloc(35*sizeof(char));
int n,i,flag=0;
printf("\n\n\nEnter name of product you want to remove:\n");
n=recv(csock,name4,1024,0);
name4[n]=0;
printf("You selected: %s",name4);
for (i=0;i<100;i++){
	if (!strncmp(goods[i].name,name4,strlen(name4)-2)){
		goods[i].amount=0;
		goods[i].price=0;
		goods[i].id=0;
		goods[i].name[0]=0;
		flag++;
	}	
}
if(flag==1)
	printf("Succesfully removed.\n");
else printf("No such product. Try again.\n");
free(name4);
}








void add(int csock){
char *name3=(char*)malloc(35*sizeof(char));
char *am3=(char*)malloc(7*sizeof(char));
int n,am,i,flag=0;
printf("\n\nEnter name of product:\n");
n=recv(csock,name3,1024,0);
name3[n]=0;
printf("How many selected products you want to add?\n");
n=recv(csock,am3,1024,0);
am3[n]=0;
am=atoi(am3);
free(am3);
for (i=0;i<seNum-1;i++){
	if (!strncmp(goods[i].name,name3,strlen(name3)-2)){
		goods[i].amount=goods[i].amount+am;
		flag++;
	}	
}
if(flag==1)
	printf("Changes doned.\n");
else printf("No such product. Try again.\n");
free(name3);
}




void buy(int csock){
char *name2=(char*)malloc(35*sizeof(char));
char *am2=(char*)malloc(7*sizeof(char));
int n,am,i,flag=0;
printf("\n\nEnter name of selected product:\n");
n=recv(csock,name2,1024,0);
name2[n]=0;
printf("You selected: %s",name2);
printf("How many selected products you want to buy?\n");
n=recv(csock,am2,1024,0);
am2[n]=0;
am=atoi(am2);
free(am2);
printf("Processing your request... %s",name2);
printf("Amount - %d\n",am);
for (i=0;i<seNum-1;i++){
	if (!strncmp(goods[i].name,name2,strlen(name2)-2)){
		goods[i].amount=goods[i].amount-am;
		flag++;
	}	
}

if(flag==1)
	printf("Purchase is made. Thank you for your order.\n");
else printf("Purchase error. Please try again.\n");
free(name2);
}



//void disc(int csock){
//close(csock);
//}





void dialog(int csock){
int n,com=0;
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
free(str);
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
case 4:
   create(csock);
  break;
case 5:
   rem(csock);
   break;
//case 6:
//   disc(csock);
//   break;
default:
  printf("Incorrect entry. ");
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



