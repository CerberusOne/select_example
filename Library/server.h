#ifndef SERVER_H
#define SERVER_H

#include "socketwrappers.h"
#include "client.h"
#include <netinet/in.h>
#include <iostream>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define LISTENQ 	5		//number of connections to listen for

class Server
{
public:
	Server(int listenPort);
	Server(int listenPort, struct sockaddr_in *sockInfo);
	~Server() { 
		cout << "Closing server" << endl <<  endl;	
	}
	void Connect();
	const char *GetTransferIP();
	int GetConnectfd();
	int GetListenfd();
	sockaddr_in* GetCliaddr();
private:
	int listenfd, connectfd;
	char transferIP[BUFLEN];
	struct sockaddr_in servaddr, cliaddr;
	socklen_t clilen;
};

#endif



