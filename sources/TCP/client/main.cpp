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
#include "dialogs.h"

#define PORT 1234
//#define SERVERADDR "10.1.99.25"
#define size  1024

int cl = 0;


int main()
{
	setlocale(LC_ALL, "Russian");
	char buffer[size];
	int i, n, usr = 0;
	char str[size];
	char inp[size];
	char SERVERADDR[size];
	printf("Enter server's address:\n");
	scanf("%s",SERVERADDR);
	if (WSAStartup(0x202, (WSADATA *)&buffer[0]))
	{
		printf("WSAStart error %d\n", WSAGetLastError());
		_getch();
		return -1;
	}

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		printf("Socket() error %d\n", WSAGetLastError());
		_getch();
		return -1;
	}
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	HOSTENT *hst;

	if (inet_addr(SERVERADDR) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else
	if (hst = gethostbyname(SERVERADDR))
		((unsigned long *)&dest_addr.sin_addr)[0] =
		((unsigned long **)hst->h_addr_list)[0][0];
	else
	{
		printf("Invalid address %s\n", SERVERADDR);
		closesocket(sock);
		WSACleanup();
		_getch();
		return -1;
	}

	if (connect(sock, (sockaddr *)&dest_addr,
		sizeof(dest_addr)))
	{
		printf("Connect error %d\n", WSAGetLastError());
		_getch();
		return -1;
	}
	else
	{
		n = recv(sock, str, size, 0);
		str[n] = 0;
		printf(str);
		memset(str, 0, sizeof(str));

		strcpy(str, "1");
		send(sock, str, strlen("1"), 0);
		memset(str, 0, sizeof(str));

		n = recv(sock, str, size, 0);
		str[n] = 0;
		printf(str);
		memset(str, 0, sizeof(str));

		scanf("%s", inp);
		if (!strcmp(inp, "admin")){
			usr = 1;
		}
		else
			usr = 0;
		while (cl == 0){
			switch (usr) {
			case 1:
				memset(inp, 0, sizeof(inp));
				send(sock, "admin\r\n", strlen("admin\r\n"), 0);
				admDial(sock);
				break;
			case 0:
				memset(inp, 0, sizeof(inp));
				send(sock, "user\r\n", strlen("user\r\n"), 0);
				usrDial(sock);
				break;
			}
		}
		n = recv(sock, str, size, 0);
		str[n] = 0;
		printf(str);
		memset(str, 0, sizeof(str));
		closesocket(sock);
		WSACleanup();
		return 0;
	}
}