#include "Library/server_select.h"

#define LISTEN_PORT 80000

int main(int argc, char **argv) {
	int nready, i, bytesRecv, bytesSent;
	int sockfd;
	char buf[BUFLEN];

	Server_Select *server = new Server_Select(LISTEN_PORT);
	int* client = server->GetClientArray();

	while(1) {
		//make sure this still works with a general select as well
		nready = server->Select();

		//check for new connection request
		if(FD_ISSET(server->GetServer()->GetListenfd(), server->GetRset())) {
			server->GetServer()->Connect();
			
			//find first open spot in the client array
			for(i = 0; i < FD_SETSIZE; i++) {
				if(client[i] < 0) {
					client[i] = server->GetServer()->GetConnectfd();
					break;
				}
			}

			//check if the client list is already full
			if(i == FD_SETSIZE) {
				fprintf(stderr, "Max number of client's reached");
				return -1;
			} 

			//add the new connection's fd
			FD_SET(server->GetServer()->GetConnectfd(), server->GetAllset()); 

			//update maxfd if connectfd is greater
			if(server->GetServer()->GetConnectfd() > server->GetMaxfd()) {
				server->SetMaxfd(server->GetServer()->GetConnectfd());
			}

			//update max index in client
			if(i > server->GetMaxi()) {
				server->SetMaxi(i); 	
			}

			//check if there is anything else was updated
			if(--nready <= 0) {
				continue;
			}
		}

		//check for incomming data
		for(i = 0; i <= server->GetMaxi(); i++) {
			//check if fd is set
			if((sockfd = client[i]) < 0) {
				continue;
			}

			if(FD_ISSET(sockfd, server->GetRset())) {
				if((bytesRecv = read(sockfd, buf, BUFLEN)) == 0) {
					close(sockfd);
					FD_CLR(sockfd, server->GetAllset());
					client[i] = -1;
				} else {
					printf("bytesRecv: %d\n", bytesRecv);
					printf("Recv: %s\n", buf);
					bytesSent = write(sockfd, buf, bytesRecv);
					printf("bytesSent: %d\n", bytesSent);

				}
			
				//check if theres anything else to check
				if(--nready <= 0) {
					break;
				}
			}
		}
	}
}

