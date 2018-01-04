#ifndef SERVER_SELECT_H
#define SERVER_SELECT_H

#include "server.h"

using namespace std;

class Server_Select
{
public:
	Server_Select(int listenPort);
	~Server_Select() {
		printf("Closing server\n");
	}
	int Select();
	Server* GetServer();
	int GetMaxfd();
	int GetMaxi();
	fd_set* GetRset();
	fd_set* GetAllset();
	int* GetClientArray();
	void SetMaxfd(int newMaxfd);
	void SetMaxi(int newMaxi);
	void SetRset(fd_set* newSet);
	void SetAllset(fd_set* newSet);
private:
	Server *server;
	int maxfd, maxi, client[FD_SETSIZE];
	fd_set rset, allset;
};

#endif 

