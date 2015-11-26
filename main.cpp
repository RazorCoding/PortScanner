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
		
		void gethostbyname_(char* hostname)
		{
			char ip[40];
			if ((he = gethostbyname(hostname)) == NULL)
				std::cerr << "GethostByname: " << std::endl;

			addr_list = (struct in_addr **) he->h_addr_list;

			for (int i = 0; addr_list[i] != NULL; i++)
			{
				strncpy(ip, inet_ntoa(*addr_list[i]), 24);
			}
			server.sin_addr.s_addr = inet_addr(ip);
			server.sin_family = AF_INET;
			std::cout << "Scanning: " << ip << std::endl;
		}
		
		bool TcpScan(int startP)
		{
			int s;
			server.sin_port = htons(startP);
			s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			int result = connect(s, (struct sockaddr *)&server, sizeof(server));
			close(s);
			if(result == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool UdpScan(int startP)
		{
			int s;
			server.sin_port = htons(startP);
			s = socket(s,SOCK_DGRAM,0);
			int result = connect(s, (struct sockaddr *)&server, sizeof(server));
			close(s);
			if(result == 0)	
			{
				return true;
			}else
			{
				return false;						
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
		int startP, endP, result;
		 std::cout << " Port range: " << std::endl;; 
		 std::cout << ":";
		 std::cin >> startP; 
		 std::cout << ":";
		 std::cin >> endP;
   		
		 for(;startP<=endP;startP++)
		 {
			if(sLib.TcpScan(startP))
		 	std::cout << "TCP::Port is open :: " << startP << std::endl;
		 	else
		 	std::cout << "TCP::Port is closed :: " << startP << std::endl;
		 	
		 	if(sLib.UdpScan(startP))
		 	std::cout << "UDP::Port is open :: " <<  startP << std::endl;
		 	else
		  	std::cout << "UDP::Port closed :: " << startP <<  std::endl;
		 }
	}
	else if(argv[2])
	{
		int startP, endP;
		std::cout << "Port Range " << std::endl;
		std::cout << ":";
		std::cin >> startP;
		std::cout << ":";
		std::cin >> endP;
		
		for(;startP<=endP;startP++)
		{
			if(sLib.TcpScan(startP))
			std::cout << "TCP::Port is open :: " << startP << std::endl;
			else
			std::cout << "TCP::Port is closed :: " << startP << std::endl;		
		}
	}
	else if(argv[3])
	{
		int startP, endP;
		std::cout << "Port Range-> ";
		std::cout << " Start: ";
		std::cin >> startP;
		std::cout << " End: ";
		std::cin >> endP;
		
		for(;startP<=endP;startP++)
		{
			if(sLib.UdpScan(startP))
			std::cout << "UDP::Port is open :: " << startP << std::endl;
			else
			std::cout << "UDP::Port is closed :: " << startP << std::endl;		
		}
	}
    else std::cerr << "USAGE: <hostname> -T for TcpScan  -U for UdpScan" << std::endl;
	}
return 0;
}