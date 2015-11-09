#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

class Socklib
{
	public:
		struct hostent *he;
		struct in_addr **addr_list;
		struct sockaddr_in server;
		void gethostbyname_(char hostname[])
		{
			char ip[100];
			if ((he = gethostbyname(hostname)) == NULL)
			{
				std::cerr << "GethostByname: " << std::endl;
			}

			addr_list = (struct in_addr **) he->h_addr_list;

			for (int i = 0; addr_list[i] != NULL; i++)
			{
				strcpy(ip, inet_ntoa(*addr_list[i]));
			}
			
			server.sin_addr.s_addr = inet_addr(ip);
			server.sin_family = AF_INET;
		}
			
		void connectScan(int startP, int EndP)
		{
			int s;
			for (int i = startP; i <= EndP; i++)
			{
				s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
					close(s);
			}
		}
}; // end of class

int main(int argc, char *argv[])
{
	Socklib sLib;
	char hostname[100];
	std::cout << "Hostname: ";
	std::cin >> hostname;
	sLib.gethostbyname_(hostname);
	
	int startP, EndP;
	std::cout << "Port Range-> ";
	std::cout << " Start: ";
	std::cin >> startP;
	std::cout << " End: ";
	std::cin >> EndP;

     
	sLib.connectScan(startP,EndP);
	return 0;
}
