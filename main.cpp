#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
class Socklib
{
	public:
		struct hostent *he;
		struct in_addr **addr_list;
		struct sockaddr_in server, *servinfo;	
		
		/*void getaddrinfo_(char *hostname)
		{
			memset(&server, 0 ,  sizeof(server));
			int status;
			if((status = getaddrinfo(hostname,"80",&server, &servinfo)) == -1)
			{
				std::cerr << "getaddrinfo " << std::endl;
			}
		}*/

		void gethostbyname_(char* hostname)
		{
			char ip[40];
			if ((he = gethostbyname(hostname)) == NULL)
			{
				std::cerr << "GethostByname: " << std::endl;
			}

			addr_list = (struct in_addr **) he->h_addr_list;

			for (int i = 0; addr_list[i] != NULL; i++)
			{
				strncpy(ip, inet_ntoa(*addr_list[i]), 4);
			}

			server.sin_addr.s_addr = inet_addr(ip);
			server.sin_family = AF_INET;
		}
		
		void TcpScan(int startP, int endP)
		{
			int s;
			// -------- Connect Scann -------- //
			for (int i = startP; i <= endP; i++)
			{
				server.sin_port = htons(i);
				// ----------- Socket Creation ------------ //
				std::cout << "HIT #1" << std::endl;
				s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				std::cout << "HIT #2" << std::endl;
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

				close(s);
			}
		}

		void UdpScan(int startP, int endP)
		{
			int s;
			for(int i=startP; i <= endP; i++)
			{
				server.sin_port = htons(i);
				s = socket(s,SOCK_DGRAM,0);
				std::cout << "HIT #3" << std::endl;
				int result = connect(s, (struct sockaddr *)&server, sizeof(server));
				std::cout << "HIT #4" << std::endl;
				if(result == 0)
				{
					std::cout << "Port is Open: " << i << std::endl;
				}
					else
					{
						std::cout << "Port is Closed: " << i << std::endl;
					}
				close(s);
			}
		}
}; // end of class

int main(int argc, char *argv[])
{
	if(argc > 1)
	{	
	Socklib sLib;
	
       // std::string hostname[100] = "hostname";
      // hostname = argv[1];
	
	sLib.gethostbyname_(argv[1]);

	if(argv[2] && argv[3])
	{
		int startP, endP;
		 std::cout << " Port range: " << std::endl;; 
		 std::cout << ":";
		 std::cin >> startP; 
		 std::cout << ":";
		 std::cin >> endP;
   		 std::cout << "TCP Scanning..." << std::endl;
		 sLib.TcpScan(startP, endP);	
		 std::cout << "UDP scanning..." << std::endl;
		 sLib.UdpScan(startP, endP);	
	}
	else if(argv[2])
	{
		int startP, endP;
		std::cout << "Port Range " << std::endl;
		std::cout << ":";
		std::cin >> startP;
		std::cout << ":";
		std::cin >> endP;
		sLib.TcpScan(startP,endP);
	}
	else if(argv[3])
	{
		int startP, endP;
		std::cout << "Port Range-> ";
		std::cout << " Start: ";
		std::cin >> startP;
		std::cout << " End: ";
		std::cin >> endP;
		sLib.UdpScan(startP,endP);
	}
	}else return std::cerr << "USAGE: <hostname> -T for TcpScan  -U for UdpScan" << std::endl;
return 0;
}
