#ifndef GENCOMMANDS
#define GENCOMMANDS
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
#define size 1024

void showList(int sock){
	char str[size];
	char temp[1024];
	int counter,i;
	int n;

	n = recv(sock, str, size, 0);
	str[n] = 0;
	printf(str);
	memset(str, 0, sizeof(str));


	strcpy(temp, "1");
	send(sock, temp, strlen("1"), 0);
	memset(temp, 0, sizeof(temp));

	n = recv(sock, str, size, 0);
	str[n] = 0;
	printf(str);
	memset(str, 0, sizeof(str));

	strcpy(temp, "1");
	send(sock, temp, strlen("1"), 0);
	memset(temp, 0, sizeof(temp));

	n = recv(sock, str, size, 0);
	str[n] = 0;
	counter = atoi(str);
	memset(str, 0, sizeof(str));

	strcpy(temp, "1");
	send(sock, temp, strlen("1"), 0);
	memset(temp, 0, sizeof(temp));

	for (i = 0; i < counter - 1; i++){
		n = recv(sock, str, size, 0);
		str[n] = 0;
		printf(str);
		memset(str, 0, sizeof(str));


		strcpy(temp, "1");
		send(sock, temp, strlen("1"), 0);
		memset(temp, 0, sizeof(temp));
	}

}
#endif // GENCOMMANDS