#include "server.h"

using namespace std;

Server::Server(int listenPort) {
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	SetReuse(listenfd);
	ConfigServerSocket(&servaddr, listenPort);
	Bind(listenfd, &servaddr);
	Listen(listenfd, LISTENQ);	//LISTENQ = 5
}

void Server::Connect() {
	clilen = sizeof(cliaddr);

	//accept a connection
	connectfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

	//get the ip address from the connection
	inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, transferIP, INET_ADDRSTRLEN);
}

const char *Server::GetTransferIP()
{
	return transferIP;
}

int Server::GetConnectfd() {
	return connectfd;
}

int Server::GetListenfd() {
	return listenfd;
}

struct sockaddr_in* Server::GetCliaddr() {
	return &cliaddr;
}

