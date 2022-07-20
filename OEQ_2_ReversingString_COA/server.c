#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#define PORT 8008
#define MAX 100
int main()
{
	int sockfd, newsockfd, cliaddr_len;
	struct sockaddr_in srvaddr, cliaddr;
	char str[MAX], temp[MAX], temp1;
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
			read(newsockfd, &str, sizeof(str));
			strcpy(temp,str);
			int len = strlen(temp);
			for(int i = 0; i<len/2; i++) {
				temp1 = temp[i];
				temp[i] = temp[len - i -1];
				temp[len -i -1] = temp1;
			}
			write(newsockfd, &temp, sizeof(temp));
		}
		close(newsockfd);
	}
	return 0;
}
