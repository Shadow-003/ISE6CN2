#include<netinet/in.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
	struct sockaddr_in sa,cli;
	int n,sockfd;
	int len;
	char buff[100];
	if(argc < 2) {
		printf("Usage : %s <port>\n",argv[0]);
		exit(0);
	}
	int arg1 = atoi(argv[1]);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0) {
		printf("\nError in Socket");
		exit(0);
	}
	else
		printf("\nSocket is Opened");
	memset(&sa,0,sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_port=htons(arg1);
	if(connect(sockfd,(struct sockaddr*)&sa,sizeof(sa))<0) {
		printf("\nError in connection failed");
		exit(0);
	}
	else
		printf("\nconnected successfully");
	if(n=read(sockfd,buff,sizeof(buff))<0) {
		printf("\nError in Reading");
		exit(0);
	}
	else
		printf("\nMessage Read %s",buff);
}
