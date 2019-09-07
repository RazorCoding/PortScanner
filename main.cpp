// NEED DEBUGGING

include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netdb.h>
#include <cstring>
#include <iostream>

class P {
       public:
	void gethostbyname_(char *);
	bool TcpScan(int);
	bool UdpScan(int);
} Pi;

struct hostent *he;
struct in_addr **addr_list;
struct sockaddr_in server, *servinfo;

// GetHostByName()
void P ::gethostbyname_(char *hostname) {
	char ip[40];
	if ((he = gethostbyname(hostname)) == NULL)
		std::cerr << "GethostByname: " << std::endl;

	addr_list = (struct in_addr **)he->h_addr_list;

	for (int i = 0; addr_list[i] != NULL; i++) {
		strncpy(ip, inet_ntoa(*addr_list[i]), 24);
	}
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	std::cout << "Scanning: " << ip << std::endl;
}
// TCP Scan
bool P ::TcpScan(int counter) {
	server.sin_port = htons(counter);
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int result = connect(s, (struct sockaddr *)&server, sizeof(server));
	close(s);
	if (result == 0) {
		return true;
	} else {
		return false;
	}
}

// UDP Scan
bool P ::UdpScan(int counter) {
	int s;
	server.sin_port = htons(counter);
	s = socket(s, SOCK_DGRAM, 0);
	int result = connect(s, (struct sockaddr *)&server, sizeof(server));
	close(s);
	if (result == 0) {
		return true;
	} else {
		return false;
	}
}
// Main Function
int main(int argc, char *argv[]) {
	bool flag;
	std::string T = "-T";
	std::string U = "-U";
	int counter = 0, range = 0;
	int portS = 0, portE = 0;
	if (argc < 3) {
		std::cout << "USAGE: Hostname -T for TCP SCAN -U For UDP scan" << std::endl;
		exit(1);
	}
	if (argv[2] == T){
		Pi.gethostbyname_(argv[1]);
		std::cout << "Enter port range: ";
		std::cin >> range;
		for (; counter <= range; counter++) {
			flag = Pi.TcpScan(counter);
			if (flag == 0) {
				std::cout << "TCP Port is open " << counter
					  << std::endl;
			} else
				std::cout << "TCP Port Closed " << counter
					  << std::endl;
		}
	}
	if(argv[3] == U)
	{
		std::cout << "Enter port range: ";
		std::cin >> range;
		for(;counter <= range; counter++)
		{
			flag = Pi.UdpScan(counter);
			if(flag == 0)
			{
				std::cout << "UDP Port is open: " << counter << std::endl;
			}else std::cout << "UDP Port is closed: " << counter << std::endl;
		}
	}
	return 0;
}
