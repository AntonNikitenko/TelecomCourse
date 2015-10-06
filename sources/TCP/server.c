#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


struct product{
	int id;
	char *name;
	int price;
	int amount;
};


void server(){
FILE *id,*names,*prices,*amount;
id = fopen("id.txt","r");
names = fopen("names.txt","r");
prices = fopen("prices.txt","r");
amount = fopen("amount.txt","r");
char st[35];
struct product goods[3];
int i=0;
/*while (!feof(names)){
	fgets(st,35,names);
	printf("i = %d\n",i);
	printf("st = %s\n",st);
	goods[i].name=&st;
	printf("name = %s\n",goods[0].name);
	i++;
}*/

//for (i;i<3;i++){

	fgets(st,35,names);
	printf("i = %d\n",0);
	printf("st = %s\n",st);
	goods[0].name=st;
	printf("name = %s\n",goods[0].name);
	printf("name = %s\n",goods[1].name);
	printf("name = %s\n",goods[2].name);

	fgets(st,35,names);
	printf("i = %d\n",1);
	printf("st = %s\n",st);
	goods[1].name=st;
	printf("name = %s\n",goods[0].name);
	printf("name = %s\n",goods[1].name);
	printf("name = %s\n",goods[2].name);

	fgets(st,35,names);
	printf("i = %d\n",2);
	printf("st = %s\n",st);
	goods[2].name=st;
	printf("name = %s\n",goods[0].name);
	printf("name = %s\n",goods[1].name);
	printf("name = %s\n",goods[2].name);

//}


}


int main(int argc, char**argv[])
{
//	int lsock,csock,n;
//	struct sockaddr_in serv_addr,cli_addr;
//	socklen_t addr_len;
//	char mesg[50];
	
	server();
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



