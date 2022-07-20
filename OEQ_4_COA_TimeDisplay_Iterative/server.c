#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
int main(int argc, char* argv[])
{
	struct sockaddr_in sa;
	struct sockaddr_in cli;int sockfd,conntfd;int len,ch;char str[100];
	time_t tick;
	if(argc < 2) {
		printf("Usage : %s <port>\n",argv[0]);
		exit(0);
	}
	int arg1 = atoi(argv[1]);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0) {
		printf("error in socket\n");
		exit(0);
	}
	else 
		printf("Socket opened");
	bzero(&sa,sizeof(sa));
	sa.sin_port=htons(arg1);
	sa.sin_addr.s_addr=htonl(0);
	if(bind(sockfd,(struct sockaddr*)&sa,sizeof(sa))<0) {
		printf("Error in binding\n");
	}
	else
		printf("Binded Successfully");
	listen(sockfd,50);
	for(;;) {
		len=sizeof(ch);
		conntfd=accept(sockfd,(struct sockaddr*)&cli,&len);
		printf("Accepted");
		tick=time(NULL);
		snprintf(str,sizeof(str),"%s",ctime(&tick));
		//printf("%s",str);
		write(conntfd,str,100);
	}
}
