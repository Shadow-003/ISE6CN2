#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#define PORT 8008
int main()
{
	char op;
	int pid, sockfd, newsockfd, cliaddr_len, ans, n1, n2;
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
		pid = fork();
		if(pid == 0) {
			while(1) {
				read(newsockfd, &op, sizeof(op));
				read(newsockfd, &n1, sizeof(n1));
				read(newsockfd, &n2, sizeof(n2));
				printf("%d\t%c\t%d\n",n1,op,n2);
				switch(op) {
					case '+' : ans = n1+n2;
						break;
					case '-' : ans = n1-n2;
						break;
					case '*' : ans = n1*n2;
						break;
					case '/' : ans = n1/n2;
						break;
					default : break;
				}
				write(newsockfd, &ans, sizeof(ans));
				printf("Received and set %d\n",ans);
			}
			exit(0);
		}
		else {
			close(newsockfd);
		}
	}
	return 0;
}
