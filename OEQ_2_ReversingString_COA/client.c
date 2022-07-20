#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
#define SERVER "127.0.0.1"
#define PORT 8008
#define MAX 100
int main() {
	int sockfd;
	struct sockaddr_in srvaddr;
	char str[MAX], revstr[MAX];
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(SERVER);
	srvaddr.sin_port = htons(PORT);
	connect(sockfd, (struct sockaddr *)&srvaddr,sizeof(srvaddr));
	while(1) {
		printf("Enter string : ");
		fgets(str, MAX, stdin);
		write(sockfd, &str, sizeof(str));
		read(sockfd, &revstr, sizeof(revstr));
		printf("Received answer from server : %s\n",revstr);
	}
	return 0;
} 
