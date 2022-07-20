#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
#define SERVER "127.0.0.1"
#define PORT 8008
int main() {
	int sockfd;
	struct sockaddr_in srvaddr;
	int n1, ans;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(SERVER);
	srvaddr.sin_port = htons(PORT);
	connect(sockfd, (struct sockaddr *)&srvaddr,sizeof(srvaddr));
	while(1) {
		printf("Enter number : ");
		scanf("%d",&n1);
		write(sockfd, &n1, sizeof(n1));
		read(sockfd, &ans, sizeof(ans));
		printf("Received answer from server : %d\n",ans);
	}
	return 0;
} 
