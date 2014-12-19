#include<iostream> 
#include"Scan.h"

int main(int argc, char *argv[])
{
	Socklib sock;
	char hostname[100];
	std::cout << "Hostname: ";
	std::cin >> hostname;
	sock.inistilizeWinSock();
	sock.gethostbyname_(hostname);
	
	int startP, EndP;
	std::cout << "Port Range " << std::endl;
	std::cout << ":";
	std::cin >> startP;
	std::cout << ":";
	std::cin >> EndP;
	
	sock.connectScan(startP,EndP);

	std::cin.get();
	return 0;
}
