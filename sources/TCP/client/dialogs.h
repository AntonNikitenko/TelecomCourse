#ifndef DIALOGS
#define DIALOGS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <locale.h> 
#include <malloc.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
/*#include "product.h"*/
#include "admcommands.h"
/*#include "usrcommands.h"
#include "gencommands.h"
#include "server.h"*/
#include "gencommands.h"
#define size 1024

extern int cl;

void usrDial(int sock){
	char str[size];
	char temp[1024];
	int com = 0;
	int n;

	n = recv(sock, str, size, 0);
	str[n] = 0;
	printf(str);
	memset(str, 0, sizeof(str));

	strcpy(temp, "\nAvailable commands : showlist,buy,exit");
	send(sock, temp, strlen(temp), 0);
	memset(temp, 0, sizeof(temp));

	n = recv(sock, str, size, 0);
	str[n] = 0;
	printf(str);
	memset(str, 0, sizeof(str));

	scanf("%s", str);
	strcat(str, "\r\n");
	if (!strcmp(str, "showlist\r\n")){
		com = 1;
		send(sock, "showlist\r\n", strlen("showlist\r\n"), 0);
		showList(sock);
	}
	if (!strcmp(str, "buy\r\n")){
		com = 2;
		send(sock, "buy\r\n", strlen("buy\r\n"), 0);
		decrease(sock);
	}
	if (!strcmp(str, "exit\r\n")){
		com = 3;
		send(sock, "exit\r\n", strlen("exit\r\n"), 0);
		cl = 1;
	//	showList(sock);
	}
	if (com == 0){

		send(sock, "incorrect\r\n", strlen("incorrect\r\n"), 0);

		n = recv(sock, str, size, 0);
		str[n] = 0;
		printf(str);
		memset(str, 0, sizeof(str));
	}
	memset(str, 0, sizeof(str));
}






void admDial(int sock){
	char str[size]; 
	char temp[1024];
	int com = 0;
	int n;

	n = recv(sock, str, size, 0);
	str[n] = 0;
	printf(str);
	memset(str, 0, sizeof(str));

	strcpy(temp, "\nAvailable commands : increase, decrease,create,remove,showlist,exit");
	send(sock, temp, strlen(temp), 0);
	memset(temp, 0, sizeof(temp));

	n = recv(sock, str, size, 0);
	str[n] = 0;
	printf(str);
	memset(str, 0, sizeof(str));

	scanf("%s", str);
	strcat(str, "\r\n");

	if (!strcmp(str, "increase\r\n"))
	{
		com = 1;
		send(sock, "increase\r\n", strlen("increase\r\n"), 0);
		increase(sock);
	}
	if (!strcmp(str, "decrease\r\n")){
		com = 2;
		send(sock, "decrease\r\n", strlen("decrease\r\n"), 0);
		decrease(sock);
	}
	if (!strcmp(str, "create\r\n"))
	{
		com = 3;
		send(sock, "create\r\n", strlen("create\r\n"), 0);
		create(sock);
	}
	if (!strcmp(str, "remove\r\n")){
		com = 4;
		send(sock, "remove\r\n", strlen("remove\r\n"), 0);
		rem(sock);
	}
	if (!strcmp(str, "showlist\r\n")){
		com = 5;
		send(sock, "showlist\r\n", strlen("showlist\r\n"), 0);
		showList(sock);
	}
	if (!strcmp(str, "exit\r\n")){
		com = 6;
		send(sock, "exit\r\n", strlen("exit\r\n"), 0);
		//closesocket(sock);
		cl = 1;
		//showList(sock);
	}


	if (com == 0){

		send(sock, "incorrect\r\n", strlen("incorrect\r\n"), 0);

		n = recv(sock, str, size, 0);
		str[n] = 0;
		printf(str);
		memset(str, 0, sizeof(str));
	}
	memset(str, 0, sizeof(str));
}


#endif // DIALOGS