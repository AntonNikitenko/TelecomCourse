#include<stdio.h>
#include<winsock2.h>
#include<process.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
DWORD WINAPI threadHandler(LPVOID);
#define size 1024
#define BUFLEN 1024 //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

struct product{
	int id;
	char name[35];
	int price;
	int amount;
};
typedef struct {
	int sockfd;
	struct sockaddr_in client;
	int clilen;
} btClient;

int cl = 0, clientsNum = 0, seNum = 0;
struct product goods[100];

void closeServ(){
	FILE *id, *names, *prices, *amount;
	id = fopen("id.txt", "w");
	names = fopen("names.txt", "w");
	prices = fopen("prices.txt", "w");
	amount = fopen("amount.txt", "w");
	int i = 0;
	for (i = 0; i<seNum; i++) {
		if (goods[i].id != 0){
			fprintf(names, "%s", goods[i].name);
			fprintf(id, "%i\n", goods[i].id);
			fprintf(prices, "%i\n", goods[i].price);
			fprintf(amount, "%i\n", goods[i].amount);
		}
	}
	fclose(id);
	fclose(names);
	fclose(prices);
	fclose(amount);
}

void disc(){
	closeServ();
	cl = 1;
	//close(csock);
}

void create(btClient client){
	char temp[size];
	char temp1[size];
	char str[size];
	int n, am, pr, i = 0, j = 0;
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;

	seNum++;
	sendto(csock, "\nEnter name of product:\n", strlen("\nEnter name of product:\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, temp, size, 0, (struct sockaddr *)&si_other, &slen);
	temp[n] = 0;
	printf("\n\n%s\n\n", temp);

	strcpy(goods[seNum - 1].name, temp);
	memset(temp, 0, sizeof(temp));

	sendto(csock, "Enter the product price: \n", strlen("Enter the product price: \n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, str, size, 0, (struct sockaddr *)&si_other, &slen);
	str[n] = 0;
	pr = atoi(str);
	memset(str, 0, sizeof(str));
	goods[seNum - 1].price = pr;

	sendto(csock, "How many of created products you want to add? \n", strlen("How many of created products you want to add? \n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, str, size, 0, (struct sockaddr *)&si_other, &slen);
	str[n] = 0;
	am = atoi(str);
	memset(str, 0, sizeof(str));

	goods[seNum - 1].amount = am;
	goods[seNum - 1].id = 1;

	for (j = 0; j<seNum - 1; j++)
	for (i = 0; i<seNum - 1; i++)
	{
		if (goods[seNum - 1].id == goods[i].id){
			goods[seNum - 1].id++;
		}
	}
}

void rem(btClient client){
	char temp[size];
	char str[size];
	int n, i = 0, flag = 0, r_num = 0;
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;
	sendto(csock, "\n\n\nEnter name of product you want to remove:\n", strlen("\n\n\nEnter name of product you want to remove:\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, temp, size, 0, (struct sockaddr *)&si_other, &slen);
	temp[n] = 0;


	for (i = 0; i<seNum; i++){
		if (!strncmp(goods[i].name, temp, strlen(temp) - 2)){
			r_num = i;
			flag++;
		}
	}

	if (flag>0){
		for (i = r_num; i<seNum - 1; i++){
			goods[i].amount = goods[i + 1].amount;
			goods[i].id = goods[i + 1].id;
			goods[i].price = goods[i + 1].price;
			strcpy(goods[i].name, goods[i + 1].name);

		}
		memset(&goods[seNum - 1], 0, sizeof(struct product));
		seNum--;

		sendto(csock, "Succesfully removed.\n", strlen("Succesfully removed.\n"), 0, (struct sockaddr *)&si_other, slen);
	}
	else {
		sendto(csock, "No such product. Try again.\n", strlen("No such product. Try again.\n"), 0, (struct sockaddr *)&si_other, slen);
	}
	memset(temp, 0, sizeof(temp));
}

void add(btClient client){
	char temp[size];
	char str[size];
	int n, am, i, flag = 0;
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;

	sendto(csock, "\n\nEnter name of product:\n", strlen("\n\nEnter name of product:\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, temp, size, 0, (struct sockaddr *)&si_other, &slen);
	temp[n] = 0;

	sendto(csock, "How many selected products you want to add?\n", strlen("How many selected products you want to add?\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, str, size, 0, (struct sockaddr *)&si_other, &slen);
	str[n] = 0;
	am = atoi(str);
	memset(str, 0, sizeof(str));
	printf("am=%i", am);


	for (i = 0; i<seNum; i++){
		if (!strncmp(goods[i].name, temp, strlen(temp) - 2)){
			goods[i].amount = goods[i].amount + am;
			flag++;
		}
	}
	if (flag == 1){
		sendto(csock, "Changes doned\n", strlen("Changes doned\n"), 0, (struct sockaddr *)&si_other, slen);

	}
	else {
		sendto(csock, "No such product. Try again.\n", strlen("No such product. Try again.\n"), 0, (struct sockaddr *)&si_other, slen);
	}
	memset(temp, 0, sizeof(temp));
}

void decr(btClient client){
	char temp[size];
	char str[size];
	int n, am, i, flag = 0;
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;

	sendto(csock, "\n\nEnter name of selected product:\n", strlen("\n\nEnter name of selected product:\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, temp, size, 0, (struct sockaddr *)&si_other, &slen);
	temp[n] = 0;

	sendto(csock, "How many selected products you want to subtract?\n", strlen("How many selected products you want to subtract?\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, str, size, 0, (struct sockaddr *)&si_other, &slen);
	str[n] = 0;
	am = atoi(str);
	memset(str, 0, sizeof(str));
	printf("am=%i\n", am);

	sendto(csock, "Processing your request... \n", strlen("Processing your request... \n"), 0, (struct sockaddr *)&si_other, slen);


	for (i = 0; i<seNum; i++){
		if (!strncmp(goods[i].name, temp, strlen(temp) - 2)){
			if (am>goods[i].amount)
			{
				flag = 0;
			}
			else
			{
				goods[i].amount = goods[i].amount - am;
				flag++;
			}
		}
	}
	if (flag == 1){
		sendto(csock, "Products amount changes. Check this using 'show list' command\n", strlen("Products amount changes. Check this using 'show list' command\n"), 0, (struct sockaddr *)&si_other, slen);
	}
	else {
		sendto(csock, "Error(no such product or too few products). Please try again.\n", strlen("Error(no such product or too few products). Please try again.\n"), 0, (struct sockaddr *)&si_other, slen);
	}
	memset(temp, 0, sizeof(temp));
}

void buy(btClient client){
	char temp[size];
	char str[size];
	int n, am, i, flag = 0;
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;
	sendto(csock, "\n\nEnter name of selected product:\n", strlen("\n\nEnter name of selected product:\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, temp, size, 0, (struct sockaddr *)&si_other, &slen);
	temp[n] = 0;

	sendto(csock, "How many selected products you want to buy?\n", strlen("How many selected products you want to buy?\n"), 0, (struct sockaddr *)&si_other, slen);

	n = recvfrom(csock, str, size, 0, (struct sockaddr *)&si_other, &slen);
	str[n] = 0;
	am = atoi(str);
	memset(str, 0, sizeof(str));


	sprintf(str, "\n\n%s %s\n", "Processing your request...", temp);
	sendto(csock, str, strlen(str), 0, (struct sockaddr *)&si_other, slen);
	memset(str, 0, sizeof(str));

	for (i = 0; i<seNum - 1; i++){
		if (!strncmp(goods[i].name, temp, strlen(temp) - 2)){
			if (am>goods[i].amount)
			{
				flag = 0;
			}
			else
			{
				goods[i].amount = goods[i].amount - am;
				flag++;
			}
		}
	}
	if (flag == 1){
		sendto(csock, "Purchase is made. Thank you for your order.\n", strlen("Purchase is made. Thank you for your order.\n"), 0, (struct sockaddr *)&si_other, slen);
	}
	else {
		sendto(csock, "Purchase error. Please try again.\n", strlen("Purchase error. Please try again.\n"), 0, (struct sockaddr *)&si_other, slen);
	}
	memset(temp, 0, sizeof(temp));
}

void showList(btClient client){
	char temp[size];
	int i, n;
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;
	Sleep(5);
	n = recvfrom(csock, temp, size, 0, (struct sockaddr *) &si_other, &slen);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	strcpy(temp, "\n\nThis is the list of products:\n");
	sendto(csock, temp, strlen(temp), 0, (struct sockaddr *)&si_other, slen);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	strcpy(temp, "id	amount	price	name\n");
	sendto(csock, temp, strlen(temp), 0, (struct sockaddr *)&si_other, slen);
	memset(temp, 0, sizeof(temp));
	Sleep(5);


	sprintf(temp, "%i", seNum);
	sendto(csock, temp, strlen(temp), 0, (struct sockaddr *)&si_other, slen);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	n = recvfrom(csock, temp, size, 0, (struct sockaddr *)&si_other, &slen);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	for (i = 0; i<seNum; i++){
		if (goods[i].id != 0){
			sprintf(temp, "%i       %i       %i       %s", goods[i].id, goods[i].amount, goods[i].price, goods[i].name);
			sendto(csock, temp, strlen(temp), 0, (struct sockaddr *)&si_other, slen);
			memset(temp, 0, sizeof(temp));
		}
	}
}

void admDial(btClient client){
	int n, com = 0;
	char temp[size];
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;
	Sleep(5);
	n = recvfrom(csock, temp, size, 0, (struct sockaddr *) &si_other, &slen);
	temp[n] = 0;
	printf("recv=%s", temp);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	strcpy(temp, "\nAvailable commands : increase,decrease,create,remove,showlist,exit");
	sendto(csock, temp, strlen(temp), 0, (struct sockaddr *) &si_other, slen);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	strcpy(temp, "\nEnter command:\n");
	sendto(csock, temp, strlen(temp), 0, (struct sockaddr *) &si_other, slen);
	memset(temp, 0, sizeof(temp));


	n = recvfrom(csock, temp, size, 0, (struct sockaddr *) &si_other, &slen);
	temp[n] = 0;
	if (!strcmp(temp, "increase\r\n"))
		com = 1;
	if (!strcmp(temp, "decrease\r\n"))
		com = 2;
	if (!strcmp(temp, "create\r\n"))
		com = 3;
	if (!strcmp(temp, "remove\r\n"))
		com = 4;
	if (!strcmp(temp, "showlist\r\n"))
		com = 5;
	if (!strcmp(temp, "exit\r\n"))
		com = 6;
	memset(temp, 0, sizeof(temp));
	switch (com) {
	case 1:
		printf("\nincrease\n");
		add(client);
		break;
	case 2:
		printf("\ndecrease\n");
		decr(client);
		break;
	case 3:
		printf("\ncreate\n");
		create(client);
		break;
	case 4:
		printf("\nremove\n");
		rem(client);
		break;
	case 5:
		printf("\nshowlist\n");
		showList(client);
		break;
	case 6:
		printf("\nexit\n");
		disc();
		break;
	default:

		strcpy(temp, "Incorrect entry.\n");
		sendto(csock, temp, strlen(temp), 0, (struct sockaddr*)&si_other, slen);
		memset(temp, 0, sizeof(temp));

	}
}

void usrDial(btClient client){
	int n, com = 0;
	char temp[size];
	Sleep(5);
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;
	n = recvfrom(csock, temp, size, 0, (struct sockaddr *) &si_other, &slen);
	temp[n] = 0;
	printf("recv=%s", temp);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	strcpy(temp, "\nAvailable commands : buy,showlist,exit");
	sendto(csock, temp, strlen(temp), 0, (struct sockaddr *) &si_other, slen);
	memset(temp, 0, sizeof(temp));
	Sleep(5);

	strcpy(temp, "\nEnter command:\n");
	sendto(csock, temp, strlen(temp), 0, (struct sockaddr *) &si_other, slen);
	memset(temp, 0, sizeof(temp));


	n = recvfrom(csock, temp, size, 0, (struct sockaddr *) &si_other, &slen);
	temp[n] = 0;
	if (!strcmp(temp, "buy\r\n"))
		com = 1;
	if (!strcmp(temp, "showlist\r\n"))
		com = 2;
	if (!strcmp(temp, "exit\r\n"))
		com = 3;
	memset(temp, 0, sizeof(temp));
	switch (com) {
	case 1:
		printf("buy\n");
		buy(client);
		break;
	case 2:
		printf("showlist\n");
		showList(client);
		break;
	case 3:
		printf("exit\n");
		disc();
		break;
	default:

		strcpy(temp, "Incorrect entry.\n");
		sendto(csock, temp, strlen(temp), 0, (struct sockaddr *) &si_other, slen);
		memset(temp, 0, sizeof(temp));
		break;
	}
}


void servInit(){
	FILE *id, *names, *prices, *amount;
	id = fopen("id.txt", "r");
	names = fopen("names.txt", "r");
	prices = fopen("prices.txt", "r");
	amount = fopen("amount.txt", "r");
	int i = 0;
	while (!feof(names)) {
		fgets(goods[i].name, 35, names);
		fscanf(id, "%i", &goods[i].id);
		fscanf(prices, "%i", &goods[i].price);
		fscanf(amount, "%i", &goods[i].amount);
		i++;
		seNum++;
	}
	strcat(goods[seNum - 1].name, "\n");
	fclose(id);
	fclose(names);
	fclose(prices);
	fclose(amount);
}

unsigned _stdcall handler(void* param){
	char str[size];
	int n, usr = 0;

	btClient* cli = (btClient*)param;
	btClient client = *cli;
	int csock = client.sockfd;
	struct sockaddr_in si_other = client.client;
	int slen = client.clilen;

	if ((recvfrom(csock, str, size, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	memset(str, 0, sizeof(str));
	//print details of the client/peer and the data received
	Sleep(5);
	sendto(csock, "\n\nWelcome to our e-shop!\n", strlen("\n\nWelcome to our e-shop!\n"), 0, (struct sockaddr *) &si_other, slen);
	Sleep(5);
	sendto(csock, "Enter your name:\n", strlen("Enter your name:\n"), 0, (struct sockaddr *) &si_other, slen);
	n = recvfrom(csock, str, size, 0, (struct sockaddr *) &si_other, &slen);
	str[n] = 0;

	if (!strcmp(str, "admin")){
		usr = 1;
	}
	else
		usr = 2;
	while (1){
		switch (usr) {
		case 1:
			admDial(client);
			break;
		case 2:
			usrDial(client);
			break;
		}
		if (cl != 0){
			cl = 0;
			break;
		}
	}
	memset(str, 0, sizeof(str));
	strcpy(str, "\nConnection closed.\n");
	sendto(csock, str, strlen("\nConnection closed.\n"), 0, (struct sockaddr *) &si_other, slen);
	memset(str, 0, sizeof(str));
	closesocket(csock);
};

int main()
{
	SOCKET s;
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);
	struct sockaddr_in server;
	int n;
	int newport;
	char str[size];
	WSADATA wsa;

	servInit();
	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	while (1){
		int ns;
		recvfrom(s, str, size, 0, (struct sockaddr *) &si_other, &slen);

		struct sockaddr_in serveraddr;
		ns = socket(AF_INET, SOCK_DGRAM, 0);
		clientsNum++;
		newport = PORT + clientsNum + 1;
		sprintf(str, "%i", newport);
		printf("%i\n", newport);

		int optval = 1;
		setsockopt(ns, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(int));


		memset((char *)&serveraddr, '\0', sizeof(serveraddr));

		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = INADDR_ANY;
		serveraddr.sin_port = htons(newport);
		bind(ns, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

		sendto(s, str, strlen(str), 0, (struct sockaddr *)&si_other, slen);
		memset(str, 0, sizeof(str));

		struct sockaddr_in newclientaddr; /* client addr */
		int newclientlen = sizeof(newclientaddr); /* byte size of client's address */
		memset(str, 0, size);
		recvfrom(ns, str, sizeof(str), 0, (struct sockaddr *) &newclientaddr, &newclientlen);
		printf("\ngg=%s\n", str);

		btClient client;
		client.sockfd = ns;
		client.client = newclientaddr;
		client.clilen = newclientlen;

		HANDLE t;
		t = (HANDLE)_beginthreadex(NULL, 0, &handler, (void*)&client, 0, NULL);
	}
	closesocket(s);
	WSACleanup();
}