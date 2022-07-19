#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define PORT 8008
#define MAX 100
int main() {
	int sockfd, newsockfd, cliaddr_len, n;
	struct sockaddr_in srvaddr,cliaddr;
	char msg[MAX];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(PORT);
	bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
	listen(sockfd,1);
	while(1) {
		printf("***Waiting for new connection***\n");
		cliaddr_len = sizeof(cliaddr);
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		while(1) {
			n = recv(newsockfd, msg, MAX, 0);
			if(n==0) {
				close(newsockfd);
				break;
			}
			msg[n] = 0;
			send(newsockfd,msg,n,0);
			printf("Received and set : %s\n",msg);
		}
	}
	return 0;
}
