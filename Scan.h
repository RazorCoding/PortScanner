#ifndef SCAN_H
#define SCAN_H

class Socklib
{
public:
	struct hostent *he;
	struct in_addr **addr_list;
	struct sockaddr_in server;
	int inistilizeWinSock();
	int gethostbyname_(char hostname[]);
	void connectScan(int, int);
};
#endif
