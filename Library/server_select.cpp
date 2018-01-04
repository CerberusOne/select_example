#include "server_select.h"

using namespace std;

Server_Select::Server_Select(int listenPort) {
	server = new Server(listenPort);
	maxfd = server->GetListenfd();
	maxi = -1;
	
	for(int i = 0; i < FD_SETSIZE; i++) {
		client[i] = -1;
	}

	FD_ZERO(&allset);
	FD_SET(server->GetListenfd(), &allset);
}

int Server_Select::Select() {
	rset = allset;
	return select(maxfd + 1, &rset, NULL, NULL, NULL);
}

Server* Server_Select::GetServer() {
	return server;
}

int Server_Select::GetMaxfd() {
	return maxfd;
}

int Server_Select::GetMaxi() {
	return maxi;
}

int* Server_Select::GetClientArray() {
	return client;
}

fd_set* Server_Select::GetRset() {
	return &rset;
}

fd_set* Server_Select::GetAllset() {
	return &allset;
}

void Server_Select::SetMaxfd(int newMaxfd) {
	maxfd = newMaxfd;
}

void Server_Select::SetMaxi(int newMaxi) {
	maxi = newMaxi;
}
void Server_Select::SetRset(fd_set* newSet) {
	rset = *newSet;
}

void Server_Select::SetAllset(fd_set* newSet) {
	allset = *newSet;
}

