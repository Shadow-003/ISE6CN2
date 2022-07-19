#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define PORT 8008
#define SERVER "127.0.0.1"
#define MAX 100
int main() {
	char msg[MAX], rmsg[MAX];
	int n, sockfd;
	struct sockaddr_in srvaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(SERVER);
	srvaddr.sin_port = htons(PORT);
	connect(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
	while(1) {
		printf("Enter message to send : ");
		fgets(msg, MAX, stdin);
		if(msg[0] == '#') { break; }
		n = strlen(msg)+1;
		send(sockfd, msg, n, 0);
		n = recv(sockfd, rmsg, MAX, 0);
		printf("Received message from server : %s\n", rmsg);
	}
	return 0;
}
