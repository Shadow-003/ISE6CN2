#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#define PORT 8008
int main()
{
	int sockfd, newsockfd, cliaddr_len, ans, n1;
	struct sockaddr_in srvaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&srvaddr,0,sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(PORT);
	bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
	listen(sockfd,5);
	while(1) {
		printf("***Server waiting for new connection***\n");
		cliaddr_len = sizeof(cliaddr);
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr,&cliaddr_len);
		printf("Connected to client...\n");
		while(1) {
			read(newsockfd, &n1, sizeof(n1));
			printf("%d\n",n1);
			ans = n1 * n1;
			write(newsockfd, &ans, sizeof(ans));
			printf("Received and set %d\n",ans);
		}
		close(newsockfd);
	}
	return 0;
}
