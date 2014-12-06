#include<iostream> 
#include<fstream>
#include<cstring>
#include<WinSock2.h>

#pragma comment (lib, "ws2_32.lib") // Winsock lib

using namespace std;

int main(int argc, char *argv[])
{
	// --------- Varibales --------//
	SOCKET s;
	WSADATA wsa;
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;
	struct sockaddr_in server;

	// ----- Inistializing WinSock ------ //
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << WSAGetLastError() << std::endl;
	}

	// ---- Get hostname ---- //
	char hostname[100];
	std::cout << "Hostname: ";
	std::cin >> hostname;

	// ----------- Port Range ------------- //
	int startP, EndP;
	std::cout << "Port Range " << std::endl;
	std::cout << ":";
	std::cin >> startP;
	std::cout << ":";
	std::cin >> EndP;
	
	// -------- GetHostByName --------- //
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

	std::cout << "Scanning Starting " << ip << " --->" << startP << " To " << EndP << std::endl;

	// -------- Connect Scann -------- //
	for (int i = startP; i <= EndP ; i++)
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
		std::cin.get();
		return 0;
}
