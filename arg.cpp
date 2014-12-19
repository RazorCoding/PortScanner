#include<iostream>
#include<fstream>
#include<string.h>
#include<Winsock2.h>
#include"Scan.h"


int Socklib::inistilizeWinSock()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << WSAGetLastError() << std::endl;
	}
	return 0;
}

int Socklib::gethostbyname_(char hostname[])
{
	char ip[100];
	if ((he = gethostbyname(hostname)) == NULL)
	{
		std::cout << "gethostbyname failed: " << WSAGetLastError();
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for (int i = 0; addr_list[i] != NULL; i++)
	{
		strcpy_s(ip, inet_ntoa(*addr_list[i]));
	}
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	return 0;
}
void Socklib::connectScan(int startP, int EndP)
{
	SOCKET s;
	// -------- Connect Scann -------- //
	for (int i = startP; i <= EndP; i++)
	{
		// ----------- Socket Creation ------------ //
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// ------------- Connecting ------------ //
		int result = connect(s, (struct sockaddr *)&server, sizeof(server));
		if (result == 0)
		{
			std::cout << "Port is Open: " << i << std::endl;
		}
		else
		{
			std::cout << "Port is Closed: " << i << std::endl;
		}
		server.sin_port = htons(i);
		closesocket(s);
	}
}
